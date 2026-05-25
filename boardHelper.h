#ifndef BOARDHELPER_H
#define BOARDHELPER_H
#include <string>
#include "piece.h"
using std::string;

/** Prints s to stdout with no newline appended. */
void print(const string& s);

/** Clears the terminal screen using ANSI escape codes. */
void clearBuf();

void boardRefresh(bool white);

/** Places all 32 pieces in their standard starting positions on the board. */
void setup();

/** Prints the current board state to stdout. */
void printBoard();

/** Returns true if loc is a valid algebraic coordinate (file a-h, rank 1-8). */
bool validLoc(string loc);

/** Parses an algebraic coordinate and writes the board indices into x and y. */
void storeParsedCoord(string coord, int& x, int& y);

/**
 * Returns true if the piece at (x, y) belongs to the current player and
 * their king is not currently in check.
 */
bool isValidPieceToMove(bool white, int x, int y);

/**
 * Prompts the current player to enter a destination square for the given piece.
 * Loops until a valid move for that piece is entered.
 */
string getMove(Piece* piece, string msg);

/** Runs one full turn: prompts for a piece and destination, then executes the move. */
void turn(bool white);

/**
 * Returns true if moving the piece at (fromX, fromY) to (toX, toY) would leave
 * that piece's king in check. Handles en passant captures correctly.
 */
bool leavesKingInCheck(int fromX, int fromY, int toX, int toY);

/**
 * Checks both kings for checkmate or stalemate.
 * On checkmate sets the global `winner` to the winning color ('w' or 'b').
 * On stalemate leaves `winner` unchanged.
 * Returns true if the game is over (either condition).
 */
bool gameOver();

#endif
