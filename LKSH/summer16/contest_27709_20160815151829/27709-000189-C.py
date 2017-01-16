from collections import deque


file = open("card-game.in", "r")
out = open("card-game.out", "w")

n = int(file.readline())
p1 = deque()
p2 = deque()
num = [int(i) for i in file.readline().split()]
for i in range(len(num)):
    p1.append(num[i])
num = [int(i) for i in file.readline().split()]
for i in range(len(num)):
    p2.append(num[i])

turn = 0
while turn < 2 * (10 ** 5) and p1 and p2:
    card1 = p1.popleft()
    card2 = p2.popleft()
    if card1 == 0 and card2 == n - 1:
        p1.append(card1)
        p1.append(card2)
    elif card2 == 0 and card1 == n - 1:
        p2.append(card1)
        p2.append(card2)
    elif card1 > card2:
        p1.append(card1)
        p1.append(card2)
    elif card1 < card2:
        p2.append(card1)
        p2.append(card2)
    turn += 1
if turn == 2 * (10 ** 5):
    print("draw", file=out)
elif p1:
    print("first", turn, file=out)
elif p2:
    print("second", turn, file=out)

file.close()
out.close()
