def sort(numbers):
    for i in range(len(numbers) - 1):
        min_num = float("+inf")
        for j in range(i, len(numbers)):
            if numbers[j] < min_num:
                min_num = numbers[j]
                min_ind = j
        numbers[i], numbers[min_ind] = numbers[min_ind], numbers[i]
    return numbers


file = open("sort.in", "r")
num = file.readline()
numbers = [int(i) for i in file.readline().split()]

numbers = sort(numbers)

out = open("sort.out", "w")
numbers = [str(numbers[i]) for i in range(len(numbers))]
print(" ".join(numbers), file=out)

out.close()
file.close()