//
// Created by camilo on 12/12/21 05:05 PM <3ThomasBorregaardSørensen!!
//
#pragma once


namespace linux
{



   class CLASS_DECL_APP_BUILD build :
      virtual public ::app_build::build
   {
   public:


      string      m_strDistro;
      string      m_strDesktopEnvironment;
      string      m_strVersion;


      build();
      ~build() override;


      void prepare_build() override;

      void do_build() override;


   };



} // namespace app_build




