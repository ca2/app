// Created by camilo on 2024-09-13 00:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "window.h"


namespace innate_ui
{


   class CLASS_DECL_APEX still :
      virtual public ::innate_ui::window
   {
   public:

      int m_iLayoutWidth = 0;
      int m_iLayoutHeight = 0;
      double m_dFontSizeEm = 1.0;
      int m_iFontWeight = 400;



      still();
      ~still() override;


      virtual void create_icon_still(window * pwindowParent);

      //void _create_window(window * pwindowParent) override;
      //virtual void create_child(window * pwindowParent);

      virtual void set(::simple_dialog_box_line * psimpledialogboxline);
      virtual void set_font_size(double dSizeEm);
      virtual void set_font_weight(int iWeight);
      virtual int layout_width();
      virtual int layout_height();
      virtual void layout();
      //virtual void set_text(const ::scoped_string & scopedstr);

      //virtual void fit();


   };


} // namespace innate_ui



