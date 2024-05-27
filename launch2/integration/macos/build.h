//
//  build_helper.hpp
//  integration_console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 17:55
//
#pragma once


#include "../build.h"
#include "acme/primitive/collection/string_map.h"


namespace console_integration
{


   namespace macos
   {
   

      class build :
      virtual public ::console_integration::build
      {
      public:
         

         string_map < string_map < ::file::path > >      m_mappath;
         
         ::string       m_strArch;
         ::string       m_strTargetting;
         ::string       m_strTarget;
         ::string       m_strHost;


         build();
         ~build() override;
         
         
         void initialize(::particle * pparticle) override;
         
         void initialize_macos_build(
                              const ::scoped_string & scopedstrPlatform);

         void _001MakeInitialize(
                              const ::scoped_string & scopedstrArch,
                              const ::scoped_string & scopedstrTargetting,
                              const ::scoped_string & scopedstrTarget,
                              const ::scoped_string & scopedstrHost);

         void lipo(const ::scoped_string & scopedstrLibraryName = {});
         
         virtual void remap_dependencies(const ::scoped_string & scopedstrLibraryName);
         virtual void remap_dependency(const ::scoped_string & scopedstrLibraryName,
                               const ::scoped_string & scopedstrLibraryDependency);
         
         ::file::path library_source_path(const ::scoped_string & scopedstrLibraryName);
         
         virtual ::file::path calculate_prefix_path(const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration);
         
         
         void _001MakeConfigure(bool bAutogen, const ::scoped_string & scopedstrExtra);
         
         
         void _001MakeInstall(const ::scoped_string & scopedstrLibraryModifier);

         
      };


   } // namespace macos


} // namespace console_integration


