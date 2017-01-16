def fill(num):
    arr = [[0] * num for i in range(num)]
    work_num = 1
    for i in range(num):
        for j in range(num):
            if i % 2 == 0:
                arr[i][j] = work_num
            else:
                arr[i][num - j - 1] = work_num
            work_num += 1
    return arr


file = open("snake.in", "r")
out = open("snake.out", "w")

num = [int(i) for i in file.readline().split()]
num = num[0]
arr = fill(num)
# arr.reverse()
for i in arr:
    print(*i, file=out)

file.close()
out.close()
