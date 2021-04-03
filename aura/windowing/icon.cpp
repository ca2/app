// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
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


   string icon::get_tray_icon_name() const
   {

      return m_strTrayIconName;

   }


   void icon::set_tray_icon_name(const ::string & strTrayIconName)
   {

      m_strTrayIconName = strTrayIconName;

   }


   void * icon::get_os_data(const ::size_i32 & size) const
   {

      return nullptr;

   }


   ::e_status icon::load_file(string strPath)
   {

      __throw(error_interface_only);

      return false;

   }


   ::e_status icon::load_matter(string strMatter)
   {

      auto pcontext = get_context();

      string strPath = pcontext->m_papexcontext->dir().matter(strMatter);

      if (!load_file(strPath))
      {

         return false;

      }

//      on_update_icon();

      return true;

   }


   ::e_status icon::load_app_tray_icon(string strApp)
   {

#ifdef WINDOWS_DESKTOP

      string strMatter = "main/icon.ico";

      if (!load_matter(strMatter))
      {

         return false;

      }

      return true;

#else

      //m_strAppTrayIcon = strApp;

      return true;

#endif


   }


   image_pointer icon::get_image(const concrete < ::size_i32 > & size)
   {

      __throw(error_interface_only);
      
      return nullptr;

   }


   void icon::get_sizes(array < concrete < ::size_i32 > > & a)
   {


   }


} // namespace windowing



