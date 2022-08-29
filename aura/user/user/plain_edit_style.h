// From control_style.h (just a while ago style_control.h) by camilo
// on 2022-08-27 02:25 <3ThomasBorregaardSorensen!! (ThomasLikesNumber5!!)
#pragma once


#include "control_style.h"


namespace user
{


   class plain_edit_style :
      virtual public control_style
   {
   public:


      ::draw2d::pen_pointer              m_ppenCaret;
      ::draw2d::brush_pointer            m_pbrushText;
      ::draw2d::brush_pointer            m_pbrushTextCr;
      ::draw2d::brush_pointer            m_pbrushTextSel;
      ::draw2d::brush_pointer            m_pbrushTextEmpty;


      plain_edit_style();
      ~plain_edit_style() override;


      virtual void on_update(::draw2d::graphics_pointer & pgraphics, style * ppstyle, ::user::interaction * pinteraction) override;


   };


} // namespace user



