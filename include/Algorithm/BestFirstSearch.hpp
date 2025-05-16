#ifndef __BEST_FIRST_SEARCH_HPP__
#define __BEST_FIRST_SEARCH_HPP__


#include "Algorithm/Algorithm.hpp"

class BestFirstSearch : public Algorithm {
 public:
  BestFirstSearch(std::shared_ptr<IHeuristic> h);
  ~BestFirstSearch();

  State solve(const Board& board, const std::vector<Piece>& pieces) override;

 private:
  std::shared_ptr<IHeuristic> heuristic;
};

#endif  // __BEST_FIRST_SEARCH_HPP__
