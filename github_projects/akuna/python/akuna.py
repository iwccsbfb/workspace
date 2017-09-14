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





import sys

# start packing melons from start_m into boxes
def melon_count_from_mid(boxes, melons, start_m):
    res = 0 
    pm = start_m  # pointer of melon
    pb = 0 # pointer of box
    while pm < len(melons) and pb < len(boxes):
        if boxes[pb] >= melons[pm]:
            res += 1
            pm += 1
        pb += 1
    return res

          
def melon_count(boxes, melons):
	res = 0
    # starting melon iterate from all melons
	for start_m in range(0, len(melons)):
		tmp_res = melon_count_from_mid(boxes, melons, start_m)
		res = max(res, tmp_res)
	return res
	


def solve(input):
    wdic = {}
    ldic = [0]*26
    cnt = 0
    for l in input:
    #for l in sys.stdin:
        words = l.strip().split(' ')
        cnt += len(words)
        for w in words:
            if wdic.has_key(w):
                wdic[w] += 1
            else:
                wdic[w] = 1
    for k in wdic:
        for l in k:
            ldic[ord(l) - ord('a')] += 1


    print cnt
    print 'words'
    for k in sorted(wdic.items(), key = lambda x: x[0]):
        print k[0] + ' ' + str(k[1])
    print 'letters'
    for l in xrange(26):
        print chr(l + ord('a')) + ' ' + str(ldic[l])



def is_valid_word(word):
    assert word != ''

    for ch in word:
        if ch < 'a' or 'z' < ch:
            return False
    return True

# assume ' '  and '\t' are both spaces
def parsing_words(input):
    wd_count = 0  # word count
    wd_dict = {} # word dictionary, map word -> occurances
    letter_count = [0]*26  # count of letters

    for line in input: 
    #for line in sys.stdin:
        words = line.split()
        for word in words:
            if is_valid_word(word):
                wd_count += 1
                if wd_dict.has_key(word): 
                    wd_dict[word] += 1
                else: wd_dict[word] = 1

                for ch in word: 
                    letter_count[ord(ch) - ord('a')] += 1

    print "%d" % wd_count
    print 'words'
    for word in sorted(wd_dict):
        print "%s %d" % (word, wd_dict[word])
    print 'letters'
    for i in range(0, 26):
        print "%s %d" % (chr(ord('a')+i), letter_count[i])

        



import sys
import math

feature_count = 3
mix_ratio = 0.9999999999

# prob density function for N(miu, var) at x
def npdf(miu, var, x):
    try:
        return math.exp(-0.5*(x-miu)*(x-miu)/var)
    except: # exception when exponet explodes 
        return 0

# mix normal distribution with normal dist
def pdf_my_dist(miu, var, x):
    normal_part = npdf(miu, var, x) / math.sqrt(2*math.pi)
    uniform_part = 0.01
    return mix_ratio*normal_part + (1-mix_ratio) * uniform_part


def init_stat(trades, labels):
    label_set = set(labels)
    label_count = len(label_set)
    trades_count = len(trades)

    prior = {} # prior probability of each class
    # stat: label --> list; the sub_list has the conditional mean and var of the feature
    # stat[label][feature]: (mean, var) of feature conditioal on label
    stat = {} 
    sum = {} # a helper to get stat

    for label in label_set: 
        stat[label] = [[0.0, 0.0] for i in range(0, feature_count)]
        sum[label] = [0.0] * feature_count  

    for i in range(0, trades_count):
        trade = trades[i] 
        label = labels[i]
        prior[label] = 1 if not prior.has_key(label) else prior[label] + 1
        for feature in range(0, feature_count):
            stat[label][feature][0] += float(trade[feature])
            # get variance
            stat[label][feature][1] += float(trade[feature]) * float(trade[feature])
            sum[label][feature] += 1.0

    for label in stat:
        for feature in range(0, feature_count):
            # get mean
            stat[label][feature][0] = stat[label][feature][0] / sum[label][feature]
            mean = stat[label][feature][0]
            var = stat[label][feature][1]
            # variance is at least 0.25
            stat[label][feature][1] =  max(var / sum[label][feature] - mean*mean, 0.25)

    return (stat, prior)

def prediction(new_trades, stat, prior):
    label_count = len(prior)
    res = []
    for trade in new_trades:
        prob = 0 # log probablity
        max, idx = -1e100, ""
        tmp = []
        for label in prior:
            prob = math.log(prior[label])
            for f in range(feature_count):
                prob = prob + math.log( pdf_my_dist(stat[label][f][0], stat[label][f][1], trade[f]))
            if prob > max:
                idx = label
                max = prob    
            tmp.append(prob)
        res.append(idx)
    return res


def classify(trades, labels, new_trades):
    stat, prior = init_stat(trades, labels)
    res =  prediction(new_trades, stat,  prior)
    return res

ts = [
[99.0, 5.0, 20.0],
[95.0, 15.0, 10.0],
[5.0, 80.0, 40.0],
[3.0, 92.0, 20.0],
[60.0, 75.0, 10.0],
[50.0, 30.0, 60.0]]

ls=[
"green",
"green",
"red",
"red",
"blue",
"blue"]

ins=[
[90.0 ,10.0, 15.0],
[55.0, 40.0, 20.0],
[10.0, 98.0, 50.0]]



if __name__ == '__main__':
    pass
    #print classify(ts,ls,ins)
    #sys.exit(0)


import sys
def time_to_deliver(num_packages, delivery_sequence):
    grids = {} # grid name --> order information
    
    # change order number to int
    ids = [] 
    for s in delivery_sequence:
        order = s.strip().split('-')
        ids.append([order[0], int(order[1])])
    delivery_sequence = ids

    for order in delivery_sequence:
        if grids.has_key(order[0]):
            grids[order[0]][2].append(order[1])
        else:
            # for each grid, it stores ready time, order_pointer, order list;
            grids[order[0]] = [0, 0, [order[1]]] 

    timer = 0
    res = 0
    for order in delivery_sequence:
        grid_name = order[0]
        deliver_time = grids[grid_name][0]
        if deliver_time > timer:
            res += (deliver_time - timer + 1)
            timer = deliver_time + 1
        else:
            res += 1
            timer += 1

        grid_pointer = grids[grid_name][1]
        if grid_pointer < len(grids[grid_name][2]) - 1:
            transport_time = abs(grids[grid_name][2][grid_pointer + 1] - grids[grid_name][2][grid_pointer])
            grids[grid_name][0] = timer + transport_time
        grids[grid_name][1] += 1
    return res

#input=['aa-1','bb-3','aa-2','bb-6']
delivery_sequence=['aa-1','bb-1','bb-4','cc-5','aa-2','cc-7']
res,dt = time_to_deliver(6, delivery_sequence)
res





