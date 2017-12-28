class Dots:
	def __init__(self, bord1, bord2):
		self.bord1 = bord1
		self.bord2 = bord2
	def __getitem__(self, value):
		if type(value) == type(123):
			ans = []
			size = (self.bord2 - self.bord1) / (value - 1)
			for elem in range(value):
				ans.append(self.bord1 + (size*elem))
			return tuple(ans)
		tmp = slice(5)
		if type(value) == type(tmp):
			if value.step == None:
				size = (self.bord2 - self.bord1) / (value.stop - 1)
				return self.bord1 + size*value.start
			else:
				ans = []
				size = (self.bord2 - self.bord1) / (value.step - 1)
				if value.start == None:
					if value.stop == None:
						for elem in range(value.step):
							ans.append(self.bord1 + (elem*size))
					else:
						for elem in range(value.stop):
							ans.append(self.bord1 + (elem*size))
				elif value.stop == None:
					for elem in range(value.start, value.step):
						ans.append(self.bord1 + (elem*size))
				else:
					for elem in range(value.start, value.stop):
						ans.append(self.bord1 + (elem*size))
			return tuple(ans)
