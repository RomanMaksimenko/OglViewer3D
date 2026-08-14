#include "ViewMainWindow.h"

#include <QHBoxLayout>

#include "UI/IControlButtonsView.h"
#include "UI/IRenderView.h"
#include "UI/VisibleRect.h"


//------------------------------------------------------------------------------
/**
*/
//---
ViewMainWindow::ViewMainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_buttonsView(CreateControlButtonsView(this))
	, m_renderView(CreateRenderView(this))
{
  QWidget * centralWidget = new QWidget(this);
  QHBoxLayout * layout = new QHBoxLayout(centralWidget);
  layout->addWidget(m_buttonsView->widget());/// TODO убрать статик касты
  layout->addWidget(m_renderView->widget());
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
  resize(1024, 768);
  show();
}


//------------------------------------------------------------------------------
/**
   Установить подписчика на события представления
*/
//---
void ViewMainWindow::SetViewObserver(IViewObserver* observer)
{
  m_buttonsView->SetViewObserver(observer);
}


//------------------------------------------------------------------------------
/**
   Установить проводника модели
*/
//---
void ViewMainWindow::SetModelProvider(IModelProvider * modelProvider)
{
  m_renderView->SetModelProvider(modelProvider);
}


//------------------------------------------------------------------------------
/**
   Отрисовать сцену
*/
//---
void ViewMainWindow::RenderScene()
{
  if (m_renderView)
    m_renderView->RenderScene();
}


//------------------------------------------------------------------------------
/**
   Получить размер видимой области
*/
//---
const VisibleRect& ViewMainWindow::GetVisibleRect() const
{
  // TODO после перехода к 3D модели добавить сущность камеры, расчет видимой области осуществлять в ней
  return VisibleRect(-1.0, 1.0, -1.0, 1.0);
}
