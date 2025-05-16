#ifndef __CONSTANT_HPP__
#define __CONSTANT_HPP__

#include <stdio.h>

constexpr const char PRIMARY_PIECE_SYMBOL = 'P';
constexpr const char EXIT_SYMBOL = 'K';
constexpr const char WALL_SYMBOL = '#';
constexpr const char EMPTY_SYMBOL = '.';
constexpr const char* BOLD = "\033[1m";
constexpr const char* RESET = "\033[0m";
constexpr const char* RED = "\033[31m";     // P
constexpr const char* GREEN = "\033[32m";   // K
constexpr const char* YELLOW = "\033[33m";  // moved piece

#endif