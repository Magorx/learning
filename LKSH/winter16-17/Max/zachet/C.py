def next(arr):
    for i in range(len(arr) - 1, 0, -1):
        if arr[i] > arr[i - 1]:
            num = i
            for j in range(i, len(arr)):
                if abs(arr[i - 1] - arr[j]) < abs(arr[i - 1] - arr[num]):
                    if arr[j] > arr[i - 1]:
                        num = j
                        #arr[j], arr[i - 1] = arr[i - 1], arr[j]
            arr[num], arr[i - 1] = arr[i - 1], arr[num]
            arrr = sorted(arr[i:])
            arr = arr[:i] + arrr
            print(*arr, file=fout)
            break
    else:
        ar = [i + 1 for i in range(len(arr))]
        print(*ar, file=fout)


fin = open("nextperm.in", 'r')
fout = open("nextperm.out", "w")

n = list(map(int, fin.readline().split()))
arr = list(map(int, fin.readline().split()))
next(arr)

fout.close()