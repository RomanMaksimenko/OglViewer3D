////////////////////////////////////////////////////////////////////////////////
//
/// UI/IRenderView.h содержит интерфейс окна содержащего сцену
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

struct ISceneProvider;
class QWidget;

////////////////////////////////////////////////////////////////////////
//
/// Интерфейс UI части c окном отрисовки модели
/**
*/
////////////////////////////////////////////////////////////////////////
struct IRenderView
{
  /// Установить проводника модели
  virtual void SetSceneProvider(ISceneProvider * sceneProvider) = 0;
  /// Отрисовать сцену
  virtual void RenderScene() = 0; 
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() = 0;
};


/// Функция создания
IRenderView* CreateRenderView(QWidget * parent);
