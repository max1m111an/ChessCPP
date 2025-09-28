#include "figures.h"

void Figure::moveFigure(const float x, const float y) {
    this->x = x;
    this->y = y;
}

void Figure::dragAtCursor(const float x, const float y) const {
    const float centerX = static_cast<float>(this->texture.width) / 2.0f,
        centerY = static_cast<float>(this->texture.height) / 2.0f;
    DrawTextureV(this->texture, {x - centerX, y - centerY}, WHITE);
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
