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

        Vec2 GetNormalized() const;

        Vec2 GetRotated(const float& d) const;

        float Magnitude() const;
        
        float Distance(const Vec2& v) const;

        float XAxisInclination() const;

        Vec2& operator+=(const Vec2& rhs);
        Vec2& operator-=(const Vec2& rhs);
        Vec2& operator*=(const float& rhs);
        Vec2& operator=(const Vec2& rhs);

        friend Vec2 operator+(Vec2 lhs, const Vec2& rhs) {
            lhs += rhs;
            return lhs;
        }

        friend Vec2 operator-(Vec2 lhs, const Vec2& rhs) {
            lhs -= rhs;
            return lhs;
        }
        
        friend Vec2 operator*(Vec2 lhs, const float& rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend Vec2 operator*(const float& lhs, Vec2 rhs) {
            rhs *= lhs;
            return rhs;
        }

        std::string ToString() const {
            return std::string("x:") + std::to_string(x) + std::string(" y:") + std::to_string(y);
        }
        
        static float XAxisLineInclination(const Vec2& v1, const Vec2& v2);
        
        float x;
        float y;
};

#endif
