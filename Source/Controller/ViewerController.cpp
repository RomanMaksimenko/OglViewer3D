#include "ViewerController.h"

#include "IModelService.h"


struct IView
{
};

struct IModel
{
};

//------------------------------------------------------------------------------
/**
*/
//---
ViewerController::ViewerController()
  : m_view(nullptr)
  , m_model(nullptr)
  , m_modelService(CreateModelService())
{
}

ViewerController::~ViewerController() = default;

//------------------------------------------------------------------------------
/**
   Обработка события движение модели
*/
//---
void ViewerController::MoveModel(Direction dir, float delta)
{
}


//------------------------------------------------------------------------------
/**
   Обработка события вращения модели
*/
//---
void ViewerController::RotateModel(Axis axis, float angle)
{
}


//------------------------------------------------------------------------------
/**
   Обработка события масштабирования модели
*/
//---
void ViewerController::ScaleModel(float scale)
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
