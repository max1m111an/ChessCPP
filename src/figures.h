#pragma once
#include <array>
#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
//
// Created by maksi on 24.09.2025.
//

inline constexpr int cellSize = 80;
inline constexpr int cellsQuantity = 8;

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
};


class Cell {
    public:
        bool isBlack;
        bool occupied = false;
        std::optional<Figure> figure = std::nullopt;
};

class Board {
    public:
        std::array<std::array<Cell, 8>, 8> board;
};
