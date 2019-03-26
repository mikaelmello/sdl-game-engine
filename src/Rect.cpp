#include "Rect.hpp"
#include "Vec2.hpp"

Rect::Rect() : x(0), y(0), w(0), h(0) {}

Rect::Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

float Rect::Distance(const Rect& rect) const {
    Vec2 c1 = this->Center();
    Vec2 c2 = rect.Center();
    return c1.Distance(c2);
}

Vec2 Rect::Center() const {
    return Vec2(x + w/2, y + h/2);
}

Rect Rect::GetCentered(Vec2 pos) const {
    return GetCentered(pos.x, pos.y);
}

Rect Rect::GetCentered(float centerX, float centerY) const {
    return Rect(centerX - w/2, centerY - h/2, w, h);
}

bool Rect::Contains(const Vec2& point) const {
    if (x > point.x || (x+w) < point.x) {
        return false;
    } else if (y > point.y || (y+h) < point.y) {
        return false;
    }
    return true;
}

Rect& Rect::operator+=(const Vec2& rhs) {
    w += rhs.x;
    h += rhs.y;
    return *this;
}

Rect& Rect::operator=(const Rect& v) {
    x = v.x;
    y = v.y;
    w = v.w;
    h = v.h;
    return *this;
}
