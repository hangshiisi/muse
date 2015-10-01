


def curry2(f): 
    """
    Return a curried version of the given two-argument function
    """
    def g(x): 
        def h(y): 
            return f(x, y)
        return h
    return g

def curry(f, x): 
    """
    Return a curried version of the given function f
    """
    def h(y): 
        return f(x, y)

    return h

def uncurry2(g): 
    """
    Return a two-argument version of the given curried function 
    """
    def f(x, y): 
        return g(x, y)
    return f



"""
Example
>>> power_curried = curry2(pow) 
>>> pow_curried(2)(5)
32
>>> power2 = curry(pow, 2) 
>>> power2(5)
32

>>> map_to_range(0, 10, pow_curried(2)) 
1
2
4
..
512
"""

