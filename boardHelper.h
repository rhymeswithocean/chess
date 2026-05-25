#ifndef BOARDHELPER_H
#define BOARDHELPER_H
#include <string>
#include "piece.h"
using std::string;

/** Prints s to stdout with no newline appended. */
void print(const string& s);

/** Clears the terminal screen using ANSI escape codes. */
void clearBuf();

/** Clears the screen and prints whose turn it is, followed by the board. */
void boardRefresh(bool white);

/** Places all 32 pieces in their standard starting positions on the board. */
void setup();

/** Prints the current board state to stdout. */
void printBoard();

/**
 * Returns true if fmt is a valid move string (e.g. "e2e4" or "b7b8Q").
 * The first four characters must be source and destination in algebraic notation.
 * An optional fifth character specifies promotion: Q, r, b, or k.
 */
bool validFmt(string fmt);

/**
 * Parses a move string and writes the source (cX, cY) and destination (x, y)
 * board indices into the output parameters.
 */
void storeParsedCoords(string coord, int& cX, int& cY, int& x, int& y);

/**
 * Returns true if the piece at (x, y) belongs to the current player and
 * their king is not currently in check.
 */
bool isValidPieceToMove(bool white, int x, int y);

/**
 * Prompts the player to enter a move. Returns the move string on success,
 * or empty string if the input was invalid or leaves the king in check.
 * Accepts an optional fifth character for pawn promotion (e.g. "b7b8Q").
 */
string getMove(string msg);

/** Runs one full turn: prompts for a move and executes it. */
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
