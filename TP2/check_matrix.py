
f = open("graph.txt","r")
g = f.read()
m = [[int(j) for j in i.split(" ")] for i in g.split("\n")[:-1]]
r = True in [True in [(m[x][y] != m[y][x]) for x in range(0,8)] for y in range(0,8)]
print("Valid" if not r else "Invalid")
