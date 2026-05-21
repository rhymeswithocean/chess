#pragma once
#include <string>
using std::string;

class Piece {
public:
    Piece(char color, char shorthand);
    virtual void move(int x, int y) = 0;
    virtual bool isValidMove(int x, int y) = 0;
    virtual ~Piece() = default;
    string toString() const;
    void storeCurrentPos(int& x, int& y);
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);
    char getColor() { return color; }
    bool canTake(int x, int y);

protected:
    char color;
    char shorthand;
};

class King : public Piece {
public:
    King(char color) : Piece(color, 'K') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

class Queen : public Piece {
public:
    Queen(char color) : Piece(color, 'Q') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

class Rook : public Piece {
public:
    Rook(char color) : Piece(color, 'r') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

class Bishop : public Piece {
public:
    Bishop(char color) : Piece(color, 'b') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

class Knight : public Piece {
public:
    Knight(char color) : Piece(color, 'k') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

class Pawn : public Piece {
public:
    Pawn(char color) : Piece(color, 'p') {}
    bool isValidMove(int x, int y) override;
    void move(int x, int y) override;
};

