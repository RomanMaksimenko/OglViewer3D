////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/ShaderProgram.h содержит класс ShaderProgram - RAII обертка над шейдерной программой
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <GL/glew.h>
#include <GL/GL.h>

////////////////////////////////////////////////////////////////////////////////
//
///
/** 
    ShaderProgram - RAII обертка над шейдерной программой
*/
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram
{
private:
  GLuint m_program = 0;
  GLuint m_transformLocation = 0;

public:
  ShaderProgram() = default;
  // Конструктор копирования
  ShaderProgram(const ShaderProgram &) = delete;
  // Конструктор перемещения
  ShaderProgram(ShaderProgram && other) noexcept;
  ~ShaderProgram();

  // Оператор копирования
  ShaderProgram & operator=(const ShaderProgram &) = delete;
  // Оператор перемещения
  ShaderProgram & operator=(ShaderProgram && other) noexcept;

  // Создать программу
  void Create();
  // Освободить занятые ресурсы
  void Destroy();
  // Выдать идентификатор программы
  GLuint Id() const { return m_program; }
  // Выдать идентификатор матрицы трансформации
  GLuint TransformLocation() const { return m_transformLocation; }

};