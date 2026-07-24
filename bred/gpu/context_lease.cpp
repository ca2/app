#include "framework.h"
#include "context.h"
#include "context_lease.h"
#include "device.h"


namespace gpu
{


   /*context_lease::context_lease()
   {

   }*/


   context_lease::context_lease(
      ::gpu::device * pdevice,
      ::gpu::context * pcontext,
      bool bOwned) :
       BASE_POINTER(pcontext),
      m_pdevice(pdevice), m_bOwned(bOwned)
   {

      if (!m_bOwned)
      {

         pcontext->m_bInNonOwnedLease = true;

      }

   }


   context_lease::context_lease(context_lease && lease) :
       BASE_POINTER(::transfer(lease)),
      m_bDamaged(lease.m_bDamaged), m_bOwned(lease.m_bOwned)
   {

      lease.m_bDamaged = false;

   }


   context_lease & context_lease::operator=(context_lease && lease) noexcept
   {

      if (this != &lease)
      {

         close_noexcept();

         m_pdevice = ::transfer(lease.m_pdevice);
         BASE_POINTER::operator= (::transfer(lease));
         m_bDamaged = lease.m_bDamaged;

         lease.m_bDamaged = false;

      }

      return *this;

   }


   context_lease::~context_lease() noexcept
   {

      close_noexcept();

   }


   

   void context_lease::mark_damaged()
   {

      m_bDamaged = true;

   }


   void context_lease::close()
   {

      auto pdevice = ::transfer(m_pdevice);
      auto pcontext = ::transfer((BASE_POINTER && )*this);
      auto bDamaged = m_bDamaged;
      auto bOwned = m_bOwned;

      m_bDamaged = false;
      m_bOwned = false;

      if (pdevice && pcontext && !bOwned)
      {

         pcontext->m_bInNonOwnedLease = false;

         pdevice->return_gpu_context(::transfer(pcontext), bDamaged);

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
            "[gpu.context_pool] failed to return gpu context: %s",
            exception.get_message().c_str());

      }
      catch (...)
      {

         errorf("[gpu.context_pool] failed to return gpu context");

      }

   }


} // namespace gpu
