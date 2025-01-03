// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-02-01 20:16
#pragma once


//#include "acme/filesystem/filesystem/path.h"
#include "acme/prototype/collection/osdata_array.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/size.h"



namespace windowing
{


   class CLASS_DECL_AURA cursor :
      virtual public ::particle,
      virtual public ::osdata_array
   {
   public:


      enum_cursor                                  m_ecursor;
      ::int_size                                   m_szHotspotOffset;
      ::pointer<::image::cursor>                   m_pcursor;
      ::image::image_pointer                       m_pimage;
      ::file::path                                 m_path;
      ::pointer < ::windowing::cursor_manager >    m_pcursormanager;
      ::string                                     m_strCursorName;
      //bool                                       m_bLoadSystemDefaultCursorHint;


      cursor();
      ~cursor() override;


      void destroy() override;


      virtual void set_cursor(enum_cursor ecursor);

//      virtual void load_system_default_cursor_hint();

      virtual void set_image(::image::image *pimage, int xHotspot, int yHotspot);

      virtual void set_file_path(const ::file::path & path);

      virtual ::file::path get_file_path() const;

      virtual void _create_os_cursor();
      
      //virtual void set_cursor_file(const ::file::path& pathParam, bool bFromCache);


   };



} // namespace windowing





