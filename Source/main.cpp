#include <iostream>
#include <QApplication>
#include <qwidget>

#include <Core/Exceptions/ApplicationException.h>
#include <Core/Logger/Logger.h>
#include <UI/ErrorMSG/ErrorMSG.h>
#include <UI/ViewFactory/ViewFactory.h>
#include <ViewerController.h>
#include <Scene/Scene.h>

int main(int argc, char * argv[])
{
  try
  {
    QApplication app(argc, argv);
    ViewFactory vf;
    ViewerController vc(vf,CreateScene());
    return app.exec();
  }
  catch (ApplicationException & e)
  {
    Core::Logger::Error(e);
    ErrorMessage::Show(e.what());
  }
}
