from random import randint
import time

#====Fighter=============================================
class fighter:
    name = "unnamed_fighter"
    clas = "dummy"
    hp = -1
    atk = -1
    speed = -1
    luck = -1
    defense = -1
    atk_range = -1
    kills = 0
    symb = "."
    team = -1
    x = -1
    y = -1
    behaviour = "standing"
    def construct(self):
        self.luck = randint(1, 3)
        self.hp = randint(10, 20 + self.luck)
        self.atk = randint(2, 5 + (self.luck // 2))
        self.speed = randint(5 - self.luck, 7 - self.luck)
        self.defense = randint(5 + self.luck, 13)
        self.symb = "@"
        roll = randint(1, 3)
        if roll == 1:
            self.clas = "warior"
            self.atk_range = 1
            self.hp += randint(3, 7)
            self.atk += 1
        if roll == 2:
            self.clas = "ranger"
            self.atk_range = randint(2, 3)
        if roll == 3:
            self.clas = "healer"
            self.atk_range = randint(1, 2)
            self.atk += randint(-1, 0)
        if TEAM_MODE:
            self.team = randint(1, TEAM_COUNT)
    def attack(self, defender):
        if distance(self.x, self.y, defender.x, defender.y) > self.atk_range:
            self.pursuit(defender)
            return 1
        if defender.team > 0 and defender.team == self.team:
            if self.clas == "healer":
                roll = randint(self.atk - self.luck, self.atk + self.luck)
                defender.hp += roll
                print("{}[{}][{}] heal {}[{}][{}] for {}".format(self.name,
                   self.x, self.y, defender.name, defender.x, defender.y, roll))
                return 0
            else:
                print("{}[{}][{}] bumped into {}[{}][{}]".format(self.name,
                   self.x, self.y, defender.name, defender.x, defender.y))
                return 0
        roll = randint(1, 20) + self.luck;
        if roll > defender.defense:
            roll = randint(max(1, self.atk - self.luck), self.atk + self.luck)
            defender.hp -= roll
            print("{}[{}][{}] hit {}[{}][{}] for {}".format(self.name, self.x,
                           self.y, defender.name, defender.x, defender.y, roll))
        else:
            print(self.name, "missed")
        return 0
    
    def pursuit(self, purpuse):
        roll = randint(0, 1)
        if roll:
            if self.x < purpuse.x:
                self.down(battlefield)
            elif self.x > purpuse.x:
                self.up(battlefield)
            else:
                roll = 0
        if roll == 0:
            if self.y < purpuse.y:
                self.right(battlefield)
            elif self.y > purpuse.y:
                self.left(battlefield)
        print("{}({})[{}][{}] pursuate {}({})[{}][{}]".format(self.name, self.symb,
                    self.x, self.y, purpuse.name, purpuse.symb, purpuse.x, purpuse.y))

    def die(self, battlefield):
        battlefield[self.x][self.y].fighter = fighter()
        battlefield[self.x][self.y].full = 0
        del fighters_names[fighters_names.index(self.name)] 

    def up(self, battlefield):
        if self.x > 0:
            if battlefield[self.x - 1][self.y].full == 0:
                battlefield[self.x - 1][self.y].fighter = self
                battlefield[self.x][self.y].fighter = fighter()
                battlefield[self.x][self.y].full = 0
                battlefield[self.x - 1][self.y].full = 1
                self.x -= 1
            elif battlefield[self.x - 1][self.y].full == 1:
                self.attack(battlefield[self.x - 1][self.y].fighter)

    def down(self, battlefield):
        if self.x < MAP_SIZE:
            if battlefield[self.x + 1][self.y].full == 0:
                battlefield[self.x + 1][self.y].fighter = self
                battlefield[self.x][self.y].fighter = fighter()
                battlefield[self.x][self.y].full = 0
                battlefield[self.x + 1][self.y].full = 1
                self.x += 1
            elif battlefield[self.x + 1][self.y].full == 1:
                self.attack(battlefield[self.x + 1][self.y].fighter)
    def left(self, battlefield):
        if self.y > 0:
            if battlefield[self.x][self.y - 1].full == 0:
                battlefield[self.x][self.y - 1].fighter = self
                battlefield[self.x][self.y].fighter = fighter()
                battlefield[self.x][self.y].full = 0
                battlefield[self.x][self.y - 1].full = 1
                self.y -= 1
            elif battlefield[self.x][self.y].full == 1:
                self.attack(battlefield[self.x][self.y - 1].fighter)

    def right(self, battlefield):
        if self.y < MAP_SIZE:
            if battlefield[self.x][self.y + 1].full == 0:
                battlefield[self.x][self.y + 1].fighter = self
                battlefield[self.x][self.y].fighter = fighter()
                battlefield[self.x][self.y].full = 0
                battlefield[self.x][self.y + 1].full = 1
                self.y += 1
            elif battlefield[self.x][self.y].full == 1:
                self.attack(battlefield[self.x][self.y + 1].fighter)


def choose_behaviour(self):
    index = fighters.index(self)
    min_range = float("+inf")
    min_index = -1
    for i in range(index - 1, -1 * (len(fighters) - index), -1):
        if ((fighters[i].team < 0 or fighters[i].team != self.team)
                                                and self.clas != "healer"):
            if min_range > distance(self.x, self.y, fighters[i].x, fighters[i].y):
                min_range = distance(self.x, self.y, fighters[i].x, fighters[i].y)
                min_index = i
        elif (self.clas == "healer" and fighters[i].team == self.team and
              i != fighters[fighters.index(self)]) :
            if min_range > distance(self.x, self.y, fighters[i].x, fighters[i].y):
                min_range = distance(self.x, self.y, fighters[i].x, fighters[i].y)
                min_index = i
    if self.clas != "healer":
        self.behaviour = "pursuating " + str(min_index)
        return self.behaviour
    else:
        self.hp += randint(1, 2)
        self.behaviour = "pursuating " + str(min_index)
        return self.behaviour

def handle_behaviour(self):
    beh = list(self.behaviour.split())
    if len(beh) < 1:
        return -1
    if beh[0] == "standing":
        choose_behaviour(self)
    if len(beh) == 2:
        if beh[0] == "pursuating":
            self.attack(fighters[int(beh[1])])
            return 0

#====Teams======================================================================
class team:
    spawn_point = [-99, -99]
    score = -99
    fighters_count = -1
    max_fighters_count = -1
    money = - 99
    symb = ""
    def construct(self, fighters, battlefield, teams):
        x = randint(0, MAPSIZE - 1)
        y = randint(0, MAPSIZE - 1)
        for i in teams:
            if distance(x, y, i.spawnpoint[0], i.spawnpoint[1]) > 3:
                self.spawnpoint[0] = x
                self.spawnpoint[1] = y
        #for i in fighters:
            
#====Map========================================================================
class ground():
    full = 0
    fighter = fighter()

def mapshow(battlefield):
    for i in battlefield:
        for j in i:
            print(" ", j.fighter.symb, sep="", end="")
        print("\n")
    print("====================")

def handle_player(self, command):
    if command == "w":
        self.up(battlefield)
        return 0
    if command == "s":
        self.down(battlefield)
        return 0
    if command == "a":
        self.left(battlefield)
        return 0
    if command == "d":
        self.right(battlefield)
        return 0
    if command == "f":
        choose_behaviour(self)
        handle_behaviour(self)
        self.behaviour = "player"
        return 0
    choose_behaviour(self)
    handle_behaviour(self)
    self.behaviour = "player"
    return 0
#====General========================================
def command(command):
    if len(command) == 0:
        return ""
    command = list(command.split())
    if len(command) == 0:
        return ""
    command_list = ["print_stats", "stop"]
    if len(command) == 1 and command[0] in fighters_names:
        return stats(fighters[fighters_names.index(command[0])])
    if not command[0] in command_list:
        return "INVALID COMMAND"
    if len(command) == 1:
        if command[0] == "stop":
            return -999
    if len(command) == 2:
        if command[0] == "print_stats":
            for i in fighters:
                if i.name == command[1] or i.symb == command[1]:
                    return stats(i)
                    break
            else:
                return "INVALID NAME"

def name_generate(mini, maxi):
    length = randint(mini, maxi)
    glasn = ["a", "i", "o", "u", "e"]
    soglasn = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 
          'r', 's', 't', 'v', 'w', 'x', 'y', 'z']
    name = ""
    for i in range(length):
        if i % 3 == 0:
            roll = randint(0, len(glasn) - 1)
            name = name + glasn[roll]
        else: 
            roll = randint(0, len(soglasn) - 1)
            name = name + soglasn[roll]
    return name

def stats(self):
    return "[{}]({})[{}][{}]: {}, hp {}, str {}, spd{}, luck{}, def {}, \
range {} |\nteam {}, {}|".format(self.name, self.symb, self.x, self.y,
            self.clas, self.hp, self.atk, self.speed, self.luck, self.defense,
            self.atk_range, self.team, self.behaviour)


def sort_by_score(arr):
    return arr[1]

def distance(x1, y1, x2, y2):
    return max(x1 - x2, x2 -x1) + max(y1 - y2, y2 - y1)

def arr_elements_equal(arr):
    if len(arr) < 2:
        return True
    num = arr[0]
    for i in arr:
        if num != i:
            return False
    return True
#=====Game=======================================
def battle(prints):
    tick = 0
    note = ""
    while True:
        tick += 1
        for j in range(len(fighters)):
            if tick % fighters[j].speed == 0:
                if fighters[j].behaviour == "player":
                    print("What do you do, {}[{}][{}]?".format(
                        fighters[j].name, fighters[j].x, fighters[j].y))
                    handle_player(fighters[j], input())
                else:
                    choose_behaviour(fighters[j])
                    handle_behaviour(fighters[j])
                if prints > 1:
                    mapshow(battlefield)
                    note = command(input())
                    if note == -999:
                        return -999
                if prints and note:
                    print("===\n", note, "\n===")
                note = ""
                if fighters[j - 1].hp < 0:
                    fighters[j].kills += 1
                    if prints:
                        print("[{}] >>> [{}]".format(fighters[j].name,
                                                 fighters[j - 1].name))
                        
                    score.append((fighters[j - 1].name, fighters[j - 1].kills))
                    x = fighters[j - 1].x
                    y = fighters[j - 1].y
                    battlefield[x][y].fighter.die(battlefield)
                    del fighters[j - 1]
                    break
        if not TEAM_MODE and len(fighters) < 2:
            score.append((fighters[0].name, fighters[0].kills))
            break
        elif len(team_arr) < 2:
            print("team", fighters[0].team, "won!")
            break
    return tick


def score_print():
    print("tick", tick)
    print("{0:=^21}".format("THE END OF BATTLE"))
    print("{0:=^21}".format("SCOREBOARD"))
    print("{0:=^11}{1:=^10}".format("NAME", "SCORE"))
    score.sort(reverse = True, key = sort_by_score)
    for place in range(min(len(score), 10)):
        print("{0:~^10}={1:~^10}".format(score[place][0],
                                            score[place][1]))
#==MAIN==========================================

PLAY = 1
if PLAY:
    print("Will it be [0]deathmath or [1]team battle?")
    TEAM_MODE = int(input())
    if TEAM_MODE:
        print("How many teams will collide?")
        TEAM_COUNT = int(input())
    print("How many fighters will shower field with blood?")
    FIGHTERS_COUNT = int(input())
    print("And how many players will rule some of them?")
    PLAYER_COUNT = int(input())
else:
    TEAM_MODE = 1
    TEAM_COUNT = 2
    FIGHTERS_COUNT = 6
    PLAYER_COUNT = 0
MAP_SIZE = 10
UP = 'w'
DOWN = 's'
LEFT = 'a'
RIGHT = 'd'
teams = [team() for i in range(TEAM_COUNT)]
note = ""
fighters = [fighter() for i in range(FIGHTERS_COUNT)]
fighters_names = []
battlefield = [[ground() for i in range(MAP_SIZE)] for i in range(MAP_SIZE)]
for i in range(len(fighters)):
    fighters[i].construct()
    fighters[i].name = name_generate(3, 7)
    fighters[i].team = i % TEAM_COUNT + 1
    team_arr[i % TEAM_COUNT] += 1
    fighters_names.append(fighters[i].name)
    while True:
        x = randint(0, MAP_SIZE - 1)
        y = randint(0, MAP_SIZE - 1)
        if not battlefield[x][y].full:
            break
    battlefield[x][y].fighter = fighters[i]
    battlefield[x][y].full = 1
    fighters[i].x = x
    fighters[i].y = y
    if i < PLAYER_COUNT:
        fighters[i].behaviour = "player"
        print("player ", i + 1, ")", sep="")
        print(stats(fighters[i]))
    if TEAM_MODE:
        if TEAM_COUNT < 10:
            fighters[i].symb = str(fighters[i].team)
        else:
            fighters[i].symb = chr(fighters[i].team + 97)
    else:
        fighters[i].symb = chr(97 + i)
if PLAY:
    score = []
    tick = battle(3)
    if tick > 0:
        score_print()
