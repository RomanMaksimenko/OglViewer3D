#include "ControlButtonsView.h"

#include "Controller/IViewObserver.h"

namespace Transforms
{
constexpr float delta = 0.05;
constexpr float angle = 0.01;
constexpr float scale = 0.1;
} // namespace Transforms

//------------------------------------------------------------------------------
/**
*/
//---
ControlButtonsView::ControlButtonsView(QWidget * parent)
  : QWidget(parent)
{
}


//------------------------------------------------------------------------------
/**
   Установить подписчика
*/
//---
void ControlButtonsView::SetViewObserver(IViewObserver * observer)
{
  m_viewObserver = observer;
}


//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки движения
*/
//---
void ControlButtonsView::MoveButtonPushed(Direction dir)
{
  if (m_viewObserver)
    m_viewObserver->MoveModel(dir, Transforms::delta);
}


//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки вращения
*/
//---
void ControlButtonsView::RotateButtonPushed(Axis axis)
{
  if (m_viewObserver)
    m_viewObserver->RotateModel(axis, Transforms::angle);
}

//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки вращения
*/
//---
void ControlButtonsView::ScaleButtonPushed(float sc)
{
  if (m_viewObserver)
    m_viewObserver->ScaleModel(sc);
}
