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
  cout << "4. Beam Search\n";
  do {
    cout << "Pilihan Anda (1-4): ";
    cin >> algorithmChoice;
  } while (algorithmChoice < 1 || algorithmChoice > 4);

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
  try {
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
        if (pos == string::npos) {
          throw std::runtime_error("Tidak ada posisi keluar yang ditemukan");
        }
        board.setExit(pos + 1, height + 1);
        lines.pop_back();
      }
    } else {
      int i = 0;
      while (i < (int)lines.size() && (int)lines[i].size() == width) {
        i++;
      }
      if (i == (int)lines.size()) {
        throw std::runtime_error("Tidak ada posisi keluar yang ditemukan");
      }
      if (lines[i][0] == 'K') {
        board.setExit(0, i + 1);
        lines[i].erase(lines[i].begin());
      } else {
        board.setExit(width + 1, i + 1);
        lines[i].erase(lines[i].end() - 1);
      }
    }
    if ((int)lines.size() != height) {
      throw std::runtime_error("Jumlah baris tidak sesuai dengan tinggi papan");
    }

    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if ((int)lines[y].size() != width) {
          throw std::out_of_range(
              "Jumlah kolom tidak sesuai dengan lebar papan");
        }
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

      Orientation orientation =
          (length > 1 && coords[0].first == coords[1].first) ? VERTICAL
                                                             : HORIZONTAL;

      pieces.emplace_back(
          Piece(symbol, x0, y0, length, orientation, isPrimary));
    }

    board.setPosition(board.getExit().first, board.getExit().second, 'K');

    file.close();
  } catch (const std::exception& e) {
    std::cerr << "Error saat memproses file: " << fileName << endl;
    std::cerr << "Pastikan format file sesuai dengan yang diharapkan.\n";
    std::cerr << e.what() << '\n';
    exit(1);
  }
}

void FileProcessor::save(const std::vector<std::string>& moveLog,
                         const std::vector<Board>& history, double time,
                         int nodes) {
  std::string outputName;
  std::cout << "Simpan hasil sebagai (mis. hasil1.txt): ";
  std::cin >> outputName;

  ofstream file("test/output/" + outputName);
  if (!file.is_open()) {
    cerr << "Gagal menyimpan ke file: test/output/" << outputName << endl;
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

  cout << "Hasil disimpan di: test/output/" << outputName << endl;
}
