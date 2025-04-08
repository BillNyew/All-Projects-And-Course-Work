import matplotlib.pyplot as plt 
import math
#data plot
x = ["Astronomy", "Biology", "Law", "Physics", "Psychology", "Sociology"]
y = [50,50,50,50,50,50]
plt.bar(x,y)
#range of y-axis
plt.ylim(0,100) 
#title
plt.title("Does the department a student is applying to affect their acceptence rate?")
#X-axis
plt.xlabel("Department(X-axis)")
#y-axis
plt.ylabel("Rate of Acceptance in %(Y-axis)")

plt.savefig("Lab_DataVizGraph.pdf") 
plt.savefig("Lab_DataVizGraph.pdf")
plt.show()

