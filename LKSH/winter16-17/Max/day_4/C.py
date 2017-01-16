def game(n, k):
    if n % (k + 1):
        return True
    return False


def find(arr, n):
    for i in range(len(arr)):
        if arr[i] == n:
            return i
    return -1


fin = open("input.in", "r")
fout = open("input.out", "w")

num = int(fin.readline())
p1 = p2 = 0ё
arr = list(map(int, fin.readline().split()))
dp1 = dp2 = [0] * num

ind = find(arr, max(arr))
arr = arr[ind + 1:len(arr) + 1] + arr[0: ind + 1]
print(arr)

for i in range(len(arr)):
    if i % 2:
        p2 += arr[i]
    else:
        p1 += arr[i]
print(p1, p2, file=fout)

fin.close()
fout.close()