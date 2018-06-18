#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice
from time import sleep
import telebot
import parser


TELEBOT_TOKEN = '387551779:AAFgjp-9MRrW2Dqy_v6PlaH61CT-uDDnZoo'
TeleBot = telebot.TeleBot(TELEBOT_TOKEN)
ADMIN_ID = [150486866]

TO_STOP = False

parser.parse('defs.txt')
DICT = parser.DICT

#===== TELEGRAMM INTERFACE ===================================================
class User(object):
    def __init__(self, telegramm_id, name):
        self.id = telegramm_id
        self.name = name
        self.last_definition = 1


def user_by_id(user_id):
    if user_id in USERS:
        return USERS[user_id]
    else:
        return None


def warn_invalid_args(chat_id):
    TeleBot.send_message(chat_id, 'Некоректные аргументы. ' + 
                                  '/commands_help для помощи.')


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
        TeleBot.send_message(chat.id, 'Привет. Напиши /random чтобы получить случайный допуск')
        TeleBot.send_message(chat.id, 'Если с допуском беда (любая) - напиши /fix *номер допуска*')
        USERS[chat.id] = User(chat.id, chat.first_name)

    if text.startswith('/random'):
        defenition = DICT.get_random()
        user.last_definition = defenition.id
        print('> ' + str(defenition.id) + defenition.name)
        TeleBot.send_message(chat.id, str(defenition.id) + '. ' + defenition.name + '.')
        TeleBot.send_message(chat.id, 'Узнать ответ: /reveal')

    if text.startswith('/reveal'):
        TeleBot.send_message(chat.id, DICT.dict[user.last_definition])
        TeleBot.send_message(chat.id, 'Новое определение: /random')

    if text.startswith('/fix'):
        print('FIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIX')
        print(text)
        print('FIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIXFIX')



def main():
    global WORLDS
    global USERS
    WORLDS = {}
    USERS = {}
    TeleBot.polling(interval=3)


if __name__ == "__main__":
    main()
