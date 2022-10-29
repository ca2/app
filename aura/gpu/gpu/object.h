// Created by camilo on 2022-04-25 20:42 <3ThomasBorregaardS�rensen!!
#pragma once


#include "acme/primitive/primitive/element.h"


namespace gpu
{


   class CLASS_DECL_AURA object :
      virtual public ::element
   {
   public:


      bool                       m_bPrepared;


      object();
      ~object() override;


      virtual void load(const ::file::path & path);


      virtual void prepare(::gpu::approach * papproach);


      virtual void _prepare(::gpu::approach * papproach);


      virtual void draw();

      
      virtual void set_texture_uniform(::gpu::uniform uniformTexture);


   };


} // namespace gpu



