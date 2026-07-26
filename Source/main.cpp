#include <iostream>
#include <qwidget>
#include <QApplication>

#include <ViewerController.h>
#include <UI/ViewMainWindow/ViewMainWindow.h>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  ViewerController vc;
  vc.initView(std::make_unique<ViewMainWindow>());
  std::cout << "Hello World!\n";
  return app.exec();
}
