#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from kirzhanovsky import Game, Bot, ConsolePlayer

import logging
import sys
from random import randint
from math import floor, ceil
import time


def count_before_max(arr):
    if not arr:
        return None
    mx = max(arr)
    mx2 = float("-inf")
    count = 0
    for i in range(len(arr)):
        if arr[i] < mx and arr[i] > mx2:
            mx2 = arr[i]
            count = 1
        elif arr[i] == mx2:
            count += 1
    if mx2 < -1 or count == 0:
        return 0
    return count

def count_max(arr):
    if not arr:
        return None
    mx = max(arr)
    count = 0
    for i in arr:
        if i == mx:
            count += 1
    return count

def find(arr, num):
    for i in range(len(arr)):
        if arr[i] == num:
            return i
    return None

class MyBot(Bot):
    """
    Этот класс — в целом всё, что необходимо, чтобы создать своего бота.
    Во всех функциях этого класса доступна переменная self.players_count, которая равна
    количеству участников в турнире.
    """

    # Укажите здесь имя вашего бота
    NAME = 'Polar_bear_v_0.2'

    # Укажите здесь ваше имя
    AUTHOR = 'Max_Gorishniy'
    ignore = set()
    my_num = 0
    last  = -1
    def analyze_history(self, history):
        p_c = self.players_count
        arr = [[0 for j in range(p_c)]for i in range(p_c)]
        for i in range(len(history)):
            for j in range(p_c):
                arr[j][history[i][j] - 1] += 1
        for i in range(len(arr)):
            mx_count = count_max(arr[i])
            mx2_count = count_before_max(arr[i])
            if mx_count > mx2_count + randint(7, 13): #это просто вроде подходящие числа
                self.ignore.add(max(arr[i]))


    came = False
    at = 0
    def move(self, history):
        if self.came and self.at < 5:
            max(randint(floor(p_c / 3), ceil(p_c / 2)), 2)
        self.came = True
        self.at += 1
        start_time = time.time()
        p_c = self.players_count
        if len(history) > 5:
            self.analyze_history(history)
            while time.time() - start_time < 2.5:
                ans = max(randint(floor(p_c / 3), ceil(p_c / 2)), 2)
                if not ans in self.ignore:
                    self.came = False
                    return ans
        self.came = False
        return max(randint(floor(p_c / 3), ceil(p_c / 2)), 2)

        """
        Это самая главная функция бота.
        Она принимает историю ходов игроков в предыдущих раундах (переменная history).

        Вот пример тела этой функции для бота, который всегда ходит возвращает число 1:

        def move(self, board):
            return 1

        Всегда нужно возвращать целое число от 1 до self.players_number.

        Переменная history — это двумерный массив. Количество строк в нём равно количество уже сыгранных раундов.
        Каждая строка содержит ровно self.players_number ячеек — ходы игроков в соответствующем раунде.
        Например, если три человека сыграли уже два раунда, то переменная history может выглядеть следующим образом:

        history = [[2, 3, 3], [1, 1, 2]]

        Функция move() ОБЯЗАТЕЛЬНО должна вернуть целое число.

        Вы можете использовать и изменять history как угодно, это никак не отразится на истории игры.
        Не изменяйте self.players_count, это ни на что не повлияет и только может запутать вашего же бота :-)

        Ограничение на время работы функции — 3 секунды.

        ==========================================================================================================

        Есть два способа создавать свои функции: вне класса вашего бота и внутри него.

        1. В первом случае определяйте функции вне класса как обычно в программах на питоне. Они могут использовать
        глобальные переменные из вашего файла и вообще работать как обычно. Если для работы этих функций нужны
        self.player_type или board из бота, то передайте их явно при работе функции move(). Например:

        def find_best_move(board, player_type):
           ... Здесь код, который находит лучший ход, он может использовать переданные ему переменные
           ... board и player_type
           return Move(ROW, COLUMN)

        class MyBot(Bot):
            def move(board):
                return find_best_move(board, self.player_type)

        2. Во втором случае создавайте функции прямо внутри класса бота. В этом случае ВСЕГДА добавляйте в качестве
        первого аргумента self, а для вызова используйте конструкцию self.<название_функции>(). Такие функции
        могут напрямую использовать self.player_type, так как находятся внутри бота, передавать эту переменную
        ещё раз не надо. Например:

        class MyBot(Bot):
            def find_best_move(self, board):
                ... Здесь код, который находит лучший ход, он может использовать переданные ему переменные
                ... board и self.player_type
                return Move(ROW, COLUMN)

            def move(self, board):
                # Обратите внимание на self перед названием функции и на отсутствие self в качестве первого аргумента
                # (он передаётся автоматически)
                return self.find_best_move(board)

        ============================================================================================================
        """


"""
Код ниже запускает игру между вашим ботом и человеком.
Его легко можно модифицировать, чтобы запустить игру между двумя людьми или двумя ботами.
"""
if __name__ == '__main__':
    # Следующая строка настраивает вывод информации об игре на стандартный поток вывода
    logging.basicConfig(level=logging.INFO, stream=sys.stdout, format='%(asctime)s [%(levelname)s] %(message)s')

    game = Game([ConsolePlayer, MyBot, MyBot, MyBot, MyBot, MyBot, MyBot])

    # Если вы хотите запустить игру между двумя людьми, закомментириуйте предыдущую строчку
    # и раскомментируйте следующую:
    # game = Game([ConsolePlayer, ConsolePlayer])

    # Если вы хотите запустить игру между двумя ботами, разместите их код в этом файле (не забудьте назвать классы
    # по-разному!), и укажите в следующей строке названия классов (обратите внимания, что названия классов надо
    # писать без скобок после них).
    # game = Game([MyBot1, MyBot2])

    game.play()

