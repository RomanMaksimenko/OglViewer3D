#include "ControlButtonsView.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include "Controller/IViewObserver.h"

namespace Transforms
{
constexpr float delta = 0.05;
constexpr float angle = 0.01;
constexpr float scale = 0.1;
} // namespace Transforms

//------------------------------------------------------------------------------
/**
*/
//---
ControlButtonsView::ControlButtonsView(QWidget * parent)
  : QWidget(parent)
  , moveLeft(new QPushButton("Влево",this))
  , moveRight(new QPushButton("Вправо", this))
  , moveUp(new QPushButton("Вверх", this))
  , moveDown(new QPushButton("Вниз", this))
  , moveFront(new QPushButton("Вперед", this))
  , moveBack(new QPushButton("Назад", this))
  , rotateCWX(new QPushButton("По часовой", this))
  , rotateCCWX(new QPushButton("Против", this))
  , rotateCWY(new QPushButton("По часовой", this))
  , rotateCCWY(new QPushButton("Против", this))
  , rotateCWZ(new QPushButton("По часовой", this))
  , rotateCCWZ(new QPushButton("Против", this))
  , scaleUp(new QPushButton("+", this))
  , scaleDown(new QPushButton("-", this))
{
  QVBoxLayout * verticalLayout = new QVBoxLayout(this);
  // Наполнение блока "Перемещение"
  QLabel * translate = new QLabel("Перемещение :");
  verticalLayout->addWidget(translate, 0, Qt::AlignCenter);

  QHBoxLayout * translateLR = new QHBoxLayout(this);
  translateLR->addWidget(moveLeft);
  translateLR->addWidget(moveRight);
  verticalLayout->addLayout(translateLR);

  QHBoxLayout * translateUD = new QHBoxLayout(this);
  translateUD->addWidget(moveUp);
  translateUD->addWidget(moveDown);
  verticalLayout->addLayout(translateUD);

  QHBoxLayout * translateFB = new QHBoxLayout(this);
  translateFB->addWidget(moveFront);
  translateFB->addWidget(moveBack);
  verticalLayout->addLayout(translateFB);

  // Наполнение блока "Вращение"
  QLabel * rotate = new QLabel("Вращение :");
  verticalLayout->addWidget(rotate, 0, Qt::AlignCenter);
  QLabel * axisX = new QLabel("Ось X");
  verticalLayout->addWidget(axisX, 0, Qt::AlignCenter);
  QHBoxLayout * rotateX = new QHBoxLayout(this);
  rotateX->addWidget(rotateCWX);
  rotateX->addWidget(rotateCCWX);
  verticalLayout->addLayout(rotateX);
  QLabel * axisY = new QLabel("Ось Y");
  verticalLayout->addWidget(axisY, 0, Qt::AlignCenter);
  QHBoxLayout * rotateY = new QHBoxLayout(this);
  rotateY->addWidget(rotateCWY);
  rotateY->addWidget(rotateCCWY);
  verticalLayout->addLayout(rotateY);
  QLabel * axisZ = new QLabel("Ось Z");
  verticalLayout->addWidget(axisZ, 0, Qt::AlignCenter);
  QHBoxLayout * rotateZ = new QHBoxLayout(this);
  rotateZ->addWidget(rotateCWZ);
  rotateZ->addWidget(rotateCCWZ);
  verticalLayout->addLayout(rotateZ);

  // Наполнение блока "Масштаб"
  QLabel * scale = new QLabel("Масштаб :");
  verticalLayout->addWidget(scale, 0, Qt::AlignCenter);
  QHBoxLayout * scaleBtns = new QHBoxLayout(this);
  scaleBtns->addWidget(scaleUp);
  scaleBtns->addWidget(scaleDown);
  verticalLayout->addLayout(scaleBtns);

  setLayout(verticalLayout);
  // Перемещение
  connect(moveLeft, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Left); });
  connect(moveRight, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Right); });
  connect(moveUp, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Up); });
  connect(moveDown, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Down); });
  connect(moveFront, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Front); });
  connect(moveBack, &QPushButton::clicked, this, [this]() { this->MoveButtonPushed(Direction::Back); });
  // Вращение
  connect(rotateCWX, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::X, RotationDirection::CW); });
  connect(rotateCCWX, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::X, RotationDirection::CCW); });
  connect(rotateCWY, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::Y, RotationDirection::CW); });
  connect(rotateCCWY, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::Y, RotationDirection::CCW); });
  connect(rotateCWZ, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::Z, RotationDirection::CW); });
  connect(rotateCCWZ, &QPushButton::clicked, this, [this]() { this->RotateButtonPushed(Axis::Z, RotationDirection::CCW); });
  // Масштабирование
  connect(scaleUp, &QPushButton::clicked, this, [this]() { this->ScaleButtonPushed(Scaling::INC); });
  connect(scaleDown, &QPushButton::clicked, this, [this]() { this->ScaleButtonPushed(Scaling::DESC); });
}


//------------------------------------------------------------------------------
/**
   Установить подписчика
*/
//---
void ControlButtonsView::SetViewObserver(IViewObserver * observer)
{
  m_viewObserver = observer;
}


//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки движения
*/
//---
void ControlButtonsView::MoveButtonPushed(Direction dir)
{
  if (m_viewObserver)
    m_viewObserver->MoveModel(dir);
}


//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки вращения
*/
//---
void ControlButtonsView::RotateButtonPushed(Axis axis, RotationDirection rDir)
{
  if (m_viewObserver)
    m_viewObserver->RotateModel(axis, rDir);
}

//------------------------------------------------------------------------------
/**
   Обработка нажатия кнопки вращения
*/
//---
void ControlButtonsView::ScaleButtonPushed(Scaling sc)
{
  if (m_viewObserver)
    m_viewObserver->ScaleModel(sc);
}
