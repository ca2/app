//
//  context_handle.h
//  gpu_opengl
//
//  Created by camilo on 2026-01-25 18:46 <3JegElskerDigThomasBorregaardSørensen!!
//
#pragma once


#include "bred/gpu/context.h"
#include "bred/gpu/context_object.h"
#include "bred/gpu/device.h"


namespace gpu_opengl
{

   enum enum_handle
   {
      
      e_handle_none,
      e_handle_buffer,
      e_handle_fbo,
   
   };


   template < typename HANDLE_TYPE, enum_handle t_ehandle >
   class context_handle :
      virtual public ::gpu::context_object
   {
   public:
      
      static const enum_handle s_ehandle = t_ehandle;
      
      struct object
      {
         
         HANDLE_TYPE    m_handle;
         bool           m_bCreated = false;
         bool           m_bBound = false;
         
      };
      
      //GLuint m_gluVao;
      
      context_handle()
      {
      }

      ~context_handle() override
      {
      }

      ::map < void *, object > m_mapContextHandleObject;
      
      object & context_handle_object()
      {
         
        auto poperatingsystemgpucontext = m_pgpucontext->m_pgpudevice->current_operating_system_gpu_context();
        
        if(::is_null(poperatingsystemgpucontext))
        {
           
           throw ::exception(error_wrong_state);
           
        }
        
        auto & object = m_mapContextHandleObject[poperatingsystemgpucontext];
         
         return object;

      }
      
   };


} // namespace gpu_opengl



