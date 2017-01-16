def find_area(arr):
    s = 0
    arr.append(arr[0])
    for i in range(len(arr) - 1):
        s += (arr[i + 1][0] * arr[i][1] - arr[i][0] * arr[i + 1][1]) / 2
    return abs(s)


fin = open("point.in", 'r')
fout = open("point.out", "w")

ar1 = list(map(int, fin.readline().split()))
ar2 = list(map(int, fin.readline().split()))
ar3 = list(map(int, fin.readline().split()))

if find_area([ar1, ar2, ar3]) == 0:
    print("YES", file=fout)
else:
    print("NO", file=fout)

fout.close()