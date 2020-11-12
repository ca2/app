#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif
#include "aura/os/linux/_user.h"
#define pointer x11_pointer
#include <X11/extensions/Xrandr.h>
#include <X11/extensions/Xinerama.h>
#undef pointer


CLASS_DECL_AURA int xinerama_get_monitor_count();
CLASS_DECL_AURA int xinerama_get_monitor_rect(index i, RECT32 * prect);

CLASS_DECL_AURA int xinerama_get_screen_size(int& width, int& height);




int xinerama_get_monitor_count()
{

   int heads = 0;

   xdisplay  d;

   if (!d.open(nullptr))
   {

      return 1;

   }

   int dummy1, dummy2;

   if (XineramaQueryExtension(d, &dummy1, &dummy2))
   {

      if (XineramaIsActive(d))
      {

         XineramaScreenInfo *point = XineramaQueryScreens(d, &heads);

         XFree(point);

      }

   }

   return max(1, heads);

}


int xinerama_get_monitor_rect(index iMonitor, RECT32 * prect)
{

   xdisplay  d;

   if (!d.open(nullptr))
   {

      return -1;

   }

   int screen_number = -1;

   int dummy1, dummy2;

   if (XineramaQueryExtension(d, &dummy1, &dummy2))
   {

      if (XineramaIsActive(d))
      {

         int heads = 0;

         XineramaScreenInfo *point = XineramaQueryScreens(d, &heads);

         if (iMonitor >= 0 && iMonitor < heads)
         {

            prect->left = point[iMonitor].x_org;

            prect->top = point[iMonitor].y_org;

            prect->right = prect->left + point[iMonitor].width;

            prect->bottom = prect->top + point[iMonitor].height;

            screen_number = point[iMonitor].screen_number;

         }

         XFree(point);

      }

   }

   if (screen_number >= 0)
   {

      return screen_number;

   }

   int iCount;

   XRRScreenSize * psize = XRRSizes(d.display(), 0, &iCount);

   prect->left = 0;

   prect->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->display()));

   prect->top = 0;

   prect->bottom = HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

   return 0;

}


int xinerama_get_screen_size(int& width, int& height)
{

   int num_sizes;
   Rotation original_rotation;

   Display *dpy = XOpenDisplay(nullptr);
   Window root = RootWindow(dpy, 0);
   XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
   //
   //     GET CURRENT RESOLUTION AND FREQUENCY
   //
   XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
   short original_rate = XRRConfigCurrentRate(conf);
   SizeID original_size_id = XRRConfigCurrentConfiguration(conf, &original_rotation);

   width = xrrs[original_size_id].width;
   height = xrrs[original_size_id].height;

   XCloseDisplay(dpy);
   return 0;    //Return a value that can be used for error checking.

}




// it doesn't work for final purpose, but it has example on how to "sort" rectangles with stability
::array < rect > get_ordered_monitor_recta(::layered * pobjectContext)
{

   index iMonitor = 0;

   ::array < ::rect > rectaMonitor;

   ::aura::session * psession = Sess(__object(pobjectContext)->get_context_session());

   ::count cMonitor = psession->get_monitor_count();

   ::rect rectMonitor;

   rectaMonitor.set_size(cMonitor);

   for(; iMonitor < cMonitor; iMonitor++)
   {

      psession->get_monitor_rect(iMonitor, &rectMonitor);

      rectaMonitor[iMonitor] = rectMonitor;

      output_debug_string(__str(rectMonitor.left));

      output_debug_string(__str(rectMonitor.top));

      output_debug_string(__str(rectMonitor.right));

      output_debug_string(__str(rectMonitor.bottom));

   }

   // sort horizontally

   ::sort::pred_stable_sort(rectaMonitor, [](auto & r1, auto & r2) { return r1.left <= r2.left; });

   // sort vertically in stable way

   ::sort::pred_stable_sort(rectaMonitor, [](auto & r1, auto & r2) { return r1.top <= r2.top; });

   for(auto & rectItem: rectaMonitor)
   {

      output_debug_string(__str(rectItem.left));

      output_debug_string(__str(rectItem.top));

      output_debug_string(__str(rectItem.right));

      output_debug_string(__str(rectItem.bottom));

   }

   return rectaMonitor;

}

// it doesn't work for final purpose,
// but it calls function that "sorts" rectangles with stability
int get_best_ordered_monitor(::user::interaction * pinteraction, RECT32 * prectRet)
{

   auto rectaOrdered = get_ordered_monitor_recta(pinteraction->get_context_application());

   index iJustForComparison = pinteraction->best_monitor(prectRet, nullptr, FALSE, 0, zorder_none);

   index iOrdered = rectaOrdered.pred_find_first([&](auto & rectMonitorSorted) { return rectMonitorSorted == *prectRet; });

   output_debug_string(__str(iJustForComparison));

   output_debug_string(__str(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pinteraction, const ::rect & rectParam, RECT32 * prectRet)
{

   ::null_rect(prectRet);

   ::rect rect(rectParam);

   if(rect == nullptr)
   {

      rect = prectRet;

   }

   index iOrdered = pinteraction->best_monitor(prectRet, rect, false, 0, zorder_none);

   ::count cMonitor = xinerama_get_monitor_count();

   ::rect rectMonitor;

   for(index i = 0; i < cMonitor; i++)
   {

      int iScreen = xinerama_get_monitor_rect(i, &rectMonitor);

      if(rectMonitor == rect)
      {

         iOrdered = iScreen;

         break;

      }

   }

   output_debug_string(__str(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pinteraction, RECT32 * prectRet)
{

   return best_xinerama_monitor(pinteraction, nullptr, prectRet);

}


int get_best_monitor(::user::interaction * pinteraction, const ::rect & rectParam, RECT32 * prectRet)
{

   ::rect rNull = nullptr;

   ::rect rect(rectParam);

   if(rect == nullptr)
   {

      rect = rNull;

   }

   index i = pinteraction->best_monitor(prectRet, rect, FALSE, 0, zorder_none);

   return i;

}


int get_best_monitor(::user::interaction * pinteraction, RECT32 * prectRet)
{

   return get_best_monitor(pinteraction, nullptr, prectRet);

}
