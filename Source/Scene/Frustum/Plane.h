////////////////////////////////////////////////////////////////////////////////
//
/// Scene/Frustum/Plane.h содержит объявление класса плоскости
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Math/Vector3f.h>


class AxisAlignedBoundedBox;


////////////////////////////////////////////////////////////////////////////////
//
/// Класс описывающий плоскость
/**
  Опсывает плоскость, заданную нормалью и смещением относительно начала координат.
*/
////////////////////////////////////////////////////////////////////////////////
class Plane
{
  Vector3f m_normal;
  float m_offset;

public:
  Plane() = default;
  Plane(const Vector3f & n, float offset);
  // Рассчитать расстояние до точки
  float SignedDistanceToPoint(const Vector3f & point) const;
  // Рассчитать расттояние до ограничивающего куба
  float DistanceToAABB(const AxisAlignedBoundedBox & box) const;

  private:
  Vector3f GetSupportPoint(const AxisAlignedBoundedBox & box) const;
};