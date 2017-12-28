s = input()
l = s.split()
for k in range(3):
	l[k] = float(l[k])
bigl = []
bigl.append(l)
while len(l) != 1:
	s = input()
	l = s.split()
	if len(l) != 1:
		for k in range(3):
			l[k] = float(l[k])
		bigl.append(l)
ans = -1
ans1 = ''
ans2 = ''
leng = len(bigl)
for ind1 in range(leng):
	for ind2 in range(ind1, leng):
		dist = (bigl[ind1][0] - bigl[ind2][0]) ** 2 + (bigl[ind1][1] - bigl[ind2][1]) ** 2 + (bigl[ind1][2] - bigl[ind2][2]) ** 2
		if ans < dist:
			ans = dist
			ans1 = bigl[ind1][3]
			ans2 = bigl[ind2][3]
if ans1 < ans2:
	print(ans1,ans2)
else:
	print(ans2,ans1)
