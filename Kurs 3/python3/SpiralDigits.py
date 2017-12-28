def SpecPrint(l):
	print(*l)

m,n = eval(input())
ans = []
for i in range(n):
	ans.append([])
	for j in range(m):
		ans[i].append(-1)
line = [[0,1],[1,0],[0,-1],[-1,0]] #Направления
ind = 0
route = line[ind] #Текущее направление
count=x=y=0
for i in range(m*n):
	count = count % 10
	ans[x][y] = count
	tmp1,tmp2 = x,y
	tmp1 += route[0] #Для проверки следующей клетки по этому направлению 
	tmp2 += route[1]
	if tmp1 == n or tmp2 == m or ans[tmp1][tmp2] != -1 : #Если граница или уже отмечен
		ind = (ind+1) % 4
		route = line[ind]
		x = x + route[0]
		y = y + route[1]
	else :
		x = tmp1
		y = tmp2	
	count+=1
for i in ans:
	SpecPrint(i)
