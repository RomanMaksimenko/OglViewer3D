////////////////////////////////////////////////////////////////////////////////
//
/// UI/RenderView/RenderView.h содержит виджет с окном отрисовки модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once
#include <GL/glew.h>
#include <GL/GL.h>

#include <QOpenGLWidget>

#include "UI/IRenderView.h"


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
  IModelProvider * m_modelProvider = nullptr;
  GLuint VAO;
  GLuint VBO;
  GLuint IBO;
  GLuint shaderProgram;

public:
  RenderView(QWidget * parent = nullptr);

  /// IRenderView
  /// Установить проводника модели
  virtual void SetModelProvider(IModelProvider * modelProvider) override;
  /// Отрисовать сцену
  virtual void RenderScene() override; 
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() override;

protected:
  /// QOpenGLWidget
  virtual void paintGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void initializeGL() override;

};
