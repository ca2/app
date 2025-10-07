// Created by camilo on 2025-07-30 16:05 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{

   class debug_scope
   {
   public:


      ::gpu::context* m_pgpucontext;
      bool m_bStarted;
      ::string m_strDebugHappening;

      debug_scope(::gpu::context* pgpucontext, const ::scoped_string& scopedstrDebugHappening, bool bStart = true) :
         m_pgpucontext(pgpucontext),
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
            m_pgpucontext->start_debug_happening(m_strDebugHappening);

         }

      }

      void end()
      {
         if (m_bStarted)
         {
            m_bStarted = false;
            m_pgpucontext->end_debug_happening();
         }

      }

   };



} // namespace gpu