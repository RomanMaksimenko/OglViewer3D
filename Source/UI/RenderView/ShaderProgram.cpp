#include "ShaderProgram.h"

#include <Core/RW/RWUtils.h>
#include "UI/RenderView/Shader.h"


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
  auto vertexShaderSource = ReadFile(std::filesystem::path(SHADER_DIR) / "VertexShader.txt");
  if (vertexShaderSource.empty())
  {
    return;// TODO обработка ошибок
  }
  Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource);
  vertexShader.Compile();

  auto fragmentShaderSource = ReadFile(std::filesystem::path(SHADER_DIR) / "FragmentShader.txt");
  if (fragmentShaderSource.empty())
  {
    return;// TODO обработка ошибок
  }
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  fragmentShader.Compile();

  // Линкуем OpenGl программу
  m_program = glCreateProgram();
  glAttachShader(m_program, vertexShader.GetShaderObj());
  glAttachShader(m_program, fragmentShader.GetShaderObj());
  glLinkProgram(m_program);

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
