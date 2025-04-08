def mystery(n):
    if n==0:
        print('leaf')
        return 1
    elif n>0:
        print('slipt')
        return mystery(n//2)+mystery(n//2)
mystery(2)
'''def foo(n: int)->None:
    if n == 0:
        print("foo", n)
    elif n == 1:
        print("boo", n)
    else:
        print("before", n)
        foo(n-1)
        print("after", n)
foo(4)
class PhoneLine:
    plan_cost=0
    members=0
    def __init__(self):
        self.minutes=100
        PhoneLine.members+=1
        if PhoneLine.members==1:
            PhoneLine.plan_cost+=60
        else:
            PhoneLine.plan_cost+=30
    def call(self, minutes):
        while minutes>self.minutes:
            self.minutes+=100
            PhoneLine.plan_cost+=20
        self.minutes-=minutes
    def __str__(self):
        return f'minutes:{self.minutes}, total_plan:{PhoneLine.plan_cost}'
    
Mohammed=PhoneLine()
Andrew=PhoneLine()
Mohammed.call(40)
Andrew.call(60)
print(Mohammed)
Andrew.call(70)
print(Andrew)
temp=0
for row in nums:
    for num in row:
        if():
            ()
print(temp)
import copy
class Student:
    def __init__(self, n , g):
        self.name=n
        self.gpa=g
class Course:
    def __init__(self, name:str):
        self.roster = []
        self.course_name=name

    def add_student(self, student):
        self.roster.append(student)
t= Student("TK", 3.5)
j= Student("JB", 3.7)
c1= Course("CS")
c2= c1
c2.add_student(t)
c3= copy.copy(c1)
c4= copy.deepcopy(c1)

c3.add_student(j)
c3.course_name = "CS1352"
c1.course_name = "CS2300"

print(c1.course_name)
print(c2.course_name)
print(c3.course_name)
print(c4.course_name)
print(c1.roster[-1].name)
print(c2.roster[-1].name)
print(c3.roster[-1].name)
print(c4.roster[-1].name)'''

            
