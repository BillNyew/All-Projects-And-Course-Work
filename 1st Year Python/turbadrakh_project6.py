"""

File Name: turbadrakh_project6.py
Author:Bill Turbadrakh
Date:10/24/2022
Course:COMP 1351-6
Assignment:Project 6
Internet Source:

"""
import dudraw
import random
 
x_list = []
y_list = []
x_speed = []
y_speed = []
#populates x list with random floats
for i in range(11):
    x_list.append(random.random())
    y_list.append(random.random())
 
for i in range(11):
    x_speed.append(random.uniform(.0, .03))
    y_speed.append(random.uniform(.0, .03))
 
for i in range(100):
    for i in range(9):
        dudraw.line(x_list[i], y_list[i], x_list[i+1], y_list[i+1])
    for i in range(10):
        if x_list[i] <= 0 or x_list[i] >= 1:
            x_speed[i] *= -1
    for i in range(10):
        if y_list[i] <= 0 or y_list[i] >= 1:
            y_speed[i] *= -1
    for i in range(10):
        x_list[i]+= x_speed[i]
        y_list[i] += y_speed[i]
    dudraw.show(10)
   
       
        #dudraw.line(x_list[i], y_list[i], x_list[i+1], y_list[i+1])
 
dudraw.show(float('inf'))