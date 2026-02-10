#pragma once


#include "font_enumeration.h"
#include "acme/platform/department.h"


namespace write_text
{


   class CLASS_DECL_AURA fonts :
      virtual public ::platform::department
   {
   public:


      string_map_base < ::pointer<font_enumeration> >                  m_mapFontEnumeration;
      string_map_base < ::write_text::font_enumeration_item_array >    m_mapFontEnumerationItemArray;


      fonts();
      ~fonts() override;


      void initialize(::particle * pparticle) override;


      virtual void enumerate_fonts(const ::scoped_string & scopedstrFontBranch);


      virtual font_enumeration* enumeration(const ::scoped_string & scopedstrFontBranch);


      virtual string default_font_name();


      virtual double font_similarity(const ::scoped_string & scopedstrSystem, const ::scoped_string & scopedstrUser);


   };


} //namespace write_text



