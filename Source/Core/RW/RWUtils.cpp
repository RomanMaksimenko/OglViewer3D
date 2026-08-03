#include "RWUtils.h"

#include <fstream>
#include <iostream>


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
    return result;

  std::string line;
  while (std::getline(file, line))
    result += line + '\n';

  return result;
}
