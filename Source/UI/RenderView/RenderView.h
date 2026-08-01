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
  GLuint m_VAO;
  GLuint m_VBO;
  GLuint m_EBO;
  GLuint m_GLprogram;

public:
  RenderView(QWidget * parent = nullptr);
  ~RenderView();

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

private:
  /// Создать программу отрисовки
  void CreateGLProgram();
  /// Готов ли рендер к отрисовке
  bool IsReadyToDraw() const;
  /// Освободить ресурсы OpenGl
  void CleanUpGl();

};
