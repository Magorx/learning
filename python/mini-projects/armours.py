#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Head - helmet 
Body - armour
Underbody - mail
Hands - gloves
Legs - pans
Foots - boots
"""

class Armour(object):
    def create_armour(self, name='UNNAMED', skill='none',
                      armour_type='nothing', price=0, weight=0, volume=0,
                      _type='none', defence_type={'none' : 0}):
        super(Armour, self).__init__()
        self.name = name
        self.skill = skill
        self.armour_type = armour_type
        self.price = price
        self.weight = weight
        self.volume = volume
        self._type = _type
        self.defence_type = defence_type


class leather_helmet(Armour):
    def __init__(self):
        self.create_armour(name='leather helmet',
                           skill=['light_armour', 'helmets'],
                           armour_type='helmet',
                           price=10,
                           weight=3,
                           volume=2,
                           _type='armour',
                           defence_type={'slice' : 10,
                                         'bush' : 10,
                                         'pierce' : 5})


class leather_armour(Armour):
    def __init__(self):
        self.create_armour(name='leather armour',
                           skill=['light_armour', 'armours'],
                           armour_type='armour',
                           price=30,
                           weight=7,
                           volume=7,
                           _type='armour',
                           defence_type={'slice' : 10,
                                         'bush' : 10,
                                         'pierce' : 10})


class iron_male(Armour):
    def __init__(self):
        self.create_armour(name='iron mail',
                           skill=['light_armour', 'males'],
                           armour_type='mail',
                           price=50,
                           weight=10,
                           volume=6,
                           _type='armour',
                           defence_type={'slice' : 17,
                                         'bush' : 10,
                                         'pierce' : 10})


class leather_gloves(Armour):
    def __init__(self):
        self.create_armour(name='leather gloves',
                           skill=['light_armour', 'gloves'],
                           armour_type='gloves',
                           price=15,
                           weight=2,
                           volume=2,
                           _type='armour',
                           defence_type={'slice' : 10,
                                         'bush' : 5,
                                         'pierce' : 5})


class leather_pans(Armour):
    def __init__(self):
        self.create_armour(name='leather pans',
                           skill=['light_armour', 'pans'],
                           armour_type='pans',
                           price=20,
                           weight=5,
                           volume=5,
                           _type='armour',
                           defence_type={'slice' : 10,
                                         'bush' : 10,
                                         'pierce' : 5})


class leather_boots(Armour):
    def __init__(self):
        self.create_armour(name='leather boots',
                           skill=['light_armour', 'boots'],
                           armour_type='boots',
                           price=20,
                           weight=4,
                           volume=5,
                           _type='armour',
                           defence_type={'slice' : 10,
                                         'bush' : 10,
                                         'pierce' : 5})


class blank_armour(Armour):
    def __init__(self):
        self.create_armour(name='',
                           skill=[''],
                           armour_type='',
                           price=0,
                           weight=0,
                           volume=0,
                           _type='',
                           defence_type={'' : 0})


def main():
    leather_boots()


if __name__ == "__main__":
    main()
