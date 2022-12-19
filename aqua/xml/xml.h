#pragma once


#include "acme/platform/department.h"
#include "acme/primitive/collection/string_map.h"


namespace xml
{


   class CLASS_DECL_AQUA xml :
      public ::acme::department
   {
   public:


      ::pointer<entities>          m_pentities;
      ::pointer<disp_option>       m_poptionDefault;
      ::pointer<parse_info>        m_pparseinfoDefault;
      ::pointer<string_to_string>  m_pentitiesHashDefault;
      


      xml();
      virtual ~xml();

      virtual void init1();

      virtual void init();

      //virtual ::pointer<::xml::document>create_document(); 


      string special_chars(const scoped_string & str);

      // get XML from the property considering it a node
      string from(const property* pprop, ::xml::disp_option* opt /*= &optDefault*/);
    

      // get XML from the property considering it XML attributes part of a node
      string from(const property& prop, ::xml::disp_option* opt /*= &optDefault*/);


   };


} // namespace xml



