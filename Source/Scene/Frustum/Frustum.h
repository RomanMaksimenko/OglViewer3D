////////////////////////////////////////////////////////////////////////////////
//
/// Scene/Frustum/Frustum.h содержит объявление класса объема, видимого камерой
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <array>

#include <Scene/Frustum/Plane.h>

class AxisAlignedBoundedBox;
class Matrix4f;

////////////////////////////////////////////////////////////////////////////////
//
/// Класс описывающий объем видимости камеры
/**
   Задается 6 плоскостями отсечения
*/
////////////////////////////////////////////////////////////////////////////////
class Frustum
{
  std::array<Plane, 6> m_planes;

public:
  Frustum(const Matrix4f & viewProjection);
  // Попадает ли ограничивающий куб модели внутрь Frustum
  bool IsAABBInside(const AxisAlignedBoundedBox & box) const;
};
