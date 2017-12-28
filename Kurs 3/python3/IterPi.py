def pigen():
	ans=4
	step=1
	buf=step
	while 1 :
		yield ans
		if step<0:
			step = -step
		step+=2
		buf=(step-1)//2
		if (buf % 2) != 0 :
			step = -step
		ans+=4/step

eps=eval(input())
ans=1
lastgen=10
for elem in pigen():
	ans+=1
	if abs(lastgen-elem)<eps :
		break
	lastgen=elem
print(ans-2)
