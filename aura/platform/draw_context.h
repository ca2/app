#pragma once



//#include "acme/prototype/prototype/pointer.h"
//#include "aura/graphics/draw2d/graphics_pointer.h"
#include "aura/platform/simple_chain.h"


namespace draw2d
{

   class graphics;


} // namespace draw2d





namespace aura
{

   class CLASS_DECL_AURA draw_context :
      public ::aura::simple_chain < draw_context >
   {
   public:

      //::draw2d::graphics_pointer    m_pgraphics;
      //::i32_rectangle               m_rectangleX;
      //::i32_rectangle               m_rectangleWindow;
      bool                          m_bListItemHover;
      bool                          m_bListSubItemHover;
      bool                          m_bListItemSelected;
      bool                          m_bFocus;
      draw_context *                m_pdrawcontextNext;


      draw_context();


      virtual bool is_control_selected();
      virtual bool is_control_hover();


      virtual ::draw2d::graphics *draw2d_graphics();


      virtual void _001OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::user::interaction* puserinteraction);


   };





} // namespace aura
