def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def nok(a, b):
    return a * b // gcd(a, b)


file = open("ponies.in", "r")
out = open("ponies.out", "w")

n, m = [int(i) for i in file.readline().split()]
print(nok(n, m), file=out)

file.close()
out.close()
