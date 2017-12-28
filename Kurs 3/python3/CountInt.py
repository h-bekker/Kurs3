obj = eval(input())
ans = 0
for elem in dir(obj):
	if type(eval("obj.{}".format(elem))) == type(123):
		ans += 1
print(ans)
