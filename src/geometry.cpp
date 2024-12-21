#include "geometry.h"
#include <iostream>
#include <cmath>

namespace Geometry
{
    Mat4f::Mat4f(): m_rowNumber(4), m_colNumber(4)
    {
        for (int rowIndex = 0; rowIndex < m_rowNumber; rowIndex++)
        {
            for (int colIndex = 0; colIndex < m_colNumber; colIndex++)
            {
                set(rowIndex, colIndex, (rowIndex == colIndex) ? 1 : 0); 
            }
        }
    }

    Mat4f::Mat4f(float *other) : m_rowNumber(4), m_colNumber(4)
    {
        for (int rowIndex = 0; rowIndex < m_rowNumber; rowIndex++)
        {
            for (int colIndex = 0; colIndex < m_colNumber; colIndex++)
            {
                set(rowIndex, colIndex, other[rowIndex * m_colNumber + colIndex]); 
            }
        }
    }

    Mat4f::Mat4f(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33
        ) : m_rowNumber(4), m_colNumber(4)
    {
        set(0, 0, m00);
        set(0, 1, m01);
        set(0, 2, m02);
        set(0, 3, m03);

        set(1, 0, m10);
        set(1, 1, m11);
        set(1, 2, m12);
        set(1, 3, m13);

        set(2, 0, m20);
        set(2, 1, m21);
        set(2, 2, m22);
        set(2, 3, m23);

        set(3, 0, m30);
        set(3, 1, m31);
        set(3, 2, m32);
        set(3, 3, m33);
    }

    float Mat4f::get(int rowIndex, int colIndex) const
    {
        return m_data[colIndex * m_rowNumber + rowIndex];
    }

    void Mat4f::set(int rowIndex, int colIndex, float value)
    {
        m_data[colIndex * m_rowNumber + rowIndex] = value;
    }

    const float *Mat4f::valuePtr() const
    {
        return &m_data[0];
    }

    Mat4f Mat4f::transpose()
    {
        std::cerr << "Transpose function is missing!" << std::endl;
        return Mat4f();
    }

    void Mat4f::print()
    {
        for (int i = 0; i < m_rowNumber; i++)
        {
            for (int j = 0; j < m_colNumber; j++)
            {
                std::cout << get(i, j) << "   ";
            }
            std::cout << std::endl;
        }
    }

    Mat4f Mat4f::operator+(Mat4f &other) const
    {
        Mat4f result;
        for (int i = 0; i < m_rowNumber; i++)
        {
            for (int j = 0; j < m_colNumber; j++)
            {
                result.set(i, j, get(i, j) + other.get(i, j));
            }
        }
        return result;
    }

    Mat4f Mat4f::operator*(Mat4f &other) const
    {
        Mat4f result;
        for (int i = 0; i < m_rowNumber; i++)
        {
            for (int j = 0; j < m_colNumber; j++)
            {
                float temp = 0;
                for (int k = 0; k < m_colNumber; k++)
                {
                    temp += get(i, k) * other.get(k, j);
                }
                result.set(i, j, temp);
            }
        }
        return result;
    }

    Mat4f translate(float x, float y, float z)
    {
        Mat4f result;
        //48->60 memcpy(&m_data[4 * 3], &vec3, sizeof(Vec3))
        result.set(0, 3, x);
        result.set(1, 3, y);
        result.set(2, 3, z);
        return result;
    }

    Mat4f rotateX(float angle)
    {
        Mat4f result;
        result.set(1, 1, std::cosf(angle));
        result.set(1, 2, -std::sinf(angle));
        result.set(2, 1, std::sinf(angle));
        result.set(2, 2, std::cosf(angle));
        return result;
    }

    Mat4f rotateY(float angle)
    {
        Mat4f result;
        result.set(0, 0, std::cosf(angle));
        result.set(0, 2, std::sinf(angle));
        result.set(2, 0, -std::sinf(angle));
        result.set(2, 2, std::cosf(angle));
        return result;
    }

    Mat4f rotateZ(float angle)
    {
        Mat4f result;
        result.set(0, 0, std::cos(angle));
        result.set(0, 1, -std::sin(angle));
        result.set(1, 0, std::sin(angle));
        result.set(1, 1, std::cos(angle));
        return result;
    }

    Mat4f rotate(Mat4f& matrix, Vec3f& vec3, float angle)
    {
        return Mat4f();
    }

    Mat4f scale(float scaleX, float scaleY, float scaleZ)
    {
        Mat4f result;
        result.set(0, 0, scaleX);
        result.set(1, 1, scaleY);
        result.set(2, 2, scaleZ);
        return result;
    }

    Vec3f cross(Vec3f v1, Vec3f v2)
    {
        Vec3f result;
        result.set(0, v1[1] * v2[2] - v1[2] * v2[1]);
        result.set(1, v1[2] * v2[0] - v1[0] * v2[2]);
        result.set(2, v1[0] * v2[1] - v1[1] * v2[0]);
        return result;
    }

    Mat4f operator*(Mat4f mat1, Mat4f mat2)
    {
        Mat4f result;
        for (int i = 0; i < result.m_rowNumber; i++)
        {
            for (int j = 0; j < result.m_colNumber; j++)
            {
                float temp = 0;
                for (int k = 0; k < mat1.m_colNumber; k++)
                {
                    temp += mat1.get(i, k) * mat2.get(k, j);
                }
                result.set(i, j, temp);
            }
        }
        return result;
    }
}

float rad(float angle)
{
    return (angle * PI) / 180;
}

float deg(float angle)
{
    return (angle * 180) / PI;
}
