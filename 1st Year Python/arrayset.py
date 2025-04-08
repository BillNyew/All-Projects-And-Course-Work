
from __future__ import annotations
class ArraySet:
      def __init__(self):
# store the contents of the set in a python list,
# which is itself a (dynamic) array
          self.the_set = []
      def __iter__(self):
# made so easy since the contents are stored in a python
# list which is already iterable
          return iter(self.the_set)
      def __str__(self):
          result = "{"
          for x in self.the_set:
              result += str(x) + ", "
              return result.rstrip(", ") + "}"
      def get_size(self):
          return len(self.the_set)
      def add(self, v):
# No duplicates allowed in sets, so make sure v is not
# already in the set. If not, then add it (by appending
# it to the end of the list)
            if not v in self.the_set:
              self.the_set.append(v)
      def discard(self, v):
# this one was easy since python list already has
# a remove method which removes the first found
# occurrence of v. But the_set can have no duplicates
# so this works!
          try:
              self.the_set.remove(v)
          except:
              return
      def contains(self, v)->bool:
          return v in self.the_set
      def union(self, other:ArraySet)-> ArraySet:
          new_set = ArraySet()
          for i in self:
            new_set.add(i)
          for i in other:
            if i not in new_set:
                new_set.add(i)
          return new_set
      def intersection(self, other:ArraySet)-> ArraySet:
          new_set = ArraySet()
          for i in self:
            if i in other:
                new_set.add(i)
          return new_set
      def difference(self, other:ArraySet)-> ArraySet:
          new_set = ArraySet()
          for i in self:
            if i not in other:
                new_set.add(i)
          return new_set
      
def testing_code():
    test_s= ArraySet()
    test_s.add('a')
    test_s.add('a')
    test_s.add('b')
    test_s.add('c')
    test_s.add('d')
    test_s.add('e')
    test_s.discard('d')
    test_s.discard('s')
    print(test_s)
    
    print(test_s.contains('b'))
    
testing_code()
