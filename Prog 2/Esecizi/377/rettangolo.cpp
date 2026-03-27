#include "rettangolo.h"
#include <cmath>
#include <stdexcept>

rettangolo::rettangolo(float h, float b){
    set_b(b);
    set_h(h);
}

float rettangolo::get_h() const{
    return height;
}

float rettangolo::get_b() const{
    return base;
}

void rettangolo::set_b(float b){
    if(b <= 0) {
        throw std::invalid_argument("The base must be greater than 0");
    }
    base = b;
}

void rettangolo::set_h(float h){
    if(h <= 0) {
        throw std::invalid_argument("The height must be greater than 0");
    }
    height = h;
}

float rettangolo::calcA() const{
    return (base*height);
}

float rettangolo::calcP() const{
    return ((2 * base) + (2 * height));
}

float rettangolo::calc_d() const{
    return (sqrt((base * base) + (height * height)));
}

bool rettangolo::isSquare() const{
    if(base == height) return true;
    return false;
}