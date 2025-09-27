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

inline constexpr int CELL_SIZE = 80;
inline constexpr int CELLS_QUANT = 8;
inline constexpr int NUMBERS_CELL_WIDTH { 20 };
inline constexpr int NUMBERS_CELL_HEIGHT { CELL_SIZE };
inline constexpr int LETTERS_CELL_WIDTH { CELL_SIZE };
inline constexpr int LETTERS_CELL_HEIGHT { 20 };
inline constexpr int SCREEN_WIDTH { CELL_SIZE * CELLS_QUANT + 2 * NUMBERS_CELL_WIDTH + 1};
inline constexpr int SCREEN_HEIGHT { SCREEN_WIDTH + 2 * LETTERS_CELL_HEIGHT + 1};
inline constexpr int FPS { 60 };


class Board {
    public:
        std::array<std::array<std::unique_ptr<Figure>, 8>, 8> board;

        void initBoard();
        void drawBoard();
        void drawFigure(Figure&, float, float);
};
