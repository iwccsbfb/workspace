import numpy as np 
from numpy.random import randn
from sklearn.tree import DecisionTreeRegressor
import matplotlib.pyplot as plt
from sklearn.cross_validation import cross_val_score
from sklearn import cross_validation
from sklearn.ensemble import RandomForestRegressor

def load_file(fname):
    xs = []
    ys = []
    fp= open(fname,"r")
    for l in fp:
        cols = [float(x) for x in l.strip().split(" ")]
        xcols = cols[0:-1]
        xs.append(xcols)	
        ys.append(cols[-1])
    return np.array(xs), np.array(ys)

if(__name__=="__main__"):
	# part 1
	x,y = load_file("train_input.txt")
	x_train, x_test, y_train, y_test = cross_validation.train_test_split(x, y, test_size=0.2, random_state=0)

	regre = DecisionTreeRegressor()
	regre.fit(x, y)
	print ("default DT score:",regre.score(x, y))

	# part2
	regre.fit(x_train, y_train)
	print ("default DT in sample score:",regre.score(x_train, y_train))
	print ("default DT out of sample score:",regre.score(x_test, y_test))

	# part 3
	params = np.array([ [8,7],[8,8],[8,9],[8,10],[8,11],[8,12],[8,13],[8,14],[8,15],
	    [9,7],[9,8],[9,9],[9,10],[9,11],[9,12],[9,13],[9,14],[9,15],[9,16],
	    [10,7],[10,8],[10,9],[10,10],[10,11],[10,12],[10,13],[10,14],[10,15],[10,16]])
	min_split = 25
	min_leaf=8
	for p in params:
		regre = DecisionTreeRegressor(max_depth=p[0], max_features=p[1],
		    min_samples_split=min_split, min_samples_leaf=min_leaf)
		print ("depth and feature:", p)
		scores = cross_val_score(regre, x, y, cv=10, random_state=0)
		print("score interval: %0.2f (+/- %0.2f)" % (scores.mean(), scores.std() * 2))
		regre.fit(x_train, y_train)
		print( "DT score:",regre.score(x_test, y_test))

