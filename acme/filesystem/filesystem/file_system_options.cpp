//
//  options.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-09 09:06
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved. <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "file_system_options.h"


namespace filesystem
{


   file_system_options::file_system_options()
   {
      
      if constexpr(IS_DESKTOP_SYSTEM())
      {
         
         m_bOperatingSystemRootOnes = true;
         m_bImage = true;
         m_bDocument = true;
         m_bMusic = true;
         m_bDownload = true;
         m_b_iCloud = false;
         m_b_iCloudContainer = false;
         m_bOneDrive = true;
         m_bDropbox = true;
         m_bVideo = true;
         m_bDesktop = true;

      }
      else
      {
         
         m_bOperatingSystemRootOnes = false;
         m_bImage = false;
         m_bDocument = false;
         m_bMusic = false;
         m_bDownload = false;
         m_b_iCloud = false;
         m_b_iCloudContainer = false;
         m_bOneDrive = false;
         m_bDropbox = false;
         m_bVideo = false;
         m_bDesktop = false;

      }
      
   }


   file_system_options::~file_system_options()
   {
      
   }


} // namespace filesystem



