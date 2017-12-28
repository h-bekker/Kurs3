def PointInCircle(x,y,x0,y0,R) :
  return (x-x0)*(x-x0)+(y-y0)*(y-y0) <= R*R

x,y,r = eval(input())
flag = True
notzero = True
x1,y1 = eval(input())
while x1 != 0 or y1 != 0 :
	if flag :
		flag = PointInCircle(x,y,x1,y1,r)
	x1,y1 = eval(input())
if flag :
	print("YES")
else :
	print("NO")
