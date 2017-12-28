s = input()
l = s.split()
bigl = []
bigl += l
while len(l) == 2:
	s = input()
	l = s.split()
	bigl += l
s = input()
s1 = set()
s2 = set()
s1.add(l[len(l)-1])
s2.add(s)
l = []
for k in range(len(bigl) // 2):
	if bigl[k*2] in s1 or bigl[k*2+1] in s1:
		s1.add(bigl[k*2])
		s1.add(bigl[k*2+1])
	if bigl[k*2] in s2 or bigl[k*2+1] in s2:
		s2.add(bigl[k*2])
		s2.add(bigl[k*2+1])
	if bigl[k*2] not in s1 and bigl[k*2] not in s2 and bigl[k*2+1] not in s1 and bigl[k*2+1] not in s2:
		l.append(bigl[k*2])
		l.append(bigl[k*2+1])
for k in range(len(l) // 2):
	if l[k*2] in s1 or l[k*2+1] in s1:
		s1.add(l[k*2])
		s1.add(l[k*2+1])
	if l[k*2] in s2 or l[k*2+1] in s2:
		s2.add(l[k*2])
		s2.add(l[k*2+1])
if s1.isdisjoint(s2):
	print("NO")
else:
	print("YES")
