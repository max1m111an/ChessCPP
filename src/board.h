#pragma once
#include <array>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "figures.h"
#include "Vector2Int.h"

inline constexpr int SCREEN_WIDTH { CELL_SIZE * CELLS_QUANT + 2 * NUMBERS_CELL_WIDTH};
inline constexpr int SCREEN_HEIGHT { CELL_SIZE * CELLS_QUANT + 2 * LETTERS_CELL_HEIGHT};
inline constexpr int ADD_SCREEN_HEIGHT { 150 };
inline constexpr int FPS { 60 };


class Board {
    public:
        std::array<std::array<std::unique_ptr<Figure>, CELLS_QUANT>, CELLS_QUANT> board;
        bool isFigureDragging { false };
        bool isWhiteTurn { true };
        Vector2Int dragFigurePos;
        void swapTurn();
        void turnBackFigure();
        void initBoard();
        void drawBoard() const;
        void viewAllowMoves(int, int) const;
        std::string getBoardStatus() const;
        int moveFigureOnBoard(const Figure&, int, int);
        bool isPathBlocked(int, int, int, int) const;
};

Vector2Int getPosXYFloatToInt(float, float);
