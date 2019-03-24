#include "Vec2.hpp"
#include <math.h>

Vec2::Vec2() : x(0), y(0) {}

Vec2::Vec2(float x, float y) : x(x), y(y) {}

Vec2 Vec2::GetNormalized() const {
    float magnitude = Magnitude();
    return Vec2(x / magnitude, y / magnitude);
}

Vec2 Vec2::GetRotated(const float& d) const {
    float xl = x * cos(d) - y * sin(d);
    float yl = y * cos(d) - x * sin(d);
    return Vec2(xl, yl);
}

float Vec2::Magnitude() const {
    return sqrt(x*x + y*y);
}

float Vec2::Distance(const Vec2& v) const {
    Vec2 diff = *this - v;
    return diff.Magnitude();
}

float Vec2::XAxisInclination() const {
    return -atan2(y, x);
}

Vec2& Vec2::operator+=(const Vec2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::operator-=(const Vec2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2& Vec2::operator*=(const float& rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

Vec2& Vec2::operator=(const Vec2& v) {
    x = v.x;
    y = v.y;
    return *this;
}
