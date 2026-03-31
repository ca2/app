// Created by camilo on 2026-03-31 06:30 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "dialog_box_line.h"


simple_dialog_box_line::simple_dialog_box_line()
{

   m_esimpledialogstyle = e_simple_dialog_style_normal;
   m_bSpacingLine = false;

}


simple_dialog_box_line::~simple_dialog_box_line()
{


}


void simple_dialog_box_line::initialize(::particle * pparticle)
{

   ::particle::initialize(pparticle);

}


double simple_dialog_box_line::get_font_size_em() const
{

   switch (m_esimpledialogstyle)
   {
      case e_simple_dialog_style_heading1:
         return 2.0;
      case e_simple_dialog_style_heading1_remark:
         return 0.8;
      default:
         return 1.0;
   }

}


int simple_dialog_box_line::get_font_weight() const
{

   switch (m_esimpledialogstyle)
   {
      case e_simple_dialog_style_heading1:
         return 900;
      case e_simple_dialog_style_heading1_remark:
         return 200;
      default:
         return 400;
   }

}


int simple_dialog_box_line::get_byte_text_color_strength() const
{

   switch (m_esimpledialogstyle)
   {
      case e_simple_dialog_style_heading1:
         return 208;
      case e_simple_dialog_style_heading1_remark:
         return 160;
      default:
         return 160;
   }

}


void simple_dialog_box_line::_001Parse(const ::scoped_string & scopedstr)
{

   m_str = scopedstr;

   if (m_str.begins_eat("#"))
   {

      m_esimpledialogstyle = e_simple_dialog_style_heading1;

   }
   else if (m_str.begins_eat("-#"))
   {

      m_esimpledialogstyle = e_simple_dialog_style_heading1_remark;

   }
   else if (m_str.begins_eat("<br />"))
   {

      m_esimpledialogstyle = e_simple_dialog_style_normal;
      //m_dFontSizeEm = 1.0;
      //m_iFontWeight = 400;
      m_bSpacingLine = true;

   }

}


bool simple_dialog_box_line::is_spacing_line() const
{

   return m_bSpacingLine;

}


string simple_dialog_box_line::get_line_height_text()
{

   return "THOMÁsg";

}

