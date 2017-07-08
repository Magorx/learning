fin = open("input.txt", "r")
fout = open("output.txt", "w")

n = int(fin.readline())
arr = [[int(elem) for elem in fin.readline().split()] for i in range(n)]
fin.readline()
colors = [int(i) for i in fin.readline().split()]
counter = 0
for i in range(n):
    for j in range(n):
        if arr[i][j] == 1:
            if colors[i] != colors[j]:
                counter += 1
print(counter // 2, file=fout)

fin.close()
fout.close()