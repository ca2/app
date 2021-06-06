#include "framework.h"
#include "text_box.h"
#include "font_list.h"


namespace write_text
{


   text_box::text_box()
   {

      m_bInit = false;
      m_bOk = false;

   }


   text_box::~text_box()
   {

   }


   void text_box::update(font_list * plist, int iBox, string strText)
   {

      plist->__construct(m_pimage);

      if (!m_pimage)
      {

         return;

      }

      m_pimage->create(m_size);

      auto uBackgroundColor = plist->m_uaBackgroundColor[iBox];

      m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_pimage->g()->fill_rectangle(::rectangle_i32(m_size), uBackgroundColor);

      m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

      m_pimage->g()->set(m_pfont);

      auto uForegroundColor = plist->m_uaForegroundColor[iBox];

      m_pimage->g()->set_text_color(uForegroundColor);

      m_pimage->g()->text_out(plist->m_rectMargin.left, plist->m_rectMargin.top, strText);

      m_bOk = true;

   }


} // namespace write_text



