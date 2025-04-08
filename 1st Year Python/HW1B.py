import dudraw
dudraw.set_canvas_size(400,400)
dudraw.set_x_scale(0, 4)
dudraw.set_y_scale(0, 4)
dudraw.clear(dudraw.LIGHT_GRAY)
dudraw.set_pen_color(dudraw.WHITE)
for row in range(4):
  for column in range(4-row):
    dudraw.filled_circle(column+0.5, row+0.5, 0.5)
dudraw.show(1000)
dudraw.show(float('inf'))