def find_area(arr):
    s = 0
    arr.append(arr[0])
    for i in range(len(arr) - 1):
        s += (arr[i + 1][0] * arr[i][1] - arr[i][0] * arr[i + 1][1]) / 2
    return abs(s)


fin = open("rect.in", "r")
fout = open("rect.out", "w")

num = int(fin.readline())
arr = []
for i in range(num):
    string = fin.readline()
    string = list(map(int, string.split()))
    arr.append(string)

x1 = max([i[0] for i in arr])
x2 = min([i[2] for i in arr])
y1 = max([i[1] for i in arr])
y2 = min([i[3] for i in arr])

done = False
if x1 > x2 or y1 > y2:
    print(-1, file=fout)
    done = True
if not done:
    print(x1, y1, x2, y2, file=fout)

fin.close()
fout.close()