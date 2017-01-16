max_long, strs = [int(i) for i in input().split()]
long = max_long
buyers = int(input())
things = [int(i) for i in input().split()]
for i in range(buyers):
    if long < things[i] * strs:
        print(i)
        break
    long -= things[i] * strs
else:
    print(i + 1)