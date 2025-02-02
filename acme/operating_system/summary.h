//
// Created by camilo on 07/04/23.
// From distro__release_and_desktop_environment to operating_system_summary on 2023-04-10 18:56 by camilo <3ThomasBorregaardSorensen!!
//
#pragma once

//contains() {
//   string="$1"
//   substring="$2"
//   if test "${string#*$substring}" != "$string"
//   then
//   return 0    # $substring is in $string
//   else
//   return 1    # $substring is not in $string
//           fi
//}
//

namespace operating_system
{


   class CLASS_DECL_ACME summary :
      virtual public ::particle
   {
   public:


      ::string          m_strName;

      ::string          m_strSystemName;
      ::string          m_strSystemFamilyName;
      ::string          m_strSystemBranchName;
      ::string          m_strSystemReleaseName;

      ::string          m_strAmbientName;

      ::string          m_strSystem;
      ::string          m_strSystemFamily;
      ::string          m_strSystemBranch;
      ::string          m_strSystemRelease;

      ::string          m_strAmbient;

      ::string          m_strSystemAmbientRelease;

      int               m_iMajor;
      int               m_iMinor;
      int               m_iPatch;
      
      ::string          m_strIntegrationRelease;
      ::string          m_strStoreRelease;

      ::string          m_strSudoInstall;
      ::string          m_strStandardPackageFileExtension;
      ::string          m_strPackagePlatform;


      ::string          m_strTerminal;


      ::string          m_strShellPriorityPathPatch;

      summary();
      ~summary() override;


      ::property_array get_property_array() const;
      ::string get_summary() const;
      ::string id_payload_listing() const;
      void set_ambient();

      //
      //   void initialize(::particle *pparticle) override;
      //

   };


} // namespace operating_system



