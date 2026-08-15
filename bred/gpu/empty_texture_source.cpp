// Created by camilo on 2025-12-14 06:31 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "empty_texture_source.h"
#include "bred/gpu/context.h"


namespace gpu
{


   empty_texture_source::empty_texture_source() {}


   empty_texture_source::~empty_texture_source() {}

   ::pointer<::gpu::texture_site> empty_texture_source::create_empty_texture()
   {

      auto ptextureEmpty = m_pgpucontext->create_empty_texture();

      return ptextureEmpty;
   }


   ::gpu::texture_site *empty_texture_source::empty_texture()
   {

      if (!m_ptextureEmpty)
      {

         m_ptextureEmpty = create_empty_texture();
      }

      return m_ptextureEmpty;
   }


} // namespace gpu
 


