#include "Algorithm/AStar.hpp"

AStar::AStar(std::shared_ptr<IHeuristic> h) : heuristic(h) {}

AStar::~AStar() {}

struct CompareF {
  bool operator()(const std::pair<State, int>& a,
                  const std::pair<State, int>& b) const {
    int fa = (int)a.first.path.size() + a.second;
    int fb = (int)b.first.path.size() + b.second;
    return fa > fb;
  }
};

State AStar::solve(const Board& initialBoard,
                   const std::vector<Piece>& initialPieces) {
  startTimer();

  std::priority_queue<std::pair<State, int>, std::vector<std::pair<State, int>>,
                      CompareF>
      open;

  std::unordered_map<std::string, int> bestG;
  State start(initialBoard, initialPieces, {}, {});
  open.push({start, heuristic->evaluate(initialBoard)});
  bestG[start.serialize()] = 0;

  while (!open.empty()) {
    auto [cur, h] = open.top();
    open.pop();
    std::string key = cur.serialize();
    int g = (int)cur.path.size();
    nodeVisitedCount++;

    if (bestG[key] < g) continue;

    if (isGoal(cur)) {
      endTimer();
      printSolution(initialBoard, initialPieces, cur);
      return cur;
    }

    auto neighbors = expand(cur);
    for (auto& nxt : neighbors) {
      std::string sk = nxt.serialize();
      int ng = (int)nxt.path.size();

      if (!bestG.count(sk) || ng < bestG[sk]) {
        bestG[sk] = ng;
        int hn = heuristic->evaluate(nxt.board);
        open.push({nxt, hn});
      }
    }
  }

  endTimer();
  printSolution(initialBoard, initialPieces, start);
  return State(initialBoard, initialPieces, {}, {});
}
