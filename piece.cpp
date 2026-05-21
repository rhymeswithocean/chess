#include "piece.h"
#include<string>
using std::string;

Piece::Piece(char color, char shorthand) : color(color), shorthand(shorthand) {}

string Piece::toString() const { return {color, shorthand}; }

std::ostream& operator<<(std::ostream& os, const Piece& p) {
    os << p.toString();
    return os;
}

bool King::isValidMove(char x, int y)   { return false; }
void King::move(char x, int y)          {}

bool Queen::isValidMove(char x, int y)  { return false; }
void Queen::move(char x, int y)         {}

bool Rook::isValidMove(char x, int y)   { return false; }
void Rook::move(char x, int y)          {}

bool Bishop::isValidMove(char x, int y) { return false; }
void Bishop::move(char x, int y)        {}

bool Knight::isValidMove(char x, int y) { return false; }
void Knight::move(char x, int y)        {}

bool Pawn::isValidMove(char x, int y)   { return false; }
void Pawn::move(char x, int y)          {}
