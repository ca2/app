// Created by camilo on 2021-11-15 15:39 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace programming
{


   class CLASS_DECL_APP_PROGRAMMING compiler :
      virtual public ::object
   {
   protected:

      using ::object::initialize;

   public:


      ::file::path                              m_pathProjectDir;
      string                                    m_strDynamicSourceConfiguration;
      ::file::path                              m_strDynamicSourceStage;
      ::file::path                              m_strDynamicSourceStageFolder;


      string                                    m_strLibPlatform;


      string                                    m_strPlatform;
      string                                    m_strStagePlatform;


#ifdef WINDOWS
      string                                    m_strVs;
      string                                    m_strVsTools;
      string                                    m_strVCVersion;
#endif

      string                                    m_strSdk1;


      string                                    m_strPlat1;
      string                                    m_strPlat2;
      ::file::path                              m_strTime;

      string                                    m_strEnv;


      compiler();
      ~compiler() override;


      virtual void initialize_programming_compiler(::object* pobject);

      virtual void prepare_compile_and_link_environment();

      virtual void prepare1(const ::string& lpcszSource, const ::string& lpcszDest);



   };


} // namespace programming



