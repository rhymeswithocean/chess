#pragma once
#include <string>
#include <ostream>
using std::string;

/**
 * Abstract base class representing a chess piece.
 * Stores the piece's color and shorthand symbol, and provides shared
 * utilities used by all concrete piece types.
 */
class Piece {
public:
    /**
     * @param color     'w' for white, 'b' for black
     * @param shorthand single character identifying the piece type (e.g. 'K', 'p')
     */
    Piece(char color, char shorthand);

    /**
     * Moves the piece to (x, y) on the board.
     * @pre isValidMove(x, y) returns true
     */
    virtual void move(int x, int y);

    /**
     * Returns true if moving this piece to (x, y) is a legal chess move.
     * Does not check for check/checkmate — only piece-specific movement rules.
     */
    virtual bool isValidMove(int x, int y) = 0;

    virtual ~Piece() = default;

    /**
     * Returns a 2-character string: color followed by shorthand (e.g. "wK", "bp").
     */
    string toString() const;

    /**
     * Scans the board to locate this piece and writes its coordinates into x and y.
     */
    void storeCurrentPos(int& x, int& y);

    /**
     * Enables writing a Piece directly to an output stream via <<, using toString().
     */
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);

    /**
     * Returns 'w' for white or 'b' for black.
     */
    char getColor() { return color; }
    /** Returns true if this piece has moved at least once this game. */
    bool getHasMoved() { return hasMoved; }
    /** Returns the single character identifying this piece type (e.g. 'K', 'r', 'p'). */
    char getShorthand() { return shorthand; }

    /**
     * Returns true if this piece can capture whatever is at (x, y).
     * Returns false if the target square holds a friendly piece or is empty.
     */
    bool canTake(int x, int y);

    /**
     * Returns true if square (x, y) is not under attack by any enemy piece.
     * Uses this piece's color to determine which pieces are enemies.
     */
    bool isSafe(int x, int y);

protected:
    char color;
    char shorthand;
    bool hasMoved = false;
};

extern Piece* board[8][8];

/**
 * Returns true if any piece blocks the path between (cX, cY) and (x, y).
 * Only valid for straight or diagonal paths.
 */
bool willHit(int x, int y, int cX, int cY);
