"""
    Filename: project7.py
    Author: Bill Turbadrakh
    Date: 3/10/2023
    Course: COMP_1352
    Assignment: Project7(animation)
    Collaborators: None
    Internet Source: None
"""
from __future__ import annotations
import dudraw
from dudraw import Color
import math
from random import randint
from random import uniform

class Vector:
    def __init__(self, some_x=0, some_y=0):
        self.x = some_x
        self.y = some_y

    def limit(self, l):
        if(self.length() >= l):
            self.resize(l)

    def resize(self, l):
        length = math.sqrt(self.x ** 2 + self.y**2)
        self.x *= (l/length)
        self.y *= (l/length)

    def __add__(self, other_vector):
        return Vector(self.x+other_vector.x, self.y + other_vector.y)

    def __sub__(self, other_vector):
        return Vector(self.x-other_vector.x, self.y - other_vector.y)

    def __isub__(self, other_vector):
        self.x -= other_vector.x
        self.y -= other_vector.y
        return self

    def __iadd__(self, other_vector):
        self.x += other_vector.x
        self.y += other_vector.y
        return self

    def divide(self, s):
        self.x /= s
        self.y /= s

    def length(self):
        return math.sqrt(self.x**2 + self.y**2)

    def angle_in_radians(self):
        return math.tan((self.y/self.x))
    
class Particle:
    def __init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime):
        self.x_pos = x_pos
        self.y_pos = y_pos
        
        self.pos = Vector(self.x_pos,self.y_pos)
 
        self.x_vel = x_vel
        self.y_vel = y_vel
        self.vel = Vector(self.x_vel,self.y_vel)
        self.color = Color(randint(1,255),randint(1,255),randint(1,255))
        self.size = size
        self.lifetime = lifetime

    def has_expired(self):
        if self.lifetime == 0: 
            return True
        return False
    def move(self):
        if not self.has_expired():
            self.pos +=self.vel
            self.lifetime -=1

class SparkleFirework(Particle):
    def __init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime):
        Particle.__init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime)
        self.color = Color(203,195,227)
    def draw(self):
        #dudraw.set_pen_color(self.color)
        dudraw.set_pen_color_rgb(203,195,227)
        dudraw.line(self.pos.x,self.pos.y,self.pos.x+self.vel.x,self.pos.y+self.vel.y)

class FireParticle(Particle):
    def __init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime):
        Particle.__init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime)
        self.g = 255
        self.color = Color(255,self.g,0)
    def draw(self):
        self.g *= 0.95
        dudraw.set_pen_color(Color(255,int(self.g),0))
        dudraw.filled_circle(self.pos.x,self.pos.y,self.size)
    def move(self):
        Particle.move(self)
        self.size *= .9

class AcceleratingParticle(Particle):
    def __init__(self,x_pos,y_pos,x_vel,y_vel,x_acc,y_acc,size,lifetime):
        Particle.__init__(self,x_pos,y_pos,x_vel,y_vel,size,lifetime)
        self.acc = Vector(x_acc,y_acc)
    def move(self):
        Particle.move(self)
        self.vel += self.acc

class FireworkParticle(AcceleratingParticle):
    def draw(self):
        dudraw.set_pen_color(self.color)
        dudraw.filled_square(self.pos.x,self.pos.y,self.size)
     
class MarbleParticle(AcceleratingParticle):
    def draw(self):
        dudraw.set_pen_color(self.color)
        dudraw.filled_circle(self.pos.x,self.pos.y,self.size)

class ParticleContainer:
    def __init__(self,x_pos,y_pos):
        self.pos = Vector(x_pos,y_pos)
        self.particles = []
    def animate(self):
        
        for particle in self.particles:
            if particle.has_expired():
                self.particles.remove(particle)
            else:
                particle.draw()
                particle.move()
                
class Firework(ParticleContainer):
    def __init__(self,x_pos,y_pos):
        ParticleContainer.__init__(self,x_pos,y_pos)
        for i in range(500):
            self.particles.append(FireworkParticle(x_pos,y_pos,uniform(-0.04,0.04),uniform(-0.04,0.04),0,uniform(-0.008,-0.0012),0.004,50))

class Marbles(ParticleContainer):
    def __init__(self,x_pos,y_pos):
        ParticleContainer.__init__(self,x_pos,y_pos)
        for _ in range(10):
            self.particles.append(MarbleParticle(uniform(0.05,1-0.05),uniform(0.05,1-0.05),uniform(-0.04,0.04),uniform(-0.04,0.04),0,uniform(-0.001,-0.002),0.05,500))
    def animate(self):
       for i,particle in enumerate(self.particles):
           if self.particles[i].has_expired():
              self.particles.remove(particle)
           else:
                for another_i in range(i+1,len(self.particles)):
                    distance_vector = self.particles[i].pos - self.particles[another_i].pos
                    if distance_vector.length() <= self.particles[i].size + self.particles[another_i].size:
                        distance_vector.limit(0.015)
                        self.particles[i].vel += distance_vector
                        self.particles[another_i].vel -= distance_vector
                if (self.particles[i].pos.x +self.particles[i].size >=1 and self.particles[i].vel.x >0) or (self.particles[i].pos.x - self.particles[i].size <=0  and self.particles[i].vel.x):
                    self.particles[i].vel.x = -self.particles[i].vel.x
                if (self.particles[i].pos.y - self.particles[i].size <=0  and self.particles[i].vel.y) or (self.particles[i].pos.y +self.particles[i].size >=1 and self.particles[i].vel.y >0):
                    self.particles[i].vel.y = -0.7 * self.particles[i].vel.y
                        
                self.particles[i].draw()
                self.particles[i].move()
               
class Emitter(ParticleContainer):
    def __init__(self,x_pos,y_pos,fire_rate):
        ParticleContainer.__init__(self,x_pos,y_pos)
        self.fire_rate = fire_rate

class Fire(Emitter):
    def __init__(self,x_pos,y_pos,fire_rate):
        Emitter.__init__(self,x_pos,y_pos,fire_rate)
    def animate(self):
        for _ in range(self.fire_rate):
            self.particles.append(FireParticle(self.pos.x,self.pos.y,uniform(-0.002,0.002),uniform(0.002,0.005),uniform(0.01,0.03),50))
        Emitter.animate(self)

class Sparkler(Emitter):
    def __init__(self,x_pos,y_pos,fire_rate):
        Emitter.__init__(self,x_pos,y_pos,fire_rate)
    def animate(self):
        for _ in range(self.fire_rate):
            self.particles.append(SparkleFirework(self.pos.x,self.pos.y,uniform(-0.07,0.07),uniform(-0.07,0.07),0.04,5))
        Emitter.animate(self)

tests = []
tests.append(Fire(0.3,0.15,30))
tests.append(Sparkler(0.75,0.75,100))
tests.append(Firework(0.25,0.75))
tests.append(Marbles(0.25,0.25))
key = ""
while key != "q":
    dudraw.clear(dudraw.BLACK)
    for test in tests:
        test.animate()
    dudraw.show(40)