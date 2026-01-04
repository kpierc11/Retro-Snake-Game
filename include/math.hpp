#pragma once
#include <cmath>

namespace GameMath
{
    struct Vector
    {
        float x;
        float y;

        Vector() : x(0), y(0) {}
        Vector(float x, float y) : x(x), y(y) {}
    };

    inline Vector vectorAddition(const Vector &a, const Vector &b)
    {
        return Vector(a.x + b.x, a.y + b.y);
    }

    // It's Lerping Time
    inline Vector Lerp(const Vector &a, const Vector &b, float t)
    {
        return Vector(
            a.x + (b.x - a.x) * t,
            a.y + (b.y - a.y) * t);
    }
}