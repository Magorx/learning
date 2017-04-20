#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import weapons as weapon
import armours as armour
import equipment
import atributes
import items
from random import randint, choice


class Hero(object):
    def __init__(self, name='Dummy', defined_atrs=None):
        self.atributes = atributes.Atributes(defined_atrs=defined_atrs)
        self.atrs = self.atributes
        self.name = name
        self.inventory = items.Inventory()
        self.equipment = equipment.Equipment()

        self.equip_item(weapon.fist())
        self.equip_item(weapon.fist())
        self.atacking_hand = 'right_hand'

    def set_name(self, new_name):
        self.name = name
        return 0

    def set_atr(self, atr, value, atr_type=''):
        return self.atrs.set_atr(atr, value, atr_type=atr_type)

    def add_item(self, item):
        return self.inventory.add_item(item)

    def find_item_by_name(self, name):
        if name in self.inventory.items:
            return self.inventory.items[name]
        else:
            return None

    def equip_item(self, item):
        try:
            _type = item._type
        except Exception:
            return 'Something went wrong, while you were equiping "item"'

        if _type == 'weapon':
            return self.equipment.equip_weapon(item)
        elif _type == 'armour':
            return self.equipment.equip_armour(item)

    def attack(self, defender, body_part):
        if (self.equipment.weapon['right_hand'] is None):
            self.equip_item(weapon.fist())
        if self.equipment.weapon['left_hand'] is None:
            self.equip_item(weapon.fist())

        try:
            weapon = self.equipment.weapon[self.atacking_hand]
        except Exception:
            return 'Something went wrong, while attacking'

        clear_damage = randint(weapon.min_dmg, weapon.max_dmg)

        defence_in_percents = defender



def main():
    hero = Hero()
    hero.add_item(weapon.two_handed_sword())
    hero.add_item(armour.leather_armour())
    #hero.equip_item(hero.inventory.items['two-handed sword'])
    print(hero.equip_item(hero.inventory.items['leather armour']))

    hero.inventory.debug_print()
    hero.equipment.dump_equipment()


if __name__ == "__main__":
    main()
