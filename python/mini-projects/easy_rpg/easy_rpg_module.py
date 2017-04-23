#!/usr/bin/env python3
# -*- coding: utf-8 -*-


LVL_EXP = [-1, 0, 15, 35, 58, 94, 133, 178, 241, 392, 495]


class Creature(object):
    def __init__():

class Creature(object):
    def __init__(self, strenght=1, intelligence=1, dexterity=1,
                 lvl=1, exp=0, stat_points=0,
                 attack=10, defence=10,
                 crit_chance=5, evade_chace=5, damage_cut=5, 
                 gold=0,):
        self.strenght = strenght
        self.intelligence = intelligence
        self.dexterity = dexterity
        self.lvl = lvl
        self.exp = exp
        self.attack = attack
        self.defence = defence
        self.crit_chance = crit_chance
        self.evade_chace = evade_chace
        self.damage_cut = damage_cut
        self.gold = gold

    def lvl_up(self):
        if not self.check_lvlup():
            return 0

        self.exp -= LVL_EXP[lvl + 1]
        self.lvl += 1
        self.stat_points += 1

        return 0

    def upgrade_str(self):
        if self.stat_points > 0:
            self.strenght += 1
            self.stat_points -= 1

    def upgrade_int(self):
        if self.stat_points > 0:
            self.intelligence += 1
            self.stat_points -= 1

    def upgrade_dex(self):
        if self.stat_points > 0:
            self.dexterity += 1
            self.stat_points -= 1

    def upgrade_stat(self, stat):
        if stat == 'str' or stat == 'strenght':
            self.upgrade_str()
        if stat == 'int' or stat == 'intelligence':
            self.upgrade_str()
        if stat == 'dex' or stat == 'dexterity':
            self.upgrade_str()

        return 0

    def check_lvl_up(self):
        if self.exp >= LVL_EXP[lvl + 1]:
            return True
        else:
            return False

    def update_lvl(self):
        if self.check_lvl_up():
            self.lvl_up()

        return 0


def main():
    pass


if __name__ == "__main__":
    main()
