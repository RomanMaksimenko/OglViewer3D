#include "Model.h"

#include <Math/AxisAlignedBoundedBox.h>
#include <Math/MathUtils.h>


namespace VectorUtils
{
float Length(const Vector3f & vector)
{
  return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

Vector3f Normilize(const Vector3f & vector)
{
  auto len = Length(vector);
  auto x = vector.x / len;
  auto y = vector.y / len;
  auto z = vector.z / len;
  return Vector3f{x, y, z};
}

// Умножение вектора на скаляр
Vector3f operator*(const Vector3f & vector, float a)
{
  return Vector3f(vector.x * a, vector.y * a, vector.z * a);
}

Vector3f & operator+=(Vector3f & lhs, const Vector3f & rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

Vector3f & operator-=(Vector3f & lhs, const Vector3f & rhs)
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;
  return lhs;
}

Vector3f Cross(Vector3f & lhs, const Vector3f & rhs)
{
  Vector3f result;
  result.x = lhs.y * rhs.z - lhs.z * rhs.y;
  result.y = lhs.z * rhs.x - lhs.x * rhs.z;
  result.z = lhs.x * rhs.y - lhs.y * rhs.x;
  return result;
}

Matrix4f InitCameraTransform(const Vector3f & Target, const Vector3f & Up)
{
  Matrix4f camera = Matrix4f::Identity();
  auto && target = const_cast<Vector3f &>(Target);
  auto && up = const_cast<Vector3f &>(Up);
  Vector3f N = target;

  Vector3f U = Cross(up, N);
  U = Normilize(U);

  Vector3f V = Cross(N, U);
  V = Normilize(V);

  camera[0][0] = U.x;
  camera[0][1] = U.y;
  camera[0][2] = U.z;

  camera[1][0] = V.x;
  camera[1][1] = V.y;
  camera[1][2] = V.z;

  camera[2][0] = N.x;
  camera[2][1] = N.y;
  camera[2][2] = N.z;

  return camera;
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
  , m_transform(Matrix4f::Identity())
  , rx(Matrix4f::Identity())
  , ry(Matrix4f::Identity())
  , rz(Matrix4f::Identity())
  , m_position{0.0, 0.0, -2.0}
  , m_target{0.0, 0.0, 1.0}
  , m_up{0.0, 1.0, 0.0}
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
  m_position = VectorUtils::operator+=(m_position,Vector3f{dx, dy, dz});
}


//------------------------------------------------------------------------------
/**
   Повернуть модель
*/
//---
void Model::Rotate(float angleX, float angleY, float angleZ)
{
  // TODO перейти на хранение углов, при изменении полученное значение добавлять к хранящемуся и перещитывать матрицы
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
  Vector3f U{1.0, 0.0, 0.0};
  Vector3f V{0.0, 1.0, 0.0};
  Vector3f N{0.0, 0.0, 1.0};
  Matrix4f result = {U.x, U.y, U.z, -m_position.x, V.x, V.y, V.z, -m_position.y,
                     N.x, N.y, N.z, -m_position.z, 0.0, 0.0, 0.0, 1.0};

  return result;
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
