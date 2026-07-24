// Created by camilo on 2026-07 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


#include "bred/gpu/context_pointer.h"


namespace gpu
{


   class device;
   class context;


   class CLASS_DECL_BRED context_lease : 
      public ::gpu::context_pointer
   {
   public:


      using BASE_POINTER = ::gpu::context_pointer;

      ::pointer<::gpu::device> m_pdevice;
      //::pointer<::gpu::context> m_pcontext;
      bool m_bDamaged = false;
      bool m_bOwned = false;

      using context_pointer::context_pointer;

      //context_lease();
      //context_lease(::gpu::device * pdevice, ::gpu::context * pcontext, bool bOwned);
      context_lease(::gpu::device * pgpudevice, ::gpu::context *pcontext, bool bOwned);
      context_lease(const context_lease &) = delete;
      context_lease(context_lease && lease);
      ~context_lease() noexcept;


      void mark_damaged();
      void close();
      void close_noexcept() noexcept;

      
      context_lease &operator=(const context_lease &) = delete;
      context_lease &operator=(context_lease &&lease) noexcept;


   };


} // namespace gpu
