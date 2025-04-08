"""
    Filename: project5.py
    Author: Bill Turbadrakh
    Date: 2/16/2023
    Course: COMP_1352
    Assignment: Project5(Conga Line)
    Collaborators: None
    Internet Source: None
"""
from dudraw import dudraw, Color
from random import random, randint

dudraw.set_pen_color(dudraw.BLACK)
dudraw.set_x_scale(0,100)
dudraw.set_y_scale(0,100)
dudraw.set_canvas_size(600,600)


class Conga_Dancer:
    def __init__(self,x_position = 50, y_position = 50, targ_x = 50 , targ_y = 50):
        self.x_post = x_position
        self.y_post = y_position
        self.target_x = targ_x
        self.target_y = targ_y
        self.color = Color(randint(0,255),randint(0,255),randint(0,255))
    def __str__(self):
        return f"x:{self.x_post} y:{self.y_post} targ_x:{self.target_x} targ_y:{self.target_y}"
    def draw(self):
        dudraw.set_pen_color(self.color)
        dudraw.filled_circle(self.x_post,self.y_post,1)
    def move(self):
        self.x_post += 0.1*(self.target_x - self.x_post)
        self.y_post += 0.1*(self.target_y - self.y_post)
    def set_target(self,targ_x,targ_y):
        self.target_x = targ_x
        self.target_y = targ_y

dancers = [Conga_Dancer (randint(0,100),randint(0,100),50,50) for i in range(2)]
letter = ''

while letter != 'q':
    dudraw.clear(dudraw.WHITE)

    for i in range(len(dancers)):
        dancers[i].draw()
        dancers[i].move()

        if i == 0:
            dancers[i].set_target(dudraw.mouse_x(), dudraw.mouse_y())

        else:
            dancers[i].set_target(dancers[i-1].x_post, dancers[i-1].y_post)

    if dudraw.has_next_key_typed():
        letter = dudraw.next_key_typed()

        if letter == 'n':
            dancers.append(Conga_Dancer(randint(0,100),randint(0,100),50,50))

    dudraw.show(25)