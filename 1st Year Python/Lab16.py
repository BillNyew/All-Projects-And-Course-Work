from random import randint
from random import random
from dudraw import Color
import dudraw

####### Bouncing Shape ###############
class BouncingShape:
    def __init__(self, x :float = random(), y:float = random(), xv:float = random()*0.06 - 0.03, yv:float = random()*0.06 - 0.03, s:float = 0.04):
        self.x_pos = x
        self.y_pos = y
        self.x_vel = xv
        self.y_vel = yv
        self.size = s
        self.color = Color(randint(0, 255), randint(0, 255), randint(0, 255))    

    def move(self):
        self.x_pos += self.x_vel
        self.y_pos += self.y_vel 
        if ((self.x_pos + self.size > 1 and self.x_vel > 0) or 
            (self.x_pos - self.size < 0 and self.x_vel < 0)):
            self.x_vel *= -1

        if ((self.y_pos + self.size> 1 and self.y_vel > 0) or
            (self.y_pos -self.size < 0 and self.y_vel < 0)):
            self.y_vel *= -1  

    def draw(self):
        #We don't know how to draw a generic shape so leave this as is
        pass
class BouncingCircle(BouncingShape):
  def __init__(self, x :float = random(), y:float = random(), xv:float = random()*0.06 - 0.03, yv:float = random()*0.06 - 0.03, s:float = 0.04, c = dudraw.set_pen_color(dudraw.BLUE)):
    BouncingShape.__init__ (x = random(), y = random(), xv = random()*0.06 - 0.03, yv = random()*0.06 - 0.03, s = 0.04)
    self.x_pos = x
    self.y_pos = y
    self.x_vel = xv
    self.y_vel = yv
    self.size = s
    self.color= c

    def draw(self):
      dudraw.set_pen_color(self.color)
      dudraw.filled_circle(self.x_pos, self.y_pos)
      dudraw.set_pen_color(dudraw.BLACK)
      dudraw.circle(self.x_pos, self.y_pos)

class WobblyCircle(BouncingCircle):
  def __init__(self, x :float = random(), y:float = random(), xv:float = random()*0.06 - 0.03, yv:float = random()*0.06 - 0.03, s:float = 0.04,c=dudraw.set_pen_color(dudraw.RED) ):
    BouncingShape.__init__ (x = random(), y = random(), xv = random()*0.06 - 0.03, yv = random()*0.06 - 0.03, s= 0.04)
    self.x_pos = x
    self.y_pos = y
    self.x_vel = xv
    self.y_vel = yv
    self.size = s
    self.color = c

    def move(self):
        self.x_pos += self.x_vel
        self.y_pos += self.y_vel

        if ((self.x_pos + self.size> 1 and self.x_vel> 0) or 
            (self.x_pos - self.size < 0 and self.x_vel < 0)):
            self.x_vel *= -1

        if ((self.y_pos + self.size > 1 and self.y_vel > 0) or
            (self.y_pos - self.size < 0 and self.y_vel < 0)):
            self.y_vel *= -1
class PatrollingSquare(BouncingShape):
  def __init__(self, x :float = random(), y:float = random(), xv:float = random()*0.06 - 0.03, yv:float = random()*0.06 - 0.03, s:float = 0.04, c= dudraw.set_pen_color(dudraw.GREEN)):
    BouncingShape.__init__ (x = random(), y_pos = random(), x_vel = random()*0.06 - 0.03, y_vel= random()*0.06 - 0.03, size = 0.04)
    self.x_pos = x
    self.y_pos = y
    self.x_vel = xv
    self.y_vel = yv
    self.size = s
    self.color = c 

  def move(self):
        self.x_pos += self.x_vel
        self.y_pos += self.y_vel

        if ((self.x_pos + self.size> 1 and self.x_vel> 0) or 
            (self.x_pos - self.size < 0 and self.x_vel < 0)):
            self.x_vel *= -1

        if ((self.y_pos + self.size > 1 and self.y_vel > 0) or
            (self.y_pos - self.size < 0 and self.y_vel < 0)):
            self.y_vel *= -1
  def draw(self):
      dudraw.set_pen_color(self.color)
      dudraw.filled_square(self.x_pos, self.y_pos)
      dudraw.set_pen_color(dudraw.BLACK)
      dudraw.square(self.x_pos, self.y_pos)

shapes=[]
class_list= shapes
class_list.append(BouncingCircle)
class_list.append(WobblyCircle)
class_list.append(PatrollingSquare)


       
dudraw.set_canvas_size(600,600)
dudraw.show(10000000)

