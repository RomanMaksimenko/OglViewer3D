#include "RWUtils.h"

#include <fstream>
#include <iostream>

#include "Core/Exceptions/FileException.h"


//------------------------------------------------------------------------------
/**
   Прочитать файл
*/
//---
std::string ReadFile(const std::filesystem::path& path)
{
  std::string result;
  std::ifstream file(path);
  if (!file.is_open())
    throw FileException("Failed to read file " + path.string());

  std::string line;
  while (std::getline(file, line))
    result += line + '\n';

  return result;
}
