////////////////////////////////////////////////////////////////////////////////
//
/// ViewerController.h содержит объявление контроллера приложения
//
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

#include "IViewObserver.h"

#include <Core/Scene/ISceneProvider.h>

struct IModel;
struct IView;
struct IModelService;
struct IViewFactory;
struct IScene;


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
                                ISceneProvider
{
  std::unique_ptr<IView> m_view;      ///< Представление
  std::unique_ptr<IModel> m_model; ///< Модель
  std::unique_ptr<IModelService> m_modelService;///< Объект, для чтения/записи модели
  std::unique_ptr<IScene> m_scene; ///< Объект состояния сцены

public:
  explicit ViewerController(IViewFactory & viewFactory, std::unique_ptr<IScene> scene);
  ~ViewerController();
  /// IViewObserver
  /// Обработка нажатия на кнопки трансляции
  virtual void MoveModel(Direction dir) override;
  /// Обработка нажатия на кнопки вращения модели
  virtual void RotateModel(Axis axis,RotationDirection rDir) override;
  /// Обработка нажатия на кнопки масштаба
  virtual void ScaleModel(Scaling scale) override;

  /// ISceneProvider
  /// Получить вершины для отрисовки
  virtual std::vector<Vertex> GetVertices() const override;
  /// Получить индексы порядка отрисовки вершин
  virtual std::vector<unsigned int> GetIndices() const override;
  /// Получить матрицу модели
  virtual const Matrix4f & GetModelMatrix() const override;
  /// Получить  матрицу трансформации вида
  virtual const Matrix4f & GetViewMatrix() const override;
  /// Получить матрицу проекции
  virtual const Matrix4f & GetProjectionMatrix() const override;
};
