#pragma once
#include <string>
using std::string;

class Piece {
public:
    Piece(char color, char shorthand);
    virtual void move(char x, int y) = 0;
    virtual bool isValidMove(char x, int y) = 0;
    virtual ~Piece() = default;
    string toString() const;
    friend std::ostream& operator<<(std::ostream& os, const Piece& p);

protected:
    char color;
    char shorthand;
};

class King : public Piece {
public:
    King(char color) : Piece(color, 'K') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

class Queen : public Piece {
public:
    Queen(char color) : Piece(color, 'Q') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

class Rook : public Piece {
public:
    Rook(char color) : Piece(color, 'r') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

class Bishop : public Piece {
public:
    Bishop(char color) : Piece(color, 'b') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

class Knight : public Piece {
public:
    Knight(char color) : Piece(color, 'k') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

class Pawn : public Piece {
public:
    Pawn(char color) : Piece(color, 'p') {}
    bool isValidMove(char x, int y) override;
    void move(char x, int y) override;
};

