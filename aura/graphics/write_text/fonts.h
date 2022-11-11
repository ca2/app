#pragma once


#include "font_enumeration.h"
#include "acme/platform/department.h"


namespace write_text
{


   class CLASS_DECL_AURA fonts :
      virtual public ::acme::department
   {
   public:


      ::pointer<font_enumeration>                 m_pfontenumeration;
      ::write_text::font_enumeration_item_array    m_fontenumerationitema;


      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;


      virtual void enumerate_fonts();


      virtual font_enumeration* enumeration();


      virtual string default_font_name();


      virtual double font_similarity(const ::string & pszSystem, const ::string & pszUser);


   };


} //namespace write_text



