////////////////////////////////////////////////////////////////////////////////
//
/// Math/Vector3f.h Вектор из трех вещественных чисел
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once


////////////////////////////////////////////////////////////////////////
//
/// Вектор из трех вещественных чисел
/**
*/
////////////////////////////////////////////////////////////////////////
struct Vector3f
{
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  /// Операторы
  Vector3f & operator+=(const Vector3f & other) noexcept;
  Vector3f & operator-=(const Vector3f & other) noexcept;
  Vector3f & operator*=(float a) noexcept;
  Vector3f & operator/=(float a);

  /// Квадрат длины
  float LengthSquared() const noexcept;
  /// Длина вектора
  float Length() const noexcept;
  /// Нормализовать вектор
  Vector3f & Normalize();
  /// Нормализовать вектор
  Vector3f Normalized() const;
  /// Скалярное произведение векторов
  float Dot(const Vector3f & other) const noexcept;
  /// Векторное произведение векторов
  Vector3f Cross(const Vector3f & other) const noexcept;
};

/// Оператор сложения двух векторов
Vector3f operator+(Vector3f lhs, const Vector3f & rhs) noexcept;
/// Оператор вычитания двух векторов
Vector3f operator-(Vector3f lhs, const Vector3f & rhs) noexcept;
/// Оператор умножения вектора на скаляр
Vector3f operator*(Vector3f lhs, float rhs) noexcept;
/// Оператор умножения вектора на скаляр
Vector3f operator*(float lhs, const Vector3f & rhs) noexcept;
/// Оператор деления вектора на скаляр
Vector3f operator/(Vector3f lhs, float rhs);