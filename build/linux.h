//
// Created by camilo on 12/12/21 05:05 PM <3ThomasBorregaardSorensen!!
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


      ::e_status prepare_build() override;

      ::e_status do_build() override;


   };



} // namespace app_build




