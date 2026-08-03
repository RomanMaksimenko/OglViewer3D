#include "Shader.h"

#include <string>
#include <iostream>


//------------------------------------------------------------------------------
/**
   
*/
//---
Shader::Shader(GLuint type, const std::string & source)
  : m_Type(type)
  , m_obj(0)
  , m_shaderSource(source)
{
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


//------------------------------------------------------------------------------
/**
   Компиляция шейдера
*/
//---
bool Shader::Compile()
{
  DeleteShader();

  if (m_shaderSource.empty())
    return false;

  m_obj = glCreateShader(m_Type);
  auto * src = m_shaderSource.c_str();
  glShaderSource(m_obj, 1, &src, nullptr);
  glCompileShader(m_obj);

  int success;
  char infoLog[512];
  glGetShaderiv(m_obj, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    glGetShaderInfoLog(m_obj, 512, nullptr, infoLog);
    std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
    return false;
  }
  return true;
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
