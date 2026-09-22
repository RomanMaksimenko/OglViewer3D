#include "ControlButtonsView.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>

#include "Controller/IViewObserver.h"


////////////////////////////////////////////////////////////////////////////////
//
///
/** 
    Приватный объект для инкапсуляции логики обработки долгого нажатия клавиш движения
*/
////////////////////////////////////////////////////////////////////////////////
class MovementTimer : public QTimer
{
  Q_OBJECT
private:
  Direction m_direction = Direction::None; ///< направление перемещения
  struct Rotation
  {
    Axis axis = Axis::None;
    RotationDirection rotDir = RotationDirection::None;
  } m_rotation;                    ///< направление вращения
  Scaling m_scale = Scaling::None; ///< масштабирование

public:
  explicit MovementTimer(QObject * parent);
  void StartMove(Direction dir);
  void StopMove();
  void StartRotate(Axis a, RotationDirection rd);
  void StopRotate();
  void StartScale(Scaling sc);
  void StopScale();

private:
  void Transform();

signals:
  void Move(Direction dir);
  void Rotate(Axis a, RotationDirection rd);
  void Scale(Scaling sc);
};


//------------------------------------------------------------------------------
/**
   
*/
//---
MovementTimer::MovementTimer(QObject * parent)
  : QTimer(parent)
{
  setInterval(16);
  connect(this, &QTimer::timeout, this, &MovementTimer::Transform);
}


//------------------------------------------------------------------------------
/**
   Начать движение
*/
//---
void MovementTimer::StartMove(Direction dir)
{
  m_rotation = Rotation{Axis::None, RotationDirection::None};
  m_scale = Scaling::None;

  m_direction = dir;
  start();
}


//------------------------------------------------------------------------------
/**
  Прекратить движение
*/
//---
void MovementTimer::StopMove()
{
  m_direction = Direction::None;
  stop();
}


//------------------------------------------------------------------------------
/**
   Начать вращение
*/
//---
void MovementTimer::StartRotate(Axis a, RotationDirection rd)
{
  m_direction = Direction::None;
  m_scale = Scaling::None;

  m_rotation = Rotation{a, rd};
  start();
}


//------------------------------------------------------------------------------
/**
  Прекратить вращение
*/
//---
void MovementTimer::StopRotate()
{
  m_rotation = Rotation{Axis::None, RotationDirection::None};
  stop();
}


//------------------------------------------------------------------------------
/**
   Начать масштабирование
*/
//---
void MovementTimer::StartScale(Scaling sc)
{
  m_direction = Direction::None;
  m_rotation = Rotation{Axis::None, RotationDirection::None};

  m_scale = sc;
  start();
}


//------------------------------------------------------------------------------
/**
   Прекратить масштабирование
*/
//---
void MovementTimer::StopScale()
{
  m_scale = Scaling::None;
  stop();
}


//------------------------------------------------------------------------------
/**
   Трансформация по таймеру
*/
//---
void MovementTimer::Transform()
{
  if (m_direction != Direction::None)
    emit Move(m_direction);
  if (m_rotation.axis != Axis::None && m_rotation.rotDir != RotationDirection::None)
    emit Rotate(m_rotation.axis, m_rotation.rotDir);
  if (m_scale != Scaling::None)
    emit Scale(m_scale);
}


//------------------------------------------------------------------------------
/**
*/
//---
ControlButtonsView::ControlButtonsView(QWidget * parent)
  : QWidget(parent)
  , moveLeft(new QPushButton("Влево", this))
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
  , m_timer(new MovementTimer(this))
{
  QVBoxLayout * verticalLayout = new QVBoxLayout(this);
  // Наполнение блока "Перемещение"
  QLabel * translate = new QLabel("Перемещение :");
  verticalLayout->addWidget(translate, 0, Qt::AlignCenter);

  QHBoxLayout * translateLR = new QHBoxLayout();
  translateLR->addWidget(moveLeft);
  translateLR->addWidget(moveRight);
  verticalLayout->addLayout(translateLR);

  QHBoxLayout * translateUD = new QHBoxLayout();
  translateUD->addWidget(moveUp);
  translateUD->addWidget(moveDown);
  verticalLayout->addLayout(translateUD);

  QHBoxLayout * translateFB = new QHBoxLayout();
  translateFB->addWidget(moveFront);
  translateFB->addWidget(moveBack);
  verticalLayout->addLayout(translateFB);

  // Наполнение блока "Вращение"
  QLabel * rotate = new QLabel("Вращение :");
  verticalLayout->addWidget(rotate, 0, Qt::AlignCenter);
  QLabel * axisX = new QLabel("Ось X");
  verticalLayout->addWidget(axisX, 0, Qt::AlignCenter);
  QHBoxLayout * rotateX = new QHBoxLayout();
  rotateX->addWidget(rotateCWX);
  rotateX->addWidget(rotateCCWX);
  verticalLayout->addLayout(rotateX);
  QLabel * axisY = new QLabel("Ось Y");
  verticalLayout->addWidget(axisY, 0, Qt::AlignCenter);
  QHBoxLayout * rotateY = new QHBoxLayout();
  rotateY->addWidget(rotateCWY);
  rotateY->addWidget(rotateCCWY);
  verticalLayout->addLayout(rotateY);
  QLabel * axisZ = new QLabel("Ось Z");
  verticalLayout->addWidget(axisZ, 0, Qt::AlignCenter);
  QHBoxLayout * rotateZ = new QHBoxLayout();
  rotateZ->addWidget(rotateCWZ);
  rotateZ->addWidget(rotateCCWZ);
  verticalLayout->addLayout(rotateZ);

  // Наполнение блока "Масштаб"
  QLabel * scale = new QLabel("Масштаб :");
  verticalLayout->addWidget(scale, 0, Qt::AlignCenter);
  QHBoxLayout * scaleBtns = new QHBoxLayout();
  scaleBtns->addWidget(scaleUp);
  scaleBtns->addWidget(scaleDown);
  verticalLayout->addLayout(scaleBtns);

  setLayout(verticalLayout);

  connect(m_timer, &MovementTimer::Move, this, &ControlButtonsView::MoveButtonPushed);
  connect(m_timer, &MovementTimer::Rotate, this, &ControlButtonsView::RotateButtonPushed);
  connect(m_timer, &MovementTimer::Scale, this, &ControlButtonsView::ScaleButtonPushed);

  // Перемещение влево
  connect(moveLeft, &QPushButton::pressed, m_timer, [this]() { m_timer->StartMove(Direction::Left); });
  connect(moveLeft, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Перемещение вправо
  connect(moveRight, &QPushButton::pressed, this, [this]() { m_timer->StartMove(Direction::Right); });
  connect(moveRight, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Перемещение вверх
  connect(moveUp, &QPushButton::pressed, this, [this]() { m_timer->StartMove(Direction::Up); });
  connect(moveUp, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Перемещение вниз
  connect(moveDown, &QPushButton::pressed, this, [this]() { m_timer->StartMove(Direction::Down); });
  connect(moveDown, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Перемещение вперед
  connect(moveFront, &QPushButton::pressed, this, [this]() { m_timer->StartMove(Direction::Front); });
  connect(moveFront, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Перемещение назад
  connect(moveBack, &QPushButton::pressed, this, [this]() { m_timer->StartMove(Direction::Back); });
  connect(moveBack, &QPushButton::released, m_timer, &MovementTimer::StopMove);
  // Вращение вокруг X по часовой стрелке
  connect(rotateCWX, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::X, RotationDirection::CW); });
  connect(rotateCWX, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Вращение вокруг X против часовой стрелки
  connect(rotateCCWX, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::X, RotationDirection::CCW); });
  connect(rotateCCWX, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Вращение вокруг Y по часовой стрелке
  connect(rotateCWY, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::Y, RotationDirection::CW); });
  connect(rotateCWY, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Вращение вокруг Y против часовой стрелки
  connect(rotateCCWY, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::Y, RotationDirection::CCW); });
  connect(rotateCCWY, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Вращение вокруг Z по часовой стрелке
  connect(rotateCWZ, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::Z, RotationDirection::CW); });
  connect(rotateCWZ, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Вращение вокруг Z против часовой стрелки
  connect(rotateCCWZ, &QPushButton::pressed, this, [this]() { m_timer->StartRotate(Axis::Z, RotationDirection::CCW); });
  connect(rotateCCWZ, &QPushButton::released, m_timer, &MovementTimer::StopRotate);
  // Увеличение масштаба
  connect(scaleUp, &QPushButton::pressed, this, [this]() { m_timer->StartScale(Scaling::INC); });
  connect(scaleUp, &QPushButton::released, m_timer, &MovementTimer::StopScale);
  // Уменьшение масштаба
  connect(scaleDown, &QPushButton::pressed, this, [this]() { m_timer->StartScale(Scaling::DESC); });
  connect(scaleDown, &QPushButton::released, m_timer, &MovementTimer::StopScale);
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
   Выдать указатель на себя как на QWidget
*/
//---
QWidget * ControlButtonsView::widget()
{
  return this;
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


//------------------------------------------------------------------------------
/**
   Функция создани
*/
//---
IControlButtonsView * CreateControlButtonsView(QWidget * parent)
{
  return new ControlButtonsView(parent);
}

#include "ControlButtonsView.moc"
