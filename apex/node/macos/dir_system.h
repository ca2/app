//
//  dir_system.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//
#pragma once


namespace macos
{


   class CLASS_DECL_APEX dir_system :
      virtual public ::dir_system
   {
   public:


      ::file::path            m_strTimeFolder;
      ::file::path            m_strNetSeedFolder;

      ::file::path            m_strCommonAppData;
      ::file::path            m_strAppData;
      ::file::path            m_strPrograms;
      ::file::path            m_strCommonPrograms;

      
      dir_system();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status init_system() override;
      

   };


} // namespace macos








