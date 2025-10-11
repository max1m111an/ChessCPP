#include "board.h"

typedef std::unordered_map<std::string, Texture2D> textureMap;
#define filenameIcon "../textures/chesscpp_icon.png"


// Check if the move can be able on the whole board
bool isValidMoveOnBoard(const float x, const float y) {
    return x >= NUMBERS_CELL_WIDTH && x <= SCREEN_WIDTH - NUMBERS_CELL_WIDTH &&
        y >= LETTERS_CELL_HEIGHT && y <= SCREEN_HEIGHT - LETTERS_CELL_HEIGHT;
}

// Convert figure position to screen coords
inline Vector2 getPosXYIntToFloat(const int x, const int y) {
    return {static_cast<float>(x * CELL_SIZE + NUMBERS_CELL_WIDTH), static_cast<float>(y * CELL_SIZE + LETTERS_CELL_HEIGHT)};
}

void drawFigures(const Board &board) {
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (board.board[i][j]) board.board[i][j].get()->drawFigure();
        }
    }
}

// Convert mouse pos to cell position
inline std::pair<int, int> getMousePosOnBoardXY(const Vector2 &mousePos) {
    return {static_cast<int>(mousePos.x - NUMBERS_CELL_WIDTH) / CELL_SIZE, static_cast<int>(mousePos.y - LETTERS_CELL_HEIGHT) / CELL_SIZE};
}

static std::pair<int, int> draggedFigureStartPos {};
static std::pair<int, int> draggedFigureCurrentPos {};
static bool isDragging { false };

// Captured figure
void startDragFigures(const Board& board, const Vector2& mousePos) {
    const std::pair<int, int> xy = getMousePosOnBoardXY(mousePos);

    if (board.board[xy.second][xy.first]) {
        draggedFigureStartPos = xy;
        isDragging = true;
    }
}

// Dynamic drag figure on screen
void updateDragFigures(const Board& board, const Vector2& mousePos) {
    if (isDragging) {
        draggedFigureCurrentPos = getMousePosOnBoardXY(mousePos);

        const Figure* figurePtr = board.board[draggedFigureStartPos.second][draggedFigureStartPos.first].get();
        if (figurePtr) {
            figurePtr->dragAtCursor(mousePos.x, mousePos.y);
        }
    }
}

// Stand figure on end mouse pos
void endDragFigures(Board& board) {
    if (isDragging) {
        const int newCol = draggedFigureCurrentPos.first;
        const int newRow = draggedFigureCurrentPos.second;
        const float newFigX = static_cast<float>(newCol) * CELL_SIZE + NUMBERS_CELL_WIDTH;
        const float newFigY = static_cast<float>(newRow) * CELL_SIZE + LETTERS_CELL_HEIGHT;

        if (isValidMoveOnBoard(newFigX, newFigY) && draggedFigureCurrentPos != draggedFigureStartPos) {
            Figure* figurePtr = board.board[draggedFigureStartPos.second][draggedFigureStartPos.first].get();

            if (figurePtr) {
                const int moveStatus = board.moveFigureOnBoard(*figurePtr, newCol, newRow);
                if (moveStatus == 0){
                    figurePtr->moveFigure(newFigX, newFigY);
                    std::cout << board.getBoardStatus() << std::endl;
                }
            }
        }

        isDragging = false;
    }
}

// Returns figure to its started place
void turnBackFigure() {
    isDragging = false;
}

void DragFigures(const Vector2& mousePos, Board& board) {
    if (!isDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isValidMoveOnBoard(mousePos.x, mousePos.y)) {
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
