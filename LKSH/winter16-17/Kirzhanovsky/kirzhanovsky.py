#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import copy
import logging
import multiprocessing.pool
import operator

__author__ = 'Andrew Gein <andgein@yandex.ru>'


class AbstractPlayer:
    def __init__(self, players_count):
        self.players_count = players_count

    def move(self, history):
        raise NotImplementedError()

    def __str__(self):
        raise NotImplementedError()


class Bot(AbstractPlayer):
    NAME = 'UNKNOWN NAME'
    AUTHOR = 'UNKNOWN AUTHOR'

    def move(self, history):
        raise NotImplementedError()

    def __str__(self):
        return 'Бот %s (%s)' % (self.__class__.__name__, self.get_bot_name_and_author())

    @classmethod
    def get_bot_name_and_author(cls):
        return '%s, %s' % (cls.NAME, cls.AUTHOR)


class ConsolePlayer(AbstractPlayer):
    def move(self, history):
        if len(history):
            print('История ходов:')
        for round_id, round in enumerate(history):
            print('(раунд %d)' % (round_id + 1, ), *round)
        while True:
            print('РАУНД %d. Ваш ход? Введите одно число от 1 до %d.' % (len(history), self.players_count, ))
            try:
                move = int(input())
            except ValueError:
                print('Неправильный формат. Введите одно число от 1 до %d.' % (self.players_count, ))
                continue
            return move

    def __str__(self):
        return 'Человек'


class IncorrectMove(Exception):
    pass


class Game:
    INCORRECT_MOVE_TRIES_LIMIT = 5
    BOT_MOVE_TIMEOUT = 3  # в секундах
    ROUNDS_IN_GAME = 100

    def __init__(self, players):
        self.players = [player(len(players)) for player in players]
        self._init_game()

    @staticmethod
    def _safe_run(timeout, function, args, kwargs):
        """ Запускает функцию function с таймаутом на выполнение """
        try:
            pool = multiprocessing.pool.ThreadPool(processes=1)
            async_result = pool.apply_async(function, args, kwargs)
            # Кидает исключение TimeoutError если исполнение превысило timeout секунд
            return async_result.get(timeout)
        except multiprocessing.context.TimeoutError:
            logging.info('Превышено время ожидания ответа: %d секунд' % (timeout,))
            return None

    def _safe_move(self, player):
        try_index = 1
        while try_index < self.INCORRECT_MOVE_TRIES_LIMIT:
            try:
                if isinstance(player, Bot):
                    timeout = self.BOT_MOVE_TIMEOUT
                else:
                    timeout = None

                history_copy = copy.deepcopy(self.history)
                try:
                    move = self._safe_run(timeout, player.move, (history_copy,), {})
                    logging.info('Ход игрока %s: %d' % (str(player), move))
                    if move < 1 or move > len(self.players):
                        raise IncorrectMove('неправильное значение. Должно быть число от 1 до %d' % (len(self.players), ))
                except Exception as e:
                    logging.error('Произошла ошибка при попытке сделать ход: %s' % e)
                    logging.exception(e)
                    raise IncorrectMove('Произошла ошибка при попытке сделать ход: %s' % e)

                if not isinstance(move, int):
                    raise IncorrectMove('Игрок вернул объект не типа int. Используйте констукцию '
                                        'return number в ваших ботах')
            except IncorrectMove as e:
                logging.info('Неправильный ход. %s' % e)
            else:
                break

            try_index += 1
            logging.info('Пытаюсь получить ход ещё раз. Попытка №%d:' % (try_index,))
        else:
            logging.info('Не удалось получить нормальный ход за %d попыток от игрока %s' % (
                self.INCORRECT_MOVE_TRIES_LIMIT,
                player
            ))
            logging.info('Засчитываю автоматический проигрыш в раунде')
            return -1

        return move

    def _make_one_move(self):
        self.move_number += 1
        logging.info('Ход %d' % (self.move_number, ))
        moves = [self._safe_move(player) for player in self.players]
        self.history.append(moves)

    def _init_game(self):
        self.history = []
        self.move_number = 0
        self.winner = None

    def _is_game_finished(self):
        return self.move_number == self.ROUNDS_IN_GAME

    def _show_finish_game_message(self):
        logging.info('*** Победил игрок %d: %s ***' % (self.winner, str(self.players[self.winner])))

        if any(not isinstance(p, Bot) for p in self.players):
            print('История ходов:')
            for row in self.history:
                print(*row)

    def _find_winner(self):
        scores = [0] * len(self.players)
        for round_id, round in enumerate(self.history):
            counts = {x: round.count(x) for x in set(round)}
            for player_id, player_move in sorted(enumerate(round), key=operator.itemgetter(1)):
                if counts[player_move] == 1:
                    logging.info('В раунде %d победил игрок %s и получил %d очков' % (
                        round_id + 1,
                        self.players[player_id],
                        player_move
                    ))
                    scores[player_id] += player_move
                    break

        max_score = max(scores)
        best_players = [i for i, x in enumerate(scores) if x == max_score]
        if len(best_players) != 1:
            logging.info('Несколько игроков набрали максимум очков (%d), продолжаем играть' % (max_score, ))
            return False

        self.winner = best_players[0]
        return True

    def play(self):
        self._init_game()

        while not self._is_game_finished():
            self._make_one_move()
        while not self._find_winner():
            self._make_one_move()

        self._show_finish_game_message()

        return self.winner


if __name__ == '__main__':
    import sys


    class StupidBot(Bot):
        NAME = 'Глупый бот'
        AUTHOR = 'Андрей Гейн'

        def move(self, history):
            return 1


    class StupidPrinterBot(StupidBot):
        def move(self, history):
            print('История из StupidPrinterBot:', history)
            return 2


    class SlowBot(Bot):
        NAME = 'Медленный бот'
        AUTHOR = 'Андрей Гейн'

        def move(self, history):
            import time
            time.sleep(5)


    logging.basicConfig(level=logging.DEBUG, stream=sys.stdout,
                        format='%(asctime)s [%(levelname)s] %(message)s')
    game = Game([ConsolePlayer, StupidBot])

    # Вручную уменьшаем количество раундов в игре, чтобы было проще отлаживать код
    game.ROUNDS_IN_GAME = 10
    game.play()
