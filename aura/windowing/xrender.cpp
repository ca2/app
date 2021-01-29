// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "platform/config.h"
#include "_windowing.h"
//!!!#include <X11/Xlib.h>
//!!!#include <X11/extensions/Xinerama.h>
//#define pointer x11pointer
//!!!#include <X11/extensions/Xrender.h>

//
//#if defined(RASPBIAN)
//
//Visual * get_32bit_visual(Display * disp)
//{
//
//   // return fallback Visual
//
//   return XDefaultVisual(disp, DefaultScreen(disp));
//
//}
//
//#else
//
////http://rosettacode.org/wiki/Window_creation/X11
//
//Visual * get_32bit_visual(Display * disp)
//{
//
////Window win;
////XSetWindowAttributes attr;
//XWindowAttributes att;
//XVisualInfo *xvi;
//XVisualInfo vi_in;
//int nvi, i, scr = 0;
//XRenderPictFormat *fmt;
//Visual *vis;
//
//
//
//vi_in.screen = scr;
//vi_in.depth = 32;
//vi_in.c_class = TrueColor;
//xvi = XGetVisualInfo(disp,
//                     VisualScreenMask |
//                     VisualDepthMask |
//                     VisualClassMask,
//                     &vi_in,
//                     &nvi);
//if (!xvi) return 0;
//
//vis = NULL;
//for (i = 0; i < nvi; i++)
//  {
//     fmt = XRenderFindVisualFormat(disp, xvi[i].visual);
//     if ((fmt->type == PictTypeDirect) && (fmt->direct.alphaMask))
//       {
//          vis = xvi[i].visual;
//          break;
//       }
//  }
//XFree (xvi);
//
//
//return vis;
//
//}
//
//
//#endif
//
//
//
