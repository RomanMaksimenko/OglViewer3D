////////////////////////////////////////////////////////////////////////////////
//
/// ViewerController.h содержит объявление контроллера приложения
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "IViewObserver.h"

struct IDocument;
struct IView;


////////////////////////////////////////////////////////////////////////////////
//
/// Контроллер приложения просмотра 3Д моделей
/**
  Класс реализует обработку событий пользовательского ввода, поступающих
  от представления, инициирует  изменения модели в соответствии с 
  обработанными событиями, инициирует изменения представления в 
  соответствии с изменениями модели.
*/
////////////////////////////////////////////////////////////////////////////////
class ViewerController : public IViewObserver
{
  std::unique_ptr<IView> m_view; ///< Представление
  std::unique_ptr<IDocument> m_Document; ///< Документ

public:
  ViewerController();
  ~ViewerController();
  // IViewObserver
  // Обработка нажатия на кнопки трансляции
  virtual void MoveModel(Direction dir, float delta) override;
  // Обработка нажатия на кнопки вращения модели
  virtual void RotateModel(Axis axis, float angle) override;
  // Обработка нажатия на кнопки масштаба
  virtual void ScaleModel(float scale) override;
};
