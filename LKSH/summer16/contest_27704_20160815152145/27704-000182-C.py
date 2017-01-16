def power(num):
    if num % 2 == 0:
        num //= 2
        power(num)
    else:
        if num == 1:
            print("YES", file=out)
        else:
            print("NO", file=out)
            

file = open("two.in", "r")
out = open("two.out", "w")

ans = ''
n = int(file.readline())
power(n)

file.close()
out.close()