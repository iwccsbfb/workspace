import threading
from messenger import messenger
from worker import worker
from Queue import Queue


if __name__ == '__main__':
  # thread-safe Queue. If maxsize reached, messenger will be blocked. 
  # On the other hand, if empty, worker will be blocked. 
  q = Queue()
  t1 = threading.Thread(target=messenger().send, args=(q,))
  t2 = threading.Thread(target=worker().work, args=(q,))
  t1.start()
  t2.start()
