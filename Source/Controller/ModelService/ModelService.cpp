#include "ModelService.h"

#include "Model/Creator.h"

//------------------------------------------------------------------------------
/**
*/
//---
ModelService::ModelService()
  : m_serializer(CreateModelSerializer())
{
}


//------------------------------------------------------------------------------
/**
   Загрузить модель с диска
*/
//---
bool ModelService::Load(const std::string & path)
{
  return false;
}


//------------------------------------------------------------------------------
/**
   Записать модель на диск
*/
//---
void ModelService::Save()
{
}


//------------------------------------------------------------------------------
/**
   Записать модель как
*/
//---
void ModelService::SaveAs(const std::string & path)
{
}
