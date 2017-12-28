class Desc:
	var = 0
	def __set__(self, obj, val):
		raise ValueError
	def __get__(self, obj, cls):
		if Desc.var == 0:
			Desc.var = obj
			return None
		else:
			return Desc.var
	def __delete__(self,obj):
		if Desc.var == obj:
			Desc.var = 0

class Sem:
	lock = Desc()
	def __init__(self, name):
		self.name = name
	def __str__(self):
		return "<{}>".format(self.name)

