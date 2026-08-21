////////////////////////////////////////////////////////////////////////////////
//
/// UI/IRenderView.h содержит интерфейс окна содержащего сцену
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <memory>

struct IModelProvider;
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
  virtual void SetModelProvider(IModelProvider * modelProvider) = 0;
  /// Отрисовать сцену
  virtual void RenderScene() = 0; 
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() = 0;
};


/// Функция создания
IRenderView* CreateRenderView(QWidget * parent);
