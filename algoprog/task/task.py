#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def gcd(a,b):
    """Compute the greatest common divisor of a and b"""
    while b > 0:
        a, b = b, a % b
    return a
    
def lcm(a, b):
    """Compute the lowest common multiple of a and b"""
    return a * b / gcd(a, b)

a, b = map(int, input().split())
print(lcm(a, b))