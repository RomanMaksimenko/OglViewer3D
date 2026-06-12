////////////////////////////////////////////////////////////////////////////////
//
/// Model/IModel.h содержит интерфейс модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Math/Matrix.h"

////////////////////////////////////////////////////////////////////////
//
/// Интерфейс модели.
/**
*  Определяет методы доступа к данным и методы изменения данным путем 
*  трансформации
*/
////////////////////////////////////////////////////////////////////////
struct IModel
{
  virtual ~IModel() = default;

  /// Переместить модель
  virtual void Translate(float dx, float dy, float dz) = 0;
  /// Повернуть модель
  virtual void Rotate(float angleX, float angleY, float angleZ) = 0;
  /// Масштабировать
  virtual void Scale(float sx, float sy, float sz) = 0;
  /// Получить вершины для отрисовки
  virtual std::vector<Vertex> GetVertexes() const = 0;
  /// Получить индексы порядка отрисовки вершин
  virtual std::vector<unsigned int> GetIndices() const = 0;
  /// Получить матрицу MVP
  virtual Matrix4f GetMVPMatrix() const = 0;
};
