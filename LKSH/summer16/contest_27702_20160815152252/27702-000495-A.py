def printlist(s, bef, bet, endd):
    string = bef
    for i in range(len(s)):
        string += s[i]
        if i != len(s) - 1:
            string += bet
    string += endd
    print(string)
    return 0


s = [i for i in input().split()]
printlist(s, 'x=', '*', '.')
printlist(s, '', ' ', '')
printlist(s, '', '', '')
printlist(s, '"', '","', '"')
