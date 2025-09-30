#include "board.h"

std::unordered_map<FigureType, const char> typeToStr = {
{PAWN, 'p'},
{ROOK, 'r'},
{KNIGHT, 'k'},
{KING, 'n'},
{QUEEN, 'q'},
{BISHOP, 'b'}
};

/* Board record in format:
 * _lowercase_ - black;
 * uppercase - white;
 * number - count empty cells in row;
 * '/' - shift to new row.
**/
std::string Board::getBoardStatus() const {
    std::string status;
    int emptyCells = 0;

    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (!this->board[i][j]) {
                emptyCells++;
            } else {
                if (emptyCells > 0) {
                    status += std::to_string(emptyCells);
                    emptyCells = 0;
                }
                const auto figurePtr = this->board[i][j].get();
                if (figurePtr) {
                    FigureType type = figurePtr->getType();
                    auto it = typeToStr.find(type);
                    status += figurePtr->isWhite ? std::toupper(it->second) : it->second;
                }
            }
        }if (emptyCells > 0) {
            status += std::to_string(emptyCells);
            emptyCells = 0;
        }if (i < CELLS_QUANT - 1) {
            status += '/';
        }
    }
    return status;
}


void Board::drawFigure(const Figure &figure) const {
    const float scaleFigureToCell = static_cast<float>(CELL_SIZE / figure.texture.width);
    DrawTextureEx(figure.texture, {figure.x, figure.y}, 0, scaleFigureToCell, WHITE);
}

std::pair<int, int> getPosXYFloatToInt(const float x, const float y) {
    return {(x - NUMBERS_CELL_WIDTH) / CELL_SIZE, (y - LETTERS_CELL_HEIGHT) / CELL_SIZE};
}

// Move figure to new X and Y
void Board::moveFigureOnBoard(const Figure &figure, const int newX, const int newY) {
    if (!this->board[newY][newX]) {
        const auto oldXY = getPosXYFloatToInt(figure.x, figure.y);
        this->board[newY][newX] = std::move(this->board[oldXY.second][oldXY.first]);
    } else {
      std::cout << "DON'T DO IT MF!" << std::endl;
    }
}

// Init board with figures on
void Board::initBoard() {
    for (int i = 0; i < this->board.size(); ++i) {
        for (int j = 0; j < this->board[i].size(); ++j) {
            // Position
            const float x = static_cast<float>(j * CELL_SIZE + NUMBERS_CELL_WIDTH),
            y = static_cast<float>(i * CELL_SIZE + LETTERS_CELL_HEIGHT);

            // Init white Pawns
            if (i == 6) {
                this->board[i][j] = std::make_unique<Pawn>(Pawn(LoadTexture(filenameWP),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
            }
            // Init black Pawns
            if (i == 1) {
                this->board[i][j] = std::make_unique<Pawn>(Pawn(LoadTexture(filenameBP),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
            }
            // Init blacks
            if (i == 0) {
                // Rook
                if (j == 0 || j == CELLS_QUANT - 1) {
                    this->board[i][j] = std::make_unique<Rook>(Rook(LoadTexture(filenameBR),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
                }
                // Bishop
                if (j == 1 || j == CELLS_QUANT - 2) {
                    this->board[i][j] = std::make_unique<Bishop>(Bishop(LoadTexture(filenameBB),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
                }
                // Knight
                if (j == 2 || j == CELLS_QUANT - 3) {
                    this->board[i][j] = std::make_unique<Knight>(Knight(LoadTexture(filenameBN),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
                }
                // King
                if (j == 3) {
                    this->board[i][j] = std::make_unique<King>(King(LoadTexture(filenameBK),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
                }
                // Queen
                if (j == 4) {
                    this->board[i][j] = std::make_unique<Queen>(Queen(LoadTexture(filenameBQ),
                    x, y, Cell(j, i, (i + j) % 2 == 0), false));
                }

            }
            // Init whites
            if (i == 7) {
                // Rook
                if (j == 0 || j == CELLS_QUANT - 1) {
                    this->board[i][j] = std::make_unique<Rook>(Rook(LoadTexture(filenameWR),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
                }
                // Bishop
                if (j == 1 || j == CELLS_QUANT - 2) {
                    this->board[i][j] = std::make_unique<Bishop>(Bishop(LoadTexture(filenameWB),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
                }
                // Knight
                if (j == 2 || j == CELLS_QUANT - 3) {
                    this->board[i][j] = std::make_unique<Knight>(Knight(LoadTexture(filenameWN),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
                }
                // King
                if (j == 3) {
                    this->board[i][j] = std::make_unique<King>(King(LoadTexture(filenameWK),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
                }
                // Queen
                if (j == 4) {
                    this->board[i][j] = std::make_unique<Queen>(Queen(LoadTexture(filenameWQ),
                    x, y, Cell(j, i, (i + j) % 2 == 0), true));
                }
            }
        }
    }
}

// Draw board cells and lines
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

        DrawTextCodepoint(GetFontDefault(), '8' - x, textPos, 16, BLACK);
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
                    j * CELL_SIZE + LETTERS_CELL_HEIGHT,
                    CELL_SIZE,
                    CELL_SIZE,
                    (i + j) % 2 == 0 ? WHITE : BLACK);
        }
    }
}