seq = eval(input())
seq = set(seq)
maxelem = max(seq)
exp1 = int(maxelem ** 0.5) + 1
ansset = set()
for m in range(1, exp1):
	tmp1 = m ** 2
	exp2 = int((maxelem - m*m) ** 0.5) + 1
	for n in range(m, exp2):
		tmp2 = tmp1 + n ** 2
		exp3 = int((maxelem - m*m - n*n) ** 0.5) + 1
		for k in range(n, exp3):
			tmp3 = tmp2 + k ** 2
			ansset.add(tmp3)
ansset.intersection_update(seq)
print(len(ansset))
