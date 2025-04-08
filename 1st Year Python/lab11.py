import dudraw
x1 = .5
y1 = .5
x2 = 0
y2 = 0
for i in range(10):
    dudraw.line(x1, y1, x2, 1)
    dudraw.line(x1, y1, x2, 0)
    x2 += .1
    dudraw.line(x1, y1, 1, y2)
    dudraw.line(x1, y1, 0, y2)
    y2 += .1
    dudraw.show()
dudraw.set_pen_color(dudraw.RED)
dudraw.line(.32, 0, .32, 1)
dudraw.line(.69, 0, .69, 1)
dudraw.show(float('inf'))
 
 
    

    
  
