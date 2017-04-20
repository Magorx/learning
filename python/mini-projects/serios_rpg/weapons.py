#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import items

class Weapon(items.Item):
    def __init__(self):
        items.Item.__init__(self)

    def create_weapon(self, name='UNNAMED', skill=['none'],
                      need_arms=0, price=0, weight=0, volume=0,
                      _type='none', hit_types={'none' : ['none', '0-0']}):
        self.name = name
        self.skill = skill
        self.need_arms = need_arms
        self.price = price
        self.weight = weight
        self.volume = volume
        self._type = _type

        self.atack_types = {}
        for atack_type in hit_types:
            self.atack_types[atack_type] = {}
            self.atack_types[atack_type]['type'] = hit_types[atack_type][0]
            try:
                min_dmg = int(hit_types[atack_type][1].split('-')[1])
                max_dmg = int(hit_types[atack_type][1].split('-')[2])
            except Exception:
                return None

            self.atack_types[atack_type]['min_dmg'] = min_dmg
            self.atack_types[atack_type]['max_dmg'] = max_dmg


class fist(Weapon):
    def __init__(self):
        Weapon.__init__(self)
        
        self.create_weapon(name='fist',
                           skill=['fist'],
                           need_arms=1,
                           price=0,
                           weight=0,
                           volume=0,
                           _type='weapon',
                           hit_types={'hit' : ['bash', '1-3'],
                                      'smash' : ['bash', '2-2']})


class knife(Weapon):
    def __init__(self):
        Weapon.__init__(self)

        self.create_weapon(name='knife',
                           skill=['knife'],
                           need_arms=1,
                           price=10,
                           weight=2,
                           volume=2,
                           _type='weapon',
                           hit_types={'jab' : ['pierce', '1-4'],
                                      'slice' : ['slice', '']})


class sword(Weapon):
    def __init__(self):
        Weapon.__init__(self)

        self.create_weapon(name='sword',
                           skill=['sword'],
                           need_arms=1,
                           price=20,
                           weight=9,
                           volume=5,
                           _type='weapon',
                           hit_types={'slice' : ['slice', '1-6']})


class axe(Weapon):
    def __init__(self):
        Weapon.__init__(self)

        self.create_weapon(name='axe',
                           skill=['axe'],
                           need_arms=1,
                           price=50,
                           weight=10,
                           volume=6,
                           _type='weapon',
                           hit_types={'slice' : ['slice', '1-6'],
                                     'bash' : ['bash', '2-4']})


class two_handed_sword(Weapon):
    def __init__(self):
        Weapon.__init__(self)

        self.create_weapon(name='two-handed sword',
                           skill=['two-handed_sword'],
                           need_arms=2,
                           price=100,
                           weight=13,
                           volume=15,
                           _type='weapon',
                           hit_types={'slice' : ['slice', '2-8'],
                                     'great hit' : ['pierce', '3-6']})


class blank_weapon(Weapon):
    def __init__(self):
        Weapon.__init__(self)

        self.create_weapon(name='',
                           skill=[''],
                           need_arms=1,
                           price=0,
                           weight=0,
                           volume=0,
                           _type='weapon',
                           hit_types={'slice' : ['slice', '-']})



def main():
    knife()


if __name__ == "__main__":
    main()
