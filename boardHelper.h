#ifndef BOARDHELPER_H
#define BOARDHELPER_H
#include <string>
using std::string;

/**
 * Prints s to stdout with no newline appended.
 */
void print(const string& s);

/**
 * Clears the terminal screen using ANSI escape codes.
 */
void clearBuf();

/**
 * Places all 32 pieces in their standard starting positions on the board.
 * Must be called once before any game logic runs.
 */
void setup();

/**
 * Prints the current board state to stdout.
 * Each occupied square shows a 2-character piece label (e.g. "wK"); empty squares show "..".
 */
void printBoard();

#endif
