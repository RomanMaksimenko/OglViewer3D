#include "Image.h"

#include <Core/Exceptions/FileException.h>
#include <string>

#include "stb_image.h"


//------------------------------------------------------------------------------
/**

*/
//---
Image::~Image()
{
  ClearData();
}

//------------------------------------------------------------------------------
/**
   Конструктор перемещения
*/
//---
Image::Image(Image && other) noexcept
  : m_imageData(other.m_imageData)
  , m_width(other.m_width)
  , m_height(other.m_height)
  , m_channels(other.m_channels)
{
  other.m_imageData = nullptr;
  other.m_width = 0;
  other.m_height = 0;
  other.m_channels = 0;
}


//------------------------------------------------------------------------------
/**
   Конструктор перемещения
*/
//---
Image & Image::operator=(Image && other) noexcept
{
  if (this != &other)
  {
    ClearData();
    m_imageData = other.m_imageData;
    m_width = other.m_width;
    m_height = other.m_height;
    m_channels = other.m_channels;

    other.m_imageData = nullptr;
    other.m_width = 0;
    other.m_height = 0;
    other.m_channels = 0;
  }
  return *this;
}

//------------------------------------------------------------------------------
/**
  Загрузить изображение
*/
//---
void Image::Load(const std::filesystem::path & path)
{
  ClearData();
  stbi_set_flip_vertically_on_load(1);
  m_imageData = stbi_load(path.string().c_str(), &m_width, &m_height, &m_channels, 0);
  if (!m_imageData)
    throw FileException("Cannot load texture from file " + path.string());
}


//------------------------------------------------------------------------------
/**
  Загружено ли изображение
*/
//---
bool Image::IsLoaded() const noexcept
{
  return m_imageData != nullptr;
}


//------------------------------------------------------------------------------
/**
  Получить данные изображения
*/
//---
const unsigned char * Image::Data() const
{
  return m_imageData;
}


//------------------------------------------------------------------------------
/**
  Получить ширину изображения
*/
//---
int Image::Width() const
{
  return m_width;
}


//------------------------------------------------------------------------------
/**
  Получить высоту изображения
*/
//---
int Image::Height() const
{
  return m_height;
}


//------------------------------------------------------------------------------
/**
  Получить количество каналов
*/
//---
int Image::Channels() const
{
  return m_channels;
}


//------------------------------------------------------------------------------
/**
   Освободить ресурсы
*/
//---
void Image::ClearData()
{
  if (m_imageData)
    stbi_image_free(m_imageData);
  m_imageData = nullptr;
  m_width = 0;
  m_height = 0;
  m_channels = 0;
}
