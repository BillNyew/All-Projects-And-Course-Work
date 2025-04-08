import dudraw

dudraw.set_canvas_size(500,500)
dudraw.clear(dudraw.LIGHT_GRAY)
def draw_car(x: float, y: float, w: float, h: float)->None:
    """
    Draw a little blue VW beetle car. (x,y) is the lower left-hand
    corner, while w and h give the width and height of the car.
    """
    dudraw.set_pen_color_rgb(142,199,217) # blue body of car
    dudraw.filled_elliptical_sector(x+w/2, y+h*0.1, w/2, h*0.6, 0, 180)
    dudraw.filled_elliptical_sector(x+w/2, y+h*0.5, w/3, h*0.5, 0, 180)
    dudraw.set_pen_color(dudraw.WHITE)
    dudraw.filled_elliptical_sector(x+w*0.55, y+h*0.58, w*0.25, h*0.35, 0, 90 )
    dudraw.set_pen_color(dudraw.DARK_GRAY) # dark gray outline for the car window
    dudraw.elliptical_sector(x+w*0.55, y+h*0.58, w*0.25, h*0.35, 0, 90 )
    dudraw.set_pen_color(dudraw.WHITE) # white for the wheels
    dudraw.filled_ellipse(x+w*0.15, y+h*0.1, w*0.1, h*0.1)
    dudraw.filled_ellipse(x+w*0.85, y+h*0.1, w*0.1, h*0.1)
    dudraw.set_pen_color(dudraw.BLACK) # black outline of wheels
    dudraw.ellipse(x+w*0.15, y + h*0.1, w*0.1, h*0.1)
    dudraw.ellipse(x+w*0.85, y + h*0.1, w*0.1, h*0.1)
    draw_car(1,0)
    for i in range(8):
        draw_car(0.5,0.5,0.5)
       
dudraw.show(100000)
