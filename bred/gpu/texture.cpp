// Created by camilo on 2025-06-12 21:07 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "texture.h"


namespace gpu
{



   texture::texture()
   {

   }


   texture::~texture()
   {

   }


   void texture::initialize_gpu_texture(const ::int_size& size)
   {

      m_size = size;

   }


} // namespace gpu



