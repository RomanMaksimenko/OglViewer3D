#include "Model.h"

#include <Math/AxisAlignedBoundedBox.h>

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
}


//------------------------------------------------------------------------------
/**
   Масштабировать
*/
//---
void Model::Scale(float sx, float sy, float sz)
{
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
