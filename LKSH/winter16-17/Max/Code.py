import re

text = open("moroz.in", "r").read()
fout = open("moroz.out", "w")


text = text.split(".")
for j in range(len(text)):
    text[j] = text[j].split()
for i in range(len(text)):
    for j in range(2, len(text[i]) - 1):
        if text[i][j - 2] == "Ded" and text[i][j - 1] == "Moroz" and text[i][j] == "i":
            print(text[i][j + 1], file=fout)
            break
fout.close()
