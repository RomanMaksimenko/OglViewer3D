#include "Texture.h"

#include <Core/Exceptions/FileException.h>
#include <GL/GL.h>
#include <Graphics/Image.h>

//------------------------------------------------------------------------------
/**

*/
//---
Texture::Texture(GLenum textureTarget, const std::string & source)
  : m_textureTarget(textureTarget)
  , m_textureID(0)
  , m_textureSource(source)
{
  Load();
}


//------------------------------------------------------------------------------
/**
   Деструктор
*/
//---
Texture::~Texture()
{
  Destroy();
}


//------------------------------------------------------------------------------
/**
   Move-конструктор
*/
//---
Texture::Texture(Texture && other) noexcept
  : m_textureTarget(other.m_textureTarget)
  , m_textureID(other.m_textureID)
  , m_textureSource(std::move(other.m_textureSource))
{
  other.m_textureTarget = 0;
  other.m_textureID = 0;
}


//------------------------------------------------------------------------------
/**
   Оператор перемещения
*/
//---
Texture & Texture::operator=(Texture && other) noexcept
{
  if (this != &other)
  {
    Destroy();
    m_textureTarget = other.m_textureTarget;
    m_textureID = other.m_textureID;
    m_textureSource = std::move(other.m_textureSource);
    other.m_textureTarget = 0;
    other.m_textureID = 0;
  }
  return *this;
}


//------------------------------------------------------------------------------
/**
   Привязать тектсуру к TextureUnit
*/
//---
void Texture::Bind(GLenum textureUnit)
{
  glActiveTexture(textureUnit);
  glBindTexture(m_textureTarget, m_textureID);
}


//------------------------------------------------------------------------------
/**
   Загрузить текстуру
*/
//---
void Texture::Load()
{
  Image img;
  img.Load(m_textureSource);

  if (!img.IsLoaded())
    throw FileException("Failed to load texture" + m_textureSource);

  glGenTextures(1, &m_textureID);
  glBindTexture(m_textureTarget, m_textureID);
  /// Image загружает количество каналов, TODO - перейти с GL_RGB на фактический формат
  glTexImage2D(m_textureTarget, 0, GL_RGB, img.Width(), img.Height(), 0, GL_RGB, GL_UNSIGNED_BYTE, img.Data());

  glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(m_textureTarget, 0);
}


//------------------------------------------------------------------------------
/**
   Освободить ресурсы
*/
//---
void Texture::Destroy()
{
  m_textureTarget = 0;
  if (m_textureID != 0)
    glDeleteTextures(1, &m_textureID);
  m_textureID = 0;
  m_textureSource.clear();
}
