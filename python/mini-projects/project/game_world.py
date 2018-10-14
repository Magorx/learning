#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import tk_world
import textures
import info_window
import unit

class GameWorldTyle(tk_world.TkWorldTyle):
    def __init__(self, world, canvas, x=0, y=0, symb='.'):
        super(GameWorldTyle, self).__init__(world, canvas, x, y, symb=symb)

    def clicked(self, event):
        if self.creature:
            self.creature.clicked(event)
        elif self.building:
            self.building.clicked(event)
        elif self.landshaft:
            self.landshaft.clicked(event)
        else:
            unit.spawn_unit(self.world, self.x, self.y, unit.TYPE_CREATURE, 'cr', '@', [], -1, textures.unit)

class GameWorld(tk_world.TkWorld):
    def __init__(self,
                 width, height, 
                 tyle_type=GameWorldTyle,
                 common_symb='.',
                 side_px=tk_world.SIDE_PX,
                 pre_generated=False,
                 window=None,
                 textures=None):
        super(GameWorld, self).__init__(width, height, 
                                        tyle_type,
                                        common_symb,
                                        side_px,
                                        pre_generated,
                                        window,
                                        textures)

def main():
    world = GameWorld(10, 10, pre_generated=True)
    world.root_window.mainloop()


if __name__ == '__main__':
    main()