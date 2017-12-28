v=eval(input())
m,n=eval(input())
ans=[]
l=list(v)
for i in range(len(l)) :
	if l[i] % n != 0 and i % m != 0:
		ans.append(l[i])
print(ans)
