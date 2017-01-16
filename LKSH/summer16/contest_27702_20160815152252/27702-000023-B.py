def is_prime(num):
    i = 2
    while i * i < num + 1:
        if num % i == 0:
            return False
        i += 1
    return True

chisla = int(input())
print(is_prime(chisla))
