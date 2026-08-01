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
  , m_VAO(-1)
  , m_VBO(-1)
  , m_EBO(-1)
  , m_GLprogram(-1)
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
  CleanUpGl();
}


//------------------------------------------------------------------------------
/**
   Установить подписчика
*/
//---
void RenderView::SetModelProvider(IModelProvider * modelProvider)
{
  m_modelProvider = modelProvider;
  CreateGLProgram();
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
  if (IsReadyToDraw())
  {
    glUseProgram(m_GLprogram);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
void RenderView::CreateGLProgram()
{
  if (!m_modelProvider)
    return;

  if (m_GLprogram == -1)
  {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &Shaders::vertexShaderSource, 0);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &Shaders::fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    m_GLprogram = glCreateProgram();
    glAttachShader(m_GLprogram, vertexShader);
    glAttachShader(m_GLprogram, fragmentShader);
    glLinkProgram(m_GLprogram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
  }

  auto vertices = m_modelProvider->GetVertexes();
  auto indices = m_modelProvider->GetIndices();

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}


//------------------------------------------------------------------------------
/**
   Готов ли рендер к отрисовке
*/
//---
bool RenderView::IsReadyToDraw() const
{
  return m_GLprogram != -1 && m_VAO != -1;
}


//------------------------------------------------------------------------------
/**
   Освободить ресурсы OpenGl
*/
//---
void RenderView::CleanUpGl()
{
  if (m_GLprogram != -1)
  {
    glDeleteProgram(m_GLprogram);
    m_GLprogram = -1;
  }
  if (m_VAO != -1)
  {
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = -1;
  }
  if (m_VBO != -1)
  {
    glDeleteBuffers(1, &m_VBO);
    m_VBO = -1;
  }
  if (m_EBO != -1)
  {
    glDeleteBuffers(1, &m_EBO);
    m_EBO = -1;
  }
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
