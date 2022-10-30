// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:38
#pragma once


#include "acme/primitive/primitive/object.h"


namespace windowing
{


   class CLASS_DECL_AURA icon :
      virtual public ::object
   {
   public:


      string                                    m_strTrayIconName;

      array < concrete < ::size_i32 > >         m_sizea;


      icon();
      ~icon() override;


      virtual string get_tray_icon_name() const;


      virtual void set_tray_icon_name(const ::string & strTrayIconName);


      virtual void get_sizes(array < concrete < ::size_i32 > > & a);


      virtual void * get_os_data(const ::size_i32 & size) const;


      virtual void load_matter(const ::string & strPath);
      virtual void load_app_tray_icon(const ::string & strTrayIconName);
      virtual void load_file(const ::string & strPath);


      virtual image_pointer get_image(const concrete < ::size_i32 > & size);

      
   };



} // namespace windowing



