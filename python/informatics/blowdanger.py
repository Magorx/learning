num = int(input())
arr1 = [1] * num
arr2 = [1] * num
for i in range (1, num):
    arr1[i] = arr1[i - 1] + arr2[i - 1]
    arr2[i] = arr1[i - 1]
print(arr1[-1] + arr2[-1])