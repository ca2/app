#include "framework.h"


namespace draw2d
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

      auto colorbg = plist->m_dwaBg[iBox];

      m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);

      m_pimage->g()->fill_rect(::rect(m_size), colorbg);

      m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);

      m_pimage->g()->set(m_pfont);

      auto colorfg = plist->m_dwaFg[iBox];

      m_pimage->g()->set_text_color(colorfg);

      m_pimage->g()->text_out(plist->m_rectMargin.left, plist->m_rectMargin.top, strText);

      m_bOk = true;

   }


} // namespace draw2d



