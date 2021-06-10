// Created by camilo 2021-02-10 <3TBS_!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA write_text :
      virtual public ::acme::department
   {
   public:



      __pointer(class fonts)           m_pfonts;



      write_text();
      virtual ~write_text();

      
      class fonts * fonts();


      virtual ::e_status finalize() override;
      virtual ::e_status term() override;


      virtual ::e_status handle_font_enumeration(::subject::subject* psubject);

      
      virtual font_pointer point_font(const char * pszFontName, double dFontSize, int iFontWeight = e_font_weight_normal);


      virtual font_pointer create_font();


   };


} // namespace writetext



