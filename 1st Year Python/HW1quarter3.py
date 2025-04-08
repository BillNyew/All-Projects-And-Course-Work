class Node:
    def __init__(self, value, next_node=None):
        self.value = value
        self.next = next_node

class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def __str__(self) -> str:
        if self.head is None:
            return "[]"
        else:
            #Draw a left bracket to start the list
            temp_str ="["
            #Set the temp node to be the head to the be first value
            temp_node= self.head

            #If it isn't the last one, temp node becomes temp_node.next
            while temp_node is not None:
                temp_str+=str(temp_node.value)

                #Interior Node
                if temp_node.next is not None:
                    temp_str+=", "
                #end/terminal node
                else:
                    temp_str+="]"

                temp_node=temp_node.next
            return temp_str

    def append(self, value):
        node = Node(value)
        if self.head is None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            self.tail = node
        self.size += 1

    def get(self, index):
        if not (0 <= index < self.size):
            raise IndexError("Index out of range")
        node = self.head
        for i in range(index):
            node = node.next
        return node.value
    
    def get_size(self):
        return self.size

    def is_empty(self):
        if self.head is None:
            return True
        else:
            return False
    
    def remove_first(self):
        if self.head is None:
            raise ValueError("List is empty")
        value = self.head.value
        self.head = self.head.next
        self.size -= 1  
        if self.size == 0:
            self.tail = None
        return value
    
    def remove_last(self):
        if self.tail is None:
            raise ValueError("List is empty")
        value = self.tail.value
        self.tail = self.tail.prev
        self.size -= 1
        if self.size == 0:
            self.tail = None
        return value


    def remove_at_index(self, index):
        if not (0 <= index < self.size):
            raise IndexError("Index out of range")
        if index == 0:
            value = self.head.value
            self.head = self.head.next
            self.size -= 1
            if self.size == 0:
                self.tail = None
            return value
        node = self.head
        for i in range(index - 1):
            node = node.next
        value = node.next.value
        node.next = node.next.next
        self.size -= 1
        if index == self.size:
            self.tail = node
        return value

    
    def add_first(self, value):
        node = Node(value, self.head)
        self.head = node
        if self.tail is None:
            self.tail = node
        self.size += 1

    def add_last(self, value):
        node = Node(value)
        if self.tail is None:
            self.head = node
            self.tail = node
        else:
            self.tail.next = node
            self.tail = node
        self.size += 1
import random
def homework_driver():
    random.seed(5)
    testing_list= SinglyLinkedList()
    for i in range(1,4):
        testing_list.add_first(i * random.randint(0,10))
        testing_list.add_last(i * random.randint(0,10))
        testing_list.add_first(i * random.randint(0,10))
        testing_list.add_last(i * random.randint(0,10))
    # print(TestingList)
    for _ in range(5):
        rand_index=random.randint(0,20)
        # print(f'rand_index is {rand_index}')
        try: testing_list.remove_at_index(rand_index)
        except IndexError as e:
            pass
            # print(e)
    print(testing_list)

#The following is the main code block:
homework_driver()
    