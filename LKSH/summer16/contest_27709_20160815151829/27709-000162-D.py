from collections import deque


def bfs(graph, u, visited=None, previous=None):
    queue = deque()
    if visited is None:
        visited = [False] * len(graph)
    if previous is None:
        previous = [None] * len(graph)
    visited[u] = True
    queue.append(u)
    while queue:
        current = queue.popleft()
        visited[current] = True
        for v in range(len(graph[current])):
            if graph[current][v]:
                if not visited[v]:
                    visited[v] = True
                    queue.append(v)
                    previous[v] = current
    return previous


def get_path(previous, f):
    if previous[f] is None:
        counter = -1
    else:
        counter = 0
    path = []
    while previous[f] is not None:
        path.append(f + 1)
        counter += 1
        f = previous[f]
    path.reverse()
    return counter, path


file = open("path.in", "r")
out = open("path.out", "w")
n = int(file.readline())
matrix = [[int(elem) for elem in file.readline().split()] for i in range(n)]
s, f = [int(i) for i in file.readline().split()]
previous = bfs(matrix, s - 1)
ans = get_path(previous, f - 1)
if s == f:
    print(0, "\n", s, sep="", file=out)
else:
    print(ans[0], file=out)
    if ans[1]:
        print(s, *ans[1], file=out)

file.close()
out.close()
