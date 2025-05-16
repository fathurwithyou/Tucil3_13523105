#include "Algorithm/Algorithm.hpp"

Algorithm::Algorithm() : nodeVisitedCount(0) {}

Algorithm::~Algorithm() {}

void Algorithm::startTimer() {
  startTime = std::chrono::high_resolution_clock::now();
}

void Algorithm::endTimer() {
  endTime = std::chrono::high_resolution_clock::now();
}

int Algorithm::getNodeVisitedCount() const { return nodeVisitedCount; }

double Algorithm::getExecutionTimeMs() const {
  return std::chrono::duration<double, std::milli>(endTime - startTime).count();
}

std::vector<State> Algorithm::expand(const State& currentState) {
  std::vector<State> neighbors;

  for (int i = 0; i < (int)currentState.pieces.size(); ++i) {
    const Piece& orig = currentState.pieces[i];
    auto dirs = (orig.getOrientation() == HORIZONTAL)
                    ? std::vector<std::pair<int, int>>{{-1, 0}, {1, 0}}
                    : std::vector<std::pair<int, int>>{{0, -1}, {0, 1}};

    for (auto [dx, dy] : dirs) {
      for (int step = 1;; ++step) {
        bool ok = true;
        for (auto [ex, ey] : orig.getEdgeCells(dx, dy)) {
          int tx = ex + dx * step;
          int ty = ey + dy * step;
          if (!currentState.board.isSafe(tx, ty) ||
              (currentState.board.getPosition(tx, ty) != '.' &&
               currentState.board.getPosition(tx, ty) != 'K')) {
            ok = false;
            break;
          }
        }
        if (!ok) break;

        Board newBoard = currentState.board.clone();
        auto newPieces = currentState.pieces;
        auto newPath = currentState.path;
        auto newHist = currentState.history;

        for (auto [ox, oy] : orig.getOccupiedCells())
          newBoard.setPosition(ox, oy, '.');

        Piece moved(orig);
        moved.setPosition(orig.getX() + dx * step, orig.getY() + dy * step);
        for (auto [nx, ny] : moved.getOccupiedCells())
          newBoard.setPosition(nx, ny, moved.getSymbol());

        std::stringstream ss;
        ss << orig.getSymbol() << '-';
        if (dx < 0)
          ss << "kiri";
        else if (dx > 0)
          ss << "kanan";
        else if (dy < 0)
          ss << "atas";
        else
          ss << "bawah";
        ss << step;

        newPath.push_back(ss.str());
        newHist.push_back(newBoard);

        newPieces[i] = moved;
        neighbors.emplace_back(newBoard, newPieces, newPath, newHist);
      }
    }
  }
  return neighbors;
}

bool Algorithm::isGoal(const State& state) {
  auto [ex, ey] = state.board.getExit();
  for (const Piece& p : state.pieces) {
    if (p.isPrimary()) {
      for (auto [x, y] : p.getOccupiedCells()) {
        if (x == ex && y == ey) return true;
      }
    }
  }
  return false;
}
void Algorithm::printSolution(const Board& initialBoard,
                              const std::vector<Piece>& initialPieces,
                              const State& goalState) {
  std::cout << "Solusi Ditemukan!" << std::endl;
  std::cout << "Papan Awal:" << std::endl;
  initialBoard.print(PRIMARY_PIECE_SYMBOL);

  Board temp = initialBoard.clone();
  auto pieces = initialPieces;
  for (size_t i = 0; i < goalState.path.size(); ++i) {
    const std::string& mv = goalState.path[i];

    char sym = mv[0];
    auto dashPos = mv.find('-');
    std::string dirAndCount = mv.substr(dashPos + 1);

    size_t idx = 0;
    while (idx < dirAndCount.size() && std::isalpha(dirAndCount[idx])) ++idx;
    std::string dir = dirAndCount.substr(0, idx);
    int stepCount = std::stoi(dirAndCount.substr(idx));

    int dx = 0, dy = 0;
    if (dir == "kiri")
      dx = -1;
    else if (dir == "kanan")
      dx = 1;
    else if (dir == "atas")
      dy = -1;
    else if (dir == "bawah")
      dy = 1;

    for (auto& pc : pieces) {
      if (pc.getSymbol() == sym) {
        for (auto [ox, oy] : pc.getOccupiedCells())
          temp.setPosition(ox, oy, '.');

        pc.setPosition(pc.getX() + dx * stepCount, pc.getY() + dy * stepCount);

        for (auto [nx, ny] : pc.getOccupiedCells())
          temp.setPosition(nx, ny, pc.getSymbol());
        break;
      }
    }

    std::cout << "\nLangkah " << i + 1 << ": " << mv << std::endl;
    temp.print(sym);
  }

  std::cout << "\nPapan Akhir:" << std::endl;
  temp.print(PRIMARY_PIECE_SYMBOL);

  std::cout << "\nTotal langkah: " << goalState.path.size() << std::endl;
  std::cout << "Total simpul dikunjungi: " << nodeVisitedCount
            << std::endl;
  std::cout << "Waktu eksekusi: " << getExecutionTimeMs() << " ms" << std::endl;
}

bool Algorithm::canMove(const Board& board, const Piece& piece, int dx,
                        int dy) {
  auto cells = piece.getOccupiedCells();
  int xCheck =
      (dx > 0 || dy > 0) ? cells.back().first + dx : cells.front().first + dx;
  int yCheck =
      (dx > 0 || dy > 0) ? cells.back().second + dy : cells.front().second + dy;
  if (!board.isSafe(xCheck, yCheck)) return false;

  char target = board.getPosition(xCheck, yCheck);
  return target == '.' || target == 'K';
}