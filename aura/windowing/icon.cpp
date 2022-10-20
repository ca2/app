// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "aura/graphics/image/image.h"
#include "aura/windowing/icon.h"


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

      //return ::success;

   }


   void * icon::get_os_data(const ::size_i32 & size) const
   {

      return nullptr;

   }


   void icon::load_file(const ::string & strPath)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void icon::load_matter(const ::string & strMatter)
   {

      auto pcontext = get_context();

      string strPath = pcontext->m_papexcontext->dir().matter(strMatter);

      load_file(strPath);

      //if (!load_file(strPath))
      //{

      //   return ::error_io;

      //}

      //return ::success;

   }


   void icon::load_app_tray_icon(const ::string & strTrayIconName)
   {

        m_strTrayIconName = strTrayIconName;

        //return ::success;

   }


   image_pointer icon::get_image(const concrete < ::size_i32 > & size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   void icon::get_sizes(array < concrete < ::size_i32 > > & a)
   {


   }


} // namespace windowing



