//
//  options.hpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-09 09:06
//  Copyright © 2024 Camilo Sasuke Tsumanuma. All rights reserved. <3ThomasBorregaardSorensen!!
//
#pragma once


namespace filesystem
{


   class CLASS_DECL_ACME file_system_options :
      virtual public particle
   {
   public:
      
      
      bool                 m_bOperatingSystemRootOnes;
      bool                 m_bImage;
      bool                 m_bDocument;
      bool                 m_bMusic;
      bool                 m_bDownload;
      bool                 m_b_iCloud;
      bool                 m_b_iCloudContainer;
      bool                 m_bOneDrive;
      bool                 m_bDropbox;
      bool                 m_bVideo;
      bool                 m_bDesktop;
      
      ::string             m_str_iCloudContainerIdentifier;
      ::string             m_str_iCloudContainerName;

      
      ::string_array       m_straUTType;

      ::string_array       m_straFileSystemExtension;

      
      file_system_options();
      ~file_system_options() override;
      
      
   };


} // namespace filesystem



