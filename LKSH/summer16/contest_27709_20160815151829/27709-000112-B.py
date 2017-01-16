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
    print(previous)
    return previous


def get_path(previous, f):
    counter = 0
    path = []
    while previous[f] is not None:
        path.append(f + 1)
        counter += 1
        f = previous[f]
    path.reverse()
    return counter


file = open("bfs.in", "r")
out = open("bfs.out", "w")

n, s, f = [int(i) for i in file.readline().split()]
matrix = [[int(elem) for elem in file.readline().split()] for i in range(n)]
previous = bfs(matrix, s - 1)
ans = get_path(previous, f - 1)
print(ans, file=out)
#print(s, *ans[1], file=out)

file.close()
out.close()
