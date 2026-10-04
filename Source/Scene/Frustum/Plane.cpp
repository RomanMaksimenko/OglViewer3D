#include "Plane.h"

#include <Math/AxisAlignedBoundedBox.h>

//------------------------------------------------------------------------------
/**
   
*/
//---
Plane::Plane(const Vector3f & n, float offset)
  : m_normal(n)
  , m_offset(offset)
{
}


//------------------------------------------------------------------------------
/**
   Рассчитать расстояние до точки
*/
//---
float Plane::SignedDistanceToPoint(const Vector3f & point) const
{
  return m_normal.Dot(point) + m_offset;
}


//------------------------------------------------------------------------------
/**
   Расстояние от AABB до плоскости (до самой дальней точки)
    > 0 → AABB снаружи
    <= 0 → AABB внутри или пересекает
*/
//---
float Plane::DistanceToAABB(const AxisAlignedBoundedBox & box) const
{
  auto supportPoint = GetSupportPoint(box);
  return SignedDistanceToPoint(supportPoint);
}


//------------------------------------------------------------------------------
/**
   Получить самую удаленную точку куба
*/
//--- 
Vector3f Plane::GetSupportPoint(const AxisAlignedBoundedBox & aabb) const
{
  return {m_normal.x > 0 ? aabb.Min().x : aabb.Max().x, m_normal.y > 0 ? aabb.Min().y : aabb.Max().y,
          m_normal.z > 0 ? aabb.Min().z : aabb.Max().z};
}
