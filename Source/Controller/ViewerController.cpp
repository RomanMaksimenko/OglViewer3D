#include "ViewerController.h"

#include <Model/ModelImpl/Model.h>

#include "IModelService.h"
#include "IViewFactory.h"
#include "UI/IView.h"

namespace
{
/// Константы трансляции модели
constexpr double delta = 0.05;
} // namespace


//------------------------------------------------------------------------------
/**
*/
//---
ViewerController::ViewerController(IViewFactory & viewFactory)
  : m_view(viewFactory.CreateView())
  , m_model(new Model())
  , m_modelService(CreateModelService())
{
  m_view->SetModelProvider(this);
  m_view->SetViewObserver(this);
}

ViewerController::~ViewerController() = default;


//------------------------------------------------------------------------------
/**
   Обработка события движение модели
*/
//---
void ViewerController::MoveModel(Direction dir)
{
  if (!m_model || !m_view)
    return;

  switch (dir)
  {
    case Direction::Left:
      m_model->Translate(-delta, 0.0, 0.0);
      break;
    case Direction::Right:
      m_model->Translate(delta, 0.0, 0.0);
      break;
    case Direction::Up:
      m_model->Translate(0.0, -delta, 0.0);
      break;
    case Direction::Down:
      m_model->Translate(0.0, delta, 0.0);
      break;
    case Direction::Front:
      m_model->Translate(0.0, 0.0, -delta);
      break;
    case Direction::Back:
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
  auto rotate = rDir == RotationDirection::CW ? delta * -1.0 : delta;
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
  m_model->Scale(delta, delta, delta);
  m_view->RenderScene();
}


//------------------------------------------------------------------------------
/**
   Получить вершины для отрисовки
*/
//---
std::vector<Vertex> ViewerController::GetVertexes() const
{
  return m_model->GetVertexes();
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
   Получить матрицу MVP
*/
//---
Matrix4f ViewerController::GetMVPMatrix() const
{
  return {};
}
