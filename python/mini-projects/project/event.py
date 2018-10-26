#!/usr/bin/env python3
# -*- coding: utf-8 -*-

TYLE_CLICKED = 1000
CREATURE_CLICKED = 1001
BUILDNIG_CLICKED = 1002
LANDSHAFT_CLICKED = 1003
CREATURE_DIE = 1004


class Event():
	def __init__(self, tk_event, type, tyle=None, creature=None, building=None, landshaft=None):
		self.tk_event = tk_event
		self.type = type
		self.tyle = tyle
		self.creature = creature
		self.building = building
		self.landshaft = landshaft
