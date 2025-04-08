#program draws 4 wagons, one of which has random values
import dudraw
from random import random
def draw_wagon(x:float, y:float, w:float, h:float)->None:
    
    x_position = x
    y_position = y
    height = h
    width = w
    dudraw.set_pen_color_rgb(255,0,0)             # red
    dudraw.filled_rectangle(x_position + width * 0.5, y_position + height * 0.5, width * 0.45, height *0.4)  # body of wagon
    dudraw.set_pen_color_rgb(255,255,255)         # white for wheels
    dudraw.filled_ellipse(x_position + width * 0.25, y_position + height * 0.1, width * 0.1, height * 0.1)    # left wheel
    dudraw.filled_ellipse(x_position + width * 0.75, y_position + height * 0.1, width * 0.1, height * 0.1);    # right wheel
# main program starts here
dudraw.set_canvas_size()
dudraw.clear(dudraw.BOOK_LIGHT_BLUE)

for x in "draw_wagon":
    print(draw_wagon(0.0,0.9,0.1,0.1))
    print(draw_wagon(0.1,0.8,0.1,0.1))
    print(draw_wagon(0.2,0.7,0.1,0.1))
    print(draw_wagon(0.3,0.6,0.1,0.1))
    print(draw_wagon(0.4,0.5,0.1,0.1))
    print(draw_wagon(0.5,0.4,0.1,0.1))
    print(draw_wagon(0.6,0.3,0.1,0.1))
    print(draw_wagon(0.7,0.2,0.1,0.1))
    print(draw_wagon(0.8,0.1,0.1,0.1))
    print(draw_wagon(0.9,0,0.1,0.1))










dudraw.show(float('inf'))
