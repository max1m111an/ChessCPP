#include "board.h"

#include <algorithm>
#define GREEN_CELL Color{0x4e, 0x78, 0x37, 0xff}
#define YELLOW_CELL Color{0xba, 0xca, 0x44, 0xff}

std::unordered_map<FigureType, const char> typeToStr {
{PAWN, 'p'},
{ROOK, 'r'},
{KNIGHT, 'k'},
{KING, 'n'},
{QUEEN, 'q'},
{BISHOP, 'b'}
};

/* Board record in format:
 * lowercase - black;
 * uppercase - white;
 * number - count empty cells in row;
 * '/' - shift to new row.
**/
std::string Board::getBoardStatus() const {
    std::string status;
    int emptyCells = 0;

    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (!board[i][j]) {
                emptyCells++;
            } else {
                if (emptyCells > 0) {
                    status += std::to_string(emptyCells);
                    emptyCells = 0;
                }
                const auto figurePtr = board[i][j].get();
                FigureType type = figurePtr->getType();
                auto it = typeToStr.find(type);
                status += figurePtr->isWhite ? static_cast<char>(std::toupper(it->second)) : it->second;
            }
        } if (emptyCells > 0) {
            status += std::to_string(emptyCells);
            emptyCells = 0;
        } if (i < CELLS_QUANT - 1) {
            status += '/';
        }
    }
    return status;
}

// Convert coords to cell position
Vector2Int getPosXYFloatToInt(const float x, const float y) {
    return {(x - NUMBERS_CELL_WIDTH) / CELL_SIZE, (y - LETTERS_CELL_HEIGHT) / CELL_SIZE};
}

// View allow figure moves as circles
void Board::viewAllowMoves(const int figX, const int figY) const {
    const FigureType figureType = board[figY][figX]->getType();
    const bool isWhite = board[figY][figX]->isWhite;
    auto normalMoves = board[figY][figX]->getAllowMoves();

    // Erase blocked moves
    if (figureType != KNIGHT) {
        for (auto it = normalMoves.begin(); it != normalMoves.end(); ) {
            if (isPathBlocked(figX, figY, it->first, it->second)) {
                it = normalMoves.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Allow moves visibility
    for (const auto& move : normalMoves) {
        const int x = move.first, y = move.second;

        if (x < 0 || x >= CELLS_QUANT || y < 0 || y >= CELLS_QUANT) continue;

        const int screenX = (x + 1) * CELL_SIZE + NUMBERS_CELL_WIDTH - CELL_SIZE / 2;
        const int screenY = (y + 1) * CELL_SIZE + LETTERS_CELL_HEIGHT - CELL_SIZE / 2;
        constexpr float radius = 12.0;

        // For pawn only front cells
        if (figureType == PAWN) {
            if (x == figX && !board[y][x]) {
                DrawCircle(screenX, screenY, radius, BLACK);
            }
        } else {
            if (!board[y][x]) {
                DrawCircle(screenX, screenY, radius, BLACK);
            } else if (board[y][x]->isWhite != isWhite) {
                DrawCircle(screenX, screenY, radius, RED);
            }
        }
    }

    // Pawn eat move
    if (figureType == PAWN) {
        const int direction = isWhite ? -1 : 1;

        for (int dx = -1; dx <= 1; dx += 2) {
            const int targetX = figX + dx;
            const int targetY = figY + direction;

            if (board[targetY][targetX] && board[targetY][targetX]->isWhite != isWhite) {
                const int screenX = (targetX + 1) * CELL_SIZE + NUMBERS_CELL_WIDTH - CELL_SIZE / 2;
                const int screenY = (targetY + 1) * CELL_SIZE + LETTERS_CELL_HEIGHT - CELL_SIZE / 2;
                constexpr float radius = 12;
                DrawCircle(screenX, screenY, radius, RED);
            }
        }
    }
}

// Check if T value contains in vector
template<typename T>
bool contains(const std::vector<T>& vec, const T& value) {
    return std::find_if(vec.begin(), vec.end(),
            [&value](const T& elem) {
                return elem.first == value.first && elem.second == value.second;
            }) != vec.end();}


// Check for blocked moves by another figure
bool Board::isPathBlocked(const int fromX, const int fromY, const int toX, const int toY) const {
    const int dx = toX - fromX;
    const int dy = toY - fromY;

    // Move direction
    const int stepX = (dx == 0) ? 0 : (dx > 0 ? 1 : -1);
    const int stepY = (dy == 0) ? 0 : (dy > 0 ? 1 : -1);

    // For linear figures check the whole path
    int currentX = fromX + stepX;
    int currentY = fromY + stepY;

    // Check all path
    while (currentX != toX || currentY != toY) {
        if (board[currentY][currentX] != nullptr) {
            return true;
        }
        currentX += stepX;
        currentY += stepY;
    }

    return false;
}

// Move figure to new X and Y
int Board::moveFigureOnBoard(const Figure &figure, const int newX, const int newY) {
    if (!board[newY][newX] || board[newY][newX]->isWhite != figure.isWhite) {
        auto checkArr { figure.getAllowMoves() };

        // Move filtration
        if (figure.getType() != KNIGHT) {
            const Vector2Int currentPos = getPosXYFloatToInt(figure.x, figure.y);
            const int currentX = currentPos.first;
            const int currentY = currentPos.second;

            for (auto it = checkArr.begin(); it != checkArr.end(); ) {
                const int targetX = it->first;
                const int targetY = it->second;

                // Erase blocked moves
                if (isPathBlocked(currentX, currentY, targetX, targetY)) {
                    it = checkArr.erase(it);
                } else {
                    ++it;
                }
            }
        }

        if (figure.getType() == PAWN) {
            const int isWhiteConverter = figure.isWhite ? -1 : 1;
            const Vector2Int currentPos = getPosXYFloatToInt(figure.x, figure.y);
            const int currentX = currentPos.first;
            const int currentY = currentPos.second;

            // Diagonal pawn eat move
            for (int j = -1; j <= 1; j += 2) {
                const int targetX = currentX + j;
                const int targetY = currentY + isWhiteConverter;

                if (board[targetY][targetX] && board[targetY][targetX]->isWhite != figure.isWhite) {
                    checkArr.emplace_back(targetX, targetY);
                }
            }
        }

        if (contains(checkArr, Vector2Int(newX, newY))) {
            const Vector2Int oldXY = getPosXYFloatToInt(figure.x, figure.y);
            board[newY][newX] = std::move(board[oldXY.second][oldXY.first]);
            board[oldXY.second][oldXY.first] = nullptr;
            return 0;
        }
    }
    return 1;
}

// Init board with figures on
void Board::initBoard() {
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[i].size(); ++j) {
            // Position
            const auto x = static_cast<float>(j * CELL_SIZE + NUMBERS_CELL_WIDTH),
            y = static_cast<float>(i * CELL_SIZE + LETTERS_CELL_HEIGHT);

            // Init white Pawns
            if (i == 6) {
                board[i][j] = std::make_unique<Pawn>(Pawn(LoadTexture(filenameWP),
                    x, y, true));
            }
            // Init black Pawns
            if (i == 1) {
                board[i][j] = std::make_unique<Pawn>(Pawn(LoadTexture(filenameBP),
                    x, y, false));
            }
            // Init blacks
            if (i == 0) {
                // Rook
                if (j == 0 || j == CELLS_QUANT - 1) {
                    board[i][j] = std::make_unique<Rook>(Rook(LoadTexture(filenameBR),
                    x, y, false));
                }
                // Bishop
                if (j == 1 || j == CELLS_QUANT - 2) {
                    board[i][j] = std::make_unique<Bishop>(Bishop(LoadTexture(filenameBB),
                    x, y, false));
                }
                // Knight
                if (j == 2 || j == CELLS_QUANT - 3) {
                    board[i][j] = std::make_unique<Knight>(Knight(LoadTexture(filenameBN),
                    x, y, false));
                }
                // King
                if (j == 3) {
                    board[i][j] = std::make_unique<King>(King(LoadTexture(filenameBK),
                    x, y, false));
                }
                // Queen
                if (j == 4) {
                    board[i][j] = std::make_unique<Queen>(Queen(LoadTexture(filenameBQ),
                    x, y, false));
                }

            }
            // Init whites
            if (i == 7) {
                // Rook
                if (j == 0 || j == CELLS_QUANT - 1) {
                    board[i][j] = std::make_unique<Rook>(Rook(LoadTexture(filenameWR),
                    x, y, true));
                }
                // Bishop
                if (j == 1 || j == CELLS_QUANT - 2) {
                    board[i][j] = std::make_unique<Bishop>(Bishop(LoadTexture(filenameWB),
                    x, y, true));
                }
                // Knight
                if (j == 2 || j == CELLS_QUANT - 3) {
                    board[i][j] = std::make_unique<Knight>(Knight(LoadTexture(filenameWN),
                    x, y, true));
                }
                // King
                if (j == 3) {
                    board[i][j] = std::make_unique<King>(King(LoadTexture(filenameWK),
                    x, y, true));
                }
                // Queen
                if (j == 4) {
                    board[i][j] = std::make_unique<Queen>(Queen(LoadTexture(filenameWQ),
                    x, y, true));
                }
            }
        }
    }
}

// Draw board cells and lines
void Board::drawBoard() const {
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
            startPos =  + LETTERS_CELL_HEIGHT;
            first = false;
            x = 0;
        }
    }

    // Board itself
    for (int i = 0; i < CELLS_QUANT; i++) {
        for (int j = 0; j < CELLS_QUANT; j++) {
            auto cellColor{ WHITE };

            if (isFigureDragging &&
                dragFigurePos.first == i &&
                dragFigurePos.second == j) {
                cellColor = YELLOW_CELL;
            } else if ((i + j) % 2 == 1) {
                cellColor = GREEN_CELL;
            }

            DrawRectangle(
                    i * CELL_SIZE + NUMBERS_CELL_WIDTH,
                    j * CELL_SIZE + LETTERS_CELL_HEIGHT,
                    CELL_SIZE,
                    CELL_SIZE,
                    cellColor);
        }
    }
}
