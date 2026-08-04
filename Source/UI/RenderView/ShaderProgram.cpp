#include "ShaderProgram.h"

#include <Core/RW/RWUtils.h>

#include "UI/RenderView/Shader.h"


//------------------------------------------------------------------------------
/**
   Конструктор перемещения
*/
//---
ShaderProgram::ShaderProgram(ShaderProgram && other) noexcept
  : m_program(other.m_program)
{
  other.m_program = 0;
}

//------------------------------------------------------------------------------
/**
   
*/
//---
ShaderProgram::~ShaderProgram()
{
  Destroy();
}


//------------------------------------------------------------------------------
/**
   Оператор перемещения
*/
//---
ShaderProgram & ShaderProgram::operator=(ShaderProgram && other) noexcept
{
  if (this != &other)
  {
    Destroy();
    m_program = other.m_program;
    other.m_program = 0;
  }
  return *this;
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
    return; // TODO обработка ошибок
  }
  Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource);
  vertexShader.Compile();

  auto fragmentShaderSource = ReadFile(std::filesystem::path(SHADER_DIR) / "FragmentShader.txt");
  if (fragmentShaderSource.empty())
  {
    return; // TODO обработка ошибок
  }
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
  fragmentShader.Compile();

  // Линкуем OpenGl программу
  m_program = glCreateProgram();
  glAttachShader(m_program, vertexShader.GetShaderObj());
  glAttachShader(m_program, fragmentShader.GetShaderObj());
  glLinkProgram(m_program);

   // Отсоединяем после успешной линковки
  glDetachShader(m_program, vertexShader.GetShaderObj());
  glDetachShader(m_program, fragmentShader.GetShaderObj());
}


//------------------------------------------------------------------------------
/**
   Освободить занятые ресурсы
*/
//---
void ShaderProgram::Destroy()
{
  glDeleteProgram(m_program);
  m_program = 0;
}
