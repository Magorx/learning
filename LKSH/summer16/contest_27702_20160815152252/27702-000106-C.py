def easy_factors(num):
    i = 2
    factors = []
    while i * i < num + 1:
        while num % i == 0:
            factors.append(i)
            num //= i
        i += 1
    if num != 1:
        factors.append(num)
    return factors


n = int(input())
factors = easy_factors(n)
factors = [str(i) for i in factors]
factor = " ".join(factors)
print(factor)