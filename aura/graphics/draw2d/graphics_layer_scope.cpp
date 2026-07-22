#include "framework.h"
#include "graphics_layer_scope.h"
#include "graphics_lease.h"
#include "graphics.h"


namespace draw2d
{


   graphics_layer_scope::graphics_layer_scope()
   {

   }


   graphics_layer_scope::graphics_layer_scope(
      ::draw2d::graphics_lease & graphicslease) :
      m_pgraphicslease(&graphicslease),
      m_pgraphics(graphicslease.get())
   {

      graphicslease._begin_layer_scope();

      try
      {

         m_pgraphics->on_begin_layer_scope();
         m_bOpen = true;

      }
      catch (...)
      {

         graphicslease._end_layer_scope();
         m_pgraphicslease = nullptr;
         m_pgraphics.release();

         throw;

      }

   }


   graphics_layer_scope::graphics_layer_scope(
      graphics_layer_scope && scope) noexcept :
      m_pgraphicslease(scope.m_pgraphicslease),
      m_pgraphics(::transfer(scope.m_pgraphics)),
      m_bOpen(scope.m_bOpen)
   {

      scope.m_pgraphicslease = nullptr;
      scope.m_bOpen = false;

   }


   graphics_layer_scope & graphics_layer_scope::operator=(
      graphics_layer_scope && scope) noexcept
   {

      if (this != &scope)
      {

         close_noexcept();
         m_pgraphicslease = scope.m_pgraphicslease;
         m_pgraphics = ::transfer(scope.m_pgraphics);
         m_bOpen = scope.m_bOpen;

         scope.m_pgraphicslease = nullptr;
         scope.m_bOpen = false;

      }

      return *this;

   }


   graphics_layer_scope::~graphics_layer_scope() noexcept
   {

      close_noexcept();

   }


   graphics_layer_scope::operator bool() const
   {

      return m_bOpen && m_pgraphics.is_set();

   }


   void graphics_layer_scope::close()
   {

      if (!m_bOpen)
      {

         return;

      }

      auto pgraphicslease = m_pgraphicslease;
      auto pgraphics = ::transfer(m_pgraphics);

      m_pgraphicslease = nullptr;
      m_bOpen = false;

      try
      {

         pgraphics->on_end_layer_scope();
         pgraphicslease->_end_layer_scope();

      }
      catch (...)
      {

         pgraphicslease->_end_layer_scope();
         pgraphicslease->mark_damaged();

         throw;

      }

   }


   void graphics_layer_scope::close_noexcept() noexcept
   {

      try
      {

         close();

      }
      catch (const ::exception & exception)
      {

         errorf(
            "[draw2d.graphics_layer_scope] failed to end layer: %s",
            exception.get_message().c_str());

      }
      catch (...)
      {

         errorf("[draw2d.graphics_layer_scope] failed to end layer");

      }

   }


} // namespace draw2d
