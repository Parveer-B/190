
energies = [[24, 22, 30, 15, 18, 19],
            [12, 23, 15, 23, 10, 15],
            [11, 13, 22, 13, 21, 14],
            [13, 15, 17, 28, 19, 21],
            [17, 17, 7, 27, 20, 19]]

# list of lists storing the minimum paths to each node
minimum_energies = []
for x in range(len(energies)):
    minimum_energies.append([0] * len(energies[0]))

# copy the energies list of lists and set the first row of minimum_energies to the first row of energies
minimum_energies[0] = energies[0]

# for each column
for x in range(1, len(energies)):
    # for each row
    for y in range(len(energies[0])):

        # if the node is on the left edge
        if y == 0:
            minimum_energies[x][y] = energies[x][y] + min(minimum_energies[x - 1][y], minimum_energies[x - 1][y + 1])

        # if the node is on the right edge
        elif y == (len(energies[0]) - 1):
            minimum_energies[x][y] = energies[x][y] + min(minimum_energies[x - 1][y], minimum_energies[x - 1][y - 1])

        else:
            minimum_energies[x][y] = energies[x][y] + min(minimum_energies[x - 1][y], minimum_energies[x - 1][y + 1], minimum_energies[x - 1][y - 1])

print(minimum_energies)

# bottom row contains total energies of seams
print(min(minimum_energies[-1]))
