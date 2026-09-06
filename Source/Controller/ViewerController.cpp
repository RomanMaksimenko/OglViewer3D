#include "ViewerController.h"

#include <Model/ModelImpl/Model.h>

#include "IModelService.h"
#include "IViewFactory.h"
#include <Core/Scene/IScene.h>
#include "Math/Vector3f.h"
#include "UI/IView.h"
#include "UI/VisibleRect.h"

namespace
{
/// Константы трансляции модели
constexpr double delta = 0.1;
} // namespace


//------------------------------------------------------------------------------
/**
*/
//---
ViewerController::ViewerController(IViewFactory & viewFactory,std::unique_ptr<IScene> scene)
  : m_view(viewFactory.CreateView())
  , m_model(new Model())
  , m_modelService(CreateModelService())
  , m_scene(std::move(scene))
{
  m_view->SetSceneProvider(this);
  m_view->SetViewObserver(this);
}

ViewerController::~ViewerController() = default;


namespace
{
//------------------------------------------------------------------------------
/**
   Проверка, не вышла ли модель за границы видимой области
*/
//---
bool CanTranslateModel(const AxisAlignedBoundedBox & boundedBox, const VisibleRect & visibleRect, const Vector3f & currentDelta,
                       const Vector3f & delta)
{
  auto newMin = boundedBox.Min() + currentDelta + delta;
  auto newMax = boundedBox.Max() + currentDelta + delta;

  return newMin.x >= visibleRect.left && newMax.x <= visibleRect.right && newMin.y >= visibleRect.bottom &&
         newMax.y <= visibleRect.top;
}
} // namespace

//------------------------------------------------------------------------------
/**
   Обработка события движение модели
*/
//---
void ViewerController::MoveModel(Direction dir)
{
  if (!m_model || !m_view)
    return;

  // Границы модели
  auto AABB = m_model->GetBoundedBox();
  // Границы видимой области
  auto visibleRect = m_view->GetVisibleRect();
  // Текущие значения трансформации модели
  auto currentTransform = m_model->GetTransformMatrix();
  auto currentDelta = Vector3f(currentTransform[0][3], currentTransform[1][3], currentTransform[2][3]);

  switch (dir)
  {
    case Direction::Left:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(-delta, 0.0, 0.0)))
        m_model->Translate(-delta, 0.0, 0.0);
      break;
    case Direction::Right:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(delta, 0.0, 0.0)))
        m_model->Translate(delta, 0.0, 0.0);
      break;
    case Direction::Up:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(0.0, delta, 0.0)))
        m_model->Translate(0.0, delta, 0.0);
      break;
    case Direction::Down:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(0.0, -delta, 0.0)))
        m_model->Translate(0.0, -delta, 0.0);
      break;
    case Direction::Front:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(0.0, 0.0, -delta)))
        m_model->Translate(0.0, 0.0, -delta);
      break;
    case Direction::Back:
      if (CanTranslateModel(AABB, visibleRect, currentDelta, Vector3f(0.0, 0.0, delta)))
        m_model->Translate(0.0, 0.0, delta);
      break;
    default:
      break;
  }
  m_view->RenderScene();
}


//------------------------------------------------------------------------------
/**
   Обработка события вращения модели
*/
//---
void ViewerController::RotateModel(Axis axis, RotationDirection rDir)
{
  if (!m_model || !m_view)
    return;
  auto rotate = rDir == RotationDirection::CW ? delta * 10.0 : delta * -10.0;
  switch (axis)
  {
    case Axis::X:
      m_model->Rotate(0.0, rotate, 0.0);
      break;
    case Axis::Y:
      m_model->Rotate(0.0, 0.0, rotate);
      break;
    case Axis::Z:
      m_model->Rotate(rotate, 0.0, 0.0);
      break;
  }
  m_view->RenderScene();
}


//------------------------------------------------------------------------------
/**
   Обработка события масштабирования модели
*/
//---
void ViewerController::ScaleModel(Scaling scale)
{
  if (!m_model || !m_view)
    return;
  switch (scale)
  {
    case Scaling::INC:
      m_model->Scale(delta);
      break;
    case Scaling::DESC:
      m_model->Scale(-delta);
      break;
  }
  
  m_view->RenderScene();
}


//------------------------------------------------------------------------------
/**
   Получить вершины для отрисовки
*/
//---
std::vector<Vertex> ViewerController::GetVertices() const
{
  return m_model->GetVertices();
}


//------------------------------------------------------------------------------
/**
   Получить индексы порядка отрисовки вершин
*/
//---
std::vector<unsigned int> ViewerController::GetIndices() const
{
  return m_model->GetIndices();
}


//------------------------------------------------------------------------------
/**
   Получить матрицу модели
*/
//---
const Matrix4f & ViewerController::GetModelMatrix() const
{
  return m_model->GetTransformMatrix();
}


//------------------------------------------------------------------------------
/**
   Получить  матрицу трансформации вида
*/
//---
const Matrix4f & ViewerController::GetViewMatrix() const
{
  return m_scene->GetViewMatrix();
}

 
//------------------------------------------------------------------------------
/**
   Получить матрицу проекции
*/
//---
const Matrix4f& ViewerController::GetProjectionMatrix() const
{
  return m_scene->GetProjectionMatrix();
}
