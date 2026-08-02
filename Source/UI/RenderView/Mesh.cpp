#include "Mesh.h"


Mesh::~Mesh()
{
  Destroy();
}

//------------------------------------------------------------------------------
/**
   Создать Mesh
*/
//---
void Mesh::Create(const std::vector<Vertex> & vertices, const std::vector<unsigned int> & indices)
{
  Destroy();

  if (vertices.empty() || indices.empty())
    return;

  m_indexCount = indices.size();
  // Создаим и заполним буферы
  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(0);

  glGenBuffers(1, &m_EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
  glBindVertexArray(0);
}


//------------------------------------------------------------------------------
/**
   Освободить занятые ресурсы
*/
//---
void Mesh::Destroy()
{
  if (m_VAO)
  {
    glDeleteVertexArrays(1, &m_VAO);
    m_VAO = 0;
  }
  if (m_VBO)
  {
    glDeleteBuffers(1, &m_VBO);
    m_VBO = 0;
  }
  if (m_EBO)
  {
    glDeleteBuffers(1, &m_EBO);
    m_EBO = 0;
  }
  m_indexCount = 0;
}
