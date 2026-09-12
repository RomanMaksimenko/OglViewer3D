////////////////////////////////////////////////////////////////////////////////
//
/// ProjectionParams.h содержит структуру параметров проецирования
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <Core/Scene/Viewport.h>
#include <Math/Matrix.h>


////////////////////////////////////////////////////////////////////////////////
//
/// Параметры проецирования
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ProjectionParams
{
  float m_fieldOfView; ///< Угол обзора
  Viewport m_viewport; ///< Область отрисовки
  float m_nearZ;       ///< Расстояние до ближней плоскости отсечения
  float m_farZ;        ///< Расстояние до дальней плоскости отсечения
  Matrix4f m_projectionMatrix; ///< Матрица проецирования

public:
  explicit ProjectionParams(float FOV,const Viewport & viewport, float zNear, float zFar);
  
  /// Задать угол обзора
  void SetFieldOfView(float FOV);
  /// Получить угол обзора
  float GetFieldOfView() const;
  /// Задать viewport
  void SetViewport(const Viewport & viewport);
  /// Получить viewport
  Viewport GetViewport() const;
  /// Задать расстояние до ближней плоскости отсечения
  void SetNearZ(float zNear);
  /// Получить расстояние до ближней плоскости отсечения
  float GetNearZ() const;
  /// Задать расстояние до дальней плоскости отсечения
  void SetFarZ(float zFar);
  /// Получить расстояние до дальней плоскости отсечения
  float GetFarZ() const;
  /// Выдать матрицу проецирования по текущим параметрам
  const Matrix4f & GetProjectionMatrix() const;

private:
  /// Обновить матрицу проецирования
  void UpdateProjectionMatrix();
};