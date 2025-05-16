#ifndef __UNIFORM_COST_SEARCH_HPP__
#define __UNIFORM_COST_SEARCH_HPP__

#include "Algorithm/Algorithm.hpp"

/**
 * Uniform Cost Search for Rush Hour (unit step cost).
 * Equivalent to BFS on unit-cost graph.
 */
class UniformCostSearch : public Algorithm {
 public:
  UniformCostSearch(std::shared_ptr<IHeuristic> h);
  ~UniformCostSearch();

  State solve(const Board& board, const std::vector<Piece>& pieces) override;

 private:
  std::shared_ptr<IHeuristic> heuristic;
};

#endif  // __UNIFORM_COST_SEARCH_HPP__