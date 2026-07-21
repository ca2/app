#pragma once


namespace gpu
{


   class device;
   class context;


   class CLASS_DECL_BRED context_lease
   {
   public:


      ::pointer<::gpu::device> m_pdevice;
      ::pointer<::gpu::context> m_pcontext;
      bool m_bDamaged = false;


      context_lease();
      context_lease(::gpu::device * pdevice, ::gpu::context * pcontext);
      context_lease(const context_lease &) = delete;
      context_lease & operator=(const context_lease &) = delete;
      context_lease(context_lease && lease) noexcept;
      context_lease & operator=(context_lease && lease) noexcept;
      ~context_lease() noexcept;


      explicit operator bool() const;
      ::gpu::context * get() const;
      ::gpu::context * operator->() const;
      void mark_damaged();
      void close();
      void close_noexcept() noexcept;


   };


} // namespace gpu
