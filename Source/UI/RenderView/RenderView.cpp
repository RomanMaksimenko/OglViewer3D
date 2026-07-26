#include "RenderView.h"

#include "Controller/IModelProvider.h"


//------------------------------------------------------------------------------
/**
*/
//---
RenderView::RenderView(QWidget * parent)
  : QOpenGLWidget(parent)
{
	if (parent)
	{
    QSize parentSize = parent->size();
    QWidget::resize(parentSize.width() / 2, parentSize.height() / 2);
  }
}


//------------------------------------------------------------------------------
/**
   Установить подписчика
*/
//---
void RenderView::SetModelProvider(IModelProvider * modelProvider)
{
  m_modelProvider = modelProvider;
}



//------------------------------------------------------------------------------
/**
   Отрисовать сцену
*/
//---
void RenderView::RenderScene()
{
  paintGL();
}


//------------------------------------------------------------------------------
/**
   Выдать указатель на себя как на QWidget
*/
//---
QWidget * RenderView::widget()
{
  return this;
}


//------------------------------------------------------------------------------
/**
   Отрисовать сцену
*/
//---
void RenderView::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);
}


//------------------------------------------------------------------------------
/**
   Изменить размер окна
*/
//---
void RenderView::resizeGL(int w, int h)
{

}


//------------------------------------------------------------------------------
/**
   Инициализировать OpenGL
*/
//---
void RenderView::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0.0, 0.0, 0.0, 1.0);
}


//------------------------------------------------------------------------------
/**
   Функция создания RenderView
*/
//---
IRenderView* CreateRenderView(QWidget* parent)
{
  return new RenderView(parent);
}
