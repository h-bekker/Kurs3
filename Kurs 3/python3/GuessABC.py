class A:
	def __init__(self, val):
		self.val = val
	def __str__(self):
		return "/{}/".format(self.val)
	def __add__(self,other):
		if type(self) == type(A(self.val)):
			tmp = A(self.val)
		else:
			tmp = B(self.val)		
		tmp.val += other.val
		return tmp
	def __radd__(self,other):
		tmp = A(self.val)		
		tmp.val += other.val
		return tmp
	def __rmul__(self,other):
		tmp = B(self.val)		
		tmp.val *= other.val
		return tmp

class B:
	def __init__(self, val):
		self.val = val
	def __str__(self):
		return "|{}|".format(self.val)
	def __radd__(self,other):
		if type(other) == type(A(self.val)):
			tmp = A(self.val)	
		else:
			tmp = B(self.val)		
		tmp.val += other.val
		return tmp
	def __mul__(self,other):
		tmp = B(self.val)		
		tmp.val *= other.val
		return tmp
	def __rmul__(self,other):
		tmp = B(self.val)		
		tmp.val *= other.val
		return tmp

class C(B,A):
	pass
