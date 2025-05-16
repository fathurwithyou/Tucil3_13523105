#include "Metric/BlockingHeuristic.hpp"

#include <cmath>

BlockingHeuristic::BlockingHeuristic() {}
BlockingHeuristic::~BlockingHeuristic() {}

int BlockingHeuristic::evaluate(const Board& board) const {
  auto [exitX, exitY] = board.getExit();
  int primaryY = -1;
  int rightmostX = -1;
  int height = board.getHeight();
  int width = board.getWidth();

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      if (board.getPosition(x, y) == 'P') {
        if (primaryY < 0) primaryY = y;
        rightmostX = std::max(rightmostX, x);
      }
    }
  }
  if (primaryY < 0) return 0;

  int h = 0;
  if (primaryY == exitY) {
    int dist = std::abs(exitX - rightmostX);
    h += dist;

    std::unordered_set<char> blockers;
    int start = std::min(rightmostX + 1, exitX);
    // int end = std::max(rightmostX + 1, exitX);
    for (int x = start; x < exitX; ++x) {
      char c = board.getPosition(x, primaryY);
      if (c != '.' && c != 'K') blockers.insert(c);
    }
    h += static_cast<int>(blockers.size());
  } else {
    h = std::abs(exitX - rightmostX) + std::abs(exitY - primaryY);
  }
  return h;
}