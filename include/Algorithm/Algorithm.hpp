#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include <chrono>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

#include "Metric/IHeuristic.hpp"
#include "Model/Board.hpp"
#include "Model/Piece.hpp"
#include "Model/State.hpp"

class Algorithm {
 public:
  Algorithm();
  virtual ~Algorithm();

  virtual State solve(const Board& board, const std::vector<Piece>& pieces) = 0;

  int getNodeVisitedCount() const;
  double getExecutionTimeMs() const;

 protected:
  int nodeVisitedCount;
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::high_resolution_clock::time_point endTime;

  void startTimer();
  void endTimer();
  void reconstructPath();
  bool isGoal(const State& state);
  void printSolution(const Board& initialBoard,
                     const std::vector<Piece>& initialPieces,
                     const State& goalState);
  std::vector<State> expand(const State& currentState);
  bool canMove(const Board& board, const Piece& piece, int dx, int dy);
};

#endif  // __ALGORITHM_HPP__
