#include <iostream>
#include <qwidget>
#include <QApplication>

#include <ViewerController.h>
#include <UI/ViewFactory/ViewFactory.h>

int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  ViewFactory vf;
  ViewerController vc(vf);
  return app.exec();
}
