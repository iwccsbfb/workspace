import Queue


class worker:
  def __init__(self, pnl_file = 'PNL'):
    self.portfolio = dict()
    self.prices = dict()
    self.cash = dict()
    self.pnl_file = pnl_file

  def work(self, q):
    out_file = open(self.pnl_file, 'w')
    msg = q.get().strip()
    count = 0
    while msg != 'finished':
      fields = msg.split()
      symbol = fields[2]
      if fields[0] == 'P': 
        self.prices[symbol] = float(fields[3])
        if self.prices.has_key(symbol) and self.portfolio.has_key(symbol) and self.cash.has_key(symbol):
          pnl = self.prices[symbol] * self.portfolio[symbol] + self.cash[symbol]
          line = 'PNL %s %s %s %s\n' % (fields[1], symbol, self.portfolio[symbol], pnl)
          count += 1; print 'PNL line %d' % count
          out_file.write(line)
        else: print "error for message: %s" % msg
      elif fields[0] == 'F':
        side, size, price = fields[5], float(fields[4]), float(fields[3])
        if side == 'S':
          if not self.portfolio.has_key(symbol): 
            self.portfolio[symbol] = 0
          self.portfolio[symbol] -= size
          if not self.cash.has_key(symbol): 
            self.cash[symbol] = 0
          self.cash[symbol] += size*price
        else: # side == 'B'
          if not self.portfolio.has_key(symbol): 
            self.portfolio[symbol] = 0
          self.portfolio[symbol] += size
          if not self.cash.has_key(symbol): 
            self.cash[symbol] = 0
          self.cash[symbol] -= size*price
      msg = q.get().strip()
    print 'worker done'

