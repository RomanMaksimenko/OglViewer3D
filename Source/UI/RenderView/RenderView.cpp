#include "RenderView.h"

#include "Controller/IModelProvider.h"


//------------------------------------------------------------------------------
/**
*/
//---
RenderView::RenderView(QWidget * parent)
  : QOpenGLWidget(parent)
{
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
