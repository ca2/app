//
//  macos_user.h
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/10/17.
//

#pragma once
//
//#ifdef __OBJC__
//
//#include "mm_oswindow.h"
//
//#else
//
////#include "oswindow_data.h"
//
//#endif
//
////#include "windowing.h"
//
//
//#include "window_impl.h"
//
//
//::i32 axis_main_command_line(const ::scoped_string & scopedstrParams, ::i32 argc, char_pointer argv[]);
//
//
//#ifdef cplusplus
//
//
//namespace macos
//{
//   
//   CGFloat get_system_main_menu_bar_height();
//   CGFloat get_system_dock_height();
//   
//   
//} // namespace macos
//
//
//#endif
//
////
////  c_os_cross_win_user_internal.h
////  c
////
////  Created by Snow Leopard User on 06/11/2011.
////  Copyright 2011 __MyCompanyName__. All rights reserved.
////
//
//
///*typedef struct tag_WINDOW
// {
// 
// 
// WindowRef      m_windowref;
// void *         m_pnswindow;
// 
// 
// 
// } WINDOW, * LPWINDOW;
// 
// typedef LPWINDOW oswindow;
// 
// typedef ::i32 ::i32;
// 
// typedef struct tagRECT
// {
// ::i32    left;
// ::i32    top;
// ::i32    right;
// ::i32    bottom;
// } const i32_rectangle &, *PRECT, *NPRECT, *::i32_rectangle *;
// 
// typedef const i32_rectangle & * const i32_rectangle &;
// 
// 
// 
// #pragma once
// */
////
////CGContextRef get_nswindow_cgcontext(oswindow pnswindow);
////
////
////i32_bool get_nswindow_rect(oswindow hwnd,::i32_rectangle * prectangle);
////
//
//
////inline ::i32 wxRound(::f64 x)
////{
////#if defined(HAVE_ROUND)
////   return ::i32(round(x));
////#else
////   return (::i32)(x < 0 ? x - 0.5 : x + 0.5);
////#endif
////}
//
////#include <X11/Xlib.h>
////#include <X11/Xutil.h>
//
///*  ---------------------------------------------------------------------------- */
///*  standard wxWidgets types */
///*  ---------------------------------------------------------------------------- */
//
///*  the type for screen and DC coordinates */
//typedef ::i32 wxCoord;
//
//
////enum { wxDefaultCoord = -1 };
//
//
////class CLASS_DECL_ACME wxSize
////{
////public:
////   // members are public for compatibility, don't use them directly.
////   ::i32 x,y;
////   
////   // constructors
////   wxSize(): x(0),y(0) { }
////   wxSize(::i32 xx,::i32 yy): x(xx),y(yy) { }
////   
////   // no copy ctor or assignment operator - the defaults are ok
////   
////   bool operator==(const wxSize& sz) const { return x == sz.x && y == sz.y; }
////   bool operator!=(const wxSize& sz) const { return x != sz.x || y != sz.y; }
////   
////   wxSize operator +(const wxSize& sz) const { return wxSize(x + sz.x,y + sz.y); }
////   wxSize operator-(const wxSize& sz) const { return wxSize(x - sz.x,y - sz.y); }
////   wxSize operator/(::i32 i) const { return wxSize(x / i,y / i); }
////   wxSize operator*(::i32 i) const { return wxSize(x * i,y * i); }
////   
////   wxSize& operator +=(const wxSize& sz) { x += sz.x; y += sz.y; return *this; }
////   wxSize& operator-=(const wxSize& sz) { x -= sz.x; y -= sz.y; return *this; }
////   wxSize& operator/=(const ::i32 i) { x /= i; y /= i; return *this; }
////   wxSize& operator*=(const ::i32 i) { x *= i; y *= i; return *this; }
////   
////   void IncTo(const wxSize& sz)
////   {
////      if(sz.x > x) x = sz.x; if(sz.y > y) y = sz.y;
////   }
////   void DecTo(const wxSize& sz)
////   {
////      if(sz.x < x) x = sz.x; if(sz.y < y) y = sz.y;
////   }
////   
////   void IncBy(::i32 Δx,::i32 Δy) { x += Δx; y += Δy; }
////   void IncBy(const wxSize& sz) { IncBy(sz.x,sz.y); }
////   void IncBy(::i32 d) { IncBy(d,d); }
////   
////   void DecBy(::i32 Δx,::i32 Δy) { IncBy(-Δx,-Δy); }
////   void DecBy(const wxSize& sz) { DecBy(sz.x,sz.y); }
////   void DecBy(::i32 d) { DecBy(d,d); }
////   
////   
////   wxSize& Scale(::f32 xscale,::f32 yscale)
////   {
////      x = (::i32)(x*xscale); y = (::i32)(y*yscale); return *this;
////   }
////   
////   // accessors
////   void Set(::i32 xx,::i32 yy) { x = xx; y = yy; }
////   void SetWidth(::i32 w) { x = w; }
////   void SetHeight(::i32 h) { y = h; }
////   
////   ::i32 GetWidth() const { return x; }
////   ::i32 GetHeight() const { return y; }
////   
////   bool IsFullySpecified() const { return x != wxDefaultCoord && y != wxDefaultCoord; }
////   
////   // combine this i32_size with the other one replacing the default (i.e. equal
////   // to wxDefaultCoord) components of this matter with those of the other
////   void SetDefaults(const wxSize& size)
////   {
////      if(x == wxDefaultCoord)
////         x = size.cx;
////      if(y == wxDefaultCoord)
////         y = size.cy;
////   }
////   
////   // compatibility
////   ::i32 GetX() const { return x; }
////   ::i32 GetY() const { return y; }
////};
////
////
////class CLASS_DECL_ACME wxPoint
////{
////public:
////   ::i32 x,y;
////   
////   wxPoint(): x(0),y(0) { }
////   wxPoint(::i32 xx,::i32 yy): x(xx),y(yy) { }
////   
////   // no copy ctor or assignment operator - the defaults are ok
////   
////   // comparison
////   bool operator==(const wxPoint& point) const { return x == point.x && y == point.y; }
////   bool operator!=(const wxPoint& point) const { return !(*this == point); }
////   
////   // arithmetic operations (component wise)
////   wxPoint operator +(const wxPoint& point) const { return wxPoint(x + point.x,y + point.y); }
////   wxPoint operator-(const wxPoint& point) const { return wxPoint(x - point.x,y - point.y); }
////   
////   wxPoint& operator +=(const wxPoint& point) { x += point.x; y += point.y; return *this; }
////   wxPoint& operator-=(const wxPoint& point) { x -= point.x; y -= point.y; return *this; }
////   
////   wxPoint& operator +=(const wxSize& s) { x += s.GetWidth(); y += s.GetHeight(); return *this; }
////   wxPoint& operator-=(const wxSize& s) { x -= s.GetWidth(); y -= s.GetHeight(); return *this; }
////   
////   wxPoint operator +(const wxSize& s) const { return wxPoint(x + s.GetWidth(),y + s.GetHeight()); }
////   wxPoint operator-(const wxSize& s) const { return wxPoint(x - s.GetWidth(),y - s.GetHeight()); }
////   
////   wxPoint operator-() const { return wxPoint(-x,-y); }
////};
////
////
////class CLASS_DECL_ACME device_context
////{
////public:
////   
////   
////   CGrafPtr          m_windowPort;
////   CGrafPtr          m_savedPort;
////   oswindow             m_window;
////   Rect              m_portBounds;
////   bool              m_wasSwapped;
////   
////   color32_t          m_colorText;
////   color32_t          m_colorBk;
////   CGColorRef        m_cgcolorrefText;
////   CGColorRef        m_cgcolorrefBk;
////   CTFontRef         m_ctfontref;
////   
////   // wxBase Begin
////   
////   // coordinate system variables
////   
////   // TODO ::i16 descriptions of what exactly they are would be nice...
////   
////   wxCoord m_logicalOriginX,m_logicalOriginY;
////   wxCoord m_deviceOriginX,m_deviceOriginY;
////   
////   ::f64 m_logicalScaleX,m_logicalScaleY;
////   ::f64 m_userScaleX,m_userScaleY;
////   ::f64 m_scaleX,m_scaleY;
////   
////   // Used by SetAxisOrientation() to invert the axes
////   ::i32 m_signX,m_signY;
////   
////   // bounding and clipping boxes
////   wxCoord m_minX,m_minY,m_maxX,m_maxY;
////   wxCoord m_clipX1,m_clipY1,m_clipX2,m_clipY2;
////   
////   // wxBase End
////   
////   
////   
////   // in order to preserve the const inheritance of the virtual functions,
////   // we have to use mutable variables starting from CWPro 5
////   wxPoint                         m_macLocalOrigin;
////   mutable void *                  m_macATSUIStyle;
////   
////   
////   
////   CGContextRef    m_cgcontext;
////   
////   
////   
////   
////   device_context();
////   
////   
////   wxCoord XDEV2LOG(wxCoord x) const
////   {
////      return wxRound((::f64)(x - m_deviceOriginX) / m_scaleX) * m_signX + m_logicalOriginX;
////   }
////   wxCoord XDEV2LOGREL(wxCoord x) const
////   {
////      return wxRound((::f64)(x) / m_scaleX);
////   }
////   wxCoord YDEV2LOG(wxCoord y) const
////   {
////      return wxRound((::f64)(y - m_deviceOriginY) / m_scaleY) * m_signY + m_logicalOriginY;
////   }
////   wxCoord YDEV2LOGREL(wxCoord y) const
////   {
////      return wxRound((::f64)(y) / m_scaleY);
////   }
////   wxCoord XLOG2DEV(wxCoord x) const
////   {
////      return wxRound((::f64)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX;
////   }
////   wxCoord XLOG2DEVREL(wxCoord x) const
////   {
////      return wxRound((::f64)(x)* m_scaleX);
////   }
////   wxCoord YLOG2DEV(wxCoord y) const
////   {
////      return wxRound((::f64)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY;
////   }
////   wxCoord YLOG2DEVREL(wxCoord y) const
////   {
////      return wxRound((::f64)(y)* m_scaleY);
////   }
////   
////   wxCoord XLOG2DEVMAC(wxCoord x) const
////   {
////      return wxRound((::f64)(x - m_logicalOriginX) * m_scaleX) * m_signX + m_deviceOriginX + m_macLocalOrigin.x;
////   }
////   
////   wxCoord YLOG2DEVMAC(wxCoord y) const
////   {
////      return wxRound((::f64)(y - m_logicalOriginY) * m_scaleY) * m_signY + m_deviceOriginY + m_macLocalOrigin.y;
////   }
////   
////   
////   
////};
////
////
////
////
////CGColorRef cg_create_color(color32_t crText);
////i32_bool cg_release_color(CGColorRef colorref);
//
////
////  c_os_win_user.h
////  c
////
////  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/30/11.
////  Copyright (c) 2011 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//////
////i32_bool set_nswindow_frame(oswindow hwnd, const ::i32_rectangle * prectangle, ::i32 iDisplay);
////i32_bool move_nswindow(oswindow hwnd,::i32 x,::i32 y);
////i32_bool make_key_and_order_front_nswindow(oswindow hwnd);
////i32_bool order_front_nswindow(oswindow hwnd);
////i32_bool nswindow_set_level_normal(oswindow hwnd);
////i32_bool nswindow_set_level_floating(oswindow hwnd);
////i32_bool nswindow_set_level_main_menu(oswindow hwnd);
////i32_bool nswindow_is_level_normal(oswindow hwnd);
////i32_bool nswindow_is_level_floating(oswindow hwnd);
////i32_bool nswindow_is_level_main_menu(oswindow hwnd);
//