////////////////////////////////////////////////////////////////////////////////
//
/// UI/IControlButtonsView.h содержит интерфейс модели
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

struct IViewObserver;
class QWidget;

////////////////////////////////////////////////////////////////////////
//
/// Интерфейс UI части с кнопками управления.
/**
*/
////////////////////////////////////////////////////////////////////////
struct IControlButtonsView
{
  virtual ~IControlButtonsView() = default;
  /// Установить подписчика
  virtual void SetViewObserver(IViewObserver * observer) = 0;
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() = 0;
};

/// Функция создания
IControlButtonsView * CreateControlButtonsView(QWidget * parent);
