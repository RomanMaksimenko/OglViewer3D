#include "ProjectionParams.h"

#include <Core/Exceptions/MathException.h>
#include <Math/MathUtils.h>


//------------------------------------------------------------------------------
/**

*/
//---
ProjectionParams::ProjectionParams(float FOV, const Viewport & viewport, float zNear, float zFar)
  : m_fieldOfView(FOV)
  , m_viewport(viewport)
  , m_nearZ(zNear)
  , m_farZ(zFar)
  , m_projectionMatrix(Matrix4f::Identity())
{
  if (m_viewport.height == 0)
    throw MathException("Incorrect vieport size : height is zero");
  if (m_fieldOfView <= 0.0f || m_fieldOfView >= 180.0f)
    throw MathException("FOV must be between 0 and 180 degrees");
  if (m_nearZ <= 0.0f || m_farZ <= 0.0f)
    throw MathException("Near and far planes must be positive");
  if (m_nearZ >= m_farZ)
    throw MathException("Near plane must be less than far plane");

  UpdateProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Задать угол обзора
*/
//---
void ProjectionParams::SetFieldOfView(float FOV)
{
  if (FOV <= 0.0f || FOV >= 180.0f)
    throw MathException("FOV must be between 0 and 180 degrees");
  m_fieldOfView = FOV;
  UpdateProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Получить угол обзора
*/
//---
float ProjectionParams::GetFieldOfView() const
{
  return m_fieldOfView;
}


//------------------------------------------------------------------------------
/**
   Задать viewport
*/
//---
void ProjectionParams::SetViewport(const Viewport & viewport)
{
  if (viewport.height == 0)
    throw MathException("Incorrect vieport size : height is zero");
  m_viewport = viewport;
  UpdateProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Получить viewport
*/
//---
Viewport ProjectionParams::GetViewport() const
{
  return m_viewport;
}


//------------------------------------------------------------------------------
/**
   Задать расстояние до ближней плоскости отсечения
*/
//---
void ProjectionParams::SetNearZ(float nearz)
{
  if (nearz <= 0.0f)
    throw MathException("Near plane must be positive");
  m_nearZ = nearz;
  UpdateProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Получить расстояние до ближней плоскости отсечения
*/
//---
float ProjectionParams::GetNearZ() const
{
  return m_nearZ;
}


//------------------------------------------------------------------------------
/**
   Задать расстояние до дальней плоскости отсечения
*/
//---
void ProjectionParams::SetFarZ(float farZ)
{
  if (farZ <= 0.0f)
    throw MathException("Far plane must be positive");
  m_farZ = farZ;
  UpdateProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Получить расстояние до дальней плоскости отсечения
*/
//---
float ProjectionParams::GetFarZ() const
{
  return m_farZ;
}


//------------------------------------------------------------------------------
/**
   Выдать матрицу проецирования по текущим параметрам
*/
//---
const Matrix4f & ProjectionParams::GetProjectionMatrix() const
{
  return m_projectionMatrix;
}


//------------------------------------------------------------------------------
/**
   Обновить матрицу проецирования
*/
//---
void ProjectionParams::UpdateProjectionMatrix()
{
  float tanHalfFOV = tanf(AngleUtils::ToRadians(m_fieldOfView) / 2.0f);
  float f = 1.0 / tanHalfFOV;

  float zRange = m_nearZ - m_farZ;
  float A = (-m_farZ - m_nearZ) / zRange;
  float B = (2.0f * m_farZ * m_nearZ) / zRange;
  float ar = float(m_viewport.width) / float(m_viewport.height);

  m_projectionMatrix[0][0] = f / ar;
  m_projectionMatrix[1][0] = 0;
  m_projectionMatrix[2][0] = 0;
  m_projectionMatrix[3][0] = 0;

  m_projectionMatrix[0][1] = 0;
  m_projectionMatrix[1][1] = f;
  m_projectionMatrix[2][1] = 0;
  m_projectionMatrix[3][1] = 0;

  m_projectionMatrix[0][2] = 0; 
  m_projectionMatrix[1][2] = 0;
  m_projectionMatrix[2][2] = A;
  m_projectionMatrix[3][2] = 1;

  m_projectionMatrix[0][3] = 0;
  m_projectionMatrix[1][3] = 0;
  m_projectionMatrix[2][3] = B;
  m_projectionMatrix[3][3] = 0;
}
