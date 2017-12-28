class Triangle:
	def __init__(self, k1, k2, k3):
		self.k1 = k1
		self.k2 = k2
		self.k3 = k3
	def __repr__(self):
		return "{:.1f}:{:.1f}:{:.1f}".format(self.k1, self.k2, self.k3)
	def __ge__(self, other):
		if abs(self) >= abs(other):
			return True;
		else:
			return False;
	def __gt__(self, other):
		if abs(self) > abs(other):
			return True;
		else:
			return False;
	def __eq__(self, other):
		if abs(self) == abs(other):
			return True;
		else:
			return False;
	def __bool__(self):
		if self.k1 >= self.k2+self.k3 or self.k2 >= self.k1+self.k3 or self.k3 >= self.k1+self.k2 or self.k1 < 0 or self.k2 < 0 or self.k3 < 0:
			return False;
		else:
			return True;

def abs(t):
	if not t:
		return 0
	else:
		per = (t.k1 + t.k2 + t.k3) / 2
		return (per * (per-t.k1) * (per-t.k2) * (per-t.k3)) ** 0.5
