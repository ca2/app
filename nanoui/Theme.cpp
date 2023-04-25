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
   m_standard_font_size = 16;
   m_button_font_size = 20;
   m_text_box_font_size = 20;

   
   m_icon_scale = 0.60f;

   m_window_corner_radius = 2;
   m_window_header_height = 30;
   m_window_drop_shadow_size = 10;
   m_button_corner_radius = 2;
   m_tab_border_width = 0.75f;
   m_tab_inner_margin = 5;
   m_tab_min_button_width = 20;
   m_tab_max_button_width = 160;
   m_tab_control_width = 20;
   m_tab_button_horizontal_padding = 10;
   m_tab_button_vertical_padding = 2;

   m_drop_shadow = ::color::color(0, 128);
   m_transparent = ::color::color(0, 0);
   m_border_dark = ::color::color(29, 255);
   m_border_light = ::color::color(92, 255);
   m_border_medium = ::color::color(35, 255);
   m_text_color = ::color::color(255, 160);
   m_disabled_text_color = ::color::color(255, 80);
   m_text_color_shadow = ::color::color(0, 160);
   m_icon_color = m_text_color;

   m_button_gradient_top_focused = ::color::color(64, 255);
   m_button_gradient_bot_focused = ::color::color(48, 255);
   m_button_gradient_top_unfocused = ::color::color(74, 255);
   m_button_gradient_bot_unfocused = ::color::color(58, 255);
   m_button_gradient_top_pushed = ::color::color(41, 255);
   m_button_gradient_bot_pushed = ::color::color(29, 255);

   /* Window-related */
   m_window_fill_unfocused = ::color::color(43, 230);
   m_window_fill_focused = ::color::color(45, 230);
   m_window_title_unfocused = ::color::color(220, 160);
   m_window_title_focused = ::color::color(255, 190);

   m_window_header_gradient_top = m_button_gradient_top_unfocused;
   m_window_header_gradient_bot = m_button_gradient_bot_unfocused;
   m_window_header_sep_top = m_border_light;
   m_window_header_sep_bot = m_border_dark;

   m_window_popup = ::color::color(50, 255);
   m_window_popup_transparent = ::color::color(50, 0);

   m_check_box_icon = FA_CHECK;
   m_message_information_icon = FA_INFO_CIRCLE;
   m_message_question_icon = FA_QUESTION_CIRCLE;
   m_message_warning_icon = FA_EXCLAMATION_TRIANGLE;
   m_message_alt_button_icon = FA_TIMES_CIRCLE;
   m_message_primary_button_icon = FA_CHECK;
   m_popup_chevron_right_icon = FA_CHEVRON_RIGHT;
   m_popup_chevron_left_icon = FA_CHEVRON_LEFT;
   m_text_box_up_icon = FA_CHEVRON_UP;
   m_text_box_down_icon = FA_CHEVRON_DOWN;
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
