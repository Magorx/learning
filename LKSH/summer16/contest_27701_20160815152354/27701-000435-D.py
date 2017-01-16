positions = [int(i) for i in input().split()]
num = max(positions)
names = [str(i) for i in input().split()]
for i in range(num + 1):
    print(names[positions[i]], end  = ' ')