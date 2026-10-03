#include "Frustum.h"

#include <Math/Matrix.h>

//------------------------------------------------------------------------------
/**
   
*/
//---
Frustum::Frustum(const Matrix4f & viewProjection)
{
  // Левая плоскость
  m_planes[0] = Plane(Vector3f(viewProjection[3][0] + viewProjection[0][0], viewProjection[3][1] + viewProjection[0][1], viewProjection[3][2] + viewProjection[0][2]), viewProjection[3][3] + viewProjection[0][3]);
  // Правая плоскость
  m_planes[1] = Plane(Vector3f(viewProjection[3][0] - viewProjection[0][0], viewProjection[3][1] - viewProjection[0][1], viewProjection[3][2] - viewProjection[0][2]), viewProjection[3][3] - viewProjection[0][3]);
  // Нижняя плоскость
  m_planes[2] = Plane(Vector3f(viewProjection[3][0] + viewProjection[1][0], viewProjection[3][1] + viewProjection[1][1], viewProjection[3][2] + viewProjection[1][2]), viewProjection[3][3] + viewProjection[1][3]);
  // Верхняя плоскость
  m_planes[3] = Plane(Vector3f(viewProjection[3][0] - viewProjection[1][0], viewProjection[3][1] - viewProjection[1][1], viewProjection[3][2] - viewProjection[1][2]), viewProjection[3][3] - viewProjection[1][3]);
  // Ближняя плоскость
  m_planes[4] = Plane(Vector3f(viewProjection[3][0] + viewProjection[2][0], viewProjection[3][1] + viewProjection[2][1], viewProjection[3][2] + viewProjection[2][2]), viewProjection[3][3] + viewProjection[2][3]);
  // Дальняя плоскость
  m_planes[5] = Plane(Vector3f(viewProjection[3][0] - viewProjection[2][0], viewProjection[3][1] - viewProjection[2][1], viewProjection[3][2] - viewProjection[2][2]), viewProjection[3][3] - viewProjection[2][3]);
}


//------------------------------------------------------------------------------
/**
   Попадает ли ограничивающий куб модели внутрь Frustum
*/
//---
bool Frustum::IsAABBInside(const AxisAlignedBoundedBox & box) const
{
  for (auto && clip : m_planes)
    if (clip.DistanceToAABB(box) > 0.0f)
      return false;
  return true;
}
