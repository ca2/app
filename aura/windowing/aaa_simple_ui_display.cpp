// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
//#include "os/cross/windows/_windows.h"
#include "acme/id.h"
#include "_windowing.h"
//!!!#include <X11/extensions/Xinerama.h>


void acme_defer_os_init_windowing();


namespace windowing
{


   simple_ui_display::simple_ui_display(const string &strMessageParam, const string &strTitle,
                                        const ::e_message_box &emessagebox) :
      m_strTitle(strTitle),
      m_strFontName("serif"),
      m_size(100, 40),
      m_bOsUserThemeColorModified(false),
      m_bInvalidated(false)
   {

      acme_defer_os_init_windowing();

      common_construct();

      string strMessage(strMessageParam);

      strMessage.replace_ci("<br>", " \n");

      m_stra.add_lines(strMessage);

      ::u32 uType = ((::u32) emessagebox) & 7;

      switch (uType)
      {
         case e_message_box_ok:
            m_buttona.add(new_button("OK", e_dialog_result_ok));
            m_buttona.add(new_button("Cancel", e_dialog_result_cancel));
            break;
         case e_message_box_abort_retry_ignore:
            m_buttona.add(new_button("Abort", e_dialog_result_abort));
            m_buttona.add(new_button("Retry", e_dialog_result_retry));
            m_buttona.add(new_button("Ignore", e_dialog_result_ignore));
            break;
         case e_message_box_yes_no_cancel:
            m_buttona.add(new_button("Yes", e_dialog_result_yes));
            m_buttona.add(new_button("No", e_dialog_result_no));
            m_buttona.add(new_button("Cancel", e_dialog_result_cancel));
            break;
         case e_message_box_yes_no:
            m_buttona.add(new_button("Yes", e_dialog_result_yes));
            m_buttona.add(new_button("No", e_dialog_result_no));
            break;
         case e_message_box_retry_cancel:
            m_buttona.add(new_button("Retry", e_dialog_result_retry));
            m_buttona.add(new_button("Cancel", e_dialog_result_cancel));
            break;
         case e_message_box_cancel_try_continue:
            m_buttona.add(new_button("Cancel", e_dialog_result_cancel));
            m_buttona.add(new_button("Try", e_dialog_result_retry));
            m_buttona.add(new_button("Continue", e_dialog_result_continue));
            break;
         default:
            m_buttona.add(new_button("OK", e_dialog_result_ok));
            break;
      }

   }


   i64 simple_ui_display::add_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return hook::add_ref(OBJ_REF_DBG_ARGS);

   }


   i64 simple_ui_display::dec_ref(OBJ_REF_DBG_PARAMS_DEF)
   {

      return hook::dec_ref(OBJ_REF_DBG_ARGS);

   }


   i64 simple_ui_display::release(OBJ_REF_DBG_PARAMS_DEF)
   {

      return hook::release(OBJ_REF_DBG_ARGS);

   }

   void simple_ui_display::common_construct()
   {

      m_iMarginTop = 20;
      m_iMarginLeft = 20;
      m_iMarginRight = 20;
      m_iLineSpacing = 4;
      m_iButtonHSpacing = 20;
      m_iButtonHPadding = 20;
      m_iButtonVPadding = 8;
      m_iMidSpacing = 20;
      m_iMarginBottom = 20;

   }


   simple_ui_display::~ simple_ui_display()
   {


   }


   button *simple_ui_display::new_button(const char *pszLabel, enum_dialog_result edialogresult)
   {

      return nullptr;

   }


   void simple_ui_display::on_alloc_colors(display *pdisplay)
   {

//      auto pthemecolors = ::user::os_get_theme_colors();
//
//      if (pthemecolors && ::user::is_ok(*pthemecolors))
//      {
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBack), &m_colorBack);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorFace), &m_colorFace);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorFore), &m_colorFore);
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorFaceHover),
//                           &m_colorFaceHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorFacePress),
//                           &m_colorFacePress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorButton), &m_colorButton);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorButtonHover),
//                           &m_colorButtonHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorButtonPress),
//                           &m_colorButtonPress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorder), &m_colorBorder);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorderHover),
//                           &m_colorBorderHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorderHover1),
//                           &m_colorBorderHover1);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorderHover2),
//                           &m_colorBorderHover2);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorderHover3),
//                           &m_colorBorderHover3);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, _hex_color(pthemecolors->m_colorBorderPress),
//                           &m_colorBorderPress);
//
//      }
//      else auto pnode = System.node();

               if (pnode->is_app_dark_mode())
//      {
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#555555", &m_colorBack);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#888888", &m_colorFace);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorFore);
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#999999", &m_colorFaceHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#AAAAAA", &m_colorFacePress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorButton);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#e0f0ff", &m_colorButtonHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#c0e0ff", &m_colorButtonPress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorBorder);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#E0F0FF", &m_colorBorderHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B2C0CF", &m_colorBorderHover1);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#85909F", &m_colorBorderHover2);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#59606F", &m_colorBorderHover3);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#c0e0ff", &m_colorBorderPress);
//
//      }
//      else
//      {
//
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#CCCCCC", &m_colorBack);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#AAAAAA", &m_colorFace);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#222222", &m_colorFore);
//
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#A5A5A5", &m_colorFaceHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B0B0B0", &m_colorFacePress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#222222", &m_colorButton);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#2050c7", &m_colorButtonHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#2050df", &m_colorButtonPress);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#888888", &m_colorBorder);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#7090D0", &m_colorBorderHover);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#87A0CF", &m_colorBorderHover1);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#A0B0CE", &m_colorBorderHover2);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B7C0CD", &m_colorBorderHover3);
//         XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#5070df", &m_colorBorderPress);
//
//      }

   }


   void simple_ui_display::on_free_colors(display *pdisplay)
   {

//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBack);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFore);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFace);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFaceHover);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFacePress);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButton);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButtonHover);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButtonPress);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorder);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorderHover);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorderHover1);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorderHover2);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorderHover3);
//      XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBorderPress);

   }


   void simple_ui_display::on_colors(display *pdisplay)
   {

      on_free_colors(pdisplay);

      on_alloc_colors(pdisplay);

   }


   void simple_ui_display::call_expose(display *pdisplay)
   {

//      XWindowAttributes a{};
//
//      XGetWindowAttributes(pdisplay, m_window, &a);
//
//      if (a.width > 0 && a.height > 0)
//      {
//
//         m_size.cx = a.width;
//
//         m_size.cy = a.height;
//
//      }
//
//      on_expose(pdisplay);

   }


   void simple_ui_display::on_subject(::promise::subject *psubject, ::promise::context *pcontext)
   {

      if (psubject->id() == id_os_user_theme)
      {

         m_bOsUserThemeColorModified = true;

         invalidate();

      }

   }


   void simple_ui_display::invalidate()
   {

      m_bInvalidated = true;

      auto pwindowing = System.windowing();

      if(pwindowing)
      {

         pwindowing->kick_idle();

      }

      //x11_kick_idle();

   }


   void simple_ui_display::on_idle(display *pdisplay)
   {

      if (m_bInvalidated)
      {

         m_bInvalidated = false;

         call_expose(pdisplay);

      }

   }


   void simple_ui_display::on_expose(display *pdisplay)
   {

      if (m_bOsUserThemeColorModified)
      {

         on_colors(pdisplay);

      }

//      try
//      {
//
//         int iDraw = 1;
//
//         XSync(pdisplay, False);
//
//         if (iDraw == 1)
//         {
//
//            const char *buf = "Test";
//
//            XftDrawRect(m_pdraw, &m_colorBack, 0, 0, m_size.cx, m_size.cy);
//
//         }
//
//         {
//
//            color32_t crBk = get_simple_ui_color(::user::e_element_background);
//
//            int iY = m_iMarginTop;
//
//            for (auto &str : m_stra)
//            {
//
//               str.trim_right();
//
//               XftDrawStringUtf8(m_pdraw, &m_colorFore, m_pfont, m_iMarginLeft, iY + m_iTextAscent,
//                                 (FcChar8 *) str.c_str(), str.get_length());
//
//               iY += m_iLineHeight;
//
//               iY += m_iLineSpacing;
//
//            }
//
//            int right = m_size.cx - m_iMarginRight;
//
//            XftColor colorFore;
//            XftColor colorBack;
//            XftColor colorBorder;
//
//            for (index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
//            {
//
//               auto pbutton = m_buttona[iButton];
//
//               XGlyphInfo &rText = pbutton->m_infoText;
//
//               ::rectangle_i32 &rButtonOuter = pbutton->m_rectangle;
//
//               rButtonOuter.right = right;
//               rButtonOuter.left = right - m_iButtonWidth;
//               rButtonOuter.top = m_iButtonTop;
//               rButtonOuter.bottom = m_iButtonTop + m_iButtonHeight;
//
//               ::rectangle_i32 rButton = rButtonOuter;
//
//               rButton.deflate(1, 1);
//
//               if (pbutton->m_bPress)
//               {
//
//                  colorFore = m_colorButtonPress;
//
//               }
//               else if (pbutton->m_bHover)
//               {
//
//                  colorFore = m_colorButtonHover;
//
//               }
//               else
//               {
//
//                  colorFore = m_colorButton;
//
//               }
//
//               if (pbutton->m_bPress)
//               {
//
//                  colorBack = m_colorFacePress;
//
//               }
//               else if (pbutton->m_bHover)
//               {
//
//                  colorBack = m_colorFaceHover;
//
//               }
//               else
//               {
//
//                  colorBack = m_colorFace;
//
//               }
//
//               if (pbutton->m_bPress)
//               {
//
//                  colorBorder = m_colorBorderPress;
//
//               }
//               else if (pbutton->m_bHover)
//               {
//
//                  colorBorder = m_colorBorderHover;
//
//               }
//               else
//               {
//
//                  colorBorder = m_colorBorder;
//
//               }
//
//               if (pbutton->m_bHover || pbutton->m_bPress)
//               {
//
//                  rButtonOuter.inflate(3);
//                  XftDrawRect(m_pdraw, &m_colorBorderHover3, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(),
//                              rButtonOuter.height());
//                  rButtonOuter.deflate(1);
//                  XftDrawRect(m_pdraw, &m_colorBorderHover2, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(),
//                              rButtonOuter.height());
//                  rButtonOuter.deflate(1);
//                  XftDrawRect(m_pdraw, &m_colorBorderHover1, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(),
//                              rButtonOuter.height());
//                  rButtonOuter.deflate(1);
//
//               }
//
//               XftDrawRect(m_pdraw, &colorBorder, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(),
//                           rButtonOuter.height());
//
//               XftDrawRect(m_pdraw, &colorBack, rButton.left, rButton.top, rButton.width(), rButton.height());
//
//               ::rectangle_i32 rectText(rButton);
//
//               rectText.deflate(m_iButtonHPadding, m_iButtonVPadding);
//
//               XftDrawStringUtf8(m_pdraw, &colorFore, m_pfont,
//                                 rectText.left + (rectText.width() - rText.width) / 2,
//                                 rectText.top + m_iTextAscent,
//                                 (FcChar8 *) pbutton->m_strLabel.c_str(), pbutton->m_strLabel.get_length());
//
//               right = rButton.left - m_iButtonHSpacing;
//
//            }
//
//         }
//
//      }
//      catch (...)
//      {
//
//      }

   }


   int simple_ui_display::show()
   {

//      {
//
//         sync_lock sl(x11_mutex());
//
//         Display *pdisplay = x11_get_display();
//
//         XLockDisplay(pdisplay);
//
//         try
//         {
//
//            m_iScreen = DefaultScreen(pdisplay);
//
//            //printf("Default Screen %pdisplay\n", iScreen);
//
//            auto windowRoot = DefaultRootWindow(pdisplay);
//
//            //printf("Default Root Window %" PRId64 "\n", windowRoot);
//
//            XSetWindowAttributes attr = {};
//
//            m_pvisual = get_32bit_visual(pdisplay);
//
//            m_colormap = XCreateColormap(pdisplay, windowRoot, m_pvisual, AllocNone);
//
//            attr.colormap = m_colormap;
//            attr.border_pixel = 0;
//            attr.background_pixel = argb(255, 255, 255, 255);
//            attr.event_mask =
//               KeyPressMask |
//               KeyReleaseMask |
//               ButtonPressMask |
//               ButtonReleaseMask |
//               EnterWindowMask |
//               LeaveWindowMask |
//               PointerMotionMask |
//               ExposureMask |
//               VisibilityChangeMask |
//               StructureNotifyMask |
//               FocusChangeMask |
//               PropertyChangeMask |
//               ColormapChangeMask;
//
//            //      char **missingCharset_list = NULL;
//            //
//            //      int missingCharset_count = 0;
//            //
//            //      m_fs = XCreateFontSet(pdisplay,
//            //         "-*-*-medium-r-*-*-*-140-75-75-*-*-*-*" ,
//            //         &missingCharset_list, &missingCharset_count, NULL);
//            //
//            //      if (missingCharset_count)
//            //      {
//            //
//            //         fprintf(stderr, "Missing charsets :\n");
//            //
//            //         for(int i = 0; i < missingCharset_count; i++)
//            //         {
//            //
//            //            fprintf(stderr, "%s\n", missingCharset_list[i]);
//            //
//            //         }
//            //
//            //         XFreeStringList(missingCharset_list);
//            //
//            //      }
//
//
//            m_window = XCreateWindow(
//               pdisplay, windowRoot,
//               0, 0, 1, 1, 0,
//               32,
//               InputOutput,
//               m_pvisual,
//               CWColormap |
//               CWBorderPixel |
//               CWBackPixel |
//               CWEventMask,
//               &attr);
//
//            //printf("Window created %" PRId64 "\n", m_window);
//            XStoreName(pdisplay, m_window, m_strTitle);
//
//            const char *pszFont = "Ubuntu:size_i32=12";
//
//            m_pfont = XftFontOpenName(pdisplay, m_iScreen, pszFont);
//
//            m_pdraw = XftDrawCreate(pdisplay, m_window, m_pvisual, m_colormap);
//
//            System.delivery_for(id_os_user_theme, this);
//
//            //System.(id_dark_mode);
//
//            //on_alloc_colors(pdisplay);
//
//            on_layout(pdisplay);
//
//            XMapWindow(pdisplay, m_window);
//
//            XResizeWindow(pdisplay, m_window, m_size.cx, m_size.cy);
//
//            XMoveWindow(pdisplay, m_window, m_point.x, m_point.y);
//
//            hook();
//
//         }
//         catch (...)
//         {
//
//         }
//
//         XUnlockDisplay(pdisplay);
//
//      }
//
//      x11_defer_handle_just_hooks();

      return m_iResult;

   }


   void simple_ui_display::on_layout(display *pdisplay)
   {

      ::size_i32 sizeLine;

//      XGlyphInfo infoDummy;
//
//      m_iTextAscent = 0;
//
//      string strMeasure;
//
//      strMeasure = "Áj";
//
//      XftTextExtentsUtf8(pdisplay, m_pfont, (FcChar8 *) strMeasure.c_str(), strMeasure.get_length(), &infoDummy);
//
//      XGlyphInfo info;
//
//      for (auto &str : m_stra)
//      {
//
//         strMeasure = "Áj" + str;
//
//         XftTextExtentsUtf8(pdisplay, m_pfont, (FcChar8 *) strMeasure.c_str(), strMeasure.get_length(), &info);
//
//         sizeLine.cx = max(sizeLine.cx, info.x + info.width - infoDummy.width);
//
//         m_iTextAscent = max(m_iTextAscent, info.y);
//
//         sizeLine.cy = max(sizeLine.cy, info.height);
//
//      }
//
//      int iMaxButtonTextWidth = 50;
//
//      for (index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
//      {
//
//         auto pbutton = m_buttona[iButton];
//
//         XGlyphInfo &infoText = pbutton->m_infoText;
//
//         if (!pbutton->m_bTextRect)
//         {
//
//            pbutton->m_bTextRect = true;
//
//            string strMeasure = "Áj" + pbutton->m_strLabel;
//
//            XftTextExtentsUtf8(pdisplay, m_pfont, (FcChar8 *) strMeasure.c_str(), strMeasure.get_length(), &infoText);
//
//            infoText.width -= infoDummy.width;
//
//         }
//
//         iMaxButtonTextWidth = max(iMaxButtonTextWidth, infoText.width);
//
//         m_iTextAscent = max(m_iTextAscent, info.y);
//
//         sizeLine.cy = max(sizeLine.cy, infoText.height);
//
//      }
//
//      m_iButtonWidth = m_iButtonHPadding + iMaxButtonTextWidth + m_iButtonHPadding;
//
//      m_iLineHeight = sizeLine.cy;
//
//      m_iButtonHeight = m_iButtonVPadding + m_iLineHeight + m_iButtonVPadding;
//
//      ::size_i32 sizeTotal;
//
//      sizeTotal.cx = max(m_iMarginLeft + sizeLine.cx + m_iMarginRight,
//                         m_iMarginLeft + m_iButtonWidth * m_buttona.get_count() +
//                         (m_iButtonHSpacing) * (m_buttona.get_count() - 1) + m_iMarginRight);
//
//      sizeTotal.cy = m_iMarginTop;
//
//      sizeTotal.cy += m_iLineHeight * m_stra.get_count();
//
//      sizeTotal.cy += m_iLineSpacing * (m_stra.get_count() - 1);
//
//      sizeTotal.cy += m_iMidSpacing;
//
//      m_iButtonTop = sizeTotal.cy;
//
//      sizeTotal.cy += m_iButtonHeight;
//
//      sizeTotal.cy += m_iMarginBottom;
//
//      int iButtonWidth = 100;
//
//      m_size = m_size.max(sizeTotal);
//
//      int iScreenCount = 0;
//
//      auto pscreens = XineramaQueryScreens(pdisplay, &iScreenCount);
//
//      int cxScreen = 800;
//
//      int cyScreen = 600;
//
//      int xScreen = 0;
//
//      int yScreen = 0;
//
//      if (pscreens)
//      {
//
//         cxScreen = pscreens[0].width;
//
//         cyScreen = pscreens[0].height;
//
//         xScreen = pscreens[0].x_org;
//
//         yScreen = pscreens[0].y_org;
//
//         XFree(pscreens);
//
//      }
//
//      m_point.x = xScreen;
//
//      m_point.y = yScreen;
//
//      m_point.x += (cxScreen - m_size.cx) / 2;
//
//      m_point.y += (cyScreen - m_size.cy) / 3;

   }


   bool simple_ui_display::process_event(display *pdisplay, event * pevent)
   {

//      if (e.xany.window == m_window)
//      {
//
//         if (e.type == Expose)
//         {
//
//            call_expose(pdisplay);
//
//            XFlush(pdisplay);
//
//         }
//         else if (e.type == MotionNotify)
//         {
//
//            ::point_i32 point(e.xmotion.x, e.xmotion.y);
//
//            bool bRedraw = false;
//
//            for (auto &pbutton : m_buttona)
//            {
//
//               bool bHover = pbutton->m_rectangle.contains(point);
//
//               if (is_different(bHover, pbutton->m_bHover))
//               {
//
//                  pbutton->m_bHover = bHover;
//
//                  bRedraw = true;
//
//               }
//
//            }
//
//            if (bRedraw)
//            {
//
//               call_expose(pdisplay);
//
//            }
//
//         }
//         else if (e.type == ButtonPress)
//         {
//
//            ::point_i32 point(e.xbutton.x, e.xbutton.y);
//
//            bool bRedraw = false;
//
//            for (auto &pbutton : m_buttona)
//            {
//
//               bool bPress = pbutton->m_rectangle.contains(point);
//
//               if (is_different(bPress, pbutton->m_bPress))
//               {
//
//                  pbutton->m_bPress = bPress;
//
//                  bRedraw = true;
//
//               }
//
//            }
//
//            if (bRedraw)
//            {
//
//               call_expose(pdisplay);
//
//            }
//
//         }
//         else if (e.type == ButtonRelease)
//         {
//
//            ::point_i32 point(e.xbutton.x, e.xbutton.y);
//
//            bool bRedraw = false;
//
//            for (auto &pbutton : m_buttona)
//            {
//
//               if (pbutton->m_bPress)
//               {
//
//                  pbutton->m_bPress = false;
//
//                  bRedraw = true;
//
//                  if (pbutton->m_rectangle.contains(point))
//                  {
//
//                     if (on_click(pbutton->m_edialogresult))
//                     {
//
//                        break;
//
//                     }
//
//                  }
//
//               }
//
//            }
//
//            if (bRedraw)
//            {
//
//               call_expose(pdisplay);
//
//            }
//
//         }
//
//         return true;
//
//      }

      return false;

   }


   void simple_ui_display::close_window()
   {

      //XUnmapWindow(x11_get_display(), m_window);

      //unhook();

      //::update_task::remove(id_dark_mode, this);

   }


   bool simple_ui_display::on_click(int iResult)
   {

      m_iResult = iResult;

      close_window();

      return true;

   }


} // namespace windowing



