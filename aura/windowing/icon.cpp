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


   ::e_status icon::set_tray_icon_name(const ::string & strTrayIconName)
   {

      m_strTrayIconName = strTrayIconName;

      return ::success;

   }


   void * icon::get_os_data(const ::size_i32 & size) const
   {

      return nullptr;

   }


   ::e_status icon::load_file(const ::string & strPath)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status icon::load_matter(const ::string & strMatter)
   {

      auto pcontext = get_context();

      string strPath = pcontext->m_papexcontext->dir().matter(strMatter);

      if (!load_file(strPath))
      {

         return ::error_io;

      }

      return ::success;

   }


   ::e_status icon::load_app_tray_icon(const ::string & strTrayIconName)
   {

        m_strTrayIconName = strTrayIconName;

        return ::success;

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



