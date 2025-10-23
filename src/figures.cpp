#include "figures.h"
#include "board.h"

// Change figure and its cell position
void Figure::moveFigure(const float a, const float b) {
    x = a;
    y = b;
}

// Captured figure to mouse and drag it
void Figure::dragAtCursor(const float a, const float b) const {
    const float centerX = static_cast<float>(texture.width) / 2.0f,
        centerY = static_cast<float>(texture.height) / 2.0f;
    DrawTextureV(texture, {a - centerX, b - centerY}, WHITE);
}

// Draw figure on the screen
void Figure::drawFigure() const {
    const float scaleFigureToCell = static_cast<float>(CELL_SIZE) / static_cast<float>(texture.width);
    DrawTextureEx(texture, {x, y}, 0, scaleFigureToCell, WHITE);
}


FigureType Figure::getType() {
    return NONE;
}

FigureType Pawn::getType() {
    return PAWN;
}

FigureType Rook::getType() {
    return ROOK;
}

FigureType Knight::getType() {
    return KNIGHT;
}

FigureType Bishop::getType() {
    return BISHOP;
}

FigureType Queen::getType() {
    return QUEEN;
}

FigureType King::getType() {
    return KING;
}


std::vector<Vector2Int> Figure::getAllowMoves() const {
    return {};
}


std::vector<Vector2Int> Pawn::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(2);
    if (isWhite) {
        allowMoves.emplace_back(currentPos.first - 1, currentPos.second - 1);
        allowMoves.emplace_back(currentPos.first + 1, currentPos.second - 1);
    } else {
        allowMoves.emplace_back(currentPos.first - 1, currentPos.second + 1);
        allowMoves.emplace_back(currentPos.first + 1, currentPos.second + 1);
    }
    return allowMoves;
}


std::vector<Vector2Int> Knight::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(8);
    for (int i = -1; i <= 1; i += 2) {
        allowMoves.emplace_back(currentPos.first - 2, currentPos.second + i);
        allowMoves.emplace_back(currentPos.first + 2, currentPos.second + i);
        allowMoves.emplace_back(currentPos.first - 1, currentPos.second + 2 * i);
        allowMoves.emplace_back(currentPos.first + 1, currentPos.second + 2 * i);
    }
    return allowMoves;
}


std::vector<Vector2Int> Bishop::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(14);
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = -1; j <= 1; j += 2) {
            allowMoves.emplace_back(currentPos.first + i, currentPos.second - i * j);
            allowMoves.emplace_back(currentPos.first - i, currentPos.second - i * j);
        }
    }
    return allowMoves;
}


std::vector<Vector2Int> Rook::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(14);
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = -1; j <= 1; j += 2) {
            allowMoves.emplace_back(currentPos.first, currentPos.second + i * j);
            allowMoves.emplace_back(currentPos.first + i * j, currentPos.second);
        }
    }
    return allowMoves;
}


std::vector<Vector2Int> Queen::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(28);
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = -1; j <= 1; j += 2) {
            allowMoves.emplace_back(currentPos.first, currentPos.second + i * j);
            allowMoves.emplace_back(currentPos.first + i * j, currentPos.second);
            allowMoves.emplace_back(currentPos.first + i, currentPos.second - i * j);
            allowMoves.emplace_back(currentPos.first - i, currentPos.second - i * j);
        }
    }
    return allowMoves;
}


std::vector<Vector2Int> King::getAllowMoves() const {
    const Vector2Int currentPos = getPosXYFloatToInt(x, y);
    std::vector<Vector2Int> allowMoves;
    allowMoves.reserve(8);
    allowMoves.emplace_back(currentPos.first, currentPos.second - 1);
    allowMoves.emplace_back(currentPos.first, currentPos.second + 1);
    for (int i = -1; i <= 1; ++i) {
        allowMoves.emplace_back(currentPos.first - 1, currentPos.second + i);
        allowMoves.emplace_back(currentPos.first + 1, currentPos.second + i);
    }
    return allowMoves;
}