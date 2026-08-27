#include "platform.h"
#include "graphics.h"
#include "graphics_lease.h"
#include "graphics_layer_scope.h"
#include "draw2d.h"
#include "aura/graphics/image/image.h"


namespace draw2d
{


   graphics_lease::graphics_lease() : m_bOwned(false)
   {
      m_bLeaseOn = false;
   }


   //graphics_lease::graphics_lease(
   //   ::draw2d::draw2d * pdraw2d,
   //   ::draw2d::graphics * pdraw2dgraphics,
   //   ::image::image * pimage,
   //   bool bOwned) :
   //   m_pdraw2d(pdraw2d),
   //   m_pgraphics(pdraw2dgraphics),
   //   m_pimage(pimage),
   //   m_bOwned(bOwned)
   //{

   //}

   graphics_lease::graphics_lease(::draw2d::draw2d * pdraw2d,::draw2d::graphics *pdraw2dgraphics, 
                                  ::image::image * pimage, bool bOwned) :
       graphics_pointer(pdraw2dgraphics), m_pdraw2d(pdraw2d), m_pimage(pimage), m_bOwned(bOwned),
      m_bLeaseOn(true)
   {

      if (m_pimage)
      {

         if (m_pimage->m_pgraphicslease)
         {

            throw ::exception(error_wrong_state);

         }

         m_pimage->m_pgraphicslease = this;

      }
   }

   //   graphics_lease::graphics_lease(::draw2d::graphics *pdraw2dgraphics, ::image::image * pimage, 
   //      bool bOwned) : m_pgraphics(pdraw2dgraphics), m_pimage(pimage), m_bOwned(bOwned)
   //{
   //}

   graphics_lease::graphics_lease(graphics_lease && lease) :
      m_pdraw2d(::transfer(lease.m_pdraw2d)),
      graphics_pointer(::transfer(lease)),
      m_pimage(::transfer(lease.m_pimage)),
      m_bDamaged(lease.m_bDamaged),
      m_bOwned(lease.m_bOwned),
      m_bLeaseOn(true)
   {

      ASSERT(!lease.m_bLayerScopeActive);

      lease.m_bLeaseOn = false;

      lease.m_bDamaged = false;

      lease.m_bOwned = false;

      if (m_pimage && m_pimage->m_pgraphicslease == &lease)
      {

         m_pimage->m_pgraphicslease = this;

      }

   }


   graphics_lease::~graphics_lease() noexcept
   {

      close_noexcept();

   }


   graphics_lease & graphics_lease::operator=(graphics_lease && lease)
   {

      if (this != &lease)
      {

         ASSERT(!m_bLayerScopeActive);
         ASSERT(!lease.m_bLayerScopeActive);
         close_noexcept();
         lease.m_bLeaseOn = false;
         m_pdraw2d = ::transfer(lease.m_pdraw2d);
         BASE_POINTER::operator=(::transfer(lease));
         m_pimage = ::transfer(lease.m_pimage);
         m_bDamaged = lease.m_bDamaged;
         m_bOwned = lease.m_bOwned;
         m_bLeaseOn = true;

         lease.m_bDamaged = false;

         lease.m_bOwned = false;

         if (m_pimage && m_pimage->m_pgraphicslease == &lease)
         {

            m_pimage->m_pgraphicslease = this;

         }

      }

      return *this;

   }


   //graphics_lease::operator bool() const
   //{

   //   return get() != nullptr;

   //}


   //::draw2d::graphics * graphics_lease::get() const
   //{

   //   return m_pgraphics.m_p;

   //}


   //::draw2d::graphics * graphics_lease::operator->() const
   //{

   //   return get();

   //}


   ::draw2d::graphics_layer_scope graphics_lease::begin_layer_scope()
   {

      return ::draw2d::graphics_layer_scope(*this);

   }


   void graphics_lease::_begin_layer_scope()
   {

      if (this->is_null() || m_bLayerScopeActive)
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

      if (!m_bLeaseOn)
      {

         return;

      }

      if (m_bLayerScopeActive)
      {

         m_bDamaged = true;

         throw ::exception(
            error_wrong_state,
            "cannot close a graphics lease with an active layer scope");

      }

      if (m_pimage)
      {

         if (m_pimage->m_pgraphicslease != this)
         {

            errorf("[draw2d.graphics_pool] failed to return graphics lease");

         }

         m_pimage->m_pgraphicslease = nullptr;

      }

      auto pdraw2d = ::transfer(m_pdraw2d);
      auto pdraw2dgraphics = ::transfer((BASE_POINTER &&) *this);
      auto pimage = ::transfer(m_pimage);
      auto bDamaged = m_bDamaged;
      bool bOwned = m_bOwned
         || (pimage && pimage->m_pgraphicsOwned == pdraw2dgraphics)
         || (pdraw2dgraphics && pdraw2dgraphics->m_pimage && pdraw2dgraphics->m_pimage->m_pgraphicsOwned == pdraw2dgraphics);

      m_bDamaged = false;

      m_bOwned = false;

      //if (bOwned)
      //{

      //   if (pimage && pdraw2dgraphics)
      //   {

      //      pimage->return_memory_graphics(pdraw2dgraphics);

      //   }

      //}
      //else
      //{
         
         if (pdraw2dgraphics && bOwned)
         {

            try
            {

               pdraw2dgraphics->on_release_memory_graphics();

            }
            catch (...)
            {

               if (pimage)
               {

                  pimage->end_destination_graphics_lease();

               }

               throw;

            }

            if (pimage)
            {

               pimage->end_destination_graphics_lease();

            }

         }
         else if (pdraw2d && pdraw2dgraphics)
         {

            pdraw2d->return_memory_graphics(
               ::transfer(pdraw2dgraphics),
               ::transfer(pimage),
               bDamaged);

         }
         else if (pimage)
         {

            pimage->end_destination_graphics_lease();

         }


      //}

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
