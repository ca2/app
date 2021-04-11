#pragma once


namespace xml
{


   class CLASS_DECL_AQUA xml :
      public ::acme::department
   {
   public:


      __pointer(entities)           m_pentities;
      __pointer(disp_option)        m_poptionDefault;
      __pointer(parse_info)         m_pparseinfoDefault;
      __pointer(string_to_string)   m_pentitiesHashDefault;
      


      xml();
      virtual ~xml();

      virtual ::e_status init1();

      virtual ::e_status init();

      virtual __pointer(::xml::document) create_document(); 


      string special_chars(const char * psz);

      // get XML from the property considering it a node
      string from(const property* pprop, ::xml::disp_option* opt /*= &optDefault*/);
    

      // get XML from the property considering it XML attributes part of a node
      string from(const property& prop, ::xml::disp_option* opt /*= &optDefault*/);


   };


} // namespace xml



