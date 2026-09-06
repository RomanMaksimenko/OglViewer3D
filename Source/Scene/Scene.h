////////////////////////////////////////////////////////////////////////////////
//
/// Scene.h содержит объявление класса состояния сцены
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include <Core/Scene/IScene.h>

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
public:
  ~Scene() = default;
  /// Изменить положение модели на сцене
  virtual void SetTranslation(float dx, float dy, float dz) override;
  /// Изменить углы вращения модели на сцене
  virtual void SetRotation(float rx, float ry, float rz) override;
  /// Изменить масштаб
  virtual void SetScale(float scale) override;
  /// Выдать матрицу трансформации вида
  virtual const Matrix4f & GetViewMatrix() const override;
  /// Выдать матрицу проекции
  virtual const Matrix4f & GetProjectionMatrix() const override;
};

/// Функция создания
std::unique_ptr<IScene> CreateScene();
