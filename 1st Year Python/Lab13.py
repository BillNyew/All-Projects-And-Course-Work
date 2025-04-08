class Pet:
    def __init__(self, n: str = 'Unknown name', a: float = 0):
        self.name = n
        self.age = a
    
    def __str__(self):
        return f'Pet Information:\n\tName: { self.name }\n\tAge: { self.age }'

class Cat(Pet):
    
    def __init__(self, n , a ,c = 'Unknown Color' ):
        Pet.__init__(self, n, a)
        self.color= c
    def __str__(self):
        Pet.__str__(self)
        return f'Pet Information:\n\tName: { self.name }\n\tAge: { self.age }'+ f'\n\tColor: {self.color}'

  
class Dog(Pet):
    def __init__(self, n , a ,b = 'Unknown Breed' ):
        Pet.__init__(self, n, a)
        self.breed= b
    def __str__(self):
        Pet.__str__(self)
        return f'Pet Information:\n\tName: { self.name }\n\tAge: { self.age }'+ f'\n\tBreed: {self.breed}'              
      
bill= Cat('Bill', 22, 'Orange') 
snoopy =Dog('Snoopy', 72, 'Beagle')
     
print(bill)
print(snoopy)



