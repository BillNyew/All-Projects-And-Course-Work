import random



class Node:
    def __init__(self,value=None,next=None):
        self.value=value
        self.next=next
    def __repr__(self):
        return f"{self.value}"

class DoublyCircularLinkedList:
    def __init__(self):
        self.cursor=None
        self.size = 0
    
    def __str__(self) -> str:
        if self.size ==0:
            return '[]'
        result ="["
        current_node=self.cursor
        for i in range(self.size):
            result += str(current_node.value)
            current_node = current_node.next
            if i < self.size - 1:
                result += ","
        return result +"]"
    
    def add_after_cursor(self, v):
        if self.cursor is None:
            self.cursor=Node(v)
            self.cursor.next = self.cursor
            self.cursor.prev = self.cursor
        else:
            new_node = Node(v)
            new_node.next = self.cursor.next
            new_node.prev = self.cursor
            new_node.next.prev = new_node
            new_node.prev.next = new_node
        self.size += 1
    
    def delete_cursor(self):
        if self.cursor is None:
            raise ValueError("List is empty")
        
        value = self.cursor.value

        if self.size ==1:
            self.cursor = None
            self.size = 0
        else:
            self.cursor.value = self.cursor.next.value
            self.cursor.next = self.cursor.next.next
            self.size -= 1
        return value

    def advance_cursor(self,n):
        if self.cursor is None or n <0:
            raise ValueError("List is empty")
        for i in range(n):
            self.cursor=self.cursor.next
    
    def get_value(self):
        if self.cursor is None:
            raise Exception("List is empty")
        
        return self.cursor.value
    
    def is_empty(self):
        return self.cursor is None
    
    def get_size(self):
        return self.size
    
import random
def homework_driver():
    random.seed(2)
    test_list = DoublyCircularLinkedList()

    for i in range(10):
        test_list.add_after_cursor(i)
    while not test_list.is_empty():
        n = random.randint(0,9)
        test_list.advance_cursor(n)
        print(test_list.delete_cursor(), end='')
    print()
homework_driver()