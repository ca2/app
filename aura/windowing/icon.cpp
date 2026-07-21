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

      m_strTrayIconName = scopedstrTrayIconName;

      //return ::success;

   }


   void * icon::get_os_data(const ::i32_size & size) const
   {

      return nullptr;

   }


   void icon::set_file(const ::payload & payload)
   {

      m_payload = payload;

   }


   void icon::set_matter(const ::scoped_string & scopedstrMatter)
   {

      string strPath = directory()->matter(scopedstrMatter);

      set_file(strPath);

      //if (!load_file(strPath))
      //{

      //   return ::error_io;

      //}

      //return ::success;

   }


   void icon::set_app_tray_icon(const ::scoped_string & scopedstrTrayIconName)
   {

        m_strTrayIconName = scopedstrTrayIconName;

        //return ::success;

   }


   ::image::image_pointer icon::get_image(const ::i32_size & size)
   {

      throw ::interface_only();
      
      return nullptr;

   }


   ::pointer < ::innate_ui::icon > icon::innate_ui_icon(const ::i32_size & size)
   {

      return {};

   }



   void icon::get_sizes(::i32_size_array & a)
   {


   }


} // namespace windowing



