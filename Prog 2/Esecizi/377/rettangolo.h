#pragma once

class rettangolo
{
private:
    float height;
    float base;
public:
    rettangolo(float h = 5.0f, float b = 12.0f);
    ~rettangolo() = default;
    float get_h() const;
    float get_b() const;
    void set_h(float h);
    void set_b(float b);
    float calcA() const;
    float calcP() const;
    float calc_d() const;
    bool isSquare() const;
};
