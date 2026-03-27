#include "rettangolo.h"
#include <cmath>
#include <stdexcept>

rettangolo::rettangolo(int h, int b){
    set_b(b);
    set_h(h);
}

int rettangolo::get_h() const{
    return height;
}

int rettangolo::get_b() const{
    return base;
}

void rettangolo::set_b(int b){
    if(b <= 0) {
        throw std::invalid_argument("The base must be greater than 0");
    }
    base = b;
}

void rettangolo::set_h(int h){
    if(h <= 0) {
        throw std::invalid_argument("The height must be greater than 0");
    }
    height = h;
}

int rettangolo::calcA() const{
    return (base*height);
}

int rettangolo::calcP() const{
    return ((2 * base) + (2 * height));
}

float rettangolo::calc_d() const{
    return (sqrt(((float)base * base) + ((float)height * height)));
}

bool rettangolo::isSquare() const{
    if(base == height) return true;
    return false;
}

int calcDimensions(const std::array<int, 2>& bottomL, const std::array<int, 2>& topR){
    
}