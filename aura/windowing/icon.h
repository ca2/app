// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Soerensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


//#include "acme/prototype/geometry2d/_geometry2d.h"

#include "acme/prototype/prototype/concrete.h"


namespace windowing
{


   class CLASS_DECL_AURA icon :
      virtual public ::particle
   {
   public:


      string                                    m_strTrayIconName;

      array < ::int_size >                      m_sizea;


      icon();
      ~icon() override;


      virtual string get_tray_icon_name() const;


      virtual void set_tray_icon_name(const ::scoped_string & scopedstrTrayIconName);


      virtual void get_sizes(::int_size_array & a);


      virtual void * get_os_data(const ::int_size & size) const;


      virtual void load_matter(const ::scoped_string & scopedstrPath);
      virtual void load_app_tray_icon(const ::scoped_string & scopedstrTrayIconName);
      virtual void load_file(const ::scoped_string & scopedstrPath);


      virtual ::image::image_pointer get_image(const ::int_size & size);


      virtual ::pointer < ::innate_ui::icon > innate_ui_icon(const ::int_size & size);
      
   };



} // namespace windowing



