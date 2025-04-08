from math import sqrt
import random
import dudraw

# Define the Point class
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

# Check if all points are on the same side of the line formed by p1 and p2
def all_same_side(p1, p2, points):
    initial_side = None
    for p in points:
        if p is p1 or p is p2:
            continue
        side = ((p2.x - p1.x) * (p.y - p1.y) - (p2.y - p1.y) * (p.x - p1.x))
        if side == 0:
            continue  # p lies on the line
        if initial_side is None:
            initial_side = side
        elif side * initial_side < 0:
            return False
    return True

# Brute force convex hull algorithm
def brute_force_convex_hull(points):
    if len(points) < 3:
        return points  # A convex hull cannot have less than 3 points

    hull = []
    for i in range(len(points)):
        for j in range(i + 1, len(points)):
            if all_same_side(points[i], points[j], points):
                if points[i] not in hull:
                    hull.append(points[i])
                if points[j] not in hull:
                    hull.append(points[j])
    return hull

# Generate random points
points = [Point(random.randint(1, 19), random.randint(1, 19)) for _ in range(20)]

# Compute the convex hull
hull = brute_force_convex_hull(points)

dudraw.set_x_scale(0,20)
dudraw.set_y_scale(0,20)
dudraw.clear()

for item in points:
    dudraw.set_pen_color(dudraw.BLACK)
    dudraw.filled_circle(item.x,item.y, 1/2)

hull = brute_force_convex_hull(points)
dudraw.set_pen_color(dudraw.RED)
for item in hull:
    if type(item) != type(None):
        dudraw.filled_circle(item.x, item.y, 1/4)

dudraw.show(10000)