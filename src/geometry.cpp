#include "geometry.h"
#include <iostream>

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
        )
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
                for (int k = 0; k < m_colNumber; k++)
                {
                    float temp = 0;
                    temp += get(i, k) + other.get(k, j);
                    result.set(i, j, temp);
                }
            }
        }
        return result;
    }

    // Vec::Vec()
    // {
    //     for (int i = 0; i < Number; i++)
    //     {
    //         m_data[i] = 0;
    //     }
    // }

    // Vec<Number>::~Vec()
    // {

    // }

    // float Vec<Number>::get(int index) const
    // {
    //     return 0;
    // }

    // void Vec<Number>::set(int index, float value)
    // {

    // }

    // Vec<Number> Vec<Number>::operator +(Vec<Number>& other) const
    // {
    //     return Vec<Number>();
    // }

    // Vec<Number> Vec<Number>::operator *(Vec<Number>& other) const
    // {
    //     return Vec<Number>();
    // }

    // Vec<Number> Vec<Number>::operator *(float scalar) const
    // {
    //     return Vec<Number>();
    // }

    Mat4f translate(Mat4f& matrix, Vec3& vec3)
    {
        Mat4f result;
        for (int i = 0; i < m_c)
        return Mat4f(
            get(0, 0)
        );
    }

    Mat4f rotate(Mat4f& matrix, float angleX, float angleY, float angleZ)
    {
        return Mat4f(

        );
    }

    Mat4f rotate(Mat4f& matrix, Vec3& vec3, float angle)
    {
        return Mat4f();
    }

    Mat4f scale(Mat4f& matrix, Vec3& vec3)
    {
        return Mat4f();
    }
}