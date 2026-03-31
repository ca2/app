// Created by camilo on 2024-09-13 00:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "still.h"
#include "acme/user/simple/dialog_box_line.h"


namespace innate_ui
{


   still::still()
   {
   }


   still::~still()
   {

   }

   void still::create_icon_still(window * pwindowParent)
   {


   }


   void still::set(::simple_dialog_box_line * psimpledialogboxline)
   {

      set_text(psimpledialogboxline->m_str);

      set_font_size(psimpledialogboxline->get_font_size_em());

      set_font_weight(psimpledialogboxline->get_font_weight());

      layout();

   }


   void still::set_font_size(double dSizeEm)
   {

      m_dFontSizeEm = dSizeEm;


   }


   void still::set_font_weight(int iWeight)
   {

      m_iFontWeight = iWeight;
   }


   int still::layout_width()
   {

      return m_iLayoutWidth;

   }


   int still::layout_height()
   {

      return m_iLayoutHeight;

   }

   void still::layout()
   {


   }

} // namespace innate_ui

