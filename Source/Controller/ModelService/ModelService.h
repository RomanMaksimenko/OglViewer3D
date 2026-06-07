////////////////////////////////////////////////////////////////////////////////
//
/// Controller/ModelService/ModelService.h содержит клас, отвечающий за чтение/запись модели
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "Controller/IModelService.h"
#include "Model/IModelSerializer.h"


////////////////////////////////////////////////////////////////////////////////
//
/// Файл, реализующий логику чтения/записи модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ModelService : public IModelService
{
  std::unique_ptr<IModelSerializer> m_serializer;

  public:
  ModelService();

  /// IModelService
  /// Загрузить модель с диска
  virtual bool Load(const std::string & path) override;
  /// Записать модель на диск
  virtual void Save() override;
  /// Записать модель как
  virtual void SaveAs(const std::string & path) override;
};