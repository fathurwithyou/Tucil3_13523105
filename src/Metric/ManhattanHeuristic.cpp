#include "Metric/ManhattanHeuristic.hpp"

ManhattanHeuristic::ManhattanHeuristic() {}
ManhattanHeuristic::~ManhattanHeuristic() {}

int ManhattanHeuristic::evaluate(const Board& board) const {
  auto [exitX, exitY] = board.getExit();

  int minX = board.getWidth(), maxX = -1;
  int minY = board.getHeight(), maxY = -1;

  for (int y = 0; y < board.getHeight(); ++y) {
    for (int x = 0; x < board.getWidth(); ++x) {
      if (board.getPosition(x, y) == 'P') {
        minX = std::min(minX, x);
        maxX = std::max(maxX, x);
        minY = std::min(minY, y);
        maxY = std::max(maxY, y);
      }
    }
  }

  if (maxX == -1 || maxY == -1) return 0;

  int dx = 0, dy = 0;
  if (exitX < minX)
    dx = minX - exitX;
  else if (exitX > maxX)
    dx = exitX - maxX;

  if (exitY < minY)
    dy = minY - exitY;
  else if (exitY > maxY)
    dy = exitY - maxY;

  return dx + dy;
}
