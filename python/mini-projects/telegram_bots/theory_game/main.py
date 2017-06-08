#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice


PLAYERS = {'name' : 'player'}


class Tyle(object):
    def __init__(self, x, y, bonus, owner=None):
        self.x = x
        self.y = y
        self.bonus = bonus
        self.owner = owner

        self.last_round_bonus = 0
        self.score = 0
        self.bets = {}

        self.update()

    def update(self):
        if self.owner is None:
            self.symb = str(self.bonus)
        else:
            self.symb = self.owner.name[0]

    def bet(self, player, count):
        if player.points < count:
            return 'Недостаточно очков для ставки.'
        if player in self.bets:
            self.bets[player] += count
        else:
            self.bets[player] = count
        player.points -= count
        self.score += count
        return 'Ставка засчитана.'

    def find_winners(self):
        winners = []
        winning_score = 0
        bets = self.bets
        for player in bets:
            if bets[player] > winning_score:
                winners = [player]
                winning_score = bets[player]
            elif bets[player] == winning_score:
                winners.append(player)
        return winners, winning_score

    def capture(self):
        full_score = self.score + self.bonus
        bets = self.bets
        winners, winning_score = self.find_winners()
        self.last_round_bonus = self.bonus

        if len(winners) == 0:
            pass
        elif len(winners) == 1:
            winner = winners[0]
            self.owner = winner
            winner.score += full_score
            winner.last_round_score += full_score
        elif len(winners) > 1:
            self.bonus = full_score

        self.score = 0
        self.update()
        return winners, winning_score, bets, full_score

    def dump(self):
        print('Tyle[{}][{}] Score[{}] Bets: {}'.format(self.x, self.y, 
                                                       self.score, self.bets))


class World(object):
    def __init__(self, width, height, players, id=1):
        self.map = [[Tyle(j, i, choices([_ for _ in range(4)], [1, 4, 3, 2])) 
                                for i in range(height)] for j in range(width)]
        self.map[randint(0, width - 1)][randint(0, height - 1)].score = 5
        self.width = width
        self.height = height
        self.results = None
        
        self.players = players
        for player in players:
            player.world = self

    def bet(self, player, x, y, count):
        if player not in self.players:
            return 'Something went wrong'
        if player.points < count:
            return 'Недостаточно очков для ставки.'
        return self.map[x][y].bet(player, count)

    def full_capture(self):
        world_map = self.map
        results = []
        for x in range(self.width):
            for y in range(self.height):
                tyle = world_map[x][y]
                winners, winning_score, bets, score = tyle.capture()
                if winners is None:
                    pass
                elif len(winners) >= 1:
                    results.append((tyle, winners, winning_score, bets, score))
                    tyle.bets = {}
        round_max_score = -1
        round_winner = None
        for player in self.players:
            if player.score > round_max_score:
                round_winner = player
                round_max_score = player.score
            player.last_round_score = player.score
            player.score = 0

        self.results = results
        self.round_winner = round_winner
        self.round_max_score = round_max_score
        return results, (round_winner, round_max_score)

    def get_formated_results(self):
        results = self.results
        to_return = ''
        for res in results:
            tyle = res[0]
            winners = res[1]
            winning_score = res[2]
            bets = res[3]
            score = res[4]

            to_return = to_return + 'Клетка [{}][{}] (бонус {}):\n'.format(
                tyle.x, tyle.y, tyle.last_round_bonus)
            for player in bets:
                to_return = to_return + '  {} - {}\n'.format(bets[player], 
                                                             player)
            to_return = to_return + '--------------\n'
            to_return = to_return + '{} '.format(score)
            if len(winners) == 1:
                to_return = to_return + '-> {}\n\n'.format(winners[0])
            else:
                to_return = to_return + 'уходят в бонус, ничья.\n\n'
        to_return = to_return + '\n'
        for player in self.players:
            to_return = to_return + '{}: {} очков\n'.format(
                player.name, player.last_round_score)
        to_return = to_return + '-----\n'
        to_return = to_return + 'Победитель: {}. Очки: {}\n'.format(
            self.round_winner, self.round_max_score)

        return to_return

    def console_show(self):
        for x in range(self.height):
            for y in range(self.width):
                self.map[x][y].update()
                print(self.map[y][x].symb, end=' ')
            print()


class Player(object):
    def __init__(self, name, points, world=None):
        self.name = name
        self.points = points
        self.world = world
        self.score = 0
        self.last_round_score = 0
        self.winning_count = 0

    def __repr__(self):
        return str(self.name)

    def bet(self, x, y, count):
        if self.world is None:
            return 'Вы не участвуете в игре'
        else:
            self.world.bet(x, y, self, count)


def choices(population, weights=None, k=1):
    if weights is None:
        randomizing_arr = population
    elif len(weights) != len(population):
        raise IndexError
    else:
        randomizing_arr = []
        for i in range(len(population)):
            for j in range(weights[i]):
                randomizing_arr.append(population[i])

    result_arr = []
    for i in range(k):
        result_arr.append(choice(randomizing_arr))

    if len(result_arr) == 1:
        return result_arr[0]
    else:
        return result_arr


def parse_console_input(string):
    word_arr = string.split()
    if word_arr[1] == 'bet':
        print(world.bet(player_by_name(word_arr[0]), int(word_arr[2]), 
                        int(word_arr[3]), int(word_arr[4])))


def player_by_name(name):
    if name not in PLAYERS:
        return None
    else:
        return PLAYERS[name]


def name_by_id(player):
    for name in PLAYERS:
        if PLAYERS[name] == player:
            return PLAYERS[name]
    return ''


def main():
    one = Player('One', 9)
    two = Player('Two', 9)
    PLAYERS[one.name] = one
    PLAYERS[two.name] = two

    global world
    world = World(3, 3, [one, two])
    world.console_show()
    print()

    for i in range(5):
        parse_console_input(input())
    print()

    world.full_capture()
    print(world.get_formated_results())
    world.console_show()


if __name__ == "__main__":
    main()
