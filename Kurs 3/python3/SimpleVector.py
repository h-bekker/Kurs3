class Vector:
	def __init__(self, n1, n2, n3):
		self.n1 = n1
		self.n2 = n2
		self.n3 = n3
	def __repr__(self):
		return "{:.2f}:{:.2f}:{:.2f}".format(self.n1/1, self.n2, self.n3)
	def __add__(self, other):
		return Vector(self.n1 + other.n1, self.n2 + other.n2, self.n3 + other.n3)
	def __sub__(self, other):
		return Vector(self.n1 - other.n1, self.n2 - other.n2, self.n3 - other.n3)
	def __mul__(self, numb):
		return Vector(self.n1 * numb, self.n2 * numb, self.n3 * numb)
	def __rmul__(self, numb):
		return Vector(self.n1 * numb, self.n2 * numb, self.n3 * numb)
	def __truediv__(self, numb):
		return Vector(self.n1 / numb, self.n2 / numb, self.n3 / numb)
	def __matmul__(self,other):
		return self.n1 * other.n1 + self.n2 * other.n2 + self.n3 * other.n3
