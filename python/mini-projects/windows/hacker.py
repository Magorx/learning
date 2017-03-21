from random import randint, choice
from time import sleep
from string import printable

#=FUN===========================================================================
DRIVERS = ["MX", "Windows_system", "coal.ntx", "Tags", "Expoiler",\
           "DP_Graphics_A_wnt5_x86-32_912", "GGWP", "Linux", "MacOS", "Banana",\
           "OG_V", "Mg_STT", "CX_01x_0", "CX_01x_1"]

PROGRAMS = ["File_explorer", "Google", "Amigo", "Waterfox", "Calc", "Sublime"\
            "Visual_Studio", "Paint", "Painball", "Python", "Clipday",\
            "BitTorren", "VS", "Bloom"]

STRANGE = ["NX_CMDM", "cmd", "RooTs", "CO.log"]

FILES = ["log.txt", "bot.brains", "up.down", "py.py", "lichnoe.pdf",\
         "Diploma.paint", "STD.io", "Boot.b", "ReBoot.b"]

RASSH = ["exe", "txt", "pdf", "xl", "paint", "com", "c", "py", "cpp"]

ERRORS = ["RUN_TIME", "MEMORY", "CLIENT", "DATA", "PC", "BUSH", "SELF", "COLOR"]

SETTINGS = ["Graphic", "Music", "System", "Monitor", "Headphones", "Keyboard"]

#=CODE==========================================================================

class table():
    def __init__(self, x, y, data, b1 = ["", ""], b2 = "[]"):
        if len(b1) != 2 or len(b2) != 2:
            b1 = ["", ""]
            b2 = "[]"
        self.data = [[0 for i in range(y)] for j in range(x)]
        self.obj_board = b1
        self.switch_board = b2
        x = 0
        y = 0
        for i in range(len(data)):
            try:
                c = choice(["+", "-"])
                self.data[x][y] = [str(data[i]), c]
            except:
                return "ERR_DATA"
            y += 1
            if y == len(self.data[0]):
                y = 0
                x += 1
                if x == len(self.data):
                    break
    def print(self):
        data = self.data
        b1 = self.obj_board
        b2 = self.switch_board
        l_max = [max([len(j[0]) for j in list(zip(*data))[i]])\
                 for i in range(len(data[0]))]
        for i in range(len(data)):
            for j in range(len(data[0])):
                if not data[i][j][0]:
                    continue
                spaces = l_max[j] - len(data[i][j][0])
                print(b1[0] + data[i][j][0] + b1[1] + b2[0] +\
                      data[i][j][1] + b2[1] + " " * spaces, end=" ")
            print()


def pprint(arr):
    for i in arr:
        print(*i)


def randstr(length, lvl = 3):
    str = ""
    for i in range(length):
        roll = randint(1, lvl)
        if roll == 1:
            c = chr(randint(48, 57))
        elif roll == 2:
            c = chr(randint(65, 90))
        elif roll == 3:
            c = chr(randint(97, 122))
        elif roll == 4:
            c = choice(SYMBS)
        str = str + c
    return str


def load(l = 10, symb = "=", boarder = "[]", t_min = 1, t_max = 5, end = "\n"):
    try:
        if len(symb) != 1 or len(boarder) != 2:
            return "ERR_ARGS"
    except EXCEPTION:
        return "ERR_ARGS"
    print(boarder[0], end="")
    for i in range(l):
        print(symb, end="")
        sleep(randint(t_min, t_max) / 10)
    print(boarder[1], end=end)
    return 0

def load_drivers(cnt):
    used = []
    print("===\nDriver load\n===")
    chosen = ""
    for i in range(cnt):
        itt = 0
        chosen = choice(DRIVERS)
        while chosen in used and itt < 100:
            itt += 1
            chosen = choice(DRIVERS)
        used.append(chosen)
        print(chosen, end=" ")
        load(3, ".", ["", ""], 3, 9, "")
        if randint(0, 10):
            print("OK")
        else:
            print("FAILED")
    print("Driver load completed\n===")
    return 0


def open_files(cnt):
    print("opening files\n===")
    for i in range(cnt):
        if randint(0, 3):
            print(randstr(randint(1, 7)) + "." + choice(RASSH), end=" ")
            if randint(0, 6):
                print("+")
            else:
                print("-", choice(ERRORS), "ERROR")
        else:
            print(choice(FILES), "+")
    print("===\nOpened\n===")
    return 0


def load_system():
    t = table(2, 3, SETTINGS)
    print("!!!SYSTEM_LOAD!!!")
    print("===SETTINGS===")
    t.print()
    print("===DRIVERS===")
    load_drivers(3)
    print("===FILES===")
    open_files(5)
    pas = input("password: ")
    if pas != "9999":
        print("LOGIN_ERR")
        return 0
    else:
        print("Hello!")
    load(10)
    return 0
    

SYMBS = printable[:len(printable) - 4]

load_system()
for i in range(20):
    num = randint(1, 2)
    if num == 1:
        load_drivers(randint(2, 4))
    if num == 2:
        open_files(randint(7, 10))
print("!!!SYSTEM_EXIT!!!")
