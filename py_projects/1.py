__author__ = 'Zengye'

class MyClass(object):
    common = 10
    def __init__(self, myvar):
        self.__myvar = myvar
        self.name = "Mary"
    def myfunction(self, var1):
        return self.__myvar + var1
#instance = MyClass(30)
#print instance.myfunction(10)
#print instance.common

def get_incrementor(n):
    return lambda x:x +n
#f = get_incrementor(10)

import os
user_paths = os.environ['PYTHONPATH'].split(os.pathsep)
#print user_paths
import os
class Shape(object):
    common = "abcd"
    def __init__(self, name):
        self.name = name
    def output(self):
        print self.name


from functools import total_ordering

def square(val):
    """
    Calculates the square of a number

    Param:
    ------
    val = number

    Returns:
    --------
    numbered squared
    """
    return val * val

import numpy as np
from IPython.lib.demo import Demo

def main():
    print np.version.version
    x = np.arange(16)
    y = x.reshape((2,5))
    np.linespace()
    b = x.reshape((4,4))
    c = b

    #mydemo = Demo('myscript.py')

class ListNode(object):
 def __init__(self, x):
     self.val = x
     self.next = None

def hasCycle(head):
    """
    :type head: ListNode
    :rtype: bool
    """
    if(head == None): return None
    slow = fast = head
    while slow.next != None and fast.next != None and fast.next.next != None:
        fast = fast.next.next
        slow = slow.next
        if fast == slow:
            slow = head
            while(slow != fast):
                slow = slow.next
                fast = fast.next
            return slow
    return None



if __name__ == "__main__":
    a = raw_input()
    print a+"abc"
