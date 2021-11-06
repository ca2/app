//
// Created by camilo on 28/01/2021. 03:01 --<33ThomasBorregaardSoerensen!! My ONLY GOD!!
//
#pragma once


#include "os_theme_colors.h"


namespace user
{

   bool is_ok(const os_theme_colors & themecolors);

   CLASS_DECL_ACME void os_term_theme_colors();

   ::os_theme_colors * os_get_theme_colors();

   void os_set_theme_colors(::os_theme_colors * pthemecolors);

   //CLASS_DECL_ACME string _os_get_user_theme();

   //CLASS_DECL_ACME void _os_process_user_theme(string strTheme);

   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);

   CLASS_DECL_ACME string os_get_user_theme();


} // namespace user



