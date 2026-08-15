// Created by camilo on 2026-08-11 16:20 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "texture_site.h"


namespace gpu
{



   texture_site::texture_site()
   {

   }

   
   texture_site::~texture_site()
   {


   }


   ::gpu::texture * texture_site::gpu_texture() const
   {

      return m_pgputextureSite;

   }


   bool texture_site::_is_ok() const
   {

      return m_pgputextureSite.is_set();

   }


} // namespace gpu
