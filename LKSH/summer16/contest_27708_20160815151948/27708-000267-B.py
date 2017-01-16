import sys


def dfs(graph, u, visited=None):
    if visited is None:
        visited = [False] * len(graph)
    visited[u] = True
    for v in graph[u]:
            if not visited[v]:
                dfs(graph, v, visited)
    return visited


sys.setrecursionlimit(10000)
file = open("reach.in", "r")
out = open("reach.out", "w")

n, j = [int(i) for i in file.readline().split()]
arr = [[int(i) - 1 for i in file.readline().split()][1:] for i in range(n)]
visited = dfs(arr, j - 1)
counter = 0
for i in visited:
    if i:
        counter += 1
print(counter, file=out)
file.close()
out.close()
