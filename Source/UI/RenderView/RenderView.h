////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/RenderView.h содержит виджет с окном отрисовки модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QOpenGLWidget>

#include "UI/IRenderView.h"

class RenderView : public IRenderView,
                   QOpenGLWidget
{
  IModelProvider * m_modelProvider;

public:
  RenderView(QWidget * parent = nullptr);

  /// IRenderView
  /// Установить проводника модели
  virtual void SetModelProvider(IModelProvider * modelProvider) override;
  /// Отрисовать сцену
  virtual void RenderScene() override;

protected:
  /// QOpenGLWidget
  virtual void paintGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void initializeGL() override;
};
