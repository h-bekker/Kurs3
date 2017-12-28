class Normal:
	def __init__(self, start):
		self.start = start
	def swap(self, other):
		self.start, other.start = other.start, self.start
	def what(self):
		return self.start

class Double:
	def __init__(self, start):
		self.start = start*2
	def swap(self, other):
		self.start, other.start = other.start*2, self.start*2
	def what(self):
		return self.start*2

