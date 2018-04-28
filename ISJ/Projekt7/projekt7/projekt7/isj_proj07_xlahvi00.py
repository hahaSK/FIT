#!/usr/bin/env python3

import math
from functools import wraps
import traceback

class TooManyCallsError(Exception):
    """ Error class """
    pass

def limit_calls(max_calls=2, error_message_tail='called too often'):
    """ Limit decorator """ 
    def limit_calls_decorator(func):
        """ Function decorator """
        @wraps(func)
        def func_wrapper(a, b):
            """ Function wrapper """
            func_wrapper.calls += 1
            if func_wrapper.calls > max_calls :
                specific_error_message = "function " + '"' + str(func.__name__) + '"' + " - " + error_message_tail
                raise TooManyCallsError(specific_error_message)
            else:   
                return func(a, b)

        func_wrapper.calls = 0
        return func_wrapper
    return limit_calls_decorator

def ordered_merge(*args, **kwargs):
    """ Generator function """
    if kwargs.__contains__("selector"):
        selector = kwargs["selector"]
    else:
        return list()

    argument_count = list()
    for iterator in args:
        argument_count.append(0)

    result = list()
    for index in selector:
        result.append(args[index][argument_count[index]])
        argument_count[index] += 1
    return result

class Log():
    """ Log class """

    def __init__(self, logfile):
        """ Initialize log class """
        self.filename = logfile

    def __enter__(self):
        """ Entering with """
        self.IO_file_stream = open(self.filename, "w+")
        self.IO_file_stream.write("Begin\n")
        return self

    def logging(self, text):
        """ Logging to logfile """
        return self.IO_file_stream.write(text+'\n')

    def __exit__(self, exc_type, exc_val, exc_tb):
        """ When exiting with """
        self.IO_file_stream.write("End\n")
        return self.IO_file_stream.close()
    

if __name__ == '__main__':

    with Log('mylog.txt') as logfile:
        logfile.logging('Test1')
        logfile.logging('Test2')
        a = 1/0
        logfile.logging('Test3')

    print(list(ordered_merge('abcde', [1, 2, 3], (3.0, 3.14, 3.141), range(11, 44, 11), selector = [2,3,0,1,3,1])))

    @limit_calls(1, 'that is too much')
    def pyth(a,b):
        c = math.sqrt(a**2 + b ** 2)
        return c

    print(pyth(3,4))
    print(pyth(6,8))

   