#pragma once

namespace Geometry
{
    /* 
    Mat4f is class stored each column
    */
    class Mat4f
    {
    private:
        float m_data[16];
        int m_rowNumber, m_colNumber;
    public:
        Mat4f();
        Mat4f(float *other);
        Mat4f(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33
        );
        float get(int row, int col) const;
        void set(int row, int col, float value);
        const float *valuePtr() const;
        Mat4f transpose();
        Mat4f operator +(Mat4f& other) const;
        Mat4f operator *(Mat4f& other) const;
    };

    template <int Number>
    class Vec
    {
    private:
        float m_data[Number];
    public:
        Vec();
        ~Vec();
        float get(int index) const;
        void set(int index, float value);
        Vec<Number> operator +(Vec<Number>& other) const;
        Vec<Number> operator *(Vec<Number>& other) const;
        Vec<Number> operator *(float scalar) const;
    };

    typedef Vec<2> Vec2;
    typedef Vec<3> Vec3;
    typedef Vec<4> Vec4;

    Mat4f translate(Mat4f& matrix, Vec3& vec3);
    Mat4f rotate(Mat4f& matrix, float angleX, float angleY, float angleZ);
    Mat4f rotate(Mat4f& matrix, Vec3& vec3, float angle);
    Mat4f scale(Mat4f& matrix, Vec3& vec3);
}