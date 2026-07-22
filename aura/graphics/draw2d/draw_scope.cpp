#include "framework.h"
#include "graphics.h"
#include "draw_scope.h"
#include "graphics_lease.h"


namespace draw2d
{


   draw_scope::draw_scope() {}


   draw_scope::draw_scope(::draw2d::graphics_lease &graphicslease) :
       m_pgraphicslease(&graphicslease)
   {

      try
      {

         m_pgraphicslease->get()->begin_draw();
         m_bOpen = true;
      }
      catch (...)
      {

         m_pgraphicslease = nullptr;
         m_bOpen = false;
         throw;
      }
   }


   //draw_scope::draw_scope(draw_scope &&scope) noexcept :
   //    m_pgraphicslease(scope.m_pgraphicslease), m_pgraphics(::transfer(scope.m_pgraphics)), m_bOpen(scope.m_bOpen)
   //{

   //   scope.m_pgraphicslease = nullptr;
   //   scope.m_bOpen = false;
   //}


   //draw_scope &draw_scope::operator=(draw_scope &&scope) noexcept
   //{

   //   if (this != &scope)
   //   {

   //      close_noexcept();
   //      m_pgraphicslease = scope.m_pgraphicslease;
   //      m_pgraphics = ::transfer(scope.m_pgraphics);
   //      m_bOpen = scope.m_bOpen;

   //      scope.m_pgraphicslease = nullptr;
   //      scope.m_bOpen = false;
   //   }

   //   return *this;
   //}


   draw_scope::~draw_scope() noexcept { close_noexcept(); }


   draw_scope::operator bool() const { return m_bOpen && ::is_set(m_pgraphicslease); }


   void draw_scope::close()
   {

      if (!m_bOpen)
      {

         return;
      }

      auto pgraphicslease = m_pgraphicslease;

      m_pgraphicslease = nullptr;
      m_bOpen = false;

      try
      {

         pgraphicslease->get()->end_draw();

      }
      catch (...)
      {

         throw;
      }
   }


   void draw_scope::close_noexcept() noexcept
   {

      try
      {

         close();
      }
      catch (const ::exception &exception)
      {

         errorf("[draw2d.draw_scope] failed to end layer: %s", exception.get_message().c_str());
      }
      catch (...)
      {

         errorf("[draw2d.draw_scope] failed to end layer");
      }
   }


} // namespace draw2d
