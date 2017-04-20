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

class Equipment(object):
    def __init__(self):
        self.armour = {}
        self.armour['helmet'] = None
        self.armour['cloack'] = None
        self.armour['armour'] = None
        self.armour['mail'] = None
        self.armour['gloves'] = None
        self.armour['pans'] = None
        self.armour['boots'] = None

        self.ring = {}
        self.ring['right_hand'] = None
        self.ring['left_hand'] = None

        self.weapon = {}
        self.weapon['right_hand'] = None
        self.weapon['left_hand'] = None

    def equip_weapon(self, weapon):
        try:
            if weapon._type != 'weapon':
                return 'Something is wrong with your "weapon"'
        except Exception:
            return 'Something is very wrong with your "weapon"'
            
        if weapon.need_arms == 2:
            if self.weapon['right_hand'] or self.weapon['left_hand']:
                return 'First unequip your weapon'
            self.weapon['right_hand'] = weapon
            self.weapon['left_hand'] = weapon
            
        if None not in [self.weapon['right_hand'], self.weapon['left_hand']]:
            return 'First unequip your weapon'

        if self.weapon['right_hand'] is None:
            self.weapon['right_hand'] = weapon
        elif self.weapon['left_hand'] is None:
            self.weapon['left_hand'] = weapon
        else:
            return 'First unequip your weapon'

        return 0

    def equip_armour(self, armour):
        try:
            if armour._type != 'armour':
                return 'Something is wrong with your "armour"'
        except Exception:
            return 'Something is very wrong with your "armour"'

        try:
            armour_type = armour.armour_type
        except Exception:
            return 'Some problems while equiping "armour"'

        self.armour[armour_type] = armour

        return 0

    def dump_equipment(self):
        print('helmet', self.armour['helmet'])
        print('cloack', self.armour['cloack'])
        print('armour', self.armour['armour'])
        print('mail', self.armour['mail'])
        print('gloves', self.armour['gloves'])
        print('pans', self.armour['pans'])
        print('boots', self.armour['boots'])
        print()
        print('right_hand', self.ring['right_hand'])
        print('left_hand', self.ring['left_hand'])
        print()
        print('right_hand', self.weapon['right_hand'])
        print('left_hand', self.weapon['left_hand'])

        return 0
        

def main():
    pass


if __name__ == "__main__":
    main()
