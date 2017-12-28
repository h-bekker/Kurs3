a = eval(input())
flag = False
for i in range(2,a) :
	k = i
	for j in range(i,a) :
		if k > a :
			break
		if k == a :
			print("YES")
			flag = True
			break
		k = k * i
	if flag :
		break
else :
	print("NO")
	
