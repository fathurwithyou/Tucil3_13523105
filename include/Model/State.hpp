#ifndef __STATE_HPP__
#define __STATE_HPP__

#include <string>
#include <vector>

#include "Model/Board.hpp"
#include "Model/Piece.hpp"

struct State {
  Board board;
  std::vector<Piece> pieces;
  std::vector<std::string> path;
  std::vector<Board> history;

  State(const Board& b, const std::vector<Piece>& p,
        const std::vector<std::string>& moves,
        const std::vector<Board>& hist_ = {})
      : board(b.clone()), pieces(p), path(moves), history(hist_) {}

  std::string serialize() const;
};

#endif
