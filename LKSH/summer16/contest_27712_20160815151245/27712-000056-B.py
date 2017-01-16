file = open("cubes.in", "r")
out = open("cubes.out", "w")

n, m = map(int, file.readline().split())
masha = set()
pasha = set()
for i in range(n):
    masha.add(int(file.readline()))
for i in range(m):
    pasha.add(int(file.readline()))
print(len(masha & pasha), file=out)
if len(masha & pasha):
    ans = list(masha & pasha)
    ans.sort()
    print(*ans, file=out)
print(len(masha - pasha), file=out)
if len(masha - pasha):
    ans = list(masha - pasha)
    ans.sort()
    print(*ans, file=out)
print(len(pasha - masha), file=out)
if len(pasha - masha):
    ans = list(pasha - masha)
    ans.sort()
    print(*ans, file=out)

file.close()
out.close()
