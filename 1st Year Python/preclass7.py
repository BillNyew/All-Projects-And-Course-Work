class PhonePlan:
    def __init__(self, nums_mins=0, num_messages=0,):
        self.nums_mins = 0
        self.num_messages = 0  
    def print_plan(self):
        print(f'Mins: {self.num_mins}', end=' ')
        print(f'Messages: {self.num_messages}')


my_plan = PhonePlan(input())
dads_plan = PhonePlan()
moms_plan = PhonePlan(input())

print('My plan...', end=' ')
my_plan.print_plan()

print('Dad\'s plan...', end=' ')
dads_plan.print_plan()

print('Mom\'s plan...', end= ' ')
moms_plan.print_plan()