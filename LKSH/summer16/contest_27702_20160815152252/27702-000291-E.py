def gcd(num1, num2):
    while num2 > 0:
        num1, num2 = num2, num1 % num2
    return num1


def lcm(num1, num2):
    return num1 * num2 // gcd(num1, num2)


num1, num2 = [int(i) for i in input().split()]
print(lcm(num1, num2))