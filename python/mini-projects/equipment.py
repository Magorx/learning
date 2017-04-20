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




class equipment(object):
    def __init__(self):
        self.armour = {}
        self.armour['helmet'] = None
        self.armour['cloack'] = None
        self.armour['armout'] = None
        self.armour['mail'] = None
        self.armour['gloves'] = None
        self.armour['pans'] = None
        self.armour['boots'] = None

        self.ring = {}
        self.rings['right_hand_ring'] = None
        self.rings['left_hand_ring'] = None

        self.weapon = {}
        self.weapon['right_hand_weapon'] = None
        self.weapon['left_hand_weapon'] = None

    def equip_weapon(self, weapon):
        try:
            if weapon._type != 'weapon':
                return 'Something is wrong with your "weapon"'
        except Exception:
            return 'Something is very wrong with your "weapon"'
            
        if weapon.need_arms == 2:
            if self.right_hand_weapon or self.left_hand_weapon:
                return 'First unequip your weapon'
        if None is not in [self.right_hand_weapon, self.left_hand_weapon]:
            return 'First unequip your weapon'

        if self.right_hand_weapon is None:
            self.right_hand_weapon = weapon
        elif self.left_hand_weapon is None::
            self.left_hand_weapon = weapon
        else:
            return 'First unequip your weapon'

        return 0
        

def main():
    pass


if __name__ == "__main__":
    main()
