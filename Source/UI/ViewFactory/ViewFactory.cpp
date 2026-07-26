#include "ViewFactory.h"

#include <UI/ViewMainWindow/ViewMainWindow.h>


//------------------------------------------------------------------------------
/**
   Создать ViewMainWindow
*/
//---
std::unique_ptr<IView> ViewFactory::CreateView()
{
  return std::make_unique<ViewMainWindow>();
}
