//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSørensen
//
#pragma once


namespace user
{


   struct CLASS_DECL_ACME os_theme_colors
   {

      ::color     m_colorBack;
      ::color     m_colorFace;
      ::color     m_colorFore;

      ::color     m_colorFaceHover;
      ::color     m_colorFacePress;
      ::color     m_colorButton;
      ::color     m_colorButtonHover;
      ::color     m_colorButtonPress;
      ::color     m_colorBorder;
      ::color     m_colorBorderHover;
      ::color     m_colorBorderHover1;
      ::color     m_colorBorderHover2;
      ::color     m_colorBorderHover3;
      ::color     m_colorBorderPress;


      bool is_ok() const;


   };


   CLASS_DECL_ACME void os_term_theme_colors();

   os_theme_colors * os_get_theme_colors();

   void os_set_theme_colors(os_theme_colors * pthemecolors);

   CLASS_DECL_ACME string _os_get_user_theme();

   CLASS_DECL_ACME void _os_process_user_theme(string strTheme);

   CLASS_DECL_ACME void _os_process_user_theme_color(string strTheme);


} // namespace user



