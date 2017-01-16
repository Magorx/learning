string = input()
if len(string) == 1 and string[0] == 's':
    string += string
elif string[-1] == 's':
    for i in [-2, -2]:
        ch = string[i]
        string += ch
if len(string) > 10:
    string *= 2
print(string)