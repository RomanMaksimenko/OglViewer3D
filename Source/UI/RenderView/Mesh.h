////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/Mesh.h содержит класс Mesh - RAII обертка над идентификаторами OpenGL
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <GL/glew.h>

#include <vector>

#include <Math/Vertex.h>

////////////////////////////////////////////////////////////////////////////////
//
///
/** 
    Mesh - RAII обертка над идентификаторами OpenGL
*/
////////////////////////////////////////////////////////////////////////////////
class Mesh
{
private:
  GLuint m_VAO = 0;
  GLuint m_VBO = 0;
  GLuint m_EBO = 0;
  size_t m_indexCount = 0;

public:
  Mesh() = default;
  // Конструктор копирования
  Mesh(const Mesh &) = delete;
  // Конструктор перемещения
  Mesh(Mesh && other) noexcept;
  ~Mesh();

  // Оператор присваивания
  Mesh & operator=(const Mesh &) = delete;
  // Оператор перемещения
  Mesh & operator=(Mesh &&) noexcept;

  // Создать Mesh
  void Create(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices);
  // Освободить занятые ресурсы
  void Destroy();
  // Выдать идентификатор VAO
  GLuint VAO() const { return m_VAO; }
  // Выдать количество индексов
  size_t IndexCount() const { return m_indexCount; }
};
