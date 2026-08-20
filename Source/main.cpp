#include <iostream>
#include <QApplication>
#include <qwidget>

#include <Core/Exceptions/ApplicationException.h>
#include <Core/Logger/Logger.h>
#include <UI/ViewFactory/ViewFactory.h>
#include <ViewerController.h>

int main(int argc, char * argv[])
{
  try
  {
    QApplication app(argc, argv);
    ViewFactory vf;
    ViewerController vc(vf);
    return app.exec();
  }
  catch (ApplicationException & e)
  {
    Core::Logger::Error(e);
  }
}
