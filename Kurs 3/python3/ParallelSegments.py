x1,y1,x2,y2,x3,y3,x4,y4=eval(input())
a1=x2-x1
a2=y2-y1
b1=x4-x3
b2=y4-y3
ans=a1*b2-a2*b1
if ans :
	print("NO")
else :
	print("YES")
