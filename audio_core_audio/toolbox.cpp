//
//  audio_core_audio_toolbox.cpp
//  audio_core_audio
//
//  Created by Camilo Sasuke Tsumanuma on 11/10/13.
//  Copyright (c) 2013 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"


namespace multimedia
{


   namespace audio_core_audio
   {


      toolbox::toolbox()
      {

         xxf_zero(m_dataformat);

         m_Queue           = nullptr;
         m_runloop         = nullptr;
         m_CurrentPacket   = 0;


      }


      toolbox::~toolbox()
      {

      }


      void toolbox::allocate_buffer_data(::wave::buffer::item * pbuffer, memsize len, memsize uiAlign)
      {
         
         sync_lock sl(mutex());

         AudioQueueBufferRef buffer = nullptr;
         
         OSStatus osstatus = AudioQueueAllocateBuffer(m_Queue, (UInt32) len, &buffer);

         if(osstatus != 0)
         {
            
            return;
            
         }

         if(buffer == nullptr)
         {
            
            return;
            
         }

         m_Buffers.add(buffer);

         pbuffer->m_pData = buffer->mAudioData;

      }


      void toolbox::free_buffer_data(::wave::buffer::item * pbuffer)
      {
         
//         sync_lock sl(mutex());
//
//         for(int i = 0; i < m_Buffers.get_count(); i++)
//         {
//
//            if(m_Buffers[i]->mAudioData == pbuffer->m_pData)
//            {
//
//               AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);
//
//               m_Buffers.remove_at(i);
//
//               break;
//
//            }
//
//         }

      }


      void toolbox::free_buffers()
      {

         sync_lock sl(mutex());
         
         for(int i = 0; i < m_Buffers.get_count(); i++)
         {

            AudioQueueFreeBuffer(m_Queue, m_Buffers[i]);

         }

         m_Buffers.remove_all();

      }


      AudioStreamBasicDescription * toolbox::wave_format()
      {

         return &m_dataformat;

      }


      AudioQueueBufferRef toolbox::audio_buffer(index iBuffer)
      {

         return m_Buffers[iBuffer];

      }


      ::estatus toolbox::init_thread()
      {

         m_runloop = CFRunLoopGetCurrent();

         if(m_runloop != nullptr)
         {

            CFRetain(m_runloop);

         }

         m_runmode = kCFRunLoopDefaultMode;

         if(m_runmode != nullptr)
         {

            CFRetain(m_runmode);

         }

         return true;

      }


      void toolbox::term_thread()
      {

         if(m_runmode != nullptr)
         {
            
            CFRelease(m_runmode);
            
            m_runmode = nullptr;
            
         }

         if(m_runloop != nullptr)
         {
            
            CFRelease(m_runloop);
            
            m_runloop = nullptr;
            
         }

      }


   } // namespace multimedia


} // namespace multimedia



