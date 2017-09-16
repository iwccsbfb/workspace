from messenger import messenger
from worker import worker
from Queue import Queue

if __name__ == '__main__':
  q = Queue()
  messenger(fill_file = 'test/fills', prices_file = 'test/prices').send(q)
  worker(pnl_file='test/PNL').work(q)
  with open('test/PNL', 'r') as f:
    assert f.readline().strip() == "PNL 1388534400000 MSFT 300.0 0.0"
    assert f.readline().strip() == "PNL 1388534400000 AAPL 300.0 0.0"
    assert f.readline().strip() == ""
  
