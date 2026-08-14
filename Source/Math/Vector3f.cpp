#include "Vector3f.h"


/// Оператор сложения двух векторов
Vector3f operator+(const Vector3f & lhs, const Vector3f & rhs)
{
  return Vector3f{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}
