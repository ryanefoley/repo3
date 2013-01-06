
def get_c(G):
    sum = 0
    for node in G.nodes():
        k = G.degree(node)
        if k > 1:
            for neighbor in G.neighbors(node):
                for otherNeighbor in G.neighbors(node):
                    if otherNeighbor in G.neighbors(neighbor):
                        sum += 1/float(k * (k-1))
    print sum/float(len(G.nodes()))

