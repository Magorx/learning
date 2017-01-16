def bin_left(s, x):
    left = -1
    right = len(s)
    while left + 1 < right:
        mid = (left + right) // 2
        if s[mid] < x:
            left = mid
        else:
            right = mid
    if right == len(s):
        return -1
    if s[right] == x:
        return right
    return -1


def bin_right(s, x):
    left = -1
    right = len(s)
    while left + 1 < right:
        mid = (left + right) // 2
        if s[mid] <= x:
            left = mid
        else:
            right = mid
    if left == -1:
        return -1
    if s[left] == x:
        return left
    return -1


file = open("mutants.in", "r")
out = open("mutants.out", "w")

m = file.readline()
num = [int(i) for i in file.readline().split()]
file.readline()
buter = [int(i) for i in file.readline().split()]
for i in range(len(buter)):
    left = bin_left(num, buter[i])
    right = bin_right(num, buter[i])
    print(right)
    if right == -1:
        print(0, file=out)
    elif left == right:
        print(1, file=out)
    else:
        print(right - left + 1, file=out)

file.close()
out.close()
