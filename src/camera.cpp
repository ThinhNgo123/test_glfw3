#include "camera.h"
#include <cmath>
#include <iostream>

namespace Camera
{
    Mat4f lookAt(Vec3f eye, Vec3f center, Vec3f up)
    {
        Vec3f direction = normalize(eye - center);
        Vec3f right = normalize(cross(up, direction));
        Vec3f newUp = normalize(cross(direction, right));
        // std::cout << direction << std::endl; 
        // std::cout << right << std::endl; 
        // std::cout << newUp << std::endl; 
        return Mat4f(
                right[0],     right[1],     right[2], 0,
                newUp[0],     newUp[1],     newUp[2], 0,
            direction[0], direction[1], direction[2], 0,
                       0,            0,            0, 1
        ) * translate(-eye[0], -eye[1], -eye[2]);
    }

    Mat4f ortho(float l, float r, float b, float t, float n, float f)
    {
        return Mat4f(
            2 / (r - l),           0,           0,   -(r + l) / (r -l),
                      0, 2 / (t - b),           0, - (t + b) / (t - b),
                      0,           0, 2 / (n - f), - (f + n) / (f - n),
                      0,           0,           0,                   1
        );
    }

    Mat4f frustum(float l, float r, float b, float t, float n, float f)
    {
        // std::cout << "hello" << std::endl;
        return Mat4f(
            (2 * n) / (r - l),                 0,   (r + l) / (r - l),                      0,
                            0, (2 * n) / (t - b),   (t + b) / (t - b),                      0,
                            0,                 0, - (f + n) / (f - n), (-2 * f * n) / (f - n),
                            0,                 0,                  -1,                      0
        );
        // return Mat4f(
        //     0, 0, 1, 1,
        //     0, 0, 1, 1,
        //     0, 0, 1, 1,
        //     0, 0, 1, 1
        // );
    }

    Mat4f perspective(float fov, float ratio, float near, float far)
    {
        // std::cout << "fov = " << fov << std::endl;
        // std::cout << "ratio = " << ratio << std::endl;
        // std::cout << "near = " << near << std::endl;
        // std::cout << "far = " << far << std::endl;
        float height = 2 * near * std::tan(fov / 2);
        float width = ratio * height;
        // Mat4f frustumMatrix = frustum(-width / 2, width / 2, -height / 2, height / 2, near, far);
        // frustumMatrix.print();
        // return frustumMatrix;
        return frustum(-width / 2, width / 2, -height / 2, height / 2, near, far);
    }
} // namespace Camera
