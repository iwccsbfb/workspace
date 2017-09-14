import keras
import numpy as np
from sklearn import cross_validation
from keras.models import Sequential
from keras.layers.core import Dense, Dropout
from keras.optimizers import SGD
from keras.regularizers import l1

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

def norm_input(mat, idx):
    mat[:,idx] = (mat[:,idx] - np.mean(mat[:,idx],axis=0)) / np.std(mat[:,idx], axis=0)

def get_r_squared(y_pred, y_test):
	u = np.linalg.norm(y_pred - y_test)
	v = np.var(y_test)*len(y_test)
	return 1.0 - u/v

def neural_network(X_train, y_train, X_test, y_test, lr, width_all, nb_epoch, batch_size, wl11, wl12):
    sgd=keras.optimizers.Adadelta(lr, rho=0.95, epsilon=1e-06)
    model = Sequential()
    model.add(Dense(width_all[1], input_dim=width_all[0], activation='relu',W_regularizer=l1(l=wl11)))
    model.add(Dropout(0.5))
    model.add(Dense(width_all[2], activation='relu',W_regularizer=l1(l=wl12)))
    model.add(Dropout(0.5))
    model.add(Dense(1,  activation='linear'))
    model.compile(loss='mse', optimizer=sgd)
    model.fit(X_train, y_train, nb_epoch=nb_epoch,verbose=1, batch_size=batch_size, show_accuracy=True)
    score = model.evaluate(X_test, y_test, batch_size=batch_size, verbose=1)
    print score
    y_pred = model.predict(X_test, batch_size=batch_size)
    res = get_r_squared(y_pred, y_test)
    print ("R squared is:", res)


if(__name__=="__main__"):
	x,y = load_file("train_input.txt")
	norm_input(x, [0,1])
	x_train, x_test, y_train, y_test = cross_validation.train_test_split(x, y, test_size=0.2, random_state=0)
	#part 1
	lr, nb_epoch, batch_size=0.1, 18, 200
	indim = (x.shape)[1]
	neural_network(x_train, y_train, x_test, y_test, lr, [indim, indim, indim], nb_epoch, batch_size, 3,3)

	#part 2
	lr, nb_epoch, batch_size=0.1, 18, 200
	neural_network(x_train, y_train, x_test, y_test, lr, [indim, 250, 250], nb_epoch, batch_size, 4,4)

	#part 3
	x,y = load_file("train_input.txt")
	norm_input(x, [0,1])
	x_train, x_test, y_train, y_test = cross_validation.train_test_split(x, y, test_size=0.2, random_state=0)

	lr, nb_epoch, batch_size=0.1, 20, 200
	indim = (x.shape)[1]
	neural_network(x_train, y_train, x_test, y_test, lr, [indim, indim, indim], nb_epoch, batch_size, 2.5,2.5)