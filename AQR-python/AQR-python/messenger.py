import Queue

class messenger:
  def __init__(self, fill_file = 'fills', prices_file = 'prices'):
    self.fill_file = fill_file
    self.prices_file = prices_file
  # example:  
  #  input: F 1388534472953 MSFT 42.93 300 S
  #  output: 1388534472953
  def get_time(self, s):
    return int(s.strip().split()[1])

  # message generator
  def all_data(self):
    reader1 = open(self.fill_file, "r")
    reader2 = open(self.prices_file, "r")
    line1 = reader1.readline()
    line2 = reader2.readline()

    while line1.strip() != '' or line2.strip() != '':
      if line1.strip() == '':
        yield line2; line2 = reader2.readline()
      elif line2.strip() == '':
        yield line1; line1 = reader1.readline()
      else:
        t1, t2 = self.get_time(line1), self.get_time(line2)
        # yield message by time order. If fill and prices messages have the same time, yield fill message first
        if(t2 < t1): 
          yield line2; line2 = reader2.readline()
        else: 
          yield line1; line1 = reader1.readline()
    reader1.close()
    reader2.close()

  def send(self, q):
    for msg in self.all_data():
      q.put(msg)
    q.put('finished')
    print 'finished sending'



