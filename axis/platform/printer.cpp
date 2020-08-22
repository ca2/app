#include "framework.h"
#include "aura/platform/printer.h"


namespace axis
{


   printer::printer()
   {
   }

   printer::~printer()
   {
      close();
   }

   bool printer::open(const char * pszDeviceName)
   {
      UNREFERENCED_PARAMETER(pszDeviceName);
      return false;
   }

   ::draw2d::graphics_pointer printer::create_graphics()
   {
      return nullptr;
   }

   bool printer::is_opened()
   {
      return false;
   }

   bool printer::close()
   {
      return true;
   }


} // namespace user













































