// Created by camilo on 2026-11-02 06:08 <3ThomasBorregaardSorensen!! Mummi!! bilbo!!
#pragma once


#include "acme/filesystem/filesystem/listing.h"


namespace user
{


   class CLASS_DECL_BRED gpu_shader_list :
      virtual public ::particle
   {
   public:


      ::file::listing_base m_filelisting;


      gpu_shader_list();
      ~gpu_shader_list() override;


      virtual void initialize_user_gpu_shader_list(::particle * pparticleParent);


      virtual string get_next_shader_path(const ::scoped_string & scopedstrPath);


      virtual void get_shader_listing(::file::listing_base & listing);


   };


} // namespace user



