////////////////////////////////////////////////////////////////////////////////
//
/// Model/ModelImpl/Model.h содержит класс модели
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

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

public:
  Model() = default;
  ~Model() = default;

  /// Переместить модель
  virtual void Translate(float dx, float dy, float dz) override;
  /// Повернуть модель
  virtual void Rotate(float angleX, float angleY, float angleZ) override;
  /// Масштабировать
  virtual void Scale(float sx, float sy, float sz) override;
  /// Получить вершины для отрисовки
  virtual std::vector<Vertex> GetVertexes() const override;
  /// Получить индексы порядка отрисовки вершин
  virtual std::vector<unsigned int> GetIndices() const override;
  /// Получить матрицу MVP
  virtual Matrix4f GetMVPMatrix() const override;
};
