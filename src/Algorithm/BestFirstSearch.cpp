#include "Algorithm/BestFirstSearch.hpp"

BestFirstSearch::BestFirstSearch(std::shared_ptr<IHeuristic> h)
    : heuristic(h) {}

BestFirstSearch::~BestFirstSearch() {}

struct CompareHeuristic {
  bool operator()(const std::pair<State, int>& a,
                  const std::pair<State, int>& b) const {
    return a.second > b.second;
  }
};

State BestFirstSearch::solve(const Board& initialBoard,
                             const std::vector<Piece>& initialPieces) {
  startTimer();

  std::priority_queue<std::pair<State, int>, std::vector<std::pair<State, int>>,
                      CompareHeuristic>
      pq;
  std::unordered_set<std::string> visited;

  State start(initialBoard, initialPieces, {}, {});
  pq.push({start, heuristic->evaluate(initialBoard)});

  while (!pq.empty()) {
    auto [currentState, currentHeuristic] = pq.top();
    pq.pop();
    std::string key = currentState.serialize();

    if (visited.count(key)) continue;
    visited.insert(key);
    nodeVisitedCount++;

    if (isGoal(currentState)) {
      endTimer();
      printSolution(initialBoard, initialPieces, currentState);
      return currentState;
    }

    for (const State& nextState : expand(currentState)) {
      std::string nextKey = nextState.serialize();
      if (!visited.count(nextKey)) {
        pq.push({nextState, heuristic->evaluate(nextState.board)});
      }
    }
  }

  endTimer();
  printSolution(initialBoard, initialPieces, start);
  return State(initialBoard, initialPieces, {}, {});
}
