#ifndef __BLOCKING_HEURISTIC_HPP__
#define __BLOCKING_HEURISTIC_HPP__

#include <algorithm>
#include <unordered_set>

#include "Metric/IHeuristic.hpp"
#include "Model/Board.hpp"

/**
 * Heuristic combining distance and count of direct blockers.
 */
class BlockingHeuristic : public IHeuristic {
 public:
  BlockingHeuristic();
  ~BlockingHeuristic();

  int evaluate(const Board& board) const override;
};

#endif  // __BLOCKING_HEURISTIC_HPP__