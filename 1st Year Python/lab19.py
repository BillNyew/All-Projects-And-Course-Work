import dudraw

def draw_circles( x, y, r, n):
  if n == 0:
    return
  dudraw.circle(x,y,r)
  
  draw_circles(x-r, 0.5, r/2, n-1)
  draw_circles(x+r, 0.5, r/2, n-1)
  draw_circles(0.5, x-r, r/2, n-1)
  draw_circles(0.5, x+r, r/2, n-1)
dudraw.show(100)

draw_circles(0.5, 0.5, 0.2, 10)

dudraw.show(float('inf'))
'''from math import cos, sin, radians
import dudraw

def end_point(start_x: float, start_y: float, length: float, angle: float) -> tuple:
    end_x = start_x + length * cos(radians(angle))
    end_y = start_y + length * sin(radians(angle))
    return (end_x, end_y)

def recursive_line(x: float, y: float, length: float, angle: float, depth: int):
    if depth == 0:
        return
    end = end_point(x, y, length, angle)
    dudraw.line(x, y, end[0], end[1])
    recursive_line(end[0], end[1], length/2, angle+45, depth-1)
    recursive_line(end[0], end[1], length/2, angle-45, depth-1)

# set up canvas and initial starting point
dudraw.set_canvas_size(600,600)

# call recursive function to draw lines
recursive_line(0.5, 0.5, 0.25, 90, 6)

# show the final result
dudraw.show(float('inf'))'''