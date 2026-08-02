#include "RenderView.h"

#include <iostream>

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
*/
//---
RenderView::~RenderView()
{
  // Если контекст OpenGl существует
  if (isValid())
  { // Делаем контекст OpenGl текущим
    makeCurrent();
    CleanUpGl();
    // Завершаем работу с контекстом
    doneCurrent();
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
  // Если контекст OpenGl существует
  if (isValid())
  {
    // Делаем контекст OpenGl текущим
    makeCurrent();
    CleanUpGl();
    if (m_modelProvider)
    {
      m_mesh.Create(m_modelProvider->GetVertexes(), m_modelProvider->GetIndices());
      m_GLprogram.Create();
    }
    // Завершаем работу с контекстом
    doneCurrent();
  }
}


//------------------------------------------------------------------------------
/**
   Отрисовать сцену
*/
//---
void RenderView::RenderScene()
{
  // Запрашиваем перерисовку
  update();
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
  if (IsReadyToDraw())
  {
    glUseProgram(m_GLprogram.Id());
    glBindVertexArray(m_mesh.VAO());
    glDrawElements(GL_TRIANGLES, m_mesh.IndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
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
  // Сначала инициализируем glew
  glewExperimental = GL_TRUE;
  auto err = glewInit();
  if (err != GLEW_OK)
  {
    std::cerr << "Failed to initialize GLEW\n";
  }
  glClearColor(0.0, 0.0, 0.0, 1.0);
}


//------------------------------------------------------------------------------
/**
   Готов ли рендер к отрисовке
*/
//---
bool RenderView::IsReadyToDraw() const
{
  return m_GLprogram.Id() != 0 && m_mesh.VAO() != 0;
}


//------------------------------------------------------------------------------
/**
   Освободить ресурсы OpenGl
*/
//---
void RenderView::CleanUpGl()
{
  m_GLprogram.Destroy();
  m_mesh.Destroy();
}


//------------------------------------------------------------------------------
/**
   Функция создания RenderView
*/
//---
IRenderView * CreateRenderView(QWidget * parent)
{
  return new RenderView(parent);
}
