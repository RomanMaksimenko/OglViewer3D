////////////////////////////////////////////////////////////////////////////////
//
/// Core/Exceptions/ApplicationException содержит объявление базового типа исключения
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <stdexcept>
#include <source_location>
#include <string>


////////////////////////////////////////////////////////////////////////////////
//
/// Базовый класс исключения, которые могут возникать при работе приложения
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ApplicationException : public std::runtime_error
{
  std::source_location m_sourceLocation;

public:

  explicit ApplicationException(std::string_view message, std::source_location location = std::source_location::current());
  virtual ~ApplicationException() override = default;

  const std::source_location & Location() const noexcept { return m_sourceLocation; }
};
