//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSørensen
//
#include "framework.h"


namespace user
{


   ::os_theme_colors * g_pthemecolors;


   ::os_theme_colors * os_get_theme_colors()
   {

      return g_pthemecolors;

   }


   bool is_ok(const os_theme_colors & themecolors)
   {

      if(themecolors.m_colorBack == themecolors.m_colorFore)
      {

         return false;

      }

      if(themecolors.m_colorFore == themecolors.m_colorFace)
      {

         return false;

      }

      return true;

   }


   void os_set_theme_colors(os_theme_colors * pthemecolors)
   {

      g_pthemecolors = pthemecolors;

   }


   void os_term_theme_colors()
   {

      if(g_pthemecolors)
      {

         del_os_theme_colors(g_pthemecolors);

         g_pthemecolors = nullptr;

      }

   }



} // namespace user


os_theme_colors * new_os_theme_colors()
{

   return new os_theme_colors;

}


void del_os_theme_colors(os_theme_colors * pthemecolors)
{

   delete pthemecolors;

}



