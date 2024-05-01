#pragma once
#include <cmath>

struct Vector3
{
    Vector3() = default;
    constexpr Vector3(const float x, const float y, const float z) noexcept : x(x), y(y), z(z) {}
    float x,y,z;

    constexpr const Vector3& operator-(const Vector3& other) const noexcept
    {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    constexpr const Vector3& operator+(const Vector3& other) const noexcept
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }
    
    constexpr const Vector3& operator/(const float factor) const noexcept
    {
        return Vector3(x / factor, y / factor, z / factor);
    }
    
    constexpr const Vector3& operator*(const float factor) const noexcept
    {
        return Vector3(x * factor, y * factor, z * factor);
    }
    
    static float getDistance(Vector3 v1, Vector3 v2)
    {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        float dz = v1.z - v2.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

};
