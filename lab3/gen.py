n = 20
t = 1000000
import random
s = "{0} {1}".format(n, t)

for _ in range(t):
	v = random.randint(1, 51724158235371)
	s += "\nU {0}".format(v)

with open("input.txt", "w") as f:
	f.write(s)