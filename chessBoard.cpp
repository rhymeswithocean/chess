#include "piece.h"

class board {
public:
    board();
    board(board &&) = default;
    board(const board &) = default;
    board &operator=(board &&) = default;
    board &operator=(const board &) = default;
    ~board();

private:
    
};

board::board() {
}

board::~board() {
}
