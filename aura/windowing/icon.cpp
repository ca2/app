// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "_windowing.h"


namespace windowing
{


   icon::icon()
   {

   }


   icon::~icon()
   {


   }


   iptr display::get_os_data() const
   {

      return -1;

   }


   window * display::default_root_window()
   {

      return nullptr;

   }

   bool icon::load_file(string strPath)
   {

      __throw(interface_only_exception());

      return false;

   }


   bool icon::load_matter(string strMatter)
   {

      string strPath = Context.dir().matter(strMatter);

      if (!load_file(strPath))
      {

         return false;

      }


      on_update_icon();

      return true;

   }

   bool icon::load_app_tray_icon(string strApp)
   {

#ifdef WINDOWS_DESKTOP

      string strMatter = "main/icon.ico";

      if (!load_matter(strMatter))
      {

         return false;

      }

      return true;

#else

      m_strAppTrayIcon = strApp;

      return true;

#endif


   }


   image * icon::get_image(const concrete < ::size_i32 > & size)
   {

      __throw(interface_only_exception);
      
      return nullptr;

   }




} // namespace windowing




