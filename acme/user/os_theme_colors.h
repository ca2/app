//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSørensen
//
#pragma once


#include "acme/graphics/draw2d/color32.h"


struct os_theme_colors
{


   COLOR32     m_colorBack;
   COLOR32     m_colorFace;
   COLOR32     m_colorFore;

   COLOR32     m_colorFaceHover;
   COLOR32     m_colorFacePress;
   COLOR32     m_colorButton;
   COLOR32     m_colorButtonHover;
   COLOR32     m_colorButtonPress;
   COLOR32     m_colorBorder;
   COLOR32     m_colorBorderHover;
   COLOR32     m_colorBorderHover1;
   COLOR32     m_colorBorderHover2;
   COLOR32     m_colorBorderHover3;
   COLOR32     m_colorBorderPress;


};


os_theme_colors * new_os_theme_colors();
void del_os_theme_colors(os_theme_colors * pthemecolors);



