////////////////////////////////////////////////////////////////////////////////
//
/// Math/Matrix.h содержит класс и функции для работы с матрицами
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cassert>


////////////////////////////////////////////////////////////////////////
//
/// Вспомогательный класс для организации доступа к элементам матрицы
/**
*/
////////////////////////////////////////////////////////////////////////
template<typename T, size_t len>
class MatrixRow
{
  T * m_row;

public:
  explicit MatrixRow(T * r) noexcept
    : m_row(r)
  {
  }
  const T & operator[](size_t index) const noexcept
  {
    assert(index < len);
    return m_row[index];
  }

  T & operator[](size_t index) noexcept
  {
    assert(index < len);
    return m_row[index];
  }
};


////////////////////////////////////////////////////////////////////////
//
/// Класс матрицы веществнных чисел размерности 4 х 4
/**
*  Матрица хранится в row-major порядке: m_matrix[row][col].
   Вектор-столбец v, преобразование: v' = M * v.
   Порядок комбинирования трансформаций: M_total = M_proj * M_view * M_model.
*/
////////////////////////////////////////////////////////////////////////
class Matrix4f
{
  float m_matrix[4][4];

public:
  Matrix4f();
  Matrix4f(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32,
           float a33, float a34, float a41, float a42, float a43, float a44);

  /// Операторы доступа
  MatrixRow<float, 4> operator[](size_t index) noexcept;
  const MatrixRow<const float, 4> operator[](size_t index) const noexcept;

  /// Оператор умножения матрицы на матрицу
  Matrix4f operator*(const Matrix4f & other) const;

  /// Нулевая матрица
  static Matrix4f Zero() noexcept
  {
    return Matrix4f{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
  }

  /// Единичная матрица
  static Matrix4f Identity() noexcept
  {
    return Matrix4f();
  }
};
