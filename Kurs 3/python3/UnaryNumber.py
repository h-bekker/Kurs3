class Unary:
	def __init__(self, s):
		self.s = str()
		for elem in s:
			self.s += '|'
		self.it = 0
	def __repr__(self):
		return "{}".format(self.s)
	def __str__(self):
		return self.s
	def __len__(self):
		return len(self.s)
	def __ior__(self,other):
		self.s += other.s
		return self
	def __invert__(self):
		self.s = self.s[:len(self.s)//2]
		return self
	def __pos__(self):
		self.s += '|'
		return self
	def __iter__(self):
		return self
	def __next__(self):
		if self.it < len(self.s):
			self.it += 1
			return Unary("|")
		else:
			raise StopIteration
