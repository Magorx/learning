file = open("pants.in", "r")
out = open("pants.out", "w")

tickets = set()
n = int(file.readline())
printed = [int(i) for i in file.readline().split()]
tickets = set(printed)
print(len(tickets), file=out)

file.close()
out.close()
