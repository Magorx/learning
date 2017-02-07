#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import telebot
from telebot import types
import requests
from time import sleep
from random import randint, choice
import telebot

#== CONFIG ===================================================================
URL = 'https://api.telegram.org/bot326973551:AAFg3-fUQP40CLXjAEG_dZ6yHkRZoGqz1uI/'
TOKEN = '326973551:AAFg3-fUQP40CLXjAEG_dZ6yHkRZoGqz1uI'
ADMINS = [150486866]

#== PADEJI ===================================================================
BLUE_CASTLE = ['Синий', 'Синего', 'Синему', \
               ['Синий', 'Синего'], 'Синим', 'Синем']

RED_CASTLE = ['Красный', 'Красного', 'Красному', \
              ['Красный', 'Красного'], 'Красным', 'Красном']

GREEN_CASTLE = ['Зеленый', 'Зеленого', 'Зеленому', \
                ['Зеленый', 'Зеленого'], 'Зеленым', 'Зеленом']

YELLOW_CASTLE = ['Желтый', 'Желтого', 'Желтому', \
                 ['Желтый', 'Желтого'], 'Желтым', 'Желтом']

BLACK_CASTLE = ['Черный', 'Черного', 'Черному', \
                ['Черный', 'Черного'], 'Черным', 'Черном']

WHITE_CASTLE = ['Белый', 'Белого', 'Белому', \
                ['Белый', 'Белого'], 'Белым', 'Белом']
#== CLASSES ==================================================================
class Knight(object):
    def __init__(self, user_id):
        self.id = user_id
        self.castle = choice([BLUE_CASTLE, RED_CASTLE, GREEN_CASTLE, \
                               YELLOW_CASTLE, BLACK_CASTLE, WHITE_CASTLE])
        self.name = choice(['Григорий', 'Ольга', 'Александр', 'Максим'])
        self.attack = 1
        self.defence = 1
        self.money = 10
        self.lvl = 1
        self.exp = 0
        self.nexp = 15
        self.statment = 'Отдых'

    def send_to_player(self):
        message = self.name + ', рыцарь ' + self.get_list_castle()[1] + ' замка!\n'
        message = message + 'Атака: ' + str(self.attack) + '\n'
        message = message + 'Защита: ' + str(self.defence) + '\n'
        message = message + 'Опыт: ' + str(self.exp) + '/' + str(self.nexp) + \
                                                                           '\n'
        message = message + 'Монеты: ' + str(self.money) + '\n'
        message = message + 'Состояние: ' + self.statment
        bot.send_message(self.id, message)

    def get_str_castle(self):
        if self.castle is BLUE_CASTLE:
            return "castle_blue"
        if self.castle is RED_CASTLE:
            return "castle_red"
        if self.castle is GREEN_CASTLE:
            return "castle_green"
        if self.castle is YELLOW_CASTLE:
            return "castle_yellow"
        if self.castle is BLACK_CASTLE:
            return "castle_black"
        if self.castle is WHITE_CASTLE:
            return "castle_white"
        return 'Ошибка, напишите админам, пожалуйста, и идите гулять)'

    def get_list_castle(self, castle=''):
        if castle:
            if castle == "castle_blue":
                return BLUE_CASTLE
            if castle == "castle_red":
                return RED_CASTLE
            if castle == "castle_green":
                return GREEN_CASTLE
            if castle == "castle_yellow":
                return YELLOW_CASTLE
            if castle == "castle_black":
                return BLACK_CASTLE
            if castle == "castle_white":
                return WHITE_CASTLE
        else:
            return self.castle

    def __repr__(self):
        return ' '.join(map(str, [self.id, self.get_str_castle(), self.name,\
                                 self.attack, self.defence, self.money, \
                                 self.lvl, self.exp, self.nexp,self.statment]))

#== KEYBOARDS ================================================================
main_menu_markup = types.ReplyKeyboardMarkup()
main_menu_markup.row('Атака', 'Защита', 'Замок')
main_menu_markup.row('Герой', 'Квесты')
main_menu_markup.resize_keyboard = True

castle_menu_markup = types.ReplyKeyboardMarkup()
castle_menu_markup.row('Лавка', 'Таверна')
castle_menu_markup.row('Кузница', 'Назад')
main_menu_markup.resize_keyboard = True

#== GAME ACTIONS =============================================================
def LOAD():
    global users
    global log
    data_file = open('CW.data', 'r')
    data_file.readline()
    data_file.readline()
    print("== LOADING STARTED ==", file=log)
    for data in data_file.read().split('\n'):
        if not data:
            break
        data = list(data.split('|'))
        for i in range(len(data)):
            try:
                data[i] = int(data[i])
            except:
                pass
        users[data[0]] = Knight(data[0])
        knight = users[data[0]]
        knight.castle = knight.get_list_castle(castle=data[1])
        knight.name = data[2]
        knight.attack = data[3]
        knight.defence = data[4]
        knight.money = data[5]
        knight.lvl = data[6]
        knight.exp = data[7]
        knight.nexp = data[8]
        knight.statment = data[9]
        print(users[data[0]], ' [loaded]]', file=log)
    data_file.close()
    print('== LOADING COMPLETE ==', file=log)

def SAVE():
    data_file = open('CW.data', 'w')
    print("== SAVING ==", file=log)
    print("IP|CASTLE|NAME|ATK|DEF|MONEY|LVL|EXP|NEXP", file=data_file)
    print(file=data_file)
    for user in list(users.keys()):
        usr = users[user]
        data_to_save = usr.__repr__()
        data_to_save = data_to_save.replace(' ', '|')
        print(data_to_save, file=data_file)
        print(usr, 'SAVED', file=log)
    data_file.close()
    log.close()
#== MAIN =====================================================================

def main():
    global log
    global users
    global bot
    log = open('CW.log', 'w')
    users = {}
    bot = telebot.TeleBot(TOKEN)
    LOAD()

    #== HANDLERS =============================================================
    @bot.message_handler(commands=['stop'])
    def handle_stop(message):
        if message.chat.id not in ADMINS:
            bot.send_message(message.chat.id, 'У тебя нет на это прав')
            return 0
        bot.send_message(message.chat.id, 'Меня остановил один из админов)\n\
все данные сохранены')
        SAVE()
        exit(0)

    @bot.message_handler(commands=['start'])
    def handle_start(message):
        user_id = message.chat.id
        if user_id not in users.keys():
            print(user_id, 'started new game', file=log)
            users[user_id] = Knight(user_id)
            bot.send_message(user_id, 'Теперь ты рыцарь ' + \
                             users[user_id].name + '! Твой замок: ' + \
                             users[user_id].castle[0])
        else:
            knight = users[user_id]
            bot.send_message(user_id, 'Ты уже рыцарь!')
            knight.send_to_player()
            print(user_id, 'conected', file=log)

    @bot.message_handler(commands=['help'])
    def handle_help(message):
        bot.send_message(message.chat.id, 'Эта игра создана от нечего делать,\
на коленке. Является плагиатом chatwars, делаю ее просто так.')


    @bot.message_handler()
    def menus_handler(message):
        knight = users[message.chat.id]
        text = message.text
        if text == 'Назад':
            bot.send_message(knight.id,
                             'Куда держишь путь, ' + knight.name + '?',
                             reply_markup=main_menu_markup)
        if text == 'Замок':
            bot.send_message(message.chat.id,
                             knight.get_list_castle()[0] + \
                             ' замок процветает!',
                             reply_markup=castle_menu_markup)
        if text == 'Герой':
            knight.send_to_player()
    #=========================================================================
    bot.polling()
    bot.polling(interval=3)


if __name__ == '__main__':
    main()
