fin = open("colour.in", "r")
fout = open("colour.out", "w")

ar = [["N" for i in range(210)] for j in range(210)]
num = int(fin.readline())
arr = []
color = []
for i in range(num):
    string = fin.readline()
    color.append(string[-2])
    string = string[:len(string) - 3]
    string = list(map(int, string.split()))
    for i in range(len(string)):
        string[i] += 105
    arr.append(string)

for ii in range(len(arr)):
    for i in range(arr[ii][0], arr[ii][2]):
        for j in range(arr[ii][1], arr[ii][3]):
            if (color[ii] == "R" and ar[i][j] == "Y") or\
             (color[ii] == "Y" and ar[i][j] == "R"):
                ar[i][j] = "O"
            if (color[ii] == "R" and ar[i][j] == "B") or\
             (color[ii] == "B" and ar[i][j] == "R"):
                ar[i][j] = "V"
            if color[ii] == "Y" and ar[i][j] == "B" or\
             (color[ii] == "B" and ar[i][j] == "Y"):
                ar[i][j] = "G"
            if color[ii] == "V" and ar[i][j] == "Y" or\
             (color[ii] == "Y" and ar[i][j] == "V"):
                ar[i][j] = "W"
            if color[ii] == "O" and ar[i][j] == "B" or\
             (color[ii] == "B" and ar[i][j] == "O"):
                ar[i][j] = "W"
            if color[ii] == "G" and ar[i][j] == "R" or\
             (color[ii] == "R" and ar[i][j] == "G"):
                ar[i][j] = "W"
            if ar[i][j] == "N":
                ar[i][j] = color[ii]

need = fin.readline()[0]
cnt = 0
for i in range(len(ar)):
    for j in range(len(ar)):
        if ar[i][j] == need:
            cnt += 1

print(cnt, file=fout)

fin.close()
fout.close()