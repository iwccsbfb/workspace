__author__ = 'Zengye'

class Solution(object):
    def setZeroes(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """
        height = len(matrix)
        if(height ==0): return
        width = len(matrix[0])
        for i in range(height):
            for j in range(width):
                if matrix[i][j] == 0:
                    for tmp in range(height):
                        if matrix[tmp][j] != 0:
                            matrix[tmp][j] = 'a'
                    for tmp in range(width):
                        if matrix[i][tmp] != 0:
                            matrix[i][tmp] = 'a'

        for i in range(height):
            for j in range(width):
                if matrix[i][j] == 'a':
                    matrix[i][j] = 0



class Queue(object):
    def __init__(self):
        """
        initialize your data structure here.
        """
        self.data = []

    def push(self, x):
        """
        :type x: int
        :rtype: nothing
        """
        data2 = []
        [data2.append(data.pop()) for i in range(len(self.data))]
        self.data = [x]
        [self.data.append(data2.pop()) for i in range(len(data2))]

    def pop(self):
        """
        :rtype: nothing
        """
        self.data.pop()

    def peek(self):
        """
        :rtype: int
        """
        return self.data[-1]

    def empty(self):
        """
        :rtype: bool
        """
        return (len(self.data)==0)

def maxProfit(prices):
    """
    :type prices: List[int]
    :rtype: int
    """
    n = len(prices)
    if(n<2): return 0
    pre_profits = [0]*n
    post_profits = [0]*n

    min, max_profit = prices[0], 0
    for i in range(1, len(prices)):
        max_profit = max(prices[i] - min, max_profit)
        if(prices[i] < min):
            min = prices[i]
        pre_profits[i] = max_profit

    min, max_profit = prices[-1], 0
    for i in range(1, len(prices)):
        max_profit = max(prices[-i] - min, max_profit)
        if(prices[-i] < min):
            min = prices[-i]
        post_profits[-i] = max_profit

    max_profit = 0
    for i in range(0, len(prices)):
        max_profit = max(pre_profits[i]+post_profits[i], max_profit)
    return max_profit



























