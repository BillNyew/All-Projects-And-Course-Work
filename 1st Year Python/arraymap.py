class Item:
    def __init__ (self, k=None, v=None):
        self.key=k
        self.value=v
    #def get_key(self):
        return self.key
    def set_value(self,v):
        old_value=self.value
        self.value=v
        return old_value

class ArrayMap:
    def __init__ (self):
        self.the_table=[]
    def get_size(self)->int:
        return len(self.the_table)
    def is_empty(self)->bool:
        return len(self.the_table)==0
    def get(self,k):
        for item in self.the_table:
            if k==item.key:
                return item.value
        return None
                
    def put(self, k ,v):
        for item in self.the_table:
            if k==item.key:
                return_value=item.value
                item.value=v
                return return_value
        self.the_table.append(Item(k,v))
        return None
    def remove(self, k):
      for i in range(len(self.the_table)):
        if self.the_table[i].key == k:
            value = self.the_table[i].value
            self.the_table.pop(i)
            return value
      return None
    def keys(self):
        return [entry.get_key() for entry in self.the_table]

    def values(self):
        return [entry.get_value() for entry in self.the_table]

    def entries(self):
        return [entry for entry in self.the_table]
    
    def __iter__(self):
        return self.keys()
  
