"""

File Name: turbadrakh_project4_animation.py
Author:Bill Turbadrakh
Date:10/9/2022
Course:COMP 1351-6
Assignment:Project 4
Internet Source:

"""

import dudraw
import random
dudraw.set_canvas_size(500,500)

radius=0.1
x_center = 2*radius
y_center = radius
x_velocity = 0.01
y_velocity= 0.01
x_value=random
y_value=random

while True:
    dudraw.clear(dudraw.WHITE)
    dudraw.filled_circle(x_center, y_center, radius)
    dudraw.set_pen_color_rgb(random.randint(0,255),random.randint(0,255),random.randint(0,255))
    dudraw.show(50)
    x_center = x_center + x_velocity
    y_center = y_center + y_velocity
    if x_center + radius > 1:
        x_velocity = -x_velocity
    if y_center + radius > 1:
        y_velocity = -y_velocity
    if x_center + radius < 0.2:
        x_velocity = -x_velocity
    if y_center + radius < 0.2:
        y_velocity = -y_velocity
    if dudraw.mouse_pressed(): 
        dudraw.filled_circle(dudraw.mouse_x(), dudraw.mouse_y(), 0.05) 
    dudraw.show(500) 
    
        



