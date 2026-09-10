////////////////////////////////////////////////////////////////////////////////
//
/// Scene.h содержит объявление класса состояния сцены
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include <Core/Scene/IScene.h>
#include <Scene/Camera/Camera.h>
#include <Scene/ProjectionParams.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Объект сосояния сцены
/**
  Реализует хранени данных, необходимых для описания и изменения состояния сцены
  таких как положение и поворот камеры, параметры проецирования, освещение и т.д.
*/
////////////////////////////////////////////////////////////////////////////////
class Scene : public IScene
{
  Camera m_camera;             ///< Камера
  ProjectionParams m_projPars; ///< Параметры проецирования

public:
  Scene();
  /// Изменить положение камеры
  virtual void MoveCamera(float dx, float dy, float dz) override;
  /// Повернуть камеру
  virtual void RotateCamera(float rx, float ry, float rz) override;
  /// Выдать матрицу трансформации вида
  virtual Matrix4f GetViewMatrix() const override;
  /// Выдать матрицу проекции
  virtual Matrix4f GetProjectionMatrix() const override;
  /// Задать размер области отрисовки
  virtual void SetViewport(const Viewport & viewport) override;
};

/// Функция создания
std::unique_ptr<IScene> CreateScene();
