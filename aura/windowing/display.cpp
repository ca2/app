// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "aura/user/_user.h"
#include "_windowing.h"


namespace windowing
{


   display::display()
   {

      m_bSystemSynchronizedScreen = true;
      m_iMainMonitor = 0;
      m_iMainWkspace = 0;

      defer_create_mutex();

   }


   display::~ display()
   {


   }



   
   ::e_status display::initialize_display(::windowing::windowing * pwindowing)
   {

      auto estatus = initialize(pwindowing);

      if (!estatus)
      {

         return estatus;

      }

      if (get_context_system() != nullptr)
      {

         m_bSystemSynchronizedScreen = System.m_bSystemSynchronizedScreen;

      }

      m_pwindowing = pwindowing;

      return ::success;

   }


   iptr display::get_os_data() const
   {

      return -1;

   }


   window * display::default_root_window()
   {

      return nullptr;

   }



   float display::get_dpi()
   {

      return 96.0;

   }


   ::e_status display::open()
   {

      return ::success;

   }


   bool display::set_main_wkspace(index iWkspace)
   {

      if (iWkspace == -1)
      {

         m_iMainWkspace = -1;

         return true;

      }
      else if (iWkspace < 0 || iWkspace >= get_wkspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWkspace = iWkspace;

         return true;

      }

   }




   void display::enum_display_monitors()
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      m_monitorinfoa.remove_all();
//
//      ::EnumDisplayMonitors(nullptr, nullptr, &display::monitor_enum_proc, (lparam)(dynamic_cast <::aura::session *> (this)));
//
//#elif defined(LINUX)
//
//      ::enum_display_monitors(this);
//
//#endif

   }


   ::index display::get_main_monitor(RECTANGLE_I32 * prectangle)
   {

      index iMainMonitor = 0;

      if (prectangle != nullptr)
      {

         if (!get_monitor_rect(iMainMonitor, prectangle))
         {

            return -1;

         }

      }

      return iMainMonitor;

   }


   ::size_i32 display::get_main_monitor_size()
   {

      ::rectangle_i32 rectangle;

      get_main_monitor(rectangle);

      return rectangle.size();

   }


   ::count display::get_monitor_count()
   {

//#ifdef WINDOWS_DESKTOP
//
//      return m_monitorinfoa.get_count();
//
//#elif defined(MACOS)
//
//      return GetScreenCount();
//
//#elif defined(LINUX)
//
//      synchronization_lock synchronizationlock(mutex());
//
//      return m_rectaMonitor.get_count();
//
//#else
//
//      return 1;
//
//#endif

      return 1;

   }


   bool display::get_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      auto & pmonitor = m_monitora.element_at_grow(iMonitor);

      if(!pmonitor)
      {

         __construct(pmonitor);

         pmonitor->m_iIndex = iMonitor;

      }

      auto bOk = pmonitor->get_monitor_rect(prectangle);

      return bOk;


   }


   ::count display::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool display::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)

   {

      return get_monitor_rect(iMonitor, prectangle);


   }


   index display::get_main_wkspace(RECTANGLE_I32 * prectangle)

   {

//      index iMainWkspace = 0;
//
//#ifdef WINDOWS_DESKTOP
//
//      HMONITOR hwkspacePrimary = GetPrimaryMonitorHandle();
//
//      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
//      {
//
//         if (m_hmonitora[iWkspace] == hwkspacePrimary)
//         {
//
//            iMainWkspace = iWkspace;
//
//            break;
//
//         }
//
//      }
//
//
//#endif
//
//      if (prectangle != nullptr)
//
//      {
//
//         get_wkspace_rect(iMainWkspace, prectangle);
//
//
//      }
//
//      return iMainWkspace;

      return -1;

   }


   ::count display::get_wkspace_count()
   {

//#ifdef WINDOWS_DESKTOP
//
//      return m_monitorinfoa.get_count();
//
//#else
//
//      return get_monitor_count();
//
//#endif
      return 1;

   }


   bool display::get_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle)
   {

//#ifdef WINDOWS_DESKTOP
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//         return false;
//
//      *prectangle = m_monitorinfoa[iWkspace].rcWork;
//
//
//#elif defined(_UWP)
//
//      return get_monitor_rect(iWkspace, prectangle);
//
//
//      //#elif defined(LINUX)
//      //
//      //return false;
//      //
//#elif defined(__APPLE__)
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      GetWkspaceRect(prectangle, (int)iWkspace);
//
//
//      //      prectangle->top += ::mac::get_system_main_menu_bar_height();
//
//      //    prectangle->bottom -= ::mac::get_system_dock_height();
//
//#elif defined(LINUX)
//
//      synchronization_lock synchronizationlock(mutex());
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectaWkspace[iWkspace];
//
//
//      return true;
//
//#else
//
//      //__throw(todo());
//
//      //::get_window_rect(::get_desktop_window(),prectangle);
//
//
//      get_monitor_rect(iWkspace, prectangle);
//
//
//#endif
//
//      return true;

      return false;

   }


   ::count display::get_desk_wkspace_count()
   {

      return get_wkspace_count();

   }


   bool display::get_desk_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle)

   {

      return get_wkspace_rect(iWkspace, prectangle);


   }


   bool display::set_main_monitor(index iMonitor)
   {

      if (iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   bool display::wkspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWkspace)
   {

      ::rectangle_i32 rectangle(*prectangle);

      ::rectangle_i32 rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rectangle -= rectWkspace.top_left();

      ::rectangle_i32 rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rectangle += rectMonitor.top_left();

      *prectangle = rectangle;


      return true;

   }


   bool display::wkspace_to_monitor(RECTANGLE_I32 * prectangle)
   {

      index iWkspace = get_best_wkspace(nullptr, rectangle_i32(prectangle));

      return wkspace_to_monitor(prectangle, iWkspace, iWkspace);

   }


   bool display::monitor_to_wkspace(RECTANGLE_I32 * prectangle)
   {

      index iMonitor = get_best_monitor(nullptr, rectangle_i32(prectangle));

      return monitor_to_wkspace(prectangle, iMonitor, iMonitor);

   }


   bool display::monitor_to_wkspace(RECTANGLE_I32 * prectangle, index iWkspace, index iMonitor)
   {

      ::rectangle_i32 rectangle(prectangle);

      ::rectangle_i32 rectMonitor;

      if (!get_monitor_rect(iMonitor, rectMonitor))
      {

         return false;

      }

      rectangle -= rectMonitor.top_left();

      ::rectangle_i32 rectWkspace;

      if (!get_wkspace_rect(iWkspace, rectWkspace))
      {

         return false;

      }

      rectangle += rectWkspace.top_left();

      *prectangle = rectangle;

      return true;

   }


   monitor * display::get_monitor(index iMonitor)
   {

      synchronization_lock synchronizationlock(mutex());

      if (iMonitor < 0 || iMonitor >= m_monitora.get_count())
      {

         return nullptr;

      }

      return m_monitora[iMonitor];

   }


   void display::get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const rectangle_i32 & rectParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
            {

               if (rectIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectMonitor);

                  rectaIntersect.add(rectIntersect);

               }

            }

         }

      }

   }





#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   index display::_get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectRequest, bool bPreserveSize)
   {

      ::rectangle_i32 rectangle(rectRequest);

      ::rectangle_i32 rectWkspace;

      index iBestWkspace = get_best_wkspace(&rectWkspace, rectangle);

      edisplay edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      double dMargin = System.m_dpi;

      if (ZONEING_COMPARE::is_equal(rectangle.top, rectWkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectWkspace.top);

         }
         else
         {

            rectangle.top = rectWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangle.bottom, rectWkspace.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectWkspace.bottom);

         }
         else
         {

            rectangle.bottom = rectWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectRequest.left, rectWkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectWkspace.left);

         }
         else
         {

            rectangle.left = rectWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectRequest.right, rectWkspace.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectWkspace.right);

         }
         else
         {

            rectangle.right = rectWkspace.right;

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.top, rectangle.top, rectangle.bottom, rectWkspace.bottom))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rectangle.bottom = rectWkspace.bottom;

            rectangle.top = rectWkspace.top;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.left, rectangle.left, rectangle.right, rectWkspace.right))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rectangle.left = rectWkspace.left;

            rectangle.right = rectWkspace.right;

         }

      }

      bool bLeftXorRight = is_different(edisplay & e_display_left, edisplay & e_display_right);

      bool bTopXorBottom = is_different(edisplay & e_display_top, edisplay & e_display_bottom);

      bool bTopAndBottom = edisplay & e_display_top && edisplay & e_display_bottom;

      bool bLeftAndRight = edisplay & e_display_left && edisplay & e_display_right;

      if (bLeftXorRight && bTopXorBottom)
      {

      }
      else if (bTopAndBottom && bLeftAndRight)
      {

         edisplay = e_display_zoomed;

      }
      else
      {

         if (bLeftXorRight && !bTopAndBottom)
         {

            edisplay = e_display_none;

         }

         if (bTopXorBottom && !bLeftAndRight)
         {

            edisplay = e_display_none;

         }

         if (bTopAndBottom)
         {

            edisplay -= e_display_top;

            edisplay -= e_display_bottom;

         }

         if (bLeftAndRight)
         {

            edisplay -= e_display_left;

            edisplay -= e_display_right;

         }

      }

      if (edisplay == e_display_none)
      {

         edisplay = e_display_normal;

      }

      if (is_docking_appearance(edisplay))
      {

         *prectangle = rectangle;

      }
      else if (edisplay == e_display_zoomed)
      {

         *prectangle = rectWkspace;

      }
      else
      {

         *prectangle = rectRequest;

      }

      if (pedisplay)
      {

         *pedisplay = edisplay;

      }

      //if (g_i_get_best_zoneing % 10 == 0)
      //{

      //   string strE("e");
      //   if (edisplay & e_display_left)
      //      strE += "L";
      //   if (edisplay & e_display_top)
      //      strE += "T";
      //   if (edisplay & e_display_right)
      //      strE += "R";
      //   if (edisplay & e_display_bottom)
      //      strE += "B";

      //   string strP("p");
      //   if (edisplayPrevious & e_display_left)
      //      strP += "L";
      //   if (edisplayPrevious & e_display_top)
      //      strP += "T";
      //   if (edisplayPrevious & e_display_right)
      //      strP += "R";
      //   if (edisplayPrevious & e_display_bottom)
      //      strP += "B";

      //   ::output_debug_string(
      //      "w" + ::str::from(rectWkspace.left) + ","
      //      + ::str::from(rectWkspace.top) + ","
      //      + ::str::from(rectWkspace.right) + ","
      //      + ::str::from(rectWkspace.bottom) + " " +
      //      "r" + ::str::from(prectangle->left) + ","
      //      + ::str::from(prectangle->top) + ","
      //      + ::str::from(prectangle->right) + ","
      //      + ::str::from(prectangle->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectWkspace.left,
      //   rectWkspace.top,
      //   rectWkspace.right,
      //   rectWkspace.bottom,
      //   (edisplay & e_display_left)?'L':' ',
      //   (edisplay & e_display_top) ? 'T':' ',
      //   (edisplay & e_display_right) ? 'R':' ',
      //   (edisplay & e_display_bottom) ? 'B':' ',
      //   (edisplayPrevious & e_display_left) ? 'L':' ',
      //   (edisplayPrevious & e_display_top) ? 'T':' ',
      //   (edisplayPrevious & e_display_right) ? 'R':' ',
      //   (edisplayPrevious & e_display_bottom) ? 'B':' ');

      return iBestWkspace;

   }


   index display::get_best_monitor(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::e_activation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectMatch;

      ::rectangle_i32 rectangle(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_pos();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         if (get_monitor_rect(iMonitor, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rectangle, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rectangle))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prectangle);

      return iMatchingMonitor;

   }


   index display::get_best_wkspace(::rectangle_i32 * prectangle, const rectangle_i32 & rectParam, ::e_activation eactivation)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectMatch;

      ::rectangle_i32 rectangle(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_pos();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iWkspace = 0; iWkspace < get_wkspace_count(); iWkspace++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         if (get_wkspace_rect(iWkspace, rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rectangle, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rectangle))
            {

               iMatchingWkspace = iWkspace;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_wkspace(prectangle);

      return iMatchingWkspace;

   }


   index display::get_good_iconify(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam)
   {

      ::rectangle_i32 rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      prectangle->left = rectMonitor.left;

      prectangle->top = rectMonitor.top;

      prectangle->right = rectMonitor.left;

      prectangle->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   index display::initial_frame_position(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, bool bMove, ::user::interaction * pinteraction)
   {

      ::rectangle_i32 rectRestore(rectParam);

      ::rectangle_i32 rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      ::size_i32 sizeMin;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

      }
      else
      {

         sizeMin = m_pwindowing->get_window_minimum_size();

      }

      ::rectangle_i32 rectIntersect;

      if (bMove)
      {

         rect_array rectaMonitor;

         rect_array rectaIntersect;

         get_monitor(rectaMonitor, rectaIntersect, rectParam);

         rectaIntersect.get_box(rectIntersect);

      }
      else
      {

         rectIntersect.intersect(rectMonitor, &rectParam);

      }

      auto sizeMax = rectMonitor.size() * 0.9;

      if (rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy
         || rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy)
      {

         if (rectMonitor.width() / 7 + maximum(sizeMin.cx, rectMonitor.width() * 2 / 5) > rectMonitor.width()
            || rectMonitor.height() / 7 + maximum(sizeMin.cy, rectMonitor.height() * 2 / 5) > rectMonitor.width())
         {

            rectRestore = rectMonitor;

         }
         else
         {

            rectRestore.left = rectMonitor.left + rectMonitor.width() / 7;

            rectRestore.top = rectMonitor.top + rectMonitor.height() / 7;

            rectRestore.right = rectRestore.left + maximum(sizeMin.cx, rectMonitor.width() * 2 / 5);

            rectRestore.bottom = rectRestore.top + maximum(sizeMin.cy, rectMonitor.height() * 2 / 5);

            if (rectRestore.right > rectMonitor.right - rectMonitor.width() / 7)
            {

               rectRestore.offset(rectMonitor.right - rectMonitor.width() / 7 - rectRestore.right, 0);

            }

            if (rectRestore.bottom > rectMonitor.bottom - rectMonitor.height() / 7)
            {

               rectRestore.offset(0, rectMonitor.bottom - rectMonitor.height() / 7 - rectRestore.bottom);

            }

         }

         *prectangle = rectRestore;

         return iMatchingMonitor;

      }
      else
      {

         if (!bMove)
         {

            *prectangle = rectIntersect;

         }

         return -1;

      }

   }


   index display::get_window_restore_1(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rectangle_i32 rectRestore(rectParam);

      ::rectangle_i32 rectWkspace;

      ::size_i32 sizeMin;

      index iMatchingWkspace;

      ::size_i32 sizeBroad;

      ::size_i32 sizeCompact;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

         iMatchingWkspace = pinteraction->calculate_broad_and_compact_restore(rectWkspace, sizeMin, rectParam);

         sizeBroad = pinteraction->m_sizeRestoreBroad;

         sizeCompact = pinteraction->m_sizeRestoreCompact;

      }
      else
      {

         sizeMin = m_pwindowing->get_window_minimum_size();

         iMatchingWkspace = get_best_wkspace(&rectWkspace, rectParam);

         sizeBroad = sizeMin.maximum(rectWkspace.size() * 4 / 5);

         sizeCompact = sizeMin.maximum(rectWkspace.size() * 2 / 5);

      }

      auto rectIntersect = rectWkspace & rectParam;

      auto rectTolerance(rectWkspace);

      auto sizeMax = rectWkspace.size();

      bool b1 = !rectTolerance.contains(rectRestore);
      bool b2 = rectIntersect.width() < sizeMin.cx || rectIntersect.height() < sizeMin.cy;
      bool b3 = rectIntersect.width() > sizeMax.cx || rectIntersect.height() > sizeMax.cy;
      bool b4 = (edisplayRestore == e_display_compact && rectRestore.size() != sizeCompact);
      bool b5 = (edisplayRestore == e_display_broad && rectRestore.size() != sizeBroad);
      bool b6 = (rectRestore.size() == sizeCompact || rectRestore.size() == sizeBroad);
      bool b66 = !(edisplayRestore == e_display_compact || edisplayRestore == e_display_broad);

      bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

      if (bNotHappyWithTheSizeAndOrPosition)
      {

         if (edisplayRestore == e_display_broad || sizeCompact == rectRestore.size())
         {

            rectRestore.set_size(sizeBroad);

         }
         else
         {

            rectRestore.set_size(sizeCompact);

         }

         ::rectangle_i32 rectWkspaceBitSmaller(rectWkspace);

         rectWkspaceBitSmaller.deflate(5);

         if (!rectWkspaceBitSmaller.contains(rectRestore))
         {

            rectRestore.move_to(rectWkspace.origin() + rectWkspace.size() / 10);

         }

         *prectangle = rectRestore;

         return iMatchingWkspace;

      }
      else
      {

         return -1;

      }

   }



   index display::get_window_restore_2(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rectangle_i32 rectangle(rectParam);

      index iBestWkspace = get_window_restore_1(prectangle, rectangle, pinteraction, edisplayRestore);

      bool bChangedSize = ::size_i32(*prectangle) != rectParam.size();

      if (iBestWkspace < 0 && !bChangedSize)
      {

         return -1;

      }

      ::rectangle_i32 rectWkspace;

      ::rectangle_i32 rectStart(prectangle);

      ::point_i32 pointLineStart(::top_left(prectangle));

      get_wkspace_rect(iBestWkspace, rectWkspace);

      if (rectStart > pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rectangle.move_to(pointLineStart);

      }

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWkspace;

            }

            rectangle = *prectangle;

            if (rectangle > pinteraction->m_sizeRestoreCompact)
            {

               rectangle.offset(49, 0);

               if (!rectWkspace.contains(rectangle))
               {

                  pointLineStart.offset(0, 49);

                  rectangle.move_to(pointLineStart);

                  if (!rectWkspace.contains(rectangle))
                  {

                     break;

                  }

               }

            }
            else
            {

               rectangle.offset(49, 49);

            }

            *prectangle = rectangle;

         } while (rectWkspace.contains(rectangle));

      }

      if (rectangle.size() >= pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectWkspace.origin();

         pointLineStart.offset(49, 49);

         rectangle.move_to(pointLineStart);

         *prectangle = rectangle;

         return iBestWkspace;

      }

      rectangle = rectStart;

      rectangle.set_size(pinteraction->m_sizeRestoreCompact);

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWkspace;

            }

            rectangle = *prectangle;

            rectangle.offset(49, 49);

            *prectangle = rectangle;

         } while (rectWkspace.contains(rectangle));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rectangle.move_to(pointLineStart);

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWkspace;

            }

            rectangle = *prectangle;

            rectangle.offset(49, 0);

            if (!rectWkspace.contains(rectangle))
            {

               pointLineStart.offset(0, 49);

               rectangle.move_to(pointLineStart);

               if (!rectWkspace.contains(rectangle))
               {

                  break;

               }

            }

            *prectangle = rectangle;

         } while (rectWkspace.contains(rectangle));

      }

      pointLineStart = rectWkspace.origin();

      pointLineStart.offset(49, 49);

      rectangle.move_to(pointLineStart);

      *prectangle = rectangle;

      return iBestWkspace;

   }


   index display::get_good_move(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::user::interaction * pinteraction)
   {

      index iMatchingMonitor = initial_frame_position(prectangle, rectParam, true, pinteraction);

      if (__memcmp(prectangle, &rectParam, sizeof(const rectangle_i32 &)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }

   }






   index display::get_ui_wkspace(::user::interaction * pinteraction)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return get_ui_wkspace(pinteraction);

      }
      else
      {

         ::rectangle_i32 rectangle;

         pinteraction->layout().sketch().screen_rect(rectangle);

         return get_best_wkspace(nullptr, rectangle);

      }

   }

   string_array display::get_wallpaper()
   {

      auto psession = Session;

      ::count iMonitorCount = get_monitor_count();

      string_array stra;

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         stra.add(get_wallpaper(iScreen));

      }

      bool bAllEqual = true;

      for (index iScreen = 1; iScreen < iMonitorCount; iScreen++)
      {

         if (stra[iScreen] != stra[iScreen - 1])
         {

            bAllEqual = false;

         }

      }

      if (bAllEqual && stra.get_count() >= 2)
      {

         stra.set_size(1);

      }

      return stra;

   }


   void display::set_wallpaper(const string_array & straWallpaper)
   {

      if (straWallpaper.is_empty())
      {

         return;

      }

      auto psession = Session;

      ::count iMonitorCount = get_monitor_count();

#ifdef LINUX

      if (iMonitorCount > 0)
      {

         set_wallpaper(0, straWallpaper[0]);

      }

#else

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         string strWallpaper = iScreen % straWallpaper;

         set_wallpaper(iScreen, strWallpaper);

      }

#endif

   }

   
   string display::get_wallpaper(::index iScreen)
   {

      return impl_get_wallpaper(iScreen);

   }


   string display::impl_get_wallpaper(::index)
   {

      return "";

   }

   string display::os_get_user_theme()
   {

      return impl_get_os_desktop_theme();

   }

   string display::impl_get_os_desktop_theme()
   {

      return "";

   }


   bool display::set_os_desktop_theme(string strTheme)
   {

      return impl_set_os_desktop_theme(strTheme);

   }


   bool display::impl_set_os_desktop_theme(string strTheme)
   {

      return false;

   }


   // todo color:// gradient:// if the operating system doesn't have this, create the file, please.
   bool display::impl_set_wallpaper(::index, string strWallpaper)
   {

      //return "";
      return false;

   }

   bool display::set_wallpaper(::index iScreen, string strWallpaper)
   {

      //return "";
      return impl_set_wallpaper(iScreen, strWallpaper);

   }


   void display::enable_wallpaper_change_notification()
   {


   }


} // namespace windowing




