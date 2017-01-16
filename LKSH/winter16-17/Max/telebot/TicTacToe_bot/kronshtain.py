#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from tictactoe import Game, Bot, Move, ConsolePlayer

import logging
import sys
from random import randint


class MyBot(Bot):
    """
    Этот класс — в целом всё, что необходимо, чтобы создать своего бота.
    Во всех функциях этого класса доступна переменная games[chat_id]["bot"], которая равна 1,
    если ваш бот играет за крестики, и 2, если за нолики.
    """

    # Укажите здесь имя вашего бота
    NAME = 'Trunder.shtormer'

    # Укажите здесь ваше имя
    AUTHOR = 'Max Gorishny'

    inf = 1000000

    win_lines = [[(0, 0), (0, 1), (0, 2)],    \
                 [(1, 0), (1, 1), (1, 2)],    \
                 [(2, 0), (2, 1), (2, 2)],    \
                 [(0, 0), (1, 0), (2, 0)],    \
                 [(0, 1), (1, 1), (2, 1)],    \
                 [(0, 2), (1, 2), (2, 2)],    \
                 [(0, 0), (1, 1), (2, 2)],    \
                 [(0, 2), (1, 1), (2, 0)],]
    

    def check_near_win_and_turn(self, games[chat_id]["board"], symb):
        counter = 0
        if games[chat_id]["bot"] == 1:
            other = 2
        else:
            other = 1
        for i in self.win_lines:
            for j in range(len(i)):
                if games[chat_id]["board"][i[j][0]][i[j][1]] == symb:
                    counter += 1
                    if counter == 2:
                        if j == 1:
                            if games[chat_id]["board"][i[2][0]][i[2][1]] == 0:
                                return (i[2][0], i[2][1])
                        elif j == 2:
                            if games[chat_id]["board"][i[1][0]][i[1][1]] == symb and games[chat_id]["board"][i[0][0]][i[0][1]] == 0:
                                return (i[0][0], i[0][1])
                            elif games[chat_id]["board"][i[0][0]][i[0][1]] == symb:
                                return (i[1][0], i[1][1])
                    if counter == 3:
                        return (-1, -1)
            counter = 0
        return (3, 3)

    turn = 0
    first_launch = 0

    def move(self, games[chat_id]["board"]):
        if games[chat_id]["bot"] == 1:
            other = 2
        else:
            other = 1

        if self.first_launch == 0:
            if games[chat_id]["bot"] == 1:
                self.first_launch = 1
                return Move(1, 1)
            else:
                self.first_launch = 1
                return Move(0, 0)
            
        ret1 = self.check_near_win_and_turn(games[chat_id]["board"], games[chat_id]["bot"])
        ret2 = self.check_near_win_and_turn(games[chat_id]["board"], other)

        if ret1 == (3, 3):
            ret = ret2
        else:
            ret = ret1
        if ret == (-1, -1):
            print("WAAAAAAAAAAAAAAAAAAAAAT")
            while True:
                x = randint(0, 2)
                y = randint(0, 2)
                if games[chat_id]["board"][x][y] == 0:
                    return Move(x, y)
        print(ret)
        if ret == (3, 3) or games[chat_id]["board"][ret[0]][ret[1]] != 0:
            while True:
                x = randint(0, 2)
                y = randint(0, 2)
                if games[chat_id]["board"][x][y] == 0:
                    return Move(x, y)
        
        x = ret[0]
        y = ret[1]
        return Move(x, y)

        """
        if games[chat_id]["board"][0][0] != 0 and games[chat_id]["board"][0][0] != games[chat_id]["bot"] and games[chat_id]["board"][0][1] != 0 and games[chat_id]["board"][0][1] != games[chat_id]["bot"]:
            return Move(0, 2)
        for row in range(2, -1, -1):
            for column in range(2, -1, -1):
                if games[chat_id]["board"][row][column] == 0:
                    return Move(row, column)
        """
        """
        Это самая главная функция бота.
        Она принимает на вход текущее поле (переменная games[chat_id]["board"]) и должна вернуть ход.

        Вот пример тела этой функции для бота, который всегда ходит в клетку с координатами (0, 0),
        даже если она уже занята:

        def move(self, games[chat_id]["board"]):
            return Move(0, 0)

        Как вы заметили, нужно всегда вернуть конструкцию Move(ROW, COLUMN), где (ROW, COLUMN) — координаты клетки,
        куда ваш бот хочет сходить.

        Чтобы узнать, чем занята та или иная ячейка поля, обратитесь к переменной games[chat_id]["board"].
        Например, в games[chat_id]["board"][1][1] лежит информация о центральной ячейке поля, потому что её координаты — (1, 1).
        Если в games[chat_id]["board"][1][1] лежит значение 0, то она пустая. Если 1, то там находится крестик,
        а если 2, то нолик.

        Вот пример функции move, которая ищет первую свободную ячейку и ходит в неё:

        def move(self, games[chat_id]["board"]):
            for row in range(games[chat_id]["board"].size):
                for column in range(games[chat_id]["board"].size):
                     if games[chat_id]["board"][row][column] == 0:
                          return Move(row, column)

        Внимательные заметили, что в этом примере мы использовали размер поля games[chat_id]["board"].size. Он всегда равен 3.

        Чтобы узнать, стоит ли в клетки ваш значок или значок противника, можно просто сравнить games[chat_id]["board"][row][column] и
        games[chat_id]["bot"] (о нём см. выше) на равенство. Чтобы узнать, «принадлежит» ли вам клетка,
        используйте следующую конструкцию:

        if games[chat_id]["board"][row][column] == games[chat_id]["bot"]:
            print('Это моя клетка!')

        Функция move() ОБЯЗАТЕЛЬНО должна вернуть объект Move() с какими-нибудь параметрами.
        В противном случае ход не будет засчитан.

        Вы можете использовать и изменять games[chat_id]["board"] как угодно, это никак не отразится на состоянии поля в игре.
        Не изменяйте games[chat_id]["bot"], это ни на что не повлияет и только может запутать вашего же бота :-)

        Ограничение на время работы функции — 3 секунды.

        ==========================================================================================================

        Есть два способа создавать свои функции: вне класса вашего бота и внутри него.

        1. В первом случае определяйте функции вне класса как обычно в программах на питоне. Они могут использовать
        глобальные переменные из вашего файла и вообще работать как обычно. Если для работы этих функций нужны
        games[chat_id]["bot"] или games[chat_id]["board"] из бота, то передайте их явно при работе функции move(). Например:

        def find_best_move(games[chat_id]["board"], player_type):
           ... Здесь код, который находит лучший ход, он может использовать переданные ему переменные
           ... games[chat_id]["board"] и player_type
           return Move(ROW, COLUMN)

        class MyBot(Bot):
            def move(games[chat_id]["board"]):
                return find_best_move(games[chat_id]["board"], games[chat_id]["bot"])

        2. Во втором случае создавайте функции прямо внутри класса бота. В этом случае ВСЕГДА добавляйте в качестве
        первого аргумента self, а для вызова используйте конструкцию self.<название_функции>(). Такие функции
        могут напрямую использовать games[chat_id]["bot"], так как находятся внутри бота, передавать эту переменную
        ещё раз не надо. Например:

        class MyBot(Bot):
            def find_best_move(self, games[chat_id]["board"]):
                ... Здесь код, который находит лучший ход, он может использовать переданные ему переменные
                ... games[chat_id]["board"] и games[chat_id]["bot"]
                return Move(ROW, COLUMN)

            def move(self, games[chat_id]["board"]):
                # Обратите внимание на self перед названием функции и на отсутствие self в качестве первого аргумента
                # (он передаётся автоматически)
                return self.find_best_move(games[chat_id]["board"])

        ============================================================================================================
        """


"""
Код ниже запускает игру между вашим ботом и человеком.
Его легко можно модифицировать, чтобы запустить игру между двумя людьми или двумя ботами.
"""
if __name__ == '__main__':
    # Следующая строка настраивает вывод информации об игре на стандартный поток вывода
    logging.basicConfig(level=logging.INFO, stream=sys.stdout, format='%(asctime)s [%(levelname)s] %(message)s')

    game = Game(MyBot, ConsolePlayer)

    # Если вы хотите сыграть за крестики вместо ноликов, поменяйте аргументы местами:
    # game = Game(ConsolePlayer, MyBot)

    # Если вы хотите запустить игру между двумя людьми, укажите два ConsolePlayer:
    # game = Game(ConsolePlayer, ConsolePlayer)

    # Если вы хотите запустить игру между двумя ботами, разместите их код в этом файле (не забудьте назвать классы
    # по-разному!), и укажите в следующей строке названия классов (обратите внимания, что названия классов надо
    # писать без скобок после них).
    # game = Game(MyBot1, MyBot2)

    game.play()

