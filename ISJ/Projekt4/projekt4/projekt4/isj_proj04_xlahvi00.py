#!/usr/bin/env python3

def can_be_a_set_member_or_frozenset(item):
    """ Returns item if it can be element of set. """
    try:
        hash(item)  #must be hashable
    except TypeError:
        return frozenset(item)
    return item

def all_subsets(lst):
    """ Returns all subsets from input set. """
    sets = [[]]
    for x in lst:
        sets.extend([subset + [x] for subset in sets])
   
    return sets

def all_subsets_excl_empty(*lst, **kwargs):
        """ Function gets all subsets, but removes 
            empty subset if no argument or exclude_empty is True. """
        if kwargs.get('exclude_empty') == False: #gets optional argument
            return all_subsets(lst)
        else:
            sets = all_subsets(lst)
            sets.remove([])
            return sets

def test():
    """ Run tests. """
    assert can_be_a_set_member_or_frozenset(1) == 1
    assert can_be_a_set_member_or_frozenset((1,2)) == (1,2)
    assert can_be_a_set_member_or_frozenset([1,2]) == frozenset([1,2])
    
    assert all_subsets(['a', 'b', 'c']) == [[], ['a'], ['b'], ['a', 'b'], ['c'], ['a', 'c'], ['b', 'c'], ['a', 'b', 'c']]

    assert all_subsets_excl_empty('a', 'b', 'c') == [['a'], ['b'], ['a', 'b'], ['c'], ['a', 'c'], ['b', 'c'], ['a', 'b', 'c']]
    assert all_subsets_excl_empty('a', 'b', 'c', exclude_empty = True) == [['a'], ['b'], ['a', 'b'], ['c'], ['a', 'c'], ['b', 'c'], ['a', 'b', 'c']]
    assert all_subsets_excl_empty('a', 'b', 'c', exclude_empty = False) == [[], ['a'], ['b'], ['a', 'b'], ['c'], ['a', 'c'], ['b', 'c'], ['a', 'b', 'c']]


if __name__ == '__main__':
    test()
