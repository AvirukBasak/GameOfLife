//
// Created by aviruk on 1/6/25.
//

#ifndef CLASSES_CELLBOX_H
#define CLASSES_CELLBOX_H

#include "SFML/Graphics/Rect.hpp"

class CellBox {
public:
    int topLeft;
    int topRight;
    int size;

    CellBox(const int topLeft, const int topRight, const int size);

    static sf::Vector2<int> toMatrixCoordinates(CellBox cb);

    ~CellBox();
};

#endif //CLASSES_CELLBOX_H
