// Created by camilo on 2022-04-25 21:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "object.h"


namespace gpu
{


   object::object()
   {

      m_bPrepared = false;

   }


   object::~object()
   {


   }


   void object::load(const ::file::path & path)
   {

   }


   void object::prepare(::gpu::approach * papproach)
   {

      if (m_bPrepared)
      {

         return;

      }

      _prepare(papproach);

      m_bPrepared = true;

   }


   void object::_prepare(::gpu::approach * papproach)
   {

   }


   void object::draw()
   {


   }


   void object::set_texture_uniform(::gpu::uniform uniformTexture)
   {

   }


} // namespace draw3d






