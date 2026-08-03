////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/Shader.h содержит класс Shader- RAII обертка над шейдером OpenGL
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>

#include <GL/glew.h>

////////////////////////////////////////////////////////////////////////////////
//
///
/** 
    Shader - RAII обертка над шейдером OpenGL
*/
////////////////////////////////////////////////////////////////////////////////
class Shader
{
  GLuint m_Type = 0; ///< Тип шейдера
  GLuint m_obj = 0;  ///< Идентификатор шейдера
  std::string m_shaderSource;

public:
  Shader(GLuint type, const std::string & source);
  // Конструктор копирования
  Shader(const Shader &) = delete;
  // Move-конструктор
  Shader(Shader &&) noexcept;
  ~Shader();
  // Оператор копирования
  Shader & operator=(const Shader &) = delete;
  // Оператор перемещения
  Shader & operator=(Shader &&) noexcept;

  /// Компиляция шейдера
  bool Compile();
  /// Выдать идентификатор шейдера
  GLuint GetShaderObj() const { return m_obj; }

private:
  /// Освободить ресурсы
  void DeleteShader();
};
