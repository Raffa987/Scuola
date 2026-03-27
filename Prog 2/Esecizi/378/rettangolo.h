#pragma once
#include <array>

class rettangolo
{
private:
    int height;
    int base;

    std::array<int, 2> bottomLeft;
    std::array<int, 2> topRight;

    int calcDimensions(const std::array<int, 2>& bottomL, const std::array<int, 2>& topR);
public:
    rettangolo(int h = 5, int b = 12);
    rettangolo(const std::array <int, 2>& boottomL, const std::array <int, 2>& topR);
    ~rettangolo() = default;

    int get_h() const;
    int get_b() const;

    void set_h(int h);
    void set_b(int b);

    int calcA() const;
    int calcP() const;
    float calc_d() const;

    bool isSquare() const;
};
