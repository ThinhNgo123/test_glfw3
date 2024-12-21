#pragma once
#include "geometry.h"

namespace Camera
{
    using namespace Geometry;

    Mat4f lookAt(Vec3f eye, Vec3f center, Vec3f up);
    // left, rigth, bottom, top, near, far
    Mat4f ortho(float l, float r, float b, float t, float n, float f);
    // left, right, bottom, top, near, far
    Mat4f frustum(float l, float r, float b, float t, float n, float f);
    Mat4f perspective(float fov, float ratio, float near, float far);
} // namespace Camera
