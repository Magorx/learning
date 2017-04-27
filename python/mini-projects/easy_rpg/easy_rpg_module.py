#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice, shuffle
from time import sleep
import sys
from menu import *


LVL_NEXP = [0, 15, 35, 58, 94, 133, 178, 241, 392, 495, 1, 1, 1, 1, 10000000]
LVL_ATK =  [50, 10, 11, 15, 21, 32, 47, 70]
LVL_DEF =  [110, 10, 13, 21, 35, 54, 84, 123]
LOW_SKILL_LVL = 30
MEDIUM_SKILL_LVL = 60
HIGHT_SKILL_LVL = 80
LOG = open('rpg.log', 'w')


def atk_by_lvl(lvl):
    res = 0
    for i in range(1, lvl + 1):
        res += 10 * 1.05 ** i
    return int(res)


def def_by_lvl(lvl):
    res = 0
    for i in range(1, lvl + 1):
        res += 10 * 1.10 ** i
    return int(res)


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

    def full_report(self, menu=False, file=LOG):
        self.update_lvl()
        self.attack = atk_by_lvl(self.lvl)
        self.defence = def_by_lvl(self.lvl)
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

        print('{} leveled up'.format(self), file=LOG)
        self.lvl += 1
        self.stat_points += 1
        self.attack = atk_by_lvl(self.lvl)
        self.defence = def_by_lvl(self.lvl)

        return 0

    def handle_lvl_up(self):
        print('You got new level!')

    def is_lvl_up(self):
        if self.exp >= LVL_NEXP[self.lvl]:
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
        while self.is_lvl_up():
            self.lvl_up()

        return 0

    def add_exp(self, exp):
        self.exp += exp

    def set_ad_by_lvl(self):
        self.attack = atk_by_lvl(self.lvl)
        self.defence = atk_by_lvl(self.lvl)
        self.max_attack = def_by_lvl(self.lvl)
        self.max_defence = def_by_lvl(self.lvl)

    def die(self, battle):
        self.alive = False
        self.defence = 0

        if battle is not None:
            try:
                battle.sides[self.color]['alive_hero_count'] -= 1
                if battle.sides[self.color]['alive_hero_count'] <= 0:
                        battle.alive_sides_count -= 1
            except Exception:
                print('##### ERROR KILLING', self)

        return 0

    def revive(self, full=True):
        self.alive = True
        if full:
            self.defence = self.max_defence
            self.attack = self.max_attack
        else:
            self.defence = max(1, self.defence)
            self.attack = max(1, self.attack)

        return 0

    def deal_damage(self, damage):
        self.defence -= damage

    def attack_another(self, defender, battle=None):
        if battle is None:
            file = LOG
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
    def __init__(self, creatures, x, y, win_exp=3, loos_exp=1, file=sys.stdout):
        self.creatures = creatures
        shuffle(self.creatures)
        self.hero_count = {}
        self.sides = []
        self.recount_alives()
        self.win_exp = win_exp
        self.loos_exp = loos_exp

        self.file = file
        self.x = x
        self.y = y

    def execute(self, full_log=False, hit_delay=0):
        self.recount_alives()
        print_boarder(self.file)
        print('--- Battle[{}][{}] was executed'.format(self.x, self.y),
              file=self.file)

        if full_log:
            print('Sides:', self.alive_sides())
            for cr in self.creatures:
                print(cr, 'Atk {} | Def {}'.format(cr.attack, cr.defence))
            print('---------------\nLOG:')
        creatures = self.creatures
        battle_round = 0
        while True:
            if battle_round >= 1000000:
                break
            battle_round += 1

            self.recount_alives()
            i = 0
            while i < len(creatures):
                cr = creatures[i]
                if not cr.alive:
                    i += 1
                    continue

                j = i
                while j > len(creatures) * -1:
                    if cr.color != creatures[j].color and creatures[j].alive:
                        cr.attack_another(creatures[j], battle=self)
                        break
                    j -= 1
                if self.alive_sides_count < 2:
                    battle_round = 1000001

                sleep(hit_delay)
                i += 1

        self.end()
        return 0

    def end(self):
        for i in range(len(self.creatures)):
            cr = self.creatures[i]
            cr.revive()
            if cr.color in self.alive_sides():
                cr.add_exp(self.win_exp)
            else:
                cr.add_exp(self.loos_exp)
            cr.update_lvl()

        print('--- Battle[{}][{}] was won by {} nation'.\
            format(self.x, self.y, self.alive_sides()), file=self.file)
        print_boarder(self.file)
        return self.alive_sides()

    def recount_alives(self):
        sides = {}
        self.alive_sides_count = 0
        for cr in self.creatures:
            if cr.alive:
                if cr.color in sides:
                    sides[cr.color]['alive_hero_count'] += 1
                else:
                    self.alive_sides_count += 1
                    sides[cr.color] = {}
                    sides[cr.color]['alive_hero_count'] = 1
        self.sides = sides

        return 0

    def alive_sides(self):
        alive_sides = []
        for side in self.sides:
            if self.sides[side]['alive_hero_count'] > 0:
                alive_sides.append(side)
        if len(alive_sides) > 1:
            return alive_sides
        else:
            return alive_sides[0]


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


def main():
    hero = Creature(name='Max', color='Green', lvl=2, exp=0, stat_points=5, gold=115, to_update_by_lvl=True)
    def foo():
        for i in range(1):
            creatures = [Creature(name=randname(), color=choice(['Green', 'White']),
                                  evade_chace=randint(10, 40), crit_chance=randint(10, 50), damage_cut=randint(10, 30),
                                  lvl=1, to_update_by_lvl=True) for j in range(randint(3, 5))]
            creatures = creatures + [hero]
            battle = Battle(creatures, randint(1, 5), randint(1, 5))
            battle.execute(full_log=True)
    
    
    menu = Menu(['report', 'battle', 'exit'], [hero.full_report, foo, exit])
    one = Menu(['Go'], [menu], name='first')
    menu()

    LOG.close()


if __name__ == '__main__':
    main()
