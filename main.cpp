#include "boardHelper.h"
#include "piece.h"

Piece* board[8][8] = {};
bool gO = false;

int main (int argc, char *argv[]) {
    setup();
    clearBuf();
    printBoard();

    return 0;
}

