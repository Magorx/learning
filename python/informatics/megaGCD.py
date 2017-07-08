def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

a = int(input())
arr = list(map(int, input().split()))
for i in range(1, len(arr)):
    arr[i] = gcd(arr[i], arr[i - 1])
print(arr[-1])
