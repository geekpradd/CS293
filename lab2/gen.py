import random 

s = 0
k = 100

second = ""
for _ in range(k):
	num = random.randint(1, 1000)
	s += num
	second += str(num) + " "

first = "{0} {1} \n".format(s, k)
total = first + second 
with open("input.txt", "w") as f:
	f.write(total)