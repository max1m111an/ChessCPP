#ifndef FIGURES_H
#define FIGURES_H

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

#include <vector>

#include "raylib.h"
#include "Vector2Int.h"

inline constexpr int CELL_SIZE = 80;
inline constexpr int CELLS_QUANT = 8;
inline constexpr int NUMBERS_CELL_WIDTH { 20 };
inline constexpr int NUMBERS_CELL_HEIGHT { CELL_SIZE };
inline constexpr int LETTERS_CELL_WIDTH { CELL_SIZE };
inline constexpr int LETTERS_CELL_HEIGHT { 20 };

enum FigureType {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    KING,
    QUEEN,
    NONE,
};

class Figure {
public:
    virtual ~Figure() = default;
    Figure() = default;

    Texture2D texture;
    bool alive;
    bool isWhite = false;
    float x = 0.0f;
    float y = 0.0f;

    void moveFigure(float, float);
    void dragAtCursor(float, float) const;
    void drawFigure() const;
    virtual FigureType getType();
    virtual std::vector<Vector2Int> getAllowMoves() const;

    Figure(const Texture2D &texture, const float x, const float y, const bool isWhite):
    texture(texture), alive(true), isWhite(isWhite), x(x), y(y) {}
};

class Pawn : public Figure {
    public:
    Pawn(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite) {}

    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;
};

class Knight : public Figure {
    public:
    Knight(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite){}
    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;

};

class Bishop : public Figure {
    public:
    Bishop(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite){}
    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;

};

class Rook : public Figure {
    public:
    Rook(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite){}
    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;

};

class King : public Figure {
    public:
    King(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite){}
    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;

};

class Queen : public Figure {
    public:
    Queen(const Texture2D& texture, const float x, const float y, const bool isWhite):
    Figure(texture, x, y, isWhite){}
    FigureType getType() override;
    std::vector<Vector2Int> getAllowMoves() const override;

};

#endif //FIGURES_H