num = int(input())
name = ''
all_names = list()
for i in range(num):
    s = input()
    all_names.append(s)
for i in range(1, num + 1):
    name += all_names[-i]
print(name)