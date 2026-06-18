// Created by camilo on 2026-06-09 07:17 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "framework.h"
//#include "graphics.h"
//#include "graphics_context.h"
//
//
//namespace draw2d
//{
//
//
//   graphics_context::graphics_context()
//   {
//      
//      m_bNewFrame = true; 
//   
//   }
//
//
//   graphics_context::~graphics_context()
//   {
//
//      m_pgraphics.release();
//
//      if (m_pgraphicscontextinterface)
//      {
//
//         m_pgraphicscontextinterface->_context_unlock();
//
//      }
//
//   }
//
//
//   void graphics_context::start_frame()
//   {
//
//      auto pgraphics = draw2d_graphics();
//
//      if (::is_set(pgraphics))
//      {
//
//         pgraphics->start_frame(this);
//
//      }
//
//   }
//
//
//   void graphics_context::end_frame()
//   {
//
//      auto pgraphics = draw2d_graphics();
//
//      if (::is_set(pgraphics))
//      {
//
//         pgraphics->end_frame(this);
//
//      }
//
//   }
//
//
//   void graphics_context::insert_graphics_and_context(::draw2d::graphics_context_interface *pinterface)
//   {
//
//      m_pgraphicscontextinterface = pinterface;
//
//      m_pgraphicscontextinterface->_context_lock();
//
//   }
//
//
//   ::e_graphics graphics_context::egraphics() 
//   {
//         
//      return m_pgraphics->m_egraphics; 
//      
//   }
//
//
//   void graphics_context::set_egraphics(::e_graphics egraphics)
//   {
//
//      m_pgraphics->m_egraphics = egraphics;
//
//   }
//
//
//   bool graphics_context::is_new_frame()
//   {
//
//      return m_bNewFrame;
//
//   }
//   
//   
//   void graphics_context::set_is_new_frame(bool bIsNewFrame)
//   {
//
//      m_bNewFrame = bIsNewFrame;
//
//   }
//
//
//   //void graphics_context::start_frame() 
//   //{
//   //
//   //   m_pgraphics->start_frame(pgraphicscontext);
//   //
//   //}
//
//
//   //void graphics_context::end_frame() 
//   //{
//   //
//   //   m_pgraphics->end_frame(pgraphicscontext);
//   //
//   //}
//
//
//   //void graphics_context::start_layer()
//   //{
//   //   
//   //   m_pgraphics->start_layer(pgraphicscontext);
//   //   
//   //}
//
//
//   //void graphics_context::end_layer()
//   //{
//   //
//   //   m_pgraphics->end_layer(pgraphicscontext);
//   //
//   //}
//
//
//   ::draw2d::graphics * graphics_context::draw2d_graphics()
//   {
//
//      return m_pgraphics;
//
//   }
//
//
//} // namespace draw2d
