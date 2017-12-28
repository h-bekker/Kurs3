def det2(a):
    return a[0][0] * a[1][1] -  a[0][1] * a[1][0]

def LessMatrix(m):
	m1, m2, m3, m4 = [], [], [], []
	ans = []
	for i in range(len(m)-1):
		arr = []
		for j in range(len(m)-1):
			ind = []
			for k in (0,j+1):
				ind.append(m[k][0:1] + m[k][i+1:i+2]) #в ind формируются матрицы размера 2х2, определители которых являются элементами матрицы размера (n-1)x(n-1)
			arr.append(det2(ind)) #arr - строка, элементы которого определители размера 2х2 
		ans.append(arr)
	return ans

first = eval(input())
matrix = []
matrix.append(first)
for i in range(len(first)-1) : #считывание матрицы
	elems = eval(input())
	matrix.append(elems)
initSize = len(matrix)
counter = 2
newMatrix = matrix
divider = 1
sign = 0
while len(newMatrix)>1: #процесс конденсаций
	run = 1
	while newMatrix[0][0] == 0 :
		newMatrix[0], newMatrix[run] = newMatrix[run], newMatrix[0]
		sign += 1
		run += 1
	divider *= newMatrix[0][0]**(initSize-counter)
	newMatrix = LessMatrix(newMatrix)
	counter +=1
	#print(newMatrix)
ans = newMatrix[0][0]
ans = ans * (-1)**sign
print(ans//divider)
