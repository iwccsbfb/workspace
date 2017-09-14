import numpy as np
from sklearn.tree import DecisionTreeRegressor
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

	min_split, min_leaf, max_depth, max_features = 25, 8, 9, 16
	num = 20
	scores = np.zeros((num))
	for i in range(num):
		X_sub, X_drop, y_sub, y_drop = cross_validation.train_test_split(
										x_train, y_train, test_size=0.2, random_state=i)
		regre2 = DecisionTreeRegressor(max_depth=max_depth, max_features=max_features,
									   min_samples_split=min_split, min_samples_leaf=min_leaf)
		regre2.fit(x_train, y_train)
		scores[i] = regre2.score(x_test, y_test)
	print ("mean score of %d random trees:"%num, np.mean(scores))

	#part 2
	print ("median score of %d random trees:"%num, np.median(scores))

	#part 3
	regre2 = RandomForestRegressor(max_depth=max_depth, max_features=max_features,
								   min_samples_split=min_split, min_samples_leaf=min_leaf)
	regre2.fit(x_train, y_train)
	print ("RandomForest score:",regre2.score(x_test, y_test))

