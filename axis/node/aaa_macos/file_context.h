//
//  file_context.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 28/02/20.
//

#pragma once


namespace macos
{


   class CLASS_DECL_AXIS file_context :
      virtual public ::file_context
   {
   public:

      
      __reference(dir_system)      m_pdirsystem;
      __reference(file_system)      m_pfilesystem;


      file_context();
      virtual ~file_context();
      
      
      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual ::payload length(const ::file::path & path) override;

      virtual ::e_status update_module_path() override;

      virtual file_result get_file(const ::payload & varFile, const ::file::e_open & eopen) override;


   };


} // namespace macos



