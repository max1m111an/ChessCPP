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

#include "cell.h"
#include "raylib.h"

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
    Cell cell;
    bool alive;
    bool isWhite = false;
    float x = 0.0f;
    float y = 0.0f;

    void moveFigure(float, float);
    void dragAtCursor(float, float) const;
    virtual FigureType getType();

    Figure(const Texture2D &texture, const float x, const float y, const Cell newCell, const bool isWhite):
    texture(texture), cell(newCell), alive(true), isWhite(isWhite), x(x), y(y){}
};

class Pawn : public Figure {
    public:
    Pawn(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}

    FigureType getType() override;
};

class Knight : public Figure {
    public:
    Knight(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}
    FigureType getType() override;

};

class Bishop : public Figure {
    public:
    Bishop(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}
    FigureType getType() override;

};

class Rook : public Figure {
    public:
    Rook(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}
    FigureType getType() override;
};

class King : public Figure {
    public:
    King(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}
    FigureType getType() override;
};

class Queen : public Figure {
    public:
    Queen(const Texture2D& texture, const float x, const float y, const Cell cell, const bool white):
    Figure(texture, x, y, cell, white){}
    FigureType getType() override;
};

#endif //FIGURES_H