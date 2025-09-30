#include "board.h"

typedef std::unordered_map<std::string, Texture2D> textureMap;
#define filenameIcon "../textures/chesscpp_icon.png"


bool isValidMove(const float x, const float y) {
    return x >= NUMBERS_CELL_WIDTH && x <= SCREEN_WIDTH - NUMBERS_CELL_WIDTH &&
        y >= LETTERS_CELL_HEIGHT && y <= SCREEN_HEIGHT - LETTERS_CELL_HEIGHT;
}

Vector2 getPosXYIntToFloat(const int x, const int y) {
    return {static_cast<float>(x * CELL_SIZE + NUMBERS_CELL_WIDTH), static_cast<float>(y * CELL_SIZE + LETTERS_CELL_HEIGHT)};
}

void drawFigures(const Board &board) {
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (board.board[i][j].get()) {
                const double scaleFigureToCell = static_cast<double>(CELL_SIZE) / board.board[i][j].get()->texture.width;
                const Vector2 xy = getPosXYIntToFloat(j, i);

                DrawTextureEx(board.board[i][j].get()->texture, {xy.x, xy.y},
                    0, static_cast<float>(scaleFigureToCell), WHITE);
            }
        }
    }
}

inline std::pair<int, int> getMousePosOnBoardXY(const Vector2 &mousePos) {
    return {static_cast<int>(mousePos.x - NUMBERS_CELL_WIDTH) / CELL_SIZE, static_cast<int>(mousePos.y - LETTERS_CELL_HEIGHT) / CELL_SIZE};
}

static std::pair<int, int> draggedFigureStartPos {};
static std::pair<int, int> draggedFigureCurrentPos {};
static bool isDragging { false };

void startDragFigures(const Board& board, const Vector2& mousePos) {
    const std::pair<int, int> xy = getMousePosOnBoardXY(mousePos);

    if (board.board[xy.second][xy.first]) {
        draggedFigureStartPos = xy;
        isDragging = true;
    }
}

void updateDragFigures(const Board& board, const Vector2& mousePos) {
    if (isDragging) {
        draggedFigureCurrentPos = getMousePosOnBoardXY(mousePos);

        const Figure* figurePtr = board.board[draggedFigureStartPos.second][draggedFigureStartPos.first].get();
        if (figurePtr) {
            figurePtr->dragAtCursor(mousePos.x, mousePos.y);
        }
    }
}

void endDragFigures(Board& board) {
    if (isDragging) {
        const int newCol = draggedFigureCurrentPos.first;
        const int newRow = draggedFigureCurrentPos.second;
        const float newFigX = static_cast<float>(newCol) * CELL_SIZE + NUMBERS_CELL_WIDTH;
        const float newFigY = static_cast<float>(newRow) * CELL_SIZE + LETTERS_CELL_HEIGHT;

        if (isValidMove(newFigX, newFigY) && draggedFigureCurrentPos != draggedFigureStartPos) {
            Figure* figurePtr = board.board[draggedFigureStartPos.second][draggedFigureStartPos.first].get();

            if (figurePtr) {
                board.moveFigureOnBoard(*figurePtr, newCol, newRow);
                figurePtr->moveFigure(newFigX, newFigY);
                std::cout << board.getBoardStatus() << std::endl;
            }
        }

        isDragging = false;
    }
}

// Returns figure to its place
void turnBackFigure() {
    isDragging = false;
}

void DragFigures(const Vector2& mousePos, Board& board) {
    if (!isDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isValidMove(mousePos.x, mousePos.y)) {
            startDragFigures(board, mousePos);
        }
    } else {
        updateDragFigures(board, mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            endDragFigures(board);
        } if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            turnBackFigure();
        }
    }
}

int main() {
    Vector2 mousePosition { 0 };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT + ADD_SCREEN_HEIGHT, "ChessCPP");
    SetWindowIcon(LoadImage(filenameIcon));

    Board mainBoard;
    mainBoard.initBoard();
    std::cout << mainBoard.getBoardStatus() << std::endl;

    SetTargetFPS(FPS);

    // Main game loop
    while (!WindowShouldClose()) {

        mousePosition = GetMousePosition();

        BeginDrawing();
        mainBoard.drawBoard();
        drawFigures(mainBoard);

        DragFigures(mousePosition, mainBoard);

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
