#include "framework.h"
#include "_x11.h"


simple_ui_display::simple_ui_display(const string & strMessageParam, const string & strTitle, ::emessagebox emessagebox, ::future future):
   m_strTitle(strTitle),
   m_strFontName("serif"),
   m_size(300, 200),
   m_future(future)
{

   ::user::defer_calc_os_dark_mode();

   //::user::initialize_edesktop();

   common_construct();

   string strMessage(strMessageParam);

   strMessage.replace_ci("<br>", " \n");

   m_stra.add_lines(strMessage);

   ::u32 uType = ((::u32)emessagebox) & 7;

   switch(uType)
   {
      case MB_OKCANCEL:
         m_buttona.add(__new(x11_button("OK", "ok")));
         m_buttona.add(__new(x11_button("Cancel", "cancel")));
         break;
      case MB_ABORTRETRYIGNORE:
         m_buttona.add(__new(x11_button("Abort", "abort")));
         m_buttona.add(__new(x11_button("Retry", "retry")));
         m_buttona.add(__new(x11_button("Ignore", "ignore")));
         break;
      case MB_YESNOCANCEL:
         m_buttona.add(__new(x11_button("Yes", "yes")));
         m_buttona.add(__new(x11_button("No", "no")));
         m_buttona.add(__new(x11_button("Cancel", "cancel")));
         break;
      case MB_YESNO:
         m_buttona.add(__new(x11_button("Yes", "yes")));
         m_buttona.add(__new(x11_button("No", "no")));
         break;
      case MB_RETRYCANCEL:
         m_buttona.add(__new(x11_button("Retry", "retry")));
         m_buttona.add(__new(x11_button("Cancel", "cancel")));
         break;
      case MB_CANCELTRYCONTINUE:
         m_buttona.add(__new(x11_button("Cancel", "cancel")));
         m_buttona.add(__new(x11_button("Try", "try")));
         m_buttona.add(__new(x11_button("Continue", "continue")));
         break;
      default:
         m_buttona.add(__new(x11_button("OK", "ok")));
         break;
   }

}


void simple_ui_display::common_construct()
{

   m_iMargin = 10;
   m_iMarginTop = 40;
   m_iMarginLine = 10;
   m_listMissingCharset = NULL;

}


simple_ui_display::~ simple_ui_display()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   XftDrawDestroy(m_pdraw);

   on_free_colors(pdisplay);

   XFreeStringList(m_listMissingCharset);
   XDestroyWindow(pdisplay, m_window);
   XFreeColormap(pdisplay, m_colormap);

   XUnlockDisplay(pdisplay);

}


void simple_ui_display::on_alloc_colors(Display * pdisplay)
{

   if(::user::is_app_dark_mode())
   {

      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#555555", &m_colorBack);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#888888", &m_colorFace);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorFore);

      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#999999", &m_colorFaceHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#AAAAAA", &m_colorFacePress);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorButton);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#e0f0ff", &m_colorButtonHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#c0e0ff", &m_colorButtonPress);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#ffffff", &m_colorBorder);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#E0F0FF", &m_colorBorderHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B2C0CF", &m_colorBorderHover1);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#85909F", &m_colorBorderHover2);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#59606F", &m_colorBorderHover3);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#c0e0ff", &m_colorBorderPress);

   }
   else
   {

      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#CCCCCC", &m_colorBack);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#AAAAAA", &m_colorFace);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#222222", &m_colorFore);

      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#A5A5A5", &m_colorFaceHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B0B0B0", &m_colorFacePress);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#222222", &m_colorButton);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#2050c7", &m_colorButtonHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#2050df", &m_colorButtonPress);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#888888", &m_colorBorder);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#7090D0", &m_colorBorderHover);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#87A0CF", &m_colorBorderHover1);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#A0B0CE", &m_colorBorderHover2);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#B7C0CD", &m_colorBorderHover3);
      XftColorAllocName(pdisplay, m_pvisual, m_colormap, "#5070df", &m_colorBorderPress);

   }

}


void simple_ui_display::on_free_colors(Display * pdisplay)
{

   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorBack);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFore);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFace);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFaceHover);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorFacePress);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButton);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButtonHover);
   XftColorFree(pdisplay, m_pvisual, m_colormap, &m_colorButtonPress);

}


void simple_ui_display::on_colors(Display * pdisplay)
{

   on_free_colors(pdisplay);

   on_alloc_colors(pdisplay);

}



// create_gc from https://github.com/QMonkey/Xlib-demo/blob/master/src/simple-text.c
GC simple_ui_display::create_gc()
{

   sync_lock sl(x11_mutex());

   //windowing_output_debug_string("\n::get_window_rect 1");

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   GC gc;

   try
   {

      unsigned long valuemask = 0;		/* which values in 'values' to  */
                  /* check when creating the GC.  */
      XGCValues values;			/* initial values for the GC.   */
      unsigned int line_width = 2;		/* line width for the GC.       */
      int line_style = LineSolid;		/* style for lines drawing and  */
      int cap_style = CapButt;		/* style of the line's edje and */
      int join_style = JoinBevel;		/*  joined lines.		*/
      int screen_num = DefaultScreen(pdisplay);

      gc = XCreateGC(pdisplay, m_window, valuemask, &values);

      if (gc == nullptr)
      {

         return nullptr;

      }

      XSetLineAttributes(pdisplay, gc, line_width, line_style, cap_style, join_style);

      XSetFillStyle(pdisplay, gc, FillSolid);

   }
   catch(...)
   {

   }

   XUnlockDisplay(pdisplay);

   return gc;

}





void simple_ui_display::on_expose()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   try
   {

      int iDraw = 1;

      XSync(pdisplay, False);

      if(iDraw == 1)
      {

         const char * buf = "Test";

         XftDrawRect(m_pdraw, &m_colorBack, 0, 0, m_size.cx, m_size.cy);

         //XftDrawStringUtf8(m_pdraw, &m_colorFore, m_pfont, 20, 20, (XftChar8 *)buf, strlen(buf));

         //XFlush(pdisplay);

      }
      //else
      {


         //GC gc = create_gc();

         COLORREF crBk = get_simple_ui_color(::user::element_background);

//         crBk = argb_swap_rb(crBk);
//
//         XSetForeground(pdisplay, gc, crBk);
//
//         XFillRectangle(pdisplay, m_window, gc, 0, 0, m_size.cx, m_size.cy);
//
//         int iFontHeight;
//
//         auto gcontext = XGContextFromGC(gc);
//
//         COLORREF crText = get_simple_ui_color(::user::element_text);
//
//         crText = argb_swap_rb(crText);
//
//         XSetForeground(pdisplay, gc, crText);
//
//         if(::user::is_app_dark_mode())
//         {
//
//            m_gcText = x11_create_gc(m_colormap, pdisplay, m_window, 255, 255, 255, 255);
//            m_gcTextHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 220, 170, 150);
//            //m_gcBar = x11_create_gc(m_colormap, pdisplay, m_window, 255, 240, 240, 240);
//            m_gcButton = x11_create_gc(m_colormap, pdisplay, m_window, 255, 120, 120, 120);
//            m_gcButtonHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 130, 130, 130);
//            m_gcButtonPress = x11_create_gc(m_colormap, pdisplay, m_window, 255, 140, 140, 140);
//
//         }
//         else
//         {
//
//            m_gcText = x11_create_gc(m_colormap, pdisplay, m_window, 255, 0, 0, 0);
//            m_gcTextHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 220, 170, 150);
//            //m_gcBar = x11_create_gc(m_colormap, pdisplay, m_window, 255, 240, 240, 240);
//            m_gcButton = x11_create_gc(m_colormap, pdisplay, m_window, 255, 190, 190, 190);
//            m_gcButtonHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 200, 200, 200);
//            m_gcButtonPress = x11_create_gc(m_colormap, pdisplay, m_window, 255, 210, 210, 210);
//
//         }

         int iY = m_iMarginTop;

         for(auto & str : m_stra)
         {

            str.trim_right();

            XftDrawStringUtf8(m_pdraw, &m_colorFore, m_pfont, m_iMarginLine, iY, (FcChar8 *)str.c_str(), str.get_length());

            iY += m_iButtonHeight;

         }

         int iBarTop = m_iButtonTop - m_iMarginLine * 2;

         //XFillRectangle(pdisplay, m_window, m_gcBar,
         //0, iBarTop, m_size.cx, m_size.cy - iBarTop);

         int right = m_size.cx - 10;

         int iMaxButtonWidth = 50;

         for(index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
         {

            auto pbutton = m_buttona[iButton];

            XGlyphInfo & infoText = pbutton->m_infoText;

            if(!pbutton->m_bTextRect)
            {

               pbutton->m_bTextRect = true;

               XftTextExtentsUtf8(pdisplay, m_pfont, (FcChar8 *) pbutton->m_strLabel.c_str(), pbutton->m_strLabel.get_length(), &infoText);

            }

            iMaxButtonWidth = max(iMaxButtonWidth, infoText.width);

         }

         XftColor colorFore;
         XftColor colorBack;
         XftColor colorBorder;

         for(index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
         {

            auto pbutton = m_buttona[iButton];

            XGlyphInfo & rText = pbutton->m_infoText;

            ::rect & rButtonOuter = pbutton->m_rect;

            rButtonOuter.right = right;
            rButtonOuter.left = right - iMaxButtonWidth - (m_iMarginLine * 6);
            rButtonOuter.top = m_iButtonTop;
            rButtonOuter.bottom = m_iButtonTop + m_iButtonHeight;

            ::rect rButton = rButtonOuter;

            rButton.deflate(1, 1);

            if(pbutton->m_bPress)
            {

               colorFore = m_colorButtonPress;

            }
            else if(pbutton->m_bHover)
            {

               colorFore = m_colorButtonHover;

            }
            else
            {

               colorFore = m_colorButton;

            }

            if(pbutton->m_bPress)
            {

               colorBack = m_colorFacePress;

            }
            else if(pbutton->m_bHover)
            {

               colorBack = m_colorFaceHover;

            }
            else
            {

               colorBack = m_colorFace;

            }

            if(pbutton->m_bPress)
            {

               colorBorder = m_colorBorderPress;

            }
            else if(pbutton->m_bHover)
            {

               colorBorder = m_colorBorderHover;

            }
            else
            {

               colorBorder = m_colorBorder;

            }

            if(pbutton->m_bHover || pbutton->m_bPress)
            {

               rButtonOuter.inflate(3);
               XftDrawRect(m_pdraw, &m_colorBorderHover3, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(), rButtonOuter.height());
               rButtonOuter.deflate(1);
               XftDrawRect(m_pdraw, &m_colorBorderHover2, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(), rButtonOuter.height());
               rButtonOuter.deflate(1);
               XftDrawRect(m_pdraw, &m_colorBorderHover1, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(), rButtonOuter.height());
               rButtonOuter.deflate(1);

            }


            XftDrawRect(m_pdraw, &colorBorder, rButtonOuter.left, rButtonOuter.top, rButtonOuter.width(), rButtonOuter.height());

            XftDrawRect(m_pdraw, &colorBack, rButton.left, rButton.top, rButton.width(), rButton.height());

            ::rect rectText(rButton);

            rectText.deflate(m_iMarginLine * 3, m_iMarginLine);

            XftDrawStringUtf8(m_pdraw, &colorFore, m_pfont,
            rectText.left + (rectText.width() - rText.width) / 2,
            rectText.top + m_iButtonHeight - m_iMarginLine * 2.5,
            (FcChar8 *)pbutton->m_strLabel.c_str(), pbutton->m_strLabel.get_length());

//            XftDrawText(pdisplay, m_window, m_fs, gc,
//                        rectText.left + (rectText.width() - rText.width) / 2, rectText.top + m_iButtonHeight - m_iMarginLine * 2,
//                        pbutton->m_wstrLabel, pbutton->m_wstrLabel.get_length());
//
            right = rButton.left - 10;

         }

//         XFreeGC(pdisplay, m_gcText);
//         XFreeGC(pdisplay, m_gcTextHover);
//         //XFreeGC(pdisplay, m_gcBar);
//         XFreeGC(pdisplay, m_gcButton);
//         XFreeGC(pdisplay, m_gcButtonHover);
//         XFreeGC(pdisplay, m_gcButtonPress);

         XFlush(pdisplay);

//         XFreeGC(pdisplay, gc);

      }

   }
   catch(...)
   {

   }

   XUnlockDisplay(pdisplay);


}


::estatus simple_ui_display::show()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   try
   {

      m_iScreen = DefaultScreen(pdisplay);

      //printf("Default Screen %pdisplay\n", iScreen);

      auto windowRoot = DefaultRootWindow(pdisplay);

      //printf("Default Root Window %" PRId64 "\n", windowRoot);

      XSetWindowAttributes attr={};

      m_pvisual = get_32bit_visual(pdisplay);

      m_colormap = XCreateColormap(pdisplay, windowRoot, m_pvisual, AllocNone);

      attr.colormap = m_colormap;
      attr.border_pixel = 0;
      attr.background_pixel = ARGB(255, 255, 255, 255);
      attr.event_mask =
         KeyPressMask |
         KeyReleaseMask |
         ButtonPressMask |
         ButtonReleaseMask |
         EnterWindowMask |
         LeaveWindowMask |
         PointerMotionMask |
         ExposureMask |
         VisibilityChangeMask |
         StructureNotifyMask |
         FocusChangeMask |
         PropertyChangeMask |
         ColormapChangeMask;

//      char **missingCharset_list = NULL;
//
//      int missingCharset_count = 0;
//
//      m_fs = XCreateFontSet(pdisplay,
//         "-*-*-medium-r-*-*-*-140-75-75-*-*-*-*" ,
//         &missingCharset_list, &missingCharset_count, NULL);
//
//      if (missingCharset_count)
//      {
//
//         fprintf(stderr, "Missing charsets :\n");
//
//         for(int i = 0; i < missingCharset_count; i++)
//         {
//
//            fprintf(stderr, "%s\n", missingCharset_list[i]);
//
//         }
//
//         XFreeStringList(missingCharset_list);
//
//      }


      m_window = XCreateWindow(
            pdisplay, windowRoot,
            0, 0, 1, 1, 0,
            32,
            InputOutput,
            m_pvisual,
            CWColormap |
            CWBorderPixel |
            CWBackPixel |
            CWEventMask,
            &attr);

      //printf("Window created %" PRId64 "\n", m_window);
      XStoreName(pdisplay, m_window, m_strTitle);

      const char * pszFont = "Ubuntu:size=12";

      m_pfont = XftFontOpenName(pdisplay, m_iScreen, pszFont);

      m_pdraw = XftDrawCreate(pdisplay, m_window, m_pvisual, m_colormap);

      on_alloc_colors(pdisplay);

      on_layout(pdisplay);

      XMapWindow(pdisplay, m_window);

      XResizeWindow(pdisplay, m_window, m_size.cx, m_size.cy);

      XMoveWindow(pdisplay, m_window, m_point.x, m_point.y);

      hook();

   }
   catch(...)
   {

   }

   XUnlockDisplay(pdisplay);

   x11_defer_handle_just_hooks();

   return ::success;

}


void simple_ui_display::on_layout(Display * pdisplay)
{

   ::size size;

   XGlyphInfo info;

   for(auto & str : m_stra)
   {

      XftTextExtentsUtf8(pdisplay, m_pfont, (FcChar8 *) str.c_str(), str.get_length(), &info);

      size.cx = max(size.cx, info.width + m_iMargin * 2);

      size.cy = max(size.cy, info.height + m_iMargin);

   }

   size.cy *= (m_stra.get_count() + 2);

   m_iButtonHeight = size.cy / (m_stra.get_count() + 2)  + m_iMarginLine;

   size.cy += m_iMarginTop + m_iMarginLine;

   m_size = m_size.max(size);

   m_iButtonTop = m_size.cy - m_iButtonHeight - m_iMarginLine * 2;


   int iScreenCount = 0;

   auto pscreens = XineramaQueryScreens(pdisplay, &iScreenCount);

   int cxScreen = 800;

   int cyScreen = 600;

   int xScreen = 0;

   int yScreen = 0;

   if(pscreens)
   {

      cxScreen = pscreens[0].width;

      cyScreen = pscreens[0].height;

      xScreen = pscreens[0].x_org;

      yScreen = pscreens[0].y_org;

      XFree(pscreens);

   }

   m_point.x = xScreen;

   m_point.y = yScreen;

   m_point.x += (cxScreen - m_size.cx) / 2;

   m_point.y += (cyScreen - m_size.cy) / 3;

}


bool simple_ui_display::process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie)
{

   if(e.xany.window == m_window)
   {

      if (e.type == Expose)
      {

         on_expose();

      }
      else if (e.type == MotionNotify)
      {

         ::point point(e.xmotion.x, e.xmotion.y);

         bool bRedraw = false;

         for(auto & pbutton : m_buttona)
         {

            bool bHover = pbutton->m_rect.contains(point);

            if(is_different(bHover, pbutton->m_bHover))
            {

               pbutton->m_bHover = bHover;

               bRedraw = true;

            }

         }

         if(bRedraw)
         {

            on_expose();

         }

      }
      else if(e.type == ButtonPress)
      {

         ::point point(e.xbutton.x, e.xbutton.y);

         bool bRedraw = false;

         for(auto & pbutton : m_buttona)
         {

            bool bPress = pbutton->m_rect.contains(point);

            if(is_different(bPress, pbutton->m_bPress))
            {

               pbutton->m_bPress = bPress;

               bRedraw = true;

            }

         }

         if(bRedraw)
         {

            on_expose();

         }

      }
      else if(e.type == ButtonRelease)
      {

         ::point point(e.xbutton.x, e.xbutton.y);

         bool bRedraw = false;

         for(auto & pbutton : m_buttona)
         {

            if(pbutton->m_bPress)
            {

               pbutton->m_bPress = false;

               bRedraw = true;

               if(pbutton->m_rect.contains(point))
               {

                  if(on_click(pbutton->m_strResult))
                  {

                     break;

                  }

               }

            }

         }

         if(bRedraw)
         {

            on_expose();

         }

      }

      return true;

   }

   return false;

}



bool simple_ui_display::on_click(const char * pszResult)
{

   string strResult(pszResult);

   m_future.send(strResult);

   XUnmapWindow(x11_get_display(), m_window);

   unhook();

   return true;

}



