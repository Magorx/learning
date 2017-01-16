import sys


def dfs(graph, u, visited=None):
    if visited is None:
        visited = [False] * len(graph)
    visited[u] = True
    for v in graph[u]:
            if not visited[v]:
                dfs(graph, v, visited)
    return visited

file = open("connected.in", "r")
out = open("connected.out", "w")

sys.setrecursionlimit(10000)
n, m = [int(i) for i in file.readline().split()]
arr = [[] for i in range(n)]
for i in range(m):
    v1, v2 = [(int(j) - 1) for j in file.readline().split()]
    arr[v1].append(v2)
    arr[v2].append(v1)
visited = dfs(arr, 0)
components = 1
edges = []

for i in range(len(arr)):
    if not visited[i]:
        components += 1
        edges.append((i, i + 1))
        visited = dfs(arr, i, visited)

print(components - 1, file=out)
for i in edges:
    print(*i, file=out)

file.close()
out.close()
