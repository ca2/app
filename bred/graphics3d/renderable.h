//
// Created by camilo on 2025-08-21 19:53 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "bred/gpu/renderable.h"


namespace graphics3d
{


   class CLASS_DECL_BRED renderable :
      virtual public ::particle,
      public ::gpu::renderable_t
   {

   public:


      //::gpu::enum_model             m_emodel;
      //::gpu::enum_model_usage       m_emodelusage;


      renderable();
      ~renderable();


      virtual ::gpu::enum_renderable_type renderable_type();
      //virtual void set_emodel(::gpu::enum_model emodel);
      virtual ::gpu::enum_renderable_usage renderable_usage();
      //virtual void set_model_usage(::gpu::enum_model_usage emodelusage);


      virtual void bind(::gpu::command_buffer *pcommandbuffer);


      virtual void draw(::gpu::command_buffer *pcommandbuffer);


      virtual void unbind(::gpu::command_buffer *pcommandbuffer);


   };


} // graphics3d
