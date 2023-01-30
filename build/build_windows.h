//
// Created by camilo on 12/12/21 05:05 PM <3ThomasBorregaardSørensen!!
//
#pragma once


namespace windows
{


   class CLASS_DECL_APP_BUILD build :
      virtual public ::app_build::build
   {
   public:


      string         m_strPlatform;
      string         m_strConfiguration;
      ::file::path   m_pathDevEnv;
      ::file::path   m_pathSolution;


      build();
      ~build() override;


      void prepare_build() override;

      void do_build() override;


   };



} // namespace windows




