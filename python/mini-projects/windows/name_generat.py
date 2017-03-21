import random

def name_generate(mini, maxi):
    length = random.randint(mini, maxi)
    glasn = ["a", "i", "o", "u", "e"]
    soglasn = ['b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 
          'r', 's', 't', 'v', 'w', 'x', 'y', 'z']
    name = ""
    for i in range(length):
        if i % 3 == 0:
            roll = random.randint(0, len(glasn) - 1)
            name = name + glasn[roll]
        else: 
            roll = random.randint(0, len(soglasn) - 1)
            name = name + soglasn[roll]
    return name


name = name_generate(4, 4)
print(name)
