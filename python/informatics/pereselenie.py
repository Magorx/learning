num = int(input())
arr = list(map(int, input().split()))
for i in range(len(arr)):
    for j in range(i, len(arr)):
        if arr[i] > arr[j]:
            arr[i] = j
            break
    else:
        arr[i] = -1
print(*arr)
