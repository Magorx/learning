def count_pages(a, b, m):
    return m // a + m // b


def find_time(a, b, n):
    left = -1
    right = n * max(a, b) + 1
    while left + 1 < right:
        m = (left + right) // 2
        if count_pages(a, b, m) < n:
            left = m
        else:
            right = m
    print(min(x, y) + right, file=out)


file = open("easy.in", "r")
out = open("easy.out", "w")

n, x, y = [int(i) for i in file.readline().split()]
find_time(x, y, n - 1)

file.close()
out.close()
