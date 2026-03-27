#pragma once
#include <array>

class punto2D
{
private:
    std::array <int, 2> coords;

public:
    //constructor and deconstructor
    punto2D(int x = 0, int y = 0);
    punto2D(const std::array <int, 2>& coordinates);//overloading the construcotr
    ~punto2D() = default;

    //methods to read attributes
    int get_x() const;
    int get_y() const;
    std::array <int, 2> getCoordinates() const;

    //methods to set attributes
    void set_x(int x);
    void set_y(int y);
    void setCoordinates(const std::array <int, 2>& coordinates);
};