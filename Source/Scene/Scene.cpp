#include "Scene.h"

#include <Math/Matrix.h>


const ProjectionParams c_defaultProjectionParams(90.0, {800, 600}, 1.0, 10.0);


//------------------------------------------------------------------------------
/**

*/
//---
Scene::Scene()
  : m_camera()
  , m_projPars(c_defaultProjectionParams)
{
}


//------------------------------------------------------------------------------
/**
   Изменить положение камеры
*/
//---
void Scene::MoveCamera(float dx, float dy, float dz)
{
  m_camera.Move(dx, dy, dz);
}


//------------------------------------------------------------------------------
/**
   Повернуть камеру
*/
//---
void Scene::RotateCamera(float rx, float ry, float rz)
{
  m_camera.Rotate(rx, ry, rz);
}


//------------------------------------------------------------------------------
/**
   Выдать матрицу трансформации вида
*/
//---
Matrix4f Scene::GetViewMatrix() const
{
  return m_camera.GetViewMatrix();
}


//------------------------------------------------------------------------------
/**
   Выдать матрицу проекции
*/
//---
Matrix4f Scene::GetProjectionMatrix() const
{
  return m_projPars.GetProjectionMatrix();
}


//------------------------------------------------------------------------------
/**
   Задать размер области отрисовки
*/
//---
void Scene::SetViewport(const Viewport & viewport)
{
  m_projPars.SetViewport(viewport);
}


//------------------------------------------------------------------------------
/**
   Функция создания
*/
//---
std::unique_ptr<IScene> CreateScene()
{
  return std::unique_ptr<IScene>(new Scene());
}
