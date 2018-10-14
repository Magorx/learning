#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
hp - hp
mp - mp
These atrs were making sence to me one day
Attack - clear damage output, without any buffs
Defence - clear damage reduction, without any buffs
Hardness - damage cutting after using all bonuses
Speed - every [speed] actions you can make a turn
'''


class Atributes():
    def __init__(self, hp, mp, attack, defence, hardness, speed):
        self.hp = hp
        self.mp = mp
        self. attack = attack
        self.defence = defence
        self.hardness = hardness
        self.speed = speed