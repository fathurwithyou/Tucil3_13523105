#include "Model/FileProcessor.hpp"

#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

FileProcessor::FileProcessor() {}

FileProcessor::~FileProcessor() {}

void FileProcessor::load(Board& board, std::vector<Piece>& pieces,
                         int& algorithmChoice, int& heuristicChoice) {
  string filePath;
  cout << "Masukkan nama file input (dalam folder test/input/): ";
  cin >> filePath;

  cout << "Pilih Algoritma Pathfinding:\n";
  cout << "1. Greedy Best First Search\n";
  cout << "2. Uniform Cost Search\n";
  cout << "3. A* Search\n";
  do {
    cout << "Pilihan Anda (1-3): ";
    cin >> algorithmChoice;
  } while (algorithmChoice < 1 || algorithmChoice > 3);

  cout << "Pilih Heuristik:\n";
  cout << "1. Blocking Heuristic\n";
  cout << "2. Manhattan Heuristic\n";
  do {
    cout << "Pilihan Anda (1-2): ";
    cin >> heuristicChoice;
  } while (heuristicChoice < 1 || heuristicChoice > 2);

  loadFromFile(filePath, board, pieces);
}

void FileProcessor::loadFromFile(const std::string& fileName, Board& board,
                                 std::vector<Piece>& pieces) {
  ifstream file("test/input/" + fileName);
  if (!file.is_open()) {
    cerr << "Gagal membuka file: test/input/" << fileName << endl;
    exit(1);
  }
  int height, width, pieceCount;
  file >> height >> width;
  file.ignore();
  board = Board(width + 2, height + 2);
  file >> pieceCount;
  file.ignore();

  vector<string> lines;
  string line;

  while (getline(file, line)) {
    line = trim(line);
    if (line.empty()) continue;
    lines.push_back(line);
  }

  if ((int)lines.size() > height) {
    auto pos = lines[0].find('K');
    if (pos != string::npos) {
      board.setExit(pos + 1, 0);
      lines.erase(lines.begin());
    } else {
      auto pos = lines.back().find('K');
      board.setExit(pos + 1, height + 1);
      lines.pop_back();
    }
  } else {
    int i = 0;
    while (i < (int)lines.size() && (int)lines[i].size() == width) {
      i++;
    }
    if (lines[i][0] == 'K') {
      board.setExit(0, i + 1);
      lines[i].erase(lines[i].begin());
    } else {
      board.setExit(width + 1, i + 1);
      lines[i].erase(lines[i].end() - 1);
    }
  }

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      char c = lines[y][x];
      board.setPosition(x + 1, y + 1, c);
    }
  }

  unordered_map<char, vector<pair<int, int>>> piecePositions;
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      char c = lines[y][x];
      if (c != '.' && c != 'K') {
        piecePositions[c].emplace_back(x + 1, y + 1);
      }
    }
  }

  for (const auto& [symbol, coords] : piecePositions) {
    if (coords.size() < 1) continue;
    bool isPrimary = (symbol == 'P');

    int x0 = coords[0].first;
    int y0 = coords[0].second;
    int length = coords.size();

    Orientation orientation = (length > 1 && coords[0].first == coords[1].first)
                                  ? VERTICAL
                                  : HORIZONTAL;

    pieces.emplace_back(Piece(symbol, x0, y0, length, orientation, isPrimary));
  }

  board.setPosition(board.getExit().first, board.getExit().second, 'K');

  file.close();
}

void FileProcessor::save(const std::vector<std::string>& moveLog,
                         const std::vector<Board>& history, double time,
                         int nodes, const std::string& fileName) {
  saveToFile(fileName, history, moveLog, time, nodes);
}

void FileProcessor::saveToFile(const std::string& fileName,
                               const std::vector<Board>& history,
                               const std::vector<std::string>& moveLog,
                               double time, int nodes) {
  ofstream file("test/output/" + fileName);
  if (!file.is_open()) {
    cerr << "Gagal menyimpan ke file: test/output/" << fileName << endl;
    return;
  }

  file << "Total gerakan: " << moveLog.size() << endl;
  file << "Node dikunjungi: " << nodes << endl;
  file << "Waktu eksekusi: " << time << " ms\n\n";

  for (int i = 0; i < (int)moveLog.size(); ++i) {
    file << "Langkah " << i + 1 << ": " << moveLog[i] << endl;
    const Board& b = history[i];
    for (int y = 0; y < b.getHeight(); ++y) {
      for (int x = 0; x < b.getWidth(); ++x) {
        file << b.getPosition(x, y);
      }
      file << '\n';
    }
    file << '\n';
  }

  file.close();
}
