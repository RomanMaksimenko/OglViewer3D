#include "Matrix.h"


//------------------------------------------------------------------------------
/**
   Конструктор по умолчанию. Создает единичную матрицу
*/
//---
Matrix4f::Matrix4f()
  : m_matrix{{1.0f, 0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f}}
{
}


//------------------------------------------------------------------------------
/**
   Конструктор от набора значений
*/
//---
Matrix4f::Matrix4f(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32,
                   float a33, float a34, float a41, float a42, float a43, float a44)
  : m_matrix{{a11, a12, a13, a14}, {a21, a22, a23, a24}, {a31, a32, a33, a34}, {a41, a42, a43, a44}}
{
}


//------------------------------------------------------------------------------
/**
   Оператор доступа
*/
//---
MatrixRow<float, 4> Matrix4f::operator[](size_t index) noexcept
{
  assert(index < 4);
  return MatrixRow<float, 4>(m_matrix[index]);
}


//------------------------------------------------------------------------------
/**
   Оператор доступа
*/
//---
const MatrixRow<const float, 4> Matrix4f::operator[](size_t index) const noexcept
{
  assert(index < 4);
  return MatrixRow<const float, 4>(m_matrix[index]);
}


//------------------------------------------------------------------------------
/**
   Оператор умножения матрицы на матрицу
*/
//---
Matrix4f Matrix4f::operator*(const Matrix4f & other) const
{
  Matrix4f result = Zero();

  for (size_t i = 0; i != 4; ++i)
    for (size_t j = 0; j != 4; ++j)
      for (size_t k = 0; k != 4; ++k)
        result[i][j] += m_matrix[i][k] * other.m_matrix[k][j];

  return result;
}

