////////////////////////////////////////////////////////////////////////////////
//
/// ISceneProvider.h содержит интерфейс, предоставляющий доступ к данным состояния сцены
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <vector>

#include <Core/Scene/Viewport.h>

#include <Math/Vertex.h>
#include <Math/Matrix.h>


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
  virtual Matrix4f GetModelMatrix() const = 0;
  /// Получить  матрицу трансформации вида
  virtual Matrix4f GetViewMatrix() const = 0;
  /// Получить матрицу проекции
  virtual Matrix4f GetProjectionMatrix() const = 0;
  /// Задать размер области отрисовки
  virtual void SetViewport(const Viewport &) = 0;
};
