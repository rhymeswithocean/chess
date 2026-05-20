#pragma once
#include <string>
using std::string;

class Piece {
public:
    virtual void move() = 0;
    virtual bool isValidMove() = 0;
    virtual ~Piece() = default;

protected:
    char color;
    char shorthand;
};

class King : public Piece {
public:
    King();
    void move() override;
protected:
    char color;
    char shorthand;
};
