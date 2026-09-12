////////////////////////////////////////////////////////////////////////////////
//
/// UI/ViewMainWindow/ViewMainWindow.h содержит виджет - главное окно приложения
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QMainWindow>

#include "UI/IView.h"

struct IRenderView;
struct IControlButtonsView;

class ViewMainWindow : public QMainWindow,
                       public IView
{
  Q_OBJECT

  IControlButtonsView * m_buttonsView;
  IRenderView* m_renderView;

public:
  ViewMainWindow(QWidget * parent = nullptr);

  /// IView
  /// Установить подписчика на события представления
  virtual void SetViewObserver(IViewObserver * observer) override;
  /// Установить проводника модели
  virtual void SetSceneProvider(ISceneProvider * sceneProvider) override;
  /// Отрисовать сцену
  virtual void RenderScene() override;
  /// Получить размер видимой области
  virtual const VisibleRect & GetVisibleRect() const override;
};
