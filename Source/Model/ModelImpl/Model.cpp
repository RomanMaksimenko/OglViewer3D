#include "Model.h"

#include <Math/AxisAlignedBoundedBox.h>
#include <Math/MathUtils.h>

//------------------------------------------------------------------------------
/**
   Переместить модель
*/
//---
Model::Model()
  : m_vertices{{-0.5, -0.5, 0.0}, {-0.5, 0.5, 0.0}, {0.5, 0.5, 0.0}, {0.5, -0.5, 0.0}}
  , m_indices{0, 1, 2, 2, 3, 0}
  , m_boundedBox(CalculateBoundedBox(m_vertices))
  , m_transform(Matrix4f::Identity())
{
}


//------------------------------------------------------------------------------
/**
   Переместить модель
*/
//---
void Model::Translate(float dx, float dy, float dz)
{
  m_transform[0][3] += dx;
  m_transform[1][3] += dy;
  m_transform[2][3] += dz;
}


//------------------------------------------------------------------------------
/**
   Повернуть модель
*/
//---
void Model::Rotate(float angleX, float angleY, float angleZ)
{
  Matrix4f rx, ry, rz;
  float x = AngleUtils::ToRadians(angleX);
  float y = AngleUtils::ToRadians(angleY);
  float z = AngleUtils::ToRadians(angleZ);

  rx[1][1] = cosf(x);
  rx[1][2] = -sinf(x);
  rx[2][1] = sinf(x);
  rx[2][2] = cosf(x);

  ry[0][0] = cosf(y);
  ry[0][2] = sinf(y);
  ry[2][0] = -sinf(y);
  ry[2][2] = cosf(y);

  rz[0][0] = cosf(z);
  rz[0][1] = -sinf(z);
  rz[1][0] = sinf(z);
  rz[1][1] = cosf(z);

  m_transform = m_transform * rx * ry * rz;
}


//------------------------------------------------------------------------------
/**
   Масштабировать
*/
//---
void Model::Scale(float sx, float sy, float sz)
{
  m_transform[0][0] += sx;
  m_transform[1][1] += sy;
  m_transform[2][2] += sz;
}


//------------------------------------------------------------------------------
/**
   Получить вершины для отрисовки
*/
//---
const std::vector<Vertex> & Model::GetVertices() const
{
  return m_vertices;
}


//------------------------------------------------------------------------------
/**
    Получить индексы порядка отрисовки вершин
*/
//---
const std::vector<unsigned int> & Model::GetIndices() const
{
  return m_indices;
}


//------------------------------------------------------------------------------
/**
    Получить матрицу трансформации
*/
//---
Matrix4f Model::GetTransformMatrix() const
{
  return m_transform;
}


//------------------------------------------------------------------------------
/**
    Получить ограничивающий объем модели
*/
//---
const AxisAlignedBoundedBox & Model::GetBoundedBox() const
{
  return m_boundedBox;
}
