#pragma once


namespace write_text
{


   class CLASS_DECL_AURA fonts :
      virtual public ::acme::department
   {
   public:


      __pointer(font_enumeration)                  m_pfontenumeration;
      ::write_text::font_enumeration_item_array    m_fontenumerationitema;


      fonts();
      ~fonts() override;


      ::e_status initialize(::object* pobject) override;


      virtual ::e_status enumerate_fonts();


      virtual font_enumeration* enumeration();


      virtual string default_font_name();


      virtual double font_similarity(const ::string & pszSystem, const ::string & pszUser);


   };


} //namespace write_text



