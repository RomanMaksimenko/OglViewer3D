#include "ShaderProgram.h"

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
   Создать Mesh
*/
//---
ShaderProgram::~ShaderProgram()
{
  Destroy();
}


//------------------------------------------------------------------------------
/**
   Создать программу
*/
//---
void ShaderProgram::Create()
{
  Destroy();
  // Создадим и скомпилируем шейдеры
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &Shaders::vertexShaderSource, nullptr);
  glCompileShader(vertexShader);

  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &Shaders::fragmentShaderSource, nullptr);
  glCompileShader(fragmentShader);

  // Линкуем OpenGl программу
  m_program = glCreateProgram();
  glAttachShader(m_program, vertexShader);
  glAttachShader(m_program, fragmentShader);
  glLinkProgram(m_program);

  // Освободим ресурсы, шейдеры больше не нужны
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}


//------------------------------------------------------------------------------
/**
   Освободить занятые ресурсы
*/
//---
void ShaderProgram::Destroy()
{
  if (m_program)
  {
    glDeleteProgram(m_program);
    m_program = 0;
  }
}
