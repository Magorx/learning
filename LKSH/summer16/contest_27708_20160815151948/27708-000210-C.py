def dfs(graph, u, visited=None):
    if visited is None:
        visited = [False] * len(graph)
    visited[u] = True
    for v in range(len(graph[u])):
        if graph[u][v]:
            if not visited[v]:
                dfs(graph, v, visited)
    return visited


file = open("components.in", "r")
out = open("components.out", "w")


n = int(file.readline())
matrix = [[int(elem) for elem in file.readline().split()] for i in range(n)]
counter = 0
visited = [False] * len(matrix)


for i in range(len(visited)):
    if not visited[i]:
        counter += 1
        visited = dfs(matrix, i, visited)

print(counter, file=out)

file.close()
out.close()
