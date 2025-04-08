import comp
from random import random
comp.set_canvas_size(800,400)
# set a scale according to pixels
comp.set_x_scale(0,800)
comp.set_y_scale(0,400)
# make 2000 randomly-placed circles:
for i in range(4000):
    x_position = random()*800
    y_position = random()*400
    if x_position<300:
        comp.set_pen_color_rgb(1,53,15) # Dark green
    elif y_position<200:
        comp.set_pen_color_rgb(191,10,48) # blood red
    elif y_position:
        comp.set_pen_color(comp.YELLOW)
 
 
    comp.filled_circle(x_position, y_position, 10)
    comp.show(10)
comp.show(float('inf'))