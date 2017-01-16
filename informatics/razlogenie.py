def devider(a, b):
    while b != 0:
        b, a = a % b, b
    return a


def devide(num):
    for i in range(2, int(num ** (0.5)) + 1):
        while num % i == 0:
            arr.append(i)
            num //= i
        if num == 1:
            break
    if num != 1:
        arr.append(num)

num = int(input())
arr = []
devide(num)
arr = list(map(str, arr))
print('*'.join(arr))
