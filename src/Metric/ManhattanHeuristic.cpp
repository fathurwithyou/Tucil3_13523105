#include "Metric/ManhattanHeuristic.hpp"

ManhattanHeuristic::ManhattanHeuristic() {}
ManhattanHeuristic::~ManhattanHeuristic() {}

int ManhattanHeuristic::evaluate(const Board& board) const {
  auto [exitX, exitY] = board.getExit();
  int primaryY = -1;
  int rightmostX = -1;
  for (int y = 0; y < board.getHeight(); ++y) {
    for (int x = 0; x < board.getWidth(); ++x) {
      if (board.getPosition(x, y) == 'P') {
        primaryY = y;
        rightmostX = std::max(rightmostX, x);
      }
    }
  }
  if (primaryY < 0) return 0;
  int h;
  if (primaryY == exitY) {
    h = std::abs(exitX - rightmostX);
  } else {
    h = std::abs(exitX - rightmostX) + std::abs(exitY - primaryY);
  }
  return h;
}
