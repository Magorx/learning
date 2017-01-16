def check(arr):
    for i in range(len(arr)):
        for j in range(len(arr)):
            if i != j and arr[i][j] != 1:
                return "NO"
    return "YES"


file = open("complete.in", "r")
out = open("complete.out", "w")

num = [int(i) for i in file.readline().split()]
arr = [[0] * num[0] for i in range(num[0])]
string = file.readline()
while string != '':
    mas = [int(i) for i in string.split()]
    arr[mas[0] - 1][mas[1] - 1] = 1
    arr[mas[1] - 1][mas[0] - 1] = 1
    string = file.readline()
print(check(arr), file=out)
    
file.close()
out.close()