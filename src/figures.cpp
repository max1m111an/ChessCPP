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
