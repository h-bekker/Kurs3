a = eval(input())
if a % 10 == 0 :
	print("NO")
	exit()
temp = a
b = 0
while temp != 0 :
	b = b * 10 + (temp % 10)
	temp = temp // 10
if a == b:
	print("YES")
else :
	print("NO")
	

