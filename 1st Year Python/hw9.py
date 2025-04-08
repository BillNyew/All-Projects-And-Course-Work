from pprint import pprint
import dudraw

grid=[]

dudraw.set_x_scale(0.0,12)
dudraw.set_y_scale(0.0,10)


for _ in range(10):
  inner= []
  for _ in range(12):
    inner.append(0)
  grid.append(inner)

while True:
  dudraw.clear()
  for row in range(len(grid)):
    for col in range(len(grid[row])):
        dudraw.text(col + .5, row + .5,str(grid[row][col]) )
  
  if dudraw.mouse_pressed():
    mx=dudraw.mouse_x()
    my=dudraw.mouse_y()
    grid[int(my)][int(mx)] += 1

  


  dudraw.show()




