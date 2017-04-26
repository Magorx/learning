#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice
from time import sleep
import sys


LVL_NEXP = [0, 15, 35, 58, 94, 133, 178, 241, 392, 495]
LVL_ATK =  [50, 10, 11, 15, 21, 45, 73, 98]
LVL_DEF =   [110, 10, 12, 18, 27, 59, 95, 140]
LOW_SKILL_LVL = 30
MEDIUM_SKILL_LVL = 60
HIGHT_SKILL_LVL = 80
LOG = open('rpg.log', 'w')


def choices(population, weights=None, k=1):
    if weights is None:
        randomizing_arr = population
    elif len(weights) != len(population):
        raise IndexError
    else:
        randomizing_arr = []
        for i in range(len(population)):
            for j in range(weights[i]):
                randomizing_arr.append(population[i])

    result_arr = []
    for i in range(k):
        result_arr.append(choice(randomizing_arr))

    if len(result_arr) == 1:
        return result_arr[0]
    else:
        return result_arr


def print_boarder(file=sys.stdout):
    print('-' * 77 + '|', file=file)


class Creature(object):
    def __init__(self, color='White', name='Noname', 
                 strenght=1, intelligence=1, dexterity=1,
                 lvl=1, exp=0, stat_points=0,
                 attack=10, defence=10,
                 crit_chance=5, evade_chace=5, damage_cut=5, 
                 gold=0, alive=True,
                 to_update_by_lvl=False, file=LOG):
        self.color = color
        self.name = name
        self.strenght = strenght
        self.intelligence = intelligence
        self.dexterity = dexterity
        self.exp = exp
        self.lvl = lvl
        self.stat_points = stat_points
        self.attack = attack
        self.max_attack = attack
        self.defence = defence
        self.max_defence = defence
        self.crit_chance = crit_chance
        self.evade_chace = evade_chace
        self.damage_cut = damage_cut
        self.gold = gold
        self.alive = alive
        if to_update_by_lvl:
            self.set_ad_by_lvl()

    def __repr__(self):
        return '{' + self.color + '} ' + self.name

    def full_report(self, file=LOG):
        print('Hero {} from {} castle'.format(self.name, self.color))
        print('Attack {}   Defence {}'.format(self.attack, self.defence))
        print('{}/{} exp  Lvl {} ({})'.format(self.exp, LVL_NEXP[self.lvl], 
                                         self.lvl, self.stat_points))
        print('Gold {}'.format(self.gold))
        print('Str {}  Int {}  Dex {}'.format(self.strenght, self.intelligence,
                                              self.dexterity))
        print('Crit {}  Evade {}  Damage cut {}'.format(self.crit_chance,
                                                        self.evade_chace,
                                                        self.damage_cut))


    def lvl_up(self):
        if not self.is_lvl_up():
            return 0

        print('{} leveled up'.format(self))
        self.exp -= LVL_NEXP[self.lvl + 1]
        self.lvl += 1
        self.stat_points += 1

        return 0

    def handle_lvl_up(self):
        print('You got new level!')

    def is_lvl_up(self):
        if self.exp >= LVL_NEXP[self.lvl + 1]:
            return True
        else:
            return False

    def upgrade_str(self):
        if self.stat_points <= 0:
            return 0

        self.strenght += 1
        self.stat_points -= 1
        if self.damage_cut < LOW_SKILL_LVL:
            self.damage_cut += 3
        elif self.damage_cut < MEDIUM_SKILL_LVL:
            self.damage_cut += 2
        elif self.damage_cut < HIGHT_SKILL_LVL:
            self.damage_cut += 1

    def upgrade_int(self):
        if self.stat_points <= 0:
            return 0

        self.intelligence += 1
        self.stat_points -= 1
        if self.crit_chance < LOW_SKILL_LVL:
            self.crit_chance += 3
        elif self.crit_chance < MEDIUM_SKILL_LVL:
            self.crit_chance += 2
        elif self.crit_chance < HIGHT_SKILL_LVL:
            self.crit_chance += 1

    def upgrade_dex(self):
        if self.stat_points > 0:
            return 0

        self.dexterity += 1
        self.stat_points -= 1
        if self.evade_chace < LOW_SKILL_LVL:
            self.evade_chace += 3
        elif self.evade_chace < MEDIUM_SKILL_LVL:
            self.evade_chace += 2
        elif self.evade_chace < HIGHT_SKILL_LVL:
            self.evade_chace += 1


    def upgrade_stat(self, stat):
        if stat == 'str' or stat == 'strenght':
            self.upgrade_str()
        if stat == 'int' or stat == 'intelligence':
            self.upgrade_str()
        if stat == 'dex' or stat == 'dexterity':
            self.upgrade_str()

        return 0

    def update_lvl(self):
        if self.is_lvl_up():
            self.lvl_up()

        return 0

    def add_exp(self, exp):
        self.exp += exp

    def set_ad_by_lvl(self):
        self.attack = LVL_ATK[self.lvl]
        self.defence = LVL_DEF[self.lvl]

    def die(self, battle):
        self.alive = False
        if battle is not None:
            battle.hero_count[self.color] -= 1
            if battle.hero_count[self.color] <= 0:
                try:
                    del battle.alive_sides[battle.alive_sides.index(self.color)]
                except Exception:
                    print('##### ERROR KILLING', self)

        return 0

    def deal_damage(self, damage):
        self.defence -= damage

    def attack_another(self, defender, battle=None):
        if battle is None:
            file = self.file
        else:
            file = battle.file
        clear_damage = self.attack
        if choices([0, 1], weights=[100-self.crit_chance, self.crit_chance]):
            damage = clear_damage * 2
            crit = True
        else:
            damage = clear_damage
            crit = False
        if randint(0, 1):
            damage = int(damage * (100 - self.damage_cut) / 100)
            cut = True
        else:
            cut = False

        if not choices([0, 1], weights=[100-defender.evade_chace, defender.evade_chace]):
            defender.deal_damage(damage)
            evade = False
        else:
            evade = True

        print('[', self, ']', sep='', end=' ', file=file)
        if evade:
            print('missed [', defender, '].', sep='', file=file)
        else:
            if crit:
                print('greatly hit', sep='', end=' ', file=file)
            else:
                print('hit', sep='', end=' ', file=file)
            print('[', defender, ']', sep='', end=' ', file=file)
            print('for {} damage.'.format(damage), file=file)

        

        if defender.defence <= 0:
            print(defender.name, 'was killed', file=file)
            defender.die(battle=battle)

    def set_atr(atr, value):
        self.__dict__[atr] = value


class Battle(object):
    def __init__(self, creatures, x, y, file=sys.stdout):
        self.creatures = creatures
        self.hero_count = {}
        self.alive_sides = []
        for cr in creatures:
            if not cr.color in self.hero_count:
                self.hero_count[cr.color] = 1
                self.alive_sides.append(cr.color)
            else:
                self.hero_count[cr.color] += 1

        self.file = file
        self.x = x
        self.y = y

    def execute(self, hit_delay=0):
        print_boarder(self.file)
        print('--- Battle[{}][{}] was started'.format(self.x, self.y),
              file=self.file)
        creatures = self.creatures
        while True:
            i = 0
            while i < len(creatures):
                cur_creature = creatures[i]
                for j in range(len(creatures)):
                    if (creatures[j].color != cur_creature.color and 
                        creatures[j].alive):
                        cur_creature.attack_another(creatures[j], self)
                        break
                    if len(self.alive_sides) == 1:
                        return self.end()
                sleep(hit_delay)
                i += 1

    def end(self):
        for i in range(len(self.creatures)):
            self.creatures[i].alive = True
        print('--- Battle[{}][{}] was won by {} nation'.\
            format(self.x, self.y, self.alive_sides[0]), file=self.file)
        print_boarder(self.file)
        return self.alive_sides[0]


def randname(min_len=3, max_len=7,
             vowel_raise=1, consonant_raise=2, starting_randomizing_arr=[0]):
    if not starting_randomizing_arr:
        starting_randomizing_arr = [0]
    length = randint(min_len, max_len)
    vowels = ['a', 'i', 'o', 'u', 'e']
    consonants = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 
          'r', 's', 't', 'v', 'w', 'x', 'y', 'z']

    name = ''
    randomizing_arr = starting_randomizing_arr
    for i in range(length):
        if not choice(randomizing_arr):
            name = name + choice(consonants)
            for j in range(vowel_raise):
                randomizing_arr.append(1)
        else:
            name = name + choice(vowels)
            for j in range(consonant_raise):
                randomizing_arr.append(0)

    return name


class Menu(object):
    def __init__(self, buttons, links, name='', id=0):
        if len(buttons) != len(links):
            raise IndexError
        self.buttons = ['Back'] + buttons
        self.links = ['Back'] + links
        self.name = name
        self.id = id

    def print_buttons(self):
        for i in range(len(self.buttons)):
            print('{}. {}'.format(i, self.buttons[i]))

    def button_pressed(self, button_index):
        if button_index == 0:
            return 'Back'
        link = self.links[button_index]
        if callable(link):
            link()
        elif isinstance(link, Menu):
            link.call()

    def call(self):
        while True:
            print('-- {} --'.format(self.name))
            self.print_buttons()
            print('-' * (len(self.name) + 6))
            pressed = input()
            try:
                pressed = int(pressed)
            except Exception:
                print('Input should be integer')
                continue
            if pressed >= len(self.links):
                print('Input must be chosen from variants')
                continue
            to_do = self.button_pressed(pressed)
            if to_do == 'Back':
                return 0




def main():
    # for i in range(1):
    #     creatures = [Creature(name=randname(), color=choice(['Green', 'Blue', 'White']),
    #                           evade_chace=randint(10, 40), crit_chance=randint(10, 50), damage_cut=randint(10, 30),
    #                           lvl=0, to_update_by_lvl=True) for j in range(randint(2, 2))]
    #     battle = Battle(creatures, randint(1, 5), randint(1, 5))
    #     print(battle.execute())
    hero = Creature(name='Max', color='Green', lvl=3, exp=17, stat_points=5, gold=115, to_update_by_lvl=True)
    
    menu = Menu(['report', 'stop'], [hero.full_report, exit], name='Report')
    one = Menu(['Go'], [menu], name='GO')
    one.call()

    LOG.close()


if __name__ == '__main__':
    main()
