#include "ShaderProgram.h"

#include <Core/RW/RWUtils.h>

#include "UI/RenderView/Shader.h"
#include "Core/Exceptions/ShaderException.h"


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
  Shader vertexShader(GL_VERTEX_SHADER, vertexShaderSource);

  auto fragmentShaderSource = ReadFile(std::filesystem::path(SHADER_DIR) / "FragmentShader.txt");
  Shader fragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

  // Линкуем OpenGl программу
  m_program = glCreateProgram();
  glAttachShader(m_program, vertexShader.GetShaderObj());
  glAttachShader(m_program, fragmentShader.GetShaderObj());
  glLinkProgram(m_program);
  
  // Проверим успешность линковки программы
  GLint success;
  glGetProgramiv(m_program, GL_LINK_STATUS, &success);
  if (success != GL_TRUE)
  {
    GLint logLength = 0;
    glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
    std::string infoLog;
    if (logLength > 0)
    {
      infoLog.resize(logLength);
      glGetProgramInfoLog(m_program, logLength, nullptr, infoLog.data());
    }
    throw ShaderException("Failed to link shader program: \n" + infoLog);
  }

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
