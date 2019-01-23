#!/usr/bin/env python3
# -*- coding: utf-8 -*-


MAX_N = 1000000


class Heap():
    def __init__(self, max_size=0):
        if not max_size:
            max_size = 1000000
        self.vault = [None for i in range(max_size + 1)]
        self.max_size = max_size
        self.cur_size = 0
        self.val_to_index = [[0, 0] for i in range(MAX_N)]
    
    def size(self):
        return self.cur_size - 1

    def insert(self, x):
        if self.size() == self.max_size:
            return False

        if self.val_to_index[x][1] == 0:
            self.cur_size += 1
            self.vault[self.cur_size] = x
            self.val_to_index[x][0] = self.cur_size
            self.val_to_index[x][1] = 1
            self.sift_up(self.cur_size)
        else:
            self.val_to_index[x][1] += 1
            

    def sift_up(self, v):
        if v == 1:
            return

        if self.vault[v // 2] > self.vault[v]:
            self.vault[v // 2], self.vault[v] = self.vault[v], self.vault[v // 2]
            x1, x2 = self.vault[v // 2], self.vault[v]

            self.val_to_index[x2][0] = v
            self.val_to_index[x1][0] = v // 2
            self.sift_up(v // 2)

    def sift_down(self, v):
        cur = v
        if 2 * v <= self.cur_size and self.vault[cur] > self.vault[2 * v]:
            cur = 2 * v
        if 2 * v < self.cur_size and self.vault[cur] > self.vault[2 * v + 1]:
            cur = 2 * v + 1
        
        if cur != v:
            x1, x2 = self.vault[cur], self.vault[v]
            self.val_to_index[x1][0] = v
            self.val_to_index[x2][0] = cur

            self.vault[cur], self.vault[v] = self.vault[v], self.vault[cur]
            self.sift_down(cur)
    
    def del_v(self, v):
        ret = self.vault[v]
        self.val_to_index[ret][1] -= 1
        if self.val_to_index[ret][1] == 0:
            self.vault[v] = self.vault[self.cur_size]
            self.val_to_index[self.vault[v]] = [v, self.val_to_index[self.vault[v]][1]]
            self.vault[self.cur_size] = None
            self.cur_size -= 1
            self.sift_down(v)
        return True

    def del_val(self, val):
        v = self.val_to_index[val][0]
        self.del_v(v)


n, k = map(int, input().split())
arr = list(map(int, input().split()))
h = Heap(k + 10)
for i in range(k):
        h.insert(arr[i])
print(h.vault[1])
for z in range(n - k):
    h.del_val(arr[z])
    h.insert(arr[z + k])
    print(h.vault[1])