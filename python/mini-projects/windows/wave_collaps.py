from random import randint, choice
from time import sleep
from colorama import Fore, Style, Back, init

init(autoreset = True)

def pos(y, x):
    return '\x1b[{};{}H'.format(y, x)

#=HELP_FUNCTIONS================================================================

def pprint(matr):
    for i in range(len(matr)):
        print(*matr[i])

def beauty_pprint(matr, fore = Fore.CYAN, back = Back.BLACK,
                  style = Style.BRIGHT, x = 1, y = 1):
    for i in range(len(matr)):
        for j in range(len(matr[0])):
            print(pos(x + i, y + j) + fore + back + style + str(matr[i][j]), end="")
        print()

def rotate_matrix(matr):
    matr = matr[:]
    n = len(matr)
    m = len(matr[0])
    n, m = m, n
    ans = [[0] * n for i in range(m)]
    for i in range(n):
        for j in range(m):
            ans[j][n - i - 1] = matr[i][j]
    return ans

def matrix_to_tuple(matr):
    for i in range(len(matr)):
        matr[i] = tuple(matr[i])
    matr = tuple(matr)
    return matr

def tuple_to_matrix(tup):
    tup = list(tup)
    for i in range(len(tup)):
        tup[i] = list(tup[i])
    return tup
#==COLLAPSE_FUNCTIONS===========================================================
def cut_input_matrix(matr, n):
    n -= 1
    output = set()
    piece = []
    for i in range(len(matr) - n):
        for j in range(len(matr) - n):
            piece.append(tuple((matr[i][j : j + n + 1])))
            piece.append(tuple((matr[i + 1][j : j + n + 1])))
            for z in range(3):
                piece = matrix_to_tuple(piece)
                output.add(piece)
                #piece = tuple_to_matrix(piece)
                piece = rotate_matrix(piece)
            piece = []
    return output

def check_rightness(matr, tiles, n):
    cheking = []
    tiles = set(tiles)
    for i in range(len(matr) - n):
        for j in range(len(matr) - n):
            cheking.append(matr[i][j : j + n + 1])
            cheking.append(matr[i + 1][j : j + n + 1])
            if not checking in tiles:
                return 0
            checking = []
    return 1

def wave_collapse(in_tile, n, size):
    tiles = cut_input_matrix(in_tile, n)
    tiles = list(tiles)
    confined = [[False for i in range(size)] for i in range(size)]
    out_tile = [[0 for i in range(size)] for i in range(size)]
    chosen = []
    i = 0
    j = 0
    attempts = 0
    test = []
    while True and attempts < 1000:
        chosen = choice(tiles)
        for x in range(n):
            for y in range(n):
                if confined[i + x][j + y]:
                    y += 1
                    if y >= n:
                        y = 0
                        x += 1
                        if x >= n:
                            break
                    continue
                #test[i + x][i + y] = chosen[x][y]
                out_tile[i + x][j + y] = chosen[x][y]
                if out_tile[x][y] and out_tile[x][y] != " ":
                    confined[x][y] = 1
                #pprint(out_tile)
                #sleep(0.5)
                #print("=====")
        attempts += 1
        j += 1
        if j == size - n + 1:
            i += 1
            j = 0
            if i > size - n:
                break
    return out_tile
#=MAIN==========================================================================
matrix = ["     ",
          "++#++",
          "##  +",
          "##+ +"
          "##++#",
          "    #"]

for i in range(len(matrix)):
    matrix[i] = list(matrix[i])
    
s = wave_collapse(matrix, 2, 5)
pprint(s)
