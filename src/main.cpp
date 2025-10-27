#include "board.h"

#define filenameIcon "../textures/chesscpp_icon.png"


// Check if the move can be able on the whole board
bool isValidMoveOnBoard(const float x, const float y) {
    const Vector2Int currentXY = getPosXYFloatToInt(x, y);
    return currentXY.first >= 0 && currentXY.first < CELLS_QUANT &&
        currentXY.second >= 0 && currentXY.second < CELLS_QUANT;
}

// Convert figure position to screen coords
inline Vector2 getPosXYIntToFloat(const int x, const int y) {
    return {static_cast<float>(x * CELL_SIZE + NUMBERS_CELL_WIDTH), static_cast<float>(y * CELL_SIZE + LETTERS_CELL_HEIGHT)};
}

// Convert mouse pos to cell position
inline Vector2Int getMousePosOnBoardXY(const Vector2 &mousePos) {
    return {static_cast<int>(mousePos.x - NUMBERS_CELL_WIDTH) / CELL_SIZE, static_cast<int>(mousePos.y - LETTERS_CELL_HEIGHT) / CELL_SIZE};
}

void drawFigures(const Board &board) {
    for (int i = 0; i < CELLS_QUANT; ++i) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (board.board[i][j]) board.board[i][j].get()->drawFigure();
        }
    }
}

Vector2Int draggedFigureCurrentPos {};
bool isWhiteTurn = true;

// Returns figure to its started place
bool turnBackFigure(Board& board) {
    board.isFigureDragging = false;
    return true;
}

// Captured figure
void startDragFigures(Board& board, const Vector2& mousePos) {
    const Vector2Int xy = getMousePosOnBoardXY(mousePos);

    if (board.board[xy.second][xy.first] && board.board[xy.second][xy.first]->isWhite == isWhiteTurn) {
        board.isFigureDragging = true;
        board.dragFigurePos = xy;
    }
}

// Dynamic drag figure on screen
void updateDragFigures(const Board& board, const Vector2& mousePos) {
    if (board.isFigureDragging) {
        draggedFigureCurrentPos = getMousePosOnBoardXY(mousePos);

        const Figure* figurePtr = board.board[board.dragFigurePos.second][board.dragFigurePos.first].get();
        if (figurePtr) {
            figurePtr->dragAtCursor(mousePos.x, mousePos.y);
            board.viewAllowMoves(board.dragFigurePos.first, board.dragFigurePos.second);
        }
    }
}

// Stand figure on end mouse pos
void endDragFigures(Board& board) {
    if (board.isFigureDragging) {
        const int newCol = draggedFigureCurrentPos.first;
        const int newRow = draggedFigureCurrentPos.second;
        const Vector2 newFigXY = getPosXYIntToFloat(newCol, newRow);

        if (isValidMoveOnBoard(newFigXY.x, newFigXY.y) && draggedFigureCurrentPos != board.dragFigurePos) {
            Figure* figurePtr = board.board[board.dragFigurePos.second][board.dragFigurePos.first].get();

            if (figurePtr) {
                const int moveStatus = board.moveFigureOnBoard(*figurePtr, newCol, newRow);
                if (moveStatus == 0){
                    figurePtr->moveFigure(newFigXY.x, newFigXY.y);
                    isWhiteTurn = !isWhiteTurn;
                    std::cout << board.getBoardStatus() << std::endl;
                }
            }
        }
        turnBackFigure(board);
    }
}

void DragFigures(const Vector2& mousePos, Board& board) {
    if (!board.isFigureDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && isValidMoveOnBoard(mousePos.x, mousePos.y)) {
            startDragFigures(board, mousePos);
        }
    } else {
        updateDragFigures(board, mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            endDragFigures(board);
        } if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            turnBackFigure(board);
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

        DrawText(isWhiteTurn ? "Whites turn" : "Blacks turn",
            (CELL_SIZE * CELLS_QUANT) / 2 - 50,
            CELL_SIZE * CELLS_QUANT + LETTERS_CELL_HEIGHT * 2 + 50,
            24, BLACK);

        DragFigures(mousePosition, mainBoard);

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
