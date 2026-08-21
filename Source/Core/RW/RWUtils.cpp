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



//------------------------------------------------------------------------------
/**
   Записать файл
*/
//---
bool WriteFile(const std::filesystem::path& path, std::string_view data)
{
  std::ofstream file(path);

  if (!file.is_open())
    throw FileException("Failed to open file fo writing " + path.string());

  file.write(data.data(), static_cast<std::streamsize>(data.size()));

  if (!file)
    throw FileException("Failed to write file: " + path.string());
}
