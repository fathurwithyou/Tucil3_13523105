#include "Metric/BlockingHeuristic.hpp"

#include <cmath>

BlockingHeuristic::BlockingHeuristic() {}
BlockingHeuristic::~BlockingHeuristic() {}

int BlockingHeuristic::evaluate(const Board& board) const {
  auto [exitX, exitY] = board.getExit();
  int width = board.getWidth();
  int height = board.getHeight();

  std::unordered_set<char> blockers;

  if (exitX == 0 || exitX == width - 1) {
    for (int x = 1; x < width - 1; ++x) {
      char c = board.getPosition(x, exitY);
      if (c != '.' && c != 'K' && c != 'P') blockers.insert(c);
    }
  }

  if (exitY == 0 || exitY == height - 1) {
    for (int y = 1; y < height - 1; ++y) {
      char c = board.getPosition(exitX, y);
      if (c != '.' && c != 'K' && c != 'P') blockers.insert(c);
    }
  }

  return static_cast<int>(blockers.size());
}