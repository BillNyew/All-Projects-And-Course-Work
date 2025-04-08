"""
 Filename: Project3Part2.py
 Author: Bill Turbadrakh
 Date: Febuary 2nd, 2023
 Course: COMP 1352
 Assignment: Project 3, Sand Project Part 2
 Collaborators: None
 Internet Source: None
"""
import dudraw
import random
dudraw.set_canvas_size(600,600)
dudraw.set_x_scale(0,100)
dudraw.set_y_scale(0,100)
key = ''
world = []
def create_world():
    for i in range(101):
        row = []
        for j in range(101):
            row.append(0)
        world.append(row)
create_world()
def draw_world():
    for i in range(95):
        for j in range(100):
            if world[i][j] == 1:
                dudraw.set_pen_color_rgb(222,184,160)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
            elif world[i][j] == 2:
                dudraw.set_pen_color(dudraw.GRAY)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
            elif world[i][j] == 3:
                dudraw.set_pen_color(dudraw.BOOK_LIGHT_BLUE)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
            else:
                dudraw.set_pen_color(dudraw.WHITE)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
def place_sand():
    if dudraw.mouse_is_pressed():
        mouse_x = int(dudraw.mouse_x())
        mouse_y = int(dudraw.mouse_y())
        if mouse_y <= 95:
            random1 = random.randint(-2,2)
            random2 = random.randint(-2,2)
            if mouse_x + random2 < 100 and mouse_x + random2 > -1 and mouse_y + random1 > -1:
                world[mouse_y + random1][mouse_x + random2] = 1
def place_floor():
    if dudraw.mouse_is_pressed():
        mouse_x = int(dudraw.mouse_x())
        mouse_y = int(dudraw.mouse_y())
        if mouse_y <= 95:
            world[mouse_y][mouse_x] = 2
def place_water():
    if dudraw.mouse_is_pressed():
        mouse_x = int(dudraw.mouse_x())
        mouse_y = int(dudraw.mouse_y())
        if mouse_y <= 95:
            random1 = random.randint(-2,2)
            random2 = random.randint(-2,2)
            if mouse_x + random2 < 100 and mouse_x + random2 > -1 and mouse_y + random1 > -1:
                world[mouse_y][mouse_x] = 3
def advance_world():
    for i in range(101):
        for j in range(101):
            if i != 0 and world[i][j] == 1:
                if world[i-1][j] == 0 or world[i-1][j] == 3:
                    world[i][j] = 0
                    world[i-1][j] = 1
                elif (world[i-1][j-1] == 0 or world[i-1][j] == 3) and world[i-1][j] != 2 and j-1 > -1:
                    world[i-1][j-1] = 1
                    world[i][j] = 0
                elif (world[i-1][j+1] == 0 or world[i-1][j] == 3) and world[i-1][j] != 2 and j+1 < 100:
                    world[i-1][j+1] = 1
                    world[i][j] = 0
            if i != 0 and world[i][j] == 3:
                if j-1 > -1 and j+1 < 100:
                    if world[i-1][j] == 0:
                        world[i-1][j] = 3
                        world[i][j] = 0
                    elif world[i-1][j-1] == 0 and world[i-1][j] != 2 and j-1 > -1:
                        world[i-1][j-1] = 3
                        world[i][j] = 0
                    elif world[i-1][j+1] == 0 and world[i-1][j] != 2 and j+1 < 100:
                        world[i-1][j+1] = 3
                        world[i][j] = 0
    draw_world()
while key != 'q':
    if key == '':
        dudraw.set_pen_color(dudraw.BLACK)
        dudraw.text(25,98,"Press S for sand, F for floor, W for water, or Q to quit.")
    elif key == 's':
        place_sand()
    elif key == 'f':
        place_floor()
    elif key == 'w':
        place_water()
    advance_world()
    dudraw.show(2)
    if dudraw.has_next_key_typed():
        key = dudraw.next_key_typed()