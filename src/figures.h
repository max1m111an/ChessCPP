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

    Texture2D texture;
    Cell cell;
    bool alive;
    bool isWhite = false;
    float x = 0.0f;
    float y = 0.0f;

    void moveFigure(float, float);
    void dragAtCursor(float, float) const;

    virtual FigureType getType();

    Figure() = default;

    Figure(const Texture2D &texture, const float x, const float y, const Cell newCell):
    texture(texture), cell(newCell), alive(true), x(x), y(y){}
};

class Pawn : public Figure {
    public:
    Pawn();
    FigureType getType() override;
};

class Knight : public Figure {
    public:
    Knight();
    FigureType getType() override;

};

class Bishop : public Figure {
    public:
    Bishop();
    FigureType getType() override;

};

class Rook : public Figure {
    public:
    Rook();
    FigureType getType() override;
};

class King : public Figure {
    public:
    King();
    FigureType getType() override;
};

class Queen : public Figure {
    public:
    Queen();
    FigureType getType() override;
};

#endif //FIGURES_H