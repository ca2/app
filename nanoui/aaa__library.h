// Created by camilo on 2022/03/18 2:00 AM <3ThomasBorregaardS�rensen!! (Thomas Like number 5)
#pragma once


////#include "aura/user/user/_component.h"
#include "aura/user/appearance/_appearance.h"
//#include "nano2d/_component.h"



//**
//* \brief Determine whether an icon ID is a texture loaded via ``::nano2d::_image_icon``.
//*
//* \rst
//* The implementation defines all ``value < 1024`` as image icons, and
//   * everything ``> = 1024`` as an Entypo icon(see :ref:`file_nanoui_entypo.h`).
//      * The value ``1024`` exists to provide a generous buffer on how many images
//      * may have been loaded by NanoVG.
//      * \endrst
//      *
//      *\param value
//      * The integral value of the icon.
//      *
//      *\return
//      *Whether or not this is an image icon.
//      * /
      inline bool ::nano2d::_is_image_icon(int value) { return value < 1024; }

/**
 * \brief Determine whether an icon ID is a font-based icon (e.g. from ``entypo.ttf``).
 *
 * \rst
 * See :func:`nanoui::::nano2d::_is_image_icon` for details.
 * \endrst
 *
 * \param value
 *     The integral value of the icon.
 *
 * \return
 *     Whether or not this is a font icon (from ``entypo.ttf``).
 */
inline bool ::nano2d_is_font_icon(int value) { return value >= 1024; }



//#include "nano2d/_nano2d.h"


//#include "_nanoui_main_frame.h"


#define __MOUSE_LEFT_BUTTON 0
#define __MOUSE_RIGHT_BUTTON 1


#include "Object.h"
#include "Widget.h"
#include "Screen.h"

#include "Layout.h"

#include "Window.h"
#include "Label.h"
#include "Button.h"

#include "Popup.h"
#include "PopupButton.h"

#include "CheckBox.h"


#include "MessageDialog.h"

#include "VScrollPanel.h"

#include "Canvas.h"

#include "ImagePanel.h"
#include "ImageImpact.h"

#include "ComboBox.h"

#include "Slider.h"


#include "TextBox.h"


#include "ProgressBar.h"

#include "TabWidget.h"

#include "ColorWheel.h"


