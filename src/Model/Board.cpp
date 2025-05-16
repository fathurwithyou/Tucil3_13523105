#include "Model/Board.hpp"

Board::Board(int w, int h) : w_(w), h_(h) {
  exitX_ = -1;
  exitY_ = -1;
  board_.resize(h_, vector<char>(w_, WALL_SYMBOL));
}

Board::Board() : w_(0), h_(0), exitX_(-1), exitY_(-1) {}

Board::~Board() {}

void Board::setPosition(int x, int y, char c) {
  if (x < 0 || x >= static_cast<int>(w_) || y < 0 ||
      y >= static_cast<int>(h_)) {
    throw out_of_range("setPosition: Koordinat di luar batas papan.");
  }
  board_[y][x] = c;
}

char Board::getPosition(int x, int y) const {
  if (x < 0 || x >= static_cast<int>(w_) || y < 0 ||
      y >= static_cast<int>(h_)) {
    throw out_of_range("getPosition: Koordinat di luar batas papan.");
  }
  return board_[y][x];
}

void Board::print() const {
  for (const auto& row : board_) {
    for (char c : row) {
      cout << c;
    }
    cout << endl;
  }
}

bool Board::isSafe(int x, int y) const {
  return (x >= 0 && x < static_cast<int>(w_) && y >= 0 &&
          y < static_cast<int>(h_) &&
          (board_[y][x] == EMPTY_SYMBOL || board_[y][x] == EXIT_SYMBOL));
}

Board Board::clone() const {
  Board copy(w_, h_);
  copy.board_ = board_;
  copy.exitX_ = exitX_;
  copy.exitY_ = exitY_;
  for (int y = 0; y < h_; ++y) {
    for (int x = 0; x < w_; ++x) {
      copy.board_[y][x] = board_[y][x];
    }
  }

  return copy;
}

void Board::setExit(int x, int y) {
  exitX_ = x;
  exitY_ = y;
}

std::pair<int, int> Board::getExit() const { return {exitX_, exitY_}; }

void Board::printToStream(std::ostream& os) const {
  for (const auto& row : board_) {
    for (char c : row) os << c;
    os << '\n';
  }
}