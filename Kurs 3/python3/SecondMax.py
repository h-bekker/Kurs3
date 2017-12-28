a=eval(input())
if len(a)==1 :
	print("NO")
else :
	firstmax = a[0]
	for k in a :
		if k>firstmax :
			firstmax = k
	ans = firstmax
	for k in a :
		if k<firstmax :
			ans = k
			break;
	if ans==firstmax :
		print("NO")
	else :
		for k in a :
			if k<firstmax and k > ans :
				ans = k
if ans!=firstmax :
	print(ans)
