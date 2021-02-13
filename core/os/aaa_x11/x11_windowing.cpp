#include "framework.h"
#include "aura/os/linux/_user.h"
//!!!#include <X11/extensions/Xinerama.h>

//http://rosettacode.org/wiki/Window_creation/X11

//!!!#include <X11/Xlib.h>
#include <stdio.h>

#include <string.h>

extern ::mutex * x11_mutex();

Visual * get_32bit_visual(Display * pdisplay);

static Display * s_pdisplay = NULL;

Display * x11_get_display()
{

   if(s_pdisplay == NULL)
   {

      s_pdisplay =  XOpenDisplay(NULL);

   }

   return s_pdisplay;

}




class simple_ui_display
{
public:


   string_array      m_stra;
   string            m_strTitle;
   string            m_strFontName;

   Window            m_window;
   ::size            m_size;

   //GC              m_gcBack;
   //GC              m_gcFore;

   //Colormap        m_colormap;


   simple_ui_display(const string & strLine, const string & strTitle);
   simple_ui_display(const string_array & straLines, const string & strTitle);

   GC create_gc();

   void on_expose();

   int show();

   void on_show();

};


simple_ui_display::simple_ui_display(const string & strLine, const string & strTitle) :
m_strTitle(strTitle),
m_strFontName("serif"),
m_size(600, 400)
{

   m_stra.add(strLine);

}


simple_ui_display::simple_ui_display(const string_array & straLines, const string & strTitle) :
m_strTitle(strTitle),
m_strFontName("serif"),
m_size(600, 400)
{

   m_stra = straLines;

}


int display_line(const string & str, const string & strTitle)
{

   simple_ui_display display(str, strTitle);

   return display.show();

}

int display_lines(const string_array & stra, const string & strTitle)
{

   simple_ui_display display(stra, strTitle);

   return display.show();

}

//void line_array_display::show(const string & str, const string & strTitle)
//{
//
//   Display *d;
//   Window w;
//   XEvent e;
//   int s;
//
//   d = x11_get_display();
//   if (d == NULL) {
//      fprintf(stderr, "Cannot open display\n");
//      return 0;
//   }
//
//   s = DefaultScreen(d);
//   w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
//                           BlackPixel(d, s), WhitePixel(d, s));
//   XSelectInput(d, w, ExposureMask | KeyPressMask);
//   XMapWindow(d, w);
//   XStoreName(d, w, strTitle);
//
//
//   while (1) {
//      XNextEvent(d, &e);
//      if (e.type == Expose) {
//         XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
//         XDrawString(d, w, DefaultGC(d, s), 10, 50, str, str.length());
//      }
//      if (e.type == KeyPress)
//         break;
//   }
//
//   XCloseDisplay(d);
//   return 0;
//
//}



// create_gc from https://github.com/QMonkey/Xlib-demo/blob/master/src/simple-text.c
GC simple_ui_display::create_gc()
{

   synchronization_lock synchronizationlock(x11_mutex());

   //windowing_output_debug_string("\n::get_window_rect 1");

   xdisplay d(x11_get_display());

   GC gc;

   unsigned long valuemask = 0;		/* which values in 'values' to  */
					/* check when creating the GC.  */
   XGCValues values;			/* initial values for the GC.   */
   unsigned int line_width = 2;		/* line width for the GC.       */
   int line_style = LineSolid;		/* style for lines drawing and  */
   int cap_style = CapButt;		/* style of the line's edje and */
   int join_style = JoinBevel;		/*  joined lines.		*/
   int screen_num = d.default_screen();

   gc = XCreateGC(d, m_window, valuemask, &values);

   if (gc == nullptr)
   {

      return nullptr;

   }


//      auto colormap = m_colormap;
//
//   XColor xcolour;
//
//   xcolour.red = iR * 255;
//
//   xcolour.green = iG * 255;
//
//   xcolour.blue = iB * 255;
//
//   xcolour.flags = DoRed | DoGreen | DoBlue;
//
//   XAllocColor(m_display, colormap, &xcolour);

//   XSetForeground(m_display, gc, argb(255, iR, iG, iB));

   XSetLineAttributes(d, gc, line_width, line_style, cap_style, join_style);

   XSetFillStyle(d, gc, FillSolid);

   return gc;

}


void simple_ui_display::on_expose()
{

   synchronization_lock synchronizationlock(x11_mutex());

   //windowing_output_debug_string("\n::get_window_rect 1");

   xdisplay d(x11_get_display());

   XSync(d, False);

   GC gc = create_gc();

   color32_t crBk = get_simple_ui_color(::user::color_background);

   crBk = argb_swap_rb(crBk);

   XSetForeground(d, gc, crBk);

   XFillRectangle(d, m_window, gc, 0, 0, m_size.cx, m_size.cy);

   int iFontHeight;

//   Aug 6th, 2019 - ca2 Store for Ubuntu/Linux General Build Environment Setup
//
//      - X11 Core Font Query didn't work at Ubuntu 19.04
//
//
//
//   // "*helvetica-normal-r-*-180-*"
//   // "-adobe-new century schoolbook-bold-r-normal--24-240-75-75-p-149-iso8859-9"
//
//   auto fontDesired = XLoadQueryFont(m_display, "*helvetica-normal-r-*-180-*");
//
//
//   if (fontDesired)
//   {
//
//      iFontHeight = fontDesired->ascent + fontDesired->descent;
//
//      XSetFont(m_display, gc, fontDesired->fid);
//
//   }
//   else
//   {
//
      auto gcontext = XGContextFromGC(gc);

      auto fontDefault = XQueryFont(d, gcontext);

      if (fontDefault)
      {

         iFontHeight = fontDefault->ascent + fontDefault->descent;

         XSetFont(d, gc, fontDefault->fid);

      }
      else
      {

         iFontHeight = 25;

      }

   //}

   int x = iFontHeight * 2;

   int y = iFontHeight * 2;

   color32_t crText = get_simple_ui_color(::user::color_text);

   crText = argb_swap_rb(crText);

   XSetForeground(d, gc, crText);

   for(auto & str : m_stra)
   {

      str.trim_right();

      if(str.has_char())
      {

         XDrawString(d, m_window, gc, x, y, str, str.length());

      }

      y += iFontHeight;

   }

   XFlush(d);

   XFreeGC(d, gc);

}


int simple_ui_display::show()
{

   synchronization_lock synchronizationlock(x11_mutex());

   //windowing_output_debug_string("\n::get_window_rect 1");

   xdisplay d(x11_get_display());

   Visual * pvisual = nullptr;

   int iScreen = d.default_screen();

   printf("Default Screen %d\n", iScreen);

   auto windowRoot = d.default_root_window();

   printf("Default Root Window %" PRId64 "\n", windowRoot);

   int xWindow = 0;

   int yWindow = 0;

   XSetWindowAttributes attr={};

   pvisual = get_32bit_visual(d);

   auto colormap = XCreateColormap(d, windowRoot, pvisual, AllocNone);

   int iScreenCount = 0;

   auto pscreens = XineramaQueryScreens(d, &iScreenCount);

   int cxScreen = 800;

   int cyScreen = 600;

   if(pscreens)
   {

      cxScreen = pscreens[0].width;

      cyScreen = pscreens[0].height;

      xWindow = pscreens[0].x_org;

      yWindow = pscreens[0].y_org;

      XFree(pscreens);

   }

   xWindow += (cxScreen - m_size.cx) / 2;

   yWindow += (cyScreen - m_size.cy) / 3;

   attr.colormap = colormap;
   attr.border_pixel = 0;
   attr.background_pixel = argb(255, 255, 255, 255);
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

   m_window =
      XCreateWindow(
         d, windowRoot,
         xWindow, yWindow, m_size.cx, m_size.cy, 0,
         32,
         InputOutput,
         pvisual,
         CWColormap |
         CWBorderPixel |
         CWBackPixel |
         CWEventMask,
         &attr);

   printf("Window created %" PRId64 "\n", m_window);




//   XSelectInput(m_display, m_window, ExposureMask | KeyPressMask);
//
//   if(m_iReverseVideo)
//   {
//
//      m_gcFore = create_gc(255, 250, 240);
//
//      m_gcBack = create_gc(80, 70, 60);
//
//   }
//   else
//   {
//
//      m_gcBack = create_gc(255, 250, 240);
//
//      m_gcFore = create_gc(80, 70, 60);
//
//   }


   XMapWindow(d, m_window);

   XMoveWindow(d, m_window, xWindow, yWindow);

   XStoreName(d, m_window, m_strTitle);

   XEvent e;

   while (1)
   {

      XNextEvent(d, &e);

      if (e.type == Expose)
      {

         on_expose();

      }

      if (e.type == KeyPress)
      {

         break;

      }

   }

   XUnmapWindow(d, m_window);

   XDestroyWindow(d, m_window);

   //XFreeGC(m_display, m_gcFore);

   //XFreeGC(m_display, m_gcBack);

   return 0;

}

CLASS_DECL_CORE string message_box_result_to_string(int iResult);


::e_status os_message_box(oswindow oswindow, const char * psz, const char * pszTitle, const ::e_message_box & emessagebox, ::callback callback)
{

   wstring wstr(psz);

   wstring wstrTitle(pszTitle);

   string_array straSep;

   straSep.add("\n");
   straSep.add("\r");
   straSep.add("\r\n");
   straSep.add("\n\r");

   string_array stra;

   stra.add_smallest_tokens(string(psz), straSep);

   int iResult = display_lines(stra, string(pszTitle));

   string strResult = message_box_result_to_string(iResult);

   callback.receive_response(strResult);



   return ::success;

}


int_bool MessageBox(oswindow interaction_impl, const char * psz, const widechar * pszTitle, u32 uFlags)
{

   string_array straSep;

   straSep.add("\n");
   straSep.add("\r");
   straSep.add("\r\n");
   straSep.add("\n\r");

   string_array stra;

   stra.add_smallest_tokens(string(psz), straSep);

   return display_lines(stra, string(pszTitle));

}



