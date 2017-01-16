def super_sort(numbers):
    for i in range(1, len(numbers)):
        j = i - 1
        while j >= 0 and numbers[j] < numbers[j + 1]:
            numbers[j], numbers[j + 1] = numbers[j + 1], numbers[j]
            j -= 1
    return numbers


file = open("sort.in", "r")
num = file.readline()

numbers = [int(i) for i in file.readline().split()]

numbers = super_sort(numbers)

out = open("sort.out", "w")
numbers = [str(numbers[i]) for i in range(len(numbers))]
print(" ".join(numbers), file=out)

out.close()
file.close()