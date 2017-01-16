def gcd(num1, num2):
    while num2 > 0:
        num1, num2 = num2, num1 % num2
    return num1


numbers = [int(i) for i in input().split()]
i = 0
for i in range(1, len(numbers)):
    numbers[i] = gcd(numbers[i], numbers[i - 1])
    
print(numbers[-1])