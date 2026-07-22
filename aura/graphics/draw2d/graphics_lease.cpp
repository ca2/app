#include "framework.h"
#include "graphics.h"
#include "graphics_lease.h"
#include "graphics_layer_scope.h"
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

      ASSERT(!lease.m_bLayerScopeActive);

      lease.m_bDamaged = false;

   }


   graphics_lease & graphics_lease::operator=(graphics_lease && lease) noexcept
   {

      if (this != &lease)
      {

         ASSERT(!m_bLayerScopeActive);
         ASSERT(!lease.m_bLayerScopeActive);
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


   ::draw2d::graphics_layer_scope graphics_lease::begin_layer_scope()
   {

      return ::draw2d::graphics_layer_scope(*this);

   }


   void graphics_lease::_begin_layer_scope()
   {

      if (!m_pgraphics || m_bLayerScopeActive)
      {

         throw ::exception(
            error_wrong_state,
            "graphics lease cannot begin another layer scope");

      }

      m_bLayerScopeActive = true;

   }


   void graphics_lease::_end_layer_scope()
   {

      m_bLayerScopeActive = false;

   }


   bool graphics_lease::has_active_layer_scope() const
   {

      return m_bLayerScopeActive;

   }


   void graphics_lease::mark_damaged()
   {

      m_bDamaged = true;

   }


   void graphics_lease::close()
   {

      if (m_bLayerScopeActive)
      {

         m_bDamaged = true;

         throw ::exception(
            error_wrong_state,
            "cannot close a graphics lease with an active layer scope");

      }

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
