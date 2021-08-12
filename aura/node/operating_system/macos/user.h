//
//  macos_user.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 21/10/17.
//

#pragma once

//#ifdef __OBJC__
//
////#include "mm_oswindow.h"
//
//#else
//
//#include "oswindow_data.h"
//
//#endif

#include "windowing.h"


//#include "window_impl.h"


i32 axis_main_command_line(const ::string & pszParams, int argc, char *argv[]);


#ifdef cplusplus


namespace macos
{
   
   CGFloat get_system_main_menu_bar_height();
   CGFloat get_system_dock_height();
   
   
} // namespace macos


#endif

//
//  c_os_cross_win_user_internal.h
//  c
//
//  Created by Snow Leopard User on 06/11/2011.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


/*typedef struct tag_WINDOW
 {
 
 
 WindowRef      m_windowref;
 void *         m_pnswindow;
 
 
 
 } WINDOW, * LPWINDOW;
 
 typedef LPWINDOW oswindow;
 
 typedef int ::i32;
 
 typedef struct tagRECT
 {
 ::i32    left;
 ::i32    top;
 ::i32    right;
 ::i32    bottom;
 } const rectangle_i32 &, *PRECT, *NPRECT, *RECTANGLE_I32 *;
 
 typedef const rectangle_i32 & * const rectangle_i32 &;
 
 
 
 #pragma once
 */

CGContextRef get_nswindow_cgcontext(oswindow pnswindow);


int_bool get_nswindow_rect(oswindow hwnd,RECTANGLE_I32 * prectangle);



//inline int wxRound(double x)
//{
//#if defined(HAVE_ROUND)
//   return int(round(x));
//#else
//   return (int)(x < 0 ? x - 0.5 : x + 0.5);
//#endif
//}

//#include <X11/Xlib.h>
//#include <X11/Xutil.h>

/*  ---------------------------------------------------------------------------- */
/*  standard wxWidgets types */
/*  ---------------------------------------------------------------------------- */

/*  the type for screen and DC coordinates */
typedef int wxCoord;


//enum { wxDefaultCoord = -1 };


//class CLASS_DECL_AURA wxSize
//{
//public:
//   // members are public for compatibility, don't use them directly.
//   int x,y;
//   
//   // constructors
//   wxSize(): x(0),y(0) { }
//   wxSize(int xx,int yy): x(xx),y(yy) { }
//   
//   // no copy ctor or assignment operator - the defaults are ok
//   
//   bool operator==(const wxSize& sz) const { return x == sz.x && y == sz.y; }
//   bool operator!=(const wxSize& sz) const { return x != sz.x || y != sz.y; }
//   
//   wxSize operator+(const wxSize& sz) const { return wxSize(x + sz.x,y + sz.y); }
//   wxSize operator-(const wxSize& sz) const { return wxSize(x - sz.x,y - sz.y); }
//   wxSize operator/(int i) const { return wxSize(x / i,y / i); }
//   wxSize operator*(int i) const { return wxSize(x * i,y * i); }
//   
//   wxSize& operator+=(const wxSize& sz) { x += sz.x; y += sz.y; return *this; }
//   wxSize& operator-=(const wxSize& sz) { x -= sz.x; y -= sz.y; return *this; }
//   wxSize& operator/=(const int i) { x /= i; y /= i; return *this; }
//   wxSize& operator*=(const int i) { x *= i; y *= i; return *this; }
//   
//   void IncTo(const wxSize& sz)
//   {
//      if(sz.x > x) x = sz.x; if(sz.y > y) y = sz.y;
//   }
//   void DecTo(const wxSize& sz)
//   {
//      if(sz.x < x) x = sz.x; if(sz.y < y) y = sz.y;
//   }
//   
//   void IncBy(int dx,int dy) { x += dx; y += dy; }
//   void IncBy(const wxSize& sz) { IncBy(sz.x,sz.y); }
//   void IncBy(int d) { IncBy(d,d); }
//   
//   void DecBy(int dx,int dy) { IncBy(-dx,-dy); }
//   void DecBy(const wxSize& sz) { DecBy(sz.x,sz.y); }
//   void DecBy(int d) { DecBy(d,d); }
//   
//   
//   wxSize& Scale(float xscale,float yscale)
//   {
//      x = (int)(x*xscale); y = (int)(y*yscale); return *this;
//   }
//   
//   // accessors
//   void Set(int xx,int yy) { x = xx; y = yy; }
//   void SetWidth(int w) { x = w; }
//   void SetHeight(int h) { y = h; }
//   
//   int GetWidth() const { return x; }
//   int GetHeight() const { return y; }
//   
//   bool IsFullySpecified() const { return x != wxDefaultCoord && y != wxDefaultCoord; }
//   
//   // combine this size_i32 with the other one replacing the default (i.e. equal
//   // to wxDefaultCoord) components of this object with those of the other
//   void SetDefaults(const wxSize& size)
//   {
//      if(x == wxDefaultCoord)
//         x = size.x;
//      if(y == wxDefaultCoord)
//         y = size.y;
//   }
//   
//   // compatibility
//   int GetX() const { return x; }
//   int GetY() const { return y; }
//};
//
//
//class CLASS_DECL_AURA wxPoint
//{
//public:
//   int x,y;
//   
//   wxPoint(): x(0),y(0) { }
//   wxPoint(int xx,int yy): x(xx),y(yy) { }
//   
//   // no copy ctor or assignment operator - the defaults are ok
//   
//   // comparison
//   bool operator==(const wxPoint& point) const { return x == point.x && y == point.y; }
//   bool operator!=(const wxPoint& point) const { return !(*this == point); }
//   
//   // arithmetic operations (component wise)
//   wxPoint operator+(const wxPoint& point) const { return wxPoint(x + point.x,y + point.y); }
//   wxPoint operator-(const wxPoint& point) const { return wxPoint(x - point.x,y - point.y); }
//   
//   wxPoint& operator+=(const wxPoint& point) { x += point.x; y += point.y; return *this; }
//   wxPoint& operator-=(const wxPoint& point) { x -= point.x; y -= point.y; return *this; }
//   
//   wxPoint& operator+=(const wxSize& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
//   wxPoint& operator-=(const wxSize& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }
//   
//   wxPoint operator+(const wxSize& s) const { return wxPoint(x + s.GetWidth(),y + s.GetHeight()); }
//   wxPoint operator-(const wxSize& s) const { return wxPoint(x - s.GetWidth(),y - s.GetHeight()); }
//   
//   wxPoint operator-() const { return wxPoint(-x,-y); }
//};
//
//
//class CLASS_DECL_AURA device_context
//{
//public:
//   
//   
//   CGrafPtr          m_windowPort;
//   CGrafPtr          m_savedPort;
//   oswindow             m_window;
//   Rect              m_portBounds;
//   bool              m_wasSwapped;
//   
//   color32_t          m_colorText;
//   color32_t          m_colorBk;
//   CGColorRef        m_cgcolorrefText;
//   CGColorRef        m_cgcolorrefBk;
//   CTFontRef         m_ctfontref;
//   
//   // wxBase Begin
//   
//   // coordinate system variables
//   
//   // TODO short descriptions of what exactly they are would be nice...
//   
//   wxCoord m_logicalOriginX,m_logicalOriginY;
//   wxCoord m_deviceOriginX,m_deviceOriginY;
//   
//   double m_logicalScaleX,m_logicalScaleY;
//   double m_userScaleX,m_userScaleY;
//   double m_scaleX,m_scaleY;
//   
//   // Used by SetAxisOrientation() to invert the axes
//   int m_signX,m_signY;
//   
//   // bounding and clipping boxes
//   wxCoord m_minX,m_minY,m_maxX,m_maxY;
//   wxCoord m_clipX1,m_clipY1,m_clipX2,m_clipY2;
//   
//   // wxBase End
//   
//   
//   
//   // in order to preserve the const inheritance of the virtual functions,
//   // we have to use mutable variables starting from CWPro 5
//   wxPoint                         m_macLocalOrigin;
//   mutable void *                  m_macATSUIStyle;
//   
//   
//   
//   CGContextRef    m_cgcontext;
//   
//   
//   
//   
//   device_context();
//   
//   
//   wxCoord XDEV2LOG(wxCoord x) const
//   {
//      return wxRound((double)(x - m_deviceOriginX) / m_scaleX) * m_signX + m_logicalOriginX;
//   }
//   wxCoord XDEV2LOGREL(wxCoord x) const
//   {
//      return wxRound((double)(x) / m_scaleX);
//   }
//   wxCoord YDEV2LOG(wxCoord y) const
//   {
//      return wxRound((double)(y - m_deviceOriginY) / m_scaleY) * m_signY + m_logicalOriginY;
//   }
//   wxCoord YDEV2LOGREL(wxCoord y) const
//   {
//      return wxRound((double)(y) / m_scaleY);
//   }
//   wxCoord XLOG2DEV(wxCoord x) const
//   {
//      return wxRound((double)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX;
//   }
//   wxCoord XLOG2DEVREL(wxCoord x) const
//   {
//      return wxRound((double)(x)* m_scaleX);
//   }
//   wxCoord YLOG2DEV(wxCoord y) const
//   {
//      return wxRound((double)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY;
//   }
//   wxCoord YLOG2DEVREL(wxCoord y) const
//   {
//      return wxRound((double)(y)* m_scaleY);
//   }
//   
//   wxCoord XLOG2DEVMAC(wxCoord x) const
//   {
//      return wxRound((double)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX + m_macLocalOrigin.x;
//   }
//   
//   wxCoord YLOG2DEVMAC(wxCoord y) const
//   {
//      return wxRound((double)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY + m_macLocalOrigin.y;
//   }
//   
//   
//   
//};
//
//
//
//
//CGColorRef cg_create_color(color32_t crText);
//int_bool cg_release_color(CGColorRef colorref);





//
//  c_os_win_user.h
//  c
//
//  Created by Camilo Sasuke Tsumanuma on 12/30/11.
//  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//




int_bool set_nswindow_frame(oswindow hwnd, const RECTANGLE_I32 * prectangle, int iDisplay);
int_bool move_nswindow(oswindow hwnd,int x,int y);
int_bool make_key_and_order_front_nswindow(oswindow hwnd);
int_bool order_front_nswindow(oswindow hwnd);
int_bool nswindow_set_level_normal(oswindow hwnd);
int_bool nswindow_set_level_floating(oswindow hwnd);
int_bool nswindow_set_level_main_menu(oswindow hwnd);
int_bool nswindow_is_level_normal(oswindow hwnd);
int_bool nswindow_is_level_floating(oswindow hwnd);
int_bool nswindow_is_level_main_menu(oswindow hwnd);




