////////////////////////////////////////////////////////////////////////////////
//
/// Model/ModelImpl/Model.h содержит класс модели
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Model/IModel.h"

#include <Math/AxisAlignedBoundedBox.h>
#include <Math/Matrix.h>

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
  Matrix4f m_transform;

public:
  Model();

  /// Переместить модель
  virtual void Translate(float dx, float dy, float dz) override;
  /// Повернуть модель
  virtual void Rotate(float angleX, float angleY, float angleZ) override;
  /// Масштабировать
  virtual void Scale(float sx, float sy, float sz) override;
  /// Получить вершины для отрисовки
  virtual const std::vector<Vertex> & GetVertices() const override;
  /// Получить индексы порядка отрисовки вершин
  virtual const std::vector<unsigned int> & GetIndices() const override;
  /// Получить матрицу трансформации
  virtual Matrix4f GetTransformMatrix() const override;
  /// Получить ограничивающий объем модели
  virtual const AxisAlignedBoundedBox & GetBoundedBox() const override;
};
