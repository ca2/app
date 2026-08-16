// Created by camilo on 2025-12-14 06:31 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context_object.h"


namespace gpu
{


   class CLASS_DECL_BRED empty_texture_source :
      virtual public ::gpu::context_object
   {
   public:


      ::pointer<::gpu::texture_site> m_ptextureEmpty;


      empty_texture_source();
      ~empty_texture_source() override;


      virtual ::pointer < ::gpu::texture_site > create_empty_texture();
      virtual ::gpu::texture_site *empty_texture();



   };


} // namespace gpu



