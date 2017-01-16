def dfs(graph, u, counter=1, visited=None):
    if visited is None:
        visited = [False] * len(graph)
    visited[u] = True
    for v in range(len(graph[u])):
        if graph[u][v]:
            if not visited[v]:
                counter += 1
                counter = dfs(graph, v, counter, visited)
    return counter


file = open("dfs.in", "r")
out = open("dfs.out", "w")

n, s = [int(i) for i in file.readline().split()]
arr = [[0] * n for i in range(n)]
for i in range(n):
    num = file.readline().split()
    for j in range(n):
        arr[i][j] = int(num[j])
print(dfs(arr, s - 1), file=out)

file.close()
out.close()
