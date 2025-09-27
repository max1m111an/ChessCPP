#include "figures.h"

void Figure::moveFigure(const float x, const float y){
    this->x = x;
    this->y = y;
}

void Figure::drawAtCursor(const float x, const float y) const {
    const float dx = static_cast<float>(this->texture.width) / 2.0f,
        dy = static_cast<float>(this->texture.height) / 2.0f;
    DrawTextureV(this->texture, {x - dx, y - dy}, WHITE);
}

void Figure::drawAtBoard(const float x, const float y) const {
    const Texture2D thisTexture = this->texture;
    const double scaleFigureToCell = static_cast<double>(CELL_SIZE) / thisTexture.width;
    const float dx = static_cast<float>(thisTexture.width) / 2.0f,
        dy = static_cast<float>(thisTexture.height) / 2.0f;
    DrawTextureEx(thisTexture, {x - dx, y - dy}, 0, scaleFigureToCell, WHITE);
}

bool Cell::occupied() const {
    return this->figure.has_value();
}

void Board::initBoard() {
    for (int i = 0; i < CELLS_QUANT; i++) {
        for (int j = 0; j < CELLS_QUANT; j++) {
            this->board[i][j] = Cell((i + j) % 2 == 0);
        }
    }
}

void Board::drawBoard() const {
    for (int i = 0; i < CELLS_QUANT; i++) {
        for (int j = 0; j < CELLS_QUANT; j++) {
            DrawRectangle(
                    i * CELL_SIZE,
                    j * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE,
                    this->board[i][j].isBlack ? WHITE : BLACK
                    );
        }
    }
}