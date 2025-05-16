#ifndef __FILE_PROCESSOR_HPP__
#define __FILE_PROCESSOR_HPP__

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "Board.hpp"
#include "Piece.hpp"

class FileProcessor {
 public:
  FileProcessor();
  ~FileProcessor();

  void load(Board& board, std::vector<Piece>& pieces, int& algorithmChoice,
            int& heuristicChoice);
  void loadFromFile(const std::string& fileName, Board& board,
                    std::vector<Piece>& pieces);

  void save(const std::vector<std::string>& moveLog,
            const std::vector<Board>& history, double time, int nodes,
            const std::string& fileName);
  void saveToFile(const std::string& fileName,
                  const std::vector<Board>& history,
                  const std::vector<std::string>& moveLog, double time,
                  int nodes);

 private:
  std::string ltrim(const std::string& s) {
    return std::string(
        std::find_if(s.begin(), s.end(),
                     [](unsigned char ch) { return !std::isspace(ch); }),
        s.end());
  }

  std::string rtrim(const std::string& s) {
    return std::string(s.begin(),
                       std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                         return !std::isspace(ch);
                       }).base());
  }

  std::string trim(const std::string& s) { return rtrim(s); }
};

#endif
