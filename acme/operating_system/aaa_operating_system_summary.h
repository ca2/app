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

class operating_system_summary :
virtual public ::particle
{
public:

   ::string m_strDistro;
   ::string m_strDistroFamily;
   ::string m_strDistroBranch;
   ::string m_strDistroRelease;
   ::string m_strDesktopEnvironment;
   ::string m_strSlashedOperatingSystem;
   ::string m_strUnderscoreOperatingSystem;


   ::string m_strSudoInstall;
   ::string m_strStandardPackageFileExtension;
   ::string m_strPackagePlatform;


   ::string m_strTerminal;


   distro__release_and_desktop_environment();
   ~distro__release_and_desktop_environment() override;


   ::string summary() const;


   void initialize(::particle *pparticle) override;


};
