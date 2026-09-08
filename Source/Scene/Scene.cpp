#include "Scene.h"

#include <Math/Matrix.h>


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
  return Matrix4f::Identity();
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
