////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/Texture.h содержит класс Texture- RAII обертка над объектом текстуры
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
    Texture- RAII обертка над объектом текстуры OpenGL
*/
//
////////////////////////////////////////////////////////////////////////////////
class Texture
{
  GLenum m_textureTarget = 0;  ///< Тип текстуры
  GLuint m_textureID = 0;      ///< Идентификатор текстуры
  std::string m_textureSource; ///< Путь к файлу текстуры
public:
  explicit Texture(GLenum textureTarget, const std::string & source);
  // Конструктор копирования
  Texture(const Texture &) = delete;
  // Move-конструктор
  Texture(Texture &&) noexcept;
  ~Texture();
  // Оператор копирования
  Texture & operator=(const Texture &) = delete;
  // Оператор перемещения
  Texture & operator=(Texture &&) noexcept;

  // Привязать тектсуру к TextureUnit
  void Bind(GLenum textureUnit);

private:
  // Загрузить текстуру
  void Load();
  // Освободить ресурсы
  void Destroy();
};
