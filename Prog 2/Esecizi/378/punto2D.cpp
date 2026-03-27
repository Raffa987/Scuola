#include <array>
#include "punto2D.h"

punto2D::punto2D(int x, int y) {
    set_x(x);
    set_y(y);
}

punto2D::punto2D(const std::array <int, 2>& coordinates) {
    setCoordinates(coordinates);
}

void punto2D::set_x(int x) {
    coords[0] = x;
}

void punto2D::set_y(int y) {
    coords[1] = y;
}

void punto2D::setCoordinates(const std::array <int, 2>& coordinates) {
    coords = coordinates;
}

int punto2D::get_x() const {
    return coords[0];
}

int punto2D::get_y() const {
    return coords[1];
}

std::array <int, 2> punto2D::getCoordinates() const {
    return coords;
}
