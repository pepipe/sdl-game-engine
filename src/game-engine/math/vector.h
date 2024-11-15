#pragma once

namespace GameEngine::Math
{
    struct Vector2D {
        float x;
        float y;

        explicit Vector2D(const float x = 0.0f, const float y = 0.0f) : x(x), y(y) {}
    };

    struct Vector3D {
        float x;
        float y;
        float z;

        explicit Vector3D(const float x = 0.0f, const float y = 0.0f, const float z = 0.0f) : x(x), y(y), z(z) {}
    };
}