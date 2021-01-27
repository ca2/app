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
