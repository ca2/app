// Created by camilo on 2024-09-13 00:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX still :
      virtual public ::innate_ui::window
   {
   public:

      ::i32 m_iLayoutWidth = 0;
      ::i32 m_iLayoutHeight = 0;



      still();
      ~still() override;


      virtual void create_icon_still(window * pwindowParent);

      //void _create_window(window * pwindowParent) override;
      //virtual void create_child(window * pwindowParent);

      virtual void set(::simple_dialog_box_line * psimpledialogboxline);
      virtual void set_font_size(::f64 dSizeEm);
      virtual void set_font_weight(::i32 iWeight);
      virtual ::i32 layout_width();
      virtual ::i32 layout_height();
      virtual void layout();
      //virtual void set_text(const ::scoped_string & scopedstr);

      //virtual void fit();


   };


} // namespace innate_ui



