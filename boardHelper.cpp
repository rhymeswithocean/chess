#include "boardHelper.h"

void print(const string& s) {
    std::cout << s;
}

void clearBuf() {
    std::cout << "\033[2J\033[H" << std::flush;
}
