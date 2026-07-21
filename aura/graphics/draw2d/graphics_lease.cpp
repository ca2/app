#include "framework.h"
#include "graphics.h"
#include "graphics_lease.h"
#include "draw2d.h"
#include "aura/graphics/image/image.h"


namespace draw2d
{


   graphics_lease::graphics_lease()
   {

   }


   graphics_lease::graphics_lease(
      ::draw2d::draw2d * pdraw2d,
      ::draw2d::graphics * pgraphics,
      ::image::image * pimage) :
      m_pdraw2d(pdraw2d),
      m_pgraphics(pgraphics),
      m_pimage(pimage)
   {

   }


   graphics_lease::graphics_lease(graphics_lease && lease) noexcept :
      m_pdraw2d(::transfer(lease.m_pdraw2d)),
      m_pgraphics(::transfer(lease.m_pgraphics)),
      m_pimage(::transfer(lease.m_pimage)),
      m_bDamaged(lease.m_bDamaged)
   {

      lease.m_bDamaged = false;

   }


   graphics_lease & graphics_lease::operator=(graphics_lease && lease) noexcept
   {

      if (this != &lease)
      {

         close_noexcept();

         m_pdraw2d = ::transfer(lease.m_pdraw2d);
         m_pgraphics = ::transfer(lease.m_pgraphics);
         m_pimage = ::transfer(lease.m_pimage);
         m_bDamaged = lease.m_bDamaged;

         lease.m_bDamaged = false;

      }

      return *this;

   }


   graphics_lease::~graphics_lease() noexcept
   {

      close_noexcept();

   }


   graphics_lease::operator bool() const
   {

      return get() != nullptr;

   }


   ::draw2d::graphics * graphics_lease::get() const
   {

      return m_pgraphics.m_p;

   }


   ::draw2d::graphics * graphics_lease::operator->() const
   {

      return get();

   }


   void graphics_lease::mark_damaged()
   {

      m_bDamaged = true;

   }


   void graphics_lease::close()
   {

      auto pdraw2d = ::transfer(m_pdraw2d);
      auto pgraphics = ::transfer(m_pgraphics);
      auto pimage = ::transfer(m_pimage);
      auto bDamaged = m_bDamaged;

      m_bDamaged = false;

      if (pdraw2d && pgraphics)
      {

         pdraw2d->return_memory_graphics(
            ::transfer(pgraphics),
            ::transfer(pimage),
            bDamaged);

      }

   }


   void graphics_lease::close_noexcept() noexcept
   {

      try
      {

         close();

      }
      catch (const ::exception & exception)
      {

         errorf(
            "[draw2d.graphics_pool] failed to return memory graphics: %s",
            exception.get_message().c_str());

      }
      catch (...)
      {

         errorf("[draw2d.graphics_pool] failed to return memory graphics");

      }

   }


} // namespace draw2d
