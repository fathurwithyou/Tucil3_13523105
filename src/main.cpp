#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "Algorithm/AStar.hpp"
#include "Algorithm/BeamSearch.hpp"
#include "Algorithm/BestFirstSearch.hpp"
#include "Algorithm/UniformCostSearch.hpp"
#include "Metric/BlockingHeuristic.hpp"
#include "Metric/IHeuristic.hpp"
#include "Metric/ManhattanHeuristic.hpp"
#include "Model/FileProcessor.hpp"

void displayOpeningGimmick() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  std::cout << "\033[1;36m" << R"(
                                                                                
  _____           _        _    _                       
 |  __ \         | |      | |  | |                      
 | |__) |_   _ __| |__    | |__| | ___  _   _ _ __      
 |  _  /| | | / __| '_ \  |  __  |/ _ \| | | | '__|     
 | | \ \| |_| \__ \ | | | | |  | | (_) | |_| | |        
 |_|  \_\\__,_|___/_| |_| |_|  |_|\___/ \__,_|_|        
                                                        
   _____       _                                         
  / ____|     | |                                        
 | (___   ___ | |_   _____ _ __                          
  \___ \ / _ \| \ \ / / _ \ '__|                         
  ____) | (_) | |\ V /  __/ |                            
 |_____/ \___/|_| \_/ \___|_|                            
)" << "\033[0m"
            << std::endl;

  std::cout << "\033[1;33m" << R"(
                               _______________________
                              /|       ___           \
      _________              / |      /  /|           \
     /         \   _________/__|_____/  /_/__________  \
    /           \ |  _______           _______      ||  |
    |           | | |       |         |       |     ||  |
    |           | | |_______|         |_______|     ||  |
    |           |/|                                 ||  |
    \           \ |                                 ||  |
     \___________\|_________________________________||__|
                   |                                 |
                   |_________________________________|
                      (O)                     (O)
)" << "\033[0m"
            << std::endl;
}

int main() {
  displayOpeningGimmick();
  FileProcessor fileProcessor;
  Board board;
  std::vector<Piece> pieces;
  int algorithmChoice;
  int heuristicChoice;

  fileProcessor.load(board, pieces, algorithmChoice, heuristicChoice);

  std::unique_ptr<Algorithm> algorithm;
  std::shared_ptr<IHeuristic> heuristic;

  if (heuristicChoice == 1) {
    heuristic = std::make_shared<BlockingHeuristic>();
  } else if (heuristicChoice == 2) {
    heuristic = std::make_shared<ManhattanHeuristic>();
  }

  if (algorithmChoice == 1) {
    algorithm = std::make_unique<BestFirstSearch>(heuristic);
  } else if (algorithmChoice == 2) {
    algorithm = std::make_unique<UniformCostSearch>(heuristic);
  } else if (algorithmChoice == 3) {
    algorithm = std::make_unique<AStar>(heuristic);
  } else if (algorithmChoice == 4) {
    int beamWidth;
    std::cout << "Masukkan lebar beam: ";
    std::cin >> beamWidth;
    algorithm = std::make_unique<BeamSearch>(heuristic, beamWidth);
  }

  auto startClock = std::chrono::high_resolution_clock::now();
  State solution = algorithm->solve(board, pieces);
  auto endClock = std::chrono::high_resolution_clock::now();
  double timeMs =
      std::chrono::duration<double, std::milli>(endClock - startClock).count();

  const auto& pathSteps = solution.path;
  const auto& history = solution.history;
  int nodeCount = algorithm->getNodeVisitedCount();

  fileProcessor.save(pathSteps, history, timeMs, nodeCount);

  return 0;
}
