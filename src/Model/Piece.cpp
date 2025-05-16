#include "Model/Piece.hpp"

Piece::Piece(char symbol, int x, int y, int length, Orientation orientation,
             bool isPrimary)
    : symbol(symbol),
      x(x),
      y(y),
      length(length),
      orientation(orientation),
      primary(isPrimary) {}

Piece::~Piece() {}

char Piece::getSymbol() const { return symbol; }

int Piece::getX() const { return x; }

int Piece::getY() const { return y; }

int Piece::getLength() const { return length; }

Orientation Piece::getOrientation() const { return orientation; }

bool Piece::isPrimary() const { return primary; }

void Piece::setPosition(int newX, int newY) {
  x = newX;
  y = newY;
}

std::vector<std::pair<int, int>> Piece::getOccupiedCells() const {
  std::vector<std::pair<int, int>> cells;
  for (int i = 0; i < length; ++i) {
    if (orientation == HORIZONTAL) {
      cells.emplace_back(x + i, y);
    } else {
      cells.emplace_back(x, y + i);
    }
  }
  return cells;
}

std::vector<std::pair<int, int>> Piece::getEdgeCells(int dx, int dy) const {
  std::vector<std::pair<int, int>> edges;
  if (orientation == HORIZONTAL) {
    int edgeX = (dx > 0) ? (x + length - 1) : x;
    edges.emplace_back(edgeX, y);
  } else {
    int edgeY = (dy > 0) ? (y + length - 1) : y;
    edges.emplace_back(x, edgeY);
  }
  return edges;
}
