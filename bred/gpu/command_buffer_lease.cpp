// Created by camilo on 2026-09-01 01:16 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "command_buffer_lease.h"
#include "command_buffer.h"
#include "context.h"
#include "render_target.h"
#include "renderer.h"


namespace gpu
{


   command_buffer_lease::command_buffer_lease(::pointer<::gpu::command_buffer> pgpucommandbuffer) :
      m_pgpucommandbuffer(::transfer(pgpucommandbuffer))
   {

      if (m_pgpucommandbuffer)
      {
         if (m_pgpucommandbuffer->m_pgpucommandbufferlease)
            throw ::exception(error_wrong_state, "command buffer already has an active lease");

         m_pgpucommandbuffer->m_pgpucommandbufferlease = this;
      }

   }


   command_buffer_lease::command_buffer_lease(command_buffer_lease && commandbufferlease) :
      m_pgpucommandbuffer(::transfer(commandbufferlease.m_pgpucommandbuffer))
   {

      if (m_pgpucommandbuffer)
         m_pgpucommandbuffer->m_pgpucommandbufferlease = this;

   }
   
   command_buffer_lease::~command_buffer_lease() noexcept
   {

      cancel();

   }


   void command_buffer_lease::commit()
   {

      auto pgpucommandbuffer = ::transfer(m_pgpucommandbuffer);

      if (!pgpucommandbuffer)
      {

         throw ::exception(error_wrong_state, "command buffer lease is no longer pending");

      }

      // Clear before submission, including when submission throws.
      pgpucommandbuffer->m_pgpucommandbufferlease = nullptr;

      pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->_endSingleTimeCommands(pgpucommandbuffer);

   }


   void command_buffer_lease::cancel() noexcept
   {

      if (m_pgpucommandbuffer)
         m_pgpucommandbuffer->m_pgpucommandbufferlease = nullptr;

      m_pgpucommandbuffer.release();

   }



} // namespace gpu
