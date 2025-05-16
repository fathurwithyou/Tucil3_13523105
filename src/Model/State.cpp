#include "Model/State.hpp"

std::string State::serialize() const {
  std::string result = "";
  for (int y = 1; y < board.getHeight(); ++y) {
    for (int x = 1; x < board.getWidth(); ++x) {
      result += board.getPosition(x, y);
    }
  }
  return result;
}
