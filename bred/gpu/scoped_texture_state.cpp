// Created by camilo on 2026-09-08 16:44 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#include "platform.h"
#include "command_buffer.h"
#include "scoped_texture_state.h"
#include "texture.h"


namespace gpu
{

   scoped_texture_state::scoped_texture_state(::gpu::command_buffer * pgpucommandbuffer, ::gpu::texture * pgputexture, ::gpu::enum_texture_state egputexturestate) :
         m_pgpucommandbuffer(pgpucommandbuffer),
         m_pgputexture(pgputexture),
         m_egputexturestate(pgputexture->m_egputexturestate)

      {

         m_pgputexture->set_state(m_pgpucommandbuffer, egputexturestate);

      }


   scoped_texture_state::~scoped_texture_state()
      {

         m_pgputexture->set_state(m_pgpucommandbuffer, m_egputexturestate);

      }


} // namespace gpu



