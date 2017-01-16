def shift(numbers):
    last = numbers[-1]
    for i in range(len(numbers) - 1, -1, -1):
        numbers[i] = numbers[i - 1]
    numbers[0] = last
    return numbers
        

file = open("shift.in", "r")
num = file.readline()
numbers = [int(i) for i in file.readline().split()]

print(shift(numbers))

out = open("shift.out", "w")
numbers = [str(numbers[i]) for i in range(len(numbers))]
print(" ".join(numbers), file=out)
out.close()
file.close()