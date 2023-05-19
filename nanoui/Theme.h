/*
    The text box widget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
/**
 * \file nanoui/theme.h
 *
 * \brief Storage class for basic theme-related properties.
 */

#pragma once


enum enum_font_awesome;

#include "acme/primitive/geometry2d/vector.h"
#include "Object.h"
//#include "nano2d/color.h"


namespace nanoui
{


/**
 * \class Theme theme.h nanoui/theme.h
 *
 * \brief Storage class for basic theme-related properties.
 */
   class CLASS_DECL_NANOUI Theme : public Object {
   public:

      /* Fonts */
      /// The standard font face (default: ``"sans"`` from ``resources/roboto_regular.ttf``).
      //int m_font_sans_regular;
      /// The bold font face (default: ``"sans-bold"`` from ``resources/roboto_regular.ttf``).
      //int m_font_sans_bold;
      /// The icon font face (default: ``"icons"`` from ``resources/entypo.ttf``).
      //int m_font_icons;
      /// The monospace font face (default: ``"mono"`` from ``resources/inconsolata_regular.ttf``).
      //int m_font_mono_regular;
      /**
       * The amount of scaling that is applied to each icon to fit the size of
       * NanoGUI widgets.  The default value is ``0.77f``, setting to e.g. higher
       * than ``1.0f`` is generally discouraged.
       */
      float m_fIconScale;

      /* Spacing-related parameters */
      /// The font size for all widgets other than buttons and textboxes (default: `` 16``).
      int m_iStandardFontSize;
      /// The font size for buttons (default: ``20``).
      int m_iButtonFontSize;
      /// The font size for text boxes (default: ``20``).
      int m_iTextBoxFontSize;
      /// Rounding radius for Window widget corners (default: ``2``).
      int m_iWindowCorderRadius;
      /// Default size of Window widget titles (default: ``30``).
      int m_iWindowHeaderHeight;
      /// Size of drop shadow rendered behind the Window widgets (default: ``10``).
      int m_iWindowDropShadowSize;
      /// Rounding radius for Button (and derived types) widgets (default: ``2``).
      int m_iButtonCornerRadius;
      /// The border width for Tab_header widgets (default: ``0.75f``).
      float m_fTabBorderWidth;
      /// The inner margin on a Tab_header widget (default: ``5``).
      int m_iTabInnerMargin;
      /// The minimum size for buttons on a Tab_header widget (default: ``20``).
      int m_iTabMinimumButtonWidth;
      /// The maximum size for buttons on a Tab_header widget (default: ``160``).
      int m_iTabMaximumButtonWidth;
      /// Used to help specify what lies "in bound" for a Tab_header widget (default: ``20``).
      int m_iTabControlWidth;
      /// The amount of horizontal padding for a Tab_header widget (default: ``10``).
      int m_iHorizontalPaddingTabButton;
      /// The amount of vertical padding for a Tab_header widget (default: ``2``).
      int m_iVerticalPaddingTabButton;

      /* Generic colors */
      /**
       * The color::color of the drop shadow drawn behind widgets
       * (default: intensity=``0``, alpha=``128``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorDropShadow;
      /**
       * The transparency color::color
       * (default: intensity=``0``, alpha=``0``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorTransparent;
      /**
       * The dark border color::color
       * (default: intensity=``29``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorBorderDark;
      /**
       * The light border color::color
       * (default: intensity=``92``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorBorderLight;
      /**
       * The medium border color::color
       * (default: intensity=``35``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorBorderMedium;
      /**
       * The text color::color
       * (default: intensity=``255``, alpha=``160``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorText;
      /**
       * The disable dtext color::color
       * (default: intensity=``255``, alpha=``80``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorDisableText;
      /**
       * The text shadow color::color
       * (default: intensity=``0``, alpha=``160``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorTextShadow;
      /// The icon color::color (default: \ref nanoui::Theme::m_colorText).
      color::color m_colorIcon;

      /* Button colors */
      /**
       * The top gradient color::color for buttons in focus
       * (default: intensity=``64``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientTopFocused;
      /**
       * The bottom gradient color::color for buttons in focus
       * (default: intensity=``48``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientBottomFocused;
      /**
       * The top gradient color::color for buttons not in focus
       * (default: intensity=``74``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientUnfocused;
      /**
       * The bottom gradient color::color for buttons not in focus
       * (default: intensity=``58``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientBottomUnfocused;
      /**
       * The top gradient color::color for buttons currently pushed
       * (default: intensity=``41``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientTopPushed;
      /**
       * The bottom gradient color::color for buttons currently pushed
       * (default: intensity=``29``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorButtonGradientBottomPushed;

      /* Window colors */
      /**
       * The fill color::color for a Window that is not in focus
       * (default: intensity=``43``, alpha=``230``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorWindowFillUnfocused;
      /**
       * The fill color::color for a Window that is in focus
       * (default: intensity=``45``, alpha=``230``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorWindowFillFocused;
      /**
       * The title color::color for a Window that is not in focus
       * (default: intensity=``220``, alpha=``160``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorWindowTitleUnfocused;
      /**
       * The title color::color for a Window that is in focus
       * (default: intensity=``255``, alpha=``190``; see \ref nanoui::color::color::color::color(int,int)).
       */
      color::color m_colorWindowTitleFocused;

      /**
       * The top gradient color::color for Window headings
       * (default: \ref nanoui::Theme::m_colorButtonGradientUnfocused).
       */
      color::color m_colorWindowHeaderGradientTop;
      /**
       * The bottom gradient color::color for Window headings
       * (default: \ref nanoui::Theme::m_colorButtonGradientBottomUnfocused).
       */
      color::color m_colorWindowHeaderGradientBottom;
      /// The Window header top separation color::color (default: \ref nanoui::Theme::m_colorBorderLight).
      color::color m_colorWindowHeaderSeparationTop;
      /// The Window header bottom separation color::color (default: \ref nanoui::Theme::m_colorBorderDark).
      color::color m_colorWindowHeaderSeparationBottom;

      /**
       * The popup window color::color
       * (default: intensity=``50``, alpha=``255``; see \ref nanoui::color::color::color::color(int,int))).
       */
      color::color m_colorWindowPopup;
      /**
       * The transparent popup window color::color
       * (default: intensity=``50``, alpha=``0``; see \ref nanoui::color::color::color::color(int,int))).
       */
      color::color m_window_popup_transparent;

      /// Icon to use for check box widgets (default: ``FA_CHECK``).
      enum_font_awesome m_efontawesomeCheckBox;
      /// Icon to use for informational message dialog widgets (default: ``FA_INFO_CIRCLE``).
      enum_font_awesome m_efontawesomeMessageInformation;
      /// Icon to use for interrogative message dialog widgets (default: ``FA_QUESTION_CIRCLE``).
      enum_font_awesome m_efontawesomeMessageQuestion;
      /// Icon to use for warning message dialog widgets (default: ``FA_EXCLAMATION_TRINAGLE``).
      enum_font_awesome m_efontawesomeMessageWarning;
      /// Icon to use on message dialog alt button (default: ``FA_CIRCLE_WITH_CROSS``).
      enum_font_awesome m_efontawesomeMessageAltButton;
      /// Icon to use on message_dialog primary button (default: ``FA_CHECK``).
      enum_font_awesome m_efontawesomeMessagePrimaryButton;
      /// Icon to use for Popup_button widgets opening to the right (default: ``FA_CHEVRON_RIGHT``).
      enum_font_awesome m_efontawesomePopupChevronRight;
      /// Icon to use for Popup_button widgets opening to the left (default: ``FA_CHEVRON_LEFT``).
      enum_font_awesome m_efontawesomePopupChevronLeft;
      /// Icon to use when a text box has an up toggle (e.g. IntBox) (default: ``FA_CHEVRON_UP``).
      enum_font_awesome m_efontawesomeTextBoxUp;
      /// Icon to use when a text box has a down toggle (e.g. IntBox) (default: ``FA_CHEVRON_DOWN``).
      enum_font_awesome m_efontawesomeTextBoxDown;
      
      Theme();
      
   protected:
      /// Default destructor does nothing; allows for inheritance.
      virtual ~Theme() { };
};



} // namespace nanoui


