def LookSay() :
	l = '1'
	s = 1
	y = ''
	while 1:
		x = str(l) + ' '
		for i in range(len(x) - 1):		
			if x[i] == x[i + 1]: 
				s += 1
			else:
				y += str(s) + str(x[i])
				s = 1
			yield x[i]
		x = ''
		l = y
		y = ''
		s = 1

n = eval(input())
k = 0
for i in LookSay():
	if k == n:
		print(i)
		break
	k += 1
