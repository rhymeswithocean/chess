#pragma once
#include <string>
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
    virtual void move(int x, int y) = 0;

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

    /**
     * Returns true if this piece can capture whatever is at (x, y).
     * Returns false if the target square holds a friendly piece or is empty.
     */
    bool canTake(int x, int y);

protected:
    char color;      // 'w' or 'b'
    char shorthand;  // single character identifying piece type
};

/**
 * King — moves exactly 1 square in any direction.
 */
class King : public Piece {
public:
    King(char color) : Piece(color, 'K') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

/**
 * Queen — moves any number of squares diagonally or in a straight line.
 */
class Queen : public Piece {
public:
    Queen(char color) : Piece(color, 'Q') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

/**
 * Rook — moves any number of squares horizontally or vertically.
 */
class Rook : public Piece {
public:
    Rook(char color) : Piece(color, 'r') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

/**
 * Bishop — moves any number of squares diagonally.
 */
class Bishop : public Piece {
public:
    Bishop(char color) : Piece(color, 'b') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

/**
 * Knight — moves in an L-shape: 2 squares in one axis and 1 in the other.
 * The only piece that can jump over other pieces.
 */
class Knight : public Piece {
public:
    Knight(char color) : Piece(color, 'k') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

/**
 * Pawn — moves 1 square forward, or 2 squares forward from its starting row.
 * Captures diagonally 1 square forward. Cannot capture on a forward move.
 * White moves toward lower row indices; black moves toward higher row indices.
 */
class Pawn : public Piece {
public:
    Pawn(char color) : Piece(color, 'p') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};
