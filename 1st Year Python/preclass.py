def has_zeroes(l: list):
    for i in range(len(l)):
        if l[i] == 0:
            return True
    else:
        return False
