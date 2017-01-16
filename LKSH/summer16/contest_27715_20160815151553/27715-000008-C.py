def change(num, i, taps):
    if i == taps:
        print(num, file=out)
    else:
        change(num + 1, i + 1, taps)
        change(num * 3, i + 1, taps)


file = open("calc.in", "r")
out = open("calc.out", "w")

num, taps = [int(i) for i in file.readline().split()]
change(num, 0, taps)

file.close()
out.close()
