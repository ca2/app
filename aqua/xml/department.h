#pragma once


namespace xml
{


   class CLASS_DECL_AQUA department :
      public ::apex::department
   {
   public:


      __pointer(entities)           m_pentities;
      __pointer(disp_option)        m_poptionDefault;
      __pointer(parse_info)         m_pparseinfoDefault;
      __pointer(string_to_string)   m_pentitiesHashDefault;
      


      department();
      virtual ~department();

      virtual ::e_status init1();

      virtual ::e_status init();



      string special_chars(const char * psz);


   };


} // namespace bas


