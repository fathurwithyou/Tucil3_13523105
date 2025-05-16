#ifndef __A_STAR_HPP__
#define __A_STAR_HPP__

#include "Algorithm/Algorithm.hpp"

class AStar : public Algorithm {
 public:
  AStar(std::shared_ptr<IHeuristic> h);
  ~AStar();

  State solve(const Board& board, const std::vector<Piece>& pieces) override;

 private:
  std::shared_ptr<IHeuristic> heuristic;
};

#endif
