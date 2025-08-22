//
// Created by camilo on 2025-08-21 19:53 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace graphics3d
{


   class renderable :
      virtual public ::particle
   {

   public:


      virtual void bind(::gpu::command_buffer *pcommandbuffer);


      virtual void draw(::gpu::command_buffer *pcommandbuffer);


      virtual void unbind(::gpu::command_buffer *pcommandbuffer);


   };


} // graphics3d
