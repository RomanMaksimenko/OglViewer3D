////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/RenderView.h содержит виджет с окном отрисовки модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "UI/IRenderView.h"
#include "UI/RenderView/Mesh.h"
#include "UI/RenderView/ShaderProgram.h"

#include <QOpenGLWidget>

////////////////////////////////////////////////////////////////////////////////
//
/// Виджет, содержащий поверхность отрисовки OpenGL
/**
*/
////////////////////////////////////////////////////////////////////////////////
class RenderView : public QOpenGLWidget,
                   public IRenderView
{
  Q_OBJECT

private:
  ISceneProvider * m_sceneProvider = nullptr;
  ShaderProgram m_GLprogram;
  Mesh m_mesh;

public:
  RenderView(QWidget * parent = nullptr);
  ~RenderView();

  /// IRenderView
  /// Установить проводника модели
  virtual void SetSceneProvider(ISceneProvider * sceneProvider) override;
  /// Отрисовать сцену
  virtual void RenderScene() override;
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() override;

protected:
  /// QOpenGLWidget
  virtual void paintGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void initializeGL() override;

private:
  /// Готов ли рендер к отрисовке
  bool IsReadyToDraw() const;
  /// Освободить ресурсы OpenGl
  void CleanUpGl();
};
