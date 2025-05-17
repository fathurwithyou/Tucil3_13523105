#include "Algorithm/BeamSearch.hpp"

BeamSearch::BeamSearch(std::shared_ptr<IHeuristic> h, int beamWidth)
    : heuristic(h), beamWidth_(beamWidth) {}

BeamSearch::~BeamSearch() {}

struct CompareHeuristic {
  bool operator()(const std::pair<State, int>& a,
                  const std::pair<State, int>& b) const {
    return a.second > b.second;
  }
};

State BeamSearch::solve(const Board& initialBoard,
                        const std::vector<Piece>& initialPieces) {
  startTimer();

  std::vector<std::pair<State, int>> currentLevel;
  std::unordered_set<std::string> visited;

  State start(initialBoard, initialPieces, {}, {});
  int h0 = heuristic->evaluate(initialBoard);
  currentLevel.push_back({start, h0});
  visited.insert(start.serialize());

  while (!currentLevel.empty()) {
    std::vector<std::pair<State, int>> nextLevel;

    for (auto& [currentState, currentHeuristic] : currentLevel) {
      nodeVisitedCount++;
      if (isGoal(currentState)) {
        endTimer();
        printSolution(initialBoard, initialPieces, currentState);
        return currentState;
      }

      auto neighbors = expand(currentState);
      for (auto& nxt : neighbors) {
        std::string key = nxt.serialize();
        if (visited.count(key) == 0) {
          int h = heuristic->evaluate(nxt.board);
          nextLevel.emplace_back(nxt, h);
          visited.insert(key);
        }
      }
    }

    if ((int)nextLevel.size() > beamWidth_) {
      std::nth_element(
          nextLevel.begin(), nextLevel.begin() + beamWidth_, nextLevel.end(),
          [](const auto& a, const auto& b) { return a.second < b.second; });
      nextLevel.resize(beamWidth_, nextLevel[beamWidth_]);
    }

    currentLevel = std::move(nextLevel);
  }

  endTimer();
  printSolution(initialBoard, initialPieces, start);
  return State(initialBoard, initialPieces, {}, {});
}
