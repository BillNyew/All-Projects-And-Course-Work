import dudraw
from pprint import pprint

dudraw.set_canvas_size(500,600)
dudraw.clear(dudraw.WHITE)
dudraw.set_pen_color(dudraw.BLACK)
dudraw.set_x_scale(0,10)
dudraw.set_y_scale(0,12)



grid = []
for row in range (12):
    new_row = []
    for col in range (10):
        new_row.append(0)
    grid.append(new_row)

while True:
    dudraw.clear()
    def draw_grid():
      x = 0
      y = 0
      for i in range(12):
         dudraw.line(0,y,10,y)
         y += 1
      for i in range (10):
         dudraw.line(x,0,x,12)
         x += 1
    draw_grid()

    for row in range(len(grid)):
        for col in range(len(grid[row])):
            dudraw.text(col + 0.5, row + 0.5, str(grid[row][col]))

    if dudraw.mouse_pressed():
        mx = dudraw.mouse_x()
        my = dudraw.mouse_y()
        grid[int(my)][int(mx)] += 1

    if dudraw.has_next_key_typed():
        if dudraw.next_key_typed() == 'q' or dudraw.next_key_typed() == 'Q':
            break
    

    dudraw.show()