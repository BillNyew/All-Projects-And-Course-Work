"""
 Filename: bouncing_circle.py
 Author: Bill Turbadrakh
 Date: January 2023
 Course: COMP 1352
 Assignment: animation demo, to be modified to use classes
 Collaborators: None
 Internet Source: None
"""
from random import random
from random import randint
import dudraw
from dudraw import Color
import math
# main code block:
dudraw.set_canvas_size(400,400)
class BouncingCircle:
    def __init__(self,x_pos,y_pos,x_vel,y_vel,r,color):
        self.x_pos = x_pos
        self.y_pos = y_pos
        self.x_vel = x_vel
        self.y_vel = y_vel
        self.r = r
        self.color = Color(randint(0,255),randint(0,255),randint(0,255))
    def move(self):
        self.x_pos += self.x_vel
        self.y_pos += self.y_vel
        if (self.x_pos > 1 - self.r and self.x_vel > 0 or self.x_pos < self.r and self.x_vel < 0):
            self.x_vel *= -1
        if (self.y_pos > 1-self.r and self.y_vel > 0 or self.y_pos < self.r and self.y_vel < 0):
            self.y_vel *= -1
    def draw(self):
        dudraw.set_pen_color(self.color)
        dudraw.filled_circle(self.x_pos, self.y_pos, self.r)
        dudraw.set_pen_color(dudraw.BLACK)
        # dudraw.set_pen_width(0.001)
        dudraw.circle(self.x_pos, self.y_pos, self.r)
    def overlap(self,BouncingCircle):
        distance = math.sqrt((BouncingCircle.x_pos - self.x_pos)**2 + (BouncingCircle.y_pos - self.y_pos)**2)
        if distance <= self.r + BouncingCircle.r:
            return True
        else:
            return False
circles=[]
for i in range(6):
    circles.append(BouncingCircle(random(), random(), random()*0.05, random()*0.05, 0.06))
key = ''
while key != 'q':
   dudraw.clear(dudraw.LIGHT_GRAY)
   for circle in circles:
    circle.draw()
    circle.move()
    if circle.overlap(circle) == True:
        dudraw.set_pen_color(dudraw.BLACK)
        dudraw.set_pen_width(0.01)
        dudraw.set_font_size(100)
        dudraw.text(0.5,0.5,"CRASH!")
        dudraw.show(10)
    elif circles.overlap(circles) == False:
        dudraw.set_pen_width(0.001)
    dudraw.clear(dudraw.LIGHT_GRAY)
    circle.draw()
    circles.overlap(circles)
    if dudraw.has_next_key_typed():
        key = dudraw.next_key_typed()
    dudraw.show(50)