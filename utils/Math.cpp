#include "Math.h"
#include <cmath>

#define PI 3.14159265

Vector2 Math::CalculateAngles(Vector3 from, Vector3 to)
{
    float yaw;
    float pitch;

    float deltaX = to.x - from.x;
    float deltaY = to.y - from.y;

    yaw = static_cast<float>(std::atan2(deltaY, deltaX) * 180 / PI); // convert to degrees

    float deltaZ = to.z - from.z;
    double distance = sqrt(pow(deltaX, 2) + pow(deltaY, 2));

    pitch = -static_cast<float>(std::atan2(deltaZ, distance) * 180 / PI);

    return Vector2(yaw, pitch);
}
