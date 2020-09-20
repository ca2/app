#include "framework.h"
#include "_x11.h"
#include <X11/extensions/Xinerama.h>


//http://rosettacode.org/wiki/Window_creation/X11

#include <X11/Xlib.h>
#include <stdio.h>

#include <string.h>
#include "_x11.h"

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

bool __x11_hook_process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie);
#define SIMPLE_UI_MAX_BUTTON_COUNT 8
bool __x11_hook_list_is_empty();

class x11Button :
   virtual public generic
{
public:


   wstring           m_wstrLabel;
   bool              m_bTextRect;
   ::rect            m_rect;
   XRectangle        m_rectText;
   bool              m_bPress;
   bool              m_bHover;
   string            m_strResult;


   x11Button(const char * psz, const char * pszResult) :
      m_wstrLabel(psz),
      m_strResult(pszResult)
   {

      m_bTextRect = false;
      m_bPress = false;
      m_bHover = false;

   }

   virtual ~x11Button()
   {

   }

};


class simple_ui_display :
   virtual public ::x11_hook
{
public:


   string_array                     m_stra;
   string                           m_strTitle;
   string                           m_strFontName;

   Window                           m_window;
   ::size                           m_size;

   __pointer_array(x11Button)       m_buttona;

   int                              m_iButtonTop;
   int                              m_iButtonHeight;

   XFontSet                         m_fs;
   char **                          m_listMissingCharset;
   GC                               m_gcText;
   GC                               m_gcTextHover;
   //GC                               m_gcBar;
   GC                               m_gcButton;
   GC                               m_gcButtonHover;
   GC                               m_gcButtonPress;

   Colormap                         m_colormap;

   int                              m_iMarginTop;
   int                              m_iMarginLine;

   ::callback                       m_callback;


   simple_ui_display(const string & strMessage, const string & strTitle, ::emessagebox emessagebox, ::callback callback);

   ~simple_ui_display();

   void common_construct();

   GC create_gc();

   void on_expose();

   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie) override;

   ::estatus show();

   void on_show();

   bool on_click(const char * pszResult);

};


simple_ui_display::simple_ui_display(const string & strMessageParam, const string & strTitle, ::emessagebox emessagebox, ::callback callback):
   m_strTitle(strTitle),
   m_strFontName("serif"),
   m_size(300, 200),
   m_callback(callback)
{

   //::user::initialize_edesktop();

   common_construct();

   string strMessage(strMessageParam);

   strMessage.replace_ci("<br>", " \n");

   m_stra.add_lines(strMessage);

   ::u32 uType = ((::u32)emessagebox) & 7;

   switch(uType)
   {
      case MB_OKCANCEL:
         m_buttona.add(__new(x11Button("OK", "ok")));
         m_buttona.add(__new(x11Button("Cancel", "cancel")));
         break;
      case MB_ABORTRETRYIGNORE:
         m_buttona.add(__new(x11Button("Abort", "abort")));
         m_buttona.add(__new(x11Button("Retry", "retry")));
         m_buttona.add(__new(x11Button("Ignore", "ignore")));
         break;
      case MB_YESNOCANCEL:
         m_buttona.add(__new(x11Button("Yes", "yes")));
         m_buttona.add(__new(x11Button("No", "no")));
         m_buttona.add(__new(x11Button("Cancel", "cancel")));
         break;
      case MB_YESNO:
         m_buttona.add(__new(x11Button("Yes", "yes")));
         m_buttona.add(__new(x11Button("No", "no")));
         break;
      case MB_RETRYCANCEL:
         m_buttona.add(__new(x11Button("Retry", "retry")));
         m_buttona.add(__new(x11Button("Cancel", "cancel")));
         break;
      case MB_CANCELTRYCONTINUE:
         m_buttona.add(__new(x11Button("Cancel", "cancel")));
         m_buttona.add(__new(x11Button("Try", "try")));
         m_buttona.add(__new(x11Button("Continue", "continue")));
         break;
      default:
         m_buttona.add(__new(x11Button("OK", "ok")));
         break;
   }

}


void simple_ui_display::common_construct()
{

   m_iMarginTop = 40;
   m_iMarginLine = 10;
   m_listMissingCharset = NULL;

}


simple_ui_display::~ simple_ui_display()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   XFreeStringList(m_listMissingCharset);
   XDestroyWindow(pdisplay, m_window);
   XFreeFontSet(pdisplay, m_fs);
   XFreeColormap(pdisplay, m_colormap);

   XUnlockDisplay(pdisplay);

}


GC x11_create_gc(Colormap colormap, Display* pdisplay, Window window, byte a, byte r, byte g, byte b)
{

   GC gc = XCreateGC(pdisplay, window, 0, 0);

   COLORREF cr = ARGB(a, r * a / 255, g * a / 255, b * a / 255);

   XSetForeground (pdisplay, gc, cr);

   return gc;

}


void x11_message_box(const string & str, const string & strTitle, ::emessagebox emessagebox, ::callback callback)
{

   defer_init_x11();

   auto pdisplay = __new(simple_ui_display(str, strTitle, emessagebox, callback));

   pdisplay->show();

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


::size x11_text_extents(XFontSet fs, string_array & stra, int iMargin)
{

   XRectangle rect  = {};

   ::size size;

   for(auto & str: stra)
   {

      wstring wstr(str);

      XwcTextExtents(fs, wstr, wstr.get_length(), &rect, NULL);

      size.cx = max(size.cx, rect.width + iMargin * 2);

      size.cy = max(size.cy, rect.height + iMargin);

   }

   size.cy *= stra.get_count() * 2;

   return size;

}




void simple_ui_display::on_expose()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XLockDisplay(pdisplay);

   try
   {

      XSync(pdisplay, False);

      GC gc = create_gc();

      COLORREF crBk = get_simple_ui_color(::user::element_background);

      crBk = argb_swap_rb(crBk);

      XSetForeground(pdisplay, gc, crBk);

      XFillRectangle(pdisplay, m_window, gc, 0, 0, m_size.cx, m_size.cy);

      int iFontHeight;

      auto gcontext = XGContextFromGC(gc);

      COLORREF crText = get_simple_ui_color(::user::element_text);

      crText = argb_swap_rb(crText);

      XSetForeground(pdisplay, gc, crText);

      if(::user::is_app_dark_mode())
      {

         m_gcText = x11_create_gc(m_colormap, pdisplay, m_window, 255, 255, 255, 255);
         m_gcTextHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 220, 170, 150);
         //m_gcBar = x11_create_gc(m_colormap, pdisplay, m_window, 255, 240, 240, 240);
         m_gcButton = x11_create_gc(m_colormap, pdisplay, m_window, 255, 120, 120, 120);
         m_gcButtonHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 130, 130, 130);
         m_gcButtonPress = x11_create_gc(m_colormap, pdisplay, m_window, 255, 140, 140, 140);

      }
      else
      {

         m_gcText = x11_create_gc(m_colormap, pdisplay, m_window, 255, 0, 0, 0);
         m_gcTextHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 220, 170, 150);
         //m_gcBar = x11_create_gc(m_colormap, pdisplay, m_window, 255, 240, 240, 240);
         m_gcButton = x11_create_gc(m_colormap, pdisplay, m_window, 255, 190, 190, 190);
         m_gcButtonHover = x11_create_gc(m_colormap, pdisplay, m_window, 255, 200, 200, 200);
         m_gcButtonPress = x11_create_gc(m_colormap, pdisplay, m_window, 255, 210, 210, 210);

      }

      int iY = m_iMarginTop;

      for(auto & str : m_stra)
      {

         str.trim_right();

         wstring wstr = str;

         XwcDrawString(pdisplay, m_window, m_fs, m_gcText,
                     m_iMarginLine, iY,
                     wstr, wstr.get_length());

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

         XRectangle & rText = pbutton->m_rectText;

         if(!pbutton->m_bTextRect)
         {

            pbutton->m_bTextRect = true;

            XwcTextExtents(m_fs, pbutton->m_wstrLabel, pbutton->m_wstrLabel.get_length(), &rText, NULL);

         }

         iMaxButtonWidth = max(iMaxButtonWidth, rText.width);

      }

      for(index iButton = m_buttona.get_upper_bound(); iButton >= 0; iButton--)
      {

         auto pbutton = m_buttona[iButton];

         XRectangle & rText = pbutton->m_rectText;

         ::rect & rButton = pbutton->m_rect;

         rButton.right = right;
         rButton.left = right - iMaxButtonWidth - (m_iMarginLine * 6);
         rButton.top = m_iButtonTop;
         rButton.bottom = m_iButtonTop + m_iButtonHeight;

         GC gc;

         if(pbutton->m_bPress)
         {

            gc = m_gcButtonPress;

         }
         else if(pbutton->m_bHover)
         {

            gc = m_gcButtonHover;

         }
         else
         {

            gc = m_gcButton;

         }

         XFillRectangle(pdisplay, m_window, gc, rButton.left, rButton.top, rButton.width(), rButton.height());

         ::rect rectText(rButton);

         rectText.deflate(m_iMarginLine * 3, m_iMarginLine);

         if(pbutton->m_bPress || pbutton->m_bHover)
         {

            gc = m_gcTextHover;

         }
         else
         {

            gc = m_gcText;

         }

         XwcDrawString(pdisplay, m_window, m_fs, gc,
                     rectText.left + (rectText.width() - rText.width) / 2, rectText.top + m_iButtonHeight - m_iMarginLine * 2,
                     pbutton->m_wstrLabel, pbutton->m_wstrLabel.get_length());

         right = rButton.left - 10;

      }

      XFreeGC(pdisplay, m_gcText);
      XFreeGC(pdisplay, m_gcTextHover);
      //XFreeGC(pdisplay, m_gcBar);
      XFreeGC(pdisplay, m_gcButton);
      XFreeGC(pdisplay, m_gcButtonHover);
      XFreeGC(pdisplay, m_gcButtonPress);

      XFlush(pdisplay);

      XFreeGC(pdisplay, gc);

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

      Visual * pvisual = nullptr;

      int iScreen = DefaultScreen(pdisplay);

      //printf("Default Screen %pdisplay\n", iScreen);

      auto windowRoot = DefaultRootWindow(pdisplay);

      //printf("Default Root Window %" PRId64 "\n", windowRoot);

      int xWindow = 0;

      int yWindow = 0;

      XSetWindowAttributes attr={};

      pvisual = get_32bit_visual(pdisplay);

      auto colormap = XCreateColormap(pdisplay, windowRoot, pvisual, AllocNone);

      int iScreenCount = 0;

      auto pscreens = XineramaQueryScreens(pdisplay, &iScreenCount);

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

      int iMargin = 10;

      char **missingCharset_list = NULL;

      int missingCharset_count = 0;

      m_fs = XCreateFontSet(pdisplay,
         "-*-*-medium-r-*-*-*-140-75-75-*-*-*-*" ,
         &missingCharset_list, &missingCharset_count, NULL);

      if (missingCharset_count)
      {

         fprintf(stderr, "Missing charsets :\n");

         for(int i = 0; i < missingCharset_count; i++)
         {

            fprintf(stderr, "%s\n", missingCharset_list[i]);

         }

         XFreeStringList(missingCharset_list);
      }

      ::size size = x11_text_extents(m_fs, m_stra, iMargin);

      m_iButtonHeight = size.cy / (m_stra.get_count() + 2);

      size.cy += m_iMarginTop + m_iMarginLine;

      m_size = m_size.max(size);

      m_iButtonTop = m_size.cy - m_iButtonHeight - m_iMarginLine * 2;

      m_window = XCreateWindow(
            pdisplay, windowRoot,
            xWindow, yWindow, m_size.cx, m_size.cy, 0,
            32,
            InputOutput,
            pvisual,
            CWColormap |
            CWBorderPixel |
            CWBackPixel |
            CWEventMask,
            &attr);

      //printf("Window created %" PRId64 "\n", m_window);

      XMapWindow(pdisplay, m_window);

      XMoveWindow(pdisplay, m_window, xWindow, yWindow);

      XStoreName(pdisplay, m_window, m_strTitle);

      hook();

   }
   catch(...)
   {

   }

   XUnlockDisplay(pdisplay);

   x11_defer_handle_just_hooks();

   return ::success;

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

CLASS_DECL_ACME string message_box_result_to_string(int iResult);

CLASS_DECL_ACME void x11_message_box(const string & strMessage, const string & strTitle, ::emessagebox emessagebox, ::callback callback);

::estatus os_message_box(oswindow oswindow, const char * pszMessage, const char * pszTitle, ::emessagebox emessagebox, ::callback callback)
{

   x11_message_box(pszMessage, pszTitle, emessagebox, callback);

   return ::success;

}


bool simple_ui_display::on_click(const char * pszResult)
{

   string strResult(pszResult);

   m_callback.receive_response(strResult);

   XUnmapWindow(x11_get_display(), m_window);

   unhook();

   return true;

}




::mutex * g_pmutexX11 = nullptr;


mutex * x11_mutex() {return g_pmutexX11;}


void x11_defer_handle_just_hooks()
{
   if(get_platform_level() <= e_platform_level_apex)
   {
      x11_handle_just_hooks();
   }
}

void x11_handle_just_hooks()
{

   sync_lock sl(x11_mutex());

   Display * pdisplay = x11_get_display();

   XEvent e = {};

#if !defined(RASPBIAN)

   XGenericEventCookie * cookie;

#endif

   while(true)
   {

      XLockDisplay(pdisplay);

      XNextEvent(pdisplay, &e);

      XUnlockDisplay(pdisplay);

      try
      {



         __x11_hook_process_event(pdisplay, e, nullptr);

         if(__x11_hook_list_is_empty())
         {

            break;

         }

      }
      catch(...)
      {

      }

      //XLockDisplay(pdisplay);

   }

   //XUnlockDisplay(pdisplay);

   //output_debug_string("x11_handle_just_hooks end");

}

bool init_x11();

bool g_bInitX11 = false;

void defer_init_x11()
{

   if(!g_bInitX11)
   {

      g_bInitX11 = true;

      init_x11();

   }

}

i32 _c_XErrorHandler(Display * display, XErrorEvent * perrorevent);

bool init_x11()
{

      if(!XInitThreads())
      {

         return false;

      }

      XSetErrorHandler(_c_XErrorHandler);

         g_pmutexX11 = new ::mutex();


return true;
}
