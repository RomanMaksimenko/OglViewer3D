#include "ErrorMSG.h"

#include <QMessageBox>
#include <QString>


//------------------------------------------------------------------------------
/**
   Показать сообщение
*/
//---
void ErrorMessage::Show(const std::string& msg)
{
  QMessageBox::critical(nullptr, QObject::tr("Error"),QString::fromStdString(msg));
}
