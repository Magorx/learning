def count_sort(numbers):
    min = numbers[0]
    max = numbers[0]
    for i in numbers:
        if i < min:
            min = i
        if i > max:
            max = i
    work = [0 for i in range(max + 1)]
    for i in numbers:
        work[i] += 1
    ret = []
    for i in range(len(work)):
        ret += [i] * work[i]
    return ret

file = open("countsort.in", "r")
num = file.readline()
numbers = [int(i) for i in file.readline().split()]

print(count_sort(numbers))
numbers = count_sort(numbers)

out = open("countsort.out", "w")
numbers = [str(numbers[i]) for i in range(len(numbers))]
print(" ".join(numbers), file=out)

out.close()
file.close()