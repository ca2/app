//
// Created by camilo on 12/12/21 05:05 PM <3ThomasBorregaardSorensen!!
//
#pragma once


namespace app_core_build
{



   class CLASS_DECL_APP_CORE_BUILD linux_build :
      virtual public build
   {
   public:


      string      m_strDistro;
      string      m_strDesktopEnvironment;
      string      m_strVersion;


      linux_build();
      ~linux_build() override;


      ::e_status prepare_build() override;

      ::e_status do_build() override;


   };



} // namespace app_core_build




