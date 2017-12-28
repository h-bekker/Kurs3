d = dict()
txt = 'abr'
while(txt != ''):
	flag = 0
	try:
		txt = input()
		if txt[0] != '#':
			expr = txt.split('=')
			if len(expr) > 2:
				flag = 1
				raise Exception	
			if len(expr) == 2 and expr[0][0].isdecimal():
				flag = 2
				raise Exception
			if len(expr) == 2:
				var = expr[0]
				globals()[var] = eval(expr[1])
				d1 = {expr[0]:globals()[var]}
				d.update(d1)
			else:
				print(eval(txt,d))
	except Exception as E:
		if txt != '':
			if flag == 1:
				print("invalid assignment"+" '"+txt+"'")
				flag = 0
			elif flag == 2:
				print("invalid identifier"+" '"+expr[0]+"'")
				flag = 0
			else:
				print(E)
