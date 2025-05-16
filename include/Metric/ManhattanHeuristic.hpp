// ManhattanHeuristic.hpp
#ifndef __MANHATTAN_HEURISTIC_HPP__
#define __MANHATTAN_HEURISTIC_HPP__

#include <cstdlib>

#include "Metric/IHeuristic.hpp"
#include "Model/Board.hpp"

/**
 * Simple admissible heuristic: horizontal distance of primary car to exit.
 */
class ManhattanHeuristic : public IHeuristic {
 public:
  ManhattanHeuristic();
  ~ManhattanHeuristic();

  int evaluate(const Board& board) const override;
};

#endif  // __MANHATTAN_HEURISTIC_HPP__