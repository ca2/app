#pragma once


// Ubuntu apt-get install libx11-dev
//!!!#include <X11/Xlib.h>
//!!!#include <X11/Xutil.h>
// Ubuntu apt-get install libcairo2-dev

#include "solaris_cross_win_gdi.h"

//#include "graphics/draw2d_xlib/draw2d_xlib.h"



void set(XColor & color, color32_t cr);





/*
Hi,
if you want to make a argb window using xlib/Qt here is the code i use
/**files to include from xlib*/
/*#include <X11/extensions/Xrender.h>
#include <X11/Xlib.h>

/**getting display*/
/*Display *dpy = XOpenDisplay ( 0 ); // open default display
    if ( !dpy ) {
        qWarning ( "Cannot connect to the X server" );
        //exit ( 1 );
    }

/**code for argb draw2d*/
/*  bool  argbVisual=false;
  i32 screen = DefaultScreen ( dpy );
  Colormap colormap = 0;
  Visual *draw2d = 0;
  i32 eventBase, errorBase;

  if ( XRenderQueryExtension ( dpy, &eventBase, &errorBase ) ) {
      qWarning ("You have argb support");
      i32 nvi;
      XVisualInfo templ;
      templ.screen  = screen;
      templ.depth   = 32;
      templ.c_class = TrueColor;
      XVisualInfo *xvi = XGetVisualInfo ( dpy, VisualScreenMask |
                                          VisualDepthMask |
                                          VisualClassMask, &templ, &nvi );

      for ( i32 i = 0; i < nvi; ++i ) {
          XRenderPictFormat *format = XRenderFindVisualFormat ( dpy,
                                      xvi[i].draw2d );
          if ( format->type == PictTypeDirect && format->direct.alphaMask
) {
              draw2d = xvi[i].draw2d;
              colormap = XCreateColormap ( dpy, RootWindow ( dpy, screen
),
                                           draw2d, AllocNone );
              argbVisual=true;
              break;
          }
      }
  }
  /**end of code for argb draw2d*/






void set(XColor & color, color32_t cr);





/*
Hi,
if you want to make a argb window using xlib/Qt here is the code i use
/**files to include from xlib*/
/*#include <X11/extensions/Xrender.h>
#include <X11/Xlib.h>

/**getting display*/
/*Display *dpy = XOpenDisplay ( 0 ); // open default display
    if ( !dpy ) {
        qWarning ( "Cannot connect to the X server" );
        //exit ( 1 );
    }

/**code for argb draw2d*/
/*  bool  argbVisual=false;
  i32 screen = DefaultScreen ( dpy );
  Colormap colormap = 0;
  Visual *draw2d = 0;
  i32 eventBase, errorBase;

  if ( XRenderQueryExtension ( dpy, &eventBase, &errorBase ) ) {
      qWarning ("You have argb support");
      i32 nvi;
      XVisualInfo templ;
      templ.screen  = screen;
      templ.depth   = 32;
      templ.c_class = TrueColor;
      XVisualInfo *xvi = XGetVisualInfo ( dpy, VisualScreenMask |
                                          VisualDepthMask |
                                          VisualClassMask, &templ, &nvi );

      for ( i32 i = 0; i < nvi; ++i ) {
          XRenderPictFormat *format = XRenderFindVisualFormat ( dpy,
                                      xvi[i].draw2d );
          if ( format->type == PictTypeDirect && format->direct.alphaMask
) {
              draw2d = xvi[i].draw2d;
              colormap = XCreateColormap ( dpy, RootWindow ( dpy, screen
),
                                           draw2d, AllocNone );
              argbVisual=true;
              break;
          }
      }
  }
  /**end of code for argb draw2d*/




