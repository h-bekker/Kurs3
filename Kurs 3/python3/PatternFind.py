s = input()
templ = input()
k = 0
kol = 0
ans = -1
leng = len(templ)
indt = 0
while k < len(s):
	if (s[k] == templ[indt]):
		kol = 0
		indt += 1
		leng -= 1
		if leng == 0:
			ans = k - len(templ) + 1
			break
		k += 1
	elif templ[indt] == "@":
		kol += 1
		indt += 1
		leng -= 1
		if leng == 0:
			ans = k - len(templ) + 1
			break
		k += 1
	else:
		leng = len(templ)
		indt = 0
		k = k - kol + 1
		kol = 0
print(ans)
