import math
from typing import List, Tuple

inf = float('inf')


def kruskal_method(edge_list: List[Tuple[int, ...]]):
    def get_all_vertex(edge_list):
        s = set()
        for tup in edge_list:
            s.add(tup[0])
            s.add(tup[1])
        return s

    def can_connect(vertex_lists, vertex_ints, t0, t1):
        for vertex_list in vertex_lists:
            if t0 in vertex_list and t1 in vertex_list:
                return False
            elif (t0 in vertex_list and t1 not in vertex_list) or (t1 in vertex_list and t0 not in vertex_list):
                return True
        if t0 in vertex_ints or t1 in vertex_ints:
            return True
        return False

    def connect(vertex_lists, t0, t1):
        index0 = -1  # Found t0
        index1 = -1  # Found t1
        for index, vertex_list in enumerate(vertex_lists):
            if t0 in vertex_list:
                index0 = index
            elif t1 in vertex_list:
                index1 = index

        if index0 != -1 and index1 != -1:  # found t0 and t1 in separate lists
            vertex_lists[index0].extend(vertex_lists[index1])  # append all elements of right to left
            vertex_lists = vertex_lists[0:index1] + vertex_lists[index1 + 1:]
        elif index0 != -1:
            vertex_lists[index0].append(t1)
        elif index1 != -1:
            vertex_lists[index1].append(t0)
        else:
            vertex_lists.append([t0, t1])
        return vertex_lists

    edge_column = []
    vertex_ints = get_all_vertex(edge_list)
    vertex_lists = []

    k = len(edge_list)
    n = len(vertex_ints)
    __OPERATIONS__ = (n - 1) * n + (k - n + 1) + k * math.ceil(math.log2(k))

    sorted_edge_list = sorted(edge_list, key=lambda t: t[2])
    for index, tup in enumerate(sorted_edge_list):
        # print(sorted_edge_list[index:])
        # print('Result:     ', edge_column)
        # print('Not joined: ', vertex_ints)
        # print('Joined:     ', vertex_lists)
        # print()

        if len(vertex_ints) == 0 and len(vertex_lists) == 1:
            break

        t0, t1, t2 = tup[0], tup[1], tup[2]
        if can_connect(vertex_lists, vertex_ints, t0, t1):
            edge_column.append((t0, t1, t2))
            vertex_lists = connect(vertex_lists, t0, t1)
            vertex_ints.discard(t0)
            vertex_ints.discard(t1)

    return edge_column, __OPERATIONS__


def ford_bellman_algorithm_old(graph, start_vertex):
    operations = 0
    edges_size = len(graph)
    distance = [inf for _ in range(edges_size)]

    distance[start_vertex] = 0

    for _ in range(edges_size - 1):
        for u, v, w in graph:
            operations += 1
            if distance[u] != inf and distance[u] + w < distance[v]:
                distance[v] = distance[u] + w
            elif distance[v] != inf and distance[v] + w < distance[u]:
                distance[u] = distance[v] + w

    return list(filter(lambda n: n != inf, distance)), operations


def ford_bellman_algorithm(graph, start_vertex):
    operations = 0

    distance, past = {}, {}
    vertex_amount = len(graph)
    for vertex in graph:
        distance[vertex], past[vertex] = inf, None
    distance[start_vertex] = 0

    for _ in range(vertex_amount - 1):
        changed = False
        for vertex in graph:
            for joined_vertex in graph[vertex]:
                operations += 1
                weight = graph[vertex][joined_vertex]
                if distance[vertex] + weight < distance[joined_vertex]:
                    distance[joined_vertex], past[joined_vertex] = distance[vertex] + weight, vertex
                    changed = True
        if not changed:
            break

    return distance, operations


def dijkstra_algorithm(graph: dict, start_vertex, end_vertex):
    operations = 0

    unvisited, visited = {}, {}
    path = []
    current_vertex = start_vertex
    current_distance = 0
    for vertex in graph:
        unvisited[vertex] = inf
    unvisited[start_vertex] = 0

    while True:
        operations += 1
        for joined_vertex, weight in graph[current_vertex].items():
            if joined_vertex not in unvisited:
                continue
            operations += 1
            # unvisited[joined_vertex] = min(unvisited[joined_vertex], current_distance + weight)
            if current_distance + weight < unvisited[joined_vertex]:
                unvisited[joined_vertex] = current_distance + weight
                if joined_vertex == end_vertex:  # print path to end_vertex
                    path.append(current_vertex)
        visited[current_vertex] = current_distance
        unvisited.pop(current_vertex)
        if len(unvisited) == 0:
            break
        probable_vertexes = [vertex for vertex in unvisited.items() if vertex[1] != inf]
        if len(probable_vertexes) == 0:
            break
        current_vertex, current_distance = sorted(probable_vertexes, key=lambda v: v[1])[0]

    return visited, operations, path
