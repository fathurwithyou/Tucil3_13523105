#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include <string>
#include <vector>

enum Orientation { HORIZONTAL, VERTICAL };

class Piece {
 public:
  Piece(char symbol, int x, int y, int length, Orientation orientation,
        bool isPrimary);
  ~Piece();

  char getSymbol() const;
  int getX() const;
  int getY() const;
  int getLength() const;
  Orientation getOrientation() const;
  bool isPrimary() const;

  void setPosition(int x, int y);
  // int getWidth() const { return w_; }
  // int getHeight() const { return h_; }

  std::vector<std::pair<int, int>> getOccupiedCells() const;
  std::vector<std::pair<int, int>> getEdgeCells(int dx, int dy) const;

 private:
  char symbol;
  int x, y;
  int length;
  Orientation orientation;
  bool primary;
};

#endif
