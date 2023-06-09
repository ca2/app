//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSorensen
//
#pragma once


#include "acme/graphics/draw2d/color.h"


struct os_theme_colors
{


   ::color::color    m_colorBack;
   ::color::color    m_colorFace;
   ::color::color    m_colorFore;

   ::color::color    m_colorFaceHover;
   ::color::color    m_colorFacePress;
   ::color::color    m_colorButton;
   ::color::color    m_colorButtonHover;
   ::color::color    m_colorButtonPress;
   ::color::color    m_colorBorder;
   ::color::color    m_colorBorderHover;
   ::color::color    m_colorBorderHover1;
   ::color::color    m_colorBorderHover2;
   ::color::color    m_colorBorderHover3;
   ::color::color    m_colorBorderPress;


};


os_theme_colors * new_os_theme_colors();
void del_os_theme_colors(os_theme_colors * pthemecolors);



