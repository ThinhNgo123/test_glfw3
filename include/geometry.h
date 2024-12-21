#pragma once
#include <cmath>
#include <iostream>

#define PI 3.14

float rad(float angle);
float deg(float angle);

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
        void print();
        Mat4f operator +(Mat4f& other) const;
        Mat4f operator *(Mat4f& other) const;
        friend Mat4f operator*(Mat4f mat1, Mat4f mat2);
    };

    template <int Number>
    class Vecf
    {
    private:
        float m_data[Number];
    public:
        Vecf() 
        {
            for (int i = 0; i < Number; i++)
            {
                m_data[i] = 0;
            }
        }

        ~Vecf() {}

        float get(int index) const
        {
            return m_data[index];
        }

        void set(int index, float value)
        {
            m_data[index] = value;
        }

        float length() const
        {
            float sumSquare = 0;
            for (int i = 0; i < Number; i++)
            {
                sumSquare += m_data[i] * m_data[i];
            }
            return sqrt(sumSquare);
        }

        float lengthSquare() const
        {
            float sumSquare = 0;
            for (int i = 0; i < Number; i++)
            {
                sumSquare += m_data[i] * m_data[i];
            }
            return sumSquare;
        }

        void normalize()
        {
            float len = length();
            if (len <= 0) return;
            for (int i = 0; i < Number; i++)
            {
                m_data[i] = m_data[i] / len;
            }
        }

        // Vecf<Number> operator +(const Vecf<Number>& other) const;
        // Vecf<Number> operator -(const Vecf<Number>& other) const;
        // Vecf<Number> operator *(const Vecf<Number>& other) const;
        // Vecf<Number> operator *(float scalar) const;

        float operator [](int index) const
        {
            return m_data[index];
        }

        float& operator [](int index)
        {
            return m_data[index];
        }
    };

    template <>
    class Vecf<3>
    {
    public:
        float x = 0, y = 0, z = 0;
    public:
        Vecf() 
        {
        }

        Vecf(float x, float y, float z) : x(x), y(y), z(z)
        {
        }

        ~Vecf() {}

        float get(int index) const
        {
            return (index == 0) ? (x) : ((index == 1) ? (y) : (z));
        }

        void set(int index, float value)
        {
            float &ref = (index == 0) ? (x) : ((index == 1) ? (y) : (z));
            ref = value;
        }

        float length() const
        {
            return sqrt(x * x + y * y + z * z);
        }

        float lengthSquare() const
        {
            return x * x + y * y + z * z;
        }

        void normalize()
        {
            float len = length();
            if (len <= 0) return;
            x /= len;
            y /= len;
            z /= len;
        }

        // Vecf<Number> operator +(const Vecf<Number>& other) const;
        // Vecf<Number> operator -(const Vecf<Number>& other) const;
        // Vecf<Number> operator *(const Vecf<Number>& other) const;
        // Vecf<Number> operator *(float scalar) const;

        float operator [](int index) const
        {
            return (index == 0) ? (x) : ((index == 1) ? (y) : (z));
        }

        float& operator [](int index)
        {
            return (index == 0) ? (x) : ((index == 1) ? (y) : (z));
        }
    };

    template <int Number>
    Vecf<Number> operator -(const Vecf<Number>& vec1, const Vecf<Number>& vec2)
    {
        Vecf<Number> result;
        for (int i = 0; i < Number; i++)
        {
            result.set(i, vec1.get(i) - vec2.get(i));
        }
        return result;
    }

    template <int Number>
    Vecf<Number> operator *(const Vecf<Number>& vec, float scalar)
    {
        Vecf<Number> result;
        for (int i = 0; i < Number; i++)
        {
            result.set(i, vec.get(i) * scalar);
        }
        return result;
    }

    template <int Number>
    std::ostream& operator <<(std::ostream& out, Vecf<Number>& vec)
    {
        out << "[";
        for (int i = 0; i < Number; i++)
        {
            out << vec[i] << " ";
        }
        out << "]";
        return out;
    }

    template <int Number>
    Vecf<Number> normalize(const Vecf<Number>& vec)
    {
        Vecf<Number> result;
        float len = vec.length();
        if (len <= 0) return Vecf<Number>();
        for (int i = 0; i < Number; i++)
        {
            result.set(i, vec.get(i) / len);
        }
        return result;
    }

    typedef Vecf<2> Vec2f;
    typedef Vecf<3> Vec3f;
    typedef Vecf<4> Vec4f;

    Vec3f cross(Vec3f v1, Vec3f v2);
    
    Mat4f operator *(Mat4f mat1, Mat4f mat2);

    Mat4f translate(float x, float y, float z);
    Mat4f rotateX(float angleX);
    Mat4f rotateY(float angleY);
    Mat4f rotateZ(float angleZ);
    Mat4f rotate(Mat4f& matrix, Vec3f& vec3, float angle);
    Mat4f scale(float scaleX, float scaleY, float scaleZ);
}