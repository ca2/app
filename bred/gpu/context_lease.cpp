#include "framework.h"
#include "context.h"
#include "context_lease.h"
#include "device.h"


namespace gpu
{


   context_lease::context_lease()
   {

   }


   context_lease::context_lease(
      ::gpu::device * pdevice,
      ::gpu::context * pcontext) :
      m_pdevice(pdevice),
      m_pcontext(pcontext)
   {

   }


   context_lease::context_lease(context_lease && lease) noexcept :
      m_pdevice(::transfer(lease.m_pdevice)),
      m_pcontext(::transfer(lease.m_pcontext)),
      m_bDamaged(lease.m_bDamaged)
   {

      lease.m_bDamaged = false;

   }


   context_lease & context_lease::operator=(context_lease && lease) noexcept
   {

      if (this != &lease)
      {

         close_noexcept();

         m_pdevice = ::transfer(lease.m_pdevice);
         m_pcontext = ::transfer(lease.m_pcontext);
         m_bDamaged = lease.m_bDamaged;

         lease.m_bDamaged = false;

      }

      return *this;

   }


   context_lease::~context_lease() noexcept
   {

      close_noexcept();

   }


   context_lease::operator bool() const
   {

      return get() != nullptr;

   }


   ::gpu::context * context_lease::get() const
   {

      return m_pcontext.m_p;

   }


   ::gpu::context * context_lease::operator->() const
   {

      return get();

   }


   void context_lease::mark_damaged()
   {

      m_bDamaged = true;

   }


   void context_lease::close()
   {

      auto pdevice = ::transfer(m_pdevice);
      auto pcontext = ::transfer(m_pcontext);
      auto bDamaged = m_bDamaged;

      m_bDamaged = false;

      if (pdevice && pcontext)
      {

         pdevice->return_draw2d_context(::transfer(pcontext), bDamaged);

      }

   }


   void context_lease::close_noexcept() noexcept
   {

      try
      {

         close();

      }
      catch (const ::exception & exception)
      {

         errorf(
            "[gpu.context_pool] failed to return draw2d context: %s",
            exception.get_message().c_str());

      }
      catch (...)
      {

         errorf("[gpu.context_pool] failed to return draw2d context");

      }

   }


} // namespace gpu
