import math

class Region:
    count = 0
    
    def __init__(self, n: str):
        self.name = n
        Region.count += 1
    
    def area(self) -> float:
        return 0
    
    def __eq__(self, other):
        return math.isclose(self.area(), other.area())
    
    def __lt__(self, other):
        return not(self == other) and self.area() < other.area()
    
    def __gt__(self, other):
        return not(self == other) and self.area() > other.area()

class Rectangle(Region):
    def __init__(self, n: str, l: float, w: float):
        super().__init__(n)
        self.length = l
        self.width = w
    
    def area(self) -> float:
        return self.length * self.width

class RightTriangle(Region):
    def __init__(self, n: str, b: float, h: float):
        super().__init__(n)
        self.base = b
        self.height = h
    
    def area(self) -> float:
        return 0.5 * self.base * self.height
