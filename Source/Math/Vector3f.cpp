#include "Vector3f.h"

#include <cmath>

#include <Core/Exceptions/MathException.h>

//------------------------------------------------------------------------------
/**
    Оператор сложения векторов
*/
//---
Vector3f & Vector3f::operator+=(const Vector3f & other) noexcept
{
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}


//------------------------------------------------------------------------------
/**
    Оператор сложения векторов
*/
//---
Vector3f & Vector3f::operator-=(const Vector3f & other) noexcept
{
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}


//------------------------------------------------------------------------------
/**
    Оператор умножения на скаляр
*/
//---
Vector3f & Vector3f::operator*=(float a) noexcept
{
  x *= a;
  y *= a;
  z *= a;
  return *this;
}


//------------------------------------------------------------------------------
/**
    Оператор деления на скаляр
*/
//---
Vector3f & Vector3f::operator/=(float a)
{
  if (a == 0.0f)
    throw MathException("Division by zero");
  x /= a;
  y /= a;
  z /= a;
  return *this;
}


//------------------------------------------------------------------------------
/**
    Вычислить квадрат длины вектора
*/
//---
float Vector3f::LengthSquared() const noexcept
{
  return x * x + y * y + z * z;
}

//------------------------------------------------------------------------------
/**
    Вычислить длину вектора
*/
//---
float Vector3f::Length() const noexcept
{
  return std::sqrt(LengthSquared());
}


//------------------------------------------------------------------------------
/**
    Нормализовать вектор
*/
//---
Vector3f& Vector3f::Normalize()
{
  const auto length = Length();
  if (length == 0.0f)
    throw MathException("Cannot normalize zero vector");
  *this /= length;
  return *this;
}


//------------------------------------------------------------------------------
/**
    Нормализовать вектор
*/
//---
Vector3f Vector3f::Normalized() const
{
  Vector3f result = *this;
  result.Normalize();
  return result;
}


//------------------------------------------------------------------------------
/**
   Cкалярное произведение векторов
*/
//---
float Vector3f::Dot(const Vector3f & other) const noexcept
{
  return x * other.x + y * other.y + z * other.z;
}


/// Векторное произведение векторов
Vector3f Vector3f::Cross(const Vector3f & other) const noexcept
{
  Vector3f crossProduct;
  crossProduct.x = y * other.z - z * other.y;
  crossProduct.y = z * other.x - x * other.z;
  crossProduct.z = x * other.y - y * other.z;
  return crossProduct;
}


//------------------------------------------------------------------------------
/**
    Оператор сложения двух векторов
*/
//---
Vector3f operator+(Vector3f lhs, const Vector3f & rhs) noexcept
{
  lhs += rhs;
  return lhs;
}


//------------------------------------------------------------------------------
/**
    Оператор сложения двух векторов
*/
//---
Vector3f operator-(Vector3f lhs, const Vector3f & rhs) noexcept
{
  lhs -= rhs;
  return lhs;
}


//------------------------------------------------------------------------------
/**
    Оператор умножения на скаляр
*/
//---
Vector3f operator*(Vector3f lhs, float rhs) noexcept
{
  lhs *= rhs;
  return lhs;
}


//------------------------------------------------------------------------------
/**
    Оператор умножения на скаляр
*/
//---
Vector3f operator*(float lhs, const Vector3f & rhs) noexcept
{
  return rhs * lhs;
}


//------------------------------------------------------------------------------
/**
    Оператор деления вектора на скаляр
*/
//---
Vector3f operator/(Vector3f lhs, float rhs)
{
  lhs /= rhs;
  return lhs;
}
