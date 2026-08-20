#include "Logger.h"

#include <Core/RW/RWUtils.h>

#include <Core/Exceptions/ApplicationException.h>

//------------------------------------------------------------------------------
/**
   Запись предупреждений
*/
//---
void Core::Logger::Warning(std::string_view warning)
{
  std::filesystem::path logPath = std::filesystem::current_path() / "application.txt";
  WriteFile(logPath, warning);
}


//------------------------------------------------------------------------------
/**
   Запись ошибок
*/
//---
void Core::Logger::Error(const ApplicationException & error)
{
  std::filesystem::path logPath = std::filesystem::current_path() / "application.txt";
  WriteFile(logPath, error.what());
}
