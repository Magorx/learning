#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import telebot
from telebot import types
import time

TOKEN = '326973551:AAFg3-fUQP40CLXjAEG_dZ6yHkRZoGqz1uI'


def listener(messages):
    """
    When new messages arrive TeleBot will call this function.
    """
    for m in messages:
        chatid = m.chat.id
        if m.content_type == 'text':
            text = m.text
            bot.send_message(chatid, text)


bot = telebot.TeleBot(TOKEN)
@bot.message_handler(commands=['start', 'help'])
def handle_start_help(message):
    print("hi")
    markup = types.ReplyKeyboardMarkup()
    markup.row('a', 'b')
    markup.row('c', 'd', 'e')
    markup.one_time_keyboard = True
    bot.send_message(message.chat.id, "LETTER ATTACK:", reply_markup=markup)
#bot.set_update_listener(listener) #register listener
bot.polling()
#Use none_stop flag let polling will not stop when get new message occur error.
bot.polling(none_stop=True)
# Interval setup. Sleep 3 secs between request new message.
bot.polling(interval=3)

it = 100
while it: # Don't let the main Thread end.
    it -= 1