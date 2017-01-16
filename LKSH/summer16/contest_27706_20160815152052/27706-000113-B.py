def bin_search(s, x):
    left = -1
    right = len(s)
    while left + 1 < right:
        mid = (left + right) // 2
        if s[mid] < x:
            left = mid
        else:
            right = mid
    if right == len(s):
        return "NO"
    if s[right] == x:
        return "YES"
    return "NO"


file = open("collect.in", "r")
out = open("collect.out", "w")

m = file.readline()
print(m)
num = [int(i) for i in file.readline().split()]
print(num)
file.readline()
buter = [int(i) for i in file.readline().split()]

for i in range(len(buter)):
    print(bin_search(num, buter[i]), file=out)

file.close()
out.close()
