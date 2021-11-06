//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>

typedef Window oswindow;

class CLASS_DECL_____ device_context
{
public:

   Display *   m_display;
   Drawable    m_d;
   GC          m_gc;
   oswindow        m_hwnd;


   device_context()
   {
      m_display   = nullptr;
      m_d         = 0;
      m_gc        = nullptr;
      m_hwnd      = nullptr;
   }

};

