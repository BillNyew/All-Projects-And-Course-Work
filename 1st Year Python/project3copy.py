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
                dudraw.set_pen_color_rgb(222,184,135)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
            elif world[i][j] == 2:
                dudraw.set_pen_color(dudraw.BLACK)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
            else:
                dudraw.set_pen_color(dudraw.GRAY)
                dudraw.filled_square(j+0.5,i+0.5,0.5)
def place_sand():
    dudraw.set_pen_color(dudraw.GRAY)
    dudraw.filled_rectangle(15,97.5,15,5)
    dudraw.filled_rectangle(85,97.5,15,5)
    dudraw.set_pen_color(dudraw.BLACK)
    dudraw.text(50,97.5,"Sand Mode")
    if dudraw.mouse_is_pressed():
        mouse_x = int(dudraw.mouse_x())
        mouse_y = int(dudraw.mouse_y())
        if mouse_y <= 95:
            random1 = random.randint(-2,2)
            random2 = random.randint(-2,2)
            if mouse_x + random2 < 101 and mouse_x + random2 > -1 and mouse_y + random1 > -1:
                world[mouse_y + random1][mouse_x + random2] = 1
def place_floor():
    dudraw.set_pen_color(dudraw.GRAY)
    dudraw.filled_rectangle(50,97,15,5)
    dudraw.filled_rectangle(15,97,15,5)
    dudraw.set_pen_color(dudraw.BLACK)
    dudraw.text(85,97.5,"Floor Mode")
    if dudraw.mouse_is_pressed():
        mouse_x = int(dudraw.mouse_x())
        mouse_y = int(dudraw.mouse_y())
        if mouse_y <= 95:
            world[mouse_y][mouse_x] = 2
def advance_world():
    for i in range(101):
        for j in range(101):
            if i != 0 and world[i][j] == 1:
                if world[i-1][j] == 0:
                    world[i][j] = 0
                    world[i-1][j] = 1
    draw_world()
while key != 'q':
    if key == '':
        dudraw.set_pen_color(dudraw.BLACK)
        dudraw.text(15,97.5,"Press s for sand mode and f for floor mode.")
    elif key == 's':
        place_sand()
    elif key == 'f':
        place_floor()
    advance_world()
    dudraw.show(1)
    if dudraw.has_next_key_typed():
        key = dudraw.next_key_typed()