#include "ViewerController.h"

#include "IModelService.h"
#include "IViewFactory.h"
#include "UI/IView.h"

#include <Model/ModelImpl/Model.h>

struct View:public IView
{
  /// Установить подписчика на события представления
  virtual void SetViewObserver(IViewObserver * observer) {}
  /// Установить проводника модели
  virtual void SetModelProvider(IModelProvider * modelProvider) {}
  /// Отрисовать сцену
  virtual void RenderScene() {}
};
//------------------------------------------------------------------------------
/**
*/
//---
ViewerController::ViewerController(IViewFactory & viewFactory)
  : m_view(viewFactory.CreateView())
  , m_model(new Model())
  , m_modelService(CreateModelService())
{
}

ViewerController::~ViewerController() = default;


//------------------------------------------------------------------------------
/**
   Обработка события движение модели
*/
//---
void ViewerController::MoveModel(Direction dir)
{
}


//------------------------------------------------------------------------------
/**
   Обработка события вращения модели
*/
//---
void ViewerController::RotateModel(Axis axis, RotationDirection rDir)
{
}


//------------------------------------------------------------------------------
/**
   Обработка события масштабирования модели
*/
//---
void ViewerController::ScaleModel(Scaling scale)
{
}


//------------------------------------------------------------------------------
/**
   Получить вершины для отрисовки
*/
//---
std::vector<Vertex> ViewerController::GetVertexes() const
{
  return {};
}


//------------------------------------------------------------------------------
/**
   Получить индексы порядка отрисовки вершин
*/
//---
std::vector<unsigned int> ViewerController::GetIndices() const
{
  return {};
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
