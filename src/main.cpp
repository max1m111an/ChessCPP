#include <iostream>
#include <string>

#include "raylib.h"
#include "figures.cpp"
#include <unordered_map>

typedef std::unordered_map<std::string, Texture2D> textureMap;

const std::unordered_map<std::string, int> letterToNumber = {
    {"a", 1},
    {"b", 2},
    {"c", 3},
    {"d", 4},
    {"e", 5},
    {"f", 6},
    {"g", 7},
    {"h", 8},
};

textureMap LoadData() {
    textureMap vimrc = {
        {"bB", LoadTexture("../textures/bB.png")},
        {"bQ", LoadTexture("../textures/bQ.png")},
        {"bK", LoadTexture("../textures/bK.png")},
        {"bN", LoadTexture("../textures/bN.png")},
        {"bR", LoadTexture("../textures/bR.png")},
        {"bP", LoadTexture("../textures/bP.png")},
        {"wB", LoadTexture("../textures/wB.png")},
        {"wQ", LoadTexture("../textures/wQ.png")},
        {"wK", LoadTexture("../textures/wK.png")},
        {"wN", LoadTexture("../textures/wN.png")},
        {"wR", LoadTexture("../textures/wR.png")},
        {"wP", LoadTexture("../textures/wP.png")},
    };
    return vimrc;
}

void drawFigures(textureMap &t, const Board &_board) {
    const double scaleFigureToCell = static_cast<double>(cellSize) / t["wK"].width;

    for (const auto& figure: t) {
        DrawTextureEx(figure.second,
                  (Vector2){0, 0},
                  0,
                  static_cast<float>(scaleFigureToCell),
                  WHITE);
    }
}

int main() {
    constexpr int cellsQuantity = 8;
    constexpr int screenWidth = cellSize * cellsQuantity;
    constexpr int screenHeight = screenWidth + 150;

    InitWindow(screenWidth, screenHeight, "ChessCPP");

    std::unordered_map<std::string, Texture2D> guy = LoadData();

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        Board mainBoard;

        for (int i = 0; i < cellsQuantity; i++) {
            for (int j = 0; j < cellsQuantity; j++) {
                // mainBoard.board[i][j] = mainBoard.board[i][j];
                const Cell newCell((i + j) % 2 == 0);
                mainBoard.board[i][j] = newCell;
                DrawRectangle(
                    i * cellSize,
                    j * cellSize,
                    cellSize,
                    cellSize,
                    newCell.isBlack ? WHITE : BLACK);
            }
        }

        drawFigures(guy, mainBoard);

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
