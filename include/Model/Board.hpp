#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Constant.hpp"

using namespace std;

class Board {
 public:
  Board(int, int);
  Board();
  ~Board();

  void setPosition(int x, int y, char c);
  char getPosition(int x, int y) const;
  int getWidth() const { return w_; }
  int getHeight() const { return h_; }

  void print() const;
  bool isSafe(int x, int y) const;
  Board clone() const;
  void setExit(int, int);
  std::pair<int, int> getExit() const;
  void printToStream(std::ostream& os) const;

 private:
  int w_, h_;
  int exitX_, exitY_;
  std::vector<std::vector<char>> board_;
};

#endif  // __BOARD_HPP__
