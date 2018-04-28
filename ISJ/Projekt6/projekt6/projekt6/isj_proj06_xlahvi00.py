#!/usr/bin/env python3


from operator import add, sub, mul, truediv
import itertools

def first_nonrepeating(string):
    """ returns first non-repeating character
        from strings, otherwise prints None. """

    try:
        string = string.lower()
        string = string.replace(" ", "")
        for char in string:
            if (string.count(char)) == 1 and (char.isprintable()):
                return char
        return None
    except (TypeError, AttributeError) as exception:
        return None

ops = ['+', '-', '/', '*']
op_map = {'+': add, '-': sub, '/': truediv, '*': mul}

def iter_combinations(seq):
    """ function iterates over 1 permutation and generates 
        parentheses and operator combinations """

    if len(seq) == 1:
        yield seq[0], str(seq[0])
    else:
        for i in range(len(seq)):
            # split input list at i`th place
            left, right = seq[:i], seq[i:]  
            # generate cartesian product
            for l, l_str in iter_combinations(left):
                for r, r_str in iter_combinations(right):
                    for op in ops:
                        # can't divide by zero
                        if op_map[op] is truediv and r == 0:  
                            continue
                        else:
                            if op_map[op] is add or op_map[op] is sub:
                                yield op_map[op](float(l), r), ('(' + l_str + op + r_str + ')')
                            else:
                                yield op_map[op](float(l), r), (l_str + op + r_str)


def combine4(numbers, result):
    """ Function makes all possible equations
        from 4 input numbers and result, using only +,-,*,/ """

    # check input
    if type(result) != int or type(numbers) != list or len(numbers) != 4:
        return None
    for item in numbers:
        if type(item) != int and item < 0:
            return None
    numbers.sort()

    lst = []
    # generate perms
    for current in itertools.permutations(numbers, 4): # generate perms
        for value, item in iter_combinations(list(current)):
            if eval(item) == result:
                if item not in lst:
                  lst.append(item)    
    return lst        

def test():
    """ tests. """

    assert first_nonrepeating("tooth") == 'h'
    assert first_nonrepeating("lool lool") == None 
    assert first_nonrepeating('5') == '5'
    assert first_nonrepeating('\t') == None
    assert first_nonrepeating('*/*') == '/'
    assert first_nonrepeating(' ') == None
    print(combine4([6,6,5,2],25))
    print(combine4([6,6,5,2],17))
    print(combine4([6,6,5,2],-16))
    print(combine4([6,6,5,2],36))
    print(combine4([1,1,1,1],0))

if __name__ == '__main__':
    test()