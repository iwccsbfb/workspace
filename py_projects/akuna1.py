__author__ = 'Zengye'
import string


def nums_without_digit_prob(low, high, digit) :
    digit = str(digit)
    count = 0
    for i in range(low, high+1):
        s = str(i)
        if string.find(s, digit) == -1: # cannot find
            count += 1
    print count
    return float(count) / (high - low + 1)






if __name__ == '__main__':
    print nums_without_digit_prob(1, 60000, 6)