#include "RenderView.h"

#include <iostream>

#include "Controller/IModelProvider.h"


namespace Shaders
{
const GLchar * vertexShaderSource = "#version 330 core\n"
                                    "layout (location = 0) in vec3 position;\n"
                                    "void main()\n"
                                    "{\n"
                                    "gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
                                    "}\0";
const GLchar * fragmentShaderSource = "#version 330 core\n"
                                      "out vec4 color;\n"
                                      "void main()\n"
                                      "{\n"
                                      "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                                      "}\n\0";

} // namespace Shaders


//------------------------------------------------------------------------------
/**
*/
//---
RenderView::RenderView(QWidget * parent)
  : QOpenGLWidget(parent)
  , m_GLprogram(0)
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
      CreateProgram();
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
    glUseProgram(m_GLprogram);
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
   Создать программу отрисовки
*/
//---
void RenderView::CreateProgram()
{
  if (!m_modelProvider)
    return;

  // Создадим и скомпилируем шейдеры
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &Shaders::vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &Shaders::fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // Линкуем OpenGl программу
  m_GLprogram = glCreateProgram();
  glAttachShader(m_GLprogram, vertexShader);
  glAttachShader(m_GLprogram, fragmentShader);
  glLinkProgram(m_GLprogram);

  // Освободим ресурсы, шейдеры больше не нужны
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}


//------------------------------------------------------------------------------
/**
   Готов ли рендер к отрисовке
*/
//---
bool RenderView::IsReadyToDraw() const
{
  return m_GLprogram != 0 && m_mesh.VAO() != 0;
}


//------------------------------------------------------------------------------
/**
   Освободить ресурсы OpenGl
*/
//---
void RenderView::CleanUpGl()
{
  if (m_GLprogram)
  {
    glDeleteProgram(m_GLprogram);
    m_GLprogram = 0;
  }
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
