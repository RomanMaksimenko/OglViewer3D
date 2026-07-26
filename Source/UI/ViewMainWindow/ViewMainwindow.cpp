#include "ViewMainWindow.h"

#include <QHBoxLayout>

#include "UI/IControlButtonsView.h"
#include "UI/IRenderView.h"


ViewMainWindow::ViewMainWindow(QWidget* parent)
	: QMainWindow(parent)
	, m_buttonsView(CreateControlButtonsView(this))
	, m_renderView(CreateRenderView(this))
{
  QWidget * centralWidget = new QWidget(this);
  QHBoxLayout * layout = new QHBoxLayout(centralWidget);
  layout->addWidget(m_buttonsView->widget());/// TODO убрать статик касты
  layout->addWidget(m_renderView->widget());
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
