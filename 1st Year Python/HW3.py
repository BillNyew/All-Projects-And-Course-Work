class Driver():
    def __init__(self, n:str, r:Route=None):
        self.name = n
        self.route = r
    def __str__(self)->str:
        return f"{self.name}, {self.route}"
class Route():
    def __init__(self, s1:str, s2:str):
        self.stop1 = s1
        self.stop2 = s2
    def __str__(self)->str:
        return str(self.stop1) + "->" + str(self.stop2)
print('------lines 24 and 25------')
route_1 = Route('Bank', 'Bar')
phyllis = Driver('Phyllis', route_1)
bob = phyllis
bob.name = 'Bob'
bob.route.stop2 = 'Grocery'
print(phyllis.name)
print(phyllis.route.stop2)
print('------lines 30 and 31------')
fred = copy.copy(bob)
fred.name = 'Fred'
fred.route.stop1 = 'Pharmacy'
print(bob.name)
print(bob.route.stop1)
print('------lines 37 and 38------')
ethel = Driver("Ethel", Route('Gym', 'Work'))
marge = copy.deepcopy(ethel)
marge.name  = "Marge"
marge.route.stop1 = 'School'
print(ethel.name)
print(ethel.route.stop1)



def foo(n: int)->None:
    if n == 0:
        print("Done")
    else:
        print(f"In function foo: {n}")
        foo(n-1)
        print(f"Continuing function foo: {n}")
foo(3)