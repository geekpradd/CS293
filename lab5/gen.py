n = 19
s = "{0} \n".format(n)
import random
for _ in range(2**n):
	v = random.randint(1, 6)
	s += "{0} ".format(v)

s+= "\n "

for _ in range(2**n):
	v = random.randint(0, 1)
	s += "{0} ".format(v)

s+= "\n "

with open("inp2", "w") as f:
	f.write(s)
