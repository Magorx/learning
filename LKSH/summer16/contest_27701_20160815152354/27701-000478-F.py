name = input()
ban = [str(i) for i in input().split()]
ban_pos = [int(i) for i in input().split()]
favor = input()
for i in range(len(name)):
    if name[i] in ban and not i in ban_pos:
        name_list = list(name)
        name_list[i] = favor
        name = "".join(name_list)
print(name)