#include "AxisAlignedBoundedBox.h"

#include <cassert>

//------------------------------------------------------------------------------
/**
*/
//---
AxisAlignedBoundedBox::AxisAlignedBoundedBox(const Vector3f & min, const Vector3f & max) noexcept
  : m_min(min)
  , m_max(max)
{
}


//------------------------------------------------------------------------------
/**
   Рассчитать ограничивающий куб
*/
//---
AxisAlignedBoundedBox CalculateBoundedBox(const std::vector<Vertex> & vertices)
{
  assert(!vertices.empty());

  Vector3f min = vertices[0].m_position;
  Vector3f max = vertices[0].m_position;

  for (auto && vertex : vertices)
  {
    min.x = std::min(min.x, vertex.m_position.x);
    min.y = std::min(min.y, vertex.m_position.y);
    min.z = std::min(min.z, vertex.m_position.z);

    max.x = std::max(max.x, vertex.m_position.x);
    max.y = std::max(max.y, vertex.m_position.y);
    max.z = std::max(max.z, vertex.m_position.z);
  }

  return AxisAlignedBoundedBox(min, max);
}
