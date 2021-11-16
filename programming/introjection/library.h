// From compiler.h by camilo on 2021-11-15 15:43 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace introjection
{


   class CLASS_DECL_APP_PROGRAMMING library :
      virtual public ::object
   {
   public:


      __pointer(::acme::library)                m_plibrary;
      ::file::path                              m_pathScript;
      ::string_stream                           m_memfileError;
      string                                    m_strError;
      filetime_set                              m_filetimeset;


      library();
      virtual ~library();

      virtual ::e_status initialize(::object* pobject) override;


   };


} // namespace introjection



