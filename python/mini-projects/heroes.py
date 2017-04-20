#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import weapons as weapon
import equipment
import armours

class Item(object):
    weight = 1
    volume = 1
    count = 1
    price = 1
    _type = 'UNTYPED'
    name = 'UNNAMED'
        

class Inventory(object):
    def __init__(self):
        self.items = {}
        self.full_weight = 0
        self.full_volume = 0

    def add_item(self, item):
        self.items[item.name] = item
        self.full_volume += item.volume
        self.full_weight += item.weight

        return 0


class Atributes(object):
    def __init__(self, defined_atrs=None):
        self.stats = \
        {
        'hp' : 15,
        'mp' : 5,
        'stamina' : 10,
        'exp' : 0,
        'next_lvl_exp' : 100,
        'lvl' : 1,
        'strenght' : 10,
        'agility' : 10,
        'wisdom' : 10,
        'intelligence' : 10,
        'luck' : 10,
        'charisma' : 10
        }

        self.physic_resist = \
        {
        'slice'  : 1,
        'bash'   : 1,
        'pierce' : 1,
        'pain'   : 1,
        'tear'   : 1,
        'sound'  : 1
        }

        self.magic_resist =  \
        {
        'frost'  : 1,
        'fire'   : 1,
        'wind'   : 1,
        'earth'  : 1,
        'sorcery': 1,
        'mystic' : 1,
        'heal'   : 1
        }

        self.resistance = {'physic' : self.physic_resist,
                           'magic' : self.magic_resist}

        self.skill = \
        {
        'knife' : 1,
        'sword' : 1,
        'long_sword' : 1,
        'two-handed_sword' : 1,
        'bow' : 1,
        'axe' : 1,
        'spear' : 1,
        'trident' : 1,
        'club' : 1,
        'mace' : 1,
        'shield' : 1,
        'net' : 1,
        'magic_main' : 1,
        'magic_cold' : 1,
        'magic_fire' : 1,
        'magic_wind' : 1,
        'magic_earth' : 1,
        'magic_sorcery' : 1,
        'magic_mystic' : 1,
        'magic_heal' : 1,
        'athletics' : 1,
        'acrobatics' : 1,
        'light_armour' : 1,
        'heavy_armour' : 1
        }

        self.additional_atrs = {}
        if defined_atrs is not None:
            for atr in defined_atrs:
                self.additional_atrs[atr] = defined_atrs[atr]


    def set_atr(self, atr, value, atr_type=''):
        if atr_type:
            if atr_type == 'physic_coefs':
                self.physic_coefs[atr] = value
            elif atr_type == 'magic_coefs':
                self.magic_coefs[atr] = value
            elif atr_type == 'additional_atrs':
                self.additional_atrs[atr] = value
            else:
                return 'ERR_WRONG_ATR_TYPE'

            return 0

        if atr_type == 'physic_coefs':
            self.physic_coefs[atr] = value
        elif atr_type == 'magic_coefs':
            self.magic_coefs[atr] = value
        else:
            self.additional_atrs[atr] = value

        return 0


class Hero(object):
    def __init__(self, name='Dummy', defined_atrs=None):
        self.atrs = Atributes(defined_atrs=defined_atrs)
        self.name = name
        self.inventory = Inventory()

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



def main():
    hero = Hero()
    kn = weapon.knife()
    hero.add_item(kn)


if __name__ == "__main__":
    main()
