// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Soerensen MY ONLY LORD
// recreated by Camilo 2021-01-28 16:38
#include "framework.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/directory_context.h"
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


   void icon::set_tray_icon_name(const ::scoped_string & scopedstrTrayIconName)
   {

      m_strTrayIconName = strTrayIconName;

      //return ::success;

   }


   void * icon::get_os_data(const ::int_size & size) const
   {

      return nullptr;

   }


   void icon::load_file(const ::scoped_string & scopedstrPath)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void icon::load_matter(const ::scoped_string & scopedstrMatter)
   {

      string strPath = directory()->matter(strMatter);

      load_file(strPath);

      //if (!load_file(strPath))
      //{

      //   return ::error_io;

      //}

      //return ::success;

   }


   void icon::load_app_tray_icon(const ::scoped_string & scopedstrTrayIconName)
   {

        m_strTrayIconName = strTrayIconName;

        //return ::success;

   }


   ::image::image_pointer icon::get_image(const ::int_size & size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   ::pointer < ::innate_ui::icon > icon::innate_ui_icon(const ::int_size & size)
   {

      return {};

   }



   void icon::get_sizes(::int_size_array & a)
   {


   }


} // namespace windowing



