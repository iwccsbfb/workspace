__author__ = 'Zengye'

import numpy as np
from numpy import linalg as npl
import time

if __name__=="__main__":
    N = 1000
    np.random.seed(0)
    a = np.random.rand(N,N)
    b = np.random.rand(N)

    count = 100
    start_time = time.time()
    for i in range(count):
        t = npl.solve(a,b)
    print("--- %s seconds ---" % (time.time() - start_time))

    '''
    print a
    print b
    print type(a)
    print npl.solve(a, b)'''

