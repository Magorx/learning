def find_area(arr):
    s = 0
    arr.append(arr[0])
    for i in range(len(arr) - 1):
        s += (arr[i + 1][0] * arr[i][1] - arr[i][0] * arr[i + 1][1]) / 2
    return abs(s)


fin = open("point.in", "r")
fout = open("point.out", "w")

num = int(fin.readline())
arr = []
for i in range(num):
    arr.append(list(map(float, fin.readline().split())))

dot = list(map(float, fin.readline().split()))

sm = 0
arr.append(arr[0])
for i in range(len(arr) - 1):
    sm += find_area(arr[i:i + 2] + [dot])

arr.pop()
need = find_area(arr)

if sm != need:
    print("NO", file=fout)
else:
    print("YES", file=fout)

fin.close()
fout.close()