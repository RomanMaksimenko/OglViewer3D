////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/RenderView.h содержит виджет с окном отрисовки модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "UI/IRenderView.h"


////////////////////////////////////////////////////////////////////////////////
//
/// Виджет, содержащий поверхность отрисовки OpenGL
/**
*/
////////////////////////////////////////////////////////////////////////////////
class RenderView : public QOpenGLWidget,
                   protected QOpenGLFunctions,
                   public IRenderView
{
  Q_OBJECT

private:
  IModelProvider * m_modelProvider = nullptr;

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
