#include "ModelSerializer.h"

//------------------------------------------------------------------------------
/**
   Сериализация модели
*/
//---
bool ModelSerializer::serialize(const IModel & model, std::ostream & out)
{
  return false;
}


//------------------------------------------------------------------------------
/**
   Десериализация модели
*/
//---
std::unique_ptr<IModel> ModelSerializer::deSerialize(std::istream & in)
{
  return nullptr;
}
