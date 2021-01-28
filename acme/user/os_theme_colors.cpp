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

      if(themecolors.m_colorBack.color32 == themecolors.m_colorFore.color32)
      {

         return false;

      }

      if(themecolors.m_colorFore.color32 == themecolors.m_colorFace.color32)
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


   string os_get_user_theme()
   {

      string strTheme;

      auto pnode = Node;

      if(pnode)
      {

         strTheme = pnode->os_get_user_theme();

      }

      return strTheme;

   }


} // namespace user


namespace os
{


   string get_wallpaper(::index iScreen)
   {

      string strWallpaper;

      auto pnode = Node;

      if(pnode)
      {

         strWallpaper = pnode->get_wallpaper(iScreen);

      }

      return strWallpaper;

   }


} // namespace os


os_theme_colors * new_os_theme_colors()
{

   return new os_theme_colors;

}


void del_os_theme_colors(os_theme_colors * pthemecolors)
{

   delete pthemecolors;

}



