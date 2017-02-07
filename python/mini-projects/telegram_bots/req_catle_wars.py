#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import telebot
from telebot import types
import requests
from time import sleep
from random import randint
import telebot

#== CONFIG ===================================================================
URL = "https://api.telegram.org/bot326973551:AAFg3-fUQP40CLXjAEG_dZ6yHkRZoGqz1uI/"
TOKEN = '326973551:AAFg3-fUQP40CLXjAEG_dZ6yHkRZoGqz1uI'
ans = "HI"

#== CLASSES ==================================================================
class My_bot(object):
    def __init__(self, token):
        self.token = token
        self.URL = "https://api.telegram.org/bot"
        self.updates = []

    def send_message(self, id, text):
        requests.get(self.URL + self.token + "sendMessage?user_id=" +\
                     str(user_id) + "&text=" + str(text))

    def get_updates(self):
        updates = list(requests.get(self.URL + self.token + "getUpdates"))

class Knight(object):
    def __init__(self, user_id):
        self.id = user_id
        self.last_message = 0
        self.name = "Jonson Vival"
        self.attack = 1
        self.defence = 1
        self.money = 10
#== FUNCTIONS ================================================================
def get_text(update):
    try:
        return update["message"]["text"]
    except:
        try:
            return update["edited_message"]["text"]
        except:
            return 0



def get_message_id(update):
    return update["update_id"]


def get_user_id(update):
    try:
        return update["message"]["chat"]["id"]
    except:
        try:
           return update["edited_message"]["chat"]["id"]
        except:
            return 0


def get_from(update):
    return update["message"]["from"]["first_name"],\
           update["message"]["from"]["last_name"]


def send_message(user_id, text):
    requests.get(URL + "sendMessage?user_id=" + str(user_id) + "&text=" + str(text))

#== MENU =====================================================================
main_menu = ["Attack", "Defence", "Castle", "Quests"]
castle_menu = ["Shop", "tower_dev", "arena_dev"]

def show_menu(user_id, menu):
    sending_menu = ""
    for button in menu:
        sending_menu = sending_menu + "/" + button + " \n"
    print(sending_menu)
    send_message(user_id, sending_menu)


def commands_handler(upd):
    global users
    text = get_text(upd)
    user_id = get_user_id(upd)
    if text[0] == "/":
        if text[1:] == "attack":
            #send_message(user_id, "your atk is " + str(5))
            send_message(user_id, "your atk is " + str(users[user_id].attack))
            users[user_id].attack += 1

#== KEYBOARDS ================================================================
main_menu_keyboard = [[{"text":"Attack"}]]

def send_keyboard(user_id, keyboard):
    replyKeyboardMakeup = {'keyboard': [["YES", "NO"], ["KOKOKO"]],
                           'resize_keyboard': False,
                           'one_time_keyboard': False}
    reply_markup={"keyboard":[["Yes","No"],["Maybe"],["1","2","3"]],"one_time_keyboard":True}
    data = {'user_id': user_id,
            'text': "",
            'reply_markup': reply_markup}
    return requests.get(URL + "sendMessage", data=data)
#== MAIN =====================================================================

def main():
    log = open("CW.log", "r")
    global users
    users = {}
    for data in log.read().split("\n"):
        if not data:
            break
        data = list(map(int, data.split()))
        users[data[0]] = Knight(data[0])
        users[data[0]].last_message = data[1]
        users[data[0]].attack = data[2]
        users[data[0]].defence = data[3]
        users[data[0]].money = data[4]
    t = 1
    print(users)
    while t > 0:
        t -= 1
        updates = requests.get(URL + "getUpdates").json()
        updates = updates["result"]
        for upd in updates:
            user_id = get_user_id(upd)
            if user_id not in users:
                users[user_id] = Knight(user_id)
                show_menu(user_id, main_menu)
            message_id = get_message_id(upd)
            if users[user_id].last_message < message_id:
                users[user_id].last_message = message_id
                #commands_handler(upd)
                print(send_keyboard(user_id, main_menu_keyboard))
            
        sleep(1)
    log.close()
    log = open("CW.log", "w")
    for user in users.keys():
        usr = users[user]
        print(user, usr.last_message - 1, usr.attack, usr.defence, usr.money,\
              file=log)
    log.close()





if __name__ == "__main__":
    main()
