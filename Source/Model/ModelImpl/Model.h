////////////////////////////////////////////////////////////////////////////////
//
/// Model/ModelImpl/Model.h содержит класс модели
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Math/AxisAlignedBoundedBox.h>
#include <Math/Matrix.h>

#include "Model/IModel.h"

////////////////////////////////////////////////////////////////////////////////
//
/// Модель 3Д
/**
*/
////////////////////////////////////////////////////////////////////////////////
class Model final : public IModel
{
  std::vector<Vertex> m_vertices;
  std::vector<unsigned int> m_indices;
  AxisAlignedBoundedBox m_boundedBox;
  Vector3f m_position;
  float m_rotationX = 0.0f;
  float m_rotationY = 0.0f;
  float m_rotationZ = 0.0f;
  float m_scale = 0.5f;

public:
  Model();

  /// Переместить модель
  virtual void Translate(float dx, float dy, float dz) override;
  /// Повернуть модель
  virtual void Rotate(float angleX, float angleY, float angleZ) override;
  /// Масштабировать
  virtual void Scale(float scale) override;
  /// Получить вершины для отрисовки
  virtual const std::vector<Vertex> & GetVertices() const override;
  /// Получить индексы порядка отрисовки вершин
  virtual const std::vector<unsigned int> & GetIndices() const override;
  /// Получить матрицу трансформации
  virtual Matrix4f GetTransformMatrix() const override;
  /// Получить ограничивающий объем модели
  virtual const AxisAlignedBoundedBox & GetBoundedBox() const override;

private:
  /// Получить матрицу трансформации
  Matrix4f GetRotationMatrix() const;
};
