// Created by camilo on 2023-07-14 14:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "form_handler.h"
#include "aura/graphics/write_text/font.h"


namespace user
{


   form_handler::form_handler()
   {


   }


   form_handler::~form_handler()
   {


   }


   void form_handler::design_form(::user::interaction * puserinteraction)
   {


   }


   void form_handler::on_after_create_form(const ::atom &atom, ::user::interaction *puserinteractionParent)
   {


   }


   ::write_text::font_pointer form_handler::get_title1_font()
   {

      if (!m_pfontTitle1)
      {

         øconstruct(m_pfontTitle1);

         m_pfontTitle1->create_font(e_font_sans_ui, 36.0_pt, e_font_weight_bold);

      }

      return m_pfontTitle1;

   }


   ::write_text::font_pointer form_handler::get_title2_font()
   {

      if (!m_pfontTitle2)
      {

         øconstruct(m_pfontTitle2);

         m_pfontTitle2->create_font(e_font_sans_ui, 24.0_pt, e_font_weight_bold);

      }

      return m_pfontTitle2;

   }


} // namespace user




