#include "Shader.h"

#include <iostream>
#include <string>

#include "Core/Exceptions/ShaderException.h"

//------------------------------------------------------------------------------
/**
   
*/
//---
Shader::Shader(GLuint type, const std::string & source)
  : m_Type(type)
  , m_obj(0)
  , m_shaderSource(source)
{
  Compile();
}


//------------------------------------------------------------------------------
/**
   Move-конструктор
*/
//---
Shader::Shader(Shader && other) noexcept
  : m_Type(other.m_Type)
  , m_obj(other.m_obj)
  , m_shaderSource(std::move(other.m_shaderSource))
{
  other.m_obj = 0;
}

//------------------------------------------------------------------------------
/**
   
*/
//---
Shader::~Shader()
{
  DeleteShader();
}


//------------------------------------------------------------------------------
/**
   Оператор перемещения
*/
//---
Shader & Shader::operator=(Shader && other) noexcept
{
  if (this != &other)
  {
    DeleteShader();
    m_Type = other.m_Type;
    std::swap(m_obj, other.m_obj);
    m_shaderSource = std::move(other.m_shaderSource);
  }
  return *this;
}


namespace
{
//------------------------------------------------------------------------------
/**
   Получить строковое представление типа шейдера
*/
//---
std::string ShaderTypeToString(GLuint shaderType)
{
  switch (shaderType)
  {
    case GL_VERTEX_SHADER:
      return std::string("Vertex shader");
    case GL_FRAGMENT_SHADER:
      return std::string("Fragment shader");
  }
  return {};
}
} // namespace


//------------------------------------------------------------------------------
/**
   Компиляция шейдера
*/
//---
void Shader::Compile()
{
  DeleteShader();

  m_obj = glCreateShader(m_Type);
  auto * src = m_shaderSource.c_str();
  glShaderSource(m_obj, 1, &src, nullptr);
  glCompileShader(m_obj);

  GLint success;
  glGetShaderiv(m_obj, GL_COMPILE_STATUS, &success);
  if (success != GL_TRUE)
  {
    GLint logLength = 0;
    glGetShaderiv(m_obj, GL_INFO_LOG_LENGTH, &logLength);
    std::string infoLog;
    if (logLength > 0)
    {
      infoLog.resize(logLength);
      glGetShaderInfoLog(m_obj, logLength, nullptr, infoLog.data());
    }
    throw ShaderException("Failed to compile " + ShaderTypeToString(m_Type) + infoLog);
  }
}


//------------------------------------------------------------------------------
/**
   Освободить занятые ресурсы
*/
//---
void Shader::DeleteShader()
{
  glDeleteShader(m_obj);
  m_obj = 0;
}
