#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Item(object):
    def __init__(self):
        self.weight = 1
        self.volume = 1
        self.count = 1
        self.price = 1
        self._type = 'UNTYPED'
        self.name = 'UNNAMED'

    def __repr__(self):
        return self.name

    def debug_print(self, debug_level=0):
        pretty_debug_str = '|' * debug_level
        debug_level += 1

        print(pretty_debug_str, '##Dumping_item [', self.name, ']', sep='')
        print(pretty_debug_str + ' /')

        to_print = []
        for stat in self.__dict__:
            to_print.append(pretty_debug_str + '|' + stat + ' ' + str(self.__dict__[stat]))
        to_print.sort()

        for printing in to_print:
            print(printing)

        print(pretty_debug_str + ' \\')
        

class Inventory(object):
    def __init__(self):
        self.items = {}
        self.full_weight = 0
        self.full_volume = 0

    def add_item(self, item):
        if item.name in self.items:
            self.items[item.name].count += 1
        self.items[item.name] = item
        self.full_volume += item.volume
        self.full_weight += item.weight

        return 0

    def debug_print(self, debug_level=0):
        pretty_debug_str = '|' * debug_level
        debug_level += 1

        print(pretty_debug_str + '##Dumping_inventory')
        print(pretty_debug_str + ' /')
        for item in self.items: 
            self.items[item].debug_print(debug_level=1)
        print(pretty_debug_str + ' \\')


def main():
    pass


if __name__ == "__main__":
    main()
