#include "figures.h"

typedef std::unordered_map<std::string, Texture2D> textureMap;
#define filenameWP "../textures/wP.png"
#define filenameWQ "../textures/wQ.png"
#define filenameWK "../textures/wK.png"
#define filenameWR "../textures/wR.png"
#define filenameWN "../textures/wN.png"
#define filenameWB "../textures/wB.png"
#define filenameBP "../textures/bP.png"
#define filenameBQ "../textures/bQ.png"
#define filenameBK "../textures/bK.png"
#define filenameBR "../textures/bR.png"
#define filenameBN "../textures/bN.png"
#define filenameBB "../textures/bB.png"
#define filenameIcon "../textures/chesscpp_icon.png"


bool isValidMove(const float x, const float y) {
    return x >= 0.0f && x <= CELL_SIZE * CELLS_QUANT && y >= 0.0f && y <= CELL_SIZE * CELLS_QUANT;
}

std::string pos[CELLS_QUANT][CELLS_QUANT] {
    {"bR", "bN", "bB", "bK", "bQ", "bb", "bn", "br"},
    {"bP0", "bP1", "bP2", "bP3", "bP4", "bP5", "bP6", "bP7"},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"", "", "", "", "", "", "", ""},
    {"wP0", "wP1", "wP2", "wP3", "wP4", "wP5", "wP6", "wP7"},
    {"wR", "wN", "wB", "wK", "wQ", "wb", "wn", "wr"}
};

std::unordered_map<std::string, FigureType> strToFigureType {
    {"wK", KING},
    {"wQ", QUEEN},
    {"wR", ROOK},
    {"wB", BISHOP},
    {"wN", KNIGHT},
    {"wP", PAWN},
    {"bK", KING},
    {"bQ", QUEEN},
    {"bR", ROOK},
    {"bB", BISHOP},
    {"bN", KNIGHT},
    {"bP", PAWN},
};

// Load figure textures dict
textureMap LoadData() {
    textureMap vimrc = {
            {"bb", LoadTexture(filenameBB)},
            {"bB", LoadTexture(filenameBB)},
            {"bQ", LoadTexture(filenameBQ)},
            {"bK", LoadTexture(filenameBK)},
            {"bN", LoadTexture(filenameBN)},
            {"bn", LoadTexture(filenameBN)},
            {"bR", LoadTexture(filenameBR)},
            {"br", LoadTexture(filenameBR)},
            {"bP0", LoadTexture(filenameBP)},
            {"bP1", LoadTexture(filenameBP)},
            {"bP2", LoadTexture(filenameBP)},
            {"bP3", LoadTexture(filenameBP)},
            {"bP4", LoadTexture(filenameBP)},
            {"bP5", LoadTexture(filenameBP)},
            {"bP6", LoadTexture(filenameBP)},
            {"bP7", LoadTexture(filenameBP)},
            {"wb", LoadTexture(filenameWB)},
            {"wB", LoadTexture(filenameWB)},
            {"wQ", LoadTexture(filenameWQ)},
            {"wK", LoadTexture(filenameWK)},
            {"wN", LoadTexture(filenameWN)},
            {"wn", LoadTexture(filenameWN)},
            {"wR", LoadTexture(filenameWR)},
            {"wr", LoadTexture(filenameWR)},
            {"wP0", LoadTexture(filenameWP)},
            {"wP1", LoadTexture(filenameWP)},
            {"wP2", LoadTexture(filenameWP)},
            {"wP3", LoadTexture(filenameWP)},
            {"wP4", LoadTexture(filenameWP)},
            {"wP5", LoadTexture(filenameWP)},
            {"wP6", LoadTexture(filenameWP)},
            {"wP7", LoadTexture(filenameWP)}
        };
    return vimrc;
}

std::pair<int, int> getPosXY(const std::string &figureType) {
    int i = figureType[0] == 'w' ? 6 : 0;
    while (i < CELLS_QUANT) {
        for (int j = 0; j < CELLS_QUANT; ++j) {
            if (figureType == pos[i][j]) return {j, i};
        }
        ++i;
    }
    return {0, 0};
}

void drawFigures(const textureMap &t, Board &board) {
    for (const auto& figure: t) {
        const double scaleFigureToCell = static_cast<double>(CELL_SIZE) / figure.second.width;
        const bool isFigureWhite = figure.first[0] == 'w';
        const std::pair<int, int> xy = getPosXY(figure.first);

        Figure newFigure(strToFigureType[figure.first], figure.second, isFigureWhite,
                         static_cast<float>(xy.first) * CELL_SIZE, static_cast<float>(xy.second) * CELL_SIZE);
        board.board[xy.first][xy.second].figure = newFigure;

        DrawTextureEx(newFigure.texture, {newFigure.x, newFigure.y},
                  0, static_cast<float>(scaleFigureToCell), WHITE);
    }
}

inline std::pair<int, int> getMousePosXY(const Vector2 &mousePos) {
    return {static_cast<int>(mousePos.x) / CELL_SIZE, static_cast<int>(mousePos.y) / CELL_SIZE};
}

static std::pair<int, int> draggedFigurePos {};
static bool isDragging { false };

void startDragFigures(Board& board, const Vector2& mousePos) {
    const std::pair<int, int> xy = getMousePosXY(mousePos);

    if (board.board[xy.first][xy.second].occupied()) {
        board.board[xy.first][xy.second].figure->active = true;
        draggedFigurePos = xy;
        isDragging = true;
    }
}

void updateDrawFigures(Board& board, const Vector2& mousePos) {
    if (isDragging) {
        Figure& figure = board.board[draggedFigurePos.first][draggedFigurePos.second].figure.value();

        figure.drawAtCursor(mousePos.x, mousePos.y);
    }
}

void endDragFigures(Board& board) {
    if (isDragging) {
        Figure& figure = board.board[draggedFigurePos.first][draggedFigurePos.second].figure.value();
        figure.active = false;

        figure.x = static_cast<float>(draggedFigurePos.first) * CELL_SIZE + CELL_SIZE / 2.0f;
        figure.y = static_cast<float>(draggedFigurePos.second) * CELL_SIZE + CELL_SIZE / 2.0f;

        figure.drawAtBoard(figure.x, figure.y);

        isDragging = false;
    }
}

void DragFigures(const Vector2& mousePos, Board& board) {
    if (!isDragging) {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            startDragFigures(board, mousePos);
        }
    } else {
        updateDrawFigures(board, mousePos);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            endDragFigures(board);
        }
    }
}

int main() {
    constexpr int SCREEN_WIDTH { CELL_SIZE * CELLS_QUANT };
    constexpr int SCREEN_HEIGHT { SCREEN_WIDTH + 150 };
    constexpr int FPS { 60 };

    Vector2 mousePosition { 0 };

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "ChessCPP");
    SetWindowIcon(LoadImage(filenameIcon));

    const textureMap guy { LoadData() };
    Board mainBoard;
    mainBoard.initBoard();

    SetTargetFPS(FPS);

    // Main game loop
    while (!WindowShouldClose()) {

        mousePosition = GetMousePosition();

        BeginDrawing();
        mainBoard.drawBoard();
        drawFigures(guy, mainBoard);

        if (isValidMove(mousePosition.x, mousePosition.y)) {
            DragFigures(mousePosition, mainBoard);
        }

        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    for (const auto& texture: guy) UnloadTexture(texture.second);

    CloseWindow();

    return 0;
}
