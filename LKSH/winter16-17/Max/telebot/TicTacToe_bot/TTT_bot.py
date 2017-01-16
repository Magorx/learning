import requests
from bs4 import BeautifulSoup
from time import sleep
from random import randint

def get_text(update):
    try:
        return update["message"]["text"]
    except:
        try:
            return update["edited_message"]["text"]
        except:
            return 0



def get_mes_id(update):
    return update["update_id"]


def get_chat_id(update):
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


def send_mess(id, text):
    requests.get(url_start + "sendMessage?chat_id=" + str(chat_id) + "&text=" + str(text))



win_lines = [[(0, 0), (0, 1), (0, 2)],    \
             [(1, 0), (1, 1), (1, 2)],    \
             [(2, 0), (2, 1), (2, 2)],    \
             [(0, 0), (1, 0), (2, 0)],    \
             [(0, 1), (1, 1), (2, 1)],    \
             [(0, 2), (1, 2), (2, 2)],    \
             [(0, 0), (1, 1), (2, 2)],    \
             [(0, 2), (1, 1), (2, 0)],]

def check_win(board):
    for i in win_lines:
        if board[i[0][0]][i[0][1]] == board[i[1][0]][i[1][1]] == board[i[2][0]][i[2][1]] and board[i[1][0]][i[1][1]] != 0:
            return True
    cnt = 9
    for i in range(3):
        for j in range(3):
            if board[i][j] != 0:
                cnt -= 1
    if cnt == 0:
        return False
    return False


def move(chat_id, x, y, symb):
    if x < 0 or x > 3 or y < 0 or y > 3:
        return "invalid coords, you must give natural x and y and they must be lesser than 3"
    if games[chat_id]["board"][x][y] != 0:
        return "invalid place - it's fool"
    games[chat_id]["board"][x][y] = symb
    if check_win(games[chat_id]["board"]):
        return "Game over"
    return "OK"


def board_print(board):
    string = "..0.1.2\n"
    cnt = 0
    for i in board:
        string = string + str(cnt) + " "
        cnt += 1
        for j in range(3):
            if i[j] == 0:
                string = string + "="
            if i[j] == games[chat_id]["player_symb"]:
                string = string + "" + games[chat_id]["player_symb"]
            if i[j] == games[chat_id]["bot_symb"]:
                string = string + "" + games[chat_id]["bot_symb"]
        string = string + "\n"
    print(string, end="")
    return string


def check_near_win_and_turn(board, symb):
    counter = 0
    if games[chat_id]["bot_symb"] == 1:
        other = 2
    else:
        other = 1
    for i in win_lines:
        for j in range(len(i)):
            if board[i[j][0]][i[j][1]] == symb:
                counter += 1
                if counter == 2:
                    if j == 1:
                        if board[i[2][0]][i[2][1]] == 0:
                            return (i[2][0], i[2][1])
                    elif j == 2:
                        if board[i[1][0]][i[1][1]] == symb and board[i[0][0]][i[0][1]] == 0:
                            return (i[0][0], i[0][1])
                        elif board[i[0][0]][i[0][1]] == symb and board[i[1][0]][i[1][1]] == 0:
                            return (i[1][0], i[1][1])
                if counter == 3:
                    return (-1, -1)
        counter = 0
    return (3, 3)

turn = 0
first_launch = 0


def send_board(board):
    send_mess(chat_id, board)
    return 0


def choose_move(board):
    good1 = [(1, 1), (0, 0), (0, 2), (2, 0), (2, 2), (0, 1), (1, 0), (1, 2), (2, 1)]
    good2 = [(1, 1), (0, 0), (0, 2), (2, 0), (2, 2), (0, 1), (1, 0), (1, 2), (2, 1)]

    global first_launch

    if first_launch == 0:
        if games[chat_id]["bot_symb"] == 1:
            first_launch = 1
            return (1, 1)
        else:
            first_launch = 1
            return (0, 0)
        
    ret1 = check_near_win_and_turn(board, games[chat_id]["bot_symb"])
    ret2 = check_near_win_and_turn(board, games[chat_id]["player_symb"])

    if ret1 == (3, 3):
        ret = ret2
    else:
        ret = ret1
    if ret == (-1, -1):
        print("WAAAAAAAAAAAAAAAAAAAAAT")
        for i in range(len(good1)):
            if board[good1[i][0]][good[i][1]] == 0:
                return good1[i][0], good1[i][1]
    print(ret)
    if ret == (3, 3) or board[ret[0]][ret[1]] != 0:
        for i in range(len(good1)):
            if board[good1[i][0]][good1[i][1]] == 0:
                return good1[i][0], good1[i][1]
    
    x = ret[0]
    y = ret[1]
    return (x, y)


url_start  = "https://api.telegram.org/bot321237483:AAFkFA6Gx1d_Djy6LzmKhVhP3SjRqZm19L8/"

log = open("bot.log", "r")
answered = set()
string = log.readline()
while string:
    if "ans" in string:
        answered.add(int(string.split()[1]))
    string = log.readline()
log.close()


itters = 1
STOP = False
games = dict()
while True and itters < 100:
    #print(STOP, itters)
    if STOP:
        break
    updates = requests.get(url_start + "getUpdates").json()
    #print(updates)
    for upd in updates['result']:
        text = get_text(upd)
        chat_id = get_chat_id(upd)       
        #server_call = requests.get(url_start + "/getUpdates?offset={" + str(get_mes_id(upd)) + "}")
        if get_mes_id(upd) in answered:
            continue
        answered.add(get_mes_id(upd))
        if text == "/start":
            games[chat_id] = dict()
            games[chat_id]["board"] = [[0 for i in range(3)] for j in range(3)]
            games[chat_id]["bot_symb"] = "O"
            games[chat_id]["player_symb"] = "X"

            send_mess(chat_id, "OK, let's start new game!")
            send_board(board_print(games[chat_id]["board"]))
            continue
        if text == "/stop_HOPHEY":
            send_mess(chat_id, "I'm stoped by my owner)")
            STOP = True
            break
        if text == "/stop":
            send_mess(chat_id, "OK, game killed, you have to /start it again")
            games[chat_id] = ""
            continue
        arr = 0
        try:
            arr = list(map(int, text.split()))
            r = move(chat_id, arr[0], arr[1], games[chat_id]["player_symb"])
            if check_win(games[chat_id]["board"]):
                send_mess(chat_id, "Game Over! Who won?")
            if "invalid" in r:
                send_mess(chat_id, "OH! Invalid turn, please, give me two numbers from 0 to 2 (board must be empty there). try again!")
                send_mess(chat_id, "your board: ")
                send_board(board_print(games[chat_id]["board"]))
                continue
            x, y = choose_move(games[chat_id]["board"])
            move(chat_id, x, y, games[chat_id]["bot_symb"])
            print(*get_from(upd))
            print() 
            send_board(board_print(games[chat_id]["board"]))
            if check_win(games[chat_id]["board"]):
                send_mess(chat_id, "Game Over! Who won?")
                #STOP = True
        except:
            send_mess(chat_id, "OH! Invalid turn, please, give me two numbers from 0 to 2 (board must be empty there). try again!")
            send_mess(chat_id, "your board: ")
            send_board(board_print(games[chat_id]["board"]))
            continue

    itters += 1
    sleep(1)


log = open("bot.log", "w")

for i in answered:
    print("ans " + str(i), sep="", file=log)
log.close()