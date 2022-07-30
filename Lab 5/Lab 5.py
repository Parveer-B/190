import numpy as np

class Node:
    def __init__(self, name):
        self.name = name
        self.connections = []
        self.visited = False


def connect(node1, node2, weight):
    node1.connections.append({"node": node2, "weight": weight})
    node2.connections.append({"node": node1, "weight": weight})


def BFS(node):
    """Visits and prints all nodes in a graph"""
    q = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        print(cur.name)
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                con["node"].visited = True


def get_all_nodes(node):
    '''Return a list of the nodes in the graph of nodes connected to node
    (N.B., the nodes can be indirectly connected as well)'''
    q = [node]
    nodes = [node]
    node.visited = True
    while len(q) > 0:
        cur = q.pop(0)  # remove q[0] from q and put it in cur
        for con in cur.connections:
            if not con["node"].visited:
                q.append(con["node"])
                nodes.append(con["node"])
                con["node"].visited = True

    for n in nodes:
        n.visited = False

    return nodes


def unvisit_all(node):
    '''Change all n.visited to False in all the nodes in the graph of nodes
    connected to node. Use BFS to find all the nodes'''
    q = [node]
    node.visited = False
    while len(q) > 0:
        cur = q.pop(0) # remove q[0] from q and put it in cur
        for con in cur.connections:
            if con["node"].visited:
                q.append(con["node"])
                con["node"].visited = False


def DFS_rec(node):
    '''Print out the names of all nodes connected to node using a
    recursive version of DFS'''
    node.visited = True
    print(node.name)

    for con in node.connections:
        if not con["node"].visited:
            DFS_rec(con["node"])


def DFS(node):
    '''Print out the names of all nodes connected to node using a non-recursive
    version of DFS. Make it so that the nodes are printed in the same order
    as in DFS_rec'''

    q = [node]
    node.visited = True
    while (len(q) > 0):
        cur = q.pop(-1)
        print(cur.name)

        for con in reversed(cur.connections):
            if not con["node"].visited:

                q.append(con["node"])
                con["node"].visited = True


def dijsktra_slowish(node):
    '''Implement Dijkstra's algorithm as discussed in class (i.e., you don't
    need to use a priority queue'''
    S = [node]
    d = {node.name: 0}

    unexplored = get_all_nodes(node)
    unexplored.remove(node)

    while len(unexplored) > 0:
        min = ["no node found", float("inf")]
        for node in S:
            for con in node.connections:
                if con["node"] not in S:
                    if con["weight"] + d[node.name] < min[1]:
                        min = [con["node"], con["weight"] + d[node.name]]

        S.append(min[0])
        d[min[0].name] = min[1]
        unexplored.remove(min[0])

    return d


if __name__ == '__main__':
    TO = Node("TO")
    NYC = Node("NYC")
    DC = Node("DC")
    CDMX = Node("CDMX")
    SF = Node("SF")

    connect(TO, NYC, 3)
    connect(TO, SF, 6)
    connect(TO, CDMX, 7)
    connect(NYC, DC, 2)
    connect(SF, DC, 5)

    L = get_all_nodes(TO)
    print("\n")

    BFS(TO)
    print("\n")

    unvisit_all(TO)
    DFS_rec(TO)

    unvisit_all(TO)
    print("\n")

    DFS(TO)

    print("\n")

    unvisit_all(TO)
    print(dijsktra_slowish(TO))