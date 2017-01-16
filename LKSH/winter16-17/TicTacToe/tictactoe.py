#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import logging
import collections
import enum
import multiprocessing.pool

__author__ = 'Andrew Gein <andgein@yandex.ru>'


class AbstractPlayer:
    def __init__(self, player_type):
        self.player_type = player_type

    def move(self, board):
        raise NotImplementedError()

    def __str__(self):
        raise NotImplementedError()


class Bot(AbstractPlayer):
    NAME = 'UNKNOWN NAME'
    AUTHOR = 'UNKNOWN AUTHOR'

    def move(self, board):
        raise NotImplementedError()

    def __str__(self):
        return 'Бот %s (%s)' % (self.__class__.__name__, self.get_bot_name_and_author())

    @classmethod
    def get_bot_name_and_author(cls):
        return '%s, %s' % (cls.NAME, cls.AUTHOR)


class ConsolePlayer(AbstractPlayer):
    def move(self, board):
        print('Текущее состояние поля:')
        board.print()
        while True:
            print('Ваш ход? Введите два числа через пробел, номер строки и номер столбца.')
            try:
                move = list(map(int, input().split()))
            except ValueError:
                print('Неправильный формат. Введите два числа через пробел, номер строки и номер столбца.')
                continue
            if len(move) != 2:
                print('Неправильный формат. Введите два числа через пробел, номер строки и номер столбца.')
                continue
            return Move(move[0], move[1])

    def __str__(self):
        return 'Человек'


class BoardCell(enum.Enum):
    EMPTY = 0
    X = 1
    O = 2

    def __str__(self):
        if self == BoardCell.X:
            return 'X'
        elif self == BoardCell.O:
            return 'O'
        elif self == BoardCell.EMPTY:
            return ' '


class PlayerType(enum.Enum):
    X = 1
    O = 2

    def inverse(self):
        return PlayerType(3 - self.value)

    def __str__(self):
        if self == PlayerType.X:
            return 'крестики'
        if self == PlayerType.O:
            return 'нолики'


class Winner(enum.Enum):
    X = 1
    O = 2
    DRAW = 3


class IncorrectMove(Exception):
    pass


class GameBoard:
    def __init__(self):
        self.size = 3
        self.board = [[BoardCell.EMPTY] * self.size for _ in range(self.size)]

    def apply_move(self, player_type, move):
        if move.row < 0 or move.row >= self.size or move.column < 0 or move.column >= self.size:
            raise IncorrectMove(
                'Клетка (%d, %d) имеет неправильные координаты. Все координаты должны быть от 0 до %d' % (
                    move.row, move.column, self.size - 1
                ))
        if self.board[move.row][move.column] != BoardCell.EMPTY:
            raise IncorrectMove('Клетка (%d, %d) не пуста' % (move.row, move.column))

        new_cell = BoardCell(player_type.value)
        self.board[move.row][move.column] = new_cell

    def is_full(self):
        for row in range(self.size):
            for column in range(self.size):
                if self.board[row][column] == BoardCell.EMPTY:
                    return False
        return True

    @staticmethod
    def _is_cells_full_by_player(cells):
        elements = list(set(cells))
        if len(elements) != 1:
            return False

        if elements[0] != BoardCell.EMPTY:
            return Winner(elements[0].value)

        return False

    def _get_column(self, column_id):
        return [row[column_id] for row in self.board]

    def get_winner(self):
        if self.is_full():
            return Winner.DRAW

        for row in range(self.size):
            winner = self._is_cells_full_by_player(self.board[row])
            if winner:
                return winner

        for column in range(self.size):
            winner = self._is_cells_full_by_player(self._get_column(column))
            if winner:
                return winner

        winner = self._is_cells_full_by_player([self.board[0][0], self.board[1][1], self.board[2][2]])
        if winner:
            return winner
        winner = self._is_cells_full_by_player([self.board[0][2], self.board[1][1], self.board[2][0]])
        if winner:
            return winner

        return False

    def __getitem__(self, item):
        return self.board[item]

    def print(self, via_logging=False):
        print_function = print
        if via_logging:
            print_function = logging.info

        print_function('  ' + ' '.join(str(x) for x in range(self.size)))
        for row in range(self.size):
            print_function(str(row) + ' ' + ' '.join(str(BoardCell(x)) for x in self.board[row]))

    def create_copy_for_player(self):
        board_copy = GameBoard()
        board_copy.board = [[cell.value for cell in row] for row in self.board]
        return board_copy


class Move(collections.namedtuple('Move', ('row', 'column'))):
    pass


class Game:
    INCORRECT_MOVE_TRIES_LIMIT = 5
    BOT_MOVE_TIMEOUT = 3  # в секундах

    def __init__(self, x_player_factory: callable, o_player_factory: callable):
        self.x_player = x_player_factory(PlayerType.X.value)
        self.o_player = o_player_factory(PlayerType.O.value)
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

    def _make_one_move(self):
        current_player = self.x_player if self.current_move == PlayerType.X else self.o_player
        if self.current_move == PlayerType.X:
            self.move_counter += 1

        logging.info("Ход №%d игрока «%s» за %s:" % (self.move_counter, current_player, self.current_move))
        # Несколько раз пытаемся узнать ход, пока пользователь или бот не сделает корректный ход
        try_index = 1
        while try_index < self.INCORRECT_MOVE_TRIES_LIMIT:
            try:
                if isinstance(current_player, Bot):
                    timeout = self.BOT_MOVE_TIMEOUT
                else:
                    timeout = None

                board_copy = self.board.create_copy_for_player()
                try:
                    move = self._safe_run(timeout, current_player.move, (board_copy, ), {})
                    logging.info(move)
                except Exception as e:
                    logging.error('Произошла ошибка при попытке сделать ход: %s' % e)
                    logging.exception(e)
                    raise IncorrectMove('Произошла ошибка при попытке сделать ход: %s' % e)

                if not isinstance(move, Move):
                    raise IncorrectMove('Игрок вернул объект не типа Move. Используйте констукцию '
                                        'return Move(row, column) в ваших ботах')
                self.board.apply_move(self.current_move, move)
            except IncorrectMove as e:
                logging.info('Неправильный ход. %s' % e)
            else:
                break

            try_index += 1
            logging.info('Пытаюсь получить ход ещё раз. Попытка №%d:' % (try_index,))
        else:
            logging.info('Не удалось получить нормальный ход за %d попыток от игрока %s' % (
                self.INCORRECT_MOVE_TRIES_LIMIT,
                current_player
            ))
            logging.info('Засчитываю автоматический проигрыш')
            self.winner = Winner(self.current_move.inverse().value)
            return

        self.current_move = self.current_move.inverse()

    def _init_game(self):
        self.board = GameBoard()
        self.current_move = PlayerType.X
        self.move_counter = 0
        self.winner = None

    def _is_game_finished(self):
        return self.winner is not None

    def _check_for_winner(self):
        winner = self.board.get_winner()
        if winner:
            self.winner = winner

    def _show_finish_game_message(self):
        if self.winner != Winner.DRAW:
            finish_message = 'Победили %s!' % (str(PlayerType(self.winner.value)), )
        else:
            finish_message = 'Ничья!'
        logging.info('*** %s ***' % (finish_message, ))

        if any(not isinstance(p, Bot) for p in self.players):
            self.board.print()

    @property
    def players(self):
        return [self.x_player, self.o_player]

    def play(self):
        self._init_game()

        while not self._is_game_finished():
            self._make_one_move()
            self._check_for_winner()

        self._show_finish_game_message()

        return self.winner

if __name__ == '__main__':
    import sys


    class StupidBot(Bot):
        NAME = 'Глупый бот'
        AUTHOR = 'Андрей Гейн'

        def move(self, board):
            for row in range(board.size):
                for column in range(board.size):
                    if board[row][column] == 0:
                        return Move(row, column)


    class StupidPrinterBot(StupidBot):
        def move(self, board):
            for row in range(board.size):
                for column in range(board.size):
                    if board[row][column] == self.player_type:
                        print('Нашёл свою клетку: %d, %d' % (row, column))
            return super().move(board)


    class SlowBot(Bot):
        NAME = 'Медленный бот'
        AUTHOR = 'Андрей Гейн'

        def move(self, board):
            import time
            time.sleep(5)


    logging.basicConfig(level=logging.DEBUG, stream=sys.stdout,
                        format='%(asctime)s [%(levelname)s] %(message)s')
    game = Game(StupidBot, StupidPrinterBot)
    game.play()
    game.board.print()
