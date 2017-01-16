def sieve(num):
    numbers = [True for i in range(num2 + 1)]
    i = 2
    while i * i < num + 1:
        for j in range(i * i, num + 1, i):
            numbers[j] = False
        i += 1
    return numbers

num1, num2 = [int(i) for i in input().split()]
numbers = sieve(num2)
if num1 == 1:
    num1 = 2
for i in range(num1, num2 + 1):
    if numbers[i]:
        print(i, end = ' ')