import comp

#setting size of perameters for picture size
comp.set_canvas_size(400,400)
comp.clear_rgb(100,100,255)

comp.set_pen_color( comp.BOOK_BLUE)
comp.filled_square(1,1,.5)

comp.set_pen_width(0.01)
comp.set_pen_color(comp.BLACK)
comp.triangle(0.5,0,1.01,0.5,1.01,-0.1)

comp.set_pen_width(0.01)
comp.set_pen_color(comp.BLACK)
comp.triangle(1,0,0,1,2,1)

#the duration of show time
comp.show(10000)
