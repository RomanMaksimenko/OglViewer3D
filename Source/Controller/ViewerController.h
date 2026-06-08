////////////////////////////////////////////////////////////////////////////////
//
/// ViewerController.h содержит объявление контроллера приложения
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "IModelProvider.h"
#include "IViewObserver.h"

struct IModel;
struct IView;
struct IModelService;


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
class ViewerController : public IViewObserver,
                                IModelProvider
{
  std::unique_ptr<IView> m_view;      ///< Представление
  std::unique_ptr<IModel> m_model; ///< Модель
  std::unique_ptr<IModelService> m_modelService;///< Объект, для чтения/записи модели

public:
  ViewerController();
  ~ViewerController();
  /// IViewObserver
  // Обработка нажатия на кнопки трансляции
  virtual void MoveModel(Direction dir, float delta) override;
  // Обработка нажатия на кнопки вращения модели
  virtual void RotateModel(Axis axis, float angle) override;
  // Обработка нажатия на кнопки масштаба
  virtual void ScaleModel(float scale) override;
  /// IModelProvider
  /// Получить вершины для отрисовки
  virtual std::vector<Vertex> GetVertexes() const;
  /// Получить индексы порядка отрисовки вершин
  virtual std::vector<unsigned int> GetIndices() const;
  /// Получить матрицу MVP
  virtual Matrix4f GetMVPMatrix() const;
};
