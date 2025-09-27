#include "board.h"

void Board::drawFigure(Figure &figure, const float x, const float y) {
    const float scaleFigureToCell = static_cast<float>(CELL_SIZE) / figure.texture.width;
    DrawTextureEx(figure.texture, {x, y}, 0, scaleFigureToCell, WHITE);
}


void Board::initBoard() {
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            // Init Pawns
            if (i == 1 || i == 6) {
                // this->board[i][j] = std::make_unique<Figure>(Pawn());
            }
        }
    }
}


void Board::drawBoard() {
    int x = 0;
    int startPos = 0;
    bool first = true;

    // Vertical numbers
    while (x < CELLS_QUANT) {
        const Vector2 textPos = {
            static_cast<float>(startPos + NUMBERS_CELL_WIDTH / 2 - 2),
            static_cast<float>(x * NUMBERS_CELL_HEIGHT + NUMBERS_CELL_HEIGHT / 2 + 8)
        };

        DrawTextCodepoint(GetFontDefault(), '1' + x, textPos, 16, BLACK);
        ++x;

        if (x == 8 && first) {
            startPos = CELL_SIZE * CELLS_QUANT + NUMBERS_CELL_WIDTH;
            first = false;
            x = 0;
        }
    }

    x = 0;
    startPos = 0;
    first = true;

    // Horizontal letters
    while (x < CELLS_QUANT) {
        const Vector2 textPos = {
            static_cast<float>(x * LETTERS_CELL_WIDTH + LETTERS_CELL_HEIGHT / 2 + 50),
            static_cast<float>(startPos + LETTERS_CELL_WIDTH / 2 - 38)
        };

        DrawTextCodepoint(GetFontDefault(), 'a' + x, textPos, 16, BLACK);
        ++x;

        if (x == 8 && first) {
            startPos = CELL_SIZE * CELLS_QUANT + LETTERS_CELL_HEIGHT;
            first = false;
            x = 0;
        }
    }

    // Board itself
    for (int i = 0; i < CELLS_QUANT; i++) {
        for (int j = 0; j < CELLS_QUANT; j++) {
            DrawRectangle(
                    i * CELL_SIZE + NUMBERS_CELL_WIDTH,
                    j * CELL_SIZE + NUMBERS_CELL_WIDTH,
                    CELL_SIZE,
                    CELL_SIZE,
                    (i + j) % 2 == 0 ? WHITE : BLACK);
        }
    }
}