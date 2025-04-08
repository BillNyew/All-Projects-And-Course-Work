from math import sqrt
import random
import time

# Define the Point class with necessary methods
class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def distance_to_line(self, line):
        # Assuming line is represented as ax + by + c = 0
        A, B, C = line
        distance = abs(A * self.x + B * self.y + C) / sqrt(A**2 + B**2)
        return distance

# Utility function to check if a point p3 is left of the line formed by p1 and p2
def is_left(p1, p2, p3):
    return ((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)) > 0

# Utility function to find the distance between two points
def distance(p1, p2):
    return sqrt((p1.x - p2.x)**2 + (p1.y - p2.y)**2)

# Find the point with the maximum distance from a line segment
def furthest_point(points, a, b):
    max_distance = -1
    furthest = None
    for point in points:
        # Line equation coefficients for ax + by + c = 0
        A = -(b.y - a.y)
        B = b.x - a.x
        C = -(A * a.x + B * a.y)
        dist = point.distance_to_line((A, B, C))
        if dist > max_distance:
            max_distance = dist
            furthest = point
    return furthest

# The recursive QuickHull algorithm
def quickhull(points, a, b, hull):
    if not points:
        return
    furthest = furthest_point(points, a, b)
    if furthest is None:
        return
    hull.add(furthest)
    # Partition the points into two subsets relative to the segments [a, furthest] and [furthest, b]
    left_of_af = [p for p in points if is_left(a, furthest, p)]
    left_of_fb = [p for p in points if is_left(furthest, b, p)]
    
    quickhull(left_of_af, a, furthest, hull)
    quickhull(left_of_fb, furthest, b, hull)

# Main function to find the convex hull
def convex_hull(points):
    if len(points) < 3:
        return points
    
    # Finding the leftmost and rightmost points
    leftmost = min(points, key=lambda p: p.x)
    rightmost = max(points, key=lambda p: p.x)
    hull = {leftmost, rightmost}
    
    # Split the set of points into two subsets
    left_set = [p for p in points if is_left(leftmost, rightmost, p)]
    right_set = [p for p in points if is_left(rightmost, leftmost, p)]
    
    # Recursively find the points in the hull for each subset
    quickhull(left_set, leftmost, rightmost, hull)
    quickhull(right_set, rightmost, leftmost, hull)
    
    return list(hull)

for i in range(1000, 50000, 500):

    points = [Point(random.randint(1, 19), random.randint(1, 19)) for _ in range(i)]
    Starttime = time.time()
    for j in range(2000):
        convex_hull(points)
    Endtime = time.time()

    print(Endtime-Starttime)
