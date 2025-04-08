
class HashSet:
    PRIMES = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]

    def __init__(self):
        self._init_table(16)
        self.size = 0

    def _init_table(self, new_capacity):
        self.capacity = new_capacity
        self.table = [[] for i in range(self.capacity)]

    def _hash_and_compress(self, value):
        hash_value = hash(value)
        return hash_value % self.capacity

    def _expand_table(self):
        new_capacity = self.capacity * 2
        new_table = [[] for _ in range(new_capacity)]
        for bucket in self.table:
            for value in bucket:
                new_hash = self._hash_and_compress(value)
                new_table[new_hash].append(value)
        self.capacity = new_capacity
        self.table = new_table

    def get_size(self):
        return self.size

    def add(self, value):
        bucket = self.table[self._hash_and_compress(value)]
        if value in bucket:
            return
        bucket.append(value)
        self.size += 1
        if self.size > self.capacity * 0.75:
            self._expand_table()

    def discard(self, value):
        bucket = self.table[self._hash_and_compress(value)]
        if value in bucket:
            bucket.remove(value)
            self.size -= 1

    def contains(self, value):
        bucket = self.table[self._hash_and_compress(value)]
        return value in bucket

    def union(self, other_set):
        result = HashSet()
        for bucket in self.table + other_set.table:
            for value in bucket:
                result.add(value)
        return result

    def intersection(self, other_set):
        result = HashSet()
        for value in self:
            if other_set.contains(value):
                result.add(value)
        return result

    def difference(self, other_set):
        result = HashSet()
        for value in self:
            if not other_set.contains(value):
                result.add(value)
        return result

    def __iter__(self):
        for bucket in self.table:
            for value in bucket:
                yield value

    def __str__(self):
        return "{" + ", ".join(str(value) for value in self) + "}"
    


setA = HashSet()
setB = HashSet()
setC = HashSet()
setD = HashSet()
setA.add(1)
setA.add(2)
setA.add(3)
setA.add(4)
setB.add(3)
setB.add(4)
setB.add(5)
setB.add(6)
setC.add(2)
setC.add(4)
setC.add(6)
setC.add(8)
setD.add(5)
setD.add(7)
setD.add(9)
setA = setA.union(setB)
print(setA)
setA = setA.difference(setB)
print(setA)
setB = setB.intersection(setC)
print(setB)


def has_zero_sum(nums):
    visited = HashSet()
    for i in nums:
        if i in visited or -i in visited:
            return True
        visited.add(i)
        visited.add(-i)
    return False