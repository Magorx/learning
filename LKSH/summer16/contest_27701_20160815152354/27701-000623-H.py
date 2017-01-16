def winner():
    cost = [int(i) for i in input().split()]
    sand = cost[0] * cost[2]
    if cost[0] == 0 and cost[1] != 0 and cost[3] != 0:
        return "Ron"
    if cost[3] == 0 or (cost[1] == 0 and cost[2] != 0):
        return "Hermione"
    else:
        if cost[0] == 0:
            if cost[1] == 0:
                if cost[2] == 0:
                    return "Ron"
                else:
                    return "Hermione"
        if cost[2] == 0:
            return "Ron"
        else:
            if cost[4] == 0:
                if cost[5] == 0:
                    return "Hermione"
                else:
                    return "Ron"
            else:
                if cost[5] == 0:
                    return "Hermione"
                else:
                    sand = cost[0] * cost[2]
                    gold = sand // cost[0] * cost[1] // cost[2] * cost[3]
                    if ((gold // cost[4] * cost[5] > sand) or
                        (gold // cost[4] * cost[5] == sand and gold % cost[4] > 0)):
                        return "Ron"
                    else:
                        return "Hermione"
                        
                        
print(winner())