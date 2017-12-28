inp = "str"
first_elem = True
flag = True
l = []
while inp != "":
	inp = input()
	l = inp.split()
	for elem in l:
		if elem[0] == '-':
			flag = False
			elem = elem[1::1]
		if elem.isdecimal() == True:
			if flag == False:
				elem = '-' + elem
				flag = True
			if first_elem:
				ans = int(elem)
				first_elem = False
			elif int(elem) > int(ans):
				ans = elem
		else:
			flag = True
print(ans)
