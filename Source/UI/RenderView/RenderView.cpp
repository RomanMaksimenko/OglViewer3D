#include "RenderView.h"

#include <iostream>

#include <Math/MathUtils.h>
#include <Math/Matrix.h>
#include <Math/Vector3f.h>

#include <Core/Scene/ISceneProvider.h>

#include "Core/Exceptions/ApplicationException.h"


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
void RenderView::SetSceneProvider(ISceneProvider * sceneProvider)
{
  m_sceneProvider = sceneProvider;
  // Если контекст OpenGl существует
  if (isValid())
  {
    // Делаем контекст OpenGl текущим
    makeCurrent();
    CleanUpGl();
    if (m_sceneProvider)
    {
      m_mesh.Create(m_sceneProvider->GetVertices(), m_sceneProvider->GetIndices());
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

struct ProjectionParams
{
  float FOV;
  int Width;
  int Height;
  float zNear;
  float zFar;
};

Matrix4f GetProjectionMatrix(const ProjectionParams & pars)
{
  Matrix4f ProjMatrix = Matrix4f::Identity();
  float tanHalfFOV = tanf(AngleUtils::ToRadians(pars.FOV) / 2.0f);
  float f = 1.0 / tanHalfFOV;

  float zRange = pars.zNear - pars.zFar;
  float A = (-pars.zFar - pars.zNear) / zRange;       // Исправлено
  float B = (2.0f * pars.zFar * pars.zNear) / zRange; // Исправлено
  float ar = float(pars.Width) / float(pars.Height);
  ProjMatrix[0][0] = f / ar; // 1-й столбец
  ProjMatrix[1][0] = 0;
  ProjMatrix[2][0] = 0;
  ProjMatrix[3][0] = 0;

  ProjMatrix[0][1] = 0; // 2-й столбец
  ProjMatrix[1][1] = f;
  ProjMatrix[2][1] = 0;
  ProjMatrix[3][1] = 0;

  ProjMatrix[0][2] = 0; // 3-й столбец
  ProjMatrix[1][2] = 0;
  ProjMatrix[2][2] = A;
  ProjMatrix[3][2] = 1;

  ProjMatrix[0][3] = 0; // 4-й столбец
  ProjMatrix[1][3] = 0;
  ProjMatrix[2][3] = B;
  ProjMatrix[3][3] = 0;

  return ProjMatrix;
}

//------------------------------------------------------------------------------
/**
   Отрисовать сцену
*/
//---
void RenderView::paintGL()
{
  static ProjectionParams projPars{90.0, this->width(), this->height(), 1.0, 10.0};
  glClear(GL_COLOR_BUFFER_BIT);
  if (IsReadyToDraw())
  {
    glUseProgram(m_GLprogram.Id());
    glBindVertexArray(m_mesh.VAO());
    Matrix4f View = m_sceneProvider->GetModelMatrix();
    Matrix4f Model = Matrix4f::Identity();
    Matrix4f Projection = GetProjectionMatrix(projPars);

    auto MVP = Projection * View * Model;
    glUniformMatrix4fv(m_GLprogram.TransformLocation(), 1, GL_TRUE, &MVP[0][0]);
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
    throw ApplicationException("Failed to initialize GLEW\n");
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
