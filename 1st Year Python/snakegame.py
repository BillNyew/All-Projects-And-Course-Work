"""
 Filename: snakegame.py
 Author: Bill Turbadrakh
 Date: April 10 2023
 Course: COMP 1353
 Assignment: Snake Game
 Collaborators: None
 Internet Source: None
"""

import random
import dudraw

class Node:
    def __init__(self, value):
        self.value = value
        self.next_node = None
        self.prev_node = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
    
    def add_first(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            self.tail = new_node
        else:
            new_node.next_node = self.head
            self.head.prev_node = new_node
            self.head = new_node
    
    def remove_last(self):
        if self.tail is None:
            return None
        else:
            value = self.tail.value
            if self.head is self.tail:
                self.head = None
                self.tail = None
            else:
                self.tail.prev_node.next_node = None
                self.tail = self.tail.prev_node
            return value
    
    def first_node(self):
        return self.head
    
    def __iter__(self):
        node = self.head
        while node:
            yield node
            node = node.next_node

class Snake:
    def __init__(self):
        self.body = DoublyLinkedList()
        self.body.add_first((5, 5)) # head  
        self.body.add_first((5, 6))
        self.body.add_first((5, 7)) # tail
        self.direction = None
    def draw(self):
        dudraw.set_pen_color(dudraw.DARK_GREEN)
        for node in self.body:
            x, y = node.value
            dudraw.filled_rectangle(x - 0.5, y - 0.5, .5, .5)
    
    def update(self):
    # update the position of each body part based on the direction of movement
        head = self.body.first_node()
        x, y = head.value
        if self.direction == "up":
            self.body.add_first((x, y + .5))
        elif self.direction == "down":
            self.body.add_first((x, y - .5))
        elif self.direction == "left":
            self.body.add_first((x - .5, y))
        elif self.direction == "right":
            self.body.add_first((x + .5, y))

    # remove the last body part to maintain the length of the snake
        self.body.remove_last()

    # check if the head has hit the border
        if x < -.5 or x > 19.5 or y < -.5 or y > 19.5:
            game_over = True
        
   
class Food:
    def __init__(self, snake=Snake()):
        self.x = random.randint(0, 19)
        self.y = random.randint(0, 19)
        self.snake = snake
    
    def draw(self):
        dudraw.set_pen_color(dudraw.RED)
        dudraw.filled_rectangle(self.x + 0.1, self.y + 0.1, 0.3, 0.3)
    
    def generate_new_location(self):
        self.x = random.randint(0, 19)
        self.y = random.randint(0, 19)
        while (self.x, self.y) in self.snake.body:
            self.x = random.randint(0, 18)
            self.y = random.randint(0, 18)
def main():
    #set canvas size
    dudraw.set_canvas_size(400,400)
    #strongly reccomend setting this scale-- hint where does it draw the rectangle located at 0,0 with half/height and half/width of 1/2?
    dudraw.set_x_scale(-.5, 19.5)
    dudraw.set_y_scale(-.5, 19.5)
    # make a snake
    snake = Snake()
    direction = "right"
    game_over = False

    # make some food
    food = Food(snake)
    limit = 1 #number of frames to allow to pass before snake moves
    timer = 0  #a timer to keep track of number of frames that passed
    key = ''
    while key != 'q' and not game_over:
        if key == '':
            dudraw.set_pen_color(dudraw.BLACK)
            dudraw.text(5, 10, "Press WASD To Start.")
        # process keyboard press here
        if dudraw.has_next_key_typed():
            key = dudraw.next_key_typed()
            if key == "w":
                direction = "up"
            elif key == "a":
                direction = "left"
            elif key == "s":
                direction = "down"
            elif key == "d":
                direction = "right"
            else:
                pass
         # draw and move the snake
        snake.direction = direction  # update the direction of the snake
        snake.update()  # update the position of the snake
        snake.draw()  # draw the updated snake
        # draw some food
        food.draw()  # draw the food
        # check if the snake has collided with the food
        if snake.body.first_node().value == (food.x, food.y):
            snake.body.add_last((food.x, food.y))  # add a new body part to the snake
            food.generate_new_location()  # generate a new location for the food
        # check if the snake has collided with itself or the borders
        for node in snake.body:
            if node is not snake.body.first_node() and node.value == snake.body.first_node().value or \
                    snake.body.first_node().value[0] < -.5 or snake.body.first_node().value[0] > 19.5 or \
                    snake.body.first_node().value[1] < -.5 or snake.body.first_node().value[1] > 19.5:
                game_over = True  # end the game if the snake has collided with itself or the borders
                break
        if game_over:
            break
        # update the timer
        timer += 1
        if timer == limit:
            dudraw.show(50)  # update the drawing every 100 milliseconds
            dudraw.clear()
            timer = 0
    # Game over
    dudraw.set_pen_color(dudraw.BLACK)
    dudraw.text(5, 10, "Game Over. Press Q to Quit.")
    dudraw.show()
if __name__ == '__main__':
    main()