"""
    Filename:percolation.py
    Author: Bill Turbadrakh
    Date: 04/30/2023
    Course: Data Struct
    Assignment: Percolation Part 1
    Collaborators: NONE
    Internet Source: None
"""
import numpy as np
import matplotlib.pyplot as plt
import random 
from collections import deque


class Cell:
    def __init__(self, row, col):
        self.row = row
        self.col = col


class Forest:
    def __init__(self, width, height, density):
        self.width = width
        self.height = height
        self.grid = [[int(random.random() < density) for x in range(width)] for i in range(height)]
    
    def __str__(self):
        return '\n'.join([' '.join([str(cell) for cell in row]) for row in self.grid])
    #dfs
    def depth_first_search(self):
        stack = deque()
        for x in range(self.width):
            if self.grid[0][x] == 1:
                stack.append((0, x))
                self.grid[0][x] = 2
        
        while stack:
            row, col = stack.pop()
            if row == self.height - 1:
                return True
            for i, x in [(row-1,col), (row+1,col), (row,col-1), (row,col+1)]:
                if i < 0 or i >= self.height or x < 0 or x >= self.width:
                    continue
                if self.grid[i][x] == 1:
                    stack.append((i, x))
                    self.grid[i][x] = 2
        return False
    
    def simulate_forest_fire_dfs(self, density):
        fire_spread_count = 0
        for i in range(1000):
            f = Forest(20, 20, density)
            if f.depth_first_search():
                fire_spread_count += 1
        return fire_spread_count / 1000
    
    def breadth_first_search(self):
        queue = deque()
        for x in range(self.width):
            if self.grid[0][x] == 1:
                queue.append((0, x))
                self.grid[0][x] = 2
        
        while queue:
            row, col = queue.popleft()
            if row == self.height - 1:
                return True
            for i, j in [(row-1,col), (row+1,col), (row,col-1), (row,col+1)]:
                if i < 0 or i >= self.height or j < 0 or j >= self.width:
                    continue
                if self.grid[i][j] == 1:
                    queue.append((i, j))
                    self.grid[i][j] = 2
        return False

    def simulate_forest_fire_bfs(self, density):
        fire_spread_count = 0
        for i in range(1000):
            f = Forest(20, 20, density)
            if f.breadth_first_search():
                fire_spread_count += 1
        return fire_spread_count / 1000
class FireProbability:
    def __init__(self, size=20):
        self.size = size
        self.density = 0.0
        self.grid = [[False for _ in range(size)] for _ in range(size)]

    def create_forest(self, density):
        self.density = density
        self.grid = [[random.random() < density for _ in range(self.size)] for _ in range(self.size)]

    def fire_spread_dfs(self):
        visited = set()
        stack = [(0, 0)]
        while stack:
            x, y = stack.pop()
            if not (0 <= x < self.size and 0 <= y < self.size):
                continue
            if (x, y) in visited:
                continue
            visited.add((x, y))
            if self.grid[x][y]:
                return True
            stack.append((x + 1, y))
            stack.append((x - 1, y))
            stack.append((x, y + 1))
            stack.append((x, y - 1))
        return False

    def fire_spread_bfs(self):
        visited = set()
        queue = deque([(0, 0)])
        while queue:
            x, y = queue.popleft()
            if not (0 <= x < self.size and 0 <= y < self.size):
                continue
            if (x, y) in visited:
                continue
            visited.add((x, y))
            if self.grid[x][y]:
                return True
            queue.append((x + 1, y))
            queue.append((x - 1, y))
            queue.append((x, y + 1))
            queue.append((x, y - 1))
        return False

    def highest_density_dfs(self):
        low_density = 0.0
        high_density = 1.0

        for _ in range(20):
            density = (high_density + low_density) / 2.0
            self.create_forest(density)
            if self.fire_spread_dfs():
                high_density = density
            else:
                low_density = density

        return (high_density + low_density) / 2.0

    def highest_density_bfs(self):
        low_density = 0.0
        high_density = 1.0

        for _ in range(20):
            density = (high_density + low_density) / 2.0
            self.create_forest(density)
            if self.fire_spread_bfs():
                high_density = density
            else:
                low_density = density

        return (high_density + low_density) / 2.0
    
    def probability_of_fire_spread_dfs(self, density):
        f = Forest(self.size, self.size, density)
        return f.simulate_forest_fire_dfs(density)
    
    def probability_of_fire_spread_bfs(self, density):
        f = Forest(self.size, self.size, density)
        return f.simulate_forest_fire_bfs(density)
    
