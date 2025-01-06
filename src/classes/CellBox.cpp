//
// Created by aviruk on 1/6/25.
//

#include "classes/CellBox.h"

CellBox::CellBox(const int topLeft, const int topRight, const int size): topLeft(topLeft), topRight(topRight), size(size) {}

sf::Vector2<int> CellBox::toMatrixCoordinates(CellBox cb) {

}

CellBox::~CellBox()  = default;