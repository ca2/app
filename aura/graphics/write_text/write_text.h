// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "font.h"
#include "acme/platform/department.h"
#include "acme/prototype/collection/int_map.h"


namespace write_text
{


   class CLASS_DECL_AURA write_text :
      virtual public ::acme::department
   {
   public:


      ::pointer<class fonts>                          m_pfonts;


      critical_section                                m_csFont;
      //string_to_string                                m_mapFontFaceName;
      string_map < ::memory_pointer >                 m_mapFileMemory;

      string_map < int_to_string >                    m_mapFontKeyFaceName;

      ::particle_pointer                        m_pparticleFontTextMapSynchronization;


      write_text();
      ~write_text() override;


      void on_initialize_particle() override;

      
      class fonts * fonts();


      void destroy() override;
      void term() override;


      virtual void handle_font_enumeration(::topic* ptopic);

      
      virtual font_pointer font(const font_family_pointer & pfontfamily, const font_size & fontsize, int iFontWeight = e_font_weight_normal);


      virtual font_pointer create_font();
      virtual memory_pointer get_file_memory(::acme::context * pcontext, const ::file::path & path);

      
      virtual font_descriptor calculate_font_descriptor(const char * face, float size);
      virtual string get_font_descriptor_face(const font_descriptor & font_descriptor);

      
      //virtual void enum_write_text_fonts(::write_text::font_enumeration_item_array& itema);


   };


} // namespace writetext



