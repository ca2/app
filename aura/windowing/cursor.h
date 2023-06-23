// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


//#include "acme/filesystem/filesystem/path.h"
#include "acme/primitive/collection/osdata_array.h"
//#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/size.h"
#include "acme/primitive/primitive/particle.h"


namespace windowing
{


   class CLASS_DECL_AURA cursor :
      virtual public ::particle,
      virtual public ::osdata_array
   {
   public:


      enum_cursor                         m_ecursor;
      ::size_i32                          m_szHotspotOffset;
      ::pointer<::draw2d::cursor>         m_pcursor;
      image_pointer                       m_pimage;
      ::file::path                        m_path;
      //bool                                m_bLoadSystemDefaultCursorHint;


      cursor();
      ~cursor() override;


      virtual void set_cursor(enum_cursor ecursor);

//      virtual void load_system_default_cursor_hint();

      virtual void set_image(::image * pimage, ::i32 xHotspot, ::i32 yHotspot);

      virtual void set_file_path(const ::file::path & path);

      virtual ::file::path get_file_path() const;

      virtual void _create_os_cursor();
      
      //virtual void set_cursor_file(const ::file::path& pathParam, bool bFromCache);


   };



} // namespace windowing





