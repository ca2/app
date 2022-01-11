// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "aura/user/_user.h"
#include "_windowing.h"
#include "acme/primitive/geometry2d/_.h"
#include "acme/primitive/geometry2d/_geometry2d.h"
#include "acme/primitive/geometry2d/_impl.h"


namespace windowing
{


   display::display()
   {

      m_pDisplay = nullptr;

      m_pDisplay = nullptr;

      m_bSystemSynchronizedScreen = true;
      m_iMainMonitor = 0;
      m_iMainWorkspace = 0;

      defer_create_mutex();

   }


   display::~ display()
   {


   }



   
   void display::initialize_display(::windowing::windowing * pwindowing)
   {

      auto estatus = initialize(pwindowing);

      if (!estatus)
      {

         return estatus;

      }

      auto psystem = m_psystem->m_paurasystem;

      if (psystem != nullptr)
      {

         m_bSystemSynchronizedScreen = psystem->m_paurasystem->m_bSystemSynchronizedScreen;

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


   void display::open()
   {

      return ::success;

   }


   bool display::set_main_workspace(index iWorkspace)
   {

      if (iWorkspace == -1)
      {

         m_iMainWorkspace = -1;

         return true;

      }
      else if (iWorkspace < 0 || iWorkspace >= get_workspace_count())
      {

         return false;

      }
      else
      {

         m_iMainWorkspace = iWorkspace;

         return true;

      }

   }




   void display::enum_display_monitors()
   {
//
//#ifdef WINDOWS_DESKTOP
//
//      m_monitorinfoa.erase_all();
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

         if (!get_monitor_rectangle(iMainMonitor, prectangle))
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
//      synchronous_lock synchronouslock(mutex());
//
//      return m_rectangleaMonitor.get_count();
//
//#else
//
//      return 1;
//
//#endif

      return 1;

   }


   bool display::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
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

         pmonitor->m_pdisplay = this;

      }

      auto bOk = pmonitor->get_monitor_rectangle(prectangle);

      return bOk;

   }


   ::count display::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool display::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)
   {

      return get_monitor_rectangle(iMonitor, prectangle);

   }



   index display::get_main_workspace(RECTANGLE_I32 * prectangle)
   {

      if(!get_workspace_rectangle(0, prectangle))
      {

         return -1;

      }

      return 0;

   }


   ::count display::get_workspace_count()
   {

      return get_monitor_count();

   }


   bool display::get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle)
   {

      if(iWorkspace < 0 || iWorkspace >= get_workspace_count())
      {

         return false;

      }

      auto & pmonitor = m_monitora.element_at_grow(iWorkspace);

      if(!pmonitor)
      {

         __construct(pmonitor);

         if (!pmonitor)
         {

            return false;

         }

         pmonitor->m_iIndex = iWorkspace;

         pmonitor->m_pdisplay = this;

      }

      auto bOk = pmonitor->get_workspace_rectangle(prectangle);

      return bOk;

   }


   ::count display::get_desk_workspace_count()
   {

      return get_workspace_count();

   }


   bool display::get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32 * prectangle)

   {

      return get_workspace_rectangle(iWorkspace, prectangle);


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


   bool display::workspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWorkspace)
   {

      ::rectangle_i32 rectangle(*prectangle);

      ::rectangle_i32 rectangleWorkspace;

      if (!get_workspace_rectangle(iWorkspace, rectangleWorkspace))
      {

         return false;

      }

      rectangle -= rectangleWorkspace.top_left();

      ::rectangle_i32 rectangleMonitor;

      if (!get_monitor_rectangle(iMonitor, rectangleMonitor))
      {

         return false;

      }

      rectangle += rectangleMonitor.top_left();

      *prectangle = rectangle;


      return true;

   }


   bool display::workspace_to_monitor(RECTANGLE_I32 * prectangle)
   {

      index iWorkspace = get_best_workspace(nullptr, rectangle_i32(prectangle));

      return workspace_to_monitor(prectangle, iWorkspace, iWorkspace);

   }


   bool display::monitor_to_workspace(RECTANGLE_I32 * prectangle)
   {

      index iMonitor = get_best_monitor(nullptr, rectangle_i32(prectangle));

      return monitor_to_workspace(prectangle, iMonitor, iMonitor);

   }


   bool display::monitor_to_workspace(RECTANGLE_I32 * prectangle, index iWorkspace, index iMonitor)
   {

      ::rectangle_i32 rectangle(prectangle);

      ::rectangle_i32 rectangleMonitor;

      if (!get_monitor_rectangle(iMonitor, rectangleMonitor))
      {

         return false;

      }

      rectangle -= rectangleMonitor.top_left();

      ::rectangle_i32 rectangleWorkspace;

      if (!get_workspace_rectangle(iWorkspace, rectangleWorkspace))
      {

         return false;

      }

      rectangle += rectangleWorkspace.top_left();

      *prectangle = rectangle;

      return true;

   }


   monitor * display::get_monitor(index iMonitor)
   {

      synchronous_lock synchronouslock(mutex());

      if (iMonitor < 0 || iMonitor >= m_monitora.get_count())
      {

         return nullptr;

      }

      return m_monitora[iMonitor];

   }


   void display::get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const rectangle_i32 & rectangleParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         if (get_monitor_rectangle(iMonitor, rectangleMonitor))
         {

            if (rectangleIntersect.top_left_null_intersect(&rectangleParam, rectangleMonitor))
            {

               if (rectangleIntersect.area() >= 0)
               {

                  rectaMonitor.add(rectangleMonitor);

                  rectaIntersect.add(rectangleIntersect);

               }

            }

         }

      }

   }





#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   index display::_get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
   {

      ::rectangle_i32 rectangle(rectangleRequest);

      ::rectangle_i32 rectangleWorkspace;

      index iBestWorkspace = get_best_workspace(&rectangleWorkspace, rectangle);

      edisplay edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      auto psystem = m_psystem->m_paurasystem;

      double dMargin = psystem->m_paurasystem->m_dDpi;

      if (ZONEING_COMPARE::is_equal(rectangle.top, rectangleWorkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectangleWorkspace.top);

         }
         else
         {

            rectangle.top = rectangleWorkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangle.bottom, rectangleWorkspace.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectangleWorkspace.bottom);

         }
         else
         {

            rectangle.bottom = rectangleWorkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectangleRequest.left, rectangleWorkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectangleWorkspace.left);

         }
         else
         {

            rectangle.left = rectangleWorkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangleRequest.right, rectangleWorkspace.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectangleWorkspace.right);

         }
         else
         {

            rectangle.right = rectangleWorkspace.right;

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.top, rectangle.top, rectangle.bottom, rectangleWorkspace.bottom))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rectangle.bottom = rectangleWorkspace.bottom;

            rectangle.top = rectangleWorkspace.top;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.left, rectangle.left, rectangle.right, rectangleWorkspace.right))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rectangle.left = rectangleWorkspace.left;

            rectangle.right = rectangleWorkspace.right;

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

         *prectangle = rectangleWorkspace;

      }
      else
      {

         *prectangle = rectangleRequest;

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
      //      "w" + __string(rectangleWorkspace.left) + ","
      //      + __string(rectangleWorkspace.top) + ","
      //      + __string(rectangleWorkspace.right) + ","
      //      + __string(rectangleWorkspace.bottom) + " " +
      //      "r" + __string(prectangle->left) + ","
      //      + __string(prectangle->top) + ","
      //      + __string(prectangle->right) + ","
      //      + __string(prectangle->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectangleWorkspace.left,
      //   rectangleWorkspace.top,
      //   rectangleWorkspace.right,
      //   rectangleWorkspace.bottom,
      //   (edisplay & e_display_left)?'L':' ',
      //   (edisplay & e_display_top) ? 'T':' ',
      //   (edisplay & e_display_right) ? 'R':' ',
      //   (edisplay & e_display_bottom) ? 'B':' ',
      //   (edisplayPrevious & e_display_left) ? 'L':' ',
      //   (edisplayPrevious & e_display_top) ? 'T':' ',
      //   (edisplayPrevious & e_display_right) ? 'R':' ',
      //   (edisplayPrevious & e_display_bottom) ? 'B':' ');

      return iBestWorkspace;

   }


   index display::get_best_monitor(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_position();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         if (get_monitor_rectangle(iMonitor, rectangleMonitor))
         {

            if (rectangleIntersect.top_left_null_intersect(rectangle, rectangleMonitor))
            {

               if (rectangleIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectangleIntersect.area();

                  rectangleMatch = rectangleMonitor;

               }

            }
            else if (rectangleMonitor.contains(rectangle))
            {

               iMatchingMonitor = iMonitor;

               rectangleMatch = rectangleMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectangleMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prectangle);

      return iMatchingMonitor;

   }


   index display::get_best_workspace(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation)
   {

      index iMatchingWorkspace = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_position();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iWorkspace = 0; iWorkspace < get_workspace_count(); iWorkspace++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         if (get_workspace_rectangle(iWorkspace, rectangleMonitor))
         {

            if (rectangleIntersect.top_left_null_intersect(rectangle, rectangleMonitor))
            {

               if (rectangleIntersect.area() > iBestArea)
               {

                  iMatchingWorkspace = iWorkspace;

                  iBestArea = rectangleIntersect.area();

                  rectangleMatch = rectangleMonitor;

               }

            }
            else if (rectangleMonitor.contains(rectangle))
            {

               iMatchingWorkspace = iWorkspace;

               rectangleMatch = rectangleMonitor;

            }

         }

      }

      if (iMatchingWorkspace >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectangleMatch;

         }

         return iMatchingWorkspace;

      }

      iMatchingWorkspace = get_main_workspace(prectangle);

      return iMatchingWorkspace;

   }


   index display::get_good_iconify(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam)
   {

      ::rectangle_i32 rectangleMonitor;

      index iMatchingMonitor = get_best_monitor(rectangleMonitor, rectangleParam);

      prectangle->left = rectangleMonitor.left;

      prectangle->top = rectangleMonitor.top;

      prectangle->right = rectangleMonitor.left;

      prectangle->bottom = rectangleMonitor.top;

      return iMatchingMonitor;

   }


   index display::initial_frame_position(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, bool bMove, ::user::interaction * pinteraction)
   {

      ::rectangle_i32 rectangleRestore(rectangleParam);

      ::rectangle_i32 rectangleMonitor;

      index iMatchingMonitor = get_best_monitor(rectangleMonitor, rectangleParam);

      ::size_i32 sizeMin;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

      }
      else
      {

         sizeMin = m_pwindowing->get_window_minimum_size();

      }

      ::rectangle_i32 rectangleIntersect;

      if (bMove)
      {

         rectangle_i32_array rectaMonitor;

         rectangle_i32_array rectaIntersect;

         get_monitor(rectaMonitor, rectaIntersect, rectangleParam);

         rectaIntersect.get_box(rectangleIntersect);

      }
      else
      {

         rectangleIntersect.intersect(rectangleMonitor, &rectangleParam);

      }

      auto sizeMax = rectangleMonitor.size() * 0.9;

      if (rectangleIntersect.width() < sizeMin.cx || rectangleIntersect.height() < sizeMin.cy
         || rectangleIntersect.width() > sizeMax.cx || rectangleIntersect.height() > sizeMax.cy)
      {

         if (rectangleMonitor.width() / 7 + maximum(sizeMin.cx, rectangleMonitor.width() * 2 / 5) > rectangleMonitor.width()
            || rectangleMonitor.height() / 7 + maximum(sizeMin.cy, rectangleMonitor.height() * 2 / 5) > rectangleMonitor.width())
         {

            rectangleRestore = rectangleMonitor;

         }
         else
         {

            rectangleRestore.left = rectangleMonitor.left + rectangleMonitor.width() / 7;

            rectangleRestore.top = rectangleMonitor.top + rectangleMonitor.height() / 7;

            rectangleRestore.right = rectangleRestore.left + maximum(sizeMin.cx, rectangleMonitor.width() * 2 / 5);

            rectangleRestore.bottom = rectangleRestore.top + maximum(sizeMin.cy, rectangleMonitor.height() * 2 / 5);

            if (rectangleRestore.right > rectangleMonitor.right - rectangleMonitor.width() / 7)
            {

               rectangleRestore.offset(rectangleMonitor.right - rectangleMonitor.width() / 7 - rectangleRestore.right, 0);

            }

            if (rectangleRestore.bottom > rectangleMonitor.bottom - rectangleMonitor.height() / 7)
            {

               rectangleRestore.offset(0, rectangleMonitor.bottom - rectangleMonitor.height() / 7 - rectangleRestore.bottom);

            }

         }

         *prectangle = rectangleRestore;

         return iMatchingMonitor;

      }
      else
      {

         if (!bMove)
         {

            *prectangle = rectangleIntersect;

         }

         return -1;

      }

   }


   index display::get_window_restore_1(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rectangle_i32 rectangleRestore(rectangleParam);

      ::rectangle_i32 rectangleWorkspace;

      ::size_i32 sizeMin;

      index iMatchingWorkspace;

      ::size_i32 sizeBroad;

      ::size_i32 sizeCompact;

      if (pinteraction != nullptr)
      {

         sizeMin = pinteraction->get_window_minimum_size();

         iMatchingWorkspace = pinteraction->calculate_broad_and_compact_restore(rectangleWorkspace, sizeMin, rectangleParam);

         sizeBroad = pinteraction->m_sizeRestoreBroad;

         sizeCompact = pinteraction->m_sizeRestoreCompact;

      }
      else
      {

         sizeMin = m_pwindowing->get_window_minimum_size();

         iMatchingWorkspace = get_best_workspace(&rectangleWorkspace, rectangleParam);

         sizeBroad = sizeMin.maximum(rectangleWorkspace.size() * 4 / 5);

         sizeCompact = sizeMin.maximum(rectangleWorkspace.size() * 2 / 5);

      }

      auto rectangleIntersect = rectangleWorkspace & rectangleParam;

      auto rectangleTolerance(rectangleWorkspace);

      auto sizeMax = rectangleWorkspace.size();

      bool b1 = !rectangleTolerance.contains(rectangleRestore);
      bool b2 = rectangleIntersect.width() < sizeMin.cx || rectangleIntersect.height() < sizeMin.cy;
      bool b3 = rectangleIntersect.width() > sizeMax.cx || rectangleIntersect.height() > sizeMax.cy;
      bool b4 = (edisplayRestore == e_display_compact && rectangleRestore.size() != sizeCompact);
      bool b5 = (edisplayRestore == e_display_broad && rectangleRestore.size() != sizeBroad);
      bool b6 = (rectangleRestore.size() == sizeCompact || rectangleRestore.size() == sizeBroad);
      bool b66 = !(edisplayRestore == e_display_compact || edisplayRestore == e_display_broad);

      bool bNotHappyWithTheSizeAndOrPosition = b1 || b2 || b3 || b4 || b5 || (b6 && b66);

      if (bNotHappyWithTheSizeAndOrPosition)
      {

         if (edisplayRestore == e_display_broad || sizeCompact == rectangleRestore.size())
         {

            rectangleRestore.set_size(sizeBroad);

         }
         else
         {

            rectangleRestore.set_size(sizeCompact);

         }

         ::rectangle_i32 rectangleWorkspaceBitSmaller(rectangleWorkspace);

         rectangleWorkspaceBitSmaller.deflate(5);

         if (!rectangleWorkspaceBitSmaller.contains(rectangleRestore))
         {

            rectangleRestore.move_to(rectangleWorkspace.origin() + rectangleWorkspace.size() / 10);

         }

         *prectangle = rectangleRestore;

         return iMatchingWorkspace;

      }
      else
      {

         return -1;

      }

   }



   index display::get_window_restore_2(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, ::user::interaction * pinteraction, edisplay edisplayRestore)
   {

      ::rectangle_i32 rectangle(rectangleParam);

      index iBestWorkspace = get_window_restore_1(prectangle, rectangle, pinteraction, edisplayRestore);

      bool bChangedSize = ::size_i32(*prectangle) != rectangleParam.size();

      if (iBestWorkspace < 0 && !bChangedSize)
      {

         return -1;

      }

      ::rectangle_i32 rectangleWorkspace;

      ::rectangle_i32 rectangleStart(prectangle);

      ::point_i32 pointLineStart(::top_left(prectangle));

      get_workspace_rectangle(iBestWorkspace, rectangleWorkspace);

      if (rectangleStart > pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectangleWorkspace.origin();

         pointLineStart.offset(49, 49);

         rectangle.move_to(pointLineStart);

      }

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWorkspace;

            }

            rectangle = *prectangle;

            if (rectangle > pinteraction->m_sizeRestoreCompact)
            {

               rectangle.offset(49, 0);

               if (!rectangleWorkspace.contains(rectangle))
               {

                  pointLineStart.offset(0, 49);

                  rectangle.move_to(pointLineStart);

                  if (!rectangleWorkspace.contains(rectangle))
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

         } while (rectangleWorkspace.contains(rectangle));

      }

      if (rectangle.size() >= pinteraction->m_sizeRestoreCompact)
      {

         pointLineStart = rectangleWorkspace.origin();

         pointLineStart.offset(49, 49);

         rectangle.move_to(pointLineStart);

         *prectangle = rectangle;

         return iBestWorkspace;

      }

      rectangle = rectangleStart;

      rectangle.set_size(pinteraction->m_sizeRestoreCompact);

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWorkspace;

            }

            rectangle = *prectangle;

            rectangle.offset(49, 49);

            *prectangle = rectangle;

         } while (rectangleWorkspace.contains(rectangle));

      }

      pointLineStart = rectangleWorkspace.origin();

      pointLineStart.offset(49, 49);

      rectangle.move_to(pointLineStart);

      if (m_pwindowing->is_window(pinteraction->get_oswindow()))
      {

         do
         {

            if (!m_pwindowing->point_is_window_origin(::top_left(prectangle), pinteraction->get_oswindow(), 49))
            {

               return iBestWorkspace;

            }

            rectangle = *prectangle;

            rectangle.offset(49, 0);

            if (!rectangleWorkspace.contains(rectangle))
            {

               pointLineStart.offset(0, 49);

               rectangle.move_to(pointLineStart);

               if (!rectangleWorkspace.contains(rectangle))
               {

                  break;

               }

            }

            *prectangle = rectangle;

         } while (rectangleWorkspace.contains(rectangle));

      }

      pointLineStart = rectangleWorkspace.origin();

      pointLineStart.offset(49, 49);

      rectangle.move_to(pointLineStart);

      *prectangle = rectangle;

      return iBestWorkspace;

   }


   index display::get_good_move(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, ::user::interaction * pinteraction)
   {

      index iMatchingMonitor = initial_frame_position(prectangle, rectangleParam, true, pinteraction);

      if (__memcmp(prectangle, &rectangleParam, sizeof(const rectangle_i32 &)))
      {

         return iMatchingMonitor;

      }
      else
      {

         return -1;

      }

   }






   index display::get_ui_workspace(::user::interaction * pinteraction)
   {

      if (m_bSystemSynchronizedScreen)
      {

         return get_ui_workspace(pinteraction);

      }
      else
      {

         ::rectangle_i32 rectangle;

         rectangle = pinteraction->screen_rect();

         return get_best_workspace(nullptr, rectangle);

      }

   }

   string_array display::get_wallpaper()
   {

      auto psession = get_session();

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

      auto psession = get_session();

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




