#pragma once

struct Vector2
{
    Vector2(const float x, const float y) : x(x), y(y) {}
    float x,y;

    static float getDistance(Vector2 v1, Vector2 v2)
    {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        return sqrt(dx * dx + dy * dy);
    }

    static Vector2 Add(Vector2 v1, Vector2 v2)
    {
        return Vector2(v1.x + v2.x, v1.y + v2.y);
    }
    
};
