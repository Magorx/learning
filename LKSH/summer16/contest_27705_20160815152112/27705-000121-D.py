import sys


def digital_root(num):
    num_save = num
    while num > 9:
        num = str(num)
        nums = [int(i) for i in num]
        for i in range(1, len(nums)):
            nums[i] = nums[i] + nums[i - 1]
        num = nums[-1]
    return num, num_save


sys.setrecursionlimit(100000)
file = open("dig-root.in", "r")
out = open("dig-root.out", "w")

num = [int(i) for i in file.readline().split()]
num.sort(key=digital_root)
print(*num, file=out)

file.close()
out.close()