// Created by camilo on 2025-07-30 16:05 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/command_buffer.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/renderer.h"


namespace gpu
{

   class debug_scope
   {
   public:


      ::gpu::command_buffer* m_pgpucommandbuffer;
      bool m_bStarted;
      ::string m_strDebugHappening;

      debug_scope(::gpu::command_buffer *pgpucommandbuffer, const ::scoped_string &scopedstrDebugHappening,
                  bool bStart = true) :
          m_pgpucommandbuffer(pgpucommandbuffer),
         m_bStarted(false),
         m_strDebugHappening(scopedstrDebugHappening)
      {
         
         if (bStart)
         {

            start();
         }

      }
      ~debug_scope()
      {

         end();

      }

      void start()
      {
         if (!m_bStarted)
         {


            m_bStarted = true;
            m_pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->start_debug_happening(
               m_pgpucommandbuffer, m_strDebugHappening);

         }

      }

      void end()
      {
         if (m_bStarted)
         {
            m_bStarted = false;
            m_pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->end_debug_happening(
               m_pgpucommandbuffer);
         }

      }

   };



} // namespace gpu