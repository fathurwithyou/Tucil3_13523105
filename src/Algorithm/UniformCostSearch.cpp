#include "Algorithm/UniformCostSearch.hpp"

struct CompareG {
  bool operator()(const std::pair<State, int>& a,
                  const std::pair<State, int>& b) const {
    return ((int)a.first.path.size()) > ((int)b.first.path.size());
  }
};

UniformCostSearch::UniformCostSearch(std::shared_ptr<IHeuristic> h)
    : heuristic(h) {}
UniformCostSearch::~UniformCostSearch() {}

State UniformCostSearch::solve(const Board& initialBoard,
                               const std::vector<Piece>& initialPieces) {
  startTimer();

  std::priority_queue<std::pair<State, int>, std::vector<std::pair<State, int>>,
                      CompareG>
      pq;
  std::unordered_set<std::string> visited;

  State start(initialBoard, initialPieces, {}, {});
  pq.push({start, 0});

  while (!pq.empty()) {
    auto [current, g] = pq.top();
    pq.pop();
    std::string key = current.serialize();
    if (visited.count(key)) continue;
    visited.insert(key);
    nodeVisitedCount++;

    if (isGoal(current)) {
      endTimer();
      printSolution(initialBoard, initialPieces, current);
      return current;
    }

    auto neighbors = expand(current);
    for (const State& nxt : neighbors) {
      std::string nk = nxt.serialize();
      if (!visited.count(nk)) {
        pq.push({nxt, (int)nxt.path.size()});
      }
    }
  }

  std::cout << "Tidak ditemukan solusi." << std::endl;
  endTimer();
  return State(initialBoard, initialPieces, {}, {});
}