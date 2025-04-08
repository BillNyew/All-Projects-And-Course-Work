# to install matplotlib, run "pip install matplotlib" 
# OR "pip3 install matplotlib"

import matplotlib.pyplot as plt 
import math

# viz 1 - simple line plot of y=2^x
x = [1,2,3,4,5,6]

y = []
for i in x: # for each element in x
    y.append(math.pow(2,i)) # append 2^i to the end of list y

plt.plot(x,y)

plt.ylabel("2 raised to the x") # add axis labels and title
plt.xlabel("x")
plt.title("Simple Line Plot")

plt.show()

# iz 2 - simple scatter plot
x =[5, 7, 8, 7, 2, 17, 2, 9, 4, 11, 12, 9, 6]
y =[99, 86, 87, 88, 100, 86, 103, 87, 94, 78, 77, 85, 86]

plt.scatter(x, y, c ="blue")
plt.show()


# viz 3 - shows how to change some attributes like markers and colors
# https://matplotlib.org/stable/api/_as_gen/matplotlib.pyplot.scatter.html 
# dataset-1
x1 = [89, 43, 36, 36, 95, 10, 66, 34, 38, 20]
y1 = [21, 46, 3, 35, 67, 95, 53, 72, 58, 10]
# dataset2
x2 = [26, 29, 48, 64, 6, 5, 36, 66, 72, 40]
y2 = [26, 34, 90, 33, 38, 20, 56, 2, 47, 15]

# https://matplotlib.org/stable/api/markers_api.html#module-matplotlib.markers
plt.scatter(x1, y1, c="green", linewidths = 2, marker ="s", edgecolor ="red", s = 50) # s marker means square, s is marker size
plt.scatter(x2, y2, c ="yellow", linewidths = 2, marker ="^", edgecolor ="red", s = 200) # add second set of points to same axis

plt.xlabel("X-axis")
plt.ylabel("Y-axis")

# if saving figures, need to do so BEFORE .show() as .show() resets plot
plt.savefig("out.pdf") # if path not specified, saves to current directory
plt.savefig("out.pdf")
plt.show()

# viz 4 - bar charts
x = ["a","b","c","d"]
y = [3.2,3.25,3.3,3.4]
plt.bar(x,y)
# plt.ylim(3.1,3.5) # changes range on y axis
plt.show()

# to run, type "python lecture1_demo.py" OR "python3 lecture1_demo.py" in the terminal 
# or push the "play" button in the upper right hand corner

 

 

 