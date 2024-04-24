#pragma once


#include "font_enumeration.h"
#include "acme/platform/department.h"


namespace write_text
{


   class CLASS_DECL_AURA fonts :
      virtual public ::acme::department
   {
   public:


      string_map < ::pointer<font_enumeration> >                  m_mapFontEnumeration;
      string_map < ::write_text::font_enumeration_item_array >    m_mapFontEnumerationItemArray;


      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;


      virtual void enumerate_fonts(const ::scoped_string & scopedstrFontBranch);


      virtual font_enumeration* enumeration(const ::scoped_string & scopedstrFontBranch);


      virtual string default_font_name();


      virtual double font_similarity(const ::string & pszSystem, const ::string & pszUser);


   };


} //namespace write_text



