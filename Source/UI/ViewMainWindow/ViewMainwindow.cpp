#include "ViewMainWindow.h"

#include <QHBoxLayout>

#include "UI/ControlButtonsView/ControlButtonsView.h"
#include "UI/RenderView/RenderView.h"


ViewMainWindow::ViewMainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_buttonsView(new ControlButtonsView(this))
	, m_renderView(new RenderView(this))
{
  QWidget * centralWidget = new QWidget(this);
  QHBoxLayout * layout = new QHBoxLayout(centralWidget);
  layout->addWidget(static_cast<ControlButtonsView*>(m_buttonsView));
  layout->addWidget(static_cast<RenderView *>(m_renderView));
  centralWidget->setLayout(layout);
  setCentralWidget(centralWidget);
  resize(1024, 768);
  show();
}

  /// Установить подписчика на события представления
void ViewMainWindow::SetViewObserver(IViewObserver* observer)
{
  m_buttonsView->SetViewObserver(observer);
}

  /// Установить проводника модели
void ViewMainWindow::SetModelProvider(IModelProvider * modelProvider)
{
  m_renderView->SetModelProvider(modelProvider);
}

  /// Отрисовать сцену
void ViewMainWindow::RenderScene()
{
  if (m_renderView)
    m_renderView->RenderScene();
}
