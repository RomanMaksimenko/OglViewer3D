#include "Model.h"

#include <Math/AxisAlignedBoundedBox.h>
#include <Math/MathUtils.h>


namespace VectorUtils
{

Vector3f & operator+=(Vector3f & lhs, const Vector3f & rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

} // namespace VectorUtils

//------------------------------------------------------------------------------
/**
   Переместить модель
*/
//---
Model::Model()
  : m_vertices{{-0.5f, -0.5f, -0.5f}, {-0.5f, 0.5f, -0.5f}, {0.5f, 0.5f, -0.5f}, {0.5f, -0.5f, -0.5f},
               {-0.5f, -0.5f, 0.5f},  {-0.5f, 0.5f, 0.5f},  {0.5f, 0.5f, 0.5f},  {0.5f, -0.5f, 0.5f}}
  , m_indices{0, 2, 1, 0, 3, 2, 4, 6, 5, 4, 7, 6, 0, 5, 1, 0, 4, 5, 3, 2, 6, 3, 6, 7, 1, 2, 6, 1, 6, 5, 0, 3, 7, 0, 7, 4}
  , m_boundedBox(CalculateBoundedBox(m_vertices))
  , m_position{0.0, 0.0, -2.0}
{
}


//------------------------------------------------------------------------------
/**
   Переместить модель
*/
//---
void Model::Translate(float dx, float dy, float dz)
{
  m_position = VectorUtils::operator+=(m_position,Vector3f{dx, dy, dz});
}


//------------------------------------------------------------------------------
/**
   Повернуть модель
*/
//---
void Model::Rotate(float angleX, float angleY, float angleZ)
{
  m_rotationX += angleX;
  m_rotationY += angleY;
  m_rotationZ += angleZ;
}


//------------------------------------------------------------------------------
/**
   Масштабировать
*/
//---
void Model::Scale(float scale)
{
  m_scale += scale;
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
  Matrix4f Translation = Matrix4f::Identity();
  Translation[0][3] = -m_position.x;
  Translation[1][3] = -m_position.y;
  Translation[2][3] = -m_position.z;

  Matrix4f Scale = Matrix4f::Identity();
  Scale[0][0] += m_scale;
  Scale[1][1] += m_scale;
  Scale[2][2] += m_scale;

  return Translation * GetRotationMatrix() * Scale;
}

Matrix4f Model::GetRotationMatrix() const
{
  Matrix4f rx, ry, rz;
  rx = Matrix4f::Identity();
  ry = Matrix4f::Identity();
  rz = Matrix4f::Identity();
  
  float x = AngleUtils::ToRadians(m_rotationX);
  float y = AngleUtils::ToRadians(m_rotationY);
  float z = AngleUtils::ToRadians(m_rotationZ);

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

  return rz * ry * rx;
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
