#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice
from time import sleep
import telebot


TELEBOT_TOKEN = '387551779:AAFgjp-9MRrW2Dqy_v6PlaH61CT-uDDnZoo'
TeleBot = telebot.TeleBot(TELEBOT_TOKEN)
ADMIN_ID = [150486866]

TO_STOP = False


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
        return 'Ставка засчитана. Осталось {} очков.'.format(player.points)

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
    def __init__(self, id, width, height, start_points, admin, min_players, 
                 max_players):
        self.id = id
        self.map = [[Tyle(j, i, choices([_ for _ in range(4)], [1, 4, 3, 2]) + 2) 
                                for i in range(height)] for j in range(width)]
        self.map[randint(0, width - 1)][randint(0, height - 1)].bonus = 7
        self.width = width
        self.height = height
        self.start_points = start_points
        self.admin = admin
        self.min_players = min_players
        self.max_players = max_players

        self.players = []
        self.results = None
        self.running = False
        self.round = 0

    def add_player(self, player):
        if player not in self.players:
            self.players.append(player)
            player.world = self
            if len(self.players) >= self.min_players:
                self.running = True
            return 'Вы успешно присоединились к миру.'
        elif player.world is not self:
            player.World = self
            return 'Вы успешно присоединились к миру.'
        else:
            return 'Вы уже присоединены к этому миру.'

    def new_round(self):
        self.round += 1
        width = self.width
        height = self.height
        self.map = [[Tyle(j, i, choices([_ for _ in range(4)], [1, 4, 3, 2]) + 2) 
                                for i in range(height)] for j in range(width)]
        self.map[randint(0, width - 1)][randint(0, height - 1)].bonus = 5
        for player in self.players:
            player.points = self.start_points
        self.results = None

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

    def get_to_show(self):
        to_return = ''
        for x in range(self.height):
            for y in range(self.width):
                self.map[y][x].update()
                to_return = to_return + self.map[y][x].symb + ' '
            to_return = to_return + '\n'
        return to_return


class Player(object):
    def __init__(self, user, name, world_id=None):
        self.user = user
        self.name = name

        self.points = WORLDS[world_id].start_points
        self.score = 0
        self.last_round_score = 0
        if world_id:
            self.join_world(world_id)

    def __repr__(self):
        return str(self.name)

    def join_world(self, world_id):
        if world_id in WORLDS:
            return WORLDS[world_id].add_player(self)
        else:
            return 'Мира с таким названием не существует.'

    def bet(self, x, y, count):
        if self.world is None:
            return 'Вы не участвуете в игре'
        else:
            return self.world.bet(self, x, y, count)


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


#===== TELEGRAMM INTERFACE ===================================================
class User(object):
    def __init__(self, telegramm_id, name):
        self.id = telegramm_id
        self.name = name
        self.worlds = []
        self.players = []
        self.victory_count = 0

    def join_world(self, world_id):
        if world_id not in WORLDS:
            return 'Мира с таким названием не существует.'
        if WORLDS[world_id] in self.worlds:
            return 'Вы уже присоединены к этому миру.'

        world = WORLDS[world_id]
        new_player = Player(self, self.name, world.id)
        self.worlds.append(world)
        self.players.append(new_player)
        return 'Вы успешно присоединились к миру.'


def user_by_id(user_id):
    if user_id in USERS:
        return USERS[user_id]
    else:
        return None


def world_by_id(world_id):
    if world_id in WORLDS:
        return WORLDS[world_id]
    else:
        return None


def player_by_world(user, world):
    if world in user.worlds:
        return user.players[user.worlds.index(world)]
    else:
        return None


def send_to_all_in_world(world, message):
    if world is None or not message:
        return 0

    for player in world.players:
        TeleBot.send_message(player.user.id, message)


def warn_invalid_args(chat_id):
    TeleBot.send_message(chat_id, 'Некоректные аргументы. ' + 
                                  '/input_help для помощи.')


def warn_world_not_exist(chat_id):
    TeleBot.send_message(chat_id, 'Такого мира не существует.')


def warn_invalid_coords(chat_id):
    TeleBot.send_message(chat_id, 'Введенные координаты не подходят.')


def warn_invalid_points(chat_id):
    TeleBot.send_message(chat_id, 'Операция с таким количеством очков не ' +
                                  'возможна')


def warn_invalid_sizes(chat_id):
    TeleBot.send_message(chat_id, 'Операция не возможна с данными размерами.')


def warn_player_not_in_world(chat_id):
    TeleBot.send_message(chat_id, 'Вы не участвуете в этом мире.')


def warn_player_not_admin(chat_id):
    TeleBot.send_message(chat_id, 'Вы не админ в этом мире.')


def warn_world_not_running_not_enough_players(chat_id):
    TeleBot.send_message(chat_id, 'Этот мир еще не запущен, надо больше ' +
                                  'игроков.')


@TeleBot.message_handler(commands=['stop'])
def command_start(message):
    if message.chat.id in ADMIN_ID:
        TeleBot.send_message(message.chat.id, 'Остановлен.')
        print('Killed by {}'.format(message.chat.first_name))
        global TO_STOP
        TO_STOP = True


@TeleBot.message_handler(commands=['rules'])
def command_rules(message):
    chat = message.chat
    TeleBot.send_message(chat.id, open('rules.txt', 'r').read())


@TeleBot.message_handler(func=lambda x: True)
def message_handler(message):
    if TO_STOP:
        print('ok')
        exit(0)

    chat = message.chat
    text = message.text
    user = user_by_id(chat.id)
    print('Got message from {}: {}'.format(chat.first_name, text))
    if user is None and text != '/start':
        TeleBot.send_message(chat.id, 'Напишите мне, пожалуйста, /start, ' +
                             'чтобы я добавил вас в список пользователей')
        return 0

    if text == '/start':
        TeleBot.send_message(chat.id, 'Привет. Правила доступны по /rules, ' +
                                      'помощь - по /help')
        USERS[chat.id] = User(chat.id, chat.first_name)

    if text.startswith('/new_world'):
        args = text[11:].split('_')
        print('Starting new world with args: {}'.format(args))
        if len(args) != 6:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        if world_id in WORLDS:
            TeleBot.send_message(user.id, 'Мир с таким названием уже' +
                                          'существует.')
            return None

        try:
            width = int(args[1])
            height = int(args[2])
        except Exception:
            warn_invalid_args(user.id)
            return None
        if width < 1 or height < 1:
            warn_invalid_sizes(user.id)

        try:
            start_points = int(args[3])
        except Exception:
            warn_invalid_args(user.id)
            return None
        if start_points < 1:
            warn_invalid_points(user.id)
            return None

        try:
            min_players = int(args[4])
            max_players = int(args[5])
        except Exception:
            warn_invalid_args(user.id)
            return None
        if min_players < 0 or max_players < min_players:
            warn_invalid_args(user.id)
            return None
        
        new_world = World(world_id, width, height, start_points, user, 
                          min_players, max_players)
        WORLDS[world_id] = new_world
        TeleBot.send_message(user.id, 'Мир успешно создан.\n' +
                             '/join_{0} /info_{0} /show{0}'.format(world_id))
        print('World "{}" created by {}'.format(world_id, chat.first_name))

    if text.startswith('/info'):
        args = text[6:].split('_')
        if len(args) != 1:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        world = world_by_id(world_id)
        if world is None:
            warn_world_not_exist(user.id)
            return None

        world_info = ''
        world_info = world_info + 'Мир {}\n'.format(world.id)
        world_info = world_info + 'Игроки: {}/{}\n'.format(len(world.players), 
                                                           world.max_players)
        for player in world.players:
            world_info = world_info + '  {}\n'.format(player.name)
        if world in user.worlds:
            world_info = world_info + 'Ваши очки: {}'.format(
                player_by_world(user, world).points)
        else:
            world_info = world_info + 'Вы не участвуете в мире.'

        TeleBot.send_message(user.id, world_info)

    if text.startswith('/join'):
        args = text[6:].split('_')
        if len(args) not in [1, 2]:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        if world_id not in WORLDS:
            warn_world_not_exist(user.id)
            return None

        TeleBot.send_message(user.id, user.join_world(world_id))

    if text.startswith('/show'):
        args = text[6:].split('_')
        if len(args) != 1:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        world = world_by_id(world_id)
        if world is None:
            warn_world_not_exist(user.id)
            return None

        TeleBot.send_message(user.id, world.get_to_show())

    if text.startswith('/bet'):
        args = text[5:].split('_')
        if len(args) != 4:
            warn_invalid_args(user.id)
            return None

        world = world_by_id(args[0])
        if world is None:
            warn_world_not_exist(user.id)
            return None
        if world not in user.worlds:
            warn_player_not_in_world(user.id)
            return None
        if not world.running:
            warn_world_not_running_not_enough_players(user.id)
            return None
        try:
            x = int(args[1])
            y = int(args[2])
        except Exception:
            warn_invalid_args(user.id)
            return 0
        if x < 1 or x > world.width or y < 1 or y > world.height:
            warn_invalid_coords(user.id)
            return None
        x -= 1
        y -= 1
        try:
            points_to_bet = int(args[3])
        except Exception:
            warn_invalid_args(user.id)
        if points_to_bet < 1:
            warn_invalid_points(user.id)
            return None

        bet_result = \
            player_by_world(user, world).bet(x, y, points_to_bet)
        TeleBot.send_message(user.id, bet_result)

    if text.startswith('/end_round'):
        args = text[11:].split('_')
        if len(args) != 1:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        world = world_by_id(world_id)
        if world is None:
            warn_world_not_exist(user.id)
            return None
        if world not in user.worlds:
            warn_player_not_in_world(user.id)
            return None
        if user != world.admin:
            warn_player_not_admin(user.id)
            return None
        if not world.running:
            warn_world_not_running_not_enough_players(user.id)
            return None

        world.full_capture()
        results = world.get_formated_results()
        for player in world.players:
            TeleBot.send_message(player.user.id, results)
            TeleBot.send_message(user.id, '/show_{}'.format(world.id))

    if text.startswith('/new_round'):
        args = text[11:].split('_')
        if len(args) != 1:
            warn_invalid_args(user.id)
            return None

        world_id = args[0]
        world = world_by_id(world_id)
        if world is None:
            warn_world_not_exist(user.id)
            return None
        if world not in user.worlds:
            warn_player_not_in_world(user.id)
            return None
        if user != world.admin:
            warn_player_not_admin(user.id)
            return None
        if not world.running:
            warn_world_not_running_not_enough_players(user.id)
            return None

        world.new_round()
        to_send = ''
        to_send = to_send + 'Новый раунд в мире {}\n'.format(world.id)
        to_send = to_send + '/info_{0}\n/show_{0}'.format(world.id)
        send_to_all_in_world(world, to_send)

    if text == '/lobby':
        lobby_worlds = 'Доступные миры:\n'
        for world_id in WORLDS:
            world = WORLDS[world_id]
            lobby_worlds = lobby_worlds + '/join_{} {}/{}\n'.format(
                world.id, len(world.players), world.max_players)
        
        TeleBot.send_message(user.id, lobby_worlds)

    if text.startswith('/message'):
        args = text[9:].split('_')
        world_id = args[0]
        world = world_by_id(world_id)
        if world is None:
            warn_world_not_exist(user.id)
            return None
        if world not in user.worlds and user != world.admin:
            warn_player_not_in_world(user.id)
            return None
        player = player_by_world(user, world)
        if user == world.admin:
            message = '[Admin]'
        else:
            message = ''
        message = message + '{}({}): '.format(player.name, world.id) + args[1]
        send_to_all_in_world(world, message)



def main():
    global WORLDS
    global USERS
    WORLDS = {}
    USERS = {}
    TeleBot.polling(interval=3)


if __name__ == "__main__":
    main()
