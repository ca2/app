/*
    src/theme.cpp -- Storage class for basic theme-related properties

    The text box widget was contributed by Christian Schueller.

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The widget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Theme.h"
#include "Icons.h"


char * read_resource_string(const ::scoped_string & scopedstr);
void read_resource(void *& p, size_t & s, const ::scoped_string & scopedstr);

namespace nanoui
{


Theme::Theme()
{
   m_iStandardFontSize = 16;
   m_iButtonFontSize = 20;
   m_iTextBoxFontSize = 20;

   
   m_fIconScale = 0.60f;

   m_iWindowCorderRadius = 2;
   m_iWindowHeaderHeight = 30;
   m_iWindowDropShadowSize = 10;
   m_iButtonCornerRadius = 2;
   m_fTabBorderWidth = 0.75f;
   m_iTabInnerMargin = 5;
   m_iTabMinimumButtonWidth = 20;
   m_iTabMaximumButtonWidth = 160;
   m_iTabControlWidth = 20;
   m_iHorizontalPaddingTabButton = 10;
   m_iVerticalPaddingTabButton = 2;

   m_colorDropShadow = ::color::color(0, 128);
   m_colorTransparent = ::color::color(0, 0);
   m_colorBorderDark = ::color::color(29, 255);
   m_colorBorderLight = ::color::color(92, 255);
   m_colorBorderMedium = ::color::color(35, 255);
   m_colorText = ::color::color(255, 160);
   m_colorDisableText = ::color::color(255, 80);
   m_colorTextShadow = ::color::color(0, 160);
   m_colorIcon = m_colorText;

   m_colorButtonGradientTopFocused = ::color::color(64, 255);
   m_colorButtonGradientBottomFocused = ::color::color(48, 255);
   m_colorButtonGradientUnfocused = ::color::color(74, 255);
   m_colorButtonGradientBottomUnfocused = ::color::color(58, 255);
   m_colorButtonGradientTopPushed = ::color::color(41, 255);
   m_colorButtonGradientBottomPushed = ::color::color(29, 255);

   /* Window-related */
   m_colorWindowFillUnfocused = ::color::color(43, 230);
   m_colorWindowFillFocused = ::color::color(45, 230);
   m_colorWindowTitleUnfocused = ::color::color(220, 160);
   m_colorWindowTitleFocused = ::color::color(255, 190);

   m_colorWindowHeaderGradientTop = m_colorButtonGradientUnfocused;
   m_colorWindowHeaderGradientBottom = m_colorButtonGradientBottomUnfocused;
   m_colorWindowHeaderSeparationTop = m_colorBorderLight;
   m_colorWindowHeaderSeparationBottom = m_colorBorderDark;

   m_colorWindowPopup = ::color::color(50, 255);
   m_window_popup_transparent = ::color::color(50, 0);

   m_efontawesomeCheckBox            = e_font_awesome_check;
   m_efontawesomeMessageInformation  = e_font_awesome_info_circle;
   m_efontawesomeMessageQuestion     = e_font_awesome_question_circle;
   m_efontawesomeMessageWarning      = e_font_awesome_exclamation_triangle;
   m_efontawesomeMessageAltButton    = e_font_awesome_times_circle;
   m_efontawesomeMessagePrimaryButton= e_font_awesome_check;
   m_efontawesomePopupChevronRight   = e_font_awesome_chevron_right;
   m_efontawesomePopupChevronLeft    = e_font_awesome_chevron_left;
   m_efontawesomeTextBoxUp           = e_font_awesome_chevron_up;
   m_efontawesomeTextBoxDown         = e_font_awesome_chevron_down;
   //{

   //   void * p = nullptr;
   //   size_t s = 0;

   //   read_resource(p, s, "roboto-regular.ttf");

   //   m_font_sans_regular = ::nano2d::CreateFontMem(ctx, "sans", (uint8_t *)p,
   //      s, 0);

   //}
   //{

   //   void * p = nullptr;
   //   size_t s = 0;

   //   read_resource(p, s, "roboto-bold.ttf");
   //   m_font_sans_bold = ::nano2d::CreateFontMem(ctx, "sans-bold", (uint8_t *)p,
   //      s, 0);

   //}
   //{

   //   void * p = nullptr;
   //   size_t s = 0;

   //   read_resource(p, s, "fontawesome-solid.ttf");

   //   m_font_icons = ::nano2d::CreateFontMem(ctx, "icons", (uint8_t *)p,
   //      s, 0);
   //}
   //{

   //   void * p = nullptr;
   //   size_t s = 0;

   //   read_resource(p, s, "inconsolata-regular.ttf");

   //   m_font_mono_regular = ::nano2d::CreateFontMem(ctx, "mono", (uint8_t *)p,
   //      s, 0);

   //}

   //if (m_font_sans_regular == -1 || m_font_sans_bold == -1 ||
   //   m_font_icons == -1 || m_font_mono_regular == -1)
   //   throw std::runtime_error("Could not load fonts!");
}




} // namespace nanoui




//
//
//char * read_resource_string(const ::scoped_string & scopedstr)
//{
//
//   /* declare a file pointer */
//   FILE * infile;
//   char * buffer;
//   long    numbytes;
//
//   ::string str(psz);
//
//   char sz[2048];
//   GetModuleFileNameA(
//      NULL,
//      sz,
//      sizeof(sz));
//
//   auto pFolder = strrchr(sz, '\\');
//
//   if (pFolder)
//   {
//      *pFolder = '\0';
//
//   }
//
//   str = ::string(sz) + "\\resources\\" + str;
//
//   /* open an existing file for reading */
//   infile = fopen(str.c_str(), "r");
//
//   /* quit if the file does not exist */
//   if (infile == NULL)
//      return 0;
//
//   /* Get the number of bytes */
//   fseek(infile, 0L, SEEK_END);
//   numbytes = ftell(infile);
//
//   /* reset the file position indicator to
//   the beginning of the file */
//   fseek(infile, 0L, SEEK_SET);
//
//   /* grab sufficient memory for the
//   buffer to hold the text */
//   buffer = (char *)calloc(numbytes + 1, sizeof(char));
//
//   /* memory error */
//   if (buffer == NULL)
//      return 0;
//
//   /* copy all the text into the buffer */
//   fread(buffer, sizeof(char), numbytes, infile);
//   fclose(infile);
//
//   /* confirm we have read the file by
//   outputing it to the console */
//   printf("The file called test.dat contains this text\n\n%s", buffer);
//
//   /* free the memory we used for the buffer */
//   //free(buffer);
//   buffer[numbytes] = '\0';
//   return buffer;
//
//
//}
//
//
//void read_resource(void *& p, size_t & s, const ::scoped_string & scopedstr)
//{
//
//
//   /* declare a file pointer */
//   FILE * infile;
//   char * buffer;
//   long    numbytes;
//
//   ::string str(psz);
//
//   char sz[2048];
//   GetModuleFileNameA(
//      NULL,
//      sz,
//      sizeof(sz));
//
//   auto pFolder = strrchr(sz, '\\');
//
//   if (pFolder)
//   {
//      *pFolder = '\0';
//
//   }
//
//   str = ::string(sz) + "\\resources\\" + str;
//
//   /* open an existing file for reading */
//   infile = fopen(str.c_str(), "r");
//
//   /* quit if the file does not exist */
//   if (infile == NULL)
//      throw "error 1";
//
//   /* Get the number of bytes */
//   fseek(infile, 0L, SEEK_END);
//   numbytes = ftell(infile);
//
//   /* reset the file position indicator to
//   the beginning of the file */
//   fseek(infile, 0L, SEEK_SET);
//
//   /* grab sufficient memory for the
//   buffer to hold the text */
//   buffer = (char *)calloc(numbytes, sizeof(char));
//
//   /* memory error */
//   if (buffer == NULL)
//      throw "error 2";
//
//   /* copy all the text into the buffer */
//   fread(buffer, sizeof(char), numbytes, infile);
//   fclose(infile);
//
//   /* confirm we have read the file by
//   outputing it to the console */
//   printf("The file called test.dat contains this text\n\n%s", buffer);
//
//   p = buffer;
//   s = numbytes;
//
//}
