#ifndef __BEAM_SEARCH_HPP__
#define __BEAM_SEARCH_HPP__

#include "Algorithm/Algorithm.hpp"

class BeamSearch : public Algorithm {
 public:
  BeamSearch(std::shared_ptr<IHeuristic> h, int beamWidth);
  ~BeamSearch();

  State solve(const Board& board, const std::vector<Piece>& pieces) override;

 private:
  std::shared_ptr<IHeuristic> heuristic;
  int beamWidth_;
};

#endif
