// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/primitive/geometry2d/rectangle_array.h"
#include "aura/windowing/display.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/window.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/system.h"


namespace windowing
{


   display::display()
   {

      m_pDisplay = nullptr;

      m_pDisplay2 = nullptr;

#ifdef LINUX
      _m_pX11Display = nullptr;
#endif

      m_bSystemSynchronizedScreen = true;
      m_iMainMonitor = 0;
      m_iMainWorkspace = 0;

   }


   display::~ display()
   {


   }



   
   void display::initialize_display(::windowing::windowing * pwindowing)
   {

      //auto estatus =
      
      initialize(pwindowing);

      defer_create_synchronization();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = acmesystem()->m_paurasystem;

      if (psystem != nullptr)
      {

         m_bSystemSynchronizedScreen = psystem->m_paurasystem->m_bSystemSynchronizedScreen;

      }

      m_pwindowing = pwindowing;

      //return ::success;

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

      //return ::success;

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


   ::index display::get_main_monitor_index()
   {

      return 0;

   }


   ::index display::get_main_monitor(::rectangle_i32 & rectangle)
   {

      index iMainMonitor = get_main_monitor_index();

      if (!get_monitor_rectangle(iMainMonitor, rectangle))
      {

         return -1;

      }

      return iMainMonitor;

   }


   ::size_i32 display::get_main_monitor_size()
   {

      ::rectangle_i32 rectangle;

      get_main_monitor(rectangle);

      return rectangle.size();

   }


   ::rectangle_i32 display::get_monitor_union_rectangle()
   {

      ::rectangle_i32 rectangleUnion;

      rectangleUnion.left() = I32_MAXIMUM;

      rectangleUnion.top() = I32_MAXIMUM;

      rectangleUnion.right() = I32_MINIMUM;

      rectangleUnion.bottom() = I32_MINIMUM;

      for(auto & pmonitor : m_monitora)
      {

         if (pmonitor->m_rectangle.left() < rectangleUnion.left())
         {

            rectangleUnion.left() = pmonitor->m_rectangle.left();

         }

         if (pmonitor->m_rectangle.top() < rectangleUnion.top())
         {

            rectangleUnion.top() = pmonitor->m_rectangle.top();

         }

         if (pmonitor->m_rectangle.right() > rectangleUnion.right())
         {

            rectangleUnion.right() = pmonitor->m_rectangle.right();

         }

         if (pmonitor->m_rectangle.bottom() > rectangleUnion.bottom())
         {

            rectangleUnion.bottom() = pmonitor->m_rectangle.bottom();

         }

      }

      return rectangleUnion;

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
//      synchronous_lock synchronouslock(this->synchronization());
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


   bool display::get_monitor_rectangle(index iMonitor, ::rectangle_i32 & rectangle)
   {

      if(iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }

      auto & pmonitor = m_monitora.element_at_grow(iMonitor);

      if(!pmonitor)
      {

         ((display*)this)->__construct(pmonitor);

         pmonitor->m_iIndex = iMonitor;

         pmonitor->m_pdisplay = this;

      }

      rectangle = pmonitor->monitor_rectangle();

      return true;

   }


   ::index  display::get_main_monitor_of_rectangle(const ::rectangle_i32 &rectangle)
   {

      ::rectangle_i32 rectangleMonitor;

      ::i32 iMaximumArea = -1;

      ::index iMainMonitor = -1;

      for (::index i = 0; i < get_monitor_count(); i++)
      {

         get_monitor_rectangle(i, rectangleMonitor);

         ::rectangle_i32 rectangleIntersection;

         if (rectangleIntersection.intersect(rectangleMonitor, rectangle))
         {

            if (rectangleIntersection.area() > iMaximumArea)
            {

               iMaximumArea = rectangleIntersection.area();

               iMainMonitor = i;

            }

         }

      }

      return iMainMonitor;

   }


   ::count display::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   bool display::get_desk_monitor_rect(index iMonitor, ::rectangle_i32 & rectangle)
   {

      return get_monitor_rectangle(iMonitor, rectangle);

   }



   index display::get_main_workspace(::rectangle_i32 & rectangle)
   {

      index iMainWorkspace = get_main_monitor_index();

      if(!get_workspace_rectangle(iMainWorkspace, rectangle))
      {

         return -1;

      }

      return iMainWorkspace;

   }


   ::count display::get_workspace_count()
   {

      return get_monitor_count();

   }


   bool display::get_workspace_rectangle(index iWorkspace, ::rectangle_i32 & rectangle)
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

      rectangle = pmonitor->workspace_rectangle();

      return true;

   }


   ::count display::get_desk_workspace_count()
   {

      return get_workspace_count();

   }


   bool display::get_desk_workspace_rect(index iWorkspace, ::rectangle_i32 & rectangle)

   {

      return get_workspace_rectangle(iWorkspace, rectangle);


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


   bool display::workspace_to_monitor(::rectangle_i32 & rectangleToMonitor, index iMonitor, index iWorkspace)
   {

      ::rectangle_i32 rectangle(rectangleToMonitor);

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

      rectangleToMonitor = rectangle;

      return true;

   }


   bool display::workspace_to_monitor(::rectangle_i32 & rectangle)
   {

      index iWorkspace = get_best_workspace(nullptr, rectangle);

      return workspace_to_monitor(rectangle, iWorkspace, iWorkspace);

   }


   bool display::monitor_to_workspace(::rectangle_i32 & rectangle)
   {

      index iMonitor = get_best_monitor(nullptr, rectangle);

      return monitor_to_workspace(rectangle, iMonitor, iMonitor);

   }


   bool display::monitor_to_workspace(::rectangle_i32 & rectangleToWorkspace, index iWorkspace, index iMonitor)
   {

      ::rectangle_i32 rectangle(rectangleToWorkspace);

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

      rectangleToWorkspace = rectangle;

      return true;

   }


   monitor * display::get_monitor(index iMonitor)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (iMonitor < 0 || iMonitor >= m_monitora.get_count())
      {

         return nullptr;

      }

      return m_monitora[iMonitor];

   }


   monitor * display::monitor_hit_test(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(this->synchronization());

      for(auto pmonitor : m_monitora)
      {

         auto rectangleMonitor = pmonitor->monitor_rectangle();

         if(rectangleMonitor.contains(point))
         {

            return pmonitor;

         }



      }

      return nullptr;

   }



   void display::get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const rectangle_i32 & rectangleParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         if (get_monitor_rectangle(iMonitor, rectangleMonitor))
         {

            if (rectangleIntersect.top_left_null_intersect(rectangleParam, rectangleMonitor))
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

   index display::_get_best_zoneing(::e_display * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
   {

      ::rectangle_i32 rectangle(rectangleRequest);

      ::rectangle_i32 rectangleWorkspace;

      index iBestWorkspace = get_best_workspace(&rectangleWorkspace, rectangle);

      information() << "display::_get_best_zoneing rectangleWorkspace : " << rectangleWorkspace;

      ::e_display edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      auto psystem = acmesystem()->m_paurasystem;

      double dMargin = psystem->m_paurasystem->m_dDpi;

      if (ZONEING_COMPARE::is_equal(rectangle.top(), rectangleWorkspace.top(), dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectangleWorkspace.top());

         }
         else
         {

            rectangle.top() = rectangleWorkspace.top();

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangle.bottom(), rectangleWorkspace.bottom(), dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectangleWorkspace.bottom());

         }
         else
         {

            rectangle.bottom() = rectangleWorkspace.bottom();

         }

      }

      if (ZONEING_COMPARE::is_equal(rectangleRequest.left(), rectangleWorkspace.left(), dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectangleWorkspace.left());

         }
         else
         {

            rectangle.left() = rectangleWorkspace.left();

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangleRequest.right(), rectangleWorkspace.right(), dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectangleWorkspace.right());

         }
         else
         {

            rectangle.right() = rectangleWorkspace.right();

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.top(), rectangle.top(), rectangle.bottom(), rectangleWorkspace.bottom()))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rectangle.bottom() = rectangleWorkspace.bottom();

            rectangle.top() = rectangleWorkspace.top();

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWorkspace.left(), rectangle.left(), rectangle.right(), rectangleWorkspace.right()))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rectangle.left() = rectangleWorkspace.left();

            rectangle.right() = rectangleWorkspace.right();

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

      //   ::information(
      //      "w" + as_string(rectangleWorkspace.left()) + ","
      //      + as_string(rectangleWorkspace.top()) + ","
      //      + as_string(rectangleWorkspace.right()) + ","
      //      + as_string(rectangleWorkspace.bottom()) + " " +
      //      "r" + as_string(prectangle->left()) + ","
      //      + as_string(prectangle->top()) + ","
      //      + as_string(prectangle->right()) + ","
      //      + as_string(prectangle->bottom()) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectangleWorkspace.left(),
      //   rectangleWorkspace.top(),
      //   rectangleWorkspace.right(),
      //   rectangleWorkspace.bottom(),
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


   index display::get_best_monitor(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation, ::windowing::window * pwindowCursorPosition)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor;

         if(::is_set(pwindowCursorPosition))
         {

            pointCursor = pwindowCursorPosition->get_cursor_position();

         }
         else
         {

            pointCursor = m_pwindowing->get_cursor_position();

         }

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

      iMatchingMonitor = get_main_monitor(rectangle);

      return iMatchingMonitor;

   }


   index display::get_best_workspace(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation, ::windowing::window * pwindowCursorPosition)
   {

      index iMatchingWorkspace = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      //if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      if (eactivation & e_activation_under_mouse_cursor)
      {

         ::point_i32 pointCursor = pwindowCursorPosition->get_cursor_position();

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

      iMatchingWorkspace = get_main_workspace(*prectangle);

      return iMatchingWorkspace;

   }



   monitor * display::get_best_monitor(const ::rectangle_i32 & rectangle)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         if (get_monitor_rectangle(iMonitor, rectangleMonitor))
         {

            if (rectangleMonitor.contains(rectangle))
            {

               iMatchingMonitor = iMonitor;

               break;

            }
            else if (rectangleIntersect.top_left_null_intersect(rectangle, rectangleMonitor))
            {

               if (rectangleIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectangleIntersect.area();

               }

            }

         }

      }

      if(iMatchingMonitor < 0)
      {

         return nullptr;

      }

      return m_monitora[iMatchingMonitor];

   }


   index display::get_good_iconify(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam)
   {

      ::rectangle_i32 rectangleMonitor;

      index iMatchingMonitor = get_best_monitor(&rectangleMonitor, rectangleParam);

      prectangle->left() = rectangleMonitor.left();

      prectangle->top() = rectangleMonitor.top();

      prectangle->right() = rectangleMonitor.left();

      prectangle->bottom() = rectangleMonitor.top();

      return iMatchingMonitor;

   }


   index display::initial_frame_position(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, bool bMove, ::user::interaction * pinteraction)
   {

      ::rectangle_i32 rectangleRestore(rectangleParam);

      ::rectangle_i32 rectangleMonitor;

      index iMatchingMonitor = get_best_monitor(&rectangleMonitor, rectangleParam);

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

         rectaIntersect.get_box(&rectangleIntersect);

      }
      else
      {

         rectangleIntersect.intersect(rectangleMonitor, rectangleParam);

      }
      
      auto sizeMax = rectangleMonitor.size() * 0.9;

      if (rectangleIntersect.width() < sizeMin.cx() || rectangleIntersect.height() < sizeMin.cy()
         || rectangleIntersect.width() > sizeMax.cx() || rectangleIntersect.height() > sizeMax.cy())
      {

         if (rectangleMonitor.width() / 7 + maximum(sizeMin.cx(), rectangleMonitor.width() * 2 / 5) > rectangleMonitor.width()
            || rectangleMonitor.height() / 7 + maximum(sizeMin.cy(), rectangleMonitor.height() * 2 / 5) > rectangleMonitor.width())
         {

            rectangleRestore = rectangleMonitor;

         }
         else
         {

            rectangleRestore.left() = rectangleMonitor.left() + rectangleMonitor.width() / 7;

            rectangleRestore.top() = rectangleMonitor.top() + rectangleMonitor.height() / 7;

            rectangleRestore.right() = rectangleRestore.left() + maximum(sizeMin.cx(), rectangleMonitor.width() * 2 / 5);

            rectangleRestore.bottom() = rectangleRestore.top() + maximum(sizeMin.cy(), rectangleMonitor.height() * 2 / 5);

            if (rectangleRestore.right() > rectangleMonitor.right() - rectangleMonitor.width() / 7)
            {

               rectangleRestore.offset(rectangleMonitor.right() - rectangleMonitor.width() / 7 - rectangleRestore.right(), 0);

            }

            if (rectangleRestore.bottom() > rectangleMonitor.bottom() - rectangleMonitor.height() / 7)
            {

               rectangleRestore.offset(0, rectangleMonitor.bottom() - rectangleMonitor.height() / 7 - rectangleRestore.bottom());

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


   index display::get_good_restore(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleHintParam, ::user::interaction * pinteraction, ::e_display edisplay)
   {

      ::rectangle_i32 rectangleHint(rectangleHintParam);

      ::rectangle_i32 rectangleWorkspace;

      ::size_i32 sizeMin;

      ::rectangle_i32 rectangleBroad;

      ::rectangle_i32 rectangleCompact;

      ::rectangle_i32 rectangleNormal;

      index iMatchingWorkspace;
      
      if (pinteraction != nullptr)
      {

         information() << "windowing::display get_good_restore interaction is set";

         auto iMonitor = pinteraction->get_preferred_restore(*prectangle);

         if (iMonitor >= 0)
         {

            return iMonitor;

         }

         sizeMin = pinteraction->get_window_minimum_size();

         iMatchingWorkspace = pinteraction->calculate_broad_and_compact_restore(&rectangleWorkspace, sizeMin, rectangleHint);

         if (iMatchingWorkspace < 0)
         {

            get_main_monitor(rectangleHint);

            iMatchingWorkspace = pinteraction->calculate_broad_and_compact_restore(&rectangleWorkspace, sizeMin, rectangleHint);

            if (iMatchingWorkspace < 0)
            {

               return -1;

            }

         }
         
         if (rectangleHint.left() < rectangleWorkspace.left())
         {

            rectangleHint.left() = rectangleWorkspace.left() + 5;

         }

         if(rectangleHint.top() < rectangleWorkspace.top())
         {
            
            rectangleHint.top() = rectangleWorkspace.top() + 5;
            
         }

         information() << "windowing::display get_good_restore rectangleHint.top_left() : " << rectangleHint.top_left();

         rectangleBroad = pinteraction->m_rectangleRestoreBroad;

         rectangleCompact = pinteraction->m_rectangleRestoreCompact;

         rectangleNormal = pinteraction->get_window_normal_stored_rectangle();

         if(rectangleNormal.size() < sizeMin)
         {

            rectangleNormal.set_size(rectangleWorkspace.size() * 3 / 5);

            rectangleNormal.top_left() = rectangleWorkspace.size() * 1 / 10;

         }

      }
      else
      {

         sizeMin = m_pwindowing->get_window_minimum_size();

         iMatchingWorkspace = get_best_workspace(&rectangleWorkspace, rectangleHint);
         
         if(rectangleHint.left() < (rectangleWorkspace.left() + rectangleWorkspace.width() / 48)
            || rectangleHint.top() < (rectangleWorkspace.top() + rectangleWorkspace.height() / 48))
         {
            
            rectangleHint.left() = rectangleWorkspace.left() + rectangleWorkspace.width() / 12;
            
            rectangleHint.top() = rectangleWorkspace.top() + rectangleWorkspace.height() / 12;
            
         }

         rectangleBroad.set_size(sizeMin.maximum(rectangleWorkspace.size() * 4 / 5));
         
         rectangleBroad.move_to(rectangleHint.top_left());

         rectangleCompact.set_size(sizeMin.maximum(rectangleWorkspace.size() * 2 / 5));
         
         rectangleCompact.move_to(rectangleHint.top_left());

         rectangleNormal.set_size(sizeMin.maximum(rectangleWorkspace.size() * 3 / 5));

         rectangleNormal.move_to(rectangleHint.top_left());

      }

      ::rectangle_i32 rectanglePlacement;

      if(edisplay == e_display_broad)
      {

         rectanglePlacement = rectangleBroad;

         information() << "windowing::display get_good_restore e_display_broad rectanglePlacement : " << rectanglePlacement;

      }
      else if(edisplay == e_display_compact)
      {

         rectanglePlacement = rectangleCompact;

         information() << "windowing::display get_good_restore e_display_compact rectanglePlacement : " << rectanglePlacement;

      }
      else
      {

         if (rectangleHint.size() == rectangleBroad.size() 
            || rectangleHint.size() == rectangleCompact.size()
            || is_like_maximized(rectangleWorkspace, rectangleHint))
         {

            rectanglePlacement = rectangleNormal;

         }
         else
         {

            rectanglePlacement = rectangleHint;

         }

         information() << "windowing::display get_good_restore e_display_* rectanglePlacement : " << rectanglePlacement;

      }

      if (rectanglePlacement.is_empty())
      {

         rectanglePlacement = rectangleNormal;

      }

      //rectangleRestore.move_to(rectangleHint.top_left());

      //::rectangle_i32 rectangleWorkspaceBitSmaller(rectangleWorkspace);

      //rectangleWorkspaceBitSmaller.deflate(5);

      if (rectanglePlacement.left() < rectangleWorkspace.left()
         || rectanglePlacement.right() > rectangleWorkspace.right()
         || rectanglePlacement.top() < rectangleWorkspace.top()
         || rectanglePlacement.bottom() > rectangleWorkspace.bottom())
      {

         rectanglePlacement.move_to(rectangleNormal.top_left());

         information() << "windowing::display get_good_restore fix (2) rectanglePlacement : " << rectanglePlacement;

      }

      if (rectanglePlacement.right() > rectangleWorkspace.right())
      {

         rectanglePlacement.move_right_to(rectangleWorkspace.right() - 5);

      }
      
      if (rectanglePlacement.left() < rectangleWorkspace.left())
      {

         rectanglePlacement.move_left_to(rectangleWorkspace.left() + 5);

         information() << "windowing::display get_good_restore fix (3) rectanglePlacement : " << rectanglePlacement;

      }
      
      if(rectanglePlacement.bottom() > rectangleWorkspace.bottom())
      {

         rectanglePlacement.move_bottom_to(rectangleWorkspace.bottom() - 5);

      }
      
      if (rectanglePlacement.top() < rectangleWorkspace.top())
      {

         rectanglePlacement.move_top_to(rectangleWorkspace.top() + 5);

         information() << "windowing::display get_good_restore fix (4) rectanglePlacement : " << rectanglePlacement;

      }

      *prectangle = rectanglePlacement;

      information() << "windowing::display get_good_restore final rectanglePlacement : " << rectanglePlacement;

      return iMatchingWorkspace;

   }


   index display::get_good_move(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, ::user::interaction * pinteraction)
   //index display::get_good_move(::rectangle_i32 * prectangle)
   {

      // currently allow any moves of a window!!
      // Including even the ones that would make
      // the window lie completely out of the screen.

      *prectangle = rectangleParam;

      return 0;

      //index iMatchingMonitor = initial_frame_position(prectangle, rectangleParam, true, pinteraction);

      //if (__memcmp(prectangle, &rectangleParam, sizeof(const rectangle_i32 &)))
      //{

      //   return iMatchingMonitor;

      //}
      //else
      //{

      //   return -1;

      //}

   }


   bool display::is_like_maximized(const ::rectangle_i32& rectangleWorkspace, const ::rectangle_i32& rectangle)
   {

      if (rectangle == rectangleWorkspace)
      {

         return true;

      }

      return false;

   }


   bool display::is_like_full_screen(const ::rectangle_i32& rectangleMonitor, const ::rectangle_i32& rectangle)
   {

      if (rectangle == rectangleMonitor)
      {

         return true;

      }

      return false;

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

         rectangle = pinteraction->screen_rectangle(::user::e_layout_lading);

         return get_best_workspace(nullptr, rectangle);

      }

   }



   string_array display::get_wallpaper()
   {

      auto psession = acmesession();

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

      auto psession = acmesession();

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

  
   bool display::would_be_docked(const ::rectangle_i32 & rectangleWouldBeSnapped)
   {

      if (rectangleWouldBeSnapped.is_empty())
      {

         return false;

      }

      ::count iMonitorCount = get_monitor_count();

      ::rectangle_i32 rectangleMonitor;

      ::rectangle_i32 rectangleWorkspace;

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         if (get_monitor_rectangle(iScreen, rectangleMonitor) && get_workspace_rectangle(iScreen, rectangleWorkspace))
         {

            if (would_be_docked_in_monitor(rectangleWouldBeSnapped, rectangleMonitor) ||
               would_be_docked_in_monitor(rectangleWouldBeSnapped, rectangleWorkspace))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool display::would_be_docked_in_monitor(const ::rectangle_i32 & rectangleWouldBeSnapped, const ::rectangle_i32 & rectangleMonitor)
   {

      if (rectangleWouldBeSnapped.left() < rectangleMonitor.left()
         || rectangleWouldBeSnapped.left() > rectangleMonitor.right())
      {

         return false;

      }

      if (rectangleWouldBeSnapped.right() < rectangleMonitor.left()
         || rectangleWouldBeSnapped.right() > rectangleMonitor.right())
      {

         return false;

      }

      if (rectangleWouldBeSnapped.top() < rectangleMonitor.top()
         || rectangleWouldBeSnapped.top() > rectangleMonitor.bottom())
      {

         return false;

      }

      if (rectangleWouldBeSnapped.bottom() < rectangleMonitor.top()
         || rectangleWouldBeSnapped.bottom() > rectangleMonitor.top())
      {

         return false;

      }

      auto sizeMinimum = m_pwindowing->get_window_minimum_size();

      if (rectangleWouldBeSnapped.width() < sizeMinimum.cx() || rectangleWouldBeSnapped.height() < sizeMinimum.cy())
      {

         return false;

      }

      if (rectangleWouldBeSnapped.left() == rectangleMonitor.left())
      {

         if (rectangleWouldBeSnapped.top() == rectangleMonitor.top())
         {

            if (rectangleWouldBeSnapped.bottom() == rectangleMonitor.bottom())
            {

               // left snapping

               return rectangleWouldBeSnapped.right() < rectangleMonitor.right() - sizeMinimum.cx();

            }
            else if (rectangleWouldBeSnapped.right() == rectangleMonitor.right()
               || rectangleWouldBeSnapped.right() < rectangleMonitor.right() - sizeMinimum.cx())
            {

               // top snapping, or;
               // top left snapping

               return rectangleWouldBeSnapped.bottom() < rectangleMonitor.bottom() - sizeMinimum.cy();

            }

         }
         else if (rectangleWouldBeSnapped.top() > rectangleMonitor.top() + sizeMinimum.cy())
         {

            if (rectangleWouldBeSnapped.right() == rectangleMonitor.right()
               || rectangleWouldBeSnapped.right() < rectangleMonitor.right() - sizeMinimum.cx())
            {

               // bottom snapping, or;
               // bottom left snapping

               return true;

            }

         }

      }
      else if (rectangleWouldBeSnapped.right() == rectangleMonitor.right())
      {

         if (rectangleWouldBeSnapped.top() == rectangleMonitor.top())
         {

            if (rectangleWouldBeSnapped.bottom() == rectangleMonitor.bottom())
            {

               // right snapping

               return rectangleWouldBeSnapped.left() > rectangleMonitor.left() + sizeMinimum.cx();

            }
            else if (rectangleWouldBeSnapped.left() > rectangleMonitor.left() + sizeMinimum.cx())
            {

               // top right snapping

               return rectangleWouldBeSnapped.bottom() < rectangleMonitor.bottom() - sizeMinimum.cy();

            }

         }
         else if (rectangleWouldBeSnapped.top() > rectangleMonitor.top() + sizeMinimum.cy())
         {

            if (rectangleWouldBeSnapped.left() > rectangleMonitor.left() + sizeMinimum.cx())
            {

               // bottom right snapping

               return true;

            }

         }


      }

      return false;

   }




   bool display::would_be_restored(const ::rectangle_i32 & rectangleWouldBeRestored)
   {

      if (rectangleWouldBeRestored.is_empty())
      {

         return false;

      }

      ::count iMonitorCount = get_monitor_count();

      ::rectangle_i32 rectangleMonitor;

      ::rectangle_i32 rectangleWorkspace;

      for (index iScreen = 0; iScreen < iMonitorCount; iScreen++)
      {

         if (get_monitor_rectangle(iScreen, rectangleMonitor) && get_workspace_rectangle(iScreen, rectangleWorkspace))
         {

            if (would_be_restored_in_monitor(rectangleWouldBeRestored, rectangleMonitor) ||
               would_be_restored_in_monitor(rectangleWouldBeRestored, rectangleWorkspace))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool display::would_be_restored_in_monitor(const ::rectangle_i32 & rectangleWouldBeRestored, const ::rectangle_i32 & rectangleMonitor)
   {

      if (rectangleWouldBeRestored.left() < rectangleMonitor.left()
         || rectangleWouldBeRestored.left() > rectangleMonitor.right())
      {

         return false;

      }

      if (rectangleWouldBeRestored.right() < rectangleMonitor.left()
         || rectangleWouldBeRestored.right() > rectangleMonitor.right())
      {

         return false;

      }

      if (rectangleWouldBeRestored.top() < rectangleMonitor.top()
         || rectangleWouldBeRestored.top() > rectangleMonitor.bottom())
      {

         return false;

      }

      if (rectangleWouldBeRestored.bottom() < rectangleMonitor.top()
         || rectangleWouldBeRestored.bottom() > rectangleMonitor.bottom())
      {

         return false;

      }

      auto sizeMinimum = m_pwindowing->get_window_minimum_size();

      if (rectangleWouldBeRestored.width() < sizeMinimum.cx() || rectangleWouldBeRestored.height() < sizeMinimum.cy())
      {

         return false;

      }

      auto sizeMargin = sizeMinimum / 8;

      auto rectangleWithMargin = rectangleMonitor;

      rectangleWithMargin.deflate(sizeMargin);

      if (rectangleWithMargin.contains(rectangleWouldBeRestored))
      {

         return true;

      }

      return false;

   }


} // namespace windowing



