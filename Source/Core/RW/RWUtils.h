////////////////////////////////////////////////////////////////////////////////
//
/// Core/RW/RWUtils.h содержит утилиты для чтения/записи с диска
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <filesystem>
#include <string>

/// Прочитать файл
std::string ReadFile(const std::filesystem::path & path);

/// Записать файл
bool WriteFile(const std::filesystem::path & path, std::string_view data);
