seq = input()
l = seq.split()
for ind,elem in enumerate(l):
	l[ind] = l[ind].title()
d = {elem: 0 for elem in l}
for elem in l:
	tmp = d.get(elem)
	d.update({elem : tmp+1})
l = d.values()
numb = ans = 0
for elem in l:
	if elem > numb:
		numb = elem
		ans = 1
	elif elem == numb:
		ans += 1
print(ans)
