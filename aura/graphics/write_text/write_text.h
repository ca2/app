// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


#include "font.h"


namespace write_text
{


   class CLASS_DECL_AURA write_text :
      virtual public ::acme::department
   {
   public:



      __pointer(class fonts)           m_pfonts;


      critical_section                 m_csFont;
      string_to_string                 m_mapFontFaceName;


      write_text();
      ~write_text() override;

      
      class fonts * fonts();


      void destroy() override;
      void term() override;


      virtual void handle_font_enumeration(::topic* ptopic);

      
      virtual font_pointer point_font(const ::string & pszFontName, double dFontSize, int iFontWeight = e_font_weight_normal);


      virtual font_pointer create_font();

      
      virtual void enum_write_text_fonts(::write_text::font_enumeration_item_array& itema);


   };


} // namespace writetext



