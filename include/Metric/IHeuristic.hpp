
#ifndef __I_HEURISTIC_HPP__
#define __I_HEURISTIC_HPP__

#include "Model/Board.hpp"

/**
 * Interface for heuristic function h(n) estimating cost-to-goal.
 * Must be admissible (never overestimate true cost).
 */
class IHeuristic {
 public:
  virtual ~IHeuristic() {}
  /**
   * Estimate cost from board state to goal.
   * @param board Current board configuration
   * @return Non-negative integer estimate h(n)
   */
  virtual int evaluate(const Board& board) const = 0;
};

#endif