#ifndef VEC2_H
#define VEC2_H

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                  INCLUDES E DEFINES
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <string>

class Vec2 {
    public:
        Vec2();

        Vec2(float x, float y);

        Vec2 Normalized();

        float Magnitude();
        
        float Distance(const Vec2& v);

        float XAxisInclination();

        Vec2& operator+=(const Vec2& rhs);
        Vec2& operator-=(const Vec2& rhs);
        Vec2& operator*=(const int& rhs);
        Vec2& operator=(const Vec2& rhs);

        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
            lhs += rhs;
            return lhs;
        }

        friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) {
            lhs -= rhs;
            return lhs;
        }
        
        friend Vec2 operator*(Vec2 lhs, const int& rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend Vec2 operator*(const int& lhs, Vec2 rhs) {
            rhs *= lhs;
            return rhs;
        }

        std::string ToString() {
            return std::string("x:") + std::to_string(x) + std::string(" y:") + std::to_string(y);
        }

        Vec2& Rotate(const float& d);
        
        static float XAxisLineInclination(const Vec2& v1, const Vec2& v2);
    private:
      float x;
      float y;
};

#endif
