////////////////////////////////////////////////////////////////////////////////
//
/// UI/ControlButtonsView/ControlButtonsView.h содержит виджет с кнопками управления
/**
*/
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QPushButton>
#include <QWidget>

#include "UI/IControlButtonsView.h"

enum class Direction;
enum class Axis;
enum class RotationDirection;
enum class Scaling;

class MovementTimer;

////////////////////////////////////////////////////////////////////////////////
//
/// Виджет, содержащий кнопки управления моделью
/**
*/
////////////////////////////////////////////////////////////////////////////////
class ControlButtonsView : public QWidget,
                           public IControlButtonsView
{
  Q_OBJECT

private:
  IViewObserver * m_viewObserver = nullptr;
  QPushButton * moveLeft = nullptr;
  QPushButton * moveRight = nullptr;
  QPushButton * moveUp = nullptr;
  QPushButton * moveDown = nullptr;
  QPushButton * moveFront = nullptr;
  QPushButton * moveBack = nullptr;
  QPushButton * rotateCWX = nullptr;
  QPushButton * rotateCCWX = nullptr;
  QPushButton * rotateCWY = nullptr;
  QPushButton * rotateCCWY = nullptr;
  QPushButton * rotateCWZ = nullptr;
  QPushButton * rotateCCWZ = nullptr;
  QPushButton * scaleUp = nullptr;
  QPushButton * scaleDown = nullptr;
  MovementTimer * m_timer = nullptr;

public:
  ControlButtonsView(QWidget * parent = nullptr);

  /// IControlButtonsView/// Установить подписчика
  virtual void SetViewObserver(IViewObserver * observer) override;
  /// Выдать указатель на себя как на QWidget
  virtual QWidget * widget() override;

private:
  void MoveButtonPushed(Direction dir);
  void RotateButtonPushed(Axis axis, RotationDirection rDir);
  void ScaleButtonPushed(Scaling sc);
};
