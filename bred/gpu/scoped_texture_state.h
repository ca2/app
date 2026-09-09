// Created by camilo on 2026-09-08 16:41 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


namespace gpu
{

   class CLASS_DECL_BRED scoped_texture_state
   {
   public:


      ::pointer < ::gpu::command_buffer > m_pgpucommandbuffer;
      ::pointer < ::gpu::texture > m_pgputexture;
      ::gpu::enum_texture_state m_egputexturestate;


      scoped_texture_state(::gpu::command_buffer * pgpucommandbuffer, ::gpu::texture * pgputexture, ::gpu::enum_texture_state egputexturestate);

      ~scoped_texture_state();


   };


} // namespace gpu



