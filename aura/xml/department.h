#pragma once


namespace xml
{


   class CLASS_DECL_AURA department :
      public ::aura::department
   {
   public:


      __pointer(entities)           m_pentities;
      __pointer(disp_option)        m_poptionDefault;
      __pointer(parse_info)         m_pparseinfoDefault;
      __pointer(string_to_string)   m_pentitiesHashDefault;
      


      department();
      virtual ~department();

      virtual ::estatus init1();

      virtual ::estatus init();



      string special_chars(const char * psz);


   };


} // namespace bas


