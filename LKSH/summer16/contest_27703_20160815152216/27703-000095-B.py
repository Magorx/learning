file = open("inspection.in", "r")
num = file.readline()
s = [int(i) for i in file.readline().split()]

fmin = float("+inf")
smin = float("+inf")
for i in s:
    if i <= fmin:
        smin = fmin
        fmin = i
    elif i < smin:
        smin = i
out = open("inspection.out", "w")
print(fmin, smin, file=out)
out.close()
file.close()