////////////////////////////////////////////////////////////////////////////////
//
/// ISceneProvider.h содержит интерфейс, предоставляющий доступ к данным состояния сцены
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include "Math/Vertex.h"

class Matrix4f;

////////////////////////////////////////////////////////////////////////
//
/// Интерфейс контроллера для предоставления доступа к данным состояния сцены.
/**
  Определяет методы получения рендером данных для отрисовки
*/
////////////////////////////////////////////////////////////////////////
struct ISceneProvider
{
  virtual ~ISceneProvider() = default;

  /// Получить вершины для отрисовки
  virtual std::vector<Vertex> GetVertices() const = 0;
  /// Получить индексы порядка отрисовки вершин
  virtual std::vector<unsigned int> GetIndices() const = 0;
  /// Получить матрицу модели
  virtual const Matrix4f & GetModelMatrix() const = 0;
  /// Получить  матрицу трансформации вида
  virtual const Matrix4f & GetViewMatrix() const = 0;
  /// Получить матрицу проекции
  virtual const Matrix4f & GetProjectionMatrix() const = 0;
};
