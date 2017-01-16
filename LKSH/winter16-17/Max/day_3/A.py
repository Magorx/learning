def find_area(arr):
    s = 0
    for i in range(len(arr) - 1):
        s += (arr[i + 1][0] * arr[i][1] - arr[i][0] * arr[i + 1][1]) / 2
    return abs(s)


fin = open("area.in", "r")
fout = open("area.out", "w")

num = int(fin.readline())
arr = []
for i in range(num):
    arr.append(list(map(float, fin.readline().split())))

arr.append(arr[0])

print(find_area(arr), file=fout)


fin.close()
fout.close()