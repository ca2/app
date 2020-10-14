#include "framework.h"
#include "gnome_gnome.h"
#include "acme/os/linux/appindicator.h"


namespace user
{


   bool gsettings_get(string & str, const char * pszSchema, const char * pszKey)
   {

      char * psz = gsettings_get_malloc(pszSchema, pszKey);

      if(psz == nullptr)
      {

         return false;

      }

      try
      {

         str = psz;

      }
      catch(...)
      {

      }

      try
      {

         ::free(psz);

      }
      catch(...)
      {

      }

      return true;

   }

}

#ifndef RASPBIAN

namespace linux
{


   void appindicator_destroy(appindicator * pindicator)
   {

      delete pindicator;

   }

} // namespace linux


#endif






