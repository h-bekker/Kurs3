class Stroka(str):
	def __neg__(self):
		return self[-1::-1]
	def __mul__(self,other):
		if type(other) == type(123):
			return str.__mul__(self,other)
		ans = Stroka()
		for elem1 in self:
			for elem2 in other:
				ans += elem1
				ans += elem2
		ans = Stroka(ans)
		return ans
	def __pow__(self,other):
		tmp = self
		for n in range(other-1):
			tmp = tmp*self
		return tmp
