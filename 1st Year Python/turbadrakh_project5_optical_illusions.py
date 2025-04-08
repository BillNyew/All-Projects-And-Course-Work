
'''File Name: turbadrakh _project5_optical_illusions.py
Author:Bill Turbadrakh
Date:10/14/2022
Course:COMP 1351-6
Assignment:Project 4
Internet Source:'''


import dudraw
# Set up canvas
dudraw.set_canvas_size(500,500)
dudraw.clear(dudraw.DARK_GRAY)
dudraw.set_x_scale(0,9)
dudraw.set_y_scale(0,9)
# vertical lines
for i in range(0,10):
    #sets color and pen width
    dudraw.set_pen_color(dudraw.GRAY)
    dudraw.set_pen_width(0.15)
    # draws line
    dudraw.line(i, 0, i, 9)
    # horizontal lines
    for i in range(0,10):
        #sets color and pen width
        dudraw.set_pen_color(dudraw.GRAY)
        dudraw.set_pen_width(0.15)
        #draws line
        dudraw.line(0, i, 9, i)
        # loop for circles
        for i in range(1,9):
            #loop to change x
            x = i
            #loops to make circles
            for i in range(1,9):
                dudraw.set_pen_color(dudraw.WHITE)
                dudraw.filled_circle(x,i,0.1)
#this will show for infinity the canvas
dudraw.show(float('inf'))







