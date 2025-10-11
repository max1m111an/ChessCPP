#ifndef CELL_H
#define CELL_H
#include <iostream>

class Cell {
    int col = 0;
    int row = 0;

public:
    bool isBlack = false;
    Cell(const int c, const int r, const bool isBl) {
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            row = r;
            col = c;
            isBlack = isBl;
        }
        else {
            std::cout<< "fyn🌹" << std::endl;
        }
    }
    int getCol() const {return col;}
    int getRow() const {return row;}
    void setCol(const int c) {col = c;}
    void setRow(const int r) {row = r;}
};

#endif //CELL_H
