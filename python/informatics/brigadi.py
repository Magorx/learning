r, c = list(map(int, input().split()))
arr = list(map(int, input().split()))
arr.sort(reverse=True)
m = 0
for i in range(0, len(arr), c):
    s = arr[i] - arr[i + c - 1]
    if s > m:
        m = s
print(m)
