//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSørensen
//
#include "framework.h"


namespace user
{


   os_theme_colors * g_pthemecolors;


   ::user::os_theme_colors * os_get_theme_colors()
   {

      return g_pthemecolors;

   }


   bool os_theme_colors::is_ok() const
   {

      return m_colorBack != m_colorFore && m_colorFore != m_colorFace;

   }


   void os_set_theme_colors(os_theme_colors * pthemecolors)
   {

      g_pthemecolors = pthemecolors;

   }


   void os_term_theme_colors()
   {

      ::acme::del(g_pthemecolors);

   }


} // namespace user



