import sys
import os
import math


class Location(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y



class PokeMap(object):

    def __init__(self, grid):
        self.grid = grid

    def get_value(self, x, y):
        if x >= len(self.grid) or y >= len(self.grid[x]):
            raise Exception('Requested coordinates outside of map')
        return self.grid[x][y]

    def get_value_from_loc(self, loc):
        return self.get_value(loc.x, loc.y)
    
    def get_size_y(self):
        return len(self.grid[0])
    
    def get_size_x(self):
        return len(self.grid)
class Location(object):

    def __init__(self, x, y):
        self.x = x
        self.y = y


class PokeMap(object):

    def __init__(self, grid):
        self.grid = grid

    def get_value(self, x, y):
        if y >= len(self.grid) or x >= len(self.grid[y]):
            raise Exception('Requested coordinates outside of map')
        return self.grid[y][x]

    def get_value_from_loc(self, loc):
        return self.get_value(loc.x, loc.y)
    
    def get_size_x(self):
        return len(self.grid[0])
    
    def get_size_y(self):
        return len(self.grid)

def log10(a):
    return math.log10(a)

def sqrt(a):
    return math.sqrt(a)

def round_down_to_places(d, num_places):
    scale_factor = math.pow(10, num_places)
    return math.floor(d * scale_factor) / scale_factor


def euc_dist(a, b):
    return sqrt(math.pow(a.x-b.x,2) + math.pow(a.y-b.y,2))

def split(li):
    pivot = li[-1]
    i = 0
    for j in range(len(li)-1):
        if(li[j] <= pivot): 
            li[i], li[j] = li[j], li[i]
            i += 1
    li[i], li[-1] = li[-1], li[i]
    return i

# get numbers from k-th smallest above
def helper(li, k):
    
    mid = split(li)
    if(mid == k-1): return li[mid:]
    elif(mid > k-1): return helper(li[:mid], k) + li[mid:]
    else: return helper(li[mid+1:], k-1-mid)

# get biggest k numbers from li
def topK(li, k):	
    if(k > len(li)): return li
    # change to: get numbers from k-th smallest above
    tmp = helper(li, len(li) - k + 1 )
    return sum(tmp)


# Complete the function below.
def find_maximum_xp(player_position, num_poke_balls, poke_map):
    X, Y = poke_map.get_size_x(), poke_map.get_size_y()
    li = []
    for x in range(X):
        for y in range(Y):
            #if(x == player_position.x and y == player_position.y):
            #    continue
            XP_poke = poke_map.get_value(x,y)
            if(XP_poke == 0): continue
            De = euc_dist(Location(x,y), player_position)
            cost = De + log10(XP_poke)
            XP_gained = XP_poke / cost
            li.append(XP_gained)
    res = topK(li, num_poke_balls)
    return round_down_to_places(res, 3)



f_in = open('input004.txt')
def raw_input():
    return f_in.readline()

if __name__ == '__main__':
    f = open('output001.txt', 'w')

    _startPosition_cnt = 0
    _startPosition_cnt = int(raw_input())
    _startPosition_i=0
    _startPosition = []
    while _startPosition_i < _startPosition_cnt:
        _startPosition_item = int(raw_input());
        _startPosition.append(_startPosition_item)
        _startPosition_i+=1

    startPosition = Location(_startPosition[0], _startPosition[1])


    _numPokeBalls = int(raw_input());


    _pokeMap_rows = 0
    _pokeMap_cols = 0
    _pokeMap_rows = int(raw_input())
    _pokeMap_cols = int(raw_input())

    _pokeMap = []
    for _pokeMap_i in range(_pokeMap_rows):
        _pokeMap_temp = [int(_pokeMap_t) for _pokeMap_t in raw_input().strip().split(' ')]
        _pokeMap.append(_pokeMap_temp)

    pokeMap = PokeMap(_pokeMap)

    res = find_maximum_xp(startPosition, _numPokeBalls, pokeMap)
    f.write("{:10.3f}".format(res).strip() + "\n")

    f.close()
