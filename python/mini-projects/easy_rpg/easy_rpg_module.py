#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from random import randint, choice


LVL_NEXP = [-1, 0, 15, 35, 58, 94, 133, 178, 241, 392, 495]
LVL_ATK =  [-1, 10, 11, 15, 21, 45, 73, 98]
LVL_DEF =   [-1, 10, 12, 18, 27, 59, 95, 140]
LOG = open('rpg.log', 'w')


class Creature(object):
    def __init__(self, color='White', name='Noname', 
                 strenght=1, intelligence=1, dexterity=1,
                 lvl=1, exp=0, stat_points=0,
                 attack=10, defence=10,
                 crit_chance=5, evade_chace=5, damage_cut=5, 
                 gold=0):
        self.color = color
        self.name = name
        self.strenght = strenght
        self.intelligence = intelligence
        self.dexterity = dexterity
        self.exp = exp
        self.lvl = lvl
        self.attack = attack
        self.max_attack = attack
        self.defence = defence
        self.max_defence = defence
        self.crit_chance = crit_chance
        self.evade_chace = evade_chace
        self.damage_cut = damage_cut
        self.gold = gold

    def __repr__(self):
        return self.color + ' knight ' + self.name

    def lvl_up(self):
        if not self.is_lvl_up():
            return 0

        self.exp -= LVL_NEXP[lvl + 1]
        self.lvl += 1
        self.stat_points += 1

        return 0

    def is_lvl_up(self):
        if self.exp >= LVL_NEXP[lvl + 1]:
            return True
        else:
            return False

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

    def update_lvl(self):
        if self.is_lvl_up():
            self.lvl_up()

        return 0

    def die(self, battle):
        if battle is not None:
            del battle.creatures[battle.creatures.index(self)]
            battle.hero_count[self.color] -= 1
            if battle.hero_count[self.color] <= 0:
                try:
                    del battle.alive_sides[battle.alive_sides.index(self.color)]
                except Exception:
                    print('-----ERROR KILLING', self)

        return 0

    def deal_damage(self, damage):
        self.defence -= damage

    def attack_another(self, defender, battle=None):
        clear_damage = self.attack
        if randint(0, 1):
            damage = clear_damage * self.damage_cut // 100
        else:
            damage = clear_damage

        self.deal_damage(damage)
        print(self.name, 'dealt', damage, 'damage to', defender.name, file=LOG)
        if self.defence <= 0:
            print(defender.name, 'was killed', file=LOG)
            defender.die(battle=battle)

    def set_atr(atr, value):
        self.__dict__[atr] = value


class Battle(object):
    def __init__(self, creatures, x, y):
        self.creatures = creatures #sorted(creatures, key=lambda creature: creature.color)
        self.hero_count = {}
        self.alive_sides = []
        for cr in creatures:
            if not cr.color in self.hero_count:
                self.hero_count[cr.color] = 1
                self.alive_sides.append(cr.color)
            else:
                self.hero_count[cr.color] += 1

        self.x = x
        self.y = y

    def execute(self):
        print('Battle[{}][{}] was started'.format(self.x, self.y), file=LOG)
        creatures = self.creatures
        while True:
            for i in range(len(creatures)):
                cur_creature = creatures[i]
                for j in range(len(creatures)):
                    if creatures[j].color != cur_creature.color:
                        cur_creature.attack_another(creatures[j], self)
                    if len(self.alive_sides) == 1:
                        self.end()
                        return 0

    def end(self):
        print('Battle[{}][{}] was won by {} nation'.format(self.x, self.y, self.alive_sides[0]), file=LOG)


def main():
    one = Creature(color='Green', name='One', damage_cut=50)
    two = Creature(color='Blue', name='Two', damage_cut=50)
    battle = Battle([one, two], 1, 1)
    battle.execute()
    LOG.close()


if __name__ == "__main__":
    main()
