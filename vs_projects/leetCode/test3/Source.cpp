#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>
#include <unordered_map>
using namespace std;

enum Side {BUY, SELL};
struct Trade {
  int time;
  string symbol;
  Side side;
  double price;
  long quantity;
  Trade(string &line) {
    vector<int> pos;
    // in total 4 commas
    for (int i = 0; i < line.size(); i++)
      if (line[i] == ',') 
        pos.push_back(i);
    time = std::stoi(line.substr(0, pos[0]));
    symbol = line.substr(pos[0] + 1, pos[1] - pos[0] - 1);
    if (line.substr(pos[1] + 1, pos[2] - pos[1] - 1) == "B")
      side = Side::BUY;
    else 
      side = Side::SELL;
    price = std::stod(line.substr(pos[2] + 1, pos[3] - pos[2] - 1));
    quantity = std::stol(line.substr(pos[3] + 1));
  }
};

char side_to_str(Side s) {
  if (s == Side::BUY) return 'B';
  else return 'S';
}

string get_pnl_string(Trade &open, Trade &close) {
  stringstream ss;
  auto quantity = min(open.quantity, close.quantity);
  auto pnl = quantity * (close.price - open.price);
  if (open.side == Side::SELL) 
    pnl = -pnl;
  ss.precision(2);
  ss << std::fixed << open.time << ',' << close.time << ',' << open.symbol << ',' << quantity
    << ',' << pnl << ',' << side_to_str(open.side) << ',' << side_to_str(close.side) << ','
    << open.price << ',' << close.price;
  return ss.str();
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    cerr << "format:  ./vatic_code_test [trade file]" << endl;
    return 1;
  }
  string file = argv[1];
  //string file = "input.txt"; // argv[1];
  ifstream ins(file);
  string line;
  getline(ins, line);
  unordered_map<string, queue<Trade>> m;

  cout << "OPEN_TIME,CLOSE_TIME,SYMBOL,QUANTITY,PNL,OPEN_SIDE,CLOSE_SIDE,OPEN_PRICE,CLOSE_PRICE" << endl;
  while (getline(ins, line)) {
    Trade trade(line);
    if(m.find(trade.symbol) == m.end())
      m[trade.symbol] = queue<Trade>();
    queue<Trade> &q = m[trade.symbol];
    if (q.empty()) q.push(trade);
    else if (q.front().side == trade.side)
      q.push(trade);
    // in cases below, generate pair(s)
    else {
      while (!q.empty() && trade.quantity > 0) {
        Trade & head = q.front();
        string pnl = get_pnl_string(head, trade);
        cout << pnl << endl;
        if (head.quantity <= trade.quantity) {
          trade.quantity -= head.quantity;
          q.pop();
        }
        else { // queue head has larger quantity
          trade.quantity = 0;
          head.quantity -= trade.quantity;
        }
      }
      if (trade.quantity != 0)
        q.push(trade);
    }
  }
  return 0;
}


