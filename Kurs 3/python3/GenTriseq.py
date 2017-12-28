def NotIncrease():
	global N
	v=eval(input())
	N=eval(input())
	if len(v)*len(v)<N:
		yield "NO"
	else :
		yield N
	for i in range(len(v)):
		for j in range(len(v)):
			if v[i]>=v[j]:
				yield v[j]

N=1
flag=False
step=-1
for elem in NotIncrease():
	if elem == "NO" :
		print("NO")
		break
	if step==N:
		print(elem)
		flag = True
		break
	step+=1
if flag == False:
	print("NO")
