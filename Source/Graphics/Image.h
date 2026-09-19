////////////////////////////////////////////////////////////////////////////////
//
/// Image.h содержит объявление класса изображения
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <string>


////////////////////////////////////////////////////////////////////////////////
//
/// Класс описывающий изображение
/**
* Реализует загрузку изображения и управление выделенными для него данными.
*/
////////////////////////////////////////////////////////////////////////////////
class Image
{
  unsigned char * m_imageData = nullptr; ///< изображение
  int m_width = 0;                       ///< ширина изображения
  int m_height = 0;                      ///< высота изображения
  int m_channels = 0;                    ///< количество каналов
public:
  Image() = default;
  ~Image();
  Image(const Image &) = delete;
  Image(Image &&) noexcept;
  // Операторы
  Image & operator=(const Image &) = delete;
  Image & operator=(Image &&) noexcept;

  /// Загрузить изображение
  void Load(const std::string & filePath);
  /// Загружено ли изображение
  bool IsLoaded() const noexcept;
  /// Геттеры данных изображения
  const unsigned char * Data() const;
  int Width() const;
  int Height() const;
  int Channels() const;

private:
  void ClearData();
};
