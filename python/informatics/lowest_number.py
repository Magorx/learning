num = list(input())
num.sort()
count = 0
for i in range(len(num)):
    num[i] = int(num[i])
    if num[i] == 0:
        count += 1
num = [num[count]] + [0] * count + num[count + 1:]
num = list(map(str, num))
print("".join(num))
