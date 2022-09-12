#include "framework.h"
//#include "base/user/user/_component.h"
#include "aura/os/linux/_user.h"
//!!!#define pointer x11_pointer
//!!!#include <X11/extensions/Xrandr.h>
//!!!#include <X11/extensions/Xinerama.h>
//!!!#undef pointer


CLASS_DECL_AURA int xinerama_get_monitor_count();
CLASS_DECL_AURA int xinerama_get_monitor_rect(index i, RECTANGLE_I32 * prectangle);

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

   return maximum(1, heads);

}


int xinerama_get_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)
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

            prectangle->left = point_i32[iMonitor].x_org;

            prectangle->top = point_i32[iMonitor].y_org;

            prectangle->right = prectangle->left + point_i32[iMonitor].width;

            prectangle->bottom = prectangle->top + point_i32[iMonitor].height;

            screen_number = point_i32[iMonitor].screen_number;

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

   prectangle->left = 0;

   prectangle->right = WidthOfScreen(DefaultScreenOfDisplay(d.m_pdata->display()));

   prectangle->top = 0;

   prectangle->bottom = HeightOfScreen(DefaultScreenOfDisplay(d.m_pdata->m_pdisplay));

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
::array < rectangle_i32 > get_ordered_monitor_recta(::object * pobject)
{

   index iMonitor = 0;

   ::array < ::rectangle_i32 > rectaMonitor;

   ::aura::session * psession = Sess(__object(pobject)->get_session());

   ::count cMonitor = psession->get_monitor_count();

   ::rectangle_i32 rectangleMonitor;

   rectaMonitor.set_size(cMonitor);

   for(; iMonitor < cMonitor; iMonitor++)
   {

      psession->get_monitor_rectangle(iMonitor, &rectangleMonitor);

      rectaMonitor[iMonitor] = rectangleMonitor;

      output_debug_string(__string(rectangleMonitor.left));

      output_debug_string(__string(rectangleMonitor.top));

      output_debug_string(__string(rectangleMonitor.right));

      output_debug_string(__string(rectangleMonitor.bottom));

   }

   // sort horizontally

   ::sort::predicate_stable_sort(rectaMonitor, [](auto & r1, auto & r2) { return r1.left <= r2.left; });

   // sort vertically in stable way

   ::sort::predicate_stable_sort(rectaMonitor, [](auto & r1, auto & r2) { return r1.top <= r2.top; });

   for(auto & rectangleItem: rectaMonitor)
   {

      output_debug_string(__string(rectangleItem.left));

      output_debug_string(__string(rectangleItem.top));

      output_debug_string(__string(rectangleItem.right));

      output_debug_string(__string(rectangleItem.bottom));

   }

   return rectaMonitor;

}

// it doesn't work for final purpose,
// but it calls function that "sorts" rectangles with stability
int get_best_ordered_monitor(::user::interaction * pinteraction, RECTANGLE_I32 * prectRet)
{

   auto rectaOrdered = get_ordered_monitor_recta(pinteraction->get_app());

   index iJustForComparison = pinteraction->best_monitor(prectRet, nullptr, e_display_none, e_activation_default, zorder_none);

   index iOrdered = rectaOrdered.predicate_find_first([&](auto & rectangleMonitorSorted) { return rectangleMonitorSorted == *prectRet; });

   output_debug_string(__string(iJustForComparison));

   output_debug_string(__string(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pinteraction, const ::rectangle_i32 & rectangleParam, RECTANGLE_I32 * prectRet)
{

   ::null_rect(prectRet);

   ::rectangle_i32 rectangle(rectangleParam);

   if(rectangle_i32 == nullptr)
   {

      rectangle = prectRet;

   }

   index iOrdered = pinteraction->best_monitor(prectRet, rectangle, false, e_activation_default, zorder_none);

   ::count cMonitor = xinerama_get_monitor_count();

   ::rectangle_i32 rectangleMonitor;

   for(index i = 0; i < cMonitor; i++)
   {

      int iScreen = xinerama_get_monitor_rect(i, &rectangleMonitor);

      if(rectangleMonitor == rectangle_i32)
      {

         iOrdered = iScreen;

         break;

      }

   }

   output_debug_string(__string(iOrdered));

   return iOrdered;

}


int best_xinerama_monitor(::user::interaction * pinteraction, RECTANGLE_I32 * prectRet)
{

   return best_xinerama_monitor(pinteraction, nullptr, prectRet);

}


int get_best_monitor(::user::interaction * pinteraction, const ::rectangle_i32 & rectangleParam, RECTANGLE_I32 * prectRet)
{

   ::rectangle_i32 rNull = nullptr;

   ::rectangle_i32 rectangle(rectangleParam);

   if(rectangle_i32 == nullptr)
   {

      rectangle = rNull;

   }

   index i = pinteraction->best_monitor(prectRet, rectangle, false, e_activation_default, zorder_none);

   return i;

}


int get_best_monitor(::user::interaction * pinteraction, RECTANGLE_I32 * prectRet)
{

   return get_best_monitor(pinteraction, nullptr, prectRet);

}
