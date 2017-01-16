import requests
from bs4 import BeautifulSoup
from time import sleep


#==RPG=========================================================================
COLOR = False
if COLOR:
    import fixpath
    from colorama import init, Fore, Back, Style
from random import randint, choice

if COLOR:
    init(autoreset=True)

#===DELAYED=====================================================================
class item():
    weight = 0
    price = 0
    name = "DUMP"
    def generate(self, name, weight, price):
        self.name = name
        self.weight = weight
        self.price = price

class stats():
    st = 0
    dex = 0
    con = 0
    intel = 0
    wis = 0
    cha = 0

class creature():
    name = "NONE"
    hp = 0
    mp = 0
    exp = 0
    exp_to_level = 1
    lvl = 0
    inv = []
    stats = stats()

def start():
    player.stats.st = 13
    player.hp = randint()


#===EASY========================================================================
command_list = ["roll", "inv", "trashbeen", "exit"]
inv_commands = ["add", "del", "empty", "mod", "show"]


def handle_input(string, prints = 0):
    try:
        command = string.split()
        if not command:
            return 1
        if not command[0] in command_list:
            print("invalid command \{x-x}/")
        if command[0] == "exit":
            return "exit"
        if command[0] == "roll":
            try:
                return roll(command[1], prints = prints)
            except:
                print("invalid roll \{x-x}/")
        if command[0] == "inv":
            handle_inventory(command[1:])
        if command[0] == "trashbeen":
            for i in range(len(trashbeen)):
                print(trashbeen[i])
        if prints >= 1:
            print("=====")
        return "OK"
    except:
        print("ERROR [X0X], don't worry, inv was saved")
        return "err"

def CLS():
    if COLOR:
        print("\033[H\033[J", end="")

def roll(s, prints = 1):
    s = list(s)
    if prints >= 1:
        print("Rolling...")
    dices = int("".join((s[0 : s.index("d")])))
    edges = int("".join((s[s.index("d") + 1 : len(s)])))
    roll = randint(1, edges)
    ans = roll
    if prints:
        sleep(0.5)
        print(roll, end = " ")
    for i in range(dices - 1):
        roll = randint(1, edges)
        if prints:
            sleep(0.5)
            print("+", roll, end = " ")
        ans += roll
    if prints and dices > 1:
        print("=", ans)
    elif prints:
        print()
    return ans

def handle_inventory(com):
    if not com[0] in inv_commands:
        print("Invalid inventory command \{x-x}/")
        return 1
    if com[0] == "add":
        inv.append(" ".join(com[1:]))
        return 0
    if com[0] == "del":
        try:
            ind = ord(com[1]) - ord("a")
            trashbeen.append(inv[ind])
            del inv[ind]
        except:
            print("iFailed deleting from inventory \{x-x}/")
        return 0
    if com[0] == "empty":
        ans = input("Do you realy want to clear inv? ")
        if ans == "Yes" or ans == "YES" or ans == "yes":
            trashbeen.append(inv[:])
            inv.clear()
            return 0
    if com[0] == "mod":
        try:
            ind = ord(com[1]) - ord("a")
            inv[ind] = " ".join(com[2:])
        except:
            print("Failed modding inventory \{x-x}/")
        return 0
    if com[0] == "show":
        for i in range(len(inv)):
            print(chr(ord("a") + i)+ ")", inv[i])
        return 0
#==MAIN=========================================================================
def rpg_main():
    inv_file = open("inv_file.txt", "r")
    CLS()
    time = 0
    inv = []
    trashbeen = []
    s = inv_file.readline()
    while s:
        s = s[0:len(s) - 1]
        inv.append(s)
        s = inv_file.readline()

    while True and time < 999:
        time += 1
        out = handle_input(input())
        if out == "exit":
            break
        if out == "err":
            break

#===TELEBOT====================================================================


def get_text(update):
    return update["message"]["text"]


def get_mes_id(update):
    return update["update_id"]


def get_chat_id(update):
    return update["message"]["chat"]["id"]


def send_mess(id, text):
    requests.get(url_start + "sendMessage?chat_id=" + str(chat_id) + "&text=" + str(text))



log = open("bot.log", "r")
answered = set()
string = log.readline()
while string:
    if "ans" in string:
        answered.add(int(string.split()[1]))
    string = log.readline()
log.close()


url_start  = "https://api.telegram.org/bot231975880:AAFGXm9RYOH5BfrINbeXJen71e5lP811f6c/"

HELP = open("bot.help", "r", encoding='utf-8').read()

itters = 1
STOP = False
while True and itters < 100:
    if STOP:
        break
    updates = requests.get(url_start + "getUpdates").json()
    for upd in updates['result']:
        if get_mes_id(upd) in answered:
            continue
        text = get_text(upd)
        answered.add(get_mes_id(upd))
        chat_id = get_chat_id(upd)
        if text == "/stop":
            send_mess(chat_id, "OK, by")
            STOP = True
            break
        if "/rpg " in text:
            ans = handle_input(text[5:])
            chat_id = str(chat_id)
            ans = str(ans)
            send_mess(chat_id, ans)

            break
        send_mess(chat_id, HELP)


    itters += 1
    sleep(1)

log = open("bot.log", "w")

for i in answered:
    print("ans " + str(i), sep="", file=log)
log.close()

