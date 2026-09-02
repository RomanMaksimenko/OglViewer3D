////////////////////////////////////////////////////////////////////////////////
//
/// Model/IModel.h содержит интерфейс модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Math/Matrix.h"
#include "Math/Vertex.h"

class AxisAlignedBoundedBox;

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
  virtual void Scale(float scale) = 0;
  /// Получить вершины для отрисовки
  virtual const std::vector<Vertex> & GetVertices() const = 0;
  /// Получить индексы порядка отрисовки вершин
  virtual const std::vector<unsigned int> & GetIndices() const = 0;
  /// Получить матрицу трансформации
  virtual Matrix4f GetTransformMatrix() const = 0;
  /// Получить ограничивающий объем модели
  virtual const AxisAlignedBoundedBox & GetBoundedBox() const = 0;
};
