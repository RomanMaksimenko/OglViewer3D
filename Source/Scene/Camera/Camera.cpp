#include "Camera.h"

#include <cmath>

#include <Math/Matrix.h>
#include <Math/MathUtils.h>

//------------------------------------------------------------------------------
/**
   
*/
//---
Camera::Camera()
  : m_position{0.0, 0.0, -2.0}
{
}


//------------------------------------------------------------------------------
/**
   Задать перемещение
*/
//---
void Camera::Move(float dx, float dy, float dz)
{
  m_position += Vector3f{dx,dy,dz};
}


//------------------------------------------------------------------------------
/**
   Задать вращение
*/
//---
void Camera::Rotate(float angleX, float angleY, float angleZ)
{
  m_rotationX += angleX;
  m_rotationY += angleY;
  m_rotationZ += angleZ;
}


//------------------------------------------------------------------------------
/**
   Выдать матрицу трансформации вида
*/
//---
Matrix4f Camera::GetViewMatrix() const
{
  /// Матрица перемещения
  auto Translation = Matrix4f::Identity();
  Translation[0][3] = -m_position.x;
  Translation[1][3] = -m_position.y;
  Translation[2][3] = -m_position.z;

  /// Матрица врашения
  auto Rotation = GetRotationMatrix();


  return Translation * Rotation;
}


//------------------------------------------------------------------------------
/**
   Рассчитать матрицу вращения
*/
//---
Matrix4f Camera::GetRotationMatrix() const
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
