//
// Created by camilo on 2025-08-21 23:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "renderable.h"


namespace graphics3d
{


   renderable::renderable()
   {


   }


   renderable::~renderable()
   {


   }


   ::gpu::enum_renderable_type renderable::renderable_type()
   {

      return m_erenderabletype;

   }


   // void renderable::set_emodel(::gpu::enum_model emodel)
   // {
   //
   //    m_emodel = emodel;
   //
   // }


   ::gpu::enum_renderable_usage renderable::renderable_usage()
   {

      return m_erenderableusage;

   }


   // void renderable::set_model_usage(::gpu::enum_model_usage emodelusage)
   // {
   //
   //    m_emodelusage = emodelusage;
   //
   // }


   ::gpu::texture *renderable::get_target_texture() 
   {
   
      return nullptr;
   
   }


   void renderable::bind2(::gpu::command_buffer *pcommandbuffer)
   {


   }


   void renderable::draw2(::gpu::command_buffer *pcommandbuffer)
   {
   }


   void renderable::draw_model(::gpu::command_buffer *pcommandbuffer) 
   {
      
      bind2(pcommandbuffer);

      draw2(pcommandbuffer);
   
   }


   void renderable::unbind(::gpu::command_buffer *pcommandbuffer)
   {
   }



} // graphics3d
