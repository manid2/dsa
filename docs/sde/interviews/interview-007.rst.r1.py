# Synechron -  Python, SQL - Round 1

# 1 - OOP
class P:
    x = 1
 
class C1(P):
    pass
 
class C2(C1):
    pass
 
class C3(C2):
    x = 1
 
print(P.x, C1.x, C2.x, C3.x)   # 1, 1, 1, 1
 
C3.x = 2
print(P.x, C1.x, C2.x, C3.x)   # 1, 1, 1, 2
 
C1.x = 2
print(P.x, C1.x, C2.x, C3.x)   # 1, 2, 1, 2
 
P.x = 2
print(P.x, C1.x, C2.x, C3.x)   # 2, 2, 1, 2

# 2 - Reverse Linked List
class Node:
	def __init__(self, data):
		data = data
		next

class List:
	def __init__(self, head):
		head = head # Node
		
	def reverse(self):
		h1 = self.head
		curr = h1, prev = None, next = None
				
		while (curr):
			next = curr.next
			curr.next = prev
			prev = curr
			curr = next
		self.head = curr
		return curr
