////////////////////////////////////////////////////////////////////////////////
//
/// Math/AxisAlignedBoundedBox.h содержит класс, описывающий ограничивающий объем модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Math/Vertex.h"

////////////////////////////////////////////////////////////////////////
//
/// Класс, описывающий ограничивающий куб модели
/**
*   Куб задается параллелепипедом, хранятся координаты диагонали
*/
////////////////////////////////////////////////////////////////////////
class AxisAlignedBoundedBox
{
  Vector3f m_min;///< { x_min, y_min, z_min }
  Vector3f m_max;///< { x_max, y_max, z_max }

  public:
  AxisAlignedBoundedBox(const Vector3f & min, const Vector3f & max) noexcept;

  /// Получить минимальную точку
  const Vector3f & Min() const noexcept { return m_min; }
  /// Получить максимальную точку
  const Vector3f & Max() const noexcept { return m_max; }
};

/// Рассчитать ограничивающий куб
AxisAlignedBoundedBox CalculateBoundedBox(const std::vector<Vertex> & vertices);
