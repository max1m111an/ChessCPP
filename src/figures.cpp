#include <array>
//
// Created by maksi on 24.09.2025.
//

const int cellSize = 80;

enum FigureType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    KING,
    QUEEN,
};

class Figure {
    public:
        FigureType type;
        bool alive = true;
};


class Cell {
    public:
        bool isBlack;
        bool occupied = false;
};

class Board {
    public:
        std::array<std::array<Cell, 8>, 8> board;
};
