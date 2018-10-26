#!/usr/bin/env python3
# -*- coding: utf-8 -*-


import game_engine


def main():
    engine = game_engine.GameEngine()
    engine.LoadWorld(20, 10, 'hax')
    engine.StartWorld()


if __name__ == '__main__':
    main()