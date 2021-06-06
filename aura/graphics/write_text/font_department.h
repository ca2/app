#pragma once


namespace write_text
{


   class CLASS_DECL_AURA font_department :
      virtual public ::acme::department
   {
   public:


      __pointer(::write_text::font_enumeration)    m_pfontenumeration;
      ::write_text::font_enum_item_array           m_fontenumitema;


      font_department();
      virtual ~font_department();


      ::e_status initialize(::object* pobject) override;


      virtual ::e_status enumerate_fonts();


      virtual font_enumeration* font_enumeration();


      virtual string default_font_name();


      virtual double font_similarity(const char* pszSystem, const char* pszUser);


   };


} //namespace write_text



