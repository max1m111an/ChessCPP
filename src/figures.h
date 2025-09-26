#pragma once
#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"

inline constexpr int CELL_SIZE = 80;
inline constexpr int CELLS_QUANT = 8;

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
        Texture2D texture;
        bool isWhite = false;
        float x = 0.f;
        float y = 0.f;
        bool alive = true;
        bool active = false;
        void moveFigure(float, float);
        void draw(float, float) const;
};


class Cell {
    public:
        bool isBlack;
        bool occupied() const;
        std::optional<Figure> figure = std::nullopt;
};

class Board {
    public:
        std::array<std::array<Cell, 8>, 8> board;
};
