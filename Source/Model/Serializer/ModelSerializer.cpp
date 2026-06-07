#include "ModelSerializer.h"

#include "Model/Creator.h"

struct IModel
{
};

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


//------------------------------------------------------------------------------
/**
   Создать сериалайзер
*/
//---
std::unique_ptr<IModelSerializer> CreateModelSerializer()
{
  return std::unique_ptr<IModelSerializer>(new ModelSerializer());
}
