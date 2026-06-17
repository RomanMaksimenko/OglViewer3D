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

}


void RenderView::paintGL()
{

}
void RenderView::resizeGL(int w, int h)
{

}
void RenderView::initializeGL()
{

}
