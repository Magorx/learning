file = open("frequency.in", "r")
out = open("frequency.out", "w")

dictionary = dict()
string = file.readline()
while string:
    for word in (string.split()):
        dictionary[word] = dictionary.get(word, 0) - 1
    string = file.readline()

string = file.readline()
dictionary = list(map(lambda x: list(reversed(x)), dictionary.items()))
dictionary.sort()
for i in dictionary:
    print(i[1], file=out)

file.close()
out.close()
#
