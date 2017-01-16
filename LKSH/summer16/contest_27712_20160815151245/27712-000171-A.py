# import random
# import time


# def roll():
#     return random.randint(1, 6)


# def new_gen(genome):
#     rolled = random.randint(0, 2)
#     if len(genome) > rolled:
#         del genome[0]
#     genome.append(chr(random.randint(65, 65 + limit)))
#     if len(freeze) > rolled:
#         del freeze[0]
#     freeze.append(5)
#     # print("| | |")
#     # print(*genome)


# genome = []
# genome.append("A")
# genome.append("B")
# genome.append("C")
# freeze = [4] * len(genome)
# count = 1
# rolling = []
# limit = 3
# #print(*genome)

# while True:
#     for i in range(len(genome)):
#         if freeze[i] >= 0:
#             freeze[i] -= 1
#             rolling.append(i)
#         elif roll() in (4, 5, 6):
#             if freeze[i] != -2:
#                 freeze[i] = -2
#                 new_gen(genome)
#                 rolling.append(len(genome) - 1)
#                 if limit + 1 <= 25:
#                     limit += 1
#         else:
#             freeze[i] = 4
#         if random.randint(1, 50) in (1, 0):
#             freeze[i] = 4
#         if len(rolling) > 3:
#             del rolling[random.randint(0, 1)]
#     if roll() in (3, 4) and len(rolling) > 2:
#         genome[rolling[0]], genome[rolling[1]] = genome[rolling[0]], genome[rolling[1]]
#     elif roll() in (5, 6) and len(rolling) > 2:
#         genome[rolling[0]], genome[rolling[2]] = genome[rolling[2]], genome[rolling[0]]
#     elif len(rolling) > 2:
#         genome[rolling[1]], genome[rolling[2]] = genome[rolling[2]], genome[rolling[1]]
#     if roll() in (4, 5, 6) and len(rolling) > 2:
#         genome[rolling[1]], genome[rolling[2]] = genome[rolling[2]], genome[rolling[1]]
#     print(count, ") ", genome, sep="")
#     time.sleep(0.1)
#     count += 1
#     rolling = []
#     if count > 100 and limit > 24:
#         break
# I SENT IT ONLY TO HAVE THIS CODE IN MY PROFILE

file = open("pants.in", "r")
out = open("pants.out", "w")

tickets = set()
n = int(file.readline())
printed = [int(i) for i in file.readline().split()]
tickets = set(printed)
print(len(tickets), file=out)

file.close()
out.close()
