#include "figures.h"

void Figure::moveFigure(const float x, const float y) {
    this->x = x;
    this->y = y;
    const float dx = static_cast<float>(this->texture.width) / 2.0f,
    dy = static_cast<float>(this->texture.height) / 2.0f;
    DrawTextureV(this->texture, {x - dx, y - dy}, WHITE);
}

bool Cell::occupied() const {
    return this->figure.has_value();
}
