import dudraw

dudraw.set_canvas_size(500,600)
dudraw.clear(dudraw.WHITE)
dudraw.set_pen_color(dudraw.BLACK)


def draw_grid():
    x = 0
    y = 0
    for i in range(12):
        dudraw.line(0,y,1,y)
        y += 1/12
    for i in range (10):
        dudraw.line(x,0,x,1)
        x += 1/10
     
draw_grid()

grid = []
for row in range (12):
    new_row = []
    for col in range (10):
        new_row.append(0)
    grid.append(new_row)

print(grid)

dudraw.show(float('inf'))