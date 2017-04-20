#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Creature(object):
    def __init__(self, body_parts=['head', 'body', 'arm', 'arm', 'leg', 'leg']):
        self.body_parts = {}
        for part in body_parts:


class BodyPart(object):
    def __init__(self, name='', hp='', type, attacking=False,
                 special_marks=['']):
        self.name = name
        self.hp = hp


def main():
    pass


if __name__ == "__main__":
    main()
