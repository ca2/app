#include "framework.h"
//#include "interaction_child.h"
#include "scroll_state.h"
#include "alpha_source.h"
#include "interaction.h"
#include "interaction_graphics_thread.h"
#include "interaction_scaler.h"
#include "interaction_thread.h"
#include "style.h"
#include "user.h"
#include "frame.h"
#include "form.h"
#include "still.h"
#include "size_parent_layout.h"
#include "acme/constant/user.h"
#include "acme/constant/user_key.h"
#include "acme/handler/topic.h"
#include "aura/windowing/placement_log.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/message_prototype.h"
#include "acme/constant/simple_command.h"
#include "acme/exception/interface_only.h"
#include "acme/graphics/graphics/output_purpose.h"
#include "acme/platform/keep.h"
#include "acme/parallelization/synchronous_lock.h"
//#include "acme/parallelization/asynchronous.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/node.h"
#include "acme/platform/timer.h"
#include "acme/platform/timer_array.h"
#include "acme/platform/scoped_restore.h"
//#include "acme/prototype/geometry2d/_enhanced.h"
//#include "acme/prototype/geometry2d/_collection_enhanced.h"
//#include "acme/prototype/geometry2d/_defer_shape.h"
#include "acme/prototype/geometry2d/_text_stream.h"
#include "acme/prototype/string/international.h"
//#include "acme/prototype/time/_string.h"
#include "acme/user/user/_text_stream.h"
#include "acme/user/user/content.h"
#include "acme/user/user/drag.h"
#include "acme/user/user/tool.h"
#include "apex/handler/signal.h"
#include "apex/message/simple_command.h"
#include "apex/user/user/message.h"
#include "aqua/user/controller.h"
#include "aura/graphics/draw2d/clip.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "aura/graphics/draw2d/path.h"
#include "aura/graphics/graphics/graphics.h"
#include "aura/graphics/image/image.h"
#include "aura/message/timer.h"
#include "aura/user/appearance/appearance.h"
#include "aura/user/user/calc_size.h"
#include "aura/user/user/system.h"
#include "aura/windowing/monitor.h"
#include "aura/windowing/window.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/display.h"
#include "aura/windowing/cursor.h"
#include "aura/message/user.h"
#include "aura/graphics/draw2d/graphics_call.h"
#include "aura/graphics/user/control_box_icon.h"
#include "aura/graphics/user/control_box_button.h"
#include "aura/platform/session.h"
#include "aura/platform/application.h"
#include "acme/prototype/geometry2d/item.h"
#include "acme/prototype/geometry2d/_defer_item.h"
#include "acme/prototype/collection/_tuple.h"


#ifdef WINDOWS_DESKTOP
//#include "acme/_operating_system.h"
#endif


CLASS_DECL_AURA::point_i32 __get_top_right();
CLASS_DECL_AURA void __set_top_right(const ::point_i32 & pointTopRight);
CLASS_DECL_AURA::point_i32 __get_bottom_right();
CLASS_DECL_AURA void __set_bottom_right(const ::point_i32 & pointBottomRight);


inline void make_parent_mouse_message(::enum_message & emessage)
{

   emessage = (::enum_message)((::i64)emessage + (::i64)(e_message_parent_mouse_first - e_message_mouse_first));

}

template < typename T >
class particle_primitive :
   virtual public particle
{
public:
   T m_t;

};

#define INFO_LAYOUT_DISPLAY

#define DEBUG_LEVEL 1

#undef EXTRA_LOGGING


CLASS_DECL_AURA::rectangle_i32 bounding_box(const ::user::item * pitem)
{

   if (::is_null(pitem))
   {

      return {};

   }

   if (::is_set(pitem->m_ppath))
   {

      ::rectangle_f64 rectangleBounding;

      pitem->m_ppath->get_bounding_box(rectangleBounding);

      return rectangleBounding;

   }
   else
   {

      return pitem->m_rectangle2;

   }

}

//template < typename R >
//inline int contained_vertex_count(const R & rContains, const R & rContained)
//{
//
//   int iContainedVertexCount = 0;
//
//   if (rContains.contains(rContained.top_left()))
//   {
//
//      iContainedVertexCount++;
//
//   }
//
//   if (rContains.contains(rContained.top_right()))
//   {
//
//      iContainedVertexCount++;
//
//   }
//
//   if (rContains.contains(rContained.bottom_left()))
//   {
//
//      iContainedVertexCount++;
//
//   }
//
//   if (rContains.contains(rContained.bottom_right()))
//   {
//
//      iContainedVertexCount++;
//
//   }
//
//   return iContainedVertexCount;
//
//}
//
//
//template < typename R >
//inline bool is_intersection_simple_region(R & r, R r1, R r2)
//{
//
//   r.intersect(r1, r2);
//
//   if (r.is_null())
//   {
//
//      return true;
//
//   }
//
//   return contained_vertex_count(r1, r2) % 2 == 0 && contained_vertex_count(r2, r1) % 2 == 0;
//
//}


#define MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG 0

int g_iMouseHoverCount = 0;
int g_i134 = 0;
//#define TEST_PRINT_BUFFER

#ifdef WINDOWS_DESKTOP
//#include "aura/operating_system/windows/windowing.h"
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#elif defined(UNIVERSAL_WINDOWS)

//#include "aura/os/universal_windows/_uwp.h"

#endif // WINDOWS_DESKTOP




namespace user
{


   //#ifdef UNIVERSAL_WINDOWS
   //
   //
   //   Agile<::winrt::Windows::UI::Core::CoreWindow>(*interaction::s_get_os_window)(interaction * pinteraction) = &interaction::get_os_window_default;
   //
   //
   //#endif


   interaction::interaction()
   {

      m_ekeyboardmode = e_keyboard_mode_none;

      m_bEmptyAreaIsClientArea = true;

      m_bBarDragScrollLeftButtonDown = false;

      m_bEnableHorizontalBarDragScroll = false;
      m_bHorizontalBarDragScrollingActive = false;
      m_bEnableVerticalBarDragScroll = false;
      m_bVerticalBarDragScrollingActive = false;
      m_pointBarDragScroll = {};
      m_pointBarDragScrollMax = {};

      m_bAutomaticallyStoreWindowRectangle = false;
      m_bPendingSaveWindowRectangle = false;
      m_bLoadingWindowRectangle = false;

      m_bAutoResize = false;
      m_bNeedAutoResizePerformLayout = false;

      //m_bVisualChanged = false;


#ifdef REPORT_OFFSETS

      if ((offsetof(::user::interaction, m_oswindow) & 4) != 0)
      {

         throw "invalid alignment";

      }

#endif

      user_interaction_common_construct();

   }


   void interaction::user_interaction_common_construct()
   {

      m_edisplayOwnedBeforeHidden = e_display_normal;

      m_bIgnoringSketchToLading = false;

      m_bExtendOnParent = false;
      m_bExtendOnParentIfOnlyClient = false;
      m_bExtendOnParentHostingArea = false;

      m_bToolWindow = false;
      m_bMessageWindow = false;
      m_bCompositedFrameWindow = false;

      m_bOnDraw = true;

      m_bEdgeGestureDisableTouchWhenFullscreen = false;
      //m_bScreenVisible = false;

      m_bPendingChildrenZorder = false;

      m_bMouseHoverOnCapture = false;
      //m_bMouseHover = false;
      m_bDefaultClickHandling = false;
      m_bDefaultMouseHoverHandling = false;
      m_bDefaultParentMouseMessageHandling = false;
      m_bDefaultEditHandling = false;
      m_bDefaultKeyboardMultipleSelectionHandling = false;
      m_bDefaultDataUpdateHandling = false;
      //m_bLockLadingToLayout = false;
      m_bParentScrollX = false;
      m_bParentScrollY = false;
      m_bUserInteractionHost = false;
      m_bEnableDragClient = false;
      m_bEnableDragResize = false;

      //m_pinteractiondraw2d = nullptr;

      m_bLadingToLayout = false;
      m_bContextOffsetLadingToLayout = false;

      m_bUpdateBuffer = false;
      m_bUpdateScreen = false;
      m_bUpdateWindow = false;


      //m_uUserInteractionFlags = 0;

      //m_bEnableDragClient = false;

      //m_bEnableDragResize = false;

      //m_bTaskPending = true;

      //m_pwindowBase = nullptr;

      m_bEdgeGestureDisableTouchWhenFullscreen = true;

      //m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown = false;

      m_bUserInteractionHost = false;

      m_bMouseHoverOnCapture = false;

      m_bCompositedFrameWindow = true;

      //m_oswindow = nullptr;

      //m_playout = nullptr;

      //m_puserinteractionParent = nullptr;

      m_bDerivedHeight = false;

      m_bLayoutModified = false;

      m_ewindowflag += e_window_flag_enable | e_window_flag_graphical;

      //#ifdef __APPLE__

      //this->m_ewindowflag |= e_window_flag_postpone_visual_update;

      //#endif

      //m_bFocus = false;

      m_bParentScrollX = true;
      m_bParentScrollY = true;

      m_bUserInteractionSetFinish = false;

      m_bOverdraw = false;

      //m_bDefaultEditHandling = false;

      //m_bDefaultClickHandling = false;

      //m_bDefaultMouseHoverHandling = false;

      //m_bDefaultKeyboardMultipleSelectionHandling = false;

      m_iIndex = -1;

      m_ewindowflag |= e_window_flag_enable;


      m_bOffScreenRender = false;

      m_uiUserInteractionFlags = 0;

      m_eupdown = ::user::interaction::e_updown_normal_frame;

      //m_playout = NULL;

      m_bWfiUpDownTarget = false;

      //m_puserinteraction = this;

      m_dItemHeight = -1;

      m_flagNonClient.add(e_non_client_background);

      m_flagNonClient.add(e_non_client_focus_rect);

      //m_bMouseHover = false;

      m_bNeedRedraw = false;

      m_bRedrawOnVisible = false;

      //m_bUpdateVisual = false;

      m_bNeedPerformLayout = false;

      m_bNeedLayout = false;

      //m_bNeedCheckChildrenLayout = false;

      //m_bLockLadingToLayout = false;

      m_bRedrawing = false;

      m_bWorkspaceFullScreen = false;

      m_bHideOnTransparentFrame = false;

      m_bCursorInside = false;

      m_bModal = false;

      m_bRectOk = false;

      m_bMessageWindow = false;

      m_bVoidPaint = false;

      m_bBackgroundBypass = false;

      m_bSaveWindowRect = false;

      m_bEnableSaveWindowRect2 = false;

      //m_bDefaultWalkPreTranslateParentTree = false;

      m_bMoveWindow = false;

      m_bSizeMove = false;

      //m_bEatsDoubleClick = true;

      //m_pointScroll.x() = 0;
      //m_pointScroll.y() = 0;
      //m_palphasource = nullptr;

      m_pform = nullptr;
      //m_pformParent = nullptr;


      // Control Member Variables BEGIN
      m_puiLabel = nullptr;
      //m_pdrawcontext = nullptr;
      //      m_pdescriptor = nullptr;
      m_bControlExCommandEnabled = true;
      m_pform = nullptr;
      m_bDefaultWalkPreTranslateParentTree = true;
      m_bIdBound = false;
      // Control Member Variables END

      m_atom.is_empty();
      //m_iItem = 0;
      m_econtroltype = e_control_type_none;
      m_bTransparent = false;
      m_bCreated = false;
      m_edatatype = e_control_data_type_string;
      m_flagsfunction.clear();
      //m_controlmap.erase_all();
      m_bSubclassed = false;
      //m_iSubItem = -1;
      //m_iColumn = -1;

      m_bClipRectangle = false;

      //m_puserinteractionTopLevel = nullptr;
      //m_puserframeTopLevel = nullptr;
      //m_puserframeParent = nullptr;
      m_bFullScreen = false;

      //      printf("interaction::common_construct - m_pwindow (0x%" PRI0xPTR ")\n", (uptr) m_pwindow);
      //
      //      fflush(stdout);

   }


   interaction::~interaction()
   {

   }


   void interaction::on_initialize_particle()
   {

      //__defer_construct_new(m_puseritema);

      if (m_atom.is_empty())
      {

         m_atom = ::type(this).name();

      }

      ::user::interaction_base::on_initialize_particle();

      if (m_bEnableDragClient)
      {

         m_bDefaultMouseHoverHandling = true;

         m_bDefaultClickHandling = true;

      }

      defer_create_synchronization();

   }



   //class control_descriptor & interaction::descriptor()
   //{

   //   return *m_pdescriptor;

   //}


   //const class control_descriptor & interaction::descriptor() const
   //{

   //   return *m_pdescriptor;

   //}

   ::user::interaction * interaction::user_interaction()
   {

      return this;

   }


   bool interaction::_001CanEnterScreenSaver()
   {

      return true;

   }


   void interaction::_001Maximize()
   {

      display(e_display_zoomed);

      set_need_redraw();

      post_redraw();

      //return true;

   }


   void interaction::_001Restore()
   {

      display(e_display_normal);

      set_need_redraw();

      post_redraw();

      //return true;

   }


   void interaction::_001Minimize()
   {

      display_system_minimize();

      set_need_redraw();

      post_redraw();

      //return true;

   }


   //   void interaction::set_restored_rectangle(const ::rectangle_i32 & rectangleRestored)
   //   {
   //
   //   }


   bool interaction::set_position(const ::point_i32 & point, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto pointNew = point;

      if (!on_set_position(pointNew, elayout))
      {

         //information() << "interaction::set_position !on_set_position";

//         if (::is_set(pgraphics) && elayout == ::user::e_layout_layout)
//         {
//
//            pointNew = layout().layout().m_point2;
//
//            layout().sketch().m_point2 = pointNew;
//
//            layout().lading().m_point2 = pointNew;
//
//         }

         return false;

      }

      if (::is_null(get_parent()))
      {

         int x = point.x();

         int y = point.y();

         if (x < 100 || y < 100)
         {

            //informationf("user::interaction set_position x or y < 100 (%d, %d)", x, y);

         }

      }

      m_layout.m_statea[elayout].set_visual_state_origin(pointNew);

      if (windowing_window() && elayout == e_layout_sketch)
      {

         auto size = m_layout.m_statea[elayout].m_size;

         window()->placement_log()->add({ pointNew, size });

      }

      if (::is_set(pgraphics) && elayout == ::user::e_layout_layout)
      {

         layout().sketch().m_point2 = pointNew;

         layout().lading().m_point2 = pointNew;

      }

      if (get_parent() != nullptr)
      {

         set_need_redraw({}, pgraphics);

      }

      return true;

   }


   bool interaction::set_size(const ::size_i32 & size, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto sizeNew = size;

      if (!on_set_size(sizeNew, elayout))
      {

         return false;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      auto & layoutstate = layout().m_statea[elayout];

      auto rectangleBefore = layoutstate.raw_rectangle();

      layoutstate.m_size = sizeNew;

      if (::is_set(pgraphics) && elayout == e_layout_layout)
      {

         layout().sketch().m_size = sizeNew;

         layout().lading().m_size = sizeNew;

      }

      if (windowing_window() && elayout == e_layout_sketch)
      {

         auto point = m_layout.m_statea[elayout].origin();

         window()->placement_log()->add({ point, sizeNew });

      }

      auto rectangleAfter = layoutstate.raw_rectangle();

      m_bNeedPerformLayout = true;

      set_need_layout();

      if (get_parent() == nullptr)
      {

         auto rectangleaCertainlyDamaged = get_top_left_oriented_damaged_areas_by_resizing(rectangleAfter,
                                                                                           rectangleBefore, false);

         set_need_redraw(rectangleaCertainlyDamaged, pgraphics);

      }
      else
      {

         auto rectangleaCertainlyDamaged = get_top_left_oriented_damaged_areas_by_resizing(rectangleAfter,
            rectangleBefore, false);

         set_need_redraw(rectangleaCertainlyDamaged, pgraphics);

      }

      if (::is_null(pgraphics))
      {

         post_redraw();

      }

      return true;

   }


   void interaction::_set_size(const ::size_i32 & size, enum_layout elayout)
   {

      auto & layoutstate = layout().m_statea[elayout];

      layoutstate.m_size = size;

   }


   void interaction::set_width(::i32 width, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto size = this->size(elayout);

      size.cx() = width;

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

         if (::is_set(pgraphics) && elayout == e_layout_layout)
         {

            m_layout.m_statea[e_layout_sketch].m_size = size;

            m_layout.m_statea[e_layout_lading].m_size = size;

         }

         m_bNeedPerformLayout = true;

         set_need_layout();

      }

   }


   void interaction::set_height(::i32 height, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto size = this->size(elayout);

      size.cy() = height;

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

         if (::is_set(pgraphics) && elayout == e_layout_layout)
         {

            m_layout.m_statea[e_layout_sketch].m_size = size;

            m_layout.m_statea[e_layout_lading].m_size = size;

         }

         m_bNeedPerformLayout = true;

         set_need_layout();

      }

   }


   void interaction::shift_left(::i32 left, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto point = this->position(elayout);

      auto size = this->size(elayout);

      size.cx() += point.x() - left;

      point.x() = left;

      bool bOnSetSize = on_set_size(size, elayout);

      bool bOnSetPosition = on_set_position(point, elayout);

      if (bOnSetSize && bOnSetPosition)
      {

         m_layout.m_statea[elayout].set_visual_state_origin(point);

         m_layout.m_statea[elayout].m_size = size;

         if (::is_set(pgraphics) && elayout == e_layout_layout)
         {

            m_layout.m_statea[e_layout_sketch].set_visual_state_origin(point);

            m_layout.m_statea[e_layout_sketch].m_size = size;

            m_layout.m_statea[e_layout_lading].set_visual_state_origin(point);

            m_layout.m_statea[e_layout_lading].m_size = size;

         }

         m_bNeedPerformLayout = true;

         set_need_layout();

      }

   }


   void interaction::set_right(::i32 right, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto point = this->position(elayout);

      auto size = this->size(elayout);

      point.x() = right - size.cx();

      if (on_set_position(point, elayout))
      {

         if (::is_null(get_parent()))
         {

            informationf("::user::interaction::set_right");

         }

         m_layout.m_statea[elayout].set_visual_state_origin(point);

         if (::is_set(pgraphics) && elayout == e_layout_layout)
         {

            m_layout.m_statea[e_layout_sketch].set_visual_state_origin(point);

            m_layout.m_statea[e_layout_lading].set_visual_state_origin(point);

         }

      }

   }


   void interaction::set_top(const ::i32 top, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto point = position(elayout);

      point.y() = top;

      if (on_set_position(point, elayout))
      {

         m_layout.m_statea[elayout].m_point2 = point;

         if (::is_set(pgraphics) && elayout == e_layout_layout)
         {

            m_layout.m_statea[e_layout_sketch].m_point2 = point;

            m_layout.m_statea[e_layout_lading].m_point2 = point;

         }

      }

   }


   bool interaction::on_set_position(::point_i32 & point, enum_layout elayout)
   {

      if (point == const_layout().m_statea[elayout].origin())
      {

         return false;

      }

      //information() << "on_set_position : " << point;

      return true;

   }


   bool interaction::on_set_size(::size_i32 & size, enum_layout elayout)
   {

      string strType = typeid(*this).name();

      auto sizeMin = get_window_minimum_size();

      if (size.cx() < sizeMin.cx())
      {

         size.cx() = sizeMin.cx();

      }

      if (size.cy() < sizeMin.cy())
      {

         size.cy() = sizeMin.cy();

      }

      if (size == const_layout().m_statea[elayout].m_size)
      {

         return false;

      }

      //if (const_layout().is_zoomed())
      //{

      //   layout().sketch().display(e_display_normal);

      //}

      if (strType.case_insensitive_contains("control_box"))
      {

         if (strType.case_insensitive_contains("button"))
         {

         }
         else
         {

            //informationf("control_box::on_set_size(" + as_string(size) + ")");

            //if (size.cx() > 500)
            //{

            //   informationf("size.cx() > 500");

            //}

         }

      }

      //information() << "on_set_size : " << size;

      on_change_scroll_state(elayout);

      return true;

   }


   //interaction_draw2d * interaction::get_draw2d()
   //{

   //   if(::is_null(m_pinteractiondraw2d))
   //   {


   //      m_pinteractiondraw2d = __new interaction_draw2d();

   //   }

   //   return m_pinteractiondraw2d;

   //}


   double interaction::point_dpi(double d)
   {

      auto pwindowThis = window();

      double dTransformed = pwindowThis->point_dpi((float)d);

      return dTransformed;

   }


   double interaction::dpiy(double d)
   {

      auto pwindowThis = window();

      double dTransformed = pwindowThis->dpiy((float)d);

      return dTransformed;

   }


   float interaction::get_dpi_for_window()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return 96.0f;

      }

      return pwindowThis->get_dpi_for_window();

   }


   float interaction::get_density_for_window()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return 1.0f;

      }

      return pwindowThis->get_density_for_window();

   }


   ::string interaction::calculate_data_key()
   {

      return m_atom;

   }


   ::string interaction::get_data_key(const ::scoped_string & scopedstrAppend)
   {

      if (m_strDataKey20.is_empty())
      {

         m_strDataKey20 = calculate_data_key();

      }

      return m_strDataKey20 + "." + scopedstrAppend;

   }


   ::windowing::window * interaction::window()
   {

      if (this == top_level())
      {

         return acme_windowing_window()->windowing_window();

      }

      return top_level()->window();

   }


   ::windowing::window * interaction::_window()
   {

      auto puserinteractionTopLevel = ((interaction *)this)->_top_level();

      if (::is_null(puserinteractionTopLevel))
      {

         return nullptr;

      }

      auto pwindow = puserinteractionTopLevel->windowing_window();

      if (::is_null(pwindow))
      {

         if (::is_set(puserinteractionTopLevel->m_puserinteractionParent))
         {

            pwindow = puserinteractionTopLevel->m_puserinteractionParent->windowing_window();

         }

         if (::is_null(pwindow))
         {

            return nullptr;

         }

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}

      return pwindow;

   }


   ::user::copydesk * interaction::copydesk()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return nullptr;

      }

      auto pcopydesk = pwindowThis->copydesk();

      if (::is_null(pcopydesk))
      {

         return nullptr;

      }

      return pcopydesk;

   }


   ::windowing::windowing * interaction::windowing()
   {

      return system()->windowing();

      //auto pwindow = top_level()->window();

      //if (::is_null(pwindow))
      //{

      //   auto psession = get_session();

      //   auto puser = psession->user();

      //   auto pwindowing = puser->windowing();

      //   return pwindowing;

      //}

      //auto pwindowing = pwindow->m_pwindowing;

      //if (::is_null(pwindowing))
      //{

      //   return nullptr;

      //}

      //return pwindowing;

   }


   ::windowing::display * interaction::get_display()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pdisplay = pwindowing->display();

      if (::is_null(pdisplay))
      {

         return nullptr;

      }

      return pdisplay;

   }


   ::user::interaction * interaction::get_host_user_interaction()
   {

      auto psession = get_session();

      if (psession == nullptr)
      {

         return nullptr;

      }

      ::pointer<::user::interaction> puserinteractionHost = psession->m_puserprimitiveHost;

      if (puserinteractionHost)
      {

         return puserinteractionHost;

      }

      return get_wnd();

   }


   //::windowing::window * interaction::window()
   //{

   //   auto puserinteraction = get_host_user_interaction();

   //   if (::is_null(puserinteraction))
   //   {

   //      return nullptr;

   //   }

   //   auto pwindow = puserinteraction->windowing_window();

   //   if (::is_null(pwindow))
   //   {

   //      return nullptr;

   //   }

   //   return pwindow;

   //}


   enum_element interaction::get_default_element()
   {

      return e_element_none;

   }


   ::write_text::font_pointer interaction::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if (pstyle)
      {

         if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   enum_translucency interaction::get_translucency(style * pstyle)
   {

      if (pstyle)
      {

         return pstyle->m_etranslucency;

      }

      return e_translucency_undefined;

   }


   int interaction::get_int(style * pstyle, enum_int eint, ::user::enum_state estate, int iDefault)
   {

      int i;

      if (::is_set(pstyle))
      {

         if (pstyle->get_int(this, i, eint, estate))
         {

            return i;

         }

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pstyleSession = puser->user_style();

      if (pstyleSession->get_int(this, i, eint, estate))
      {

         return i;

      }

      return iDefault;

   }


   double interaction::get_double(style * pstyle, enum_double edouble, ::user::enum_state estate, double dDefault)
   {

      double d;

      if (::is_set(pstyle))
      {

         if (pstyle->get_double(this, d, edouble, estate))
         {

            return d;

         }

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pstyleSession = puser->user_style();

      if (pstyleSession->get_double(this, d, edouble, estate))
      {

         return d;

      }

      return dDefault;

   }


   status<::rectangle_f64> interaction::get_border(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      return nullptr;

   }


   status<::rectangle_f64> interaction::get_padding(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if (get_control_type() == ::user::e_control_type_button)
      {

         ::rectangle_f64 rectangleDefaultPadding(16.0, 8.0, 16.0, 8.0);

         return rectangleDefaultPadding;

      }
      else if (get_control_type() == ::user::e_control_type_menu_button)
      {

         ::rectangle_f64 rectangleDefaultPadding(16.0, 8.0, 16.0, 8.0);

         return rectangleDefaultPadding;

      }
      else
      {

         ::rectangle_f64 rectangleDefaultPadding(2.0, 2.0, 2.0, 2.0);

         return rectangleDefaultPadding;

      }

   }


   status<::rectangle_f64> interaction::get_margin(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if (m_flagNonClient.has(e_non_client_focus_rect))
      {

         double dFocusHeightWidth = get_double(pstyle, ::user::e_double_focus_height_width, estate, 2.0);

         ::rectangle_f64 rectangleDefaultMargin(dFocusHeightWidth, dFocusHeightWidth, dFocusHeightWidth,
                                                dFocusHeightWidth);

         return rectangleDefaultMargin;

      }

      ::rectangle_f64 rectangleDefaultMargin(0.0, 0.0, 0.0, 0.0);

      return rectangleDefaultMargin;

   }


   status<::color::color> interaction::get_color(style * pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if (eelement == e_element_text)
      {

         if (m_statuscolorText.ok())
         {

            return m_statuscolorText;

         }

      }
      else if (eelement == e_element_background)
      {

         if (m_statuscolorBackground.ok())
         {

            return m_statuscolorBackground;

         }

      }

      //if (pstyle)
      //{

      //   switch (eelement)
      //   {
      //   case e_element_background:
      //      if (pstyle->m_colorBackground.is_set())
      //      {

      //         return pstyle->m_colorBackground;

      //      }
      //      break;
      //   case e_element_text:
      //      if (pstyle->m_colorText.is_set())
      //      {

      //         return pstyle->m_colorText;

      //      }
      //      break;
      //   default:
      //      break;
      //   }

      //}

      if (::is_set(pstyle))
      {

         return pstyle->get_color(this, eelement, estate);

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pstyleSession = puser->user_style();

      return pstyleSession->get_color(this, eelement, estate);

   }


   ::user::e_flag interaction::get_draw_flags(::user::style * pstyle)
   {

      return e_null;

   }


   style * interaction::get_style()
   {

      auto pframe = top_level_frame();

      if (pframe && pframe->m_puserstyle)
      {

         return pframe->m_puserstyle;

      }

      auto powner = get_owner();

      if (powner)
      {

         return powner->get_style();

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pstyleSession = puser->user_style();

      return pstyleSession;

   }


   ::user::style * interaction::get_style(::draw2d::graphics_pointer & pgraphics)
   {

      return pgraphics ? get_style(pgraphics->m_puserstyle) : get_style();

   }


   void interaction::on_tsf_activate(bool bActivate)
   {

      windowing_window()->on_tsf_activate(bActivate);

   }


   string interaction::default_id_prefix()
   {

      return ::type(this).name() + "_";

   }


   void interaction::child_set_unique_id(::user::interaction * pinteraction)
   {

      if (pinteraction->m_atom.has_char())
      {

         return;

      }

      string strDefaultIdPrefix;

      string strCandidateId;

      bool bDuplicate = true;

      //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      for (::collection::index iIdSuffix = 1; iIdSuffix <= 1000; iIdSuffix++)
      {

         strCandidateId.formatf("%s_%d", strDefaultIdPrefix.c_str(), iIdSuffix);

         bDuplicate = false;

         for (auto & pinteractionChild : puserinteractionpointeraChild->interactiona())
         {

            if (pinteractionChild->m_atom == strCandidateId)
            {

               bDuplicate = true;

               break;

            }

         }

         if (!bDuplicate)
         {

            break;

         }

      }

      if (bDuplicate)
      {

         //return false;

         return;

      }

      pinteraction->m_atom = strCandidateId;

      //return true;


   }


   /// arguments : control_descriptor
   //bool interaction::add_control(arguments arguments)
   //{

   //   arguments.insert_at(0, this);

   //   auto pdescriptor = __allocate control_descriptor(arguments);

   //   //if (::is_null(pdescriptor->m_puserinteractionParent))
   //   //{

   //   //   pdescriptor->m_puserinteractionParent = this;

   //   //}

   //   ::pointer<interaction>pinteraction = pdescriptor->alloc();

   //   if (!pinteraction)
   //   {

   //      dev_log("type " + pdescriptor->m_type.m_strName + " is not allocatable ::user::interaction");

   //      return false;

   //   }

   //   //auto pdescriptor = __allocate control_descriptor();


   //   //pdescriptor->m_atom = atom;

   //   //pdescriptor->m_type = type;

   //   //pdescriptor->m_playout = playout;

   //   if (!pinteraction->create_interaction(pdescriptor))
   //   {

   //      return false;

   //   }

   //   if (::is_set(pdescriptor->m_playout))
   //   {

   //      pdescriptor->m_playout->on_add_layout(&pinteraction->m_layout);

   //   }

   //   return true;

   //}


   interaction * interaction::get_tooltip()
   {

      return m_ptooltip;

   }


   void interaction::set_tool_window(bool bSet)
   {

      //if (::is_null(window()))
      //{

      //   m_bToolWindow = true;

      //   //return ::error_failed;

      //   return;

      //}

      //auto estatus =

      window()->set_tool_window(bSet);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bToolWindow = bSet;

      //return ::success;

   }


   void interaction::set_reposition(bool bSetThis)
   {

      //_synchronous_lock synchronouslock(mutex_children());

      _set_reposition(bSetThis);

   }


   void interaction::_set_reposition(bool bSetThis)
   {

      if (bSetThis)
      {

         m_bReposition = true;

      }

   }


   void interaction::set_need_layout()
   {

      //m_bNeedPerformLayout = true;

      m_bNeedLayout = true;

      auto pinteraction = this;

      while (true)
      {

         pinteraction = pinteraction->get_parent();

         if (!pinteraction)
         {

            break;

         }

         //pinteraction->m_bNeedCheckChildrenLayout = true;

      }

      //information() << "set_need_layout : " << node()->get_callstack();

   }


   void interaction::set_recalculate_clip_rectangle()
   {

      m_bClipRectangle = false;

      auto children = synchronized_get_children();

      for (auto puserinteraction : children)
      {

         try
         {

            puserinteraction->set_recalculate_clip_rectangle();

         }
         catch (...)
         {

         }


      }

   }


   void interaction::set_need_redraw(
      const ::rectangle_i32_array & rectangleaNeedRedraw,
      ::draw2d::graphics * pgraphics,
      function<void()> function,
      bool bAscendants)
   {

      //if (!is_window())
      //{

      //   warning() << "interaction::set_need_redraw !is_window returning...";

      //   return;

      //}

      if (::is_set(pgraphics))
      {

         if (function)
         {

            throw ::exception(error_wrong_state);

         }

      }

      if (!this->is_window_screen_visible(e_layout_sketch))
      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_setneedredrawa.add({ rectangleaNeedRedraw, function, bAscendants });

#ifdef MORE_LOG

         if (!window())
         {

            if (!this->is_window_screen_visible(e_layout_sketch))
            {

               information() << "set_need_redraw !window() and !sketch.visible m_setneedredrawa.add...";

            }
            else
            {

               information() << "set_need_redraw !window() m_setneedredrawa.add...";

            }

         }
         else if (!this->is_window_screen_visible(e_layout_sketch))
         {



            information() << "set_need_redraw !sketch.visible m_setneedredrawa.add...";

         }
#endif
         return;

      }

#ifdef MORE_LOG
      information() << "set_need_redraw (1)";
#endif
      //if(m_pdragCurrent && m_pdragCurrent->m_eelement == e_element_resize)
      //{


      //   information() << "set_need_redraw while resize";

      //   if(rectangleaNeedRedraw.size() > 0)
      //   {

      //      auto r = rectangleaNeedRedraw[0];

      //      informationf("%d,%d  %d,%d", r.left(), r.top(), r.width(), r.height());

      //   }

      // information() << node()->get_callstack();

      //}

      auto * pinteraction = get_wnd();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto rectanglea = rectangleaNeedRedraw;

      if (rectanglea.is_empty())
      {

         auto rectangle = this->rectangle();

         if (!rectangle.is_null())
         {

            if (m_flagNonClient.has(e_non_client_focus_rect) && keyboard_focus_is_focusable())
            {

               ::draw2d::graphics_pointer pgraphicsGetStyle;

               auto pstyle = get_style(pgraphicsGetStyle);

               auto rectangleFocusRectExtraMargin = pstyle->simple_ui_focus_rect_extra_margin(this);

               rectangle.inflate(rectangleFocusRectExtraMargin);

            }

         }

         rectanglea.add(rectangle);

      }

      if (::is_set(pgraphics))
      {

         for (auto & rectangleHost : rectanglea)
         {

            if (!rectangleHost.is_null())
            {

               client_to_host(e_layout_lading)(rectangleHost);

            }

         }

         pgraphics->user_redraw()->set_need_redraw(rectanglea);

         return;

      }

      pinteraction->m_bNeedRedraw = true;

      //auto edisplayRequest = pinteraction->layout().sketch().display();

      //auto edisplayState = pinteraction->layout().window().display();

      //if (function || (pinteraction->::is_set(window()) &&
      //   (
      //      layout().sketch().is_screen_visible() || edisplayState != edisplayRequest
      //      )))
      //{

      for (auto & rectangleHost : rectanglea)
      {

         client_to_host()(rectangleHost);

      }

      auto pwindow = pinteraction->m_pacmewindowingwindow;

      if (::is_set(pwindow))
      {

         window()->set_need_redraw(rectanglea, function);

      }

      //}
      post_redraw();

   }


   bool interaction::needs_to_draw(::draw2d::graphics * pgraphics, const ::rectangle_i32 & rectangleNeedsToDraw)
   {

      //return true;

      if (!this->is_this_visible())
      {

         return false;

      }

      //      if (get_host_user_interaction()->has_fps_interest())
      //      {
      //
      //         return true;
      //
      //      }

      if (get_host_user_interaction()->windowing_window()->m_pgraphicsgraphics->is_single_buffer_mode())
      {

         auto * pinteraction = get_wnd();

         if (::is_null(pinteraction))
         {

            pinteraction = this;

         }

         auto rectangle = rectangleNeedsToDraw;

         if (rectangle.is_empty())
         {

            rectangle = raw_rectangle();

            raw_to_host()(rectangle);

         }
         else
         {

            client_to_host()(rectangle);

         }

         bool bNeedsToDraw = pgraphics->user_redraw()->needs_to_draw(rectangle);

         if (!bNeedsToDraw)
         {

            return false;
            //information() << "Opting out from draw!! " << typeid(*this).name() << " " << m_atom.as_string();

         }

      }

      return true;

   }


   void interaction::set_need_load_form_data()
   {

      m_bNeedLoadFormData = true;

      post_message(e_message_need_load_form_data);

   }


   void interaction::set_need_save_form_data()
   {

      m_bNeedSaveFormData = true;

      post_message(e_message_need_save_form_data);

   }


   void interaction::post_redraw(bool bAscendants)
   {

      //      if(!is_window())
      //      {
      //
      //         warning() << "interaction::post_redraw !is_window returning...";
      //
      //         return;
      //
      //      }
      //
      auto * pinteraction = get_host_user_interaction();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto edisplaySketch = pinteraction->layout().sketch().display();

      auto edisplayWindow = pinteraction->layout().window().display();

      auto psession = get_session();

      if ((layout().sketch().is_screen_visible()
         || edisplaySketch != edisplayWindow
         || pinteraction == psession->get_user_interaction_host()))
      {

         //         if(payload("bQueuedPostRedraw").is_true())
         //         {
         //
         //            return;
         //
         //         }
         //
         //         payload("bQueuedPostRedraw") = true;

         auto ptoplevel = top_level();

         if (ptoplevel)
         {

            auto pwindow = ptoplevel->m_pacmewindowingwindow;

            if (::is_set(pwindow))
            {

               information() << "pwindow->post_redraw();";

               pwindow->post_redraw();

            }

         }

      }

   }


   bool interaction::should_redraw_on_mouse_activate()
   {

      return true;

   }


   bool interaction::should_redraw_on_mouse_hover()
   {

      return true;

   }


   bool interaction::should_redraw_on_hover(::item * pitem)
   {

      if (!::is_item_set(pitem))
      {

         return false;

      }

      if (pitem->m_item.m_eelement == e_element_client)
      {

         bool bShouldRedrawOnMouseHover = should_redraw_on_mouse_hover();

         if (!bShouldRedrawOnMouseHover)
         {

            return false;

         }

      }

      //auto * puseritem = user_item(pitem);

      if (!item_rectangle(pitem, ::user::e_layout_sketch))
      {

         if (!item_graphics_path(pitem))
         {

            return false;

         }

      }

      return true;

   }


   ::user::form * interaction::get_form()
   {

      return m_pform;

   }


   ::user::form * interaction::get_parent_form()
   {

      auto pform = get_form();

      if (::is_null(pform))
      {

         return nullptr;

      }

      return pform;

   }


   ::user::element * interaction::get_form_user_element()
   {

      return get_form();

   }


   ::user::element * interaction::get_parent_form_user_element()
   {

      return get_parent_form();

   }


   ::particle * interaction::get_taskpool_container()
   {

      return parent_frame();

   }


   void interaction::set_place_child_title(const ::string & pszTitle)
   {

      payload("place_child_title") = pszTitle;

      //::pointer<::user::place_holder>pholder = get_parent();

      //if (pholder)
      //{

      //   auto pparent = pholder->get_parent();

      //   if (pparent)
      //   {

      //      auto pupdate = new_update();

      //      ptopic->m_atom = id_place_child_title_change;

      //      ptopic->user_interaction() = pholder;

      //      pparent->apply(ptopic);

      //   }

      //}

   }


   ::user::interaction * interaction::get_user_interaction()
   {

      return this;

   }


   ::user::interaction_base * interaction::get_bind_ui()
   {

      if (::is_null(get_session()))
      {

         return nullptr;

      }

      if (m_atomImpact.is_null())
      {

         return nullptr;

      }

      auto psession = get_session();

      return psession->get_bound_ui(m_atomImpact);

   }


   string interaction::get_display_tag()
   {

      return "";

   }


   //interaction * interaction::get_parent_window()
   //{

   //   return get_parent();

   //}


   bool interaction::is_host_top_level()
   {

      return ::is_set(m_puserinteractionParent) && is_top_level();

   }


   //   bool interaction::is_host_window() const
   //   {
   //
   //      auto pwindowThis = window();
   //
   //      if (!pwindow)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      auto pwindow = pwindow.cast<::windowing::window>();
   //
   //      if (!pwindow)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool interaction::is_host_top_level() const
   //   {
   //
   //      auto psession = get_session();
   //
   //      if (::is_null(psession))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      ::pointer<::user::interaction>puserinteractionHost = psession->m_puserprimitiveHost;
   //
   //      if (::is_null(puserinteractionHost))
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      if (m_puserinteractionParent != puserinteractionHost)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return true;
   //
   //   }
   //
   //
   //   bool interaction::is_os_host() const
   //   {
   //
   //      return false;
   //
   //   }


   ::user::element * interaction::get_parent_primitive()
   {

      return get_parent();

   }


   interaction * interaction::get_parent()
   {

      if (!m_puserinteractionParent)
      {

         return nullptr;

      }

      if (is_top_level())
      {

         return nullptr;

      }

      return m_puserinteractionParent;

   }


   oswindow interaction::GetParentHandle()
   {

      interaction * puserinteractionParent = get_parent();

      if (puserinteractionParent == nullptr)
      {

         return nullptr;

      }

      return puserinteractionParent->get_safe_oswindow();

   }


   bool interaction::on_before_set_parent(::user::interaction_base * puserinteractionParent)
   {

      return true;

   }


   ::user::interaction_base * interaction::set_parent(::user::interaction_base * puserinteractionParent)
   {

      if (puserinteractionParent == nullptr && get_parent() == nullptr)
      {

         return nullptr;

      }

      if (puserinteractionParent != nullptr && is_descendant(puserinteractionParent, true))
      {

         return get_parent();

      }

      if (!on_before_set_parent(puserinteractionParent))
      {

         return get_parent();

      }

      auto puserthread = user_thread();

      if (puserthread)
      {

         if (::is_set(puserthread->m_puserinteractionbaseaThread))
         {

            puserthread->m_puserinteractionbaseaThread->erase(this);

         }

         //user_thread().release();

      }

      ::pointer<interaction> pparentOld = get_parent();

      if (puserinteractionParent == nullptr)
      {

         auto pwindowNew = __create<::windowing::window>();

         auto strName = get_window_text();

         const ::scoped_string & scopedstrClassName = nullptr;

         m_bEnableSaveWindowRect2 = true;

         on_set_parent(nullptr);

         if (m_ewindowflag & e_window_flag_load_window_rect_on_impl)
         {

            WindowDataLoadWindowRectangle();

         }

         //auto rectangleRequest = this->screen_rectangle(::user::e_layout_sketch);

         //auto pusersystem = __allocate ::user::system();

         //pusersystem->add_visible(is_visible(layout().sketch().display()));

         //pwindowNew->create_host(this, e_parallelization_synchronous);

         //pwindowNew->create_host(this);

         create_window();

         on_after_set_parent();

      }
      else // puserinteractionParent != nullptr
      {

         on_set_parent(puserinteractionParent);

         /*auto pwindowNew = __create_new<::user::interaction_child>();

         pwindowNew->m_puserinteraction = this;*/

         ::pointer<::aura::application> papp = get_app();

         //psession->erase_frame(this); // no more a top level frame if it were one
         papp->erase_user_interaction(this); // no more a top level frame if it were one

         //window() = pwindowNew;

         string strName;

         //i32 iStyle = get_window_long(GWL_STYLE);

         //iStyle |= WS_CHILD;

         //if (is_visible(layout().sketch().display()))
         //{

         //   iStyle |= WS_VISIBLE;

         //}

         ::rectangle_i32 rectangleWindow;

         ::pointer<::user::interaction> pparent = puserinteractionParent;

         if (pparent)
         {

            pparent->get_child_rect(rectangleWindow);

         }

         //if (pwindowOld.is_set())
         //{

         //   pwindowOld->destroy_impl_only();

         //}

         //pwindowNew->create_child(this, pparent);

         //if (!pwindowNew->create_child(this, pparent))
         //{

         //   throw ::exception(error_failed, "could not impl interaction");

         //}
         //else
         {

            on_after_set_parent();

         }

      }

      return pparentOld;

   }


   bool interaction::pre_message_handler(::message::key *& pkey, bool & bKeyMessage, ::message::message * pmessage)
   {

      auto emessage = pmessage->m_atom.as_emessage();

      if (emessage == e_message_left_button_down)
      {

         //         auto psession = get_session();
         //
         //         try
         //         {
         //
         //            psession->set_key_pressed(::user::e_key_left_button, true);
         //
         //         }
         //         catch (...)
         //         {
         //
         //         }

      }
      else if (emessage == e_message_left_button_up)
      {

         //         auto psession = get_session();
         //
         //         try
         //         {
         //
         //            psession->set_key_pressed(::user::e_key_left_button, false);
         //
         //         }
         //         catch (...)
         //         {
         //
         //         }

      }
      else if (emessage == e_message_right_button_down)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_right_button, true);

         }
         catch (...)
         {

         }

      }
      else if (emessage == e_message_right_button_up)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_right_button, false);

         }
         catch (...)
         {

         }

      }
      else if (emessage == e_message_middle_button_down)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_middle_button, true);

         }
         catch (...)
         {

         }

      }
      else if (emessage == e_message_middle_button_up)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_middle_button, false);

         }
         catch (...)
         {

         }

      }

      bKeyMessage = emessage == e_message_key_down ||
         emessage == e_message_key_up ||
         emessage == e_message_char ||
         emessage == e_message_text_composition
#ifdef WINDOWS_DESKTOP
         || emessage == e_message_sys_key_down
         || emessage == e_message_sys_key_up
         || emessage == e_message_sys_char
         || emessage == e_message_ime_key_down
         || emessage == e_message_ime_key_up
         || emessage == e_message_ime_char
         || emessage == e_message_ime_select
         || emessage == e_message_ime_set_context
         || emessage == e_message_ime_start_composition
         || emessage == e_message_ime_composition
         || emessage == e_message_ime_composition_full
         || emessage == e_message_ime_notify
         || emessage == e_message_ime_end_composition
         || emessage == e_message_input_language
#endif
         ;

      if (bKeyMessage)
      {

         if (emessage == e_message_key_down)
         {

            informationf("e_message_key_down");

         }

         pkey = dynamic_cast <::message::key *> (pmessage);

         if (pkey)
         {

            windowing()->set(pkey, pkey->m_oswindow, pkey->m_pwindow, pkey->m_atom, pkey->m_wparam, pkey->m_lparam);

         }

         if (emessage == e_message_key_down || emessage == e_message_sys_key_down)
         {

            auto psession = get_session();

            try
            {

               psession->set_key_pressed(pkey->m_ekey, true);

            }
            catch (...)
            {

            }

         }
         else if (emessage == e_message_key_up || emessage == e_message_sys_key_up)
         {

            auto psession = get_session();

            try
            {

               psession->set_key_pressed(pkey->m_ekey, false);

            }
            catch (...)
            {

            }

         }

      }

      if (::is_set(this))
      {

         this->pre_translate_message(pmessage);

      }

      if (pmessage->m_bRet)
      {

         return true;

      }

      return false;

   }


   //   void interaction::on_set_keyboard_focus()
   //   {
   //
   //      if (get_parent() != nullptr)
   //      {
   //
   //         on_reset_focus_start_tick();
   //
   //         // get_keyboard_focus will return the control with focus
   //
   //         auto psession = get_session();
   //
   //         auto puserinteractionHost = psession->get_user_interaction_host();
   //
   //         if (puserinteractionHost == this)
   //         {
   //
   //            return;
   //
   //         }
   //
   //         ::pointer<::aura::application>papp = get_app();
   //
   //         if (papp)
   //         {
   //
   //            // return true to set focus to this control
   //            papp->keyboard_focus_OnSetFocus(this);
   //
   //         }
   //
   //         auto einputtypePreferred = preferred_input_type();
   //
   //         if (keyboard_focus_is_focusable() && einputtypePreferred == e_input_type_text)
   //         {
   //
   //            if (psession->get_user_interaction_host())
   //            {
   //
   //               auto puserinteractionHost = psession->get_user_interaction_host();
   //
   //               if (puserinteractionHost)
   //               {
   //
   //                  puserinteractionHost->edit_on_set_focus(this);
   //
   //               }
   //
   //            }
   //
   //            show_software_keyboard(this);
   //
   //         }
   //
   //         auto ptopic = create_topic(::id_set_focus);
   //
   //         ptopic->m_puserelement = this;
   //
   //         route(ptopic);
   //
   //         // Finished setting focus, finally... Uff!
   //
   //         // Now notify it is done...
   //
   //         post_message(e_message_set_focus);
   //
   //      }
   //
   //   }


   //   void interaction::on_kill_keyboard_focus()
   //   {
   //
   //      auto einputtypePreferred = preferred_input_type();
   //
   //      if (einputtypePreferred == e_input_type_text)
   //      {
   //
   //         auto pinteractionHost = get_host_user_interaction();
   //
   //         pinteractionHost->edit_on_kill_focus(this);
   //
   ////         hide_software_keyboard(this);
   //
   //      }
   //
   //      auto ptopic = create_topic(::id_kill_focus);
   //
   //      ptopic->m_puserelement = this;
   //
   //      route(ptopic);
   //
   //   }


   ::user::element * interaction::get_keyboard_focus()
   {

      auto psession = get_session();

      if (::is_null(psession))
      {

         return nullptr;

      }

      auto puser = psession->user();

      if (::is_null(puser))
      {

         return nullptr;

      }

      auto puserthread = user_thread();

      auto puserinteractionKeyboardFocus = puser->get_keyboard_focus(puserthread);

      if (::is_null(puserinteractionKeyboardFocus))
      {

         return nullptr;

      }

      return puserinteractionKeyboardFocus;

   }


   void interaction::install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_create, pchannel, this, &interaction::on_message_create);
      MESSAGE_LINK(e_message_destroy, pchannel, this, &interaction::on_message_destroy);
      MESSAGE_LINK(e_message_non_client_destroy, pchannel, this, &interaction::on_message_non_client_destroy);
      MESSAGE_LINK(e_message_pos_create, pchannel, this, &interaction::on_message_after_create);
      MESSAGE_LINK(e_message_text_composition, pchannel, this, &interaction::_001OnTextComposition);

      ::user::interaction_base::install_message_routing(pchannel);

      if (m_bMessageWindow)
      {

         //MESSAGE_LINK(MESSAGE_DESTROY              , pchannel, this, &interaction::_001OnDestroyMessageWindow);

      }
      else
      {

         if (m_bDefaultEditHandling)
         {

            add_command_handler("edit_delete", { this, &interaction::_001OnEditDelete });

         }

         MESSAGE_LINK(e_message_close, pchannel, this, &interaction::on_message_close);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction::on_message_size);
         MESSAGE_LINK(e_message_reposition, pchannel, this, &interaction::on_message_move);
         MESSAGE_LINK(e_message_non_client_calc_size, pchannel, this,
                      &interaction::on_message_non_client_calculate_size);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction::on_message_show_window);
         MESSAGE_LINK(e_message_display_change, pchannel, this, &interaction::on_message_display_change);
         MESSAGE_LINK(e_message_subject, pchannel, this, &interaction::on_message_subject);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_double_click, pchannel, this,
                      &::user::interaction::on_message_left_button_double_click);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::interaction::on_message_set_focus);

         if (m_bDefaultParentMouseMessageHandling)
         {

            MESSAGE_LINK(e_message_parent_left_button_down, pchannel, this,
                         &::user::interaction::on_message_parent_left_button_down);
            MESSAGE_LINK(e_message_parent_left_button_up, pchannel, this,
                         &::user::interaction::on_message_parent_left_button_up);
            MESSAGE_LINK(e_message_parent_mouse_move, pchannel, this,
                         &::user::interaction::on_message_parent_mouse_move);

         }

         if (m_bDefaultDataUpdateHandling)
         {

            MESSAGE_LINK(e_message_need_load_form_data, pchannel, this, &interaction::on_message_need_load_form_data);
            MESSAGE_LINK(e_message_need_save_form_data, pchannel, this, &interaction::on_message_need_save_form_data);

         }

         //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

         //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

         if (m_bDefaultClickHandling)
         {

            MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

            m_bDefaultMouseHoverHandling = true;

#if MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG

            MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &interaction::on_message_middle_button_down);
            MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &interaction::on_message_middle_button_up);

#endif

         }

         MESSAGE_LINK(e_message_mouse_wheel, pchannel, this, &interaction::on_message_mouse_wheel);

         if (m_bDefaultMouseHoverHandling)
         {

            MESSAGE_LINK(e_message_mouse_move, pchannel, this, &interaction::on_message_mouse_move);
            MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &interaction::on_message_mouse_leave);

         }

         //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &::user::interaction::on_message_set_cursor);
         MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);

         if (m_bDefaultEditHandling || m_bDefaultKeyboardMultipleSelectionHandling)
         {

            MESSAGE_LINK(e_message_key_up, pchannel, this, &::user::interaction::on_message_key_up);
            MESSAGE_LINK(e_message_sys_key_down, pchannel, this, &::user::interaction::on_message_key_down);
            MESSAGE_LINK(e_message_sys_key_up, pchannel, this, &::user::interaction::on_message_key_up);
            MESSAGE_LINK(e_message_char, pchannel, this, &::user::interaction::on_message_character);

         }

         MESSAGE_LINK(e_message_enable, pchannel, this, &::user::interaction::_001OnEnable);

      }

      //MESSAGE_LINK(e_message_command, pchannel, this, &interaction::_001OnCommand);
      MESSAGE_LINK(e_message_simple_command, pchannel, this, &interaction::on_message_simple_command);


      MESSAGE_LINK(e_message_right_button_down, pchannel, this, &interaction::on_message_right_button_down);
      MESSAGE_LINK(e_message_right_button_up, pchannel, this, &interaction::on_message_right_button_up);


      //if (m_bDefaultClickHandling)
      //{

      //   install_click_default_mouse_handling(pchannel);
      //
      //}

      //if (m_bDefaultMouseHoverHandling)
      //{

      //   install_hover_default_mouse_handling(pchannel);

      //}

   }


   void interaction::prio_install_message_routing(::channel * pchannel)
   {

      //MESSAGE_LINK(e_message_create, pchannel, this, &interaction::on_message_prio_create);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &interaction::on_message_left_button_down);

   }


   void interaction::on_message_prio_create(::message::message * pmessage)
   {

      //on_after_set_parent();

   }


   void interaction::on_message_non_client_calculate_size(::message::message * pmessage)
   {

      pmessage->m_bRet = true; // avoid any Microsoft-Window-concept-of-non-client-area

   }


   //bool interaction::is_sketch_to_design_locked() const
   //{

   //   if (m_bLockSketchToLayout)
   //   {

   //      return true;

   //   }

   //   auto pparent = get_parent();

   //   if (::is_null(pparent))
   //   {

   //      return false;

   //   }

   //   return pparent->is_sketch_to_design_locked();

   //}


   void interaction::reset_pending(enum_layout elayout)
   {

      m_layout.m_statea[elayout].reset_pending();

   }


   void interaction::set_impact_update_going_on(enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_bImpactUpdateGoingOn = true;

   }


   void interaction::set_display(::e_display edisplay, enum_layout elayout)
   {

      //      if(edisplay == e_display_none)
      //      {
      //
      //         if(!get_parent())
      //         {
      //
      //            information() << "e_display_none";
      //
      //         }
      //         else
      //         {
      //
      //         }
      //
      //      }
      //      else if(edisplay == e_display_hide)
      //      {
      //
      //         information() << "e_display_hide";
      //
      //      }
      //      else
      //      {
      //
      //         if(!get_parent())
      //         {
      //
      //            information() << "!get_parent " << ::as_string(edisplay.m_eenum);
      //
      //         }
      //         else
      //         {
      //
      //            //information() << ::as_string(edisplay.m_eenum);
      //
      //         }
      //
      //      }

      m_layout.m_statea[elayout].m_edisplay = edisplay;

      if (::type(this) == "user::list_box")
      {

         if (!windowing()->is_screen_visible(edisplay))
         {

            information() << "hiding user::list_box";

         }
         else
         {

            information() << "showing user::list_box";

         }

      }
      else if (::type(this).as_string().contains("main_frame"))
      {

         print_line("main_frame");

      }

   }


   void interaction::set_layout_state(const layout_state & state, enum_layout elayout)
   {

      m_layout.m_statea[elayout] = state;

   }


   void interaction::set_activation(::e_activation eactivation, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eactivation = eactivation;

   }


   void interaction::display_stored_state()
   {

#ifdef INFO_LAYOUT_DISPLAY

      //information() << "interaction_layout::display e_display_normal";

#endif

#if DEBUG_LEVEL > 0

      if (get_parent() == nullptr)
      {

         information() << "Top Level Window. Display Request -> normal";

      }

#endif

      auto edisplayStored = window_stored_display();

      if (edisplayStored == e_display_stored_state)
      {

         display(e_display_normal);

      }
      else
      {

         display();

      }

   }


   void interaction::display_zoomed()
   {

      informationf("\ne_display_zoomed\n");

#ifdef INFO_LAYOUT_DISPLAY

      information() << "interaction_layout::display e_display_zoomed";

#endif

      set_display(e_display_zoomed, e_layout_sketch);

      ::rectangle_i32 rectangleRequest = this->screen_rectangle(::user::e_layout_sketch);

      best_workspace(nullptr, rectangleRequest, true, layout().sketch().activation(), layout().sketch().zorder());

   }


   void interaction::display_iconic()
   {

#ifdef INFO_LAYOUT_DISPLAY

      information() << "interaction_layout::display e_display_iconic";

      information() << node()->get_call_stack_trace();

#endif

      set_display(e_display_iconic, e_layout_sketch);

   }


   void interaction::display_full_screen(::collection::index iMonitor, ::e_activation eactivation)
   {

      best_monitor(nullptr, {}, true, e_activation_default, e_zorder_top);

   }


   void interaction::display_previous(bool bScreenVisible)
   {

      auto edisplayPrevious = window_previous_display();

      information() << "display_previous : " << edisplayPrevious;

      if (bScreenVisible && !::is_screen_visible(edisplayPrevious))
      {

         information() << "display_previous not screen visible, using e_display_normal";

         edisplayPrevious = e_display_normal;

      }

      display(edisplayPrevious);

   }


   void interaction::display_normal(::e_display edisplay, ::e_activation eactivation)
   {

#ifdef INFO_LAYOUT_DISPLAY

      //      information() << "interaction_layout::display e_display_restore";

#endif

      if (equivalence_sink(edisplay) == e_display_normal)
      {

         set_display(edisplay, e_layout_sketch);

      }
      else
      {

         set_display(e_display_normal, e_layout_sketch);

      }

      layout().sketch().activation() = eactivation;

   }


   void interaction::display_docked(::e_display edisplay, ::e_activation eactivation)
   {


      if (!is_docking_appearance(edisplay))
      {

         throw ::exception(error_wrong_state);

      }

      set_display(edisplay);

      set_activation(eactivation);

   }


   void interaction::display_notify_icon()
   {

      auto edisplayDesign = layout().design().display();

      information() << "interaction_layout::display e_display_notify_icon edisplayDesign : " << edisplayDesign;

#ifdef INFO_LAYOUT_DISPLAY

      //information() << "interaction_layout::display e_display_notify_icon edisplayDesign : " << edisplayDesign;

#endif

      if (edisplayDesign == e_display_notify_icon
          || edisplayDesign == e_display_iconic
          || !windowing()->is_screen_visible(edisplayDesign))
      {

         display_previous();

      }
      else
      {

         set_display(e_display_notify_icon, e_layout_sketch);

      }

   }


   void interaction::display(::e_display edisplay, ::e_activation eactivation)
   {

      bool bChange = false;

      if (edisplay != const_layout().sketch().display())
      {

         bChange = true;

         if (equivalence_sink(edisplay) == e_display_normal)
         {

            display_normal(edisplay, eactivation);

         }
         else if (::is_docking_appearance(edisplay))
         {

            display_docked(edisplay, eactivation);

         }
         else if (edisplay == e_display_hide || edisplay == e_display_none)
         {

#ifdef INFO_LAYOUT_DISPLAY

            //information() << "interaction_layout::display e_display_hide";

#endif

#if DEBUG_LEVEL > 0

            if (get_parent() == nullptr
                && m_econtroltype != e_control_type_button)
            {

               information() << "Top Level Window. Display Request -> hide";

            }

#endif

            set_display(e_display_hide, e_layout_sketch);

         }
         else if (edisplay == e_display_zoomed)
         {

            display_zoomed();

         }
         else if (edisplay == e_display_iconic)
         {

            display_iconic();

         }
         else if (edisplay == e_display_full_screen)
         {

            informationf("e_display_full_screen");

#ifdef INFO_LAYOUT_DISPLAY

            information() << "interaction_layout::display e_display_full_screen";

#endif
            display_full_screen(-1, eactivation);
            //layout().sketch().display() = e_display_full_screen;

         }
         else if (edisplay == e_display_stored_state)
         {

            display_stored_state();

         }
         else if (edisplay == e_display_notify_icon)
         {

            display_notify_icon();

         }
         else if (edisplay == e_display_default)
         {

#ifdef INFO_LAYOUT_DISPLAY

            //information() << "interaction_layout::display e_display_default";

#endif

            auto edisplayCurrent = layout().sketch().display();

            auto edisplayStored = window_stored_display();

            auto edisplayPrevious = window_previous_display();

            if (edisplayCurrent == e_display_undefined)
            {

               edisplay = e_display_normal;

            }
            else if (::is_screen_visible(edisplayCurrent))
            {

               edisplay = edisplayCurrent;

            }
            else if (::is_screen_visible(edisplayStored))
            {

               edisplay = edisplayStored;

            }
            else if (::is_screen_visible(edisplayPrevious))
            {

               edisplay = edisplayPrevious;

            }
            else
            {

               edisplay = ::e_display_normal;

            }

            set_display(edisplay, e_layout_sketch);

         }
         else
         {

#ifdef INFO_LAYOUT_DISPLAY

            //information() << "interaction_layout::display (unknown)";

#endif

         }

         defer_post_pending_set_need_redraw();

      }

      if (eactivation > const_layout().sketch().activation())
      {

         bChange = true;

         layout().sketch() = eactivation;

      }

      if (bChange)
      {

         if (!sketch_on_display())
         {

            return;

         }

      }

      set_need_redraw();

   }


   bool interaction::defer_post_pending_set_need_redraw()
   {

      if (m_ewindowflag & e_window_flag_window_created)
      {

         if (post_pending_set_need_redraw())
         {

            return true;

         }

      }

      return false;

   }


   bool interaction::post_pending_set_need_redraw()
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_setneedredrawa.has_element() && ::is_screen_visible(layout().sketch().display()))
         {

            for (auto & setneedredraw : m_setneedredrawa)
            {

               set_need_redraw(setneedredraw.m_rectangleaNeedRedraw, nullptr,
                                 setneedredraw.m_function, setneedredraw.m_bAscendants);

            }

         }

         m_setneedredrawa.clear();

      }

      post_redraw();

      return true;

   }


   void interaction::on_set_finish()
   {

      if (!m_bUserInteractionSetFinish)
      {

         m_bUserInteractionSetFinish = true;

         destroy_window();

         return;

         //return error_pending;

      }

      //::user::interaction_base::on_set_finish();

   }


   void interaction::notify_on_destroy(::property_object * pparticle)
   {

      ::user::interaction_base::notify_on_destroy(pparticle);

   }


   void interaction::on_message_destroy(::message::message * pmessage)
   {

      m_ewindowflag += e_window_flag_destroying;

      auto type = ::type(this);

      if (type.name().contains("main_frame"))
      {

         informationf("main_frame on_message_destroy");

      }

      __UNREFERENCED_PARAMETER(pmessage);

      user_interaction_on_destroy();

      pmessage->previous();

   }


   void interaction::on_message_non_client_destroy(::message::message * pmessage)
   {

      //destroy();

      m_ewindowflag |= e_window_flag_destroyed;

   }

   //e_message_post_user
   //   void interaction::on_message_user_post(::message::message * pmessage)
   //   {
   //
   //      if (pmessage->m_wparam == 1)
   //      {
   //
   //         ::pointer<::message::object>pobjectmessage(pmessage);
   //
   //         ::pointer<::message::message>pmessage(pobjectmessage->m_pmatter);
   //
   //         if (pmessage)
   //         {
   //
   //            message_handler(pmessage);
   //
   //         }
   //
   //         pmessage->m_bRet = true;
   //
   //      }
   //      else
   //      {
   //
   //         throw ::exception(error_bad_argument);
   //
   //      }
   //
   //   }


   void interaction::user_interaction_on_hide()
   {

      //if (!m_pdescriptor)
      //{

      //   return;

      //}

      auto psession = get_session();

      if (::is_null(psession))
      {

         return;

      }

      //if (::is_null(window()))
      //{

      //   return;

      //}

      //window()->user_interaction_on_hide();

      // Remark, Kill focus should have been called if this window
      // had focus and is being hidden. At kill focus, the host
      // window m_puserinteractionFocus member should haven cleared
      // in this case.
      //::user::interaction * pinteraction = get_wnd();

      //if(::is_set(pinteraction) && pinteraction != this && pinteraction->get_keyboard_focus()== this)
      //{

      //   if (pinteraction->get_wnd()->windowing_window()->m_puserinteractionFocus == this)
      //   {


      //   }

      //}

      //clear_fps_interest();

      //try
      //{

      //   if (!window()->has_destroying_flag())
      //   {

      //      //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());

      //      auto children = synchronized_get_children();

      //      //if (puserinteractionpointeraChild)
      //      {

      //         for (auto puserinteraction : children)
      //         {

      //            try
      //            {

      //               //if (puserinteractionpointeraChild->interaction_at(i).is_set())
      //               {

      //                  // synchronouslock.unlock();

      //                  puserinteraction->send_message(e_message_show_window, 0, 1);

      //                  //synchronouslock.lock();

      //               }

      //            }
      //            catch (...)
      //            {

      //            }

      //         }

      //      }

      //   }

      //}
      //catch (...)
      //{

      //}

      if (m_puserinteractionpointeraOwned)
      {

         try
         {

            for (::collection::index i = 0; i < m_puserinteractionpointeraOwned->interaction_count(); i++)
            {

               try
               {

                  if (::is_set(m_puserinteractionpointeraOwned->interaction_at(i)))
                  {

                     m_puserinteractionpointeraOwned->interaction_at(i)->display(e_display_none);

                  }

               }
               catch (...)
               {

               }

            }

         }

         catch (...)
         {

         }

      }

      try
      {

         if (get_app() != nullptr && get_app()->get_session() != nullptr)
         {

            defer_release_mouse_capture();

         }

      }
      catch (...)
      {

      }

      try
      {

         if (mouse_hover_erase(this))
         {

            //auto pmessage

            //call_message_handler(e_message_mouse_leave);

            auto pmessage = __create_new<::user::message>();

            pmessage->m_atom = e_message_mouse_leave;
            //pmessage->m_pwindow = window();
            //pmessage->m_oswindow = window()->oswindow();
            //pmessage->m_wparam = 0;
            //pmessage->m_lparam = 0;
            //          pmessage->m_time = pevent->time;
            //window()->message_handler(pmessage);
            //window()->message_handler(pmessage);

         }

      }
      catch (...)
      {

      }

      try
      {

         auto pinteraction = get_wnd();

         if (::is_null(pinteraction))
            //|| ::is_null(window())
            //|| window()->has_destroying_flag())
         {

            informationf("destroying os window");

         }
         else
         {

            ::pointer < ::user::interaction > puserinteraction = this;

            user_post([puserinteraction]()
                             {

                                if (puserinteraction->get_parent() != nullptr
                                   && puserinteraction->has_keyboard_focus()
                                   && puserinteraction->is_window_visible(e_layout_sketch))
                                {

                                   puserinteraction->keyboard_set_focus_next();

                                }

                             });

         }

      }
      catch (...)
      {

      }

#ifndef WINDOWS_DESKTOP

      if (get_parent() == nullptr)
      {

         if (is_active_window())
         {

            auto pwindowing = windowing();

            pwindowing->clear_active_window(user_thread(), window());

            //::set_active_window(nullptr);

         }

      }

#endif

      try
      {

         if (::is_set(get_app()))
         {

            get_app()->m_puserprimitiveActive = nullptr;

         }

      }
      catch (...)
      {

      }

      ::user::interaction * puserinteractionParent = get_parent();

      if (puserinteractionParent != nullptr)
      {

         try
         {

            puserinteractionParent->on_hide_child(this);

         }
         catch (...)
         {

         }

      }

      if (get_session())
      {

         {

            _synchronous_lock synchronouslock(psession->synchronization());

            try
            {

               if (psession->m_puiLastUserInputPopup == this)
               {

                  psession->m_puiLastUserInputPopup = nullptr;

               }

            }
            catch (...)
            {

            }

         }

      }

   }


   void interaction::hide()
   {

      display(e_display_hide);

   }


   void interaction::get_text_selection(strsize & iBeg, strsize & iEnd) const
   {


   }


   bool interaction::set_sel_by_name(const ::string & strName)
   {

      return false;

   }


   string interaction::get_sel_by_name()
   {

      return "";

   }


   string interaction::get_hover_by_name()
   {

      return "";

   }


   void interaction::ensure_sel_visible()
   {


   }


   void interaction::set_sel_color(const ::color::hls & hls)
   {


   }


   ::color::hls interaction::get_sel_color()
   {

      return {};

   }


   void interaction::synthesize_scroll_state_x(scroll_state & scrollstate, ::user::enum_layout elayout)
   {

      ::size_i32 sizeTotal = get_total_size(elayout);

      auto sizePage = get_page_size(elayout);

      auto pointOffset = get_context_offset(elayout);

      scrollstate.m_dMinimum = 0.;
      scrollstate.m_dMaximum = sizeTotal.cx();
      scrollstate.m_dPage = sizePage.cx();
      scrollstate.m_dPosition = pointOffset.x();
      scrollstate.m_dTrackingPosition = pointOffset.x();

   }


   void interaction::synthesize_scroll_state_y(scroll_state & scrollstate, ::user::enum_layout elayout)
   {

      auto sizeTotal = get_total_size(elayout);

      auto sizePage = get_page_size(elayout);

      auto pointOffset = get_context_offset(elayout);

      scrollstate.m_dMinimum = 0.;
      scrollstate.m_dMaximum = sizeTotal.cy();
      scrollstate.m_dPage = sizePage.cy();
      scrollstate.m_dPosition = pointOffset.y();
      scrollstate.m_dTrackingPosition = pointOffset.y();

   }


   void interaction::layout_scroll_bar(::user::enum_layout elayout)
   {

   }


   void interaction::on_erase_child(::user::interaction * pinteraction)
   {

   }


   ::pointer_array < ::user::interaction > interaction::synchronized_get_children()
   {

      auto pwindowThis = window();

      _synchronous_lock synchronouslock(pwindowThis ? pwindowThis->m_pparticleChildrenSynchronization : nullptr);

      if (!m_puserinteractionpointeraChild)
      {

         return {};

      }

      auto children = m_puserinteractionpointeraChild->interactiona();

      return ::transfer(children);

   }


   void interaction::erase_children()
   {

      auto children = synchronized_get_children();

      {

         _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

         if (m_puserinteractionpointeraChild)
         {

            m_puserinteractionpointeraChild->interactiona().clear();

         }

      }



      for (auto & pchild : children)
      {

         try
         {

            pchild->m_bLockSketchToDesign = true;

         }
         catch (...)
         {

         }

      }

      for (auto & pchild : children)
      {

         try
         {

            pchild->destroy_window();

         }
         catch (...)
         {

         }

      }

   }


   void interaction::erase_child(::user::interaction * puserinteraction)
   {

      ::pointer < ::user::interaction> p = puserinteraction;

      {

         _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

         if (!m_puserinteractionpointeraChild)
         {

            return;

         }

         m_puserinteractionpointeraChild->erase_interaction(puserinteraction);

      }

      try
      {

         p->destroy_window();

      }
      catch (...)
      {

      }

   }


   void interaction::on_erase_place_holder_child(::user::interaction * pinteraction)
   {

   }


   void interaction::on_hide_child(::user::interaction * pinteraction)
   {

   }


   void interaction::on_hide_place_holder_child(::user::interaction * pinteraction)
   {

   }


   void interaction::user_interaction_on_destroy()
   {

      {

         //single_lock slDraw(get_wnd() == nullptr || ::is_null(window())
         //                   || window().cast<::windowing::window>() == nullptr ? nullptr
         //                                                                                              : window().cast<::windowing::window>()->draw_mutex(),
         //                   true);


         try
         {

            hide();

         }
         catch (...)
         {

         }

      }

      user_interaction_on_hide();

      {

         auto pwindowThis = window();

         //if (pwindow)
         {

            auto ptimerarray = pwindowThis->m_ptimerarray;

            if (ptimerarray)
            {

               ptimerarray->delete_all_timers();

            }

         }

      }

      fps_interest_stop();

      {

         auto puserinteractionTopLevelHost = get_wnd();

         //#ifdef WINDOWS_DESKTOP
         //
         //      if (puserinteraction == this)
         //      {
         //
         //         ::KillTimer((HWND)get_oswindow(), e_timer_transparent_mouse_event);
         //
         //      }
         //
         //#endif



         if (::is_set(puserinteractionTopLevelHost) && puserinteractionTopLevelHost != this)
         {

            auto pwindow = puserinteractionTopLevelHost->windowing_window();

            if (pwindow)
            {

               _synchronous_lock synchronouslock(pwindow->synchronization());

               pwindow->m_userinteractionaMouseHover.erase(this);

            }

         }

      }

      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto pthread = get_thread();

         if (pthread != nullptr)
         {

            if (pthread->get_active_user_prototype() == this)
            {

               pthread->set_active_user_prototype(nullptr);

            }

         }

      }

      auto children = synchronized_get_children();

      for (auto & pinteraction : children)
      {

         try
         {

            pinteraction->destroy_window();

         }
         catch (...)
         {

         }

      }

      ::user::interaction * puserinteractionParent = m_puserinteractionParent;

      if (puserinteractionParent != nullptr)
      {

         try
         {

            //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());

            puserinteractionParent->on_erase_child(this);

            //_synchronous_lock synchronouslock(puserinteractionParent->synchronization());

            //auto puserinteractionpointeraChild = __allocate(
            //   ::user::interaction_array(*puserinteractionParent->m_puserinteractionpointeraChild));

            //if (puserinteractionParent->m_bUserElementOk)
            //{

            //   puserinteractionParent->on_erase_child(this);

            //   puserinteractionpointeraChild->erase_interaction(this);

            //   puserinteractionParent->m_puserinteractionpointeraChild = puserinteractionpointeraChild;

            //}
            //else
            //{

            //   informationf("Parent being destroyed");

            //}

         }
         catch (...)
         {

         }

         //m_puserinteractionParent = nullptr;

      }

      if (!is_message_only_window())
      {

         auto papp = get_app();

         if (papp)
         {

            try
            {

               printf_line("About to erase a %s instance from an aura::application from thread %s!!", typeid(*this).name(), task_get_name().c_str());

               auto pauraapplication = get_app()->m_pauraapplication;

               pauraapplication->erase_user_interaction(this); // guess this may be a frame, it doesn't hurt to erase if this is not there

            }
            catch (...)
            {

            }

            //            if (get_app()->get_session() != nullptr)
            //            {
            //
            //               try
            //               {
            //
            //                  auto papp = get_app()->m_pauraapplication;
            //
            //                  papp->erase_user_interaction(
            //                     this); // guess this may be a frame, it doesn't hurt to erase if this is not there
            //
            //               }
            //               catch (...)
            //               {
            //
            //               }
            //
            //            }

         }

      }

      m_bUserElementOk = false;

      m_ewindowflag -= e_window_flag_is_window;

      auto type = ::type(this);

      if (type.name().contains("simple_scroll_bar"))
      {

         informationf("simple_scroll_bar::user_interaction_on_destroy");

      }


      //task_erase_all();



      //m_pdescriptor.release();

      //m_pwindow.release();

      m_ptooltip.release();

      // windowing_window().release();

   }


   void interaction::on_message_size(::message::message * pmessage)
   {

      ::pointer<::message::size> psize(pmessage);

      pmessage->previous();

      if (psize->m_nType == ::user::e_size_minimized)
      {

         informationf("::user::interaction::on_message_size SIZE_MINIMIZED - ignoring event");

      }
      else if (window()->m_bIgnoreSizeEvent)
      {

         informationf("::user::interaction::on_message_size instructed to m_bIgnoreSizeEvent");

      }

      auto psession = get_session();

      if (this == psession->get_user_interaction_host())
      {

         //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());

         auto children = synchronized_get_children();

         // _synchronous_lock synchronouslock(this->synchronization());

         // auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         // if (puserinteractionpointeraChild)
         {

            for (auto & puserinteraction : children)
            {

               //synchronouslock.unlock();

               puserinteraction->post_message((enum_message)e_message_display_change);

               //synchronouslock.lock();

            }

         }

      }

      if (is_root())
      {

         //_synchronous_lock synchronouslock(this->synchronization());

         auto children = synchronized_get_children();

         //if (m_puserinteractionpointeraChild)
         {

            //if (m_puserinteractionpointeraChild->has_interaction())
            {

               //for (auto & puserinteraction : m_puserinteractionpointeraChild->interactiona())
               for (auto & puserinteraction : children)
               {

                  //synchronouslock.unlock();

                  puserinteraction->set_size(psize->m_size);

                  //synchronouslock.lock();

                  //                  puserinteraction->set_need_layout();
                  //
                  //                  puserinteraction->set_need_redraw();
                  //
                  //                  puserinteraction->post_redraw();

               }

            }

         }

      }

   }


   bool interaction::is_frame_window()
   {

      return false;

   }


   bool interaction::is_impact()
   {

      return false;

   }


   bool interaction::is_menu() const
   {

      return false;

   }


   //   void interaction::show_window()
   //   {
   //
   //      window_show_change_visibility();
   //
   //   }


   void interaction::on_message_move(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void interaction::defer_set_icon()
   {

      //#if defined(CUBE)
      //
      //      return;
      //
      //#endif

#ifdef WINDOWS_DESKTOP

                                                                                                                              //auto pwindowingicon = get_windowing_icon();

      if (get_parent() == nullptr)
      {

         if (application()->m_bImaging)
            //if (!window()->defer_set_icon())
         {

            ::file::path strMatter = get_window_default_matter();

            auto pwindowing = windowing();

            auto pcontext = m_pcontext->m_papexcontext;

            ::file::path pathIcon = "matter://main/icon.png";

            auto picon = window()->load_icon(pathIcon);

            set_windowing_icon(picon);

         }

      }

#endif

   }


   void interaction::set_windowing_icon(::windowing::icon * picon)
   {

      if (::is_null(windowing_window()))
      {

         return;

      }

      //auto estatus =

      windowing_window()->set_icon(picon);

      //if(!estatus)
      //{

//   return estatus;

//}

//return estatus;

   }


   ::windowing::icon * interaction::get_windowing_icon()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return nullptr;

      }

      auto picon = pwindowThis->get_icon();

      if (::is_null(picon))
      {

         return nullptr;

      }

      return picon;

   }


   ::image::icon * interaction::get_draw_icon()
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->set_origin(pgraphics);

   }


   ::point_f64 interaction::get_parent_accumulated_scroll(enum_layout elayout)
   {

      ::point_f64 pointScroll;

      auto puserinteraction = get_parent();

      while (::is_set(puserinteraction))
      {

         auto pointChildScroll = puserinteraction->get_context_offset(elayout);

         if (puserinteraction->m_bParentScrollX)
         {

            pointScroll.x() += pointChildScroll.x();
            //pointScroll.x() += puserinteraction->get_parent()->m_pointDragScroll.x();

         }

         if (puserinteraction->m_bParentScrollY)
         {

            pointScroll.y() += pointChildScroll.y();
            //pointScroll.y() += puserinteraction->get_parent()->m_pointDragScroll.y();

         }

         puserinteraction = puserinteraction->get_parent();

      }

      return pointScroll;

   }


   ::point_f64 interaction::get_accumulated_scroll(enum_layout elayout)
   {

      ::point_f64 pointScroll;

      auto puserinteraction = this;

      while (::is_set(puserinteraction))
      {

         auto pointChildScroll = puserinteraction->get_context_offset();

         if (puserinteraction->m_bParentScrollX)
         {

            pointScroll.x() += pointChildScroll.x();
            //pointScroll.x() += puserinteraction->get_parent()->m_pointDragScroll.x();

         }

         if (puserinteraction->m_bParentScrollY)
         {

            pointScroll.y() += pointChildScroll.y();
            //pointScroll.y() += puserinteraction->get_parent()->m_pointDragScroll.y();

         }

         puserinteraction = puserinteraction->get_parent();

      }

      return pointScroll;

   }


   ::point_f64 interaction::get_scroll(enum_layout elayout)
   {

      ::point_f64 pointScroll;

      auto puserinteraction = this;

      auto pointChildScroll = puserinteraction->get_context_offset();

      if (puserinteraction->m_bParentScrollX)
      {

         pointScroll.x() += pointChildScroll.x();
         //pointScroll.x() += puserinteraction->get_parent()->m_pointDragScroll.x();

      }

      if (puserinteraction->m_bParentScrollY)
      {

         pointScroll.y() += pointChildScroll.y();
         //pointScroll.y() += puserinteraction->get_parent()->m_pointDragScroll.y();

      }

      return pointScroll;

   }


   void interaction::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      //window()->_001OnNcClip(pgraphics);

      if (m_pacmewindowingwindow)
      {

         _001OnTopNcClip(pgraphics);

      }

   }


   void interaction::_001OnTopNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      if (!pgraphics->m_pgraphicsgraphics->is_single_buffer_mode())
      {

         return;

      }

      if (system()->m_paurasystem->draw2d()->graphics_context_does_full_redraw())
      {

         return;

      }

      try
      {

         pgraphics->user_redraw()->apply_clip(host_to_client());

         //pgraphics->reset_clip();

         //if (pgraphics->m_rectangleaNeedRedraw.has_element())
         //{

         //   ::draw2d::clip_group clipgroup;

         //   for (auto rectangleHostNeedRedraw: pgraphics->m_rectangleaNeedRedraw)
         //   {

         //      auto rectangleNeedRedraw = rectangleHostNeedRedraw;

         //      auto hostToClient = host_to_client();

         //      hostToClient(rectangleNeedRedraw);

         //      auto prectangle = __allocate ::draw2d::clip_rectangle();

         //      prectangle->m_item = rectangleNeedRedraw;

         //      clipgroup.add(prectangle);

         //   }

         //   pgraphics->intersect_clip(clipgroup);

         //}

      }
      catch (...)
      {

         throw ::exception(error_exception, "no more a window");

      }

   }


   void interaction::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         ::user::interaction * pinteraction = this;

         if (!m_bClipRectangle)
         {

            ::rectangle_i32 rectangleX;

            ::collection::index i = 0;

            while (pinteraction != nullptr)
            {

               rectangleX = pinteraction->rectangle();

               pinteraction->client_to_host()(rectangleX);

               host_to_client()(rectangleX);

               if (i == 0)
               {

                  m_rectangleClip = rectangleX;

               }
               else
               {

                  m_rectangleClip.intersect(m_rectangleClip, rectangleX);

               }

               pinteraction = pinteraction->get_parent();

               i++;

            }

            m_bClipRectangle = true;

         }

         pgraphics->intersect_clip(m_rectangleClip);

      }
      catch (...)
      {

         throw ::exception(error_exception, "no more a window");

      }

   }


   void interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      if (pgraphics == nullptr)
      {

         throw ::exception(error_bad_argument);

      }

      //scoped_restore(pgraphics->m_puserinteraction);

      //pgraphics->m_puserinteraction = this;

      try
      {

         {

            //_synchronous_lock synchronouslock(this->synchronization());

            if (pgraphics->m_bDraw)
            {

#ifdef __DEBUG

               auto timeStart = ::time::now();

#endif //__DEBUG

               //{

               //   auto pinteraction = get_wnd();

               //   if (pinteraction)
               //   {

               //}

               //}

               //_001OnNcClip(pgraphics);

               ////auto pstyle = get_style(pgraphics);

               //_001OnNcDraw(pgraphics);


#ifdef __DEBUG

               auto timeEnd = ::time::now();

               auto timeElapsed = timeEnd - timeStart;

               if (timeElapsed > 100_ms)
               {

                  informationf("\ndrawing took " + ::as_string(timeElapsed.integral_millisecond()) + "!!");
                  informationf("\ndrawing took more than 100ms to complete!!");
                  informationf("\n");

                  // let's trye to see what happened?
                  //_001OnNcDraw(pgraphics);


               }

#endif //__DEBUG

            }


         }

         {

#ifdef __DEBUG

            auto timeStart = ::time::now();

#endif //__DEBUG

            {

               ::draw2d::save_context savecontext(pgraphics);

               try
               {

                  _001CallOnDraw(pgraphics);

               }
               catch (...)
               {

               }

            }


#ifdef __DEBUG

            auto timeElapsed = timeStart.elapsed();

            if (timeElapsed > 50_ms)
            {

               auto type = ::type(this);

               if (type.name().contains("font_list"))
               {

                  informationf(type + "\n");

               }

#ifdef VERBOSE_LOG


               CATEGORY_INFORMATION(graphics_thread, type.m_strName << " drawing took more than 50ms to complete ("
<< timeElapsed.integral_millisecond() << ")!!\n");

               // let's trye to see what happened?
               //_001CallOnDraw(pgraphics);

#endif

            }

#endif //__DEBUG

         }


      }
      catch (...)
      {

         information() << "Exception: interaction::_001DrawThis %s" << ::type(this).name();

      }

      if (m_puserinteractionParent != nullptr)
      {

         {

#ifdef __DEBUG

            auto timeStart = ::time::now();

#endif //__DEBUG

            on_after_graphical_update();


#ifdef __DEBUG

            auto timeEnd = ::time::now();

            auto timeElapsed = timeEnd - timeStart;

#ifdef VERBOSE_LOG

            if (timeElapsed > 100_ms)
            {

               CATEGORY_INFORMATION(graphics_thread,
                  "\ndrawing took " + as_string(timeElapsed.integral_millisecond()) + "!!");
               information()(e_trace_category_graphics_thread) << "\ndrawing took more than 100ms more than 50ms to complete!!";

               // let's trye to see what happened?
               //on_after_graphical_update();


            }

#endif

#endif //__DEBUG

         }

      }

   }


   void interaction::_001CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!should_draw())
      {

         return;

      }

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      //point_i32 pointScroll = m_pointScroll;

      //if (!pointScroll.is_null())
      //{

      //   pgraphics->offset_origin(-pointScroll.x(), -pointScroll.y());

      //}

      //point_i32 pointDragScroll = m_pointDragScroll;

      //if (!pointDragScroll.is_null())
      //{

      //   pgraphics->offset_origin(-pointDragScroll.x(), -pointDragScroll.y());

      //}

      //on_context_offset(pgraphics);

#ifdef __DEBUG

      auto timeStartWithLock = ::time::now();

#endif

      //_synchronous_lock synchronouslock(this->synchronization());

      {

         if (pgraphics->m_bDraw)
         {

#ifdef __DEBUG

            auto timeStart = ::time::now();

#endif //__DEBUG

            _001OnClip(pgraphics);

            ::rectangle_i32 rectangleDraw;

            rectangleDraw = this->rectangle();

            pgraphics->m_rectangleDraw = rectangleDraw;

            _001OnDraw(pgraphics);

            //#ifdef __DEBUG
            //
            //            auto puseritemHover = user_item(m_pitemHover);
            //
            //            if (puseritemHover)
            //            {
            //
            //               puseritemHover->set_drawn();
            //
            //            }
            //
            //            auto puseritemCurrent = user_item(main_content().m_pitemCurrent);
            //
            //            if (puseritemCurrent)
            //            {
            //
            //               puseritemCurrent->set_drawn();
            //
            //            }
            //
            //            auto timeEnd = ::time::now();
            //
            //            auto timeElapsed = timeEnd - timeStart;
            //
            //#ifdef VERBOSE_LOG
            //
            //            if (timeElapsed > 100_ms)
            //            {
            //
            //               information()(e_trace_category_graphics_thread) << "\ndrawing at " << ::type(this).name() << "!!";
            //               information()(e_trace_category_graphics_thread) << "\ndrawing took " << timeElapsed.integral_millisecond() << +"!!";
            //               information()(e_trace_category_graphics_thread) << "\ndrawing took more more than 100ms more than 50ms to complete!!";
            //               information()(e_trace_category_graphics_thread) << "\n";
            //
            //               // let's trye to see what happened?
            //               //_001OnDraw(pgraphics);
            //
            //            }
            //
            //#endif
            //
            //#endif //__DEBUG

         }

      }

#ifdef __DEBUG

      auto timeEndWithLock = ::time::now();

      auto tickElapsedWithLock = timeEndWithLock - timeStartWithLock;

      if (tickElapsedWithLock > 3_ms)
      {

         //string strType = ::type(this).name();

         //         informationf("\n" + strType + "drawing took " + as_string(tickElapsedWithLock.m_i) + "!!");
         //       informationf("\ndrawing took more than 3ms to complete!!");
         //     informationf("\n");

      }

#endif //__DEBUG

      //pgraphics->offset_origin(pointScroll.x(), pointScroll.y());

   }


   void interaction::_008CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::save_context savecontext(pgraphics);

      try
      {

         set_context_org(pgraphics);

         _synchronous_lock synchronouslock(this->synchronization());

         _008OnDraw(pgraphics);

      }
      catch (...)
      {

      }

   }


   void interaction::on_context_offset_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //::point_i32 pointOffset;

      //if (m_puserinteractionParent != nullptr)
      //{

      //   pointOffset = layout().layout().origin();

      //}

      //auto pointContextOffset = get_context_offset();

      //auto offset = pointOffset - pointContextOffset;

      //pgraphics->offset_origin((::i32)offset.cx(), (::i32)offset.cy());

   }


   void interaction::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   {

      {

         ::point_i32 pointOffset;

         if (m_puserinteractionParent != nullptr)
         {

            pointOffset = layout().layout().origin();

            if (pointOffset.y() == 31)
            {

               //information() << "31";

            }

         }

         pgraphics->offset_origin((::i32)pointOffset.x(), (::i32)pointOffset.y());

      }

      {

         auto pointContextOffset = get_context_offset();

         auto offset = -pointContextOffset;

         pgraphics->offset_origin((::i32)offset.x(), (::i32)offset.y());

      }

   }


   //void interaction::on_context_offset(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ::point_i32 pointOffset;

   //   if (m_puserinteractionParent != nullptr)
   //   {

   //      pointOffset = layout().layout().origin();

   //      if (pointOffset.y() == 31)
   //      {

   //         information() << "31";

   //      }

   //   }

   //   auto pointContextOffset = get_context_offset();

   //   auto offset = pointOffset - pointContextOffset;

   //   pgraphics->offset_origin((::i32)offset.cx(), (::i32)offset.cy());

   //}


   ::particle * interaction::mutex_draw()
   {

      auto puserinteraction = get_wnd();

      if (::is_null(puserinteraction))
      {

         return nullptr;

      }

      //auto pwindow = puserinteraction->window();

      //if (::is_null(pwindow))
      //{

      //   return nullptr;

      //}

      auto pwindow = puserinteraction->window();

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      auto pgraphics = pwindow->m_pgraphicsgraphics;

      if (::is_null(pgraphics))
      {

         return nullptr;

      }

      return pgraphics->synchronization();

   }


   void interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      //point_i32 pointContextOffset = get_context_offset();

      //point_i32 pointDragScroll = m_pointDragScroll;

      //bool bParentScrollX = false;

      //bool bParentScrollY = false;

      try
      {

         //::draw2d::save_context savecontext(pgraphics);

         //on_context_offset(pgraphics);
         //// while drawing layout can occur and machine z-order.
         //// keep this past z-order
         //interaction_pointer_array uia;

         auto children = synchronized_get_children();

         //_synchronous_lock synchronouslock(this->synchronization());

         //auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         //if (puserinteractionpointeraChild)
         {

            //for (auto pinteraction : puserinteractionpointeraChild->interactiona())
            for (auto pinteraction : children)
            {

               try
               {

                  if (!pinteraction)
                  {

                     continue;

                  }

                  if (pinteraction->has_destroying_flag() || !pinteraction->is_window())
                  {

                     informationf("trying to draw window being destroyed");

                     continue;

                  }

                  if (pinteraction->m_bLockGraphicalUpdate)
                  {

                     continue;

                  }

                  if (::is_set(pinteraction) && !pinteraction->is_custom_draw())
                  {

                     //if (!pointScroll.is_null())
                     //{

                     //   if (!bParentScrollX && pinteraction->m_bParentScrollX)
                     //   {

                     //      pgraphics->offset_origin(-pointScroll.x(), 0);
                     //      //pgraphics->offset_origin(-pointDragScroll.x(), 0);

                     //      bParentScrollX = true;

                     //   }
                     //   else if (bParentScrollX && !pinteraction->m_bParentScrollX)
                     //   {

                     //      pgraphics->offset_origin(pointScroll.x(), 0);
                     //      //pgraphics->offset_origin(pointDragScroll.x(), 0);


                     //      bParentScrollX = false;

                     //   }

                     //   if (!bParentScrollY && pinteraction->m_bParentScrollY)
                     //   {

                     //      pgraphics->offset_origin(0, -pointScroll.y());
                     //      //pgraphics->offset_origin(0, -pointDragScroll.y());

                     //      bParentScrollY = true;

                     //   }
                     //   else if (bParentScrollY && !pinteraction->m_bParentScrollY)
                     //   {

                     //      pgraphics->offset_origin(0, pointScroll.y());
                     //      //pgraphics->offset_origin(0, pointDragScroll.y());

                     //      bParentScrollY = false;

                     //   }

                     //}

                     //pinteraction->_000CallOnDraw(pgraphics);

                     //synchronouslock.unlock();

                     ::draw2d::save_context savecontext(pgraphics);

                     pinteraction->defer_do_graphics(pgraphics);


                     //synchronouslock.lock();

                     //{

                     //   //::time t1 = ::time::now();

                     //   pinteraction->_000OnDraw(pgraphics);

                     //   ///::time d1 = t1.elapsed();

                     //   //if(d1.m_i > 50)
                     //   //{

                     //   //   string strType = ::type(pinteraction).name();

                     //   //   if(strType.contains("hello_multiverse") && strType.contains("frame"))
                     //   //   {

                     //   //      informationf(".");

                     //   //   }

                     //   //   CINFO(prodevian)("(more than 50ms)(D) "+strType+"::_000OnDraw took " + as_string(d1.m_i) + "::time.\n");

                     //   //   //pinteraction->_000OnDraw(pgraphics);

                     //   //}

                     //}


                  }

               }
               catch (...)
               {

                  informationf("Exception thrown while drawing user::interaction");

               }

            }

         }

      }
      catch (...)
      {


      }

      //pgraphics->offset_origin(pointScroll.x(), pointScroll.y());

      //if (bParentScrollX && pointContextOffset.x())
      //{

      //   pgraphics->offset_origin(pointContextOffset.x(), 0);

      //}

      //if (bParentScrollY && pointContextOffset.y())
      //{

      //   pgraphics->offset_origin(0, pointContextOffset.y());

      //}

   }


   //   void interaction::do_graphics(::draw2d::graphics_pointer &pgraphics)
   //   {
   //
   //      ::draw2d::save_context savecontext(pgraphics);
   //
   //      payload("draw_control_background_counter") = 0;
   //
   //      payload("nc_draw_0_fill_counter") = 0;
   //
   //      try
   //      {
   //
   //         _000CallOnDraw(pgraphics);
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   ////      auto pwindowing = windowing();
   ////
   ////      if (::is_set(pwindowing) && pwindowing->m_bDrawCursor)
   ////      {
   ////
   ////         ::draw2d::save_context savecontext(pgraphics);
   ////
   ////         try
   ////         {
   ////
   ////            auto pwindowing = windowing();
   ////
   ////            auto pwindowThis = window();
   ////
   ////            auto pointCursor = pwindow->get_cursor_position();
   ////
   ////            screen_to_client(e_layout_design)(pointCursor);
   ////
   ////            auto *pcursor = pwindowing->get_cursor();
   ////
   ////            if (pcursor != nullptr && pgraphics != nullptr)
   ////            {
   ////
   ////               pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   ////
   ////               //pgraphics->draw(pointCursor, pcursor);
   ////
   ////            }
   ////
   ////         }
   ////         catch (...)
   ////         {
   ////
   ////         }
   ////
   ////      }
   //
   //   }


   string interaction::calc_window_class()
   {

#ifdef WINDOWS_DESKTOP

      //return "windows_interaction_impl";

      auto pwindowing = windowing();

      auto strClass = pwindowing->_windows_get_user_interaction_window_class(this);

      return strClass;

      //u32 uStyle = get_window_default_style();

      //string strIcon = get_window_icon_matter();

      //if (strIcon.has_char())
      //{

      //   return windows_calc_icon_window_class(this, uStyle, strIcon);

      //}
      //else
      //{

      //   return windows_get_user_interaction_window_class(this);

      //}

#else

      return "";

#endif

   }


   //   void interaction::_000CallOnDraw(::draw2d::graphics_pointer &pgraphics)
   //   {
   //
   //      if (!(m_ewindowflag & e_window_flag_window_created))
   //      {
   //
   //         set_need_redraw();
   //
   //         post_redraw();
   //
   //         return;
   //
   //      }
   //
   //      auto type = ::type(this);
   //
   //      if (type.name().contains("app_veriwell_keyboard") && type.name().contains("main_frame"))
   //      {
   //
   //         // informationf("app_veriwell_keyboard::main_frame");
   //
   //      }
   //      else if (type.name().contains("plain_edit"))
   //      {
   //
   //         //informationf("plain_edit");
   //
   //      }
   //         //      else if (strType.case_insensitive_contains("font_list"))
   //         //      {
   //         //
   //         //         informationf("font_list");
   //         //
   //         //      }
   //      else if (type.name().contains("combo_box"))
   //      {
   //
   //         //informationf("combo_box");
   //
   //      }
   //
   //      scoped_restore(pgraphics->m_puserinteraction);
   //
   //      pgraphics->m_puserinteraction = this;
   //
   //      auto phostwindow = this->get_host_user_interaction();
   //
   //      if (phostwindow != this)
   //      {
   //
   //         bool bUpdateBuffer = false;
   //
   //         bool bUpdateWindow = false;
   //
   //
   //         //      else if (type.name().contains("list_box"))
   //         //      {
   //         //
   //         //         informationf("list_box");
   //         //
   //         //      }
   //
   //         //if (!is_sketch_to_design_locked())
   //         //{
   //
   //         sketch_to_design(bUpdateBuffer, bUpdateWindow);
   //
   //      }
   //
   //      //}
   //
   //      if (m_bSketchToLayoutLading)
   //      {
   //
   //         m_bSketchToLayoutLading = false;
   //
   //         design_layout(pgraphics);
   //
   //      }
   //
   //      bool bZorder = check_child_zorder();
   //
   //      if (bZorder)
   //      {
   //
   //         design_zorder();
   //
   //      }
   //
   //      process_graphics_call_queue(pgraphics);
   //
   //      if (!is_this_visible(e_layout_design))
   //      {
   //
   //         if (::is_null(get_parent()))
   //         {
   //
   //            informationf("Top Level Window is NOT visible.");
   //
   //         }
   //
   //         if (type.name().contains("experience"))
   //         {
   //
   //            if (type.name().contains("button"))
   //            {
   //
   //               string strTag = m_strInteractionTag;
   //
   //               strTag = "";
   //
   //               if (strTag == "button_close")
   //               {
   //
   //                  informationf("button_close not visible\n");
   //
   //               }
   //               else if (strTag == "button_maximize")
   //               {
   //
   //                  informationf("button_maximize not visible\n");
   //
   //               }
   //               else if (strTag == "button_minimize")
   //               {
   //
   //                  informationf("button_minimize not visible\n");
   //
   //               }
   //               else if (strTag == "button_restore")
   //               {
   //
   //                  informationf("button_restore not visible\n");
   //
   //               }
   //               else if (strTag == "button_dock")
   //               {
   //
   //                  informationf("button_dock not visible\n");
   //
   //               }
   //               else if (strTag == "button_transparent_frame")
   //               {
   //
   //                  informationf("button_transparent_frame not visible\n");
   //
   //               }
   //
   //            }
   //
   //         }
   //
   //         return;
   //
   //      }
   //
   //      if (layout().is_iconic())
   //      {
   //
   //         return;
   //
   //      }
   //
   //      //      if (type.name().contains("list_box"))
   //      //      {
   //      //
   //      //         informationf("list_box");
   //      //
   //      //      }
   //
   //      //      if(m_strInteractionTag.case_insensitive_begins("button_"))
   //      //      {
   //      //
   //      //         informationf("drawing: " + m_strInteractionTag + "\n");
   //      //
   //      //      }
   //      //      else if(m_strInteractionTag.case_insensitive_begins("control_box"))
   //      //      {
   //      //
   //      //         informationf("-------- drawing: " + m_strInteractionTag + "\n");
   //      //
   //      //      }
   //
   //      ::point_i32 pointOffset;
   //
   //      if (m_puserinteractionParent != nullptr)
   //      {
   //
   //         pointOffset = layout().layout().origin();
   //
   //      }
   //
   //      if (!pointOffset.is_null())
   //      {
   //
   //         pgraphics->offset_origin(pointOffset.x(), pointOffset.y());
   //
   //      }
   //
   //      try
   //      {
   //
   //         _000OnDraw(pgraphics);
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      if (!pointOffset.is_null())
   //      {
   //
   //         pgraphics->offset_origin(-pointOffset.x(), -pointOffset.y());
   //
   //      }
   //
   //      //}
   //
   ////}
   ////catch (...)
   ////{
   ////
   ////
   ////}
   //
   //#ifdef REDRAW_HINTING
   //
   //                                                                                                                              {
   //
   //   auto rectangleX = this->rectangle();
   //
   //   ::rectangle_i32 rectangleHint(rectangleX);
   //
   //   pgraphics->SelectClipRgn(nullptr);
   //
   //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //
   //   pgraphics->fill_rectangle(rectangleHint, argb(128, random(128, 255), random(128, 255), random(128, 255)));
   //
   //   //}
   //
   //#endif
   ////      pgraphics->fill_solid_rect_dim(10, 50, 200, 200, argb(128, random(128, 255), random(128, 255), random(128, 255)));
   //
   //
   //      windowing_output_debug_string("\ndo_graphics : after Print");
   //
   //#if HARD_DEBUG
   //
   //                                                                                                                              ::draw2d::graphics_pointer g(e_create);
   //
   //   g->debug();
   //
   //   m_size.cx() = 0;
   //
   //   m_size.cy() = 0;
   //
   //#endif
   //
   //   }
   //
   //
   ////   void interaction::on_graphics(::draw2d::graphics_pointer & pgraphics)
   ////   {
   ////
   ////      windowing_output_debug_string("\n_001Print A");
   ////
   ////      {
   ////
   ////         ::draw2d::save_context savecontext(pgraphics);
   ////
   ////         try
   ////         {
   ////
   ////            _000CallOnDraw(pgraphics);
   ////
   ////         }
   ////         catch (...)
   ////         {
   ////
   ////         }
   ////
   ////      }
   ////
   ////      windowing_output_debug_string("\n_001Print B");
   ////
   ////      auto pwindowing = windowing();
   ////
   ////      if (::is_set(pwindowing) && pwindowing->m_bDrawCursor)
   ////      {
   ////
   ////         {
   ////
   ////            ::draw2d::save_context savecontext(pgraphics);
   ////
   ////            try
   ////            {
   ////
   ////               auto pwindowing = windowing();
   ////
   ////               auto pwindowThis = window();
   ////
   ////               auto pointCursor = pwindow->get_cursor_position();
   ////
   ////               screen_to_client(e_layout_design)(pointCursor);
   ////
   ////               auto * pcursor = pwindowing->get_cursor();
   ////
   ////               if (pcursor != nullptr && pgraphics != nullptr)
   ////               {
   ////
   ////                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   ////
   ////                  //pgraphics->draw(pointCursor, pcursor);
   ////
   ////               }
   ////
   ////            }
   ////            catch (...)
   ////            {
   ////
   ////            }
   ////
   ////         }
   ////
   ////      }
   ////
   ////   }
   //
   ////
   ////   string interaction::calc_window_class()
   ////   {
   ////
   ////#ifdef WINDOWS_DESKTOP
   ////
   ////                                                                                                                              //return "windows_interaction_impl";
   ////
   ////      auto pwindowing = windowing();
   ////
   ////      auto strClass = pwindowing->_windows_get_user_interaction_window_class(this);
   ////
   ////      return strClass;
   ////
   ////      //u32 uStyle = get_window_default_style();
   ////
   ////      //string strIcon = get_window_icon_matter();
   ////
   ////      //if (strIcon.has_char())
   ////      //{
   ////
   ////      //   return windows_calc_icon_window_class(this, uStyle, strIcon);
   ////
   ////      //}
   ////      //else
   ////      //{
   ////
   ////      //   return windows_get_user_interaction_window_class(this);
   ////
   ////      //}
   ////
   ////#else
   ////
   ////      return "";
   ////
   ////#endif
   ////
   ////   }




   //void interaction::defer_draw(::draw2d::graphics_pointer & pgraphics)
   //{

   //   window()->defer_draw(pgraphics);

   //}


   ::user::drawable * interaction::get_drawable()
   {

      return nullptr;

   }


   void interaction::defer_do_graphics(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pacmewindowingwindow)
      {

         window()->defer_do_graphics(pgraphics);

      }
      else
      {

         _000CallOnDraw(pgraphics);

      }

   }


   void interaction::_000TopCallOnLayout(::draw2d::graphics_pointer & pgraphics)
   {

      //bool bZorder = check_child_zorder();

      //if (bZorder)
      //{

      //   layout_zorder();

      //}

      //if (should_perform_layout(pgraphics))
      //{

      //   perform_layout(pgraphics);

      //}

      //if (should_perform_layout(pgraphics))
      //if (pgraphics->m_egraphics & e_graphics_layout)
      //{

      ::string strType = typeid(*this).name();

      if (strType.contains("control_box_button"))
      {

         //information() << "should_perform_layout control_box_button";

      }
      else if (strType.contains("user::list_box"))
      {

         information() << "_000TopCallOnLayout user::list_box";

      }
      else
      {

         debug() << "_000TopCallOnLayout : " << strType;

      }


      perform_layout(pgraphics);

      defer_do_layout(pgraphics);

      //}

      //pgraphics->fill_solid_rectangle({ 100, 100, 200, 200 }, ::color::white);

      //_000CallOnDraw(pgraphics);

   }


   void interaction::_000TopCallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //bool bZorder = check_child_zorder();

      //if (bZorder)
      //{

      //   layout_zorder();

      //}

      //if (should_perform_layout(pgraphics))
      //{

      //   perform_layout(pgraphics);

      //}

      //if (should_perform_layout(pgraphics))
      //if (pgraphics->m_egraphics & e_graphics_layout)
      //{

      //   ::string strType = typeid(*this).name();

      //   if (strType.contains("control_box_button"))
      //   {

      //      //information() << "should_perform_layout control_box_button";

      //   }

      //   perform_layout(pgraphics);

      //   defer_do_layout(pgraphics);

      //}

      //pgraphics->fill_solid_rectangle({ 100, 100, 200, 200 }, ::color::white);

      _000CallOnDraw(pgraphics);

   }


   void interaction::defer_do_layout(::draw2d::graphics_pointer & pgraphics)
   {

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      ::string strType = ::type(this).as_string();

      if (pgraphics->m_egraphics & e_graphics_layout)
      {

         layout_to_design();

         if (m_bLadingToLayout)
         {

            if (layout_layout(pgraphics))
            {

               m_bLadingToLayout = false;

            }

         }

         if (m_bContextOffsetLadingToLayout)
         {

            on_context_offset_layout(pgraphics);

            m_bContextOffsetLadingToLayout = false;

         }

      }

      if (pgraphics->m_egraphics & e_graphics_layout)
      {

         process_graphics_call_queue(pgraphics);

         if (get_parent() != nullptr)
         {

            design_to_window();

         }

      }

      auto children = synchronized_get_children();

      // _synchronous_lock synchronouslock(this->synchronization());

      // if (!m_puserinteractionpointeraChild)
      // {

      //    return;

      // }

      //for (auto & pchild : m_puserinteractionpointeraChild->interactiona())
      for (auto & pchild : children)
      {

         //synchronouslock.unlock();

         try
         {

            if (!pchild)
            {

               continue;

            }

            pchild->defer_do_layout(pgraphics);

         }
         catch (...)
         {

         }

         //synchronouslock.lock();

      }

   }


   void interaction::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      scoped_restore(pgraphics->m_puserinteraction);

      //pgraphics->m_puserinteraction = m_puserinteraction;

      //if (pgraphics->m_egraphics & e_graphics_layout)
      //{

      //   layout_to_design();

      //   if (m_bLadingToLayout)
      //   {

      //      m_bLadingToLayout = false;

      //      layout_layout(pgraphics);

      //   }

      //}

      //if (pgraphics->m_egraphics & e_graphics_layout)
      //{

      //   process_graphics_call_queue(pgraphics);

      //   if (get_parent() != nullptr)
      //   {

      //      layout().window() = layout().design();

      //      layout().design().reset_pending();

      //   }

      //}

      //if (!is_this_visible(e_layout_design))
      //{

      //   if (::is_null(get_parent()))
      //   {

      //      informationf("Top Level Window is NOT visible.");

      //   }

      //   if (type.name().contains("experience"))
      //   {

      //      if (type.name().contains("button"))
      //      {

      //         string strTag = m_strInteractionTag;

      //         strTag = "";

      //         if (strTag == "button_close")
      //         {

      //            informationf("button_close not visible\n");

      //         }
      //         else if (strTag == "button_maximize")
      //         {

      //            informationf("button_maximize not visible\n");

      //         }
      //         else if (strTag == "button_minimize")
      //         {

      //            informationf("button_minimize not visible\n");

      //         }
      //         else if (strTag == "button_restore")
      //         {

      //            informationf("button_restore not visible\n");

      //         }
      //         else if (strTag == "button_dock")
      //         {

      //            informationf("button_dock not visible\n");

      //         }
      //         else if (strTag == "button_transparent_frame")
      //         {

      //            informationf("button_transparent_frame not visible\n");

      //         }

      //      }

      //   }

      //   return;

      //}

      if (layout().is_iconic())
      {

         information() << "_000CallOnDraw exit on is_iconic";

         return;

      }

      //      if (type.name().contains("list_box"))
      //      {
      //
      //         informationf("list_box");
      //
      //      }

      //      if(m_strInteractionTag.case_insensitive_begins("button_"))
      //      {
      //
      //         informationf("drawing: " + m_strInteractionTag + "\n");
      //
      //      }
      //      else if(m_strInteractionTag.case_insensitive_begins("control_box"))
      //      {
      //
      //         informationf("-------- drawing: " + m_strInteractionTag + "\n");
      //
      //      }

      ::point_i32 pointOffset;

      //if (m_puserinteractionParent != nullptr)
      //{

      //   pointOffset = layout().layout().origin();

      //}

      //if (!pointOffset.is_null())
      //{

      //   pgraphics->offset_origin(pointOffset.x(), pointOffset.y());

      //}

      try
      {

         auto pdrawable = get_drawable();

         if (pdrawable)
         {

            pdrawable->_000DrawImpl(pgraphics);

         }
         else
         {

            _000OnDraw(pgraphics);

         }

      }
      catch (...)
      {

      }

      //if (!pointOffset.is_null())
      //{

      //   pgraphics->offset_origin(-pointOffset.x(), -pointOffset.y());

      //}

      m_bUpdateBuffer = true;

      m_bUpdateScreen = true;

   }


   void interaction::queue_graphics_call(const ::function<void(::draw2d::graphics_pointer &)> & function)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      __defer_construct_new(m_pgraphicscalla);

      m_pgraphicscalla->add(__allocate::draw2d::graphics_call(function));

   }


   void interaction::process_graphics_call_queue(::draw2d::graphics_pointer & pgraphics)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_pgraphicscalla)
      {

         while (m_pgraphicscalla && m_pgraphicscalla->has_element())
         {

            auto pcall = m_pgraphicscalla->pick_first();

            synchronouslock.unlock();

            try
            {

               pcall->call(pgraphics);

            }
            catch (...)
            {

            }

            synchronouslock._lock();

         }

      }

   }


   void interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      scoped_restore(pgraphics->m_bInheritDraw);

      //      auto pszType = typeid(*this).name();
      //
      //      if(::string(pszType).case_insensitive_contains("line_layout"))
      //      {
      //
      //         information() << "interaction::_000OnDraw line_layout";
      //
      //      }
      //      else if (::string(pszType).case_insensitive_contains("user::list_box"))
      //      {
      //
      //         information() << "interaction::_000OnDraw user::list_box";
      //
      //      }


      //      if (!pgraphics->m_bInheritDraw)
      //      {
      //         if (!get_parent())
      //         {
      //
      //            information() << "!get_parent !pgraphics->m_bInheritDraw";
      //
      //         }
      //
      //      }

      if (pgraphics->m_bInheritDraw && !(pgraphics->m_egraphics & e_graphics_draw))
      {

         pgraphics->m_bInheritDraw = false;

         //         if (!get_parent())
         //         {
         //
         //            information() << "!get_parent !(pgraphics->m_egraphics & e_graphics_draw)";
         //
         //         }


      }

      if (pgraphics->m_bInheritDraw && !this->is_this_visible())
      {

         //         if (!get_parent())
         //         {
         //
         //            information() << "interaction::_000OnDraw (no parent) (top level) this is not visible";
         //
         //         }
         //         else if (!get_parent())
         //         {
         //
         //            information() << "!get_parent !this->is_this_visible()";
         //
         //         }


         pgraphics->m_bInheritDraw = false;

      }

      if (pgraphics->m_bInheritDraw && !pgraphics->m_bDraw)
      {

         //         if (pgraphics->payload("set_transparent") == "set_transparent")
         //         {
         //
         //            information() << "Not draw (!m_bDraw) !?!?!";
         //
         //         }
         //         else if (!get_parent())
         //         {
         //
         //            information() << "!get_parent !pgraphics->m_bDraw";
         //
         //         }

         pgraphics->m_bInheritDraw = false;

      }

      if (pgraphics->m_bInheritDraw && !needs_to_draw(pgraphics))
      {

         //         ::string strType = ::type(this).name();
         //
         //         if (strType.case_insensitive_contains("impact"))
         //         {
         //
         //            information() << "Not draw (!needs_to_draw)!?!?!";
         //
         //         }
         //         else if (strType.case_insensitive_contains("user::list_box"))
         //         {
         //
         //            information() << "Not draw (!needs_to_draw)!?!?!";
         //
         //         }
         //         else if (!get_parent())
         //         {
         //
         //            information() << "!get_parent Not draw (!needs_to_draw)!?!?!";
         //
         //         }
         //
         //         if (pgraphics->payload("set_transparent") == "set_transparent")
         //         {
         //
         //            //information() << "Not draw (!needs_to_draw)!?!?!";
         //
         //            //if (!needs_to_draw(pgraphics))
         //            //{
         //
         //
         //            //}
         //
         //         }
         //
         //         //return;

         pgraphics->m_bInheritDraw = false;

      }

      if (!pgraphics->m_bInheritDraw)
      {

         //         if (!get_parent())
         //         {
         //
         //            information() << "_000OnDraw exit on !pgraphics->m_bInheritDraw";
         //
         //         }

         return;

      }
      if (!should_draw())
      {
         //         if (!get_parent())
         //         {
         //
         //            information() << "_000OnDraw exit on !should_draw()";
         //
         //         }

         return;

      }

      {


         //point_f64 pointScroll = get_context_offset();

         //if (!pointScroll.is_null())
         //{

         //   pgraphics->offset_origin(-pointScroll.x(), -pointScroll.y());

         //}


         pgraphics->m_dFontFactor = 1.0;

         ::draw2d::save_context savecontext(pgraphics);

         on_context_offset(pgraphics);

         try
         {

            if (!m_bOnDraw)
            {

               //information() << "_000OnDraw exit on !m_bOnDraw";

            }
            else
            {


               //                     auto type = ::type(this);
               //
               //                     ::string strType = type.as_string();
               //
               //                     if (strType.case_insensitive_contains("pane_impact"))
               //                     {
               //
               //                        information() << "pane_impact";
               //
               //                     }
               //                     else if (strType.case_insensitive_contains("app_core_store::impact"))
               //                     {
               //
               //                        debug() << "app_core_store::impact";
               //
               //                     }
               //                     else if (strType.case_insensitive_contains("main_window"))
               //                     {
               //
               //                        //information() << "_000OnDraw";
               //
               //                     }

                                    //if (pgraphics->m_bDraw)
                                    //{

#ifdef __DEBUG

               auto timeStart = ::time::now();

#endif //__DEBUG

               //{

               //   auto pinteraction = get_wnd();

               //   if (pinteraction)
               //   {

               //}

               //}

               //if (is_top_level())
               //{

               _001OnNcClip(pgraphics);

               //}

               //auto pstyle = get_style(pgraphics);

               _001OnNcDraw(pgraphics);

               //         if (type.name().contains("waven::impact"))
               //         {
               //
               //            informationf("waven::impact");
               //         }
               //         else if(strType.case_insensitive_contains("menu_list_impact"))
               //         {
               //
               //            informationf("menu_list_impact");
               //
               //         }
               //   if (!is_custom_draw() && pgraphics->m_pnext == nullptr)
               //   {

               //      set_context_org(pgraphics);

               //   }

               //}
               ////         ::point_i32 pointParentOffset = get_parent_context_offset();
               ////
               ////         pgraphics->offset_origin(-pointParentOffset.x(), -pointParentOffset.y());
               {

                  ::draw2d::save_context savecontextThis(pgraphics);

                  //{

                  //   auto rectangleClient = this->client2_rectangle();

                  //   pgraphics->offset_origin(rectangleClient.left(), rectangleClient.top());

                  //}

                  try
                  {

                     _001DrawThis(pgraphics);

                  }
                  catch (...)
                  {

                     information() << "Exception: interaction::_000OnDraw _001DrawThis %s"
                        << ::type(this).as_string();

                  }

               }

            }

            try
            {

               ///_synchronous_lock synchronouslock(this->synchronization());

               //if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
               {

                  //::draw2d::save_context savecontext(pgraphics);

                  //synchronouslock.unlock();

                  try
                  {

                     _001DrawChildren(pgraphics);

                  }
                  catch (...)
                  {

                     information() << "Exception: interaction::_000OnDraw _001DrawChildren %s"
                        << ::type(this).as_string();

                  }

                  //synchronouslock.lock();

               }

            }
            catch (...)
            {

            }

            if (pgraphics->m_bInheritDraw && should_draw())
            {

               try
               {

                  if (m_bOverdraw)
                  {

                     {

                        auto t1 = ::time::now();

                        _008CallOnDraw(pgraphics);

                        auto d1 = t1.elapsed();

#ifdef VERBOSE_LOG

                        if (d1 > 50_ms)
                        {

                           auto type = ::type(this);

                           CATEGORY_INFORMATION(prodevian, "(more than 50ms)(E) " << type.m_strName << "::_008CallOnDraw took " <<
                              d1.integral_millisecond() << "::time.\n");

                        }

#endif

                     }

                  }

                  try
                  {

                     _001OnNcPostDraw(pgraphics);

                  }
                  catch (...)
                  {



                  }

               }
               catch (...)
               {

               }


            }

         }
         catch (...)
         {

         }

      }

      //}

//               }

   }


   void interaction::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void interaction::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain<::aura::draw_context>::get_last();

      auto rectangleRaw = this->rectangle();

      auto pstyle = get_style(pgraphics);

      ::string strType = ::type(this).name();

      if (get_draw_flags(pstyle) & e_flag_background_bypass)
      {

         if (strType.case_insensitive_contains("font_list"))
         {

            information() << "e_flag_background_bypass";

         }


      }
      else if (get_translucency(pstyle) >= e_translucency_total)
      {


         if (strType.case_insensitive_contains("font_list"))
         {

            information() << "e_translucency_total";

         }


      }
      else if (get_translucency(pstyle) >= e_translucency_present)
      {


         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto colorBackground = get_color(pstyle, e_element_background);

         //if (strType.case_insensitive_contains("font_list"))
         //{

         //   information() << "e_translucency_present";

         //}

         //if (colorBackground.u8_red() == 255)
         //{

         //   informationf("full red");

         //}

         if (colorBackground.is_ok())
         {

            auto esmoothmode = pgraphics->get_smooth_mode();

            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

            pgraphics->fill_rectangle(rectangleRaw, colorBackground);

            pgraphics->set_smooth_mode(esmoothmode);

         }

      }
      else
      {

         auto colorBackground = get_color(pstyle, e_element_background);

         //if (color32_u8_red(crBackground) != 255)
         //{

         //   informationf("no full red");

         //}

         //auto pwindowHost = window();



//         if (colorBackground.m_u8Opacity != 127)
//         {
//
//            information() << "Opacity: " << (::u32) colorBackground.u8_opacity();
//
//         }

         //return;

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleRaw, colorBackground);

         auto phostwindow = get_host_user_interaction();

         auto & iDrawControlBackgroundCounter = phostwindow->payload("draw_control_background_counter").i32_reference();

         auto & iNcDraw0FillCounter = phostwindow->payload("nc_draw_0_fill_counter").i32_reference();

         iDrawControlBackgroundCounter++;

         if (iDrawControlBackgroundCounter >= 2)
         {

            //informationf("draw_control_background_counter >= 2");

         }

         if (iNcDraw0FillCounter <= 0)
         {

            //informationf("nc_draw_0_fill_counter <= 0");

         }

      }

   }


   bool interaction::is_custom_draw()
   {

      return false;

   }


   void interaction::design_to_window()
   {

      ::string strType = ::type(this).name();

      //information() << "type : " << strType << " design_to_window";

      auto edisplayOld = layout().window().display();

      auto edisplayNew = layout().design().display();

      layout().window() = layout().design();

      layout().design().reset_pending();

      try
      {

         if (windowing()->is_screen_visible(edisplayNew)
         && !windowing()->is_screen_visible(edisplayOld))
         {

            //ModifyStyle(0, WS_VISIBLE);

            this->send_message(e_message_show_window, 1);

         }
         else if (!windowing()->is_screen_visible(edisplayNew)
             && windowing()->is_screen_visible(edisplayOld))
         {

            ///ModifyStyle(WS_VISIBLE, 0);

            this->send_message(e_message_show_window, 0);

         }

      }
      catch (...)
      {

      }

      //this->layout().m_statea[e_layout_window].m_edisplay = edisplay;

   }


   void interaction::add(::graphics::output_purpose * poutputpurpose)
   {

      if (::is_null(poutputpurpose))
      {

         return;

      }

      if (poutputpurpose->m_egraphicsoutputpurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         __defer_construct_new(m_pusersystem);

         m_pusersystem->add(poutputpurpose);

         return;

      }

      pwindowThis->add(poutputpurpose);

   }


   void interaction::erase(::graphics::output_purpose * poutputpurpose)
   {

      if (::is_null(poutputpurpose))
      {

         return;

      }

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         return;

      }

      pwindowThis->erase(poutputpurpose);

   }


   void interaction::add_graphical_output_purpose(::particle * pparticle, ::graphics::enum_output_purpose epurpose)
   {

      if (::is_null(pparticle))
      {

         return;

      }

      if (epurpose == ::graphics::e_output_purpose_none)
      {

         return;

      }

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         __defer_construct_new(m_pusersystem);

         m_pusersystem->add(__allocate::graphics::output_purpose(pparticle, epurpose));

         return;

      }

      pwindowThis->add_graphical_output_purpose(pparticle, epurpose);

   }


   void interaction::erase_graphical_output_purpose(::particle * pparticle)
   {

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         return;

      }

      pwindowThis->erase_graphical_output_purpose(pparticle);

   }


   //   ::graphics::enum_output_purpose interaction::most_demanding_graphical_output_purpose() const
   //   {
   //
   //      if(!window())
   //      {
   //
   //         return ::graphics::e_output_purpose_none;
   //
   //      }
   //
   //      return window()->most_demanding_graphical_output_purpose();
   //
   //   }


   bool interaction::has_screen_output_purpose()
   {

      //if(!window())
      //{

      //   return false;

      //}

      return window()->has_screen_output_purpose();

   }


   bool interaction::has_graphical_output_purpose()
   {

      //if(!window())
      //{

      //   return ::graphics::e_output_purpose_none;

      //}

      return window()->has_graphical_output_purpose();

   }


   bool interaction::has_fps_output_purpose()
   {

      //if(!window())
      //{

      //   return false;

      //}

      return window()->has_fps_output_purpose();

   }


   //   ::graphics::enum_output_purpose interaction::graphical_output_purpose()
   //   {
   //
   //      if (this->const_layout().window().display() == e_display_iconic)
   //      {
   //
   //         return ::graphics::e_output_purpose_none;
   //
   //      }
   //      else if (this->const_layout().window().display() == e_display_notify_icon)
   //      {
   //
   //         m_bAutoRefresh = false;
   //
   //      }
   //      else if (!::is_visible(this->const_layout().design().display()))
   //      {
   //
   //         m_bAutoRefresh = false;
   //
   //      }
   //
   //   }


   void interaction::add_fps_interest(::particle * pparticle)
   {

      auto pwindowThis = window();

      if (pwindowThis == nullptr)
      {

         throw ::exception(error_wrong_state);

      }

      return pwindowThis->add_graphical_output_purpose(pparticle, ::graphics::e_output_purpose_fps);

   }


   void interaction::erase_fps_interest(::particle * pparticle)
   {

      auto pwindowThis = window();

      if (pwindowThis == nullptr)
      {

         throw ::exception(error_wrong_state);

      }

      return pwindowThis->erase_graphical_output_purpose(pparticle);

   }



   bool interaction::is_fps_interest(::particle * pparticle)
   {

      auto pwindowThis = window();

      if (pwindowThis == nullptr)
      {

         return false;

      }

      return pwindowThis->has_particle_fps_purpose(pparticle);

   }


   void interaction::default_message_handler(::message::message * pmessage)
   {

      //if (!window())
      //{

      //   return;

      //}

      if (m_pacmewindowingwindow)
      {

         ::pointer < ::windowing::window > pwindow;

         pwindow = m_pacmewindowingwindow;

         if (pwindow)
         {

            pwindow->default_message_handler(pmessage);

         }

      }

   }


   void interaction::_001OnTextComposition(::message::message * pmessage)
   {

      ::pointer<::message::key> ptext = pmessage;

      on_text_composition(ptext->m_strText);

      pmessage->m_bRet = true;

      //      string strText;
      //
      //      bool bOk = false;
      //
      //      try
      //      {
      //
      //         string * pstringText = (string *) (iptr) (lparam) pmessage->m_lparam.m_lparam;
      //
      //         if(pstringText)
      //         {
      //
      //            strText = *pstringText;
      //
      //            ::acme::del(pstringText);
      //
      //            bOk = true;
      //
      //         }
      //
      //      }
      //      catch(...)
      //      {
      //
      //      }
      //
      //      if(bOk)
      //      {
      //
      //         auto puserinteractionFocus = get_keyboard_focus();
      //
      //         if (puserinteractionFocus)
      //         {
      //
      //            puserinteractionFocus->on_text_composition(strText);
      //
      //         }
      //         else
      //         {
      //
      //            on_text_composition(strText);
      //
      //         }
      //
      //      }

   }


   element * interaction::keyboard_set_focus_next(bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

      element * pelement = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);

      auto psession = get_session();

      if (pelement == nullptr || pelement == this)
      {

         clear_keyboard_focus();

      }
      else
      {

         pelement->set_keyboard_focus();

      }

      if (::is_null(psession))
      {

         return nullptr;

      }

      auto puser = psession->user();

      if (::is_null(puser))
      {

         return nullptr;

      }

      auto puserthread = user_thread();

      return puser->get_keyboard_focus(puserthread);

   }


   void interaction::on_message_display_change(::message::message * pmessage)
   {

      //_001FancyInitialFramePlacement();

   }


   void interaction::on_message_subject(::message::message * pmessage)
   {

      ::pointer<::topic> ptopic(pmessage->m_lparam);

      if (!ptopic)
      {

         return;

      }

      if (pmessage->m_wparam == 0)
      {

         route(ptopic);

      }

   }


   //void interaction::on_create_user_interaction()
   //{

   //   m_pwindow = _window();

   //}


   bool interaction::is_branch_current() const
   {

      //if (::is_null(user_thread()))
      //{

      //   return false;

      //}

      auto itaskCurrent = current_itask();

      auto puserthread = ((interaction *)this)->user_thread();

      auto itaskUserInteraction = puserthread->m_itask;

      return itaskCurrent == itaskUserInteraction;

   }


   //::item_pointer interaction::get_user_item(::item * pitem)
   //{

   //   for (auto & pitem : *m_puseritema)
   //   {

   //      if (pitem->m_pitem == pitem)
   //      {

   //         return pitem;

   //      }

   //   }

   //   return nullptr;

   //}


   void interaction::host_post(const ::procedure & procedure)
   {

#ifdef WINDOWS_DESKTOP

      auto puserthread = user_thread();

      if (::is_null(puserthread))
      {

         procedure();

         return;

      }

      puserthread->post(procedure);

#else

      node()->user_post(procedure);

#endif

   }


   void interaction::_user_send(const ::procedure & procedure)
   {

      auto puserthread = user_thread();

      if (::is_null(puserthread))
      {

         procedure();

         return;

      }

      if (puserthread == ::get_task())
      {

         procedure();

         return;

      }

      puserthread->_send(procedure);

   }


   void interaction::_user_post(const ::procedure & procedure)
   {

      auto puserthread = user_thread();

      if (::is_null(puserthread))
      {

         procedure();

         return;

      }

      puserthread->_post(procedure);

   }


   void interaction::_main_send(const ::procedure & procedure)
   {

      window()->_main_send(procedure);

   }


   void interaction::_main_post(const ::procedure & procedure)
   {

      window()->_main_post(procedure);

   }


   //void interaction::enumerate_composite(matter_array& a)
   //{

   //   auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //   if (puserinteractionpointeraChild)
   //   {

   //      for (auto& puserinteractionChild : puserinteractionpointeraChild->interactiona())
   //      {

   //         a.add_non_null(puserinteractionChild);

   //      }

   //   }

   //}


   bool interaction::_is_set() const
   {

      return true;

   }


   bool interaction::is_user_thread()
   {

      auto pthreadCurrent = ::get_task();

      auto puserthread = user_thread();

      auto bUserThread = pthreadCurrent && pthreadCurrent == puserthread;

      return bUserThread;

   }


   void interaction::host_send(const ::procedure & procedure)
   {

      //__matter_send_procedure(this, this, &interaction::interaction_post, procedure);

      auto pevent = __allocate manual_reset_event();

      host_post([procedure, pevent]
                {

                   procedure();

                   pevent->SetEvent();

                });

      if (!pevent->wait(procedure.timeout()))
      {

         throw ::exception(error_timeout);
         //pevent.release();

         //return false;

      }


   }


   void interaction::on_message_create(::message::message * pmessage)
   {


      //m_pwindowbase = this->window();


      //information() << "user::interaction::on_message_create";

      set_need_layout();

      //      if (::is_null(get_parent()))
      //      {
      //
      //         m_bNeedPerformLayout();
      //
      //      }

      if (pmessage->previous())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(pmessage);

      //m_pitemClient = __allocate ::item(e_element_client);

      if (m_bEnableDragClient || m_bDefaultClickHandling)
      {

         auto pitemClient = tool().defer_item(e_element_client);

         auto puseritem = user_item(pitemClient);

         puseritem->m_ezorder = e_zorder_back;

         if (m_bEnableDragClient)
         {

            enable_drag(pitemClient, e_zorder_back);

         }

      }

      if (m_bEnableDragResize)
      {

         debug() << "user::interaction::on_message_create enable drag resize";

         auto pitemResize = tool().defer_item(e_element_resize);

         if (pitemResize->m_item.m_eelement == e_element_resize)
         {

            debug() << "user::interaction::on_message_create enable drag resize yes, it is e_element_resize : " << (::iptr)pitemResize.m_p;

         }

         debug() << "user::interaction::on_message_create enable drag resize m_item.m_iItem : " << pitemResize->m_item.m_iItem;

         enable_drag(pitemResize, e_zorder_front);

      }

      //if (m_bEnableHorizontalBarDragScroll)
      //{

      //   enable_drag(e_element_bar_drag_scroll_horizontal);

      //}


      //if (m_bEnableVerticalBarDragScroll)
      //{

      //   enable_drag(e_element_bar_drag_scroll_vertical);

      //}

      auto psystem = system()->m_paurasystem;

      auto psignal = psystem->get_signal(id_user_style_change);

      psignal->add_handler(this);

      //on_create_user_interaction();

      auto pcursor = get_mouse_cursor();

      if (::is_null(pcursor))
      {

         pcursor = windowing()->get_cursor(::e_cursor_arrow);

         set_default_mouse_cursor(pcursor);

      }

      defer_run_property(ID_CREATE);

      //call_procedures(CREATE_ROUTINE);

      sync_style();

      m_bUserElementOk = true;

      m_ewindowflag |= e_window_flag_is_window;

      m_bReposition = true;

      auto ptopic = create_topic(::id_create);

      ptopic->m_puserelement = this;

      route(ptopic);

      //auto psession = get_session();

      if (is_top_level_window() && !is_message_only_window())
      {

         //_synchronous_lock synchronouslock(this->synchronization());

         //if (get_app()->get_context_system() != nullptr)
         //{

         //   psystem->add_frame(this);

         //}

         //if (get_app()->get_session() != nullptr)
         //{

         //   psession->add_frame(this);

         //}

         if (get_app() != nullptr)
         {

            ::pointer<::aura::application> papp = get_app();

            papp->add_user_interaction(this);

         }

      }

      //try
      //{
      //   if ((get_parent() != nullptr && get_parent() != psession->get_user_interaction_host())
      //         && !is_message_only_window()
      //         && psession->get_user_interaction_host() != this
      //      )
      //   {

      //      //::pointer<place_holder>pholder = get_parent();

      //      //if (pholder.is_set())
      //      //{

      //      //   // A Copy Paste error (the commented out code below)?
      //      //   //single_lock synchronouslock(puserinteractionParent->mutex(),true);
      //      //   //single_lock sl2(mutex(),true);

      //      //   if (!pholder->is_place_holding(this))
      //      //   {

      //      //      pholder->place_hold(this);

      //      //   }

      //      //}

      //   }

      //}
      //catch (...)
      //{

      //}

      if (!is_message_only_window())
      {

         message_call(e_message_change_experience);

      }

      if (::is_null(get_parent()))
      {

         auto pusersystem = m_pusersystem;

         if (pusersystem && pusersystem->m_procedureSuccess)
         {

            pusersystem->m_procedureSuccess();

         }

      }

   }


   void interaction::on_message_after_create(::message::message * pmessage)
   {

      if (m_procedureOnAfterCreate)
      {

         m_procedureOnAfterCreate();

      }

   }


   //   void interaction::windowing_send(const ::procedure & procedure)
   //   {
   //
   //      auto pwindowing = windowing();
   //
   //      if (::is_null(pwindowing))
   //      {
   //
   //         throw ::exception(error_wrong_state);
   //
   //      }
   //
   //      pwindowing->windowing_send(procedure);
   //
   //   }
   //
   //
   //   void interaction::windowing_post(const ::procedure & procedure)
   //   {
   //
   //      auto pwindowing = windowing();
   //
   //      if (::is_null(pwindowing))
   //      {
   //
   //         throw ::exception(error_wrong_state);
   //
   //      }
   //
   //      pwindowing->windowing_post(procedure);
   //
   //   }


   void interaction::_000OnDrag(::message::drag_and_drop * pdrag)
   {

      //#ifdef WINDOWS
      //
      //      if (pdrag->m_atom != MESSAGE_OLE_DRAGLEAVE)
      //      {
      //
      //         try
      //         {
      //
      //            if (!is_window_visible(e_layout_sketch))
      //            {
      //
      //               return;
      //
      //            }
      //
      //            if (!_001IsPointInside(point_i32(pdrag->point.x(), pdrag->point.y())))
      //            {
      //
      //               return;
      //
      //            }
      //
      //         }
      //         catch (...)
      //         {
      //            return;
      //         }
      //
      //      }
      //
      //      // these try catchs are needed for multi threading : multi threaded windows: the hell
      //      // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.
      //
      //      ::pointer<::user::interaction>pinteraction = top_child();
      //
      //      //      i32 iSize;
      //
      //      try
      //      {
      //
      //         while (pinteraction != nullptr)
      //         {
      //
      //            try
      //            {
      //
      //               if (pinteraction->is_window_visible(e_layout_sketch) && (pdrag->m_atom == MESSAGE_OLE_DRAGLEAVE || pinteraction->_001IsPointInside(point_i32(pdrag->point.x(), pdrag->point.y()))))
      //               {
      //
      //                  try
      //                  {
      //
      //                     pinteraction->_000OnDrag(pdrag);
      //
      //                     if (pdrag->m_bRet)
      //                     {
      //
      //                        return;
      //
      //                     }
      //
      //                  }
      //                  catch (...)
      //                  {
      //
      //                  }
      //
      //               }
      //
      //               pinteraction = pinteraction->under_sibling();
      //
      //            }
      //            catch (...)
      //            {
      //
      //            }
      //
      //         }
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //      try
      //      {
      //
      //         if (window() == nullptr)
      //         {
      //
      //            return;
      //
      //         }
      //
      //         route_message(pdrag);
      //
      //         if (pdrag->m_bRet)
      //         {
      //
      //            return;
      //
      //         }
      //
      //      }
      //      catch (...)
      //      {
      //
      //      }
      //
      //#endif

   }

   double interaction::get_rotate()
   {

      return 0.0;

   }


   void interaction::_000OnMouseLeave(::message::message * pmessage)
   {

      //if (!window())
      //{

      //   return;

      //}

      //window()->_000OnMouseLeave(pmessage);

   }


   //void interaction::_000OnMouse(::message::mouse * pmouse)
   //{

   //   // must lock ::user::pointer < ::mutex >_children() at top stack chain
   //   // and only at top stack chain.

   //   bool bThisCapture = false;

   //   try
   //   {

   //      if (!is_window_visible(e_layout_sketch))
   //      {

   //         return;

   //      }

   //      auto psession = get_session();

   //      bThisCapture = is_descendant(psession->m_puiCapture, true);

   //      if (!bThisCapture && !_001IsPointInside(pmouse->m_point))
   //      {

   //         return;

   //      }

   //   }
   //   catch (...)
   //   {

   //      return;

   //   }

   //   if (bThisCapture)
   //   {

   //      _000OnThisMouse(pmouse);

   //      if (pmouse->m_bRet)
   //      {

   //         return;

   //      }

   //      _000OnChildrenMouse(pmouse);

   //   }
   //   else
   //   {

   //      _000OnChildrenMouse(pmouse);

   //      if (pmouse->m_bRet)
   //      {

   //         return;

   //      }

   //      _000OnThisMouse(pmouse);

   //   }

   //}


   //void interaction::_000OnThisMouse(::message::mouse * pmouse)
   //{

   //   try
   //   {

   //      if (window() == nullptr)
   //      {

   //         return;

   //      }

   //      route_message(pmouse);

   //      if (pmouse->m_lresult != 0)
   //      {

   //         return;

   //      }

   //   }
   //   catch (...)
   //   {

   //   }

   //}


   //void interaction::_000OnChildrenMouse(::message::mouse * pmouse)
   //{

   //   // must lock ::user::pointer < ::mutex >_children() at top stack chain
   //   // and only at top stack chain.

   //   // these try catchs are needed for multi threading : multi threaded windows: the hell
   //   // Now I understand why many OSes windows are single threaded.
   //   ::pointer<::user::interaction>pinteraction;

   //   try
   //   {

   //      if (m_puserinteractionpointeraChild)
   //      {
   //         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //         while (puserinteractionpointeraChild->rget_child(pinteraction))
   //         {
   //            try
   //            {
   //               if (!pinteraction)
   //               {
   //                  continue;
   //               }
   //               if (pinteraction->is_window_visible(e_layout_sketch) && pinteraction->_001IsPointInside(pmouse->m_point))
   //               {
   //                  try
   //                  {
   //                     pinteraction->_000OnMouse(pmouse);
   //                     if (pmouse->m_bRet)
   //                        return;
   //                  }
   //                  catch (...)
   //                  {
   //                  }
   //               }
   //            }
   //            catch (...)
   //            {
   //            }
   //         }

   //      }


   //   }
   //   catch (...)
   //   {
   //   }

   //}


   void interaction::_000OnKey(::message::key * pkey)
   {

      if (!(pkey->m_uiMessageFlags & 1)) // message already pre translated
      {

         pre_translate_message(pkey);

         if (pkey->m_bRet)
         {

            return;

         }

         pkey->m_uiMessageFlags |= 1;

      }

      auto pwindowing = windowing();

      auto pwindowThis = window();

      //auto pointCursor = pwindow->get_cursor_position();

      if (!pkey->m_bRet)
      {

         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.

         ::user::interaction * pinteraction = top_child();

         //         i32 iSize;

         try
         {

            while (pinteraction != nullptr)
            {

               try
               {

                  if (pinteraction->is_window_visible(e_layout_sketch))
                  {

                     try
                     {

                        pinteraction->_000OnKey(pkey);

                        if (pkey->m_bRet)
                        {

                           return;

                        }

                     }
                     catch (...)
                     {

                     }

                  }

                  pinteraction = pinteraction->under_sibling();

               }
               catch (...)
               {

               }

            }

         }
         catch (...)
         {

         }

         //try
         //{

         //   window()->route_message(pkey);

         //   if (pkey->get_lresult() != 0)
         //   {

         //      return;

         //   }

         //}
         //catch (...)
         //{

         //}

      }

   }


   ::user::interaction * interaction::_001FromPoint(::point_i32 point, bool bTestedIfParentVisible)
   {

      if (bTestedIfParentVisible)
      {

         if (!is_this_visible(e_layout_sketch) ||
             !_001IsPointInside(point)) // inline version - do not need pointer to the function
         {

            return nullptr;

         }

      }
      else
      {

         if (!is_window_visible(e_layout_sketch) ||
             !_001IsPointInside(point)) // inline version - do not need pointer to the function
         {

            return nullptr;

         }

      }

      ::pointer<interaction> pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         ::pointer<interaction> puie = pinteraction->_001FromPoint(point, true);

         if (puie != nullptr)
         {

            return puie;

         }

         pinteraction = pinteraction->under_sibling();

      }

      return this;

   }


   bool interaction::_001IsPointInside(const ::point_i32 & point)
   {

      //if (::is_null(window()))
      //{

      //   return false;

      //}

      if (!is_window_screen_visible())
      {

         return false;

      }

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, e_layout_sketch);

      return rectangleWindow.contains(point);

   }


   ::rectangle_i32 interaction::client2_rectangle(enum_layout elayout)
   {

      return rectangle(elayout);

   }


   ::rectangle_i32 interaction::hosting_rectangle(enum_layout elayout)
   {

      return rectangle(elayout);

   }


   rectangle_i32 interaction::host_rectangle(enum_layout elayout)
   {

      auto rectangle = this->rectangle(elayout);

      client_to_host(elayout)(rectangle);

      return rectangle;

   }


   rectangle_i32 interaction::screen_rectangle(enum_layout elayout)
   {

      auto rectangle = this->rectangle(elayout);

      client_to_screen(elayout)(rectangle);

      return rectangle;

   }


   bool interaction::_001IsPointInsideInline(const ::point_i32 & point)
   {

      return host_rectangle(e_layout_design).contains(point);

   }


   bool interaction::_001IsClientPointInsideInline(const ::point_i32 & point)
   {

      return layout().design().raw_rectangle().contains(point);


   }


   bool interaction::_001IsParentClientPointInsideInline(const ::point_i32 & point, enum_layout elayout)
   {

      return parent_client_rectangle(elayout).contains(point);

   }


   void interaction::on_message_key_down(::message::message * pmessage)
   {

      if (m_ekeyboardmode == e_keyboard_mode_reposition
         || m_ekeyboardmode == e_keyboard_mode_resize)
      {

         ::size_i32 sizeOffset;

         if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_up)
         {

            sizeOffset.cy() -= 10;

         }
         else if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_down)
         {

            sizeOffset.cy() += 10;

         }
         else if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_left)
         {

            sizeOffset.cx() -= 10;

         }
         else if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_right)
         {

            sizeOffset.cx() += 10;

         }
         else if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_escape)
         {

            m_ekeyboardmode = e_keyboard_mode_none;
            m_sizeInitialResizeOffset.cx() = 0;
            m_sizeInitialResizeOffset.cy() = 0;

            auto pwindowing = windowing();

            auto pcursor = pwindowing->get_cursor(::e_cursor_arrow);

            window()->set_mouse_cursor(pcursor);

         }

         if (sizeOffset.cx() != 0 || sizeOffset.cy() != 0)
         {

            if (m_ekeyboardmode == e_keyboard_mode_reposition)
            {

               auto position = this->position();

               position += sizeOffset;

               set_position(position);

               set_reposition();

               post_redraw();

            }
            else
            {

               if (m_sizeInitialResizeOffset.cx() == 0
                  && sizeOffset.cx() != 0)
               {

                  m_sizeInitialResizeOffset.cx() = sizeOffset.cx();
                  m_sizeInitialResizeOffset.cy() = 0;

               }
               else if (m_sizeInitialResizeOffset.cy() == 0
                  && sizeOffset.cy() != 0)
               {

                  m_sizeInitialResizeOffset.cy() = sizeOffset.cy();
                  m_sizeInitialResizeOffset.cx() = 0;

               }

               auto r = this->parent_client_rectangle();

               bool bChanged = true;

               if (m_sizeInitialResizeOffset.cx() > 0)
               {

                  r.right() += sizeOffset.cx();

               }
               else if (m_sizeInitialResizeOffset.cx() < 0)
               {

                  r.left() += sizeOffset.cx();

               }
               else if (m_sizeInitialResizeOffset.cy() > 0)
               {

                  r.bottom() += sizeOffset.cy();

               }
               else if (m_sizeInitialResizeOffset.cy() < 0)
               {

                  r.top() += sizeOffset.cy();

               }
               else
               {

                  bChanged = false;

               }

               if (bChanged)
               {

                  place(r);

                  set_need_layout();

                  set_need_redraw();

                  post_redraw();

               }

            }

            pmessage->m_bRet = true;

         }

      }

      if (!m_bDefaultEditHandling && !m_bDefaultKeyboardMultipleSelectionHandling)
      {

         return;

      }

      if (get_parent() == nullptr)
      {

         if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_f4)
         {

            auto psession = this->get_session();

            if (psession->is_key_pressed(::user::e_key_alt))
            {

               post_message(MESSAGE_CLOSE);

               pmessage->m_bRet = true;

               return;

            }

         }

      }

      if (m_pappearance)
      {

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (m_pappearance->on_key_down(pmessage->m_union.m_pkey->m_ekey, pmessage->m_wparam, ekeyModifiers,
            pmessage->m_union.m_pkey->m_strText))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (m_bDefaultEditHandling || m_bDefaultKeyboardMultipleSelectionHandling)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey)
         {

            if (m_bDefaultEditHandling && pkey->m_ekey == ::user::e_key_delete)
            {

               auto pcommand = __allocate::message::command("edit_delete");

               pcommand->initialize(this);

               route_command(pcommand);

               pkey->m_bRet = pcommand->m_bRet;

            }
            else if (m_bDefaultKeyboardMultipleSelectionHandling &&
                    (
                       pkey->m_ekey == ::user::e_key_shift
                       || pkey->m_ekey == ::user::e_key_left_shift
                       || pkey->m_ekey == ::user::e_key_right_shift
                       || pkey->m_ekey == ::user::e_key_control
                       || pkey->m_ekey == ::user::e_key_left_control
                       || pkey->m_ekey == ::user::e_key_right_control
                       ))
            {

               pkey->m_bRet = true;

            }

         }

      }

      //if(psession->get_keyboard_focus() != this
      //   && psession->get_keyboard_focus() != nullptr)
      //{
      // psession->get_keyboard_focus()->keyboard_focus_OnKeyDown(pmessage);
      //}
   }


   void interaction::on_message_key_up(::message::message * pmessage)
   {

      if (m_pappearance)
      {

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (m_pappearance->on_key_up(pmessage->m_union.m_pkey->m_ekey, pmessage->m_wparam, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (m_bDefaultEditHandling || m_bDefaultKeyboardMultipleSelectionHandling)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey)
         {

            if (m_bDefaultEditHandling && pkey->m_ekey == ::user::e_key_delete)
            {

               pkey->m_bRet = true;

            }
            else if (m_bDefaultKeyboardMultipleSelectionHandling &&
                    (
                       pkey->m_ekey == ::user::e_key_shift
                       || pkey->m_ekey == ::user::e_key_left_shift
                       || pkey->m_ekey == ::user::e_key_right_shift
                       || pkey->m_ekey == ::user::e_key_control
                       || pkey->m_ekey == ::user::e_key_left_control
                       || pkey->m_ekey == ::user::e_key_right_control
                       ))
            {

               pkey->m_bRet = true;

            }

         }

      }

      //if(psession->get_keyboard_focus() != this
      ///&& psession->get_keyboard_focus() != nullptr)
      //{
      // psession->get_keyboard_focus()->keyboard_focus_OnKeyUp(pmessage);
      //}
   }


   void interaction::drag_set_capture()
   {

      set_mouse_capture();

   }


   bool interaction::on_drag_start(::point_i32 & pointDrag, ::item * pitem)
   {

      get_wnd()->hide_software_keyboard(this);

      if (pitem->m_item.m_eelement == e_element_client)
      {

         if (!is_top_level())
         {

            return false;

         }

         if (is_display_like_maximized() || is_display_like_full_screen())
         {

            return false;

         }

         auto puseritem = user_item(pitem);

         if (window()->defer_perform_entire_reposition_process(puseritem->m_pmouse.cast<::user::mouse>()))
         {

            return false;

         }

         pointDrag = layout().window().origin();

         return true;

      }
      else if (pitem->m_item.m_eelement == e_element_resize)
      {

         auto puseritem = user_item(pitem);

         if (window()->defer_perform_entire_resizing_process(::experience::e_frame_sizing_bottom_right, puseritem->m_pmouse.cast<::message::mouse>()))
         {

            puseritem->m_pmouse->m_union.m_pmouse->m_bRet = true;

            return false;

         }

         pointDrag = layout().window().origin() + layout().window().size();

         return true;

      }
      else if (pitem->m_item.m_eelement == e_element_tab_near_scroll
               || pitem->m_item.m_eelement == e_element_tab_far_scroll)
      {

         pointDrag = m_pointBarDragScroll;

         return true;

      }

      return false;

   }


   ::point_i32 interaction::drag_mouse_cursor_position(::item * pitem, const ::point_i32 & point)
   {

      auto p = windowing()->try_absolute_mouse_position(this, point);

      return p;

   }


   bool interaction::drag_shift(::item * pitem, ::user::mouse * pmouse)
   {

      if (pitem->m_item.m_eelement == e_element_client)
      {

         printf_line("drag_shift e_element_client");

         auto pdrag = drag(pitem);

         pdrag->m_ecursor = e_cursor_move;

         auto point = drag_point(pitem, pmouse);

         //set_position(point);

         set_position(point);

         //set_reposition();

         //set_need_redraw();

         //post_redraw();

         return true;
      }
      else if (pitem->m_item.m_eelement == e_element_resize)
      {

         printf_line("drag_shift e_element_resize");

         auto pdrag = drag(pitem);

         pdrag->m_ecursor = e_cursor_size_bottom_right;

         auto pointBottomRight = drag_point(pitem, pmouse);

         //auto Δ = point - pdrag->m_pointLButtonDown;

         //auto pointBottomRight = pdrag->m_pointInitial + Δ;

         auto size = pointBottomRight - layout().window().origin();

         auto sizeMinimum = get_window_minimum_size();

         size = size.maximum(sizeMinimum);

         informationf("drag_shift resize %d, %d", size.cx(), size.cy());

         //auto rectanglePrevious = layout().window().raw_rectangle();

         //layout().sketch().m_size = size;

         set_size(size);

         //set_need_layout();

         //on_size_change_request(rectanglePrevious);

         return true;

      }

      return false;

   }


   //void interaction::on_size_change_request(const ::rectangle_i32 &rectanglePrevious)
   //{

   //   auto rectangle = layout().sketch().raw_rectangle();

   //   ::rectangle_i32_array rectanglea;

   //   if (rectangle.right() > rectanglePrevious.right())
   //   {

   //      ::rectangle_i32 r;

   //      r.left() = rectanglePrevious.right();
   //      r.right() = rectangle.right();
   //      r.top() = rectangle.top();
   //      r.bottom() = rectangle.bottom();

   //      rectanglea.add(r);

   //   }

   //   if (rectangle.bottom() > rectanglePrevious.bottom())
   //   {

   //      ::rectangle_i32 r;

   //      r.left() = rectangle.left();
   //      r.right() = rectangle.right();
   //      r.top() = rectanglePrevious.bottom();
   //      r.bottom() = rectangle.bottom();

   //      rectanglea.add(r);

   //   }

   //   if (rectanglea.has_element())
   //   {

   //      set_need_redraw(rectanglea);

   //   }

   //   post_redraw();


   //}


   bool interaction::drag_hover(::item * pitem)
   {

      if (pitem->m_item.m_eelement == e_element_client)
      {

         auto pdrag = drag(pitem);

         pdrag->m_ecursor = e_cursor_arrow;

         return true;

      }
      else if (pitem->m_item.m_eelement == e_element_resize)
      {

         auto pdrag = drag(pitem);

         //information() << "drag_hover e_element_resize";

         pdrag->m_ecursor = e_cursor_size_bottom_right;

         return true;

      }

      return false;

   }


   void interaction::drag_release_capture()
   {

      defer_release_mouse_capture();

   }


   void interaction::drag_set_cursor(::item * pitem)
   {

      auto pwindowing = windowing();

      auto pdrag = drag(pitem);

      auto pcursor = pwindowing->get_cursor(pdrag->m_ecursor);

      user_mouse_set_cursor(pdrag->m_pmouse, pcursor);

   }


   void interaction::set_text_and_selection(const ::scoped_string & scopedstr, strsize iSelStart, strsize iSelEnd, const ::action_context & actioncontext)
   {

   }


   //void interaction::on_message_ime_char(::message::message * pmessage)
   //{

   //

   //   //if (m_bDefaultEditHandling || m_bDefaultKeyboardMultipleSelectionHandling)
   //   //{

   //   //   auto pkey = pmessage->m_union.m_pkey;

   //   //   if (pkey)
   //   //   {

   //   //      if (m_bDefaultEditHandling && pkey->m_ekey == ::user::e_key_delete)
   //   //      {

   //   //         pkey->m_bRet = true;

   //   //      }
   //   //      else if (m_bDefaultKeyboardMultipleSelectionHandling &&
   //   //         (
   //   //            pkey->m_ekey == ::user::e_key_shift
   //   //            || pkey->m_ekey == ::user::e_key_left_shift
   //   //            || pkey->m_ekey == ::user::e_key_right_shift
   //   //            || pkey->m_ekey == ::user::e_key_control
   //   //            || pkey->m_ekey == ::user::e_key_left_control
   //   //            || pkey->m_ekey == ::user::e_key_right_control
   //   //            ))
   //   //      {

   //   //         pkey->m_bRet = true;

   //   //      }

   //   //   }

   //   //}

   //   //if(psession->get_keyboard_focus() != this
   //   ///&& psession->get_keyboard_focus() != nullptr)
   //   //{
   //   // psession->get_keyboard_focus()->keyboard_focus_OnKeyUp(pmessage);
   //   //}
   //}


   void interaction::on_message_character(::message::message * pmessage)
   {

      if (m_pappearance)
      {

         if (pmessage->m_wparam.m_number != 0)
         {

            m_pappearance->on_character((int)pmessage->m_wparam.m_number);

         }

         for (auto psz = pmessage->m_union.m_pkey->m_strText.c_str();
              psz < pmessage->m_union.m_pkey->m_strText.end(); psz = ::unicode_next(psz))
         {

            m_pappearance->on_character(unicode_index(psz));

         }

         pmessage->m_bRet = true;

      }
      //if(psession->get_keyboard_focus() != this
      // && psession->get_keyboard_focus() != nullptr)
      //{
      // psession->get_keyboard_focus()->keyboard_focus_OnChar(pmessage);
      //}
   }


   void interaction::_001OnTimer(::timer * ptimer)
   {

   }


   void interaction::on_timer(::timer * ptimer)
   {

      _001OnTimer(ptimer);

      //return true;

   }


   ::user::interaction * interaction::get_child_by_name(const ::string & strName, ::collection::index iItem, i32 iLevel)
   {

      ::pointer<interaction> pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         if (pinteraction->m_strName == strName)
         {

            if (iItem < 0 || iItem == pinteraction->m_item.m_iItem)
            {

               return pinteraction;

            }

         }

         pinteraction = pinteraction->under_sibling();

      }

      ::pointer<interaction> pchild;

      if (iLevel > 0 || iLevel == -1)
      {

         if (iLevel > 0)
         {

            iLevel--;

         }

         ::pointer<interaction> pinteractionItem = top_child();

         while (pinteractionItem != nullptr)
         {

            pchild = pinteractionItem->get_child_by_name(strName, iItem, iLevel);

            if (pchild != nullptr)
            {

               return pchild;

            }

            pinteractionItem = pinteractionItem->under_sibling();

         }

      }

      return nullptr;

   }


   ::user::interaction * interaction::get_child_by_id(const atom & atom, ::collection::index iItem, i32 iLevel)
   {

      auto pwindow = this->window();

      _synchronous_lock synchronouslock(pwindow ? pwindow->m_pparticleChildrenSynchronization : nullptr);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return nullptr;

      }

      for (::collection::index i = puserinteractionpointeraChild->interaction_last_index(); i >= 0; i--)
      {

         auto pinteraction = puserinteractionpointeraChild->get_interaction(i);

         if (pinteraction->GetDlgCtrlId() == atom)
         {

            if (iItem < 0 || iItem == pinteraction->m_item.m_iItem)
            {

               return pinteraction;

            }

         }

      }

      if (iLevel == 0)
      {

         return nullptr;

      }
      else if (iLevel > 0)
      {

         iLevel--;

      }

      for (::collection::index i = puserinteractionpointeraChild->interaction_last_index(); i >= 0; i--)
      {

         auto pinteraction = puserinteractionpointeraChild->get_interaction(i);

         ::user::interaction * puiChild = pinteraction->get_child_by_id(atom, -1, iLevel);

         if (::is_set(puiChild))
         {

            return puiChild;

         }

      }

      return nullptr;

   }


   ::user::element * interaction::get_primitive_by_id(const atom & atom, ::collection::index iItem, i32 iLevel)
   {

      auto pchild = get_child_by_id(atom, iItem, iLevel);

      if (::is_null(pchild))
      {

         return nullptr;

      }

      return pchild;

   }


   ::user::interaction * interaction::child_from_point(const ::point_i32 & point, ::i32 iLevel,
                                                       const ::user::interaction_array * pinteractionaExclude)
   {

      auto pointClient = point;

      ::user::interaction * puserinteractionParent = nullptr;

      ::user::interaction * puserinteractionSearchChildren = this;

      if (iLevel >= 0)
      {

         iLevel++;

      }

      do
      {

         if (!puserinteractionSearchChildren->is_this_visible())
         {

            break;

         }

         puserinteractionParent = puserinteractionSearchChildren;

         puserinteractionParent->parent_to_client()(pointClient);

         _synchronous_lock synchronouslock(puserinteractionParent->window()->m_pparticleChildrenSynchronization);

         auto puserinteractionpointeraChild = puserinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            break;

         }

         puserinteractionSearchChildren = nullptr;

         for (::collection::index iChild = puserinteractionpointeraChild->interaction_last_index();
              iChild >= 0; iChild--)
         {

            auto & puserinteractionChild = puserinteractionpointeraChild->interaction_at(iChild);

            if (::is_null(pinteractionaExclude) || !pinteractionaExclude->contains_interaction(puserinteractionChild))
            {
               //if (puserinteractionChild->is_this_visible()
               //&& (!puserinteractionChild->is_place_holder()
               //   || (puserinteractionChild->m_puserinteractionpointeraChild
               //      && puserinteractionChild->m_puserinteractionpointeraChild->interaction_count() == 1
               //      && puserinteractionChild->m_puserinteractionpointeraChild->first_interaction()->is_this_visible())))
               if (puserinteractionChild->is_this_visible())
               {

                  if (puserinteractionChild->_001IsParentClientPointInsideInline(pointClient))
                  {

                     iLevel--;

                     puserinteractionSearchChildren = puserinteractionChild;

                     break;

                  }

               }

            }

         }

      } while (puserinteractionSearchChildren != nullptr && iLevel != 0);

      return puserinteractionParent;

   }


   ::user::interaction *
      interaction::_child_from_point(const ::point_i32 & point, const ::user::interaction_array * pinteractionaExclude)
   {

      if (::is_null(window()))
      {

         return nullptr;

      }

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return nullptr;

      }

      auto pointClient = point;

      host_to_client()(pointClient);

      for (::collection::index iChild = puserinteractionpointeraChild->interaction_last_index();
           iChild >= 0; iChild--)
      {

         auto & puserinteractionChild = puserinteractionpointeraChild->interaction_at(iChild);

         if (::is_null(pinteractionaExclude) || !pinteractionaExclude->contains_interaction(puserinteractionChild))
         {
            //if (puserinteractionChild->is_this_visible()
            //&& (!puserinteractionChild->is_place_holder()
            //   || (puserinteractionChild->m_puserinteractionpointeraChild
            //      && puserinteractionChild->m_puserinteractionpointeraChild->interaction_count() == 1
            //      && puserinteractionChild->m_puserinteractionpointeraChild->first_interaction()->is_this_visible())))
            if (puserinteractionChild->is_this_visible())
            {

               if (puserinteractionChild->_001IsParentClientPointInsideInline(pointClient))
               {

                  return puserinteractionChild;

               }

            }

         }

      }

      return nullptr;

   }

   //void interaction::_002OnLButtonDown(::message::message * pmessage)
   //{
   //   __UNREFERENCED_PARAMETER(pmessage);
   //}

   //void interaction::_002OnLButtonUp(::message::message * pmessage)
   //{
   //   __UNREFERENCED_PARAMETER(pmessage);
   //}

   //void interaction::_002OnMouseMove(::message::message * pmessage)
   //{
   //   __UNREFERENCED_PARAMETER(pmessage);
   //}

   //void interaction::_002OnMouseEnter(::message::message * pmessage)
   //{
   //   __UNREFERENCED_PARAMETER(pmessage);
   //}

   //void interaction::_002OnMouseLeave(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   //void interaction::_002OnKeyDown(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   //void interaction::_002OnKeyUp(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


   //void interaction::_002OnTimer(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //}


//   lresult interaction::send_message(::message::message * pmessage)
//   {
//
//      message_handler(pmessage);
//
//      return pmessage->m_lresult;
//
//   }




   lresult interaction::send_message(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
   {

      //if (window() == nullptr)
      //{

      //   return 0;

      //}

      auto a = atom;

      auto pLresult = __allocate particle_primitive < ::lresult >();

      pLresult->m_t = 0;

      ::pointer < ::user::interaction > pthis = this;

      user_thread()->send([pthis, a, wparam, lparam, pLresult]()
         {

            try
            {

               if (!pthis->is_window())
               {

                  pLresult->m_t = -2;

                  return;

               }

               pLresult->m_t = pthis->message_handler(a, wparam, lparam);

            }
            catch (...)
            {

               pLresult->m_t = -1;

            }

         });

      return pLresult->m_t;

      //return window()->send_message(atom, wparam, lparam);

   }


   lresult interaction::send_message(::message::message * pmessage)
   {

      //if (window() == nullptr)
      //{

      //   return 0;

      //}

      //::lresult lresult = 0;

      ::pointer < ::message::message > p = pmessage;

      user_thread()->send([this, p]()
         {

            this->message_handler(p);

         });


      return p->m_lresult;

   }


   void interaction::post_message(::message::message * pmessage)
   {

      if (pmessage->m_atom == e_message_key_down)
      {

         informationf("::user::interaction::post e_message_key_down");

      }

      ::pointer<::user::message> pusermessage = pmessage;

      if (pusermessage)
      {

         pusermessage->m_pchannel = this;

      }

      auto p = __as_pointer pmessage;

      auto puserthread = user_thread();

      puserthread->post([this, p]()
      {

         message_handler(p);

      });

   }


   //   lresult interaction::send_create_message()
   //   {
   //   
   //      return send_message(e_message_create);
   //      
   //   }


   lresult interaction::message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
   {

      //if (window() == nullptr)
      //{

      //   return 0;

      //}

      return message_handler(atom, wparam, lparam);

   }


   lresult interaction::message_call(::message::message * pmessage)
   {

      message_call(pmessage);

      return pmessage->m_lresult;

   }


   void interaction::on_message(::message::message * pmessage)
   {

      if (layout().is_moving())
      {

         informationf("moving: skip walk pre translate tree");

      }
      else if (layout().is_sizing())
      {

         informationf("sizing: skip walk pre translate tree");

      }
      else
      {

         walk_pre_translate_tree(pmessage);

         if (pmessage->m_bRet)
         {

            return;

         }

      }

      message_handler(pmessage);

   }


#ifdef LINUX


   lresult interaction::send_x11_event(void * pevent)
   {

      if (window() == nullptr)
      {

         return false;

      }
      else
      {

         return window()->send_x11_event(pevent);

      }

   }


#endif


   void interaction::enable_window(bool bEnable)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->enable_window(bEnable);

   }


   // void interaction::SetWindowDisplayChanged()
   // {

   //    if (::is_null(window()))
   //    {

   //       return;

   //    }

   //    window()->SetWindowDisplayChanged();

   // }


   //bool interaction::is_this_enabled() const
   //{

   //   if (window() == nullptr)
   //   {

   //      return false;

   //   }

   //   return window()->is_this_enabled();

   //}


   void interaction::send_message_to_descendants(const ::atom & atom, wparam wparam, lparam lparam, bool bDeep,
                                                 bool bOnlyPerm)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //_synchronous_lock synchronouslock(::user::pointer < ::mutex >_children());

      //_synchronous_lock synchronouslock(this->synchronization());

      auto children = synchronized_get_children();

      //if (m_puserinteractionpointeraChild)
      {

         //auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         //synchronouslock.unlock();

         for (auto & puserinteraction : children)
         {

            //synchronouslock.lock();

            try
            {

               puserinteraction->send_message(atom, wparam, lparam);

            }
            catch (...)
            {

            }

            //synchronouslock.unlock();

         }

         if (!bDeep)
         {

            return;

         }

         for (auto & puserinteraction : children)
         {

            try
            {

               puserinteraction->send_message_to_descendants(atom, wparam, lparam, true, bOnlyPerm);


            }
            catch (...)
            {

            }

         }

      }

   }


   void interaction::route_message_to_descendants(::message::message * pmessage)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      auto children = synchronized_get_children();

      // _synchronous_lock synchronouslock(this->synchronization());

      // auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      // {

      //    //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());



      // }

      for (auto & puiChild : children)
      {

         //synchronouslock.unlock();

         try
         {

            puiChild->route_message_to_descendants(pmessage);

         }
         catch (...)
         {

         }

         //synchronouslock.lock();

      }

   }


   //void interaction::pre_translate_message(::message::message * pmessage)
   //{

   //   __UNREFERENCED_PARAMETER(pmessage);

   //   //::pointer<::message::message>pmessage(pmessage);

   //   //if(pmessage->m_atom == e_message_key_down)
   //   //{

   //   //   auto pkey = pmessage->m_union.m_pkey;

   //   //   if(pkey->m_ekey == ::user::e_key_tab)
   //   //   {

   //   //      ::topic topic;

   //   //      topic.m_puserinteraction         = this;

   //   //      topic.m_atom       = ::id_tab_key;

   //   //      topic.m_context        = ::e_source_user;

   //   //      if(!route(&topic))
   //   //      {

   //   //         ::pointer<::user::interaction>pinteraction = psession->get_keyboard_focus();

   //   //         pinteraction =  pinteraction->is_set() ? pinteraction->keyboard_get_next_focusable() : keyboard_get_next_focusable();

   //   //         if(pinteraction != nullptr)
   //   //         {

   //   //            if (!pinteraction->does_consume_key(::user::e_key_tab))
   //   //            {

   //   //               pinteraction->keyboard_set_focus();

   //   //               pkey->m_bRet = true;

   //   //            }

   //   //         }

   //   //      }

   //   //   }

   //   //}


   //}


   //   oswindow interaction::get_oswindow() const
   //   {
   //
   //#if defined(UNIVERSAL_WINDOWS)
   //
   //      ::pointer<::user::interaction>puserinteraction;
   //
   //      try
   //      {
   //
   //         puserinteraction = get_wnd();
   //
   //         if (!puserinteraction)
   //         {
   //
   //            return nullptr;
   //
   //         }
   //
   //         if (!puserinteraction->window())
   //         {
   //
   //            return nullptr;
   //
   //         }
   //
   //         return oswindow_get(puserinteraction->window()->windowing_window());
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      return nullptr;
   //
   //#else
   //
   //      ::user::interaction * pinteraction;
   //
   //      ::windowing::window * puserinteraction;
   //
   //      try
   //      {
   //
   //         pinteraction = get_wnd();
   //
   //         if (pinteraction == nullptr)
   //            return nullptr;
   //
   //         if (pinteraction->window() == nullptr)
   //            return nullptr;
   //
   //         puserinteraction = pinteraction->window()->get_user_interaction_impl();
   //
   //         if (puserinteraction == nullptr)
   //            return nullptr;
   //
   //         return puserinteraction->get_oswindow();
   //
   //      }
   //      catch (...)
   //      {
   //
   //      }
   //
   //      return nullptr;
   //
   //#endif
   //
   //
   //   }



   //bool interaction::subclass_window(oswindow posdata)
   //{
   //
   //      _synchronous_lock synchronouslock(this->synchronization());
   //
   //      if (is_window())
   //      {
   //
   //         start_destroying_window();
   //
   //      }
   //
   //      erase_all_routes();
   //
   //      ::pointer<primitive_impl>pwindowOld = window();
   //
   //      auto pwindowNew = __create < interaction_impl >();
   //
   //      pwindowNew->m_puserinteraction = this;
   //
   //      if (!pwindowNew->subclass_window(posdata))
   //      {
   //
   //         pwindowNew.release();
   //
   //      }
   //
   //      if (pwindowNew != nullptr)
   //      {
   //
   //         if (pwindowOld != nullptr)
   //         {
   //
   //            pwindowOld->m_puserinteraction = nullptr;
   //
   //            pwindowOld->erase_all_routes();
   //
   //            auto pwindowOld = pwindowOld;
   //
   //            if (pwindowOld != nullptr)
   //            {
   //
   //               pwindowOld->install_message_routing(this);
   //
   //            }
   //
   //            pwindowOld.release();
   //
   //         }
   //
   //         window() = pwindowNew;
   //
   //         return true;
   //
   //      }
   //      else
   //      {
   //
   //         return false;
   //
   //      }
   //
   //}
   //
   //oswindow interaction::unsubclass_window()
   //{
   //
   //      auto pwindowThis = window();
   //
   //      if (pwindow != nullptr)
   //      {
   //
   //         return pwindow->unsubclass_window();
   //      }
   //
   //      return nullptr;
   //
   //}


   //bool interaction::create_child(::user::interaction * pinteractionParent)
   //{

   //   if (!create_interaction(puserinteractionParent))
   //   {

   //      informationf("Failed to create control");

   //      return false;

   //   }

   //   return true;

   //}


   void interaction::create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      if (!atom.is_empty())
      {

         m_atom = atom;

      }

      ::e_status estatus;

      if (!puserinteractionParent)
      {

         create_window();

      }
      else
      {

         create_child(puserinteractionParent);

      }

   }



   void interaction::create_child(::user::interaction * puserinteractionParent)
   {

      if (is_window())
      {

         destroy_window();

      }

      if (::is_null(m_pcontext))
      {

         initialize(puserinteractionParent);

      }

      if (::is_null(system()))
      {

         initialize(puserinteractionParent);

      }

      ::e_status estatus = error_exception;

      //try
      //{

      m_bUserElementOk = true;
      //      
      //      if(m_pusersystem
      //         && m_pusersystem->m_prequest->m_egraphicsoutputpurpose & ::graphics::e_output_purpose_screen)
      //      {
      //
      //         display();
      //
      //      }

            //auto psession = get_session();

            //auto puserinteractionHost = psession->get_user_interaction_host();

            //if (puserinteractionParent == nullptr && this != puserinteractionHost && ::is_set(puserinteractionHost))
            //{

            //   puserinteractionParent = __user_interaction(psession->get_user_interaction_host());

            //}

            //if ((WS_CHILD & pusersystem->m_createstruct.style) == 0 && (!puserinteractionParent || puserinteractionParent != psession->get_user_interaction_host()))
            //{

            //   //if (psession->m_pwindowLastSeed || pusersystem->window())
            //   //{

            //   //   if (pusersystem->window())
            //   //   {

            //   //      window() = pusersystem->window();

            //   //      pusersystem->window().release();

            //   //   }
            //   //   else
            //   //   {

            //   //      window() = psession->m_pwindowLastSeed;

            //   //      psession->m_pwindowLastSeed.release();

            //   //   }

            //   //   if (!window())
            //   //   {

            //   //      auto estatus = window()->initialize(this);

            //   //      if (!estatus)
            //   //      {

            //   //         return false;

            //   //      }

            //   //   }

            //   //   pusersystem->m_createstruct.x() = window()->m_rectangle.left();
            //   //   pusersystem->m_createstruct.y() = window()->m_rectangle.top();
            //   //   pusersystem->m_createstruct.cx() = window()->m_rectangle.width();
            //   //   pusersystem->m_createstruct.cy() = window()->m_rectangle.height();

            //   //}
            //   //else
            //   //{

            //   //   window() = __create < interaction_impl >();

            //   //}

            //   //uStyle &= ~WS_CHILD;

            //   //m_pdescriptor.defer_create(this);

            //   if (!window()->create_window_ex(this, pusersystem, puserinteractionParent, atom))
            //   {

            //      m_bUserElementOk = false;

            //      window().release();

            //      if (user_thread())
            //      {

            //         if (::is_set(user_thread()->m_puiptraThread))
            //         {

            //            user_thread()->m_puiptraThread->erase(this);

            //         }

            //         __release(user_thread() REFERENCING_DEBUGGING_COMMA_THIS);

            //      }

            //      return false;

            //   }

            //   return true;

            //}
            //else
            //{

            //if (puserinteractionParent == nullptr && this != psession->get_user_interaction_host() && psession->get_user_interaction_host().is_set())
            //{

            //   puserinteractionParent = __user_interaction(psession->get_user_interaction_host());

            //}

            //::rectangle_i32 rectangle;

            ////pusersystem->get_rect(rectangle);

            //::rectangle_i32 rectangleFrame(0, 0, 0, 0);

            //if (IsRectEmpty(&rectangle))
            //{

            //   if (rectangleFrame.is_null() && ::is_set(puserinteractionParent) && puserinteractionParent->is_place_holder())
            //   {

            //      puserinteractionParent->rectangle(rectangleFrame);

            //   }

            //}
            //else
            //{

            //   rectangleFrame = rectangle;

            //}

            //_synchronous_lock synchronouslock(puserinteractionParent == nullptr ? nullptr : puserinteractionParent->synchronization());

            //window() = __create_new<::user::interaction_child>();

            //window()->m_puserinteraction = this;

            //m_pdescriptor.defer_create(this);

            //estatus =

            //window()->create_child(this, puserinteractionParent);

            //if (!estatus)
            //{

            //   m_bUserElementOk = false;

            //   window().release();

            //   if (user_thread())
            //   {

            //      if (::is_set(user_thread()->m_puiptraThread))
            //      {

            //         user_thread()->m_puiptraThread->erase(this);

            //      }

            //      __release(user_thread() REFERENCING_DEBUGGING_COMMA_THIS);

            //   }

            //   return estatus;

            //}

            //}

            //}
            //catch (...)
            //{

            //   m_bUserElementOk = false;

            //   if (user_thread())
            //   {

            //      if (::is_set(user_thread()->m_puiptraThread))
            //      {

            //         user_thread()->m_puiptraThread->erase(this);

            //      }

            //      __release(user_thread() REFERENCING_DEBUGGING_COMMA_THIS);

            //   }

            //}

            //return estatus;





















      if (!_create_child(puserinteractionParent))
      {

         m_bUserElementOk = false;

         //window().release();

         //if (user_thread())
         //{

         //   if (::is_set(user_thread()->m_puiptraThread))
         //   {

         //      user_thread()->m_puiptraThread->erase(this);

         //   }

         //   __release(user_thread() REFERENCING_DEBUGGING_COMMA_THIS);

         //}

         return;

      }

      //}

      //}
      //catch (...)
      //{

      //   m_bUserElementOk = false;

      //   if (user_thread())
      //   {

      //      if (::is_set(user_thread()->m_puiptraThread))
      //      {

      //         user_thread()->m_puiptraThread->erase(this);

      //      }

      //      __release(user_thread() REFERENCING_DEBUGGING_COMMA_THIS);

      //   }

      //}

      //return estatus;

   }


   bool interaction::_create_child(::user::interaction * puserinteractionParent)
   {

      if (_is_window())
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction_child::create_window_ex (DestroyWindow)";
         information() << "";
         information() << "";

         destroy_window();

      }

      //try
      //{

      //m_bCreate = true;

      //m_puserinteraction = pinteraction;

      //if (::is_null(system()))
      //{

      //   initialize(pprimitiveParent);

      //}

      //__refer(m_pthreadUserImpl,  m_puserinteraction->m_pthreadUserInteraction  REFERENCING_DEBUGGING_COMMA_THIS_FUNCTION_FILE_LINE);

      //m_puserinteraction->m_pprimitiveimpl = this;

      //m_puserinteraction->m_pinteractionimpl.release();

      //m_puserinteraction->m_atom = atom;

      //if (!m_puserinteraction->pre_create_window(pusersystem))
      //{
      //   information() << "-------------------------------------------------------------------";
      //   information() << "";
      //   information() << "";
      //   information() << "interaction_child::create_window_ex (2)";
      //   information() << "";
      //   information() << "";

      //   return false;

      //}

      on_set_parent(puserinteractionParent);

      on_after_set_parent();

      if (m_puserinteractionOwner)
      {

         on_set_owner(m_puserinteractionOwner);

         //::user::interaction_base * puiRet = set_owner(m_puserinteractionOwner);

         //if (m_ewindowflag & e_window_flag_satellite_window)
         //{

         //   m_pthreadUserInteraction = m_puserinteractionOwner->m_pthreadUserInteraction;

         //}

      }

      install_message_routing(this);

      if (m_ewindowflag & e_window_flag_load_window_rect_on_impl
          && (!is_top_level()
             || !windowing()->is_sandboxed()))
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction_child::create_window_ex (rectangle)";
         information() << "";
         information() << "";

         WindowDataLoadWindowRectangle();

      }
      else
      {

         display(const_layout().sketch().m_edisplay);

      }

      m_ewindowflag |= e_window_flag_is_window;

      //m_puserinteraction->set_window_long_ptr(GWL_STYLE, pusersystem->m_createstruct.style);
      //m_puserinteraction->set_window_long_ptr(GWL_STYLE, m_puserinteraction-());

      //auto rectangleChild = pusersystem->get_rect();

      //if (rectangleChild.is_set())
      //{

      //   information() << "-------------------------------------------------------------------";
      //   information() << "";
      //   information() << "";
      //   informationf("interaction_child::create_window_ex (rectangleChild %d, %d, (%d, %d))", rectangleChild.origin().x(), rectangleChild.origin().y(), rectangleChild.width(), rectangleChild.height());
      //   information() << "";
      //   information() << "";

      //   m_puserinteraction->layout().sketch() = rectangleChild;

      //}

      string strType = ::type(this).name();

      if (is_top_level())
      {

         information() << "top_level";

      }
      else
      {

         //if (pusersystem->m_createstruct.style & WS_VISIBLE)
         //{

         //   information() << "-------------------------------------------------------------------";
         //   information() << "";
         //   information() << "";
         //   information() << "interaction_child::create_window_ex VISIBLE";
         //   information() << "";
         //   information() << "";

         //   m_puserinteraction->display();

         //}
         //else
         //{

         //   information() << "-------------------------------------------------------------------";
         //   information() << "";
         //   information() << "";
         //   information() << "interaction_child::create_window_ex NOT VISIBLE";
         //   information() << "";
         //   information() << "";

         //   m_puserinteraction->hide();

         //}

      }

      //m_puserinteraction->send_message(e_message_create, 0, (lparam)(lparam)& pusersystem->m_createstruct);
      if (!(m_ewindowflag & ::e_window_flag_window_created))
      {
         //            auto pmessage = __create_new <::message::create>();
         //            pmessage->m_atom = e_message_create;
         //            m_puserinteraction->send_message(pmessage);

         //            m_puserinteraction->send_create_message();

         message_call(e_message_create);

      }

      if (m_procedureOnAfterCreate)
      {

         m_procedureOnAfterCreate();

      }

      //}
      //catch (...)
      //{

      //   m_puserinteraction->m_ewindowflag -= e_window_flag_is_window;

      //   m_bCreate = false;

      //   return false;

      //}

      m_ewindowflag |= e_window_flag_window_created;

      //m_bUserImplCreated = true;

      set_flag(e_flag_task_started);

      return true;

   }

   void interaction::create_control(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      m_atom = atom;

      create_child(puserinteractionParent);

   }


   void interaction::defer_create_interaction(::user::interaction * puserinteractionParent, const ::atom & atom)
   {

      if (!is_window())
      {

         create_interaction(puserinteractionParent, atom);

      }
      //else
      //{

      //   if (m_atom != atom)
      //   {

      //      m_atom = atom;

      //   }

      //   if (get_parent() != puserinteractionParent)
      //   {

      //      set_parent(puserinteractionParent);

      //   }

      //   if(m_procedureOnAfterCreate)
      //   {

      //      m_procedureOnAfterCreate();

      //   }

      //}

   }


   void interaction::on_finished_window_creation()
   {

      m_ewindowflag |= e_window_flag_window_created;

      if (!get_parent())
      {

         information() << "on_finished_window_creation of Top Level Window";

         post_message(e_message_pos_create);

         if (!defer_post_pending_set_need_redraw())
         {

            //if(pusersystem->m_createstruct.style & WS_VISIBLE)
            //if(pusersystem->m_.style & WS_VISIBLE)
            //if(puserinteraction->const_layout().sketch().is_screen_visible())
            if (const_layout().sketch().is_screen_visible())
            {

               //               puserinteraction->display();
               //
               //               puserinteraction->set_need_redraw();
               //
               //               puserinteraction->post_redraw();
               //
               set_need_redraw();

               post_redraw();

               //;//macos_window_show();

            }

         }

      }

   }


   bool interaction::_is_window() const
   {

      if (::is_null(this))
      {

         return false;

      }

      //if (::is_null(window()))
      //{

      //   return false;

      //}

      if (((interaction *)this)->get_parent() != nullptr)
      {

         if (!((interaction *)this)->get_parent()->is_window())
         {

            return false;

         }

      }

      return is_window();

   }


   //::i32 interaction::get_window_long(i32 nIndex) const
   //{

   //   if (window() == nullptr)
   //   {

   //      return 0;

   //   }

   //   return window()->get_window_long(nIndex);

   //}


   //::i32 interaction::set_window_long(i32 nIndex, ::i32 lValue)
   //{

   //   if (window() == nullptr)
   //   {

   //      return 0;

   //   }

   //   return window()->set_window_long(nIndex, lValue);

   //}


   ::property_object * interaction::parent_property_set_holder() const
   {

      ::user::element * pelement = ((interaction *)
         this)->get_parent();

      if (::is_set(pelement))
      {

         return pelement->user_interaction_base();

      }

      pelement = ((interaction *)
         this)->get_owner();

      if (::is_set(pelement))
      {

         return pelement->user_interaction_base();

      }

      return ::user::interaction_base::parent_property_set_holder();

   }


   //iptr interaction::get_window_long_ptr(i32 nIndex) const
   //{

   //   if (window() == nullptr)
   //   {

   //      return 0;

   //   }

   //   return window()->get_window_long_ptr(nIndex);

   //}


   //void interaction::set_window_long_ptr(i32 nIndex, iptr lValue)
   //{

   //   if (window() == nullptr)
   //   {

   //      return 0;

   //   }

   //   return window()->set_window_long_ptr(nIndex, lValue);

   //}


   void interaction::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point_i32 & point)
   {

      //if (window() == nullptr)
      //{

      //   return nullptr;

      //}

      //return window()->ChildWindowFromPoint(point);

      return nullptr;

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags)
   {

      //if (window() == nullptr)
      //{

      //   return nullptr;

      //}

      //return window()->ChildWindowFromPoint(point, nFlags);

      return nullptr;

   }


   ::user::interaction * interaction::get_first_child_window()
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto pchildren = m_puserinteractionpointeraChild;

      if (::is_null(pchildren) || pchildren->has_no_interaction())
      {

         return nullptr;

      }

      return pchildren->get_first_interaction();

   }


   ::user::interaction * interaction::get_next_sibling_window()
   {

      auto pparent = get_parent();

      if (pparent == nullptr)
      {

         return nullptr;

      }

      _synchronous_lock synchronouslock(pparent->window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = pparent->m_puserinteractionpointeraChild;

      auto iFind = puserinteractionpointeraChild->find_first_interaction(this);

      if (iFind + 1 >= puserinteractionpointeraChild->interaction_count())
      {

         return nullptr;

      }

      return puserinteractionpointeraChild->interaction_at(iFind + 1);

   }


   ::user::interaction * interaction::get_next_window(bool bIgnoreChildren, ::user::interaction * puserinteractionStop)
   {

      {

         _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

         if (!bIgnoreChildren)
         {

            auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

            if (puserinteractionpointeraChild && puserinteractionpointeraChild->has_interaction())
            {

               auto puserinteractionFirstChild = puserinteractionpointeraChild->first_interaction();

               if (puserinteractionFirstChild)
               {

                  if (puserinteractionFirstChild == puserinteractionStop)
                  {

                     return nullptr;

                  }

                  return puserinteractionpointeraChild->first_interaction();

               }

            }

         }

      }

      {

         auto puserinteractionParent = get_parent();

         if (!puserinteractionParent)
         {

            return nullptr;

         }

         _synchronous_lock synchronouslockParent(puserinteractionParent->window()->m_pparticleChildrenSynchronization);

         auto puserinteractionpointeraChild = puserinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         auto iFind = puserinteractionpointeraChild->find_first_interaction(this);

         if (::not_found(iFind))
         {

            return nullptr;

         }

         if (iFind >= puserinteractionpointeraChild->interaction_count())
         {

            if (puserinteractionParent == puserinteractionStop)
            {

               return nullptr;

            }

            return puserinteractionParent->get_next_window(true, puserinteractionStop);

         }

         auto puserinteractionNextSibling = puserinteractionpointeraChild->interaction_at(iFind + 1);

         if (puserinteractionNextSibling == puserinteractionStop)
         {

            return nullptr;

         }

         return puserinteractionNextSibling;

      }

   }


   ::user::interaction * interaction::get_window(enum_next enext)
   {

      if (enext == e_next_sibling)
      {

         return get_next_window(true);

      }
      else if (enext == e_next_proper)
      {

         return get_next_window(false);

      }
      else
      {

         throw ::exception(error_bad_argument);

      }

      return nullptr;

   }


   bool interaction::is_message_only_window()
   {

      return m_bMessageWindow;

   }


   ::user::interaction * interaction::get_wnd(::u32 nCmd)
   {

      //if (window() == nullptr)
      //{

      //   return nullptr;

      //}

      //return window()->get_wnd(nCmd);

      return nullptr;

   }


   //::user::interaction * interaction::GetActiveWindow()
   //{

   //   if (window() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return window()->GetActiveWindow();

   //}


   //bool interaction::set_keyboard_focus()
   //{

   //   if (window() == nullptr)
   //   {

   //      return false;

   //   }

   //   return window()->set_keyboard_focus();

   //}


   //::user::interaction_base * interaction::get_keyboard_focus()
   //{

   //   if (window() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return window()->get_keyboard_focus();

   //}


   //::user::interaction * interaction::set_active_window()
   //{

   //   if (window() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return window()->set_active_window();

   //}


   //bool interaction::set_foreground_window()
   //{

   //   if (window() == nullptr)
   //   {

   //      return false;

   //   }

   //   return window()->set_foreground_window();

   //}


   ::user::interaction * interaction::GetLastActivePopup()
   {

      //if (window() == nullptr)
      //{

      //   return nullptr;

      //}

      //return window()->GetLastActivePopup();

      return nullptr;

   }


   /*bool interaction::is_text_composition_active()
      {

         auto pwindowThis = window();

         if (::is_null(pwindow))
         {

            return false;

         }

         return pwindow->is_text_composition_active();

      }*/


      //::form_property_set * interaction::get_form_property_set()
      //{

      //   if (m_pformpropertyset)
      //   {

      //      return m_pformpropertyset;

      //   }

      //   return ::user::interaction_base::get_form_property_set();

      //}


   int interaction::on_text_composition_message(int iMessage)
   {

      return -1;

   }


   void interaction::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & actioncontext)
   {

      auto strText = get_window_text();

      strsize iBeg = strText.length();

      strsize iEnd = strText.length();

      get_text_selection(iBeg, iEnd);

      strText.translate_index(iBeg);

      strText.translate_index(iEnd);

      strText.replace_index(iBeg, iEnd, strText);

      if (m_pappearance)
      {

         auto psz = strText.c_str();

         while (*psz)
         {

            string strUtf8Character = get_utf8_char(psz);

            auto iCharacter = unicode_index(strUtf8Character);

            m_pappearance->on_character(iCharacter);

            psz += strUtf8Character.length();

         }

      }

   }


   void interaction::set_window_text(const ::string & pszString)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         //m_strWindowText2 = pszString;
         m_textproperty.set_property(pszString, ::e_source_sync);

      }

      on_set_window_text();

   }


   void interaction::set_window_text_source(const ::a_string_function & astringfunction)
   {

      m_astringfunctionWindowText = astringfunction;

   }


   void interaction::clear_window_text_source()
   {

      m_astringfunctionWindowText = nullptr;

   }


   void interaction::on_set_window_text()
   {

      //if (window() != nullptr)
      //{

      //   window()->on_set_window_text();

      //}

   }


   ::string interaction::get_window_text()
   {

      if (m_astringfunctionWindowText)
      {

         return m_astringfunctionWindowText();

      }
      else
      {

         _synchronous_lock synchronouslock(this->synchronization());

         //return m_strWindowText2;

         return m_textproperty.get_property();

      }

   }


   //   strsize interaction::get_window_text(char* pszStringBuf, strsize nMaxCount)
   //   {
   //
   //      ::string strWindowText = _get_window_text();
   //
   //      strsize n = minimum(nMaxCount, strWindowText.length());
   //
   //      ansi_count_copy(pszStringBuf, strWindowText, n);
   //
   //      return n;
   //
   //   }


   //   string interaction::get_window_text()
   //   {
   //
   //      string str;
   //
   //      get_window_text(str);
   //
   //      return str;
   //
   //   }


   //   void interaction::get_window_text(string& str)
   //   {
   //
   //      str = _get_window_text();
   //
   //   }


   //   strsize interaction::get_window_text_length()
   //   {
   //
   //      _synchronous_lock synchronouslock(this->synchronization());
   //
   //      if (window() == nullptr)
   //      {
   //
   //         return 0;
   //
   //      }
   //
   //      return window()->get_window_text_length();
   //
   //   }


   //::user::interaction * interaction::EnsureTopLevel()
   //{

   //   ::pointer<interaction>pwindow = get_top_level();

   //   ENSURE_VALID(pwindow);

   //   return pwindow;

   //}


   ::user::frame * interaction::frame()
   {

      ::user::interaction * pinteraction = (::user::interaction *)this;

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      do
      {

         if (pinteraction->is_frame_window())
         {

            return dynamic_cast <::user::frame *>(pinteraction);

         }

         pinteraction = pinteraction->get_parent();

      } while (pinteraction != nullptr);

      return nullptr;

   }


   ::user::interaction * interaction::top_level()
   {

      return _top_level();

   }


   ::user::frame * interaction::top_level_frame()
   {

      return _top_level_frame();

   }


   ::user::frame * interaction::parent_frame()
   {

      return _parent_frame();

   }


   ::user::frame * interaction::_parent_frame()
   {

      ::user::interaction * pinteraction = get_parent();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      return pinteraction->frame();

   }


   ::user::interaction * interaction::_top_level()
   {

      ::user::interaction * puserinteractionParent = (::user::interaction *)this;

      ::user::interaction * puiTopLevelParent;

      if (puserinteractionParent == nullptr)
      {

         return nullptr;

      }

      do
      {

         puiTopLevelParent = puserinteractionParent;

         puserinteractionParent = puserinteractionParent->get_parent();

      } while (puserinteractionParent != nullptr);

      return puiTopLevelParent;

   }


   ::user::frame * interaction::_top_level_frame()
   {

      auto pframe = frame();

      if (!pframe)
      {

         return nullptr;

      }

      ::user::frame * pframeTopLevel;

      do
      {

         pframeTopLevel = pframe;

         pframe = pframeTopLevel->parent_frame();

      } while (::is_set(pframe));

      return pframeTopLevel;

   }


   void interaction::on_destroy()
   {

      //auto estatus =

      ::object::on_destroy();

      //return estatus;

   }


   //void interaction::start_destroying_window()
   //{

   //   auto type = ::type(this);

   //   if (type.name().contains("main_frame"))
   //   {

   //      informationf("main_frame start_destroying_window\n");

   //   }

   //   if (has_destroying_flag())
   //   {

   //      return;

   //   }

   //   set_destroying_flag();

   //   destroy_window();

   //   // set_destroying() m_bUserElementOk = false;

   //   // set_destroying() m_ewindowflag -= e_window_flag_is_window;

   //   //if (window() == nullptr)
   //   //{

   //   //   return;

   //   //}

   //   //::user::interaction_base::on_finish();

   //   //window->start_destroying_window();

   //}


   void interaction::destroy_window()
   {

      //   m_bUserElementOk = false;
      //
      if (!(m_ewindowflag & e_window_flag_is_window))
      {

         return;

      }

      if (has_destroying_flag())
      {

         return;

      }

      set_destroying_flag();


      //
      //   if (!window())
      //   {
      //
      //      throw ::exception(error_wrong_state);
      //
      //   }

      if (m_pacmewindowingwindow)
      {

         auto pacmewindowingwindow = m_pacmewindowingwindow;

         pacmewindowingwindow->destroy_window();

         try
         {

            pacmewindowingwindow->destroy();

         }
         catch (...)
         {

         }

      }
      else
      {

         _destroy_window();

      }

      try
      {

         destroy();

      }
      catch (...)
      {

      }

   }



   void interaction::_destroy_window()
   {

      if (!(m_ewindowflag & e_window_flag_is_window))
      {

         return;

      }

      message_call(e_message_destroy);

      message_call(e_message_non_client_destroy);

   }


   void interaction::destroy()
   {

      finalize();

      {

         _synchronous_lock synchronouslock(this->synchronization());

         try
         {

            erase_all_routes();

         }
         catch (...)
         {

         }

      }

      set_flag(e_flag_task_ready);

      set_flag(e_flag_task_terminated);

      {

         auto pobjectParentTask = m_pobjectParentTask;

         if (::is_set(pobjectParentTask))
         {

            pobjectParentTask->erase_task_and_set_task_new_parent(this, nullptr);

         }

      }


      auto type = ::type(this);

      if (type.name().contains("main_frame"))
      {

         informationf("main_frame post_non_client_destroy");

      }

      //::user::interaction_base::post_non_client_destroy();

      //window().release();

      //windowing_window().release();


      //auto pacmewindowingwindow = m_pacmewindowingwindow;

      //if (::is_set(pacmewindowingwindow))
      //{

      //   try
      //   {

      //      pacmewindowingwindow->destroy();

      //   }
      //   catch (...)
      //   {

      //   }

      //}

      // ownership

      //if(m_pinteractiondraw2d)
      //{
      //if (m_pshapeaClip) m_pshapeaClip->destroy();
      m_pdrawcontext.defer_destroy();
      
      m_pmatterCommandHandler.release();
      //}
      m_pusersystem.defer_destroy();
      //      if (m_playout) m_playout->destroy();
      m_pgraphicscalla.defer_destroy();
      m_puserinteractionCustomWindowProc.defer_destroy();
      m_puiLabel.defer_destroy();
      //if (m_puseritema) m_puseritema->destroy_all();
      // tasks should not be destroyed in destroy
      //m_pform && m_pform != this && m_pform->destroy();
      m_palphasource.defer_destroy();
      //if (m_pdrawableBackground) m_pdrawableBackground->destroy();
      //if (window()) window()->destroy();
      //if (windowing_window()) windowing_window()->destroy();

      {

         _synchronous_lock synchronouslock(this->synchronization());

         if (m_puserinteractionpointeraOwned) m_puserinteractionpointeraOwned->destroy();

      }


      //user_thread() && user_thread()->destroy();
      // tasks should not be destroyed in destroy
      //user_thread() && user_thread()->destroy();
      m_ptooltip.defer_destroy();
      m_pmenuitem.defer_destroy();
      m_menua.clear();

      // ownership
      //if(m_pinteractiondraw2d)
      {
         //m_pshapeaClip.release();
         m_pdrawcontext.release();

      }

      m_pusersystem.release();
      ///m_playout.release();
      m_pgraphicscalla.release();
      m_puserinteractionCustomWindowProc.release();
      m_puiLabel.release();
      //if (m_puseritema) m_puseritema->erase_all();
      m_pform.release();
      m_palphasource.release();
      //m_pdrawableBackground.release();
      //window().release();
      ///windowing_window().release();

      m_pinteractionScaler.defer_destroy();

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_puserinteractionpointeraOwned.release();

      }

      //{

      //   _synchronous_lock synchronouslock(m_pwindow ? m_pwindow->m_pparticleChildrenSynchronization : nullptr);

      //   m_puserinteractionpointeraChild.release();

      //}

      m_ptooltip.release();
      m_pmenuitem.release();
      //m_menua.erase_all();


      // references
      m_pitemComposing.release();
      //user_thread().release();
      m_puserinteractionParent.release();
      m_pupdowntarget.release();
      m_ptaskModal.release();
      m_puserinteractionOwner.release();
      //m_pwindow.release();
      //return ::success;
      ::user::interaction_base::destroy();



   }


   //void interaction::post_non_client_destroy()
   //{

   //   finalize();

   //   {

   //      _synchronous_lock synchronouslock(this->synchronization());

   //      try
   //      {

   //         erase_all_routes();

   //      }
   //      catch (...)
   //      {

   //      }

   //   }

   //   set_flag(e_flag_task_ready);

   //   set_flag(e_flag_task_terminated);

   //   {

   //      auto pobjectParentTask = m_pobjectParentTask;

   //      if (::is_set(pobjectParentTask))
   //      {

   //         pobjectParentTask->erase_task_and_set_task_new_parent(this, nullptr);

   //      }

   //   }


   //   auto type = ::type(this);

   //   if (type.name().contains("main_frame"))
   //   {

   //      informationf("main_frame post_non_client_destroy");

   //   }

   //   ::user::interaction_base::post_non_client_destroy();

   //   //window().release();

   //   //windowing_window().release();

   //}


   bool interaction::is_ready_to_quit() const
   {

      bool bShouldContinue = task_get_run();

      return !bShouldContinue && has_flag(e_flag_task_ready);

   }


   void interaction::set_appearance(::appearance::appearance * pappearance)
   {

      m_pappearance = pappearance;

      pappearance->set_user_interaction(this);

   }


   ::appearance::appearance * interaction::get_appearance()
   {

      return m_pappearance;

   }


   bool interaction::is_sandboxed()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         throw ::exception(error_wrong_state);

      }

      bool bSandboxed = pwindowing->get_application_host_window() != nullptr;

      return bSandboxed;

   }


   ::user::thread * interaction::user_thread()
   {

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         return nullptr;

      }

      auto puserthread = pwindowThis->m_puserthread;

      if (!puserthread)
      {

         return nullptr;

      }

      return puserthread;

   }


   //void interaction::CalcWindowRect(::rectangle_i32 * prectangle, ::u32 nAdjustType)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   return window()->CalcWindowRect(prectangle, nAdjustType);

   //}


   void interaction::show_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void interaction::hide_control_bar(::user::control_bar * pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void interaction::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeft, ::u32 nFlags,
                                    ::rectangle_i32 * prectParam, const ::rectangle_i32 & rectangleX,
                                    bool bStretch)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //return window()->RepositionBars(nIDFirst, nIDLast, idLeftOver, nFlag, prectParam, rectangleX,
//                                              bStretch);


      if (!_is_window())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(nIDFirst);

      __UNREFERENCED_PARAMETER(nIDLast);

      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery ||
             (nFlags & ~reposNoPosLeftOver) == reposExtra);

      size_parent_layout sizeparentlayout;

      ::pointer<::user::interaction> puiLeft;

      sizeparentlayout.m_bStretch = bStretch;

      sizeparentlayout.m_sizeTotal.cx() = sizeparentlayout.m_sizeTotal.cy() = 0;

      if (rectangleX.is_set())
      {

         sizeparentlayout.m_rectangle = rectangleX;

      }
      else
      {

         input_client_rectangle(sizeparentlayout.m_rectangle, e_layout_sketch);

      }

      if (::is_empty(sizeparentlayout.m_rectangle))
      {

         return;

      }

      ::pointer<::user::interaction> pinteraction;

      while (this->get_child(pinteraction))
      {

         atom atom = pinteraction->GetDlgCtrlId();

         if (atom == idLeft)
         {

            puiLeft = pinteraction;

         }
         else
         {

            pinteraction->send_message(e_message_size_parent, 0, (lparam)&sizeparentlayout);

         }

      }

      if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
      {

         ASSERT(prectParam != nullptr);

         if (bStretch)
         {

            *prectParam = sizeparentlayout.m_rectangle;

         }
         else
         {

            prectParam->left() = prectParam->top() = 0;

            prectParam->right() = sizeparentlayout.m_sizeTotal.cx();

            prectParam->bottom() = sizeparentlayout.m_sizeTotal.cy();

         }

         return;

      }

      if (!idLeft.is_empty() && puiLeft != nullptr)
      {

         if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {

            ASSERT(prectParam != nullptr);


            sizeparentlayout.m_rectangle.left() += prectParam->left();

            sizeparentlayout.m_rectangle.top() += prectParam->top();

            sizeparentlayout.m_rectangle.right() -= prectParam->right();

            sizeparentlayout.m_rectangle.bottom() -= prectParam->bottom();

         }

         if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
         {

            //puiLeft->CalcWindowRect(&sizeparentlayout.m_rectangle);

            puiLeft->place(sizeparentlayout.m_rectangle);

            puiLeft->display();

            puiLeft->set_need_layout();

         }

      }

   }


   ::user::interaction_base * interaction::set_owner(::user::interaction_base * pprimitive)
   {

      auto puserinteractionOwnerOld = m_puserinteractionOwner;

      if (::is_set(puserinteractionOwnerOld)
         && puserinteractionOwnerOld != pprimitive)
      {

         auto puserinteractionpointeraOwned = puserinteractionOwnerOld->m_puserinteractionpointeraOwned;

         if (::is_set(puserinteractionpointeraOwned))
         {

            try
            {

               puserinteractionpointeraOwned->erase_interaction(this);

            }
            catch (...)
            {

            }

         }

      }

      m_puserinteractionOwner = pprimitive;

      m_puserinteractionOwner->on_add_owned(this);

      //__defer_set_owner_to_impl();

      return puserinteractionOwnerOld;

   }


   /* void interaction::__defer_set_owner_to_impl()
    {

       if(window())
       {

          on_set_owner(m_puserinteractionOwner);

          window()->set_owner(m_puserinteractionOwner);

          if (m_ewindowflag & e_window_flag_satellite_window)
          {

             user_thread() = m_puserinteractionOwner->user_thread();

          }

       }

    }*/


   void interaction::on_add_owned(::user::interaction_base * pprimitive)
   {

      __defer_construct_new(m_puserinteractionpointeraOwned);

      m_puserinteractionpointeraOwned->add_interaction(dynamic_cast <::user::interaction *> (pprimitive));

   }


   ::user::interaction * interaction::get_owner()
   {

      auto ptoplevel = top_level();

      if (!ptoplevel)
      {

         return nullptr;

      }

      auto powner = ptoplevel->m_puserinteractionOwner;

      if (!powner)
      {

         return nullptr;

      }

      return powner;

   }


   ::user::frame * interaction::get_owner_frame()
   {

      ::user::interaction * pinteraction = get_owner();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      ::user::frame * pframe = dynamic_cast <::user::frame *> (pinteraction);

      while (pinteraction != nullptr)
      {

         if (pframe != nullptr)
         {

            return pframe;

         }

         pframe = pinteraction->parent_frame();

         if (pframe != nullptr)
         {

            return pframe;

         }

         pinteraction = pinteraction->get_owner();

         if (pinteraction == nullptr)
         {

            break;

         }

         pframe = dynamic_cast <::user::frame *> (pinteraction);

      }

      return nullptr;

   }


   ::user::interaction * interaction::top_owner()
   {

      return _top_owner();

   }


   ::user::interaction * interaction::_top_owner()
   {

      ::user::interaction * pinteractionOwner = get_owner();

      if (!pinteractionOwner)
      {

         return nullptr;

      }

      while (true)
      {

         ::user::interaction * pinteractionOwnerOwner = pinteractionOwner->get_owner();

         if (!pinteractionOwnerOwner)
         {

            return pinteractionOwner;

         }

         pinteractionOwner = pinteractionOwnerOwner;

      }

   }


   ::user::interaction * interaction::get_parent_owner()
   {

      ::pointer<::user::interaction> puserinteractionParent = get_parent();

      if (puserinteractionParent.is_null())
      {

         return nullptr;

      }

      return puserinteractionParent->get_owner();

   }


   ::user::interaction * interaction::get_parent_or_owner()
   {

      ::pointer<::user::interaction> puserinteractionParent = get_parent();

      if (puserinteractionParent.is_set())
      {

         return puserinteractionParent;

      }

      return get_owner();

   }


   ::user::interaction * interaction::get_top_level_owner()
   {

      ::pointer<::user::interaction> puiOwner = get_owner();

      ::pointer<::user::interaction> puiTopLevelOwner;

      if (puiOwner.is_null())
      {

         return nullptr;

      }

      do
      {

         puiTopLevelOwner = puiOwner;

         puiOwner = puiOwner->get_parent();

      } while (puiOwner.is_set());

      return puiTopLevelOwner;

   }


   //   bool interaction::is_host_top_level() const
   //   {
   //
   //      if(is_top_level())
   //      {
   //
   //         auto pwindowing = windowing();
   //
   //         if(pwindowing->is_sandboxed())
   //         {
   //
   //            return true;
   //
   //         }
   //
   //      }
   //
   //      return false;
   //
   //   }


   void interaction::viewport_client_to_screen(::sequence2_i32 & sequence)
   {

      //window()->viewport_client_to_screen(sequence);

   }


   bool interaction::window_is_notify_icon_enabled()
   {

      return false;

   }


   void interaction::viewport_screen_to_client(::sequence2_i32 & sequence)
   {

      //if (::is_null(window()))
      //{

      //   return;

      //}

      viewport_screen_to_client(sequence);

   }


   void interaction::viewport_client_to_screen(::rectangle_i32 & rectangle)
   {

      viewport_client_to_screen(rectangle.top_left());

      viewport_client_to_screen(rectangle.bottom_right());

   }


   void interaction::viewport_screen_to_client(::rectangle_i32 & rectangle)
   {

      viewport_screen_to_client(rectangle.top_left());

      viewport_screen_to_client(rectangle.bottom_right());

   }


   //bool interaction::layout().is_zoomed()
   //{

   //   if (window() == nullptr)
   //   {

   //      return false;

   //   }

   //   return window()->layout().is_zoomed();

   //}


   ::e_display interaction::window_stored_display()
   {

      return e_display_none;

   }


   ::e_display interaction::window_previous_display()
   {

      return e_display_none;

   }


   void interaction::set_window_previous_display(::e_display edisplayPrevious)
   {


   }


   bool interaction::is_full_screen_enabled()
   {

      return true;

   }


   bool interaction::_is_full_screen()
   {

      auto pwindowThis = window();

      if (!pwindowThis->is_full_screen())
      {

         return false;

      }

      bool bDisplayIsFullScreen = top_level_frame()->layout().is_full_screen();

      return bDisplayIsFullScreen;

   }


   float interaction::preferred_dpi_x()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return ::user::interaction_base::preferred_dpi_x();

      }

      return pwindowThis->get_dpi_for_window();

   }


   float interaction::preferred_dpi_y()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return ::user::interaction_base::preferred_dpi_y();

      }

      return pwindowThis->get_dpi_for_window();

   }


   float interaction::preferred_density()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return ::user::interaction_base::preferred_density();

      }

      return pwindowThis->get_density_for_window();

   }


   void interaction::sort_children_by_zorder(::user::interaction_array & interactiona)
   {

      interactiona.interactiona().predicate_sort([this](auto & p1, auto & p2)
         {

            return child_zorder(p1) < child_zorder(p2);

         });

   }


   ::collection::index interaction::child_zorder(::user::interaction * puserinteraction)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      if (!m_puserinteractionpointeraChild)
      {

         return -1;

      }

      auto iZorderIndex = m_puserinteractionpointeraChild->find_first_interaction(puserinteraction);

      return iZorderIndex;

   }


   bool interaction::check_children_zorder()
   {

      if (m_bPendingChildrenZorder)
      {

         return true;

      }

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         for (auto & pchild : puserinteractionpointeraChild->interactiona())
         {

            if (pchild && pchild->layout().sketch().zorder().is_change_request())
            {

               //::string strType = ::type(pchild).name();

               //if (strType.case_insensitive_contains("place_holder"))
               //{

               //   _synchronous_lock synchronouslockChild(pchild->window()->m_pparticleChildrenSynchronization);

               //   if (pchild->m_puserinteractionpointeraChild
               //      && pchild->m_puserinteractionpointeraChild->has_interaction())
               //   {

               //      auto puserinteractionChild = pchild->m_puserinteractionpointeraChild->first_interaction();



               //      ::string strTypePlaceHolderChild = ::type(puserinteractionChild).name();

               //      if (strTypePlaceHolderChild.case_insensitive_contains("simple_frame_window"))
               //      {

               //         auto puserinteractionChild2 = puserinteractionChild->m_puserinteractionpointeraChild->first_interaction();

               //         ::string strTypePlaceHolderChild2 = ::type(puserinteractionChild2).name();

               //         if (strTypePlaceHolderChild2.case_insensitive_contains("font_impact"))
               //         {

               //            information() << "interaction::check_child_zorder " << strTypePlaceHolderChild2;

               //            if (m_puserinteractionpointeraChild->contains_interaction(pchild))
               //            {

               //               information() << "tab impact has font_list place_holder as child window";

               //            }

               //         }

               //      }

               //   }

               //}

               m_bPendingChildrenZorder = true;

            }

         }

      }

      return m_bPendingChildrenZorder;

   }


   zorder interaction::zorder(enum_layout elayout)
   {

      return const_layout().state(elayout).zorder();

   }


   void interaction::order(::zorder zorder)
   {

      layout().sketch() = zorder;

   }


   bool interaction::should_save_window_rectangle()
   {

      return false;

   }


   void interaction::WindowDataSaveWindowRectangle()
   {

      //return false;

   }


   bool interaction::WindowDataLoadWindowRectangle()
   {

      return false;

   }


   bool interaction::FancyWindowDataLoadWindowRectangle(bool bForceRestore, bool bInitialFramePosition)
   {

      return false;

   }


   void interaction::on_defer_display()
   {

   }


   bool interaction::display_lading_to_layout()
   {

      auto type = ::type(this);

      auto edisplayLayout = layout().layout().display();

      auto edisplayLading = layout().lading().display();

      auto eactivationLading = layout().lading().activation();

      bool bDisplay =
         edisplayLading != edisplayLayout
         || eactivationLading & e_activation_under_mouse_cursor
         || eactivationLading & e_activation_display_change;

      if (bDisplay)
      {

         bDisplay = _001OnBeforeEnterAppearance();

      }

      if (bDisplay)
      {

         bDisplay = _001OnBeforeExitAppearance();

      }

      if (bDisplay)
      {

         layout_display();

      }

      return bDisplay;

   }


   void interaction::design_window_stored_state()
   {

      auto edisplayStored = window_stored_display();

      display(edisplayStored);

   }


   void interaction::design_window_iconic()
   {

      if (get_parent() != nullptr)
      {

         warning() << "iconify child window?";

         layout().sketch() = e_display_normal;

      }
      else
      {

         design_window_minimize(layout().sketch().activation());

      }

   }


   void interaction::layout_display()
   {

      ::string strType = ::type(this).name();

      if (strType.case_insensitive_contains("page_home"))
      {

         information() << "page_home";

      }

      auto edisplayPrevious = layout().layout().display();

      auto edisplayLading = layout().lading().display();

      if (!get_parent())
      {

         information() << "interaction::layout_display type: " << strType << ", edisplayLading : " << edisplayLading;

      }

      // This check prevents saving a previous state that is the same as
      // the current one or that is equivalent (through the equivalence_sink function)
      // to the current e_display (Currently this means that e_display_broad,
      // e_display_compact and e_display_normal are considered the same
      // and not saved as previous state of such equivalent e_displays)
      if (!::is_equivalent_in_equivalence_sink(edisplayPrevious, edisplayLading)
          && ::is_screen_visible(edisplayPrevious))
      {

         set_window_previous_display(edisplayPrevious);

      }

      if (edisplayLading == ::e_display_full_screen)
      {

         if (!is_top_level_window())
         {

            warning() << "full screen child window?";

            layout().sketch() = e_display_normal;

         }
         else
         {

            design_window_full_screen(layout().sketch().parent_raw_rectangle());

         }

      }
      else if (edisplayLading == ::e_display_iconic)
      {

         design_window_iconic();

      }
      else if (edisplayLading == ::e_display_zoomed)
      {

         if (get_parent() != nullptr)
         {

            warning() << "zooming child window?";

            set_display(e_display_normal, e_layout_sketch);

         }
         else
         {

            design_window_maximize();

         }

      }
      else if (edisplayLading == ::e_display_normal)
      {

         //bool bIsUniversalWindows = is_universal_windows();

         //bool bIsSandboxed = is_sandboxed();

         //if (get_parent() != nullptr || bIsSandboxed || bIsUniversalWindows)
         //{

         //   warning() <<"restoring child window?";

         //   layout().sketch() = e_display_normal;

         //}
         //else
         //{

         //design_window_restore(edisplayLading);

         //   }


         set_display(e_display_normal, e_layout_lading);

      }
      else if (edisplayLading == ::e_display_normal)
      {

         //information() << "::user::interaction::design_display e_display_normal";

         set_display(e_display_normal, e_layout_lading);

      }
      else if (edisplayLading == ::e_display_compact
              || edisplayLading == ::e_display_broad)
      {

         if (get_parent() != nullptr)
         {

            warning() << "restoring child window?";

            set_display(e_display_normal, e_layout_lading);

         }
         else
         {

            design_window_normal(edisplayLading);

         }

      }
      else if (edisplayLading == ::e_display_up)
      {

         design_up();

      }
      else if (edisplayLading == ::e_display_down)
      {

         design_down();

      }
      else if (::is_docking_appearance(edisplayLading))
      {

         if (get_parent() != nullptr)
         {

            warning() << "snapping child window?";

            set_display(e_display_normal, e_layout_lading);

         }
         else
         {

            design_window_dock(edisplayLading);

         }

      }
      else if (is_screen_visible(edisplayLading))
      {

         if (get_parent() != nullptr)
         {

            information() << "showing child window";

         }
         else
         {

            information() << "simply showing top level window";

         }

         //display();

      }
      else
      {

         auto type = ::type(this);

         if (type.name().contains("page_home"))
         {

            information() << "page_home";

         }

         if (get_parent() != nullptr)
         {

            //information() << "hiding child window";

            set_display(e_display_none, e_layout_lading);

         }
         else
         {

            information() << "hiding top level window";

         }

         //hide();

      }

      //return true;

   }


   void interaction::layout_appearance()
   {

      //      ui_state().m_eappearance = process_state().m_eappearance;

      //return true;

   }


#undef false


   CLASS_DECL_AURA void zorder_sort(::user::interaction_array & uia, ::user::enum_layout elayout)
   {

      auto predZ = [elayout](auto & pui1, auto & pui2)
         {

            if (!pui1 || !pui2)
            {

               return false;

            }

            return (bool)(pui1->const_layout().state(elayout).zorder() < pui2->const_layout().state(elayout).zorder());

         };

      uia.interactiona().predicate_sort(predZ);

   }


   void interaction::layout_children_zorder()
   {

      //information() << "interaction::layout_children_zorder";

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puiptraChildNew = __allocate::user::interaction_array(*m_puserinteractionpointeraChild);

      zorder_sort(*puiptraChildNew, e_layout_sketch);

      m_puserinteractionpointeraChild = puiptraChildNew;

      int iZOrder = 1024;

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      ::string strType = ::type(this).name();

      for (auto & pchild : puserinteractionpointeraChild->interactiona())
      {

         pchild->layout().sketch()._patch_order(iZOrder);

         pchild->layout().sketch().zorder().clear_request();

         if (strType.case_insensitive_contains("pane_impact"))
         {

            if (pchild->is_this_visible(e_layout_sketch))
            {

               ::string strTypeChild = ::type(pchild).name();

               information() << strTypeChild << " (" << pchild->m_atom.as_string() << ")" << " zorder " << iZOrder;

            }

         }

         iZOrder += 1024;

      }

      m_bPendingChildrenZorder = false;

   }


#undef EXTRA_DESIGN_REPOSITION_LOG


   void interaction::layout_reposition()
   {

      if (!m_bUserElementOk)
      {

         return;

      }

#ifdef EXTRA_DESIGN_REPOSITION_LOG
      auto type = ::type(this);

      if (type.name().contains("control_box"))
      {

         informationf("control_box design_reposition");

      }

#endif

      ::point_i32 point = layout().lading().origin();

      ::point_i32 pointScreen;

      ::point_i32 pointHost;

      auto type = ::type(this);

      if (type.name().contains("list_box"))
      {

         informationf("list_box reposition");

      }
      else if (type.name().contains("_001"))
      {

         informationf("_001 reposition");

      }


      ::point_i32 screenOriginLadingBefore = layout().lading().origin();

      ::point_i32 screenOriginLayoutBefore = layout().layout().origin();

      bool bRepositionThis = true;
      //         layout().lading().origin() != point ||
      //         layout().layout().origin() != pointScreen;
      //
      //      if(bRepositionThis)
      //      {
      //
      //         screen_origin() = pointScreen;
      //
      //         layout().layout().screen_origin() = pointScreen;
      //
      //         layout().lading().host_origin() = pointHost;
      //
      //         layout().layout().host_origin() = pointHost;
      //
      //      }

//      auto type = ::type(this);

      if (type.name().contains("tap"))
      {

         information() << "tap graphics_thread_reposition (" << this->screen_origin().x() << ", "
            << this->screen_origin().y()
            << ")";
      }

      if (bRepositionThis)
      {

         auto children = synchronized_get_children();

         //if (puserinteractionpointeraChild)
         {

            for (auto & pinteraction : children)
            {

               //synchronouslock.unlock();

               if (pinteraction)
               {

                  pinteraction->set_reposition(true);

               }

               ///synchronouslock.lock();

            }

         }

      }

      on_reposition();

      set_reposition(false);

      //return true;

   }


   ::size_i32 interaction::preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         return pappearance->preferred_size(pgraphics);

      }

      return {};

   }


   bool interaction::is_display_like_maximized()
   {

      if (const_layout().design().display() == e_display_zoomed)
      {

         return true;

      }

      auto rectangleWindow = const_layout().design().parent_raw_rectangle();

      ::rectangle_i32 rectangleWorkspace;

      get_best_workspace(&rectangleWorkspace, rectangleWindow);

      if (windowing()->display()->is_like_maximized(rectangleWorkspace, rectangleWindow))
      {

         return true;

      }

      return false;

   }


   bool interaction::is_display_like_full_screen()
   {

      if (const_layout().design().display() == e_display_full_screen)
      {

         return true;

      }

      auto rectangleWindow = const_layout().design().parent_raw_rectangle();

      ::rectangle_i32 rectangleMonitor;

      get_best_monitor(&rectangleMonitor, rectangleWindow);

      if (windowing()->display()->is_like_full_screen(rectangleMonitor, rectangleWindow))
      {

         return true;

      }

      return false;

   }


   bool interaction::layout_layout(::draw2d::graphics_pointer & pgraphics)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //if (!window() || !window()->m_puserinteraction)
      //{

      //   return false;

      //}

      if (!is_this_visible())
      {

         if (::type(this) == "user::list_box")
         {

            information() << "interaction::layout_layout";

         }

         return false;

      }

      if (::type(this) == "user::list_box")
      {

         information() << "interaction::layout_layout";

      }

      auto rectangleRaw = raw_rectangle();

      if (rectangleRaw.is_empty())
      {

#ifdef  EXTRA_LOGGING

         information() << "layout_layout raw_rectangle is empty";

#endif

         return false;

      }

      ////if(m_pinteractiondraw2d)
      //{

      //   //m_pshapeaClip.release();

      //}

      if (pgraphics)
      {

         //defer_graphics(pgraphics);

         //window()->on_layout(pgraphics);

         on_layout(pgraphics);

         //on_change_sketch_scroll_state();

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            pappearance->perform_layout(pgraphics);

         }

      }

      {

         _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (puserinteractionpointeraChild)
         {

            auto rectangleX = this->rectangle();

            auto children = puserinteractionpointeraChild->m_interactiona;

            for (auto & pinteraction : children)
            {

               try
               {

                  ::pointer<::aura::application> papp = get_app();

                  if (pinteraction->m_bExtendOnParent ||
                      (pinteraction->m_bExtendOnParentIfOnlyClient
                         && papp && papp->m_bExperienceMainFrame))
                  {

                     synchronouslock.unlock();

                     bool bThisVisible = pinteraction->is_this_visible();

                     pinteraction->place(rectangleX);

                     pinteraction->set_need_layout();

                     synchronouslock._lock();

                  }

               }
               catch (...)
               {

               }

            }

         }

      }

      if (pgraphics)
      {

         on_drag_scroll_layout(pgraphics);

      }

      //if (::is_set(m_playout))
      //{

      //   if (m_playout->m_bFillParent)
      //   {

      //      ::rectangle_i32 rectangleX;

      //      this->rectangle(rectangleX);

      //      m_playout->place(rectangleX);

      //   }

      //   m_playout->on_layout(pgraphics);

      //}

      m_bNeedLayout = false;

      set_recalculate_clip_rectangle();

      return true;

   }


   //bool interaction::CheckAutoCenter()
   //{
   //
   //   if (window() == nullptr)
   //   {
   //
   //      return true;
   //
   //   }
   //
   //   return window()->CheckAutoCenter();
   //
   //}


   void interaction::CenterWindow(::user::interaction * pAlternateOwner)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->CenterWindow(pAlternateOwner);

   }


   //void interaction::default_window_procedure(::message::message * pmessage)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   return window()->default_window_procedure(pmessage);

   //}


   void interaction::pre_translate_message(::message::message * pmessage)
   {

      if (pmessage->m_uiMessageFlags & 1)
      {

         // message already pre translated
         return;

      }

      //auto psession = session()->m_paurasession;

      //if (::is_set(psession))
      //{

      //   auto puser = psession->user();

      //   auto pwindowing = puser->windowing();

      //   if (pwindowing)
      //   {

      //      auto psystemwindow = pwindowing->get_system_window();

      //      if (psystemwindow == nullptr || psystemwindow != this)
      //      {

      //         if (!(pmessage->m_uiMessageFlags & 2)) // message already pre translated
      //         {

      //            auto paurasession = psession->m_paurasession;

      //            paurasession->pre_translate_message(pmessage);

      //            if (pmessage->m_bRet)
      //            {

      //               return;

      //            }

      //         }

      //      }

      //   }

      //}

      pmessage->m_uiMessageFlags |= 1;

   }


   void interaction::message_handler(::message::message * pmessage)
   {

      if (pmessage->m_atom == e_message_post_user)
      {

         auto pparticle = pmessage->m_union.m_pparticle;

         ::pointer<::message::message> pmessagePost = pparticle->m_pparticle;

         if (::is_null(pmessagePost))
         {

            return;

         }

         if (pmessagePost->m_atom == e_message_scroll_y)
         {

            informationf("e_message_scroll_y");


         }
         else if (pmessagePost->m_atom == e_message_text_composition)
         {

            informationf("message text composition");

         }

         message_handler(pmessagePost);

         return;

      }

      //m_puserinteraction->message_handler(pmessage);

      bool bKeyMessage = false;

      ::message::key * pkey = nullptr;

      //if (::is_null(m_puserinteraction))
      //{

      //   return;

      //}

      if (pre_message_handler(pkey, bKeyMessage, pmessage))
      {

         information() << "returning on pre_message_handler";

         return;

      }

      if (pmessage->m_atom == e_message_timer)
      {

         //m_pthread->step_timer();

      }
      else if (pmessage->m_atom == e_message_left_button_down)
      {

         informationf("linux::interaction_impl::e_message_left_button_down");

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         informationf("linux::interaction_impl::e_message_left_button_up");

      }
      else if (pmessage->m_atom == e_message_mouse_move)
      {

         //g_iMouseMove++;

         //informationf("interaction_impl::message_handler e_message_mouse_move");
         //printf("g_iMouseMove = %d\n", g_iMouseMove);

      }
      else if (pmessage->m_atom == e_message_paint)
      {

      }
      else if (pmessage->m_atom == e_message_left_button_up)
      {

         informationf("e_message_left_button_up (0)");

      }

      //      if(::is_set(m_puserinteraction))
      //      {
      //
      //         m_puserinteraction->pre_translate_message(pmessage);
      //
      //      }

      //      if(tickDebugmessage_handlerTime.timeout(1))
      //      {
      //
      //         iDebugmessage_handlerTime = 0;
      //
      //      }
      //      else
      //      {
      //
      //         if(iDebugmessage_handlerTime > 20)
      //         {
      //
      //            informationf("interaction_impl::message handler flooded?\n");
      //
      //         }
      //         else
      //         {
      //
      //            iDebugmessage_handlerTime++;
      //
      //         }
      //
      //      }

      //if (m_puserinteraction != nullptr)
      {

         if (layout().is_moving())
         {
            //informationf("moving: skip pre translate message");
         }
         else if (layout().is_sizing())
         {
            //informationf("sizing: skip pre translate message");
         }
         else
         {

            //m_puserinteraction->pre_translate_message(pmessage);

            //if (pmessage->m_bRet)
            //{

            // return;

            //}

            //pmessage->m_uiMessageFlags |= 1;

         }

      }



      //      if(bKeyMessage)
      //      {
      //
      //         auto psession = get_session();
      //
      //         auto puser = psession->user();
      //
      //         auto pwindowing = puser->windowing();
      //
      //         ::pointer<::message::key>pkey = pmessage;
      //
      //         //pwindowing->set(pkey, get_oswindow(), m_pwindow, pkey->m_atom, pkey->m_wparam, pkey->m_lparam);
      //
      ////         if(pmessage->m_atom == e_message_key_down)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, true);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      ////         else if(pmessage->m_atom == e_message_key_up)
      ////         {
      ////
      ////            try
      ////            {
      ////
      ////               psession->set_key_pressed(pkey->m_ekey, false);
      ////
      ////            }
      ////            catch(...)
      ////            {
      ////
      ////            }
      ////
      ////         }
      //
      //      }

      pmessage->m_lresult = 0;

      if (pmessage->m_atom == e_message_mouse_leave)
      {

         _000OnMouseLeave(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_left_button_down ||
          pmessage->m_atom == e_message_left_button_up ||
          pmessage->m_atom == e_message_middle_button_down ||
          pmessage->m_atom == e_message_middle_button_up ||
          pmessage->m_atom == e_message_right_button_down ||
          pmessage->m_atom == e_message_right_button_up ||
          pmessage->m_atom == e_message_left_button_double_click ||
          pmessage->m_atom == e_message_mouse_move ||
          pmessage->m_atom == e_message_mouse_wheel)
      {

         ::pointer<::message::mouse> pmouse = pmessage;

         //information() << "msghdl pwnd : " << (::iptr) pmouse->m_pwindow.m_p;

         on_mouse_message(pmouse);

         return;

      }
      /*      else if(pmessage->m_atom == e_message_key_down ||
                    pmessage->m_atom == e_message_key_up ||
                    pmessage->m_atom == e_message_char)*/
      else if (bKeyMessage)
      {

         if (::is_set(pkey))
         {

            information() << "key message";

            ::pointer<::user::interaction> puiKeyboardFocus = window()->m_puserinteractionKeyboardFocus;

            if (puiKeyboardFocus)
            {

               information() << "key message control with keyboard focus : " << ::string(::type(puiKeyboardFocus.m_p));

               puiKeyboardFocus->route_message(pkey);

            }
            else
            {

               route_message(pkey);

            }

         }

         if (pmessage->m_bRet)
         {

            return;

         }

         on_default_window_procedure(pmessage);

         return;

      }

      if (pmessage->m_atom == e_message_subject)
      {

         //if (m_puserinteraction != nullptr)
         {

            handle((::topic *)pmessage->m_lparam.m_lparam, nullptr);

         }
         //         else
         //         {
         //
         //            on_control_event((::user::control_event *) pmessage->m_lparam.m_lparam);
         //
         //         }

         return;

      }

      //if (::is_set())
      {

         route_message(pmessage);

      }
      //else
      //{

      //   route_message(pmessage);

      //}

      if (!pmessage->m_bRet)
      {

         on_default_window_procedure(pmessage);

      }

      if (pmessage->m_atom == e_message_create)
      {

         //if (m_puserinteraction->m_procedureOnAfterCreate)
         //{

         //   m_puserinteraction->post_message(e_message_pos_create);

         //}

//         if(has_screen_output_purpose())
//         {
//
//            m_puserinteraction->set_need_layout();
//
//            m_puserinteraction->set_need_redraw();
//
//            m_puserinteraction->post_redraw();
//
//         }

         //if(m_puserinteraction->m_setneedredrawa.has_element())
         //{

         //   m_puserinteraction->post_redraw();

         //}

      }

   }

   void interaction::on_default_window_procedure(::message::message * pmessage)
   {

   }


   //lresult interaction::message_handler(MESSAGE * pmessage)
   //{

   //   return send_message((enum_message) pmessage->message, pmessage->wParam, pmessage->lParam);

   //}


   //#ifdef WINDOWS_DESKTOP
   //
   //   bool interaction::GetWindowPlacement(WINDOWPLACEMENT* puserinteractionpl)
   //   {
   //
   //      if (window() == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return window()->GetWindowPlacement(puserinteractionpl);
   //
   //   }
   //
   //
   //   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
   //   {
   //
   //      if (window() == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return window()->SetWindowPlacement(puserinteractionpl);
   //
   //   }
   //
   //
   //#endif


   bool interaction::pre_create_window(::user::system * pusersystem)
   {
      //
      //#ifdef WINDOWS_DESKTOP
      //

      //#endif

      return true;

   }


   bool interaction::IsTopParentActive()
   {

      //if (window() == nullptr)
      //{

      //   return false;

      //}

      //return window()->IsTopParentActive();

      return false;

   }


   void interaction::ActivateTopParent()
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->ActivateTopParent();

   }


   void interaction::update_dialog_controls(channel * pTarget)
   {

      //if (::is_null(window()))
      //{

      //   return;

      //}

      //window()->update_dialog_controls(pTarget);

   }


   //void interaction::UpdateWindow()
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->UpdateWindow();

   //}


   void interaction::register_drop_target()
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->register_drop_target();

   }


   //void interaction::SetRedraw(bool bRedraw)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->SetRedraw(bRedraw);

   //}


   //bool interaction::GetUpdateRect(::rectangle_i32 *prectangle, bool bErase)
   //{

   //   //if (window() == nullptr)
   //   //{

   //   //   return false;

   //   //}

   //   //return window()->GetUpdateRect(prectangle, bErase);

   //   return false;

   //}


   //i32 interaction::GetUpdateRgn(::draw2d::region *pRgn, bool bErase)
   //{

   //   if (window() == nullptr)
   //   {

   //      return 0;

   //   }

   //   return window()->GetUpdateRgn(pRgn, bErase);

   //}


   //void interaction::Invalidate(bool bErase)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->Invalidate(bErase);

   //}


   //void interaction::InvalidateRect(const ::rectangle_i32 &rectangle, bool bErase)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->InvalidateRect(rectangle, bErase);

   //}


   //void interaction::InvalidateRgn(::draw2d::region *pRgn, bool bErase)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->InvalidateRgn(pRgn, bErase);

   //}


   //void interaction::ValidateRect(const ::rectangle_i32 &rectangle)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->ValidateRect(rectangle);

   //}


   //void interaction::ValidateRgn(::draw2d::region *pRgn)
   //{

   //   if (window() == nullptr)
   //   {

   //      return;

   //   }

   //   window()->ValidateRgn(pRgn);

   //}


   void interaction::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      layout().m_elayoutexperience = elayoutexperience;

      //if (::is_null(window()))
      //{

      //   return;

      //}

      //window()->on_start_layout_experience(elayoutexperience);

   }


   void interaction::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {

      ASSERT(layout().m_elayoutexperience == elayoutexperience);

      layout().m_elayoutexperience = e_layout_experience_none;

      //if (::is_null(window()))
      //{

      //   return;

      //}

      //window()->on_end_layout_experience(elayoutexperience);

   }


   void interaction::on_configuration_change(::user::interaction_base * pprimitiveSource)
   {

      //if (window())
      //{

      //   window()->on_configuration_change(pprimitiveSource);

      //}

   }


   ::size_f64 interaction::get_fitting_size(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_font(this, ::e_element_none);

      ::write_text::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      ::size_f64 setFittingFontHeight;

      string strWindowText = get_window_text();

      ::size_f64 size = pgraphics->get_text_extent(strWindowText);

      setFittingFontHeight.cx() = size.cx();

      setFittingFontHeight.cy() = metric.get_line_height();

      return setFittingFontHeight;

   }


   ::size_f64 interaction::get_adjusted_fitting_size(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      ::rectangle_f64 rectanglePadding = get_padding(pstyle);

      auto sizeFitting = get_fitting_size(pgraphics);

      ::size_f64 sizePaddedFitting;

      sizePaddedFitting.cx() = rectanglePadding.left() + sizeFitting.cx() + rectanglePadding.right();

      sizePaddedFitting.cy() = rectanglePadding.top() + sizeFitting.cy() + rectanglePadding.bottom();

      return sizePaddedFitting;

   }


   ::size_f64 interaction::get_preferred_size(::draw2d::graphics_pointer & pgraphics)
   {

      return const_layout().sketch().size();

   }


   void interaction::resize_to_fit(::draw2d::graphics_pointer & pgraphics)
   {

      auto size = get_preferred_size(pgraphics);

      set_size(size);

   }


   ::user::enum_state interaction::get_user_state()
   {

      if (!is_window_enabled())
      {

         return ::user::e_state_disabled;

      }
      else
      {

         auto pwindowThis = window();

         if (has_hover() && (::is_set(m_pitemHover) || pwindowThis->m_puiLastLButtonDown == this))
         {

            return ::user::e_state_hover;

         }
         else
         {

            return ::user::e_state_none;

         }

      }

   }


   bool interaction::has_hover()
   {

      return has_link();

   }


   bool interaction::has_link()
   {

      return false;

   }


   pointer_array<interaction> * interaction::children()
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      if (::is_null(m_puserinteractionpointeraChild))
      {

         return nullptr;

      }

      return &m_puserinteractionpointeraChild->interactiona();

   }


   void interaction::_extend_on_parent(::draw2d::graphics_pointer & pgraphics)
   {

      //if (::string(typeid(*this).name()).contains("impact"))
      //{

      //   information() << "interaction::on_perform_top_down_layout impact";

      //}

      auto pparent = get_parent();

      auto sizeParent = pparent->size(::user::e_layout_lading);

      auto sizeThis = size(::user::e_layout_lading);

      if (sizeThis != sizeParent)
      {

         set_size(sizeParent, ::user::e_layout_layout, pgraphics);

      }

      auto positionThis = position(::user::e_layout_lading);

      if (positionThis.is_set())
      {

         set_position({}, ::user::e_layout_layout, pgraphics);

      }

   }


   void interaction::_extend_on_parent_hosting_area(::draw2d::graphics_pointer & pgraphics)
   {

      auto pparent = get_parent();

      auto rectangleClient = pparent->hosting_rectangle(::user::e_layout_layout);

      auto sizeParentClientArea = rectangleClient.size();

      auto sizeThis = size(::user::e_layout_lading);

      if (sizeThis != sizeParentClientArea)
      {

         set_size(sizeParentClientArea, ::user::e_layout_layout, pgraphics);

      }

      auto positionParentClientArea = rectangleClient.origin();

      auto positionThis = position(::user::e_layout_lading);

      if (positionThis != positionParentClientArea)
      {

         set_position(positionParentClientArea, ::user::e_layout_layout, pgraphics);

      }

   }


   void interaction::top_down_prefix()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::string strType = ::type(this).name();

      //      if (strType == "user::still")
      //      {
      //
      //         ::pointer < ::user::still > puserstill = this;
      //
      //         auto psz2 = puserstill->m_strWindowText2.c_str();
      //
      //         information() << "user::still top_down_prefix text " << psz2;
      //
      //      }

      sketch_to_lading();

      m_bUpdateBuffer = false;

      m_bUpdateWindow = false;

      lading_to_layout(m_bUpdateBuffer, m_bUpdateWindow);

   }


   bool interaction::should_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

      return m_bNeedPerformLayout;

   }


   bool interaction::need_on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

      bool bNeedOnPerformLayout = false;

      if (!bNeedOnPerformLayout && m_bNeedAutoResizePerformLayout)
      {

         bNeedOnPerformLayout = true;

      }

      return bNeedOnPerformLayout;

   }


   bool interaction::perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_bLockGraphicalUpdate)
      {

         return false;

      }

      if (m_bLockSketchToDesign)
      {

         return false;

      }

      //if (!window())
      //{

      //   return false;

      //}

      if (!(m_ewindowflag & ::e_window_flag_window_created))
      {

         return false;

      }

      top_down_prefix();

      if (m_bNeedPerformLayout)
      {

         m_bNeedPerformLayout = false;

         try
         {

            on_perform_top_down_layout(pgraphics);

         }
         catch (...)
         {

         }

      }

      bool bNeedPerformLayoutHere = need_on_perform_layout(pgraphics);

      //_synchronous_lock synchronouslock(this->synchronization());

      auto children = synchronized_get_children();

      //if (m_puserinteractionpointeraChild)
      {

         for (auto & puserinteraction : children)
         {

            //synchronouslock.unlock();

            try
            {

               if (!puserinteraction)
               {

                  continue;

               }

               if (puserinteraction->perform_layout(pgraphics))
               {

                  bNeedPerformLayoutHere = true;

               }

            }
            catch (...)
            {

            }

            //synchronouslock.lock();

         }

      }

      bool bParentMayNeedToPerformLayout = m_bNeedLayout;

      if (bNeedPerformLayoutHere)
      {

         try
         {

            bParentMayNeedToPerformLayout = on_perform_layout(pgraphics);

         }
         catch (...)
         {

         }

         m_bNeedLayout = true;

      }

      return bParentMayNeedToPerformLayout;

   }


   void interaction::on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics)
   {

      ::string strType = ::type(this).name();

      if (strType == "RedDotLogicsInternal_license_manager::user_form")
      {

         information() << "RedDotLogicsInternal_license_manager::user_form";

      }
      else if (strType.contains("scroll_bar"))
      {

         information() << "on_perform_top_down_layout scroll_bar";

      }

      if (m_bExtendOnParent)
      {

         _extend_on_parent(pgraphics);

      }

      if (m_bExtendOnParentHostingArea)
      {

         _extend_on_parent_hosting_area(pgraphics);

      }

      if (m_bNeedFullRedrawOnResize)
      {

         auto rectangle = this->rectangle(e_layout_lading);

         set_need_redraw({ rectangle }, pgraphics);

      }

   }


   bool interaction::on_perform_layout(::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }

   void
      interaction::on_items_layout(::draw2d::graphics_pointer & pgraphics, ::collection::index iIdContainer, ::item_array * pitema)
   {

      if (::is_null(pitema))
      {

         return;

      }


      for (auto & pitem : *pitema)
      {

         auto puseritem = user_item(pitem);

         if (puseritem->m_euseritemflag & ::user::e_item_flag_rectangle_callback)
         {

            continue;

         }

         if (pitem && pitem->m_item.m_eelement != ::e_element_item)
         {

            puseritem->m_ppath.release();

            if (pitem->m_item.m_eelement != e_element_item)
            {

               auto rectangle = this->rectangle(pitem->m_item.m_eelement);

               puseritem->m_rectangle2 = rectangle;

            }

         }

      }

   }


   void interaction::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      auto rectangleX = this->rectangle();

      layout_tooltip();

      //if(m_pinteractiondraw2d)
      {

         m_pathFocusRect1.release();
         m_pathFocusRect2.release();
         m_pathFocusRect3.release();
         m_pathFocusRect4.release();

      }

      defer_setup_default_bottom_right_resize_user_item();

      defer_setup_default_client_area_user_item();

      //auto pitemClient = item(::item_t{ e_element_client });

      //if (pitemClient)
      //{

      //   auto puseritemClient = user_item(pitemClient);

      //   puseritemClient->m_rectangle = rectangleX;

      //}

      for (auto [iIndex, pitemcontainer] : m_itemcontainermap)
      {

         on_items_layout(pgraphics, iIndex, pitemcontainer->m_pitema);

      }


      //{

      //   auto pitem = get_user_item(::e_element_close_button);

      //   if (pitem)
      //   {

      //      //if (pitem->m_rectangle.is_null())
      //      {

      //         this->rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left() = pitem->m_rectangle.right() - 32;

      //         pitem->m_rectangle.bottom() = pitem->m_rectangle.top() + 32;

      //      }

      //   }

      //}

      //{

      //   auto pitem = get_user_item(::e_element_close_icon);

      //   if (pitem)
      //   {

      //      if (pitem->m_rectangle.is_null())
      //      {

      //         this->rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left() = pitem->m_rectangle.right() - 48;

      //         pitem->m_rectangle.bottom() = pitem->m_rectangle.top() + 48;

      //      }

      //   }

      //}

      //{

      //   auto pitem = get_user_item(::e_element_switch_button);

      //   if (pitem)
      //   {

      //      if (pitem->m_rectangle.is_null())
      //      {

      //         this->rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left() = pitem->m_rectangle.right() - 48;

      //         pitem->m_rectangle.top() = pitem->m_rectangle.bottom() - 48;

      //      }

      //   }

      //}

      if (is_root())
      {

         this->set_size(get_size());

      }

   }


   //   void interaction::_window_request_presentation_locked()
   //   {
   //
   //      windowing_window()->_window_request_presentation_locked();
   //
   //   }
   //
   //
   //   void interaction::_window_request_presentation_unlocked()
   //   {
   //
   //      windowing_window()->_window_request_presentation_unlocked();
   //
   //      window()->_on_visual_changed_unlocked();
   //
   //   }


   void interaction::_on_configure_notify_unlocked(const ::rectangle_i32 & rectangle)
   {

      //      if (m_bVisualChanged)
      //      {
      //
      //         on_visual_applied();
      //
      //         m_bVisualChanged = false;
      //
      //      }


      //auto pwindowpos = (WINDOWPOS *)lparam;

      ////::GetWindowRect(m_hwnd, &r);

      //auto pointLparam = lparam_as_point(lparam);

      //auto xPos = (int)(short)LOWORD(lparam);   // horizontal position 
      //auto yPos = (int)(short)HIWORD(lparam);   // vertical position 
      auto xPos = rectangle.left();
      auto yPos = rectangle.top();

      //::point_i32 p(r.left, r.top);

      ::point_i32 p(xPos, yPos);

      //m_pointWindow = p;

      //::SetWindowPos(m_hwnd, nullptr, xPos, yPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      layout().m_statea[::user::e_layout_sketch].m_point2 = p;
      layout().m_statea[::user::e_layout_lading].m_point2 = p;
      layout().m_statea[::user::e_layout_layout].m_point2 = p;
      layout().m_statea[::user::e_layout_design].m_point2 = p;
      layout().m_statea[::user::e_layout_output].m_point2 = p;
      layout().m_statea[::user::e_layout_window].m_point2 = p;
      layout().m_statea[::user::e_layout_normal].m_point2 = p;



   }


   void interaction::_on_reposition_notify_unlocked(const ::point_i32 & point)
   {

      //      if (m_bVisualChanged)
      //      {
      //
      //         on_visual_applied();
      //
      //         m_bVisualChanged = false;
      //
      //      }

   }


   //   void interaction::on_visual_applied()
   //   {
   //
   //      if (windowing_window())
   //      {
   //
   //         windowing_window()->on_visual_applied();
   //
   //      }
   //
   //   }


   void interaction::on_reposition()
   {

      m_bClipRectangle = false;

      layout_tooltip();

      auto strType = ::type(this).as_string();

      if (strType.case_insensitive_contains("scroll_bar"))
      {

         information() << "on_reposition scroll_bar";

      }

   }


   void interaction::on_show_window()
   {

      layout_tooltip();

      //      user_interaction_update_visibility_cache(_is_window_visible());

   }


   bool interaction::is_this_visible(enum_layout elayout)
   {

      //      if (!m_puserinteraction)
      //      {
      //
      //         return false;
      //
      //      }

      //      if (m_bOfflineRender)
      //      {
      //
      //         return true;
      //
      //      }

      if (!(m_ewindowflag & e_window_flag_is_window))
      {

         return false;

      }

      if (m_ewindowflag & e_window_flag_not_visible)
      {

         return false;

      }

      if (!const_layout().state(elayout).is_visible())
      {

         return false;

      }

      //      if(!this->m_bVisible)
      //      {
      //
      //         return false;
      //
      //      }

      return true;

      //      return window()->is_this_visible(elayout);

   }


   bool interaction::should_draw()
   {

      return true;

   }


   //   bool interaction::is_there_graphics_output_interest() const
   //   {
   //
   //      return window()->is_there_graphics_output_interest();
   //
   //   }


#undef INFO_LAYOUT_DISPLAY


   bool interaction::sketch_on_display()
   {

      return true;

   }


   void interaction::_on_show_window()
   {

      ::string strType = ::type(this).name();

      //      if (is_fps_interest_on_show())
      //      {
      //
      //         if (is_this_visible(::user::e_layout_layout))
      //         {
      //
      //            set_fps_interest();
      //
      //         }
      //         else
      //         {
      //
      //            clear_fps_interest();
      //
      //         }
      //
      //      }

      if (is_window_screen_visible(::user::e_layout_layout))
      {

         if (get_parent() == nullptr)
         {

            check_transparent_mouse_events();

         }

      }
      else
      {

         user_interaction_on_hide();

      }

      //      if (get_parent() == nullptr || is_top_level())
      //      {
      //
      //         window_show_change_visibility();
      //
      //      }

   }


   void interaction::on_drag_scroll_layout(::draw2d::graphics_pointer & pgraphics)
   {

      //if(m_bVerticalDragScroll)
      //{
      auto rectangleX = this->rectangle();
      m_pointBarDragScrollMax = m_sizeBarDragScroll - rectangleX.size();
      //}
      //if(m_bHorizontalDragScroll)
      //   {
      //      //auto rectangleX = this->rectangle();
      //      //m_iHorizontalDragScrollMax = m_iHorizontalDragSize - rectangleX.width();
      //
      //   }


   }


   //   void interaction::_window_show_change_visibility_locked()
   //   {
   //
   //      window()->_window_show_change_visibility_locked();
   //
   //   }
   //
   //
   //   void interaction::_window_show_change_visibility_unlocked()
   //   {
   //
   //      //::enum_display edisplayOutput = layout().output().display();
   //      ::enum_display edisplayOutput = layout().layout().display();
   //
   //      ::enum_display edisplayWindow = layout().window().display();
   //
   //      if (equivalence_sink(edisplayOutput) == e_display_normal)
   //      {
   //
   //         edisplayOutput = e_display_normal;
   //
   //      }
   //
   //      if (equivalence_sink(edisplayWindow) == e_display_normal)
   //      {
   //
   //         edisplayWindow = e_display_normal;
   //
   //      }
   //
   //      ::enum_display edisplayOutputForOsShowWindow = edisplayOutput;
   //
   //      ::enum_display edisplayWindowForOsShowWindow = edisplayWindow;
   //
   //      if (::is_docking_appearance(edisplayOutputForOsShowWindow))
   //      {
   //
   //         edisplayOutputForOsShowWindow = e_display_normal;
   //
   //      }
   //
   //      if (::is_docking_appearance(edisplayWindowForOsShowWindow))
   //      {
   //
   //         edisplayWindowForOsShowWindow = e_display_normal;
   //
   //      }
   //
   //#ifdef WINDOWS_DESKTOP
   //      if (
   ////((GetExStyle() & WS_EX_LAYERED) &&
   ////(::is_different(
   //// ::is_screen_visible(edisplayOutputForOsShowWindow),
   //// ::is_screen_visible(edisplayWindowForOsShowWindow))))
   ////||
   ////(!(GetExStyle() & WS_EX_LAYERED) &&
   //(edisplayOutputForOsShowWindow != edisplayWindowForOsShowWindow)
   ////)
   //)
   //#else
   //      if (edisplayOutputForOsShowWindow != edisplayWindowForOsShowWindow)
   //#endif
   //      {
   //
   //         if (::is_set(window()))
   //         {
   //
   //            //auto eactivation = layout().output().activation();
   //
   //            auto eactivation = layout().layout().activation();
   //
   //            window()->_window_show_change_visibility_unlocked(edisplayOutputForOsShowWindow, eactivation);
   //
   //         }
   //
   //      }
   //
   //      //      if (edisplayOutput == e_display_iconic)
   //      //      {
   //      //
   //      //         //#ifdef WINDOWS_DESKTOP
   //      //         //
   //      //         //         if (GetExStyle() & WS_EX_LAYERED)
   //      //         //         {
   //      //         //
   //      //         //            layout().window() = edisplayOutput;
   //      //         //
   //      //         //         }
   //      //         //
   //      //         //#endif
   //      //         //
   //      //         informationf("blocking setting window state to iconic (1)");
   //      //
   //      //      }
   //      //      else
   //      //      {
   //
   //      layout().window() = edisplayOutput;
   //
   //      //      }
   //      //
   //   }


   void interaction::defer_save_window_placement()
   {


   }


   //void interaction::ShowOwnedPopups(bool bShow)
   //{
   //   if (window() == nullptr)
   //      return;
   //   else
   //   {
   //      window()->ShowOwnedPopups(bShow);

   //   }
   //}


   void * interaction::get_os_data()
   {

      return window()->get_os_data();

   }


   //void interaction::clear_cache(bool bRecursive) const
   //{
   //
   //   zero(m_cache);

   //   if (bRecursive)
   //   {

   //      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

   //      if (puserinteractionpointeraChild)
   //      {

   //         for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
   //         {

   //            pinteraction->clear_cache(true);

   //         }

   //      }

   //   }
   //
   //}



   //bool interaction::attach(::windowing::window * pwindow_New)
   //{
   //   if (window() == nullptr)
   //      return false;
   //   else
   //      return window()->attach(oswindow_New);

   //}


   oswindow interaction::detach_window()
   {

      //auto pwindowThis = window();

      //if (!pwindow)
      //{

      //   return nullptr;

      //}

      auto oswindow = window()->detach_window();

      if (!oswindow)
      {

         return nullptr;

      }

      return oswindow;

   }


   /* ::windowing::window * interaction::_window() const
       {

          auto puserinteraction = get_wnd();

          if (!puserinteraction)
          {

             return nullptr;

          }

          auto pwindow = puserinteraction->windowing_window();

          if (!pwindow)
          {

             return nullptr;

          }

          return pwindow->get_window();

       }*/


   void interaction::pre_subclass_window()
   {
      //if (window() == nullptr)
      //   return;
      //else
      //   window()->pre_subclass_window();
   }


   void interaction::_001Emphasize(int cx, int cy)
   {

      ::rectangle_i32 rectangleMainMonitor;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      pdisplay->get_main_monitor(rectangleMainMonitor);

      int x = (rectangleMainMonitor.width() - cx) / 2;

      int y = (rectangleMainMonitor.height() - cy) / 3;

      order(e_zorder_top);

      layout().sketch().set_visual_state_origin({ x, y });
      layout().sketch().m_size = { cx, cy };

      display(e_display_normal);

   }


   //atom interaction::run_modal_loop(::user::interaction * pinteraction, u32 dwFlags)
   //{

   //   return pinteraction->_001RunModalLoop(dwFlags);

   //}


   //atom interaction::RunModalLoop(u32 dwFlags)
   //{

   //   set_need_redraw();

   //   post_redraw();

   //   return _001RunModalLoop(dwFlags);

   //}


   //atom interaction::_001RunModalLoop(u32 dwFlags)
   //{

   //   ASSERT(!m_bModal);

   //   if (m_bModal)
   //   {

   //      return ::atom();

   //   }

   //   KEEP(m_bModal);

   //   __keep_current_thread(m_ptaskModal);

   //   while (true)
   //   {

   //      if (!ContinueModal())
   //      {

   //         break;

   //      }


   //      if (::is_null(get_task()))
   //      {

   //         break;

   //      }

   //      if (!get_thread()->pump_message())
   //      {

   //         break;

   //      }

   //   }

   //   //psystem->post_to_all_threads(e_message_kick_idle, 0, 0);

   //   return m_atomModalResult;

   //}


   //bool interaction::ContinueModal()
   //{

   //   bool bRun = ::task_get_run();

   //   return m_bModal && bRun;

   //}


   //void interaction::EndModalLoop(atom idResult)
   //{

   //   informationf("EndModalLoop");

   //   ASSERT(is_window());

   //   // this result will be returned from interaction_impl::RunModalLoop
   //   m_atomModalResult = idResult;

   //   // make sure a message goes through to exit the modal loop
   //   m_bModal = false;

   //   //if (::sequence<::conversation>::m_p)
   //   {

   //      m_payloadResult = idResult;

   //      m_estatus = ::success;

   //   }

   //   post_message(MESSAGE_CLOSE);

   //   if (::is_set(m_ptaskModal))
   //   {

   //      m_ptaskModal->kick_thread();

   //   }

   //   auto puserthread = user_thread();

   //   if (get_wnd() != nullptr && ::is_set(puserthread))
   //   {

   //      puserthread->kick_thread();

   //   }

   //}


   lresult interaction::message_handler(const ::atom & atom, wparam wparam, lparam lparam)
   {

      // if (::is_null(m_puserinteraction))
      // {

      //    throw ::exception(error_wrong_state);

      // }

      // this->interaction_post(__allocate call_message_handler_task(m_puserinteraction, atom, wparam, lparam));

      //auto pmessage

      //get_message()

      ::pointer<::message::message>pmessage;

      pmessage = get_message(atom, wparam, lparam);

      pmessage->m_pchannel = this;

      //return message_call(pmessage);

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void interaction::post_message(const ::atom & atom, wparam wparam, lparam lparam)
   {

      if (::is_null(window()))
      {

         throw ::exception(error_wrong_state);

      }

      auto a = atom;

      _post([this, a, wparam, lparam]()
         {

            message_call(a, wparam, lparam);

            });
      //return window()->post_message(atom, wparam, lparam);

   }


   void interaction::post_object(const ::atom & atom, wparam wparam, lparam lparam)
   {

      //bool bIsWindow = ::is_set(window()) && is_window();

      //if (atom == e_message_quit || !bIsWindow)
      {

         {

            // discards object
            ::pointer<::particle> pparticle(lparam);


         }

         /*        if (!bIsWindow)
                 {

                    return;

                 }*/

                 //return window()->post_message(atom);

      }

      //return window()->post_message(atom, wparam, lparam);


   }


   //bool interaction::user_post(const ::atom& atom, wparam wparam, lparam lparam)
   //{
   //
   //   return user_thread()->post_message(atom, wparam, lparam);
   //
   //}



   void interaction::call_and_set_timer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer)
   {

      if (has_flag(e_flag_destroying))
      {

         return;

      }

      ::timer timer(uEvent);

      _001OnTimer(&timer);

      return SetTimer(uEvent, timeElapse, pfnTimer);

   }


   void interaction::set_timer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer, bool bPeriodic,
                               void * pdata)
   {

      if (has_destroying_flag())
      {

         return;

      }

      return SetTimer(uEvent, timeElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::SetTimer(uptr uEvent, const class time & timeElapse, PFN_TIMER pfnTimer, bool bPeriodic,
                              void * pdata)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      if (has_destroying_flag())
      {

         return;

      }

      //return window()->SetTimer(uEvent, timeElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::KillTimer(uptr uEvent)
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //window()->KillTimer(uEvent);

   }


   bool interaction::has_keyboard_focus()
   {

      if (!is_window())
      {

         return false;

      }

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         information() << "has_keyboard_focus No Window";

         return false;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   information() << "has_keyboard_focus No Primitive Impl";

      //   return false;

      //}

      if (!pwindowThis->has_keyboard_focus())
      {

         if (pwindowThis->m_puserinteraction->m_puserinteractionOwner)
         {

            auto pwindowOwner = pwindowThis->m_puserinteraction->m_puserinteractionOwner->window();

            if (::is_null(pwindowOwner))
            {

               information() << "has_keyboard_focus No Owner Window";

               return false;

            }

            //auto pwindowOwner = pwindowOwner->m_pwindow;

            //if (::is_null(pwindowOwner))
            //{

            //   information() << "has_keyboard_focus No Owner Primitive Impl";

            //   return false;

            //}

            if (pwindowOwner->has_keyboard_focus())
            {

               //::string strType;

               //strType = ::type(pwindowOwner->m_pwindow->m_puserinteraction.m_p);

               //information() << "pwindowOwner->has_keyboard_focus() : " << strType;

               //::string strTypeOldFocus;

               //strTypeOldFocus = ::type(pwindowOwner->m_pwindow->m_puserinteraction.m_p);

               //information() << "old focus : " << strTypeOldFocus;

               if (pwindowOwner->m_puserinteractionKeyboardFocus == this)
               {

                  return true;

               }
               else
               {

                  return false;

               }

            }

         }


         return false;

      }

      //if (::is_null(pwindow))
      //{

      //   return false;

      //}

      if (pwindowThis->m_puserinteractionKeyboardFocus != this)
      {

         return false;

      }

      return true;

   }


   bool interaction::should_show_keyboard_focus()
   {

      return has_keyboard_focus();

   }


   void interaction::set_keyboard_focus()
   {

      information() << "set_keyboard_focus";

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         information() << "set_keyboard_focus No Window";

         return;

      }

      if (pwindowThis->has_keyboard_focus())
      {

         information() << "pwindowThis->has_keyboard_focus()";

         if (pwindowThis->m_puserinteractionToKillKeyboardFocus == this)
         {

            pwindowThis->m_puserinteractionToKillKeyboardFocus.release();

         }

         pwindowThis->m_puserinteractionKeyboardFocusRequest = this;

         pwindowThis->on_final_set_keyboard_focus();

         return;

      }
      else
      {

         if (pwindowThis->m_puserinteraction->m_puserinteractionOwner)
         {

            auto pwindowOwner = pwindowThis->m_puserinteraction->m_puserinteractionOwner->window();

            if (::is_null(pwindowOwner))
            {

               return;

            }

            //auto pwindowOwner = pwindowOwner->m_pwindow;

            //if (::is_null(pwindowOwner))
            //{

            //   return;

            //}

            if (pwindowOwner->has_keyboard_focus())
            {

               ::string strType;

               strType = ::type(pwindowOwner->m_puserinteraction.m_p);

               information() << "pwindowOwner->has_keyboard_focus() : " << strType;

               ::string strTypeOldFocus;

               strTypeOldFocus = ::type(pwindowOwner->m_puserinteraction.m_p);

               information() << "old focus : " << strTypeOldFocus;

               pwindowOwner->m_puserinteractionKeyboardFocusRequest = this;

               pwindowOwner->on_final_set_keyboard_focus();

               return;

            }

         }

      }

      pwindowThis->m_puserinteractionKeyboardFocusRequest = this;

      pwindowThis->set_keyboard_focus();

   }


   bool interaction::has_mouse_capture()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return false;

      }

      auto pwindow = pwindowing->get_mouse_capture(user_thread());

      if (::is_null(pwindow))
      {

         return false;

      }

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return false;

      }

      if (*pwindowThis != *pwindow)
      {

         return false;

      }

      /*auto pwindow = pwindow->m_pwindow;

      if (::is_null(pwindow))
      {

         return false;

      }*/

      if (pwindow->m_puserinteractionMouseCapture != this)
      {

         return false;

      }

      return true;

   }


   void interaction::set_foreground_window()
   {

      auto phost = get_host_user_interaction();

      if (!phost)
      {

         //return error_failed;

         return;

      }

      auto pwindow = phost->windowing_window();

      if (!pwindow)
      {

         //return error_failed;

         return;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (!pwindow)
      //{

      //   //return error_failed;

      //   return;

      //}

      return pwindow->set_foreground_window();

   }


   void interaction::set_active_window()
   {

      auto phost = get_host_user_interaction();

      if (!phost)
      {

         //return error_failed;

         return;

      }

      auto pwindow = phost->windowing_window();

      if (!pwindow)
      {

         //return error_failed;

         return;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (!pwindow)
      //{

      //   //return error_failed;

      //   return;

      //}

      return pwindow->set_active_window();

   }


   void interaction::bring_to_front()
   {

      window()->bring_to_front();

   }


   bool interaction::is_active_window()
   {

      //      auto psession = get_session();
      //
      //      if (::is_null(psession))
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      auto puser = psession->user();
      //
      //      if (!puser)
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      auto pwindowing = puser->windowing();
      //
      //      if (::is_null(pwindowing))
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      auto pwindow = pwindowing->get_active_window(user_thread());
      //
      //      if (::is_null(pwindow))
      //      {
      //
      //         return false;
      //
      //      }

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return false;

      }

      //      if (*pwindow != *pwindow)
      //      {
      //
      //         return false;
      //
      //      }

      if (!pwindowThis->is_active_window())
      {

         return false;

      }

      return true;

   }




   //::user::interaction * interaction::get_capture()
   //{

   //   if (window() != nullptr)
   //   {

   //      return window()->get_capture();

   //   }

   //   ::user::interaction * puserinteraction = get_wnd();

   //   if (puserinteraction != nullptr)
   //   {

   //      return puserinteraction->get_capture();

   //   }

   //   return nullptr;

   //}


   //bool interaction::ReleaseCapture()
   //{

   //   if (window() == nullptr)
   //   {

   //      return false;

   //   }

   //   return window()->ReleaseCapture();

   //}


   void interaction::track_mouse_leave()
   {

      track_mouse_hover();

   }


   void interaction::track_mouse_hover()
   {
#ifdef MORE_LOG
      information() << "interaction::track_mouse_hover";
#endif

      //      _synchronous_lock synchronouslock(this->synchronization());

      //if (m_bTrackMouseLeave)
      //{

      //   return;

      //}

      auto pwnd = get_wnd();

      if (::is_null(pwnd))
      {

         return;

      }

      pwnd->mouse_hover_add(this);

      //m_bTrackMouseLeave = true;

   }


   //void interaction::defer_restore(const ::rectangle_i32& rectangleRequest)
   //{

   //   ::rectangle_i32 rectangleWorkspace;

   //   auto pwindowing = windowing();

   //   auto pdisplay = pwindowing->display();

   //   index iBestWorkspace = pdisplay->get_best_monitor(&rectangleWorkspace, rectangleRequest);

   //   bool bWindowCrossesWorkspaceBoundaries = !rectangleWorkspace.contains(rectangleRequest);

   //   bool bWindowLargerThanBroadRestore = rectangleRequest.width() > m_sizeRestoreBroad.cx()
   //      || rectangleRequest.height() > m_sizeRestoreBroad.cy();

   //   if (bWindowCrossesWorkspaceBoundaries || bWindowLargerThanBroadRestore)
   //   {

   //      design_window_normal(e_display_restore);

   //   }
   //   else
   //   {

   //      //place(rectangle_i32_dimension(10, 10, 800, 300));

   //      ::rectangle_i32 rectanglePlace(rectangleRequest);

   //      if (rectanglePlace.size().any_lt(get_window_minimum_size()))
   //      {

   //         rectanglePlace.set_size(get_window_minimum_size());

   //      }

   //      place(rectanglePlace);

   //      display(e_display_normal);

   //   }

   //}


   int interaction::get_derived_height(int iWidth)
   {

      return -1;

   }


   int interaction::get_derived_width(int iHeight)
   {

      return -1;

   }


   void interaction::sketch_to_lading()
   {

      if (::type(this) == "user::list_box")
      {

         information() << "interaction::sketch_to_lading";

      }

      _synchronous_lock synchronouslock(this->synchronization());

      //      if (get_parent() == nullptr)
      //      {
      //
      //         if (layout().sketch().m_size.area() > 0)
      //         {
      //
      //            auto & sizeSketch = layout().sketch().m_size;
      //
      //            auto & sizeWindow = layout().window().m_size;
      //
      //            if (sizeSketch != sizeWindow
      //                && !(m_bIgnoringSketchToLading && m_timeLastIgnoredSketchToLading.elapsed() < 200_ms))
      //            {
      //
      //               if (!m_bIgnoringSketchToLading)
      //               {
      //
      //                  m_timeLastIgnoredSketchToLading.Now();
      //
      //                  m_bIgnoringSketchToLading = true;
      //
      //                  synchronouslock.unlock();
      //
      //                  post_redraw();
      //
      //               }
      //               else
      //               {
      //
      //                  synchronouslock.unlock();
      //
      //               }
      //
      //
      //               //information() << "ignoring sketch with size : " << layout().sketch().m_size;
      //
      //
      //               //                  if(m_ptask)
      //               //
      //               //                  m_ptaskRecheckIgnoredSketchToLading =
      //               //                  fork([this]()
      //               //                  {
      //               //
      //               //                     prempt(16.67_ms);
      //               //
      //               //                     post_redraw();
      //               //
      //               //                  });
      //
      //               return;
      //
      //            }
      //
      //         }
      //
      //         m_bIgnoringSketchToLading = false;
      //
      //      }


      //      if (get_parent() == nullptr)
      //      {
      //
      //         if (layout().lading().m_size.area() > 0)
      //         {
      //
      //            auto & sizeLading = layout().lading().m_size;
      //
      //            auto & sizeWindow = layout().window().m_size;
      //
      //            if (sizeLading != sizeWindow
      //            && !(m_bIgnoringSketchToLading && m_timeLastIgnoredSketchToLading.elapsed() < 200_ms))
      //            {
      //
      //               if (!m_bIgnoringSketchToLading)
      //               {
      //
      //                  m_timeLastIgnoredSketchToLading.Now();
      //
      //                  m_bIgnoringSketchToLading = true;
      //
      //               }
      //
      //               synchronouslock.unlock();
      //
      //               //information() << "ignoring sketch with size : " << layout().sketch().m_size;
      //
      //               post_redraw();
      //
      //               //                  if(m_ptask)
      //               //
      //               //                  m_ptaskRecheckIgnoredSketchToLading =
      //               //                  fork([this]()
      //               //                  {
      //               //
      //               //                     prempt(16.67_ms);
      //               //
      //               //                     post_redraw();
      //               //
      //               //                  });
      //
      //               return;
      //
      //            }
      //
      //         }
      //
      //         m_bIgnoringSketchToLading = false;
      //
      //      }

      layout().lading() = layout().sketch();

      layout().sketch().reset_pending();

      //layout().sketch().m_eactivation = e_activation_default;
      //layout().sketch().m_bImpactUpdateGoingOn = false;

      if (get_parent() == nullptr)
      {

         auto p = __get_top_right();

         if (p.is_set())
         {

            auto r = layout().lading().parent_raw_rectangle();

            auto Δ = r.top_right() - p;

            if (Δ.cx() != 0 || Δ.cy() != 0)
            {

               //information() << "sketch_to_lading top right offset not null " << Δ;

            }

         }

      }

      //scroll_x_sketch_to_lading();

      //scroll_y_sketch_to_lading();

   }


   //static i64 g_i_graphics_thread_update_visual = 0;

   //void interaction::scroll_x_sketch_to_lading()
   //{

   //}


   //void interaction::scroll_x_lading_to_layout()
   //{

   //}


   //void interaction::scroll_y_sketch_to_lading()
   //{

   //}


   //void interaction::scroll_y_lading_to_layout()
   //{

   //}


   void interaction::lading_to_layout(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      bUpdateBuffer = false;

      bUpdateWindow = false;

      //string strType = ::type(this).name();

      //if (strType.contains("app_veriwell_keyboard") && strType.contains("main_frame"))
      //{

      //   //informationf("app_veriwell_keyboard::main_frame");

      //}
      ////      else if (strType.contains("main_frame"))
      ////      {
      ////
      ////         informationf("main_frame");
      ////
      ////      }
      ////      else if (strType.contains("place_holder"))
      ////      {
      ////
      ////         informationf("place_holder");
      ////
      ////      }
      ////   else if (strType.contains("combo_box"))
      ////   {
      ////
      ////      informationf("combo_box");
      ////
      ////   }
      ////   else if (strType.contains("list_box"))
      ////   {
      ////
      ////      informationf("list_box");
      ////
      ////   }

      KEEP(m_bUpdatingVisual);

      bool bDisplay = display_lading_to_layout();

      //      if (windowing_window() && windowing_window()->m_bOfflineRender)
      //      {
      //
      //         if (layout().lading().display() != e_display_hide)
      //         {
      //
      //            hide();
      //
      //         }
      //
      //      }

      if (!is_equivalent(layout().lading().display(), layout().layout().display()))
      {

         layout().m_timeLastLadingToLayout.Now();

      }

      bool bAppearance = layout().lading().appearance() != layout().layout().appearance();

      ::point_i32 pointLading = layout().lading().origin();

      ::point_i32 pointLayout = layout().layout().origin();

      bool bPosition = pointLading != pointLayout || m_bReposition;

      m_bReposition = false;

      ::size_i32 & sizeLading = layout().lading().size();

      ::size_i32 & sizeLayout = layout().layout().size();

      if (m_bDerivedHeight)
      {

         int iDerivedWidth = sizeLading.cx();

         int iDerivedHeight = get_derived_height(iDerivedWidth);

         ::size_i32 sizeMinimum = get_window_minimum_size();

         if (iDerivedHeight > 0)
         {

            if (iDerivedHeight < sizeMinimum.cy())
            {

               iDerivedHeight = sizeMinimum.cy();

               iDerivedWidth = get_derived_width(iDerivedHeight);

            }

         }

         if (iDerivedWidth >= sizeMinimum.cx() && iDerivedHeight >= sizeMinimum.cy())
         {

            sizeLading.cx() = iDerivedWidth;

            sizeLading.cy() = iDerivedHeight;

            layout().lading().size() = sizeLading;

         }

      }

      //bool bSize = sizeLading != sizeLayout || m_bNeedLayout;

      bool bSize = sizeLading != sizeLayout;

      ::string strType = typeid(*this).name();

      if (strType.contains("control_box_button"))
      {

         //information() << "should_perform_layout control_box_button";

      }

      //if (::is_screen_visible(layout().layout().display()))
      //{

      //   m_bNeedLayout = false;

      //}

      if (bSize)
      {

         layout().layout().copy_size(layout().lading());

      }

      if (bPosition)
      {

         layout().layout().copy_position(layout().lading());

         //if (::is_set(get_parent()))
         //{

         //   set_need_redraw({layout().layout().raw_rectangle() });

         //}

      }

      if (bDisplay)
      {

         layout().layout().copy_display(layout().lading());

      }

      //if (bDisplay)
      //{

      //   layout().layout().copy_display(layout().lading());

      //}

      bool bZorder = false;

      if (is_top_level())
      {

         if (layout().lading().zorder().is_change_request())
         {

            layout().layout() = layout().lading().zorder();

            bZorder = true;

         }

      }

      bool bActivation = layout().lading().m_eactivation != ::e_activation_default;

      layout().layout() = layout().lading().appearance();

      if (bActivation)
      {

         layout().layout().m_eactivation = layout().lading().m_eactivation;

      }

      if (layout().lading().m_bImpactUpdateGoingOn)
      {

         layout().layout().m_bImpactUpdateGoingOn = true;

      }

      layout().lading().reset_pending();

      if (m_bAutomaticallyStoreWindowRectangle)
      {

         if (bDisplay || bAppearance)
         {

            // bPosition and bLading wouldn't set this flag,
            // as it can trigger too many calls to save_window_rect.
            // moving and sizing changes are handled at
            // on_end_layout_experience
            // only changes to display and appearance
            // will set e_window_flag_loading_window_rect here
            // (because they are "rare" and it seems
            // good location to manage the machine*)
            // (*instead of flagging e_window_flag_loading_window_rect
            // at every location display or appearance is changed)
            // (so while this is still applicable)

            if (m_bLoadingWindowRectangle)
            {

               informationf(
                       "window visual changed: not setting pending save rectangle_i32 cause loading window rectangle_i32");

            }
            else
            {

               m_bPendingSaveWindowRectangle = true;

            }

         }

      }

      bool bChildrenZorder = check_children_zorder();

      auto bUpdateVisual = bDisplay || bZorder || bChildrenZorder || bSize || bActivation || m_bNeedLayout;

      if (!bUpdateBuffer && ::is_set(get_parent()))
      {

         bUpdateBuffer = bPosition;

      }

      //if (!bUpdateBuffer && windowing_window())
      //{

      //   bUpdateBuffer = windowing_window()->m_redrawa.has_element();

      //}

      //information() << "bLading=" << (bLading?"true":"false");

      bUpdateWindow = bDisplay || bZorder || bPosition;

      bool bDeferDisplay =
         bUpdateVisual
         || bPosition
         || !is_equivalent(layout().lading().display(), layout().layout().display());

      if (bDeferDisplay)
      {

         on_defer_display();

      }

      if (bUpdateVisual)
      {

         if (bAppearance)
         {

            layout_appearance();

         }

         //         if (bZorder)
         //         {
         //
         //            //design_zorder();
         //            m_bPendingZorder = true;
         //
         //         }
         //
         if (bSize || m_bNeedLayout)
         {

            //::pointer<::windowing::window>pwindow = window();

            //if (pwindow)
            //{

            //   pwindow->m_re;

            //}

            m_bLadingToLayout = true;

            //design_layout(pgraphics);

         }

         if (layout().layout().m_bImpactUpdateGoingOn)
         {

            if (!m_bLadingToLayout)
            {

               m_bLadingToLayout = true;

            }

         }

         if (bDisplay)
         {

            //information(as_string(++g_i_graphics_thread_update_visual) + "updvis dpy machine\n");

         }

      }

      if (bSize)
      {

         m_bNeedPerformLayout = true;

      }

      if (get_parent() != nullptr)
      {

         if (bDeferDisplay || bPosition)
         {

            if (!(m_ewindowflag & e_window_flag_embedded_graphics_thread_if_child))
            {

               if (!(m_ewindowflag & e_window_flag_postpone_visual_update))
               {

                  //if (window())
                  //{

                  //   //window()->_window_request_presentation_locked();

                  //}

               }

            }

         }

      }

      if (bPosition)
      {

         layout_reposition();

      }

      if (bDisplay)
      {

         _001OnAfterExitAppearance();

         _001OnAfterEnterAppearance();

      }

      if (get_parent() != nullptr)
      {

         if (!layout().layout().is_screen_visible())
         {

            if (m_ewindowflag & e_window_flag_on_show_window_visible
                || m_ewindowflag & e_window_flag_on_show_window_screen_visible)
            {

               m_ewindowflag -= e_window_flag_on_show_window_visible;

               m_ewindowflag -= e_window_flag_on_show_window_screen_visible;

               _on_show_window();

            }

         }
         else
         {

            if (!(m_ewindowflag & e_window_flag_on_show_window_visible)
                && !(m_ewindowflag & e_window_flag_on_show_window_screen_visible))
            {

               m_ewindowflag += e_window_flag_on_show_window_visible;

               m_ewindowflag += e_window_flag_on_show_window_screen_visible;

               _on_show_window();

            }

         }

      }

      //      if (m_bUpdateVisual || m_bReposition)
      //      {
      //
      //         if (!(m_ewindowflag & e_window_flag_postpone_visual_update))
      //         {
      //
      //            if (m_ewindowflag & e_window_flag_embedded_graphics_thread)
      //            {
      //
      //               auto psession = get_session();
      //
      //               if (get_parent() == nullptr || get_parent() == psession->get_user_interaction_host())
      //               {
      //
      //                  if (windowing_window())
      //                  {
      //
      //                     windowing_window()->_window_show();
      //
      //                  }
      //
      //               }
      //               else
      //               {
      //
      //                  if (window())
      //                  {
      //
      //                     window()->start_window_visual();
      //
      //                  }
      //
      //               }
      //
      //            }
      //
      //         }
      //
      //      }

            //::string strType = type(this).name();

      //if (strType.contains("pane_impact"))
      //{

      //   information() << "top_down_prefix " << strType;

      //}

      //bool bZorder = check_child_zorder();

      if (bChildrenZorder)
      {

         layout_children_zorder();

      }

      m_bNeedLayout = false;

      //scroll_x_lading_to_layout();

      //scroll_y_lading_to_layout();

   }


   void interaction::layout_to_design()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (!layout().design().visual_state::operator==(layout().layout()))
      {

         layout().design().visual_state::operator=(layout().layout());

         m_bClipRectangle = false;

      }

      if (!layout().design().m_zorder.is_change_request() || layout().layout().m_zorder.is_change_request())
      {

         layout().design().m_zorder = layout().layout().m_zorder;

      }

      if (layout().design().m_eactivation == e_activation_default || layout().layout().m_eactivation != e_activation_default)
      {

         layout().design().m_eactivation = layout().layout().m_eactivation;

      }

      auto & eactivation = layout().design().m_eactivation;

      layout().layout().reset_pending();

      if (get_parent() == nullptr)
      {

         auto p = __get_top_right();

         if (p.is_set())
         {

            auto r = layout().design().parent_raw_rectangle();

            auto Δ = r.top_right() - p;

            if (Δ.cx() != 0 || Δ.cy() != 0)
            {

               information() << "interaction::layout_to_design top right offset not null " << Δ;

            }

         }

      }

      //information() << "layout().design().m_edisplay : " << layout().design().m_edisplay;

   }


   void interaction::_001UpdateWindow()
   {

      //if (window() == nullptr)
      //{

      //   return;

      //}

      //_001UpdateWindow();

      on_after_graphical_update();

   }


   void interaction::add_appearance(::e_appearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance += eappearance;

   }


   void interaction::erase_appearance(::e_appearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance -= eappearance;

   }


   void interaction::toggle_appearance(::e_appearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance.toggle(eappearance);

      if (eappearance == e_appearance_transparent_frame)
      {

         if (m_layout.m_statea[elayout].m_eappearance & e_appearance_transparent_frame)
         {

            auto ptopic = create_topic(id_on_set_transparent_frame);

            route(ptopic);

         }
         else
         {

            auto ptopic = create_topic(id_on_clear_transparent_frame);

            route(ptopic);

         }

      }

   }

   // void interaction::window_apply_visual(const struct layout_state & windowstate)
   // {

   //    window()->window_apply_visual(windowstate);

   // }


   //void interaction::GuieProc(::message::message * pmessage)
   //{
   //
   //   __UNREFERENCED_PARAMETER(pmessage);
   //
   //}


   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      //if (window() != nullptr)
      //{

      //   //         window()->_001DeferPaintLayeredWindowBackground(pgraphics);

      //}

   }


   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      _001DeferPaintLayeredWindowBackground(pgraphics);

   }


   ::oswindow interaction::oswindow()
   {

      auto pwindowThis = window();

      if (!pwindowThis)
      {

         return nullptr;

      }

      auto oswindow = pwindowThis->oswindow();

      if (!oswindow)
      {

         return nullptr;

      }

      return oswindow;

   }


   //::oswindow interaction::_oswindow() const
   //{

   //   return oswindow();

   //}


   void interaction::OnLinkClick(const ::string & psz, const ::string & pszTarget)
   {

      auto phyperlink = __create_new<::hyperlink>();

      phyperlink->m_strLink = psz;

      phyperlink->m_strTarget = pszTarget;

      phyperlink->run();

      //hyperlink.open_link(psz, "", pszTarget);

   }


   bool interaction::on_set_parent(::user::interaction_base * puserprimitiveParent)
   {

      ::pointer<::user::interaction> puserinteractionParent = puserprimitiveParent;

      if (m_puserinteractionParent == puserinteractionParent)
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction::on_set_parent (xxxx1)";
         information() << "";
         information() << "";
         return false;

      }

      if (::is_set(puserinteractionParent) && puserinteractionParent->is_descendant_of(this, true))
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction::on_set_parent (xxxx2)";
         information() << "";
         information() << "";

         return false;

      }

      ::pointer<::user::interaction> puiThis = this;

      //_synchronous_lock slChildren(::user::pointer < ::mutex >_children());

      try
      {

         if (m_puserinteractionParent != nullptr
             && m_puserinteractionParent != puserinteractionParent)
         {

            information() << "-------------------------------------------------------------------";
            information() << "";
            information() << "";
            information() << "interaction::on_set_parent (erase)";
            information() << "";
            information() << "";


            _synchronous_lock synchronouslock(m_puserinteractionParent->window()->m_pparticleChildrenSynchronization);
            //auto puiptraChildNew = __allocate(
//                    ::user::interaction_array(*m_puserinteractionParent->m_puserinteractionpointeraChild));
            m_puserinteractionParent->m_puserinteractionpointeraChild->erase_interaction(this);
            //m_puserinteractionParent->m_puserinteractionpointeraChild = puiptraChildNew;

         }

      }
      catch (...)
      {
      }

      m_puserinteractionParent = puserinteractionParent;

      m_pacmeuserinteractionParent = puserinteractionParent;

      try
      {

         if (::is_set(puserinteractionParent))
         {

            auto puserthreadParent = puserinteractionParent->user_thread();

            if (user_thread() != puserthreadParent)
            {

               if (user_thread())
               {

                  if (::is_set(user_thread()->m_puserinteractionbaseaThread))
                  {

                     user_thread()->m_puserinteractionbaseaThread->erase(this);

                  }

                  //user_thread().release();

               }

               //user_thread() = puserinteractionParent->get_wnd()->user_thread();

            }

            puserinteractionParent->on_add_child(this);

         }

      }
      catch (...)
      {

         information() << "-------------------------------------------------------------------";
         information() << "";
         information() << "";
         information() << "interaction::on_set_parent (xxxxxx3)";
         information() << "";
         information() << "";

      }

      return true;

   }


   bool interaction::on_add_child(::user::interaction * puserinteractionChild)
   {

      //information() << "interaction::on_add_child start\n";
      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      puserinteractionChild->m_pinteractionScaler = m_pinteractionScaler;

      // ::pointer<::user::interaction_array> puserinteractionpointeraChildNew;

      // if (::is_set(m_puserinteractionpointeraChild))
      // {

      //    puserinteractionpointeraChildNew = __allocate ::user::interaction_array(*m_puserinteractionpointeraChild);

      // }
      // else
      // {

      __defer_construct_new(m_puserinteractionpointeraChild);

      // }

      m_puserinteractionpointeraChild->add_unique_interaction(puserinteractionChild);

      //m_puserinteractionpointeraChild = puserinteractionpointeraChildNew;

      return true;

   }


   void interaction::on_after_set_parent()
   {

#ifdef REPORT_OFFSET

      printf("interaction::on_after_set_parent(1) m_pwindow (0x%x)\n", m_pwindow);

      fflush(stdout);

#endif

      //m_puserinteractionTopLevel = _top_level();

      //m_puserframeParent = _parent_frame();

      //m_puserframeTopLevel = _top_level_frame();

      //m_pwindow = _window();

#ifdef REPORT_OFFSET

      printf("interaction::on_after_set_parent(2) m_pwindow (0x%x)\n", m_pwindow);

      fflush(stdout);

#endif

      //m_oswindow = m_pwindow->oswindow();

   }


   bool interaction::on_set_owner(::user::interaction_base * pprimitive)
   {

      return true;

   }


   void interaction::route_as_parent_mouse_message(::message::mouse * pmouse)
   {

      auto emessage = pmouse->m_atom.m_emessage;

      at_end_of_scope
      {

         pmouse->m_atom = emessage;

      };

      ::make_parent_mouse_message(pmouse->m_atom.m_emessage);

      route_message(pmouse);

   }


   void interaction::user_mouse_initialize_cursor(::user::mouse * pmouse, ::windowing::cursor * pcursor)
   {

      pmouse->m_pwindowingcursor = pcursor;

      //information() << "user_mouse_initialize_cursor : " << pcursor->m_ecursor;

   }


   void interaction::user_mouse_set_cursor(::user::mouse * pmouse, ::windowing::cursor * pcursor)
   {

      pmouse->m_pwindowingcursor = pcursor;

      //information() << "user_mouse_set_cursor : " << pcursor->m_ecursor;

   }


   ::windowing::cursor * interaction::user_mouse_get_cursor(::user::mouse * pmouse)
   {

      return pmouse->m_pwindowingcursor;

   }


   bool interaction::on_mouse_message(::message::mouse * pmouse)
   {

      if (pmouse->m_atom == e_message_left_button_down)
      {

         informationf("on_mouse_message e_message_left_button_down");

      }

      user_mouse_initialize_cursor(pmouse, m_pcursorDefault);

      ::user::interaction * pchild = this;

      if (pmouse->m_atom.m_emessage < e_message_mouse_first
         || pmouse->m_atom.m_emessage > e_message_mouse_last)
      {

         pchild = child_from_point(pmouse->m_pointHost);

      }
      else
      {

         auto puserinteraction = this;

         while (puserinteraction)
         {

            puserinteraction->route_as_parent_mouse_message(pmouse);

            if (pmouse->m_bRet)
            {

               return true;

            }

            pchild = puserinteraction->_child_from_point(pmouse->m_pointHost);

            if (!pchild || pchild == this)
            {

               pchild = puserinteraction;

               break;

            }

            puserinteraction = pchild;

         }


      }

      return pchild->on_child_from_point_mouse_message_routing(pmouse);

   }


   bool interaction::on_child_from_point_mouse_message_routing(::message::mouse * pmouse)
   {

      auto pchild = this;

      string strType = ::type(pchild).name();

      if (strType.case_insensitive_contains("button"))
      {

         //informationf("mouse transfer on button");

      }
      else if (strType.case_insensitive_contains("tab"))
      {

         //informationf("mouse transfer on tab");

      }

      auto puserinteraction = pchild;

      ::user::interaction_array interactionaHandled;

      while (::is_set(puserinteraction))
      {

         puserinteraction->route_message(pmouse);

         interactionaHandled.add_interaction(puserinteraction);

         if (pmouse->m_bRet)
         {

            break;

         }

         puserinteraction = puserinteraction->get_parent();

         //if (::is_set(puserinteraction))
         //{

         //   auto pchild = puserinteraction->child_from_point(pmouse->m_point, -1, &interactionaHandled);

         //   if (::is_set(pchild))
         //   {

         //      pchild->route_message(pmouse);

         //      if (pmouse->m_bRet)
         //      {

         //         break;

         //      }

         //   }

         //}

      }


      return pmouse->m_bRet;

      //}
      //else
      //{
      //
      //   m_puserinteraction->route_message(pmouse);
      //
      //}

   }




   void interaction::_raw_client_to_screen(::point_i32 & point)
   {

      client_to_screen(::user::e_layout_design)(point);

   }


   void interaction::_raw_screen_to_client(::point_i32 & point)
   {

      screen_to_client(::user::e_layout_design)(point);

   }


#define _NEW_MESSAGE(TYPE) \
   auto pmessage = __create_new<TYPE>(); \
   pmessage->m_pchannel = this; \
   pmessage->m_oswindow = oswindow; \
   pmessage->m_puserinteraction = this; \
   pmessage->m_pwindow = pwindow; \
   pmessage->m_atom = atom; \
   pmessage->m_wparam = wparam; \
   pmessage->m_lparam = lparam; \
   pmessageBase = pmessage


   ::pointer<::message::message>
      interaction::get_message(const ::atom & atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype)
   {

      ::pointer<::message::message>pmessageBase;

      if (eprototype == ::message::e_prototype_none)
      {

         eprototype = ::message::get_message_prototype(atom.as_emessage(), 0);

      }

      ::pointer < ::windowing::window > pwindow;

      if (m_pacmewindowingwindow)
      {

         pwindow = m_pacmewindowingwindow;

      }

      auto oswindow = pwindow ? pwindow->oswindow() : nullptr;

      switch (eprototype)
      {
      case ::message::e_prototype_none:
      {

         _NEW_MESSAGE(::user::message);

      }
      break;
      case ::message::e_prototype_create:
      {
         _NEW_MESSAGE(::message::create);

      }
      break;
      case ::message::e_prototype_enable:
      {
         _NEW_MESSAGE(::message::enable);

      }
      break;
      case ::message::e_prototype_non_client_activate:
      {
         _NEW_MESSAGE(::message::nc_activate);
         {

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            pmessage->m_bActive = wparam != false;

         }
      }
      break;
      case ::message::e_prototype_key:
      {
         _NEW_MESSAGE(::message::key);
         //void key::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         {

            // ::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            pmessage->m_nChar = static_cast<::u32>(wparam);

            pmessage->m_nRepCnt = lower_u16(lparam);

            pmessage->m_nFlags = upper_u16(lparam);

            pmessage->m_iVirtualKey = (int)wparam;

            pmessage->m_nScanCode = ((lparam >> 16) & 0xff);

            pmessage->m_bExt = (lparam & (1 << 24)) != 0;

         }

      }
      break;
      case ::message::e_prototype_timer:
      {

         //throw ::exception(::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));

         _NEW_MESSAGE(::message::timer);

         pmessage->m_uEvent = static_cast<::u32>(wparam);

      }
      break;
      case ::message::e_prototype_show_window:
      {
         _NEW_MESSAGE(::message::show_window);
         pmessage->m_bShow = wparam != false;

         pmessage->m_nStatus = static_cast<::u32>(lparam);

      }
      break;
      case ::message::e_prototype_set_cursor:
      {
         _NEW_MESSAGE(::message::set_cursor);
      }
      break;
      case ::message::e_prototype_non_client_hit_test:
      {
         _NEW_MESSAGE(::message::nc_hit_test);
         pmessage->m_point.x() = i32_x(lparam);

         pmessage->m_point.y() = i32_y(lparam);
      }
      break;
      case ::message::e_prototype_move:
      {
         _NEW_MESSAGE(::message::reposition);
         pmessage->m_point = lparam.point();
      }
      break;
      case ::message::e_prototype_erase_background:
      {
         _NEW_MESSAGE(::message::erase_bkgnd);
      }
      break;
      case ::message::e_prototype_scroll:
      {
         _NEW_MESSAGE(::message::scroll);

#ifdef WINDOWS_DESKTOP
         pmessage->m_oswindowScrollBar = (::oswindow)(::iptr)(lparam);

#endif

         //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

         pmessage->m_ecommand = (enum_scroll_command)(i16)lower_u16(wparam);

         pmessage->m_dPosition = (::f64)(i16)upper_u16(wparam);

      }
      break;
      case ::message::e_prototype_set_focus:
      {
         _NEW_MESSAGE(::message::set_keyboard_focus);
      }
      break;
      case ::message::e_prototype_kill_focus:
      {
         _NEW_MESSAGE(::message::kill_keyboard_focus);
         pmessage->m_oswindowNew = (::oswindow)wparam.m_number;
      }
      break;
#if !defined(UNIVERSAL_WINDOWS) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(__BSD__)
      case ::message::e_prototype_window_pos:

      {
         _NEW_MESSAGE(::message::window_pos);
         pmessage->m_pWINDOWPOS = reinterpret_cast<void *>(lparam.m_lparam);
      }
      break;
      case ::message::e_prototype_non_client_calc_size:
      {
         _NEW_MESSAGE(::message::nc_calc_size);
         pmessage->m_pNCCALCSIZE_PARAMS = reinterpret_cast<void *>(lparam.m_lparam);
      }
      break;
#endif
      case ::message::e_prototype_mouse:
      {
         _NEW_MESSAGE(::message::mouse);
         pmessage->m_ebuttonstate = (::user::enum_button_state)wparam.m_number;

         //         if ((pmessage->m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM))
         //         {
         //
         //            informationf("(m_ebuttonstate & I32_MINIMUM) == (I32_MINIMUM)");
         //
         //         }

         pmessage->m_pointHost = lparam.point();

         pmessage->m_pointAbsolute = lparam.point();

         _raw_client_to_screen(pmessage->m_pointAbsolute);

      }
      break;
      case ::message::e_prototype_object:
      {
         _NEW_MESSAGE(::message::particle);
         //void particle::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         {

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

            ::particle_pointer pparticle(lparam);

            pmessage->m_pparticle = pparticle;

            pmessage->m_lparam = 0;

         }
      }
      break;
      case ::message::e_prototype_mouse_wheel:
      {
         _NEW_MESSAGE(::message::mouse_wheel);

         pmessage->m_ebuttonstate = (::user::enum_button_state)lower_u16(wparam);

         pmessage->m_pointAbsolute = lparam.point();

         pmessage->m_Δ = upper_i16(wparam);

         pmessage->m_pointHost = pmessage->m_pointAbsolute;

         _raw_screen_to_client(pmessage->m_pointHost);

      }
      break;
      case ::message::e_prototype_size:
      {
         _NEW_MESSAGE(::message::size);

         pmessage->m_nType = static_cast <::u32> (wparam);

         pmessage->m_size = ::size_i32(i32_x(lparam), i32_y(lparam));
      }
      break;
      case ::message::e_prototype_activate:
      {
         _NEW_MESSAGE(::message::activate);
         //pmessage = p;
         //default_set(pmessage, atom, wparam, lparam)
         //void activate::set(oswindow oswindow, ::windowing::window * pwindow, const ::atom & atom, wparam wparam, ::lparam lparam)
         //{

            //::user::message::set(oswindow, pwindow, atom, wparam, lparam);

         pmessage->m_eactivate = (enum_activate)(lower_u16(wparam));

         if (lparam == 0)
         {

            pmessage->m_pWndOther = nullptr;

         }
         else
         {

            auto paurasession = m_pcontext->m_pacmesession->m_paurasession;

            auto puser = paurasession->m_puser;

            auto pwindowing = system()->windowing();

            auto pwindow = pwindowing->window(lparam.raw_cast <::oswindow>());

            if (pwindow)
            {

               pmessage->m_pWndOther = pwindow->m_puserinteraction;

            }

         }

         pmessage->m_bMinimized = upper_u16(wparam) != false;

         //}

      }
      break;
      case ::message::e_prototype_mouse_activate:
      {
         _NEW_MESSAGE(::message::mouse_activate);
      }
      break;
      default:
      {

         auto pmessage = ::channel::get_message(atom, wparam, lparam, eprototype);

         pmessageBase = pmessage;

      }
      break;
      }

      if (pmessageBase.is_null())
      {

         return nullptr;

      }

      //auto estatus =




      //if (!estatus)
      //{

      //   return nullptr;

      //}

      return pmessageBase;

   }


   void interaction::walk_pre_translate_tree(::message::message * pmessage, ::user::interaction * puiStop)
   {

      if (puiStop == this)
      {

         return;

      }

      try
      {

         pre_translate_message(pmessage);

      }
      catch (...)
      {

      }

      if (!m_bDefaultWalkPreTranslateParentTree)
      {

         return;

      }

      if (pmessage->m_bRet)
      {

         return;

      }

      ::user::interaction * puserinteractionParent = get_parent();

      if (::is_null(puserinteractionParent))
      {

         return;

      }

      if (puserinteractionParent == puiStop)
      {

         return;

      }

      try
      {

         puserinteractionParent->pre_translate_message(pmessage);

      }
      catch (...)
      {

      }


   }


   bool interaction::contains_user_interaction(::user::interaction * pinteraction, bool bRecursive)
   {

      if (this == pinteraction)
      {

         return true;

      }

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (::is_null(puserinteractionpointeraChild))
      {

         return false;

      }

      if (puserinteractionpointeraChild->contains_interaction(pinteraction))
      {

         return true;

      }

      if (!bRecursive)
      {

         return false;

      }

      for (auto & puiChild : puserinteractionpointeraChild->interactiona())
      {

         if (puiChild->contains_user_interaction(pinteraction))
         {

            return true;

         }

      }

      return false;

   }


   void interaction::on_select()
   {

   }


   bool interaction::is_place_holder()
   {

      return false;

   }


   ::frequency interaction::get_output_per_second()
   {

      auto pinteraction = get_host_user_interaction();

      if (::is_null(pinteraction))
      {

         return 0.0;

      }

      auto pwindow = pinteraction->windowing_window();

      if (!pwindow)
      {

         return 0.0;

      }

      return pwindow->get_output_per_second();

   }


   ::pointer<::windowing::cursor> interaction::get_mouse_cursor(enum_cursor ecursor)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      auto pcursor = pwindowing->get_cursor(ecursor);

      if (::is_null(pcursor))
      {

         return nullptr;

      }

      return pcursor;

   }


   ::windowing::cursor * interaction::get_mouse_cursor()
   {

      return m_pcursorDefault;

   }


   ::point_i32 interaction::host_mouse_cursor_position()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return {};

      }

      auto pointCursor = pwindowThis->m_pointCursor2;

      return pointCursor;

   }


   ::point_i32 interaction::mouse_cursor_position()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return {};

      }

      auto pointCursor = pwindowThis->m_pointCursor2;

      host_to_client()(pointCursor);

      return pointCursor;

   }


   ::point_i32 interaction::absolute_mouse_cursor_position()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return {};

      }

      auto pdisplay = pwindowThis->display();

      if (::is_null(pdisplay))
      {

         return {};

      }

      auto pointCursor = pdisplay->m_pointCursor2;

      return pointCursor;

   }


   //   void interaction::set_cursor_position(const ::point_i32 & pointCursor)
   //   {
   //
   //      auto pwindowThis = window();
   //
   //      if (::is_null(pwindow))
   //      {
   //
   //         throw ::exception(::error_wrong_state);
   //
   //      }
   //
   //      pwindow->set_cursor_position(pointCursor);
   //
   //   }


   void interaction::set_mouse_capture()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         throw ::exception(error_wrong_state);

      }

      /*auto pwindow = pwindow->m_pwindow;

      if (::is_null(pwindow))
      {

         throw ::exception(error_wrong_state);

      }*/

      pwindowThis->set_mouse_capture(this);

      g_i134++;

      //return true;

   }


   bool interaction::defer_release_mouse_capture()
   {

      ::string strType = ::type(this).name();

      information() << "interaction::defer_release_mouse_capture type : " << strType << ", atom : " << m_atom.as_string();

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return false;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return false;

      //}

      return pwindowThis->defer_release_mouse_capture(this);

   }


   ::draw2d::graphics_pointer interaction::create_memory_graphics()
   {

      auto psystem = system()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      return pgraphics;

   }


   double interaction::_001GetDefaultFontHeight(::draw2d::graphics_pointer & pgraphics)
   {

      defer_graphics(pgraphics);

      pgraphics->set_font(this, ::e_element_none);

      ::size_f64 size;

      size = pgraphics->get_text_extent(unitext("Ap"));

      return size.cy();

   }


   void interaction::set_default_mouse_cursor(::windowing::cursor * pcursor)
   {

      //      if (!window())
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      auto estatus = window()->set_mouse_cursor(pcursor);
      //
      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }

      m_pcursorDefault = pcursor;

   }


   //void interaction::aaa_set_mouse_cursor(::windowing::cursor * pcursor)
   //{

   //   if (!windowing_window())
   //   {

   //      return false;

   //   }

   //   if (!windowing_window()->aaa_set_mouse_cursor(pcursor))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //::point_i32 interaction::get_cursor_position() const
   //{

   //   auto puserinteraction = get_host_user_interaction();

   //   if (puserinteraction == this)
   //   {

   //      return window()->get_cursor_position();

   //   }

   //   if (!puserinteraction)
   //   {

   //      return ::point_i32();

   //   }

   //   return puserinteraction->get_cursor_position();

   //}


   void interaction::on_message_mouse_enter(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   //void interaction::on_message_set_cursor(::message::message* pmessage)
   //{

   //   //auto pcursor = get_mouse_cursor();

   //   //if (pcursor)
   //   //{

   //   //   ::pointer<::message::set_cursor>psetcursor = pmessage;


   //   //   if (psetcursor)
   //   //   {

   //   //      //psetcursor->m_pcursor = pcursor;

   //   //      psetcursor->m_bRet = true;

   //   //   }

   //   //}

   //}



   bool interaction::can_merge(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   bool interaction::merge(::user::interaction * pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   ::user::element * interaction::first_child_user_element()
   {

      return first_child();

   }


   ::user::element * interaction::top_user_element()
   {

      return ::user::interaction_base::top_user_element();

   }


   ::user::element * interaction::under_user_element()
   {

      return under_sibling();

   }


   ::user::element * interaction::above_user_element()
   {

      return above_sibling();

   }


   ::user::element * interaction::next_user_element()
   {

      return next_sibling();

   }


   ::user::element * interaction::previous_user_element()
   {

      return previous_sibling();

   }


   ::user::interaction * interaction::first_child()
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      try
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
         {

            return nullptr;

         }
         else
         {

            return puserinteractionpointeraChild->first_interaction();

         }

      }
      catch (...)
      {
      }
      return nullptr;
   }


   ::user::interaction * interaction::last_child()
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      try
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
         if (!puserinteractionpointeraChild || puserinteractionpointeraChild->has_no_interaction())
            return nullptr;
         else
            return puserinteractionpointeraChild->last_interaction();
      }
      catch (...)
      {
      }
      return nullptr;
   }


   ::user::interaction * interaction::first_sibling()
   {
      try
      {

         if (get_parent() == nullptr)
            return nullptr;

         return get_parent()->first_child();

      }
      catch (...)
      {
      }
      return nullptr;

   }


   ::user::interaction * interaction::next_sibling()
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      try
      {

         ::user::interaction * pinteractionParent = nullptr;
         try
         {
            pinteractionParent = get_parent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteractionParent == nullptr)
            return nullptr;
         auto puserinteractionpointeraChild = pinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         ::collection::index i = puserinteractionpointeraChild->interactiona().find_first(this);
         if (i < 0)
            return nullptr;
         i++;
         if (i >= puserinteractionpointeraChild->interaction_count())
            return nullptr;
         else
            return puserinteractionpointeraChild->interaction_at(i);

      }
      catch (...)
      {
      }
      return nullptr;


   }


   ::user::interaction * interaction::next_sibling(::user::interaction * pinteraction)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      try
      {
         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
         ::collection::index i = puserinteractionpointeraChild->find_first_interaction(pinteraction);
         if (i < 0)
            return nullptr;
         i++;
      restart:
         if (i >= puserinteractionpointeraChild->interaction_count())
            return nullptr;
         else
         {
            try
            {
               return puserinteractionpointeraChild->interaction_at(i);
            }
            catch (...)
            {
               goto restart;
            }
         }
      }
      catch (...)
      {

      }

      return nullptr;

   }

   ::user::interaction * interaction::previous_sibling()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      try
      {

         ::user::interaction * pinteractionParent = nullptr;
         try
         {
            pinteractionParent = get_parent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteractionParent == nullptr)
            return nullptr;

         auto puserinteractionpointeraChild = pinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         ::collection::index i = puserinteractionpointeraChild->find_first_interaction(this);
         if (i < 0)
            return nullptr;
         i--;
         if (i < 0)
            return nullptr;
         else
            return puserinteractionpointeraChild->interaction_at(i);

      }
      catch (...)
      {

      }

      return nullptr;

   }

   ::user::interaction * interaction::last_sibling()
   {

      try
      {

         if (get_parent() == nullptr)
            return nullptr;

         return get_parent()->last_child();

      }
      catch (...)
      {

      }

      return nullptr;


   }


   void interaction::mouse_hover_add(::user::interaction * pinterface)
   {

      //auto puserinteraction = get_wnd();

      //if (!puserinteraction)
      //{

      //   return ;

      //   //throw ::exception(error_wrong_state);

      //}

      //auto pwindow = puserinteraction->window();

      //if (!pwindow)
      //{

      //   return;
      //   //throw ::exception(error_null_pointer);

      //}

      //auto bOk =

      window()->mouse_hover_add(pinterface);

      //if (!bOk)
      //{

      //   return bOk;

      //}

      //return bOk;

   }


   bool interaction::mouse_hover_erase(::user::interaction * pinterface)
   {

      auto puserinteraction = get_wnd();

      if (!puserinteraction || puserinteraction == this)
      {

         return false;

      }

      //auto pwindow = puserinteraction->window();

      //if (!pwindow)
      //{

      //   return false;

      //}

      auto bOk = window()->mouse_hover_erase(pinterface);

      if (!bOk)
      {

         return false;

      }

      return true;

   }


   i32 interaction::get_wheel_scroll_delta()
   {

      return 0;

   }


   ::user::interaction * interaction::previous_sibling(::user::interaction * pinteraction)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      ::collection::index i = puserinteractionpointeraChild->find_first_interaction(pinteraction);
      if (i < 0)
         return nullptr;
   restart:
      i--;
      if (i < 0)
         return nullptr;
      else
      {
         try
         {
            return m_puserinteractionpointeraChild->interaction_at(i);
         }
         catch (...)
         {
            goto restart;
         }
      }
   }


   void interaction::get_child_rect(::rectangle_i32 & rectangle)
   {

      rectangle = this->rectangle();

   }


   //bool interaction::keyboard_focus_OnChildKillFocus()
   //{

   //   if (window() == nullptr)
   //      return true;


   //   return window()->keyboard_focus_OnChildKillFocus();

   //}


   ::user::interaction * interaction::get_os_focus_uie()
   {

      return nullptr;

   }


   bool interaction::is_ascendant(element * puiIsAscendant, bool bIncludeSelf)
   {

      //if (::is_null(window()))
      //{

      //   return false;

      //}

      return ::user::interaction_base::is_ascendant(puiIsAscendant, bIncludeSelf);

   }


   bool interaction::is_parent(element * puiIsParent)
   {

      return ::user::interaction_base::is_parent(puiIsParent);

   }


   bool interaction::is_child(element * puiIsChild)
   {

      return ::user::interaction_base::is_child(puiIsChild);

   }


   //bool interaction::is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const
   //{

   //   return window()->is_descendant(puiIsDescendant, bIncludeSelf);

   //}


   bool interaction::is_ascendant(::user::controller * pcontroller, bool bIncludeSelf)
   {

      if (::is_null(pcontroller))
      {

         return false;

      }

      for (::collection::index iImpact = 0; iImpact < pcontroller->impact_count(); iImpact++)
      {

         auto pimpact = pcontroller->impact_at(iImpact);

         if (::is_set(pimpact))
         {

            if (is_ascendant(pimpact, bIncludeSelf))
            {

               return true;

            }

         }

      }

      return false;

   }


   bool interaction::contains(element * puiIsChild)
   {

      return is_child(puiIsChild);

   }


   bool interaction::recursively_contains(element * puiIsChild, bool bIncludeSelf)
   {

      return is_descendant(puiIsChild, bIncludeSelf);

   }


   ::user::interaction * interaction::get_wnd()
   {

      if (m_puserinteractionParent == this)
      {

         ((::user::interaction *)this)->m_puserinteractionParent.release();

         return nullptr;

      }

      if (m_puserinteractionParent == nullptr)
      {

         return (::user::interaction *)this;

      }

      //auto psession = get_session();

      //if(::is_set(psession) && m_puserinteractionParent == psession->get_user_interaction_host())
      if (m_bUserInteractionHost)
      {

         return (::user::interaction *)this;

      }

      return m_puserinteractionParent->get_wnd();

   }


   // returns -1 if not descendant
   i32 interaction::get_descendant_level(::user::element * pinteraction)
   {

      i32 iLevel = 0;

      while (pinteraction != nullptr)
      {

         if (pinteraction == this)
         {

            return iLevel;

         }

         pinteraction = pinteraction->get_parent();

         iLevel++;

      }

      return -1;

   }


   bool interaction::is_descendant(::user::element * pinteraction, bool bIncludeSelf)
   {

      if (bIncludeSelf)
      {

         return get_descendant_level(pinteraction) >= 0;

      }
      else
      {

         return get_descendant_level(pinteraction) > 0;

      }

   }


   ::user::interaction * interaction::get_focusable_descendant()
   {

      auto pinteraction = this;

      while (true)
      {

         pinteraction = pinteraction->get_next_window(false, this);

         if (::is_null(pinteraction))
         {

            return nullptr;

         }
         else if (pinteraction->keyboard_focus_is_focusable())
         {

            return (::user::interaction *)pinteraction;

         }

      }

   }


   //   void interaction::_001OnTriggerMouseInside()
   //   {
   //
   //      if (window() != nullptr)
   //      {
   //
   //         window()->_001OnTriggerMouseInside();
   //
   //      }
   //
   //   }


   void interaction::update_data(bool bSaveAndValidate)
   {

      //return true;

   }


   void interaction::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      if (tool().contains_item(e_element_close_button)
         || tool().contains_item(e_element_close_icon)
         || tool().contains_item(id_close_app))
      {

         if (is_top_level())
         {

            window()->m_bQuitGraphicsOnHide = true;
            window()->m_bDestroyWindowOnHide = true;
            window()->m_bTryCloseApplicationOnHide = true;

         }

         display(e_display_hide);

         set_need_layout();

         set_need_redraw();

         post_redraw();

         return;

      }

      display(e_display_none);

      destroy_window();

   }


   string interaction::get_window_default_matter()
   {

      return "main";

   }


   string interaction::get_window_icon_matter()
   {

      return get_window_default_matter();

   }


   u32 interaction::get_window_default_style()
   {

      return 0;

   }


   //::user::enum_window_type interaction::get_window_type()
   //{
   //
   //   return e_window_type_window;

   //}


   //bool interaction::post_simple_command(e_simple_command ecommand,lparam lparam)

   //{

   //   post_message(e_message_simple_command,(wparam)ecommand,lparam);


   //   return true;

   //}

   //void interaction::_001OnCommand(::message::message * pmessage)
   //{

   //   ::pointer<::message::message>pmessage(pmessage);

   //   lresult lresult = 0;

   //   pmessage->m_bRet = OnCommand(pmessage);

   //   pmessage->m_lresult = lresult;

   //}


   void interaction::on_message_simple_command(::message::message * pmessage)
   {

      ::pointer<::message::simple_command> psimplecommand = pmessage;

      on_simple_command(psimplecommand);

   }


   void interaction::on_message_need_load_form_data(::message::message * pmessage)
   {

      m_bNeedLoadFormData = false;

      update_data(false);

      set_need_redraw();

      post_redraw();

   }


   void interaction::on_message_need_save_form_data(::message::message * pmessage)
   {

      m_bNeedSaveFormData = false;

      update_data(true);

   }


   bool interaction::OnCommand(::message::message * pmessage)
   {

      //if (window() != nullptr)
      //{

      //   return window()->OnCommand(pmessage);

      //}

      return false;

   }


   bool interaction::OnNotify(::message::message * pmessage)
   {

      //if (window() != nullptr)
      //{

      //   return window()->OnNotify(pmessage);

      //}

      return false;

   }


   bool interaction::OnChildNotify(::message::message * pmessage)
   {

      //if (window() != nullptr)
      //{

      //   return window()->OnChildNotify(pmessage);

      //}

      return false;

   }


   void interaction::on_simple_command(::message::simple_command * psimplecommand)
   {

      auto esimplecommand = psimplecommand->command();

      switch (esimplecommand)
      {
      case e_simple_command_layout:
      {

         psimplecommand->m_bRet = true;

      }
      case e_simple_command_check_transparent_mouse_events:
      {

#ifdef WINDOWS_DESKTOP

         ::user::interaction * puiTop = get_wnd();

         if (puiTop != this)
         {

            ASSERT(false);

            return;

         }

         //::pointer<::windowing::window>pwindow = window();

         bool bStart = window()->m_bTransparentMouseEvents
            && puiTop->is_this_visible();
         // || (puiTop->GetExStyle() & WS_EX_LAYERED
         //    && puiTop->layout().is_full_screen());

         if (bStart && layout().is_changing())
         {

            bStart = false;

         }

         if (bStart)
         {

            defer_branch("transparent_mouse_event_thread",
               [this]()
               {

                  _task_transparent_mouse_event();
               }
            );

            //::SetTimer(get_handle(), e_timer_transparent_mouse_event, 5, NULL);

            //SetTimer(e_timer_transparent_mouse_event, 100);

         }
         else
         {

            _synchronous_lock synchronouslock(this->synchronization());

            auto pthread = payload("transparent_mouse_event_thread").cast<::thread>();

            if (pthread)
            {

               pthread->post_quit();

               payload("transparent_mouse_event_thread").unset();

            }

            //::KillTimer(get_handle(), e_timer_transparent_mouse_event);

            //KillTimer(e_timer_transparent_mouse_event);

         }

#endif

      }
      break;
      //case e_simple_command_defer_start_graphics_thread:
      //{

      //   window()->_defer_start_graphics_thread();


      //}
      break;
      default:

         break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::interaction_base::on_simple_command(psimplecommand);

   }


   void interaction::on_command(::message::command * pcommand)
   {

      ::user::interaction_base::on_command(pcommand);

   }


   bool interaction::is_selected(::data::item * pitem)
   {

      __UNREFERENCED_PARAMETER(pitem);

      return false;

   }


   //// <3ThomasBorregaardSorensen__!!
   void interaction::handle_command(const ::atom & atom)
   {

      if (m_pmatterCommandHandler)
      {

         return m_pmatterCommandHandler->handle_command(atom);

      }

      //return ::error_failed;

   }


   bool interaction::has_command_handler(::message::command * pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

      return false;

   }


   bool interaction::_001OnBeforeEnterIconic()
   {

      return ::user::interaction_base::_001OnBeforeEnterIconic();

   }


   bool interaction::_001OnBeforeEnterNormal()
   {

      return ::user::interaction_base::_001OnBeforeEnterNormal();

   }


   bool interaction::_001OnBeforeEnterZoomed()
   {

      return ::user::interaction_base::_001OnBeforeEnterZoomed();

   }


   bool interaction::_001OnBeforeEnterFullScreen()
   {

      return ::user::interaction_base::_001OnBeforeEnterFullScreen();

   }


   bool interaction::_001OnBeforeEnterAppearance()
   {

      if (layout().lading().display() != e_display_none && layout().lading().display() != e_display_current)
      {

         auto edisplayLading = layout().lading().display();

         auto edisplayLayout = layout().layout().display();

         if (edisplayLading == e_display_iconic && edisplayLayout != e_display_iconic)
         {

            return _001OnBeforeEnterIconic();

         }
         else if (edisplayLading == e_display_zoomed && edisplayLayout != e_display_zoomed)
         {

            return _001OnBeforeEnterZoomed();

         }
         else if (equivalence_sink(edisplayLading) == e_display_normal &&
                  equivalence_sink(edisplayLayout) != e_display_normal)
         {

            return _001OnBeforeEnterNormal();

         }
         else if (edisplayLading == e_display_full_screen && edisplayLayout != e_display_full_screen)
         {

            return _001OnBeforeEnterFullScreen();

         }

      }

      return true;

   }


   void interaction::_001OnAfterEnterIconic()
   {

      ::user::interaction_base::_001OnAfterEnterIconic();

   }


   void interaction::_001OnAfterEnterNormal()
   {

      ::user::interaction_base::_001OnAfterEnterNormal();

   }


   void interaction::_001OnAfterEnterZoomed()
   {

      ::user::interaction_base::_001OnAfterEnterZoomed();

   }


   void interaction::_001OnAfterEnterFullScreen()
   {

      ::user::interaction_base::_001OnAfterEnterFullScreen();

   }


   void interaction::_001OnAfterEnterAppearance()
   {

      if (layout().lading().display() != e_display_none && layout().lading().display() != e_display_current)
      {

         auto edisplayLayout = layout().layout().display();

         if (edisplayLayout == e_display_iconic)
         {

            _001OnAfterEnterIconic();

            auto ptopic = create_topic(id_on_after_enter_iconic);

            route(ptopic);

         }
         else if (equivalence_sink(edisplayLayout) == e_display_normal)
         {

            _001OnAfterEnterNormal();

            auto ptopic = create_topic(id_on_after_enter_normal);

            route(ptopic);

         }
         else if (edisplayLayout == e_display_zoomed)
         {

            _001OnAfterEnterZoomed();

            auto ptopic = create_topic(id_on_after_enter_zoomed);

            route(ptopic);

         }
         else if (layout().layout().display() == e_display_full_screen)
         {

            _001OnAfterEnterFullScreen();

            auto ptopic = create_topic(id_on_after_enter_full_screen);

            route(ptopic);

         }

      }

   }


   bool interaction::_001OnBeforeExitIconic()
   {

      return ::user::interaction_base::_001OnBeforeExitIconic();

   }


   bool interaction::_001OnBeforeExitNormal()
   {

      return ::user::interaction_base::_001OnBeforeExitNormal();

   }


   bool interaction::_001OnBeforeExitZoomed()
   {

      return ::user::interaction_base::_001OnBeforeExitZoomed();

   }


   bool interaction::_001OnBeforeExitFullScreen()
   {

      return ::user::interaction_base::_001OnBeforeExitFullScreen();

   }


   bool interaction::_001OnBeforeExitAppearance()
   {

      if (layout().lading().display() != e_display_none && layout().lading().display() != e_display_current)
      {

         auto edisplayCurrent = layout().layout().display();

         if (edisplayCurrent == e_display_iconic)
         {

            return _001OnBeforeExitIconic();

         }
         else if (equivalence_sink(edisplayCurrent) == e_display_normal)
         {

            return _001OnBeforeExitNormal();

         }
         else if (edisplayCurrent == e_display_zoomed)
         {

            return _001OnBeforeExitZoomed();

         }
         else if (edisplayCurrent == e_display_full_screen)
         {

            return _001OnBeforeExitFullScreen();

         }

      }

      return true;

   }


   void interaction::_001OnAfterExitIconic()
   {

      //if (::is_null(window()))
      //{

      //   return;

      //}

//      if (layout().normal().m_bAutoRefresh)
//      {
//
//         if (!is_fps_interest())
//         {
//
//            set_fps_interest();
//
//         }
//
//      }

      //window()->_001OnAfterExitIconic();

   }


   void interaction::_001OnAfterExitNormal()
   {

      auto rectangle = layout().window().parent_raw_rectangle();

      layout().normal() = layout().window();

      //bool bAutoRefresh = is_fps_interest();

      //layout().normal().m_bAutoRefresh = bAutoRefresh;

      //window()->_001OnAfterExitNormal();

   }


   void interaction::_001OnAfterExitZoomed()
   {

      auto rectangle = layout().window().parent_raw_rectangle();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      //bool bAutoRefresh = is_fps_interest();

      ///layout().normal().m_bAutoRefresh = bAutoRefresh;

      //window()->_001OnAfterExitZoomed();

   }


   void interaction::_001OnAfterExitFullScreen()
   {

      auto rectangle = layout().window().parent_raw_rectangle();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      //      bool bAutoRefresh = is_fps_interest();

      //      layout().normal().m_bAutoRefresh = bAutoRefresh;

            //if (::is_null(window()))
            //{

            //   return;

            //}

            //window()->_001OnAfterExitFullScreen();

   }


   void interaction::_001OnAfterExitAppearance()
   {

      if (layout().lading().display() != e_display_none && layout().lading().display() != e_display_current)
      {

         auto edisplay = layout().lading().display();

         auto edisplayPrevious = window_previous_display();

         if (edisplay != edisplayPrevious)
         {

            if (edisplayPrevious == e_display_iconic)
            {

               _001OnAfterExitIconic();

               auto ptopic = create_topic(id_on_after_exit_iconic);

               route(ptopic);

            }
            else if (equivalence_sink(edisplayPrevious) == e_display_normal)
            {

               _001OnAfterExitNormal();

               auto ptopic = create_topic(id_on_after_exit_normal);

               route(ptopic);

            }
            else if (edisplayPrevious == e_display_zoomed)
            {

               _001OnAfterExitZoomed();

               auto ptopic = create_topic(id_on_after_exit_zoomed);

               route(ptopic);

            }
            else if (edisplayPrevious == e_display_full_screen)
            {

               _001OnAfterExitFullScreen();

               auto ptopic = create_topic(id_on_after_exit_full_screen);

               route(ptopic);

            }

         }

      }

   }


   //bool interaction::_001OnExitAppearance()
   //{

   //   if (layout().lading().display() != e_display_none && layout().lading().display() != e_display_current)
   //   {

   //      auto edisplayLading = layout().lading().display();

   //      auto edisplayLayout = layout().layout().display();

   //      if (edisplayLading != e_display_iconic && edisplayLayout == e_display_iconic)
   //      {

   //         _001OnExitIconic();

   //      }
   //      else if (edisplayLading != e_display_zoomed && edisplayLayout == e_display_zoomed)
   //      {

   //         _001OnExitZoomed();

   //      }
   //      else if (
   //         !(edisplayLading == e_display_restore ||
   //            edisplayLading == e_display_normal)
   //         &&
   //         (edisplayLayout == e_display_restore
   //            || edisplayLayout == e_display_normal))
   //      {

   //         _001OnExitNormal();

   //      }
   //      else if (layout().lading().display() != e_display_full_screen && layout().layout().display() == e_display_full_screen)
   //      {

   //         _001OnExitFullScreen();

   //      }

   //   }

   //   return true;

   //}


   void interaction::keep_alive(::object * pliveobject)
   {

      get_app()->keep_alive();

      if (::get_task() != nullptr)
      {

         ::get_task()->keep_alive();

      }

      if (pliveobject != nullptr)
      {

         pliveobject->keep_alive();

      }

   }


   //   void interaction::move_to(const ::point_i32 & point)
   //   {
   //
   //      layout().lading().origin() = point;
   //
   //   }


   //   void interaction::set_size(const ::size_i32 & size)
   //   {
   //
   //      layout().lading().size() = size;
   //
   //   }


   //   void interaction::move_to(i32 x, i32 y)
   //   {
   //
   //      move_to({ x, y });
   //
   //   }


   //   void interaction::set_size(i32 cx, i32 cy)
   //   {
   //
   //      set_size({ cx, cy });
   //
   //   }


   //   void interaction::set_dim(const ::point_i32 & point, const ::size_i32 & size)
   //   {
   //
   //      place(::rectangle_i32(point, size));
   //
   //   }


   void interaction::place(const ::rectangle_i32 & rectangle, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto sizeNew = rectangle.size();

      bool bOnSetSize = on_set_size(sizeNew, elayout);

      if (!bOnSetSize)
      {

         //information() << "interaction::place !bOnSetSize";

         set_position(rectangle.origin(), elayout, pgraphics);

         return;

      }

      auto pointNew = rectangle.origin();

      bool bOnSetPosition = on_set_position(pointNew, elayout);

      if (!bOnSetPosition)
      {

         //information() << "interaction::place !bOnSetSize";

         set_size(rectangle.size(), elayout, pgraphics);

         return;

      }

      ::rectangle_i32_array rectangleaCertainlyDamaged;

      ::rectangle_i32 rectangleBefore;

      ::rectangle_i32 rectangleAfter;

      {

         _synchronous_lock synchronouslock(this->synchronization());

         auto & layoutstate = layout().m_statea[elayout];

         rectangleBefore = layoutstate.raw_rectangle();

         layoutstate.set_visual_state_origin(pointNew);

         layoutstate.m_size = sizeNew;

         auto r = layout().m_statea[elayout].parent_raw_rectangle();

         rectangleAfter = layoutstate.raw_rectangle();

         if (get_parent() == nullptr)
         {

            auto p = __get_top_right();

            if (p.is_set())
            {

               auto Δ = r.top_right() - p;

               if (Δ.cx() != 0 || Δ.cy() != 0)
               {

                  information() << "place top right offset not null " << Δ;

               }

            }

         }

      }

      auto iLayout = (::i32)elayout;

      while (iLayout >= 0)
      {

         layout().m_statea[iLayout].m_size = sizeNew;

         layout().m_statea[iLayout].m_point2 = pointNew;

         iLayout--;

      }

      if (windowing_window() && elayout == e_layout_sketch)
      {

         window()->placement_log()->add({ pointNew, sizeNew });

      }

      m_bNeedPerformLayout = true;

      set_need_layout();

      if (get_parent() != nullptr)
      {

         set_need_redraw({}, pgraphics);

      }
      else
      {

         place_set_need_redraw(rectangleAfter, rectangleBefore, pgraphics);

      }

      if (::is_null(pgraphics))
      {

         post_redraw();

      }

   }


   void interaction::place_set_need_redraw(const ::rectangle_i32 & rectangleAfter, const ::rectangle_i32 & rectangleBefore, ::draw2d::graphics * pgraphics)
   {
      //  if (get_parent() == nullptr)
        //{

      auto rectangleaCertainlyDamaged = get_top_left_oriented_damaged_areas_by_resizing(rectangleAfter,
                                                                                         rectangleBefore);

      //}


   //auto rectangleaCertainlyDamaged = get_top_left_oriented_damaged_areas_by_resizing(rectangleAfter, rectangleBefore);

      set_need_redraw(rectangleaCertainlyDamaged, pgraphics);

   }


   void interaction::place(::i32 x, ::i32 y, ::i32 w, ::i32 h, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      auto rectangle = ::rectangle_f32_dimension(x, y, w, h);

      place(rectangle, elayout, pgraphics);

   }


   //   void interaction::set_dim(i32 x, i32 y, i32 cx, i32 cy)
   //   {
   //
   //      place(rectangle_i32_dimension(x, y, cx, cy));
   //
   //   }


   interaction & interaction::operator=(const ::rectangle_i32 & rectangle)
   {

      place(rectangle);

      return *this;

   }


   void interaction::place_rate_or_size(const ::rectangle_f64 & rectangleRateOrSize)
   {

      ::rectangle_i32 rectangle;

      calculate_window_rectangle_in_main_monitor(rectangle, rectangleRateOrSize);

      place(rectangle);

   }


   void interaction::activation(::e_activation eactivation)
   {

      layout().sketch() = eactivation;

   }


   void interaction::display_child(const ::rectangle_i32 & rectangle, enum_layout elayout, ::draw2d::graphics * pgraphics)
   {

      place(rectangle, elayout, pgraphics);

      display(e_display_normal);

   }


   ::user::interaction * interaction::best_top_level_parent(::rectangle_i32 & rectangle)
   {

      auto ptoplevel = top_level();

      if (!ptoplevel || ptoplevel == this)
      {

         best_monitor(&rectangle);

      }
      else
      {

         ptoplevel->window_rectangle(rectangle);

      }

      return ptoplevel;

   }


   ::rectangle_i32 interaction::parent_client_rectangle(enum_layout elayout)
   {

      auto rectangle = this->rectangle(elayout);

      this->client_to_parent(elayout)(rectangle);

      return rectangle;

   }


   ::point_i32 interaction::position(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).top_left();
   }

   ::size_i32 interaction::size(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).size();
   }

   ::i32 interaction::top(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).top();
   }

   ::i32 interaction::left(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).left();
   }

   ::i32 interaction::right(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).right();
   }

   ::i32 interaction::bottom(enum_layout elayout)
   {
      return parent_client_rectangle(elayout).bottom();
   }


   void interaction::window_rectangle(::rectangle_i32 & rect, enum_layout elayout)
   {

      rect = this->window_rectangle(elayout);

   }


   ::rectangle_i32 interaction::window_rectangle(enum_layout elayout)
   {

      auto rectangle = this->raw_rectangle(elayout);

      this->client_to_screen(elayout)(rectangle);

      return rectangle;

   }


   void interaction::design_window_minimize(::e_activation eactivation)
   {

      auto rectangleRequest = this->screen_rectangle(e_layout_lading);

      good_iconify(nullptr, rectangleRequest, true, eactivation, layout().lading().zorder());

   }


   void interaction::design_window_maximize()
   {

      ::rectangle_i32 rectangleRequest = this->screen_rectangle(e_layout_lading);

      best_workspace(nullptr, rectangleRequest, true, layout().lading().activation(), layout().lading().zorder());

   }


   void interaction::design_window_full_screen(const ::rectangle_i32 & rectangleHint)
   {

      ::rectangle_i32 rectangleRequest;

      if (!rectangleHint.is_empty())
      {

         rectangleRequest = rectangleHint;

      }
      else
      {

         rectangleRequest = this->screen_rectangle(::user::e_layout_lading);

      }

      best_monitor(nullptr, rectangleRequest, true, layout().lading().activation(), layout().lading().zorder());

   }


   void interaction::design_window_normal(::e_display edisplay)
   {

      auto activation = layout().lading().activation();

      auto zorder = layout().lading().zorder();

      auto rectangle = layout().lading().parent_raw_rectangle();

      information() << "design_window_normal rectangle : " << rectangle;

      good_restore(nullptr, rectangle, true, layout().lading().activation(), layout().lading().zorder(), edisplay);

   }


   void interaction::design_window_dock(::e_display edisplay)
   {

      ASSERT(is_docking_appearance(edisplay));

      if (is_docking_appearance(edisplay))
      {

         auto rectangleRequest = this->screen_rectangle(::user::e_layout_lading);

         make_zoneing(nullptr, rectangleRequest, true, &edisplay, layout().lading().activation(),
                      layout().lading().zorder());

      }

   }


   void interaction::frame_experience_restore(::e_activation eactivation)
   {

      //throw ::interface_only();

      //display_previous();

      display(e_display_normal, eactivation);

   }


   ::user::notify_icon * interaction::notify_icon()
   {

      return nullptr;

   }


   void interaction::on_update_notify_icon_menu(::collection::index & iNotifyIconIndex)
   {

   }


   void interaction::on_app_activated()
   {

      //auto estatus =

      //bool bDisplayPreviousOnRestore = true;

      //frame_toggle_restore(bDisplayPreviousOnRestore);

      frame_restore();

      //if(!estatus)
      //{
      //
      //   return estatus;
      //
      //}
      //
      //return estatus;

//      bool bWindowVisible = is_window_visible();
//
//      double dOccludedOpaqueRate = _001GetTopLeftWeightedOccludedOpaqueRate();
//
//      bool bIconic = layout().is_iconic();
//
//      if (!bWindowVisible || dOccludedOpaqueRate > 0.025 || bIconic)
//      {
//
//         display_previous();
//
//      }
//      else
//      {
//
//         frame_occlude();
//
//      }


   }


   void interaction::frame_restore()
   {

      if (notify_icon())
      {

         set_tool_window(false);

      }

      order_top();

      if (!is_window_screen_visible())
      {

         frame_experience_restore(e_activation_set_foreground);

      }
      else
      {

         display(e_display_normal, e_activation_set_foreground);

      }

   }


   void interaction::frame_occlude()
   {

      if (notify_icon())
      {

         set_tool_window();

         hide();

      }
      else
      {

         display(e_display_iconic);

      }

   }


   void interaction::frame_toggle_restore(bool bDisplayPreviousOnRestore)
   {

      bool bWindowVisible = is_window_visible()
         && has_graphical_output_purpose();

      double dOccludedOpaqueRate = _001GetTopLeftWeightedOccludedOpaqueRate();

      bool bIconic = layout().is_iconic();

      if (!bWindowVisible || dOccludedOpaqueRate > 0.025 || bIconic)
      {

         if (!has_graphical_output_purpose())
         {

            add_graphical_output_purpose(this, ::graphics::e_output_purpose_screen);

         }

         if (bDisplayPreviousOnRestore)
         {

            display_previous();

         }
         else
         {

            frame_restore();

         }

      }
      else
      {

         frame_occlude();

      }

      set_need_redraw();

      post_redraw();

      //return success;

   }


   void interaction::display_previous_restore()
   {

      throw ::interface_only();

   }


   void interaction::input_client_rectangle(::rectangle_i32 & rectangle, enum_layout elayout)
   {

      rectangle = this->rectangle(elayout);

   }


   //   void interaction::raw_rectangle(::rectangle_i32 & rectangle, enum_layout elayout)
   //   {
   //
   //      const_layout().state(elayout).raw_rectangle(rectangle);
   //
   //   }


   ::rectangle_i32 interaction::raw_rectangle(enum_layout elayout)
   {

      auto r = const_layout().state(elayout).raw_rectangle();

      return r;

   }


   //   void interaction::this->rectangle(::rectangle_i32 & rectangle, enum_layout elayout)
   //   {
   //
   //      raw_rectangle(rectangle);
   //
   //      rectangle += get_parent_accumulated_scroll();
   //
   //   }


   ::rectangle_i32 interaction::rectangle(enum_layout elayout)
   {

      auto r = raw_rectangle(elayout);

      r += get_accumulated_scroll();

      return r;

   }


   ::collection::index interaction::best_monitor(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                   ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleSample;

      //auto pwindowing = windowing();

      //auto pdisplay = pwindowing->display();

      if (window() && (eactivation & e_activation_under_mouse_cursor || rectangle.is_null()))
      {

         if (windowing()->display()->has_readily_gettable_absolute_pointer_position())
         {

            ::point_i32 pointCursor = windowing()->display()->get_mouse_cursor_position();

            rectangleSample.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

         }
         else
         {

            warning() << "This windowing system !is_absolute_pointer_position_readily_gettable(). Is there a specific flag to set at window creation for enabling e_activation_under_mouse_cursor?";

            //throw ::exception(todo,
            //             "The window may not be visible yet so no mouse position in it."
            //             "Is there reliable cross platform to get pointer position, "
            //             "or maybe at least just make this feature work in platforms that "
            //             "supports getting pointer position globally?");

         }

      }
      else if (rectangle.is_set())
      {

         rectangleSample = rectangle;

      }
      else
      {

         window_rectangle(rectangleSample);

      }

      ::rectangle_i32 rectangleNew;

      ::collection::index iMatchingMonitor = -1;

      if (get_parent() != nullptr)
      {

         rectangleNew = get_parent()->rectangle();

         iMatchingMonitor = 0;

      }
      else
      {

         if (m_bWorkspaceFullScreen)
         {

            iMatchingMonitor = get_best_workspace(&rectangleNew, rectangleSample);

         }
         else
         {

            auto pwindowing = windowing();

            auto pdisplay = pwindowing->display();

            iMatchingMonitor = pdisplay->get_best_monitor(&rectangleNew, rectangleSample);

         }

      }

      if (bSet && rectangleNew.is_set() && iMatchingMonitor >= 0)
      {

         information() << "interaction::bestmonitor (" << rectangleNew.left() << ", " << rectangleNew.top() << ", "
            << rectangleNew.right() << ", " << rectangleNew.bottom() << ") activation " << (i32)eactivation;

         order(zorderParam);

         place(rectangleNew);

         set_display(e_display_full_screen);

         set_activation(eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   ::rectangle_i32 interaction::outer_frame()
   {

      return this->raw_rectangle();

   }


   ::collection::index interaction::best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                     ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         window_rectangle(rectangleWindow);

      }

      ::rectangle_i32 rectangleZoomedWindowSite{};

      ::collection::index iMatchingMonitor = -1;

      if (const_layout().window().m_edisplay == e_display_zoomed)
      {

         rectangleZoomedWindowSite = window()->get_window_rectangle();

      }
      else
      {

         ::rectangle_i32 rectangleMonitor;

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         auto pdisplay = pwindowing->display();

         iMatchingMonitor = pdisplay->get_best_monitor(&rectangleMonitor, rectangleWindow, eactivation, this);

         pdisplay->get_zoomed_window_site(iMatchingMonitor, rectangleZoomedWindowSite);

      }

      if (bSet && (!::is_empty(rectangle) || iMatchingMonitor >= 0))
      {

#if !MOBILE_PLATFORM

         if (iMatchingMonitor >= 0 && rectangleZoomedWindowSite.bottom() > 0)
         {

            if (rectangleZoomedWindowSite.bottom() > rectangleZoomedWindowSite.bottom() - 2)
            {

               rectangleZoomedWindowSite.bottom() = rectangleZoomedWindowSite.bottom() - 2;

            }

         }

#endif

         order(zorderParam);

         place(rectangleZoomedWindowSite);

         //display(e_display_zoomed, eactivation | e_activation_display_change);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleZoomedWindowSite;

      }

      //if(const_layout().window().m_edisplay != e_display_zoomed)
      //{

      //   if (is_top_level())
      //   {

      //      auto pwindowThis = window();

      //      pwindowThis->window_maximize();

      //   }

      //}

      return iMatchingMonitor;

   }


   ::collection::index
      interaction::get_zoneing(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleParam, ::e_display edisplay)
   {

      if (!is_docking_appearance(edisplay))
      {

         return -1;

      }

      ::rectangle_i32 rectangleWorkspace;

      ::collection::index iWorkspace = get_best_workspace(&rectangleWorkspace, rectangleParam);

      if (iWorkspace < 0 || rectangleWorkspace.is_empty())
      {

         return -1;

      }

      if (rectangleParam.is_set())
      {

         *prectangle = rectangleParam;

      }
      else
      {

         auto point = rectangleWorkspace.center();

         ::top_left(*prectangle) = point;

         ::bottom_right(*prectangle) = point;

      }

      auto sizeMinimum = get_window_minimum_size();

      if (edisplay & ::e_display_top)
      {

         prectangle->move_top_to(rectangleWorkspace.top());

         if (::height(*prectangle) < sizeMinimum.cy())
         {

            prectangle->bottom() = prectangle->top() + sizeMinimum.cy();

         }

      }

      if (edisplay & ::e_display_bottom)
      {

         prectangle->move_bottom_to(rectangleWorkspace.bottom());

         if (::height(*prectangle) < sizeMinimum.cy())
         {

            prectangle->top() = prectangle->bottom() - sizeMinimum.cy();

         }

      }

      if (edisplay & ::e_display_left)
      {

         prectangle->move_left_to(rectangleWorkspace.left());

         if (::width(*prectangle) < sizeMinimum.cx())
         {

            prectangle->right() = prectangle->left() + sizeMinimum.cx();

         }

      }

      if (edisplay & ::e_display_right)
      {

         prectangle->move_right_to(rectangleWorkspace.right());

         if (::width(*prectangle) < sizeMinimum.cx())
         {

            prectangle->left() = prectangle->right() + sizeMinimum.cx();

         }

      }

      return iWorkspace;

   }


   ::e_display interaction::initial_restore_display()
   {

      return e_display_normal;

   }


   ::collection::index interaction::get_preferred_restore(::rectangle_i32 & rectWorkspace)
   {

      return -1;

   }


   bool interaction::calculate_window_rectangle_in_main_monitor(::rectangle_i32 & rectangle,
                                                               const ::rectangle_f64 & rectangleOptionalRateOrSize)
   {

      ::rectangle_f64 rectangleRate(rectangleOptionalRateOrSize);

      ::rectangle_i32 rectangleMainMonitor;

      auto psession = get_session();

      auto puser = user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::collection::index iMainMonitor = pdisplay->get_main_monitor(rectangleMainMonitor);

      if (iMainMonitor < 0)
      {

         return false;

      }

      ::rectangle_i32 rectangleWindow;

#if MOBILE_PLATFORM

      rectangleWindow = rectangleMainMonitor;

#else

      if (rectangleRate.is_empty())
      {

         rectangleRate.set_dimension(100, 100, 800, 400);

      }
      else if (fabs(rectangleRate.left()) < 10.0
               && fabs(rectangleRate.right()) < 10.0
               && fabs(rectangleRate.bottom()) < 10.0
               && fabs(rectangleRate.top()) < 10.0)
      {

         rectangleRate *= rectangle_f64(rectangleMainMonitor.width(), rectangleMainMonitor.height(),
                                        rectangleMainMonitor.width(), rectangleMainMonitor.height());

      }

      rectangleWindow = rectangleRate;

      rectangleWindow += rectangleMainMonitor.top_left();

#endif

      rectangle = rectangleWindow;

      return true;

   }


   ::collection::index
      interaction::calculate_broad_and_compact_restore(::rectangle_i32 * prectWorkspace, const ::size_i32 & sizeMinParam,
                                                       const ::rectangle_i32 & rectangleHintParam)
   {

      ::rectangle_i32 rectangleHint(rectangleHintParam);

      if (rectangleHint.is_empty())
      {

         debug() << "calculate_broad_and_compact_restore rHint is empty";

         rectangleHint = this->screen_rectangle(::user::e_layout_lading);

      }

      debug() << "calculate_broad_and_compact_restore rHint : " << rectangleHint;

      ::size_i32 sizeMin(sizeMinParam);

      if (sizeMin.is_empty())
      {

         debug() << "calculate_broad_and_compact_restore sizeMin is empty";

         sizeMin = this->get_window_minimum_size();

      }

      debug() << "calculate_broad_and_compact_restore sizeMin : " << sizeMin;

      ::rectangle_i32 rectangleWorkspace;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::collection::index iMatchingWorkspace = pdisplay->get_best_workspace(&rectangleWorkspace, rectangleHint);

      if (iMatchingWorkspace >= 0)
      {

         debug() << "calculate_broad_and_compact_restore found best workspace : " << iMatchingWorkspace;

         ::size_i32 sizeNormal = sizeMin.maximum(rectangleWorkspace.size() * 3 / 5);

         ::size_i32 sizeMinimumBroad = sizeMin.maximum(rectangleWorkspace.size() * 7 / 10);

         auto rectangleStoredBroad = get_window_broad_stored_rectangle();

         if (rectangleStoredBroad.size() >= sizeMinimumBroad
             && rectangleStoredBroad.size() <= rectangleWorkspace.size())
         {

            m_rectangleRestoreBroad = rectangleStoredBroad;

         }
         else
         {

            m_rectangleRestoreBroad.set_size(sizeMin.maximum(rectangleWorkspace.size() * 4 / 5));

            m_rectangleRestoreBroad.move_to(rectangleWorkspace.size() / 10);

         }

         information() << "calculate_broad_and_compact_restore restore broad : " << m_rectangleRestoreBroad;

         ::size_i32 sizeMaximumCompact = sizeMin.maximum(rectangleWorkspace.size() * 5 / 10);

         auto rectangleStoreCompact = get_window_compact_stored_rectangle();

         if (rectangleStoreCompact.size() >= sizeMin
             && rectangleStoreCompact.size() <= sizeMaximumCompact)
         {

            m_rectangleRestoreCompact = rectangleStoreCompact;

         }
         else
         {

            m_rectangleRestoreCompact.set_size(sizeMin.maximum(rectangleWorkspace.size() * 2 / 5));

            m_rectangleRestoreCompact.move_to(rectangleWorkspace.size() / 10);

         }

         debug() << "calculate_broad_and_compact_restore restore compact : " << m_rectangleRestoreCompact;

         if (::is_set(prectWorkspace))
         {

            *prectWorkspace = rectangleWorkspace;

            debug() << "calculate_broad_and_compact_restore worspace : " << rectangleWorkspace;

         }

      }
      else
      {

         information() << "calculate_broad_and_compact_restore no matching workspace";

      }

      return iMatchingWorkspace;

   }


   //void interaction::reset_window_state()
   //{

   //   m_statePrevious2.reset();
   //   m_stateRequest2.reset();
   //   m_stateProcess2.reset();
   //   m_state2.reset();
   //   m_stateWindow3.reset();
   //   m_windowdisplayandlayout.reset();
   //   m_windowdisplayandlayoutStore.reset();

   //}


   ::collection::index interaction::make_zoneing(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                   ::e_display * pedisplay, ::e_activation eactivation, ::zorder zorderParam)
   {

      if (pedisplay == nullptr || !is_docking_appearance(*pedisplay))
      {

         return best_zoneing(prectangle, rectangle, bSet, pedisplay, eactivation, zorderParam);


      }

      ::rectangle_i32 rectangleWindow;

      if (is_empty(rectangle))
      {

         window_rectangle(rectangleWindow);

      }
      else
      {

         rectangleWindow = rectangle;

      }

      ::rectangle_i32 rectangleNew;

      ::collection::index iMatchingMonitor = get_zoneing(&rectangleNew, rectangleWindow, *pedisplay);

      if (bSet && !is_empty(rectangleNew) && iMatchingMonitor >= 0)
      {

         _synchronous_lock slUserMutex(synchronization());

         order(zorderParam);

         place(rectangleNew);

         display(*pedisplay, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   ::collection::index interaction::get_best_zoneing(::e_display & edisplay, ::rectangle_i32 * prectangle,
                                       const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
   {

      edisplay = layout().layout().display();

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      if (rectangleRequest.is_empty())
      {

         return pdisplay->_get_best_zoneing(&edisplay, prectangle, this->screen_rectangle(e_layout_lading), bPreserveSize);

      }
      else
      {

         return pdisplay->_get_best_zoneing(&edisplay, prectangle, rectangleRequest, bPreserveSize);

      }

   }


   ::collection::index interaction::get_best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle,
                                         ::e_activation eactivation)
   {

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      return pdisplay->get_best_workspace(prectangle, rectangle, eactivation, this);

   }


   ::collection::index
      interaction::get_best_monitor(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle,
                                    ::e_activation eactivation)
   {

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      return pdisplay->get_best_monitor(prectangle, rectangle, eactivation, this);

   }


   ::collection::index interaction::best_zoneing(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                   ::e_display * pedisplay, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::e_display edisplay;

      if (pedisplay == nullptr)
      {

         pedisplay = &edisplay;

      }

      *pedisplay = layout().layout().display();

      ::rectangle_i32 rectangleNew;

      ::collection::index iMatchingMonitor;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      if (rectangle.is_set())
      {

         iMatchingMonitor = pdisplay->_get_best_zoneing(pedisplay, &rectangleNew, rectangle);

      }
      else
      {

         iMatchingMonitor = get_best_zoneing(*pedisplay, &rectangleNew);

      }

      if (bSet && (!is_empty(rectangle) || iMatchingMonitor >= 0))
      {

         _synchronous_lock slUserMutex(synchronization());

         order(zorderParam);

         place(rectangleNew);

         display(*pedisplay, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;


      }

      return iMatchingMonitor;

   }


   /// the rectangle parameter indicates to the function
   /// which monitor or monitors the window restore should
   /// be positioned at.
   ::collection::index interaction::good_restore(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                   ::e_activation eactivation, ::zorder zorderParam, ::e_display edisplay)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

         information() << "interaction::good_restore using rectangle parameter : " << rectangleWindow;

      }
      else
      {

         window_rectangle(rectangleWindow);

         information() << "interaction::good_restore getting window_rectangle : " << rectangleWindow;

      }

      ::rectangle_i32 rectangleNew;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::collection::index iMatchingMonitor = pdisplay->get_good_restore(&rectangleNew, rectangleWindow, this, edisplay);

      if (bSet)
      {

         {

            //lock_sketch_to_design lockLadingToLayout(this);

            order(zorderParam);

            if (rectangleNew.is_set() && iMatchingMonitor >= 0)
            {

               place(rectangleNew);

               ///set_restored_rectangle(rectangleNew);

               //display(edisplay, eactivation);

               set_display(edisplay);

               set_activation(eactivation);

               information() << "interaction::good_restore : " << rectangleNew;
               information() << "interaction::good_restore : " << edisplay;

            }
            else
            {

               place(rectangleWindow);

               set_display(e_display_normal);

               set_activation(eactivation);

            }

            set_need_redraw();

         }

         post_redraw();

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      if (is_top_level())
      {

         auto pwindowThis = window();

         pwindowThis->window_restore();

      }

      return iMatchingMonitor;

   }


   void interaction::create_window()
   {

      ::pointer < ::user::thread > puserthread;

      if (m_ewindowflag & e_window_flag_satellite_window)
      {

         if (m_puserinteractionOwner)
         {

            puserthread = m_puserinteractionOwner->user_thread();

         }

      }

      if (!puserthread)
      {

         puserthread = create_user_thread();

      }

      auto pwindow = acme_windowing_window();

      pwindow->set_user_interaction(this);

      pwindow->set_user_thread(puserthread);

      ::pointer<::user::graphics_thread> pusergraphicsthread;

      if (is_graphical())
      {

         pusergraphicsthread = create_user_graphics_thread();

         //auto pusersystem = m_puserinteraction->m_pusersystem;

         //if (pusersystem)
         //{

         //   auto prequest = pusersystem->m_prequest;

         //   if (prequest)
         //   {

         //      information() << "pgraphicsthread->m_eventReady.ResetEvent();";

         //      pgraphicsthread->m_eventReady.ResetEvent();

         //      prequest->m_procedureaOnFinishRequest.add(
         //         [this, pgraphicsthread]()
         //         {

         //            information() << "pgraphicsthread->m_eventReady.SetEvent();";

         //            pgraphicsthread->m_eventReady.SetEvent();

         //         });

         //   }

         //}

         pwindow->set_user_graphics_thread(pusergraphicsthread);

      }

      puserthread->send([this]()
         {

            _create_window();

         });

   }


   void interaction::_create_window()
   {

      auto pwindow = window();

      if (m_bMessageWindow)
      {

         pwindow->create_message_queue(this, m_strName);

      }
      else
      {

         pwindow->create_window();

      }

   }


   void interaction::on_create_window_object()
   {

      ::user::interaction_base::on_create_window_object();

      ::pointer < ::windowing::window > pwindow = m_pacmewindowingwindow;

      if (pwindow)
      {

         pwindow->m_puserinteraction = this;

      }

   }


   ::pointer < ::user::thread > interaction::create_user_thread()
   {

      auto puserthread = __create < ::user::thread >();

      puserthread->initialize_user_thread(this);

      puserthread->branch_synchronously();

      application()->add_task(puserthread);

      return puserthread;


   }


   ::pointer < ::user::graphics_thread > interaction::create_user_graphics_thread()
   {

      auto pusergraphicsthread = __create < ::user::graphics_thread >();

      pusergraphicsthread->initialize_graphics_thread(this);

      //pusergraphicsthread->branch_synchronously();

      //add_task(pusergraphicsthread);

      return pusergraphicsthread;

   }


   void interaction::create_message_queue(const ::string & strName)
   {

      //if (is_window())
      //{

      //   start_destroying_window();

      //}

      ////try
      ////{

      ////m_bUserElementOk = true;

      ////window() = __create<interaction_impl>();

      //if (!window())
      //{

      //   //m_bUserElementOk = false;

      //   throw ::exception(error_no_memory);

      //}

      m_bMessageWindow = true;

      m_strName = strName;

      create_window();

      //window()->m_puserinteraction = this;

      //m_pdescriptor.defer_create(this);

      //window()->create_message_queue(this, lpszName);

      //window()->create_message_queue(this, strName);
      //{

      //   //m_threadptra.erase_all();

      m_bUserElementOk = true;

      //m_pacmewindowingwindow.release();

     //return;

      //throw ::exception(error_failed);

   //}

   //}
   //catch (...)
   //{

   //   m_bUserElementOk = false;

   //   return false;

   //}

   //return true;

   }



   ::collection::index interaction::good_iconify(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet,
                                   ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         window_rectangle(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      ::collection::index iMatchingMonitor = pdisplay->get_good_iconify(&rectangleNew, rectangleWindow);

      if (bSet && (!::is_empty(rectangleNew) || iMatchingMonitor >= 0))
      {

         _synchronous_lock slUserMutex(synchronization());

         display(e_display_iconic, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      if (is_top_level())
      {

         auto pwindowThis = window();

         pwindowThis->window_minimize();

      }

      return iMatchingMonitor;

   }


   ::collection::index
      interaction::good_move(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation,
                             ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         window_rectangle(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      ::collection::index iMatchingMonitor = pdisplay->get_good_move(&rectangleNew, rectangleWindow, this);

      if (!is_empty(rectangleNew) || iMatchingMonitor >= 0)
      {

         order(zorderParam);

         place(rectangleNew);

         if (equivalence_sink(layout().lading().display()) != e_display_normal
             || equivalence_sink(layout().layout().display()) != e_display_normal)
         {

            display(e_display_normal, eactivation);

         }

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   atom interaction::GetDlgCtrlId() const
   {

      return m_atom;

   }


   atom interaction::SetDlgCtrlId(const atom & atom)
   {

      m_atom = atom;

      return m_atom;

   }


   //#ifdef WINDOWS_DESKTOP
   //
   //
   //   bool interaction::open_clipboard()
   //   {
   //
   //      if (!window())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return window()->open_clipboard();
   //
   //   }
   //
   //
   //   bool interaction::close_clipboard()
   //   {
   //
   //      if (!window())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return window()->close_clipboard();
   //
   //   }
   //
   //
   //#endif


   void interaction::get_rect_normal(::rectangle_i32 * prectangle)
   {

      //return

      //window()->get_rect_normal(prectangle);

   }


   scroll_bar * interaction::get_scroll_bar_x()
   {

      return nullptr;

   }


   scroll_bar * interaction::get_scroll_bar_y()
   {

      return nullptr;

   }


   scroll_state interaction::get_scroll_state_x(::user::enum_layout elayout)
   {

      return {};

   }


   scroll_state interaction::get_scroll_state_y(::user::enum_layout elayout)
   {

      return {};

   }


   void interaction::set_scroll_state_x(const scroll_state & scrollstate, ::user::enum_layout elayout)
   {

   }


   void interaction::set_scroll_state_y(const scroll_state & scrollstate, ::user::enum_layout elayout)
   {

   }


   //void interaction::offset_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   void interaction::offset_context_offset(const ::size_f64 & size, ::user::enum_layout elayout)
   {

      auto pointOffset = get_context_offset(elayout);

      pointOffset += size;

      set_context_offset(pointOffset, elayout);

   }


   //void interaction::offset_context_offset_x(::draw2d::graphics_pointer & pgraphics, ::f64 cx)
   void interaction::offset_context_offset_x(::f64 cx, ::user::enum_layout elayout)
   {

      auto x = get_context_offset_x(elayout);

      x += cx;

      set_context_offset_x(x, elayout);

   }


   //   void interaction::offset_context_offset_y(::draw2d::graphics_pointer & pgraphics, int y)
   void interaction::offset_context_offset_y(::f64 cy, ::user::enum_layout elayout)
   {

      auto y = get_context_offset_y(elayout);

      y += cy;

      set_context_offset_y(y, elayout);

   }



   //void interaction::set_context_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   void interaction::set_context_offset(const ::point_f64 & pointOffset, ::user::enum_layout elayout)
   {

      //auto point = pointOffset;

      ////if (pointOffset == (m_pointScroll + m_pointDragScroll))
      //if (point == get_context_offset(elayout))
      //{

      //   return;

      //}

      //constrain_context_offset(point, elayout);
      ////{

      ////   return;

      ////}

      //m_pointScroll = pointOffset;

      on_change_context_offset(elayout);

   }


   void interaction::on_change_context_offset(::user::enum_layout elayout)
   {

      m_bClipRectangle = false;

      set_reposition();

      layout_scroll_bar(elayout);

      m_bContextOffsetLadingToLayout = true;

   }


   void interaction::constrain_context_offset(point_f64 & point, ::user::enum_layout elayout)
   {

      //if (point == m_pointScroll)
      //{

      //   return false;

      //}

      //return true;

   }


   //void interaction::set_context_offset_x(::draw2d::graphics_pointer & pgraphics, int x)
   //{

   //   set_context_offset(pgraphics, x, (::i32)get_context_offset().y());

   //}


   //void interaction::set_context_offset_y(::draw2d::graphics_pointer & pgraphics, int y)
   //{

   //   set_context_offset(pgraphics, (::i32)get_context_offset().x(), y);

   //}


   //void interaction::on_context_offset_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //   ////set_need_redraw();

   //   //set_reposition();

   //}


   point_f64 interaction::get_context_offset(::user::enum_layout elayout)
   {

      //::point_i32 point = m_pointScroll + m_pointDragScroll;
      //::point_i32 point = m_pointScroll;

      //return point;

      return {};

   }


   ::f64 interaction::get_context_offset_x(::user::enum_layout elayout)
   {

      //::point_i32 point = m_pointScroll + m_pointDragScroll;
      //::point_i32 point = m_pointScroll;

      //return point;

      return {};

   }


   ::f64 interaction::get_context_offset_y(::user::enum_layout elayout)
   {

      //::point_i32 point = m_pointScroll + m_pointDragScroll;
      //::point_i32 point = m_pointScroll;

      //return point;

      return {};

   }


   size_f64 interaction::get_total_size(::user::enum_layout elayout)
   {

      auto rectangleX = this->rectangle();

      return rectangleX.size();

   }


   void interaction::set_total_size(const ::size_f64 & size, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }


   void interaction::set_page_size(const ::size_f64 & size, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }


   //void interaction::set_context_offset(const ::point_f64 & point, ::user::enum_layout elayout)
   //{

   //   throw ::interface_only();

   //}


   void interaction::set_scroll_tracking_x(::f64 x, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }


   void interaction::set_scroll_tracking_y(::f64 x, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }



   void interaction::set_context_offset_x(::f64 x, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }


   void interaction::set_context_offset_y(::f64 x, ::user::enum_layout elayout)
   {

      throw ::interface_only();

   }


   void interaction::on_would_change_total_size(::user::enum_layout elayout)
   {


   }


   void interaction::on_change_scroll_state(::user::enum_layout elayout)
   {

   }


   //void interaction::on_context_offset_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


   size_f64 interaction::get_page_size(::user::enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      return rectangleX.size();

   }


   point_f64 interaction::get_ascendant_context_offset()
   {

      ::pointer<::user::interaction> puser = get_parent();

      point_f64 point;

      while (puser.is_set())
      {

         point += puser->get_context_offset();

         puser = puser->get_parent();

      }

      return point;

   }


   void interaction::get_margin_rect(::rectangle_i32 * prectMargin)
   {

      prectMargin->left() = 0;

      prectMargin->top() = 0;

      prectMargin->right() = 0;

      prectMargin->bottom() = 0;


   }


   int interaction::get_final_scroll_bar_x_thickness(::user::enum_layout elayout)
   {

      return 0;

   }


   int interaction::get_final_scroll_bar_y_thickness(::user::enum_layout elayout)
   {

      return 0;

   }


   bool interaction::is_system_message_window()
   {

      return false;

   }


   point_f64 interaction::get_parent_context_offset()
   {

      ::user::interaction * puser = get_parent();

      if (puser == nullptr)
      {

         return {};

      }

      ::point_f64 pointParentAccumulated;

      if (puser != NULL)
      {

         pointParentAccumulated = puser->get_context_offset();

         pointParentAccumulated += puser->get_parent_context_offset();

      }

      return pointParentAccumulated;

   }


   //   bool interaction::set(::draw2d::graphics_pointer & pgraphics, e_font efont)
   //   {
   //
   //      return ::user::style::set(pgraphics, efont, this);
   //
   //   }


   //::user::style * interaction::parent_userstyle()
   //{

   //   ::user::interaction * puserinteractionParent = get_parent();

   //   if (puserinteractionParent == nullptr)
   //      return nullptr;

   //   return puserinteractionParent->userstyle();

   //}

   void interaction::on_message_show_window(::message::message * pmessage)
   {

      ::pointer<::message::show_window> pshowwindow(pmessage);

      bool bShowWindow = pshowwindow->m_bShow;

      if (!bShowWindow
         || layout().layout().is_screen_visible()
          || layout().layout().m_edisplay == e_display_iconic)
      {

         //information() << "on_message_show_window (A)";

         if (::type(this).name().contains("main_frame"))
         {

            // information() << "on_message_show_window main_frame (A)";

         }

         auto menua = m_menua;

         for (auto & pmenu : menua)
         {

            pmenu->hide();

            pmenu->set_need_redraw();

            pmenu->post_redraw();

         }

         if (m_puserinteractionpointeraOwned)
         {

            for (auto & puserprimitiveOwned : m_puserinteractionpointeraOwned->interactiona())
            {

               ::pointer < ::user::interaction > puserinteractionOwned = puserprimitiveOwned;

               auto edisplayOwnedBeforeHidden = puserinteractionOwned->const_layout().design().m_edisplay;

               puserinteractionOwned->m_edisplayOwnedBeforeHidden = edisplayOwnedBeforeHidden;

               puserinteractionOwned->hide();

               puserinteractionOwned->set_need_redraw();

               puserinteractionOwned->post_redraw();

            }

         }

      }
      else
      {

         //information() << "on_message_show_window (B)";

         if (::type(this).name().contains("main_frame"))
         {

            //information() << "on_message_show_window main_frame (B)";

         }

         auto menua = m_menua;

         for (auto & pmenu : menua)
         {

            try
            {

               pmenu->display();

               pmenu->set_need_redraw();

               pmenu->post_redraw();

            }
            catch (...)
            {

            }

         }

         if (m_puserinteractionpointeraOwned)
         {

            for (auto & puserprimitiveOwned : m_puserinteractionpointeraOwned->interactiona())
            {

               ::pointer < ::user::interaction > puserinteractionOwned = puserprimitiveOwned;

               auto edisplayOwnedBeforeHidden = puserinteractionOwned->m_edisplayOwnedBeforeHidden;

               puserinteractionOwned->display(edisplayOwnedBeforeHidden, e_activation_no_activate);

               puserinteractionOwned->set_need_redraw();

               puserinteractionOwned->post_redraw();

            }

         }

      }

      //      string strType = ::type(this).name();
      //
      //      if(strType.contains("main_frame"))
      //      {
      //
      //         informationf("main_frame interaction::on_message_show_window\n");
      //
      //      }

      //SW_OTHERUNZOOM
      //4
      //The window is being uncovered because a maximize window was restored or minimized.
      //SW_OTHERZOOM
      //2
      //The window is being covered by another window that has been maximized.
      //SW_PARENTCLOSING
      //1
      //The window's owner window is being minimized.
      //SW_PARENTOPENING
      //3
      //The window's owner window is being restored.

      //_synchronous_lock synchronouslock(mutex_children());

      //if(m_uiptraChild.has_element())
      //{

      //   auto uiptra = m_uiptraChild;

      //   if(pshowwindow->m_bShow)
      //   {

      //      for(auto & pui : uiptra)
      //      {

      //         try
      //         {

      //            if (pui && pui->is_this_visible())
      //            {

      //               pui->send_message(e_message_show_window, 1, SW_PARENTOPENING);

      //            }

      //         }
      //         catch (...)
      //         {

      //         }

      //      }

      //   }
      //   else
      //   {

      //      for (::collection::index i = 0; i < uiptra.get_size(); i++)
      //      {

      //         try
      //         {

      //            if (uiptra[i].is_set() && uiptra[i]->is_this_visible())
      //            {

      //               uiptra[i]->send_message(e_message_show_window, 0, SW_PARENTCLOSING);

      //            }

      //         }
      //         catch (...)
      //         {

      //         }

      //      }

      //   }

      //}

   }


   ::graphics::graphics * interaction::get_window_graphics()
   {

      //if (window() == nullptr)
      //{

      //   return nullptr;

      //}

      if (this != top_level())
      {

         return nullptr;

      }

      return window()->get_window_graphics();

   }


   ::draw2d::graphics_pointer interaction::get_internal_draw2d_graphics()
   {

      auto pinteractionHost = get_wnd();

      if (::is_null(pinteractionHost))
      {

         informationf("interaction::get_internal_draw2d_graphics ::is_null(pinteractionHost)");

         return nullptr;

      }

      auto pwindow = pinteractionHost->windowing_window();

      if (::is_null(pwindow))
      {

         informationf("interaction::get_internal_draw2d_graphics ::is_null(pwindow)");

         return nullptr;

      }

      auto & pdraw2dgraphics = pwindow->m_pdraw2dgraphics;

      defer_graphics(pdraw2dgraphics);

      return pdraw2dgraphics;

   }


   bool interaction::is_composite()
   {

      //if (window() == nullptr)
      //{

      //   return true; // optimistic response, assume always true alpha blendable

      //}

      return window()->is_composite();

   }


   size_i32 interaction::get_window_minimum_size()
   {

      return {};

   }


   ::rectangle_i32 interaction::get_window_normal_stored_rectangle()
   {

      return this->raw_rectangle();

   }


   ::rectangle_i32 interaction::get_window_broad_stored_rectangle()
   {

      return m_rectangleRestoreBroad;

   }


   ::rectangle_i32 interaction::get_window_compact_stored_rectangle()
   {

      return m_rectangleRestoreCompact;

   }


   void interaction::set_window_normal_stored_rectangle(const ::rectangle_i32 & rectangle)
   {


   }


   // up down target

   //UpDownTarget::UpDownTarget()
   //{
   //   m_eupdowntargettype = type_normal_frame;
   //}

   void interaction::UpDownTargetAttach(::user::interaction * pupdown)
   {

      bool bAttached = false;

      pupdown->m_eupdown = e_updown_down;

      try
      {

         if (OnUpDownTargetAttach(pupdown))
         {

            bAttached = true;

         }

      }
      catch (...)
      {

      }

      if (!bAttached)
      {

         pupdown->m_eupdown = e_updown_none;

      }

   }


   void interaction::UpDownTargetDetach(::user::interaction * pupdown)
   {

      bool bDetached = false;

      pupdown->m_eupdown = e_updown_up;

      try
      {

         if (OnUpDownTargetDetach(pupdown))
         {

            bDetached = true;

         }

      }
      catch (...)
      {

      }

      if (!bDetached)
      {

         pupdown->m_eupdown = e_updown_none;

      }

   }


   bool interaction::OnUpDownTargetAttach(::user::interaction * pupdown)
   {

      return false;

   }


   bool interaction::OnUpDownTargetDetach(::user::interaction * pupdown)
   {

      return false;

   }


   void interaction::keyboard_focus_OnKeyDown(::message::message * pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_tab)
      {

         auto ptopic = create_topic(::id_tab_key);

         ptopic->m_puserelement = dynamic_cast <::user::interaction *> (this);
         ptopic->m_actioncontext = ::e_source_user;

         route(ptopic);

      }

   }


   bool interaction::get_child(::pointer<::user::interaction> & pinteraction)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->get_child(pinteraction);

   }


   bool interaction::rget_child(::pointer<::user::interaction> & pinteraction)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->rget_child(pinteraction);

   }


   enum_input_type interaction::preferred_input_type()
   {

      return e_input_type_none;

   }


   //::user::interaction_base * interaction::get_keyboard_focus()
   //{

   //   if (window() == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return window()->get_keyboard_focus();

   //}


   //void interaction::set_keyboard_focus(::user::interaction_base * pprimitive)
   //{

   //   auto puserinteractionHost = get_host_user_interaction();

   //   if (this == puserinteractionHost)
   //   {

   //      return pprimitive->set_keyboard_focus();

   //   }
   //   else
   //   {

   //      return puserinteractionHost->set_keyboard_focus(pprimitive);

   //   }

   //}


   //void interaction::erase_keyboard_focus(::user::interaction_base * pprimitive)
   //{

   //   auto puserinteractionHost = get_host_user_interaction();

   //   if (this == puserinteractionHost)
   //   {

   //      return window()->erase_keyboard_focus(pprimitive);

   //   }
   //   else
   //   {

   //      return puserinteractionHost->erase_keyboard_focus(pprimitive);

   //   }

   //}


   //void interaction::set_keyboard_focus()
   //{

   //   return set_keyboard_focus(this);

   //}


   //void interaction::erase_keyboard_focus()
   //{

   //   return erase_keyboard_focus(this);

   //}


   void interaction::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return;

      }

      //auto pwindow = pwindow->m_pwindow;

      //if (::is_null(pwindow))
      //{

      //   return;

      //}

      pwindowThis->m_puserinteractionToKillKeyboardFocus = pwindowThis->m_puserinteractionKeyboardFocus;


      //      if (pwindow->has_keyboard_focus())
      //      {
      //
      //         pwindow->m_puserinteractionToKillKeyboardFocus->clear_keyboard_focus(pelementGainingFocusIfAny);
      //
      //      }
      //      else
      //      {

      pwindowThis->on_final_kill_keyboard_focus();

      //}

//      auto puserinteractionHost = get_host_user_interaction();
//
//      if (this == puserinteractionHost)
//      {
//
//         ::user::primitive_impl* pwindowGainingFocusIfAny = nullptr;
//
//         if (pelementGainingFocusIfAny)
//         {
//
//            pwindowGainingFocusIfAny = pelementGainingFocusIfAny->get_primitive_impl();
//
//         }
//
//         return window()->clear_keyboard_focus(pwindowGainingFocusIfAny);
//
//      }
//      else
//      {
//
//         return puserinteractionHost->clear_keyboard_focus(pelementGainingFocusIfAny);
//
//      }

   }


   bool interaction::is_ascendant_of(::user::element * puiDescendantCandidate, bool bIncludeSelf)
   {

      if (::is_null(puiDescendantCandidate))
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of(::user::element * puiAscendantCandidate, bool bIncludeSelf)
   {

      const ::user::interaction * pinteraction = bIncludeSelf ? this : get_parent();

      while (pinteraction != nullptr)
      {

         if (pinteraction == puiAscendantCandidate)
         {

            return true;

         }

         //if(::is_null(pinteraction->m_pdescriptor))
         //{

         //   return false;

         //}

         pinteraction = pinteraction->m_puserinteractionParent;

      }

      return false;

   }


   bool interaction::is_ascendant_or_owner_of(::user::element * puiDescendantCandidate, bool bIncludeSelf)
   {

      if (puiDescendantCandidate == nullptr)
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of_or_owned_by(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of_or_owned_by(::user::element * puiAscendantCandidate, bool bIncludeSelf)
   {

      ::user::interaction * pinteraction = bIncludeSelf ? this : get_parent_or_owner();

      while (pinteraction != nullptr)
      {

         if (pinteraction == puiAscendantCandidate)
         {

            return true;

         }

         pinteraction = pinteraction->get_parent_or_owner();

      }

      return false;

   }


   void interaction::kick_queue()
   {

      post_message(e_message_null);

      //      return true;

   }


   bool interaction::is_left_button_pressed()
   {

      auto pwindowThis = window();

      return pwindowThis->m_puiLastLButtonDown == this;

   }


   void interaction::set_current_item(::item * pitem, const ::action_context & context)
   {

      if (::is_same_item(main_content().m_pitemCurrent, pitem))
      {

         return;

      }

      main_content().m_pitemCurrent = pitem;

      if (has_handler())
      {

         auto ptopic = create_topic(::id_after_change_cur_sel);

         ptopic->m_puserelement = this;

         ptopic->m_pitem = pitem;

         ptopic->m_actioncontext = context;

         route(ptopic);

         set_need_redraw();

         post_redraw();

      }

      //return success;

   }


   ::item_pointer interaction::current_item()
   {

      return main_content().m_pitemCurrent;

   }


   ::item_pointer interaction::stock_item(enum_element eelement)
   {

      auto pitem = tool().item(eelement);

      if (!pitem)
      {

         tool().add_item(__allocate::item(eelement));

         pitem = tool().item(eelement);

      }

      return pitem;

   }


   //item_pointer interaction::hover_item()
   //{

   //   return m_pitemHover;

   //}


   void interaction::show_tooltip(const ::string & str, bool bError)
   {

      //
      //
      //      if (m_ptooltip.is_null())
      //      {
      //
      //         m_ptooltip = __allocate tooltip(this);
      //
      //
      //         m_ptooltip->create_window_ex(pusersystem);
      //
      //      }
      //
      //      get_tooltip()->m_str = str;
      //
      //      get_tooltip()->m_bError = bError;
      //
      //      get_tooltip()->CalcSize();
      //
      //      if (!layout_tooltip(true))
      //      {
      //
      //         return false;
      //
      //      }

      //return true;

   }


   void interaction::ExitHelpMode()
   {

   }


   void interaction::handle(::topic * ptopic, ::context * pcontext)
   {

      //auto pevent = pmessage->m_lparam.cast < ::user::control_event >();

      //handle(ptopic, pcontext);

      if (ptopic)
      {

         if (ptopic->m_atom == ID_UPDATE)
         {

            update_impact();

         }
         else if (ptopic->m_atom == ID_INCOMING_DOCUMENT)
         {

            update_impact();

         }
         else if (ptopic->m_atom == ID_REDRAW || ptopic->m_atom == m_atom)
         {

            if (this->m_ewindowflag & ::e_window_flag_window_created)
            {

               set_need_redraw();

               post_redraw();

            }

         }
         else if (ptopic->m_atom == id_user_style_change)
         {

            if (this->m_ewindowflag & ::e_window_flag_window_created)
            {

               set_need_redraw();

               post_redraw();

            }

         }

      }

   }


   void interaction::on_after_impact_update()
   {

      set_need_redraw();

      post_redraw();

   }


   void interaction::layout_tooltip(bool bForceShow)
   {

      if (m_ptooltip.is_null())
      {

         //throw ::exception(error_wrong_state);

         return;

      }

      if (m_ptooltip->is_window_visible() && !get_wnd()->is_active_window())
      {

         hide_tooltip();

         return;

      }

      if (!bForceShow && !m_ptooltip->is_window_visible())
      {

         return;

      }

      //::size_i32 sizeTooltip = get_tooltip()->m_size;

      //::rectangle_i32 rectangleThisWindow;

      //window_rectangle(rectangleThisWindow);

      //::rectangle_i32 rectangleWindow;

      //::rectangle_i32 rectangleMonitor;

      //psession->get_best_monitor(rectangleMonitor, rectangleThisWindow);

      //rectangleWindow = rectangleThisWindow;

      //rectangleWindow.SetBottomRightSize(sizeTooltip);

      //rectangleWindow.offset(0, -sizeTooltip.cy());

      //if (rectangleWindow.top() < rectangleMonitor.top())
      //{

      //   rectangleWindow.move_top_to(rectangleThisWindow.bottom());

      //}

      //if (rectangleWindow.right() > rectangleMonitor.right())
      //{

      //   rectangleWindow.move_left_to(rectangleMonitor.right() - sizeTooltip.cx() - rectangleThisWindow.height());

      //}

      //m_ptooltip->order(e_zorder_top_most);
      //m_ptooltip->place(rectangleWindow);
      //m_ptooltip->display(e_display_normal, e_activation_no_activate);
      ////m_ptooltip->show(show_no_activate);
      ////SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOACTIVATE);

      //return true;

   }


   void interaction::hide_tooltip()
   {

      if (m_ptooltip.is_null())
      {

         return;

      }

      m_ptooltip->display(e_display_none);

      //return true;

   }


   bool interaction::frame_is_transparent()
   {

      return false;

   }


   bool interaction::has_translucency()
   {

      return true;

   }


   double interaction::get_alpha()
   {

      if (m_palphasource == nullptr)
      {

         return 1.0;

      }
      else
      {

         return m_palphasource->get_alpha(this);

      }

   }


   //   bool interaction::has_pending_graphical_update()
   //   {
   //
   //      if (has_fps_interest())
   //      {
   //
   //         return true;
   //
   //      }
   //
   //      //#ifdef APPLE_IOS
   //      //
   //      //      {
   //      //
   //      //         _synchronous_lock synchronouslock(this->synchronization());
   //      //
   //      //         for (::collection::index i = 0; i < m_uiptraChild.get_size(); i++)
   //      //         {
   //      //
   //      //            ::user::interaction * pinteraction = m_uiptraChild[i];
   //      //
   //      //            if (pinteraction)
   //      //            {
   //      //               synchronouslock.unlock();
   //      //
   //      //
   //      //               if (pinteraction->has_pending_graphical_update())
   //      //               {
   //      //
   //      //                  return true;
   //      //
   //      //               }
   //      //
   //      //               synchronouslock.lock();
   //      //
   //      //            }
   //      //
   //      //
   //      //         }
   //      //
   //      //      }
   //      //
   //      //#endif
   //
   //      if (is_window_visible())
   //      {
   //
   //         if (m_bRedrawOnVisible)
   //         {
   //
   //            return true;
   //
   //         }
   //
   //      }
   //
   //      if (!window())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      if (window()->has_pending_graphical_update())
   //      {
   //
   //         return true;
   //
   //      }
   //
   //      return false;
   //
   //   }


   void interaction::enable_transparent_mouse_events(bool bEnable)
   {

      //#ifdef WINDOWS

      _synchronous_lock synchronouslock(top_level()->synchronization());

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (is_different(pwindowThis->m_bTransparentMouseEvents, bEnable))
      {

         pwindowThis->m_bTransparentMouseEvents = bEnable;

         check_transparent_mouse_events();

      }

      //#endif

      //return true;

   }


   void interaction::check_transparent_mouse_events()
   {

#ifdef WINDOWS_DESKTOP

      auto puserinteraction = get_wnd();

      if (::is_null(puserinteraction))
      {

         return;

      }

      if (!puserinteraction->is_composite())
      {

         enable_transparent_mouse_events(false);

         return;

      }

      puserinteraction->post_message(e_message_simple_command, e_simple_command_check_transparent_mouse_events);

#endif

   }


   void interaction::redraw_add(::particle * pparticle)
   {

      window()->redraw_add(pparticle);

   }


   void interaction::redraw_erase(::particle * pparticle)
   {

      window()->redraw_erase(pparticle);

   }


   bool interaction::has_redraw()
   {

      return window()->has_redraw();

   }


   //void interaction::defer_notify_mouse_move(bool & bPointInside, point_i32 & pointLast)
   //{

   //   auto psession = get_session();

   //   if (psession->get_capture() != nullptr)
   //   {

   //      return;

   //   }

   //   ::point_i32 pointCurrent;

   //   psession->get_cursor_position(pointCurrent);

   //   if (pointCurrent != pointLast)
   //   {

   //      pointLast = pointCurrent;

   //      bPointInside = _001IsPointInside(pointCurrent);

   //      if (bPointInside || m_bMouseHover)
   //      {

   //         auto pinteraction = get_wnd();

   //         //bool bMoving = pinteraction->layout().is_moving();

   //         //bool bSizing = pinteraction->layout().is_sizing();

   //         //bool bDocking = pinteraction->window_is_docking();

   //         //bool bVoidSending = bMoving || bSizing || bDocking;;

   //         //if (bVoidSending)
   //         //{

   //         //   informationf("void sending :: defer_notify_mouse_move");

   //         //}
   //         //else
   //         {


   //            //#if !defined(LINUX)
   //            //
   //            //            get_wnd()->screen_to_client(pointCurrent);
   //            //
   //            //#endif

   //            if (bPointInside)
   //            {

   //               m_bMouseHover = true;

   //               auto pmouse = __allocate message::mouse();

   //               pmouse->m_eflagMessage += ::message::flag_synthesized;

   //               pmouse->m_atom = e_message_mouse_move;
   //               pmouse->m_playeredUserPrimitive = pinteraction;
   //               pmouse->m_point = pointCurrent;
   //               pmouse->m_bTranslated = true;

   //               pinteraction->message_handler(pmouse);

   //            }
   //            else
   //            {

   //               m_bMouseHover = false;

   //               get_impl()->mouse_hover_erase(this);

   //               send_message(e_message_mouse_leave);

   //               set_need_redraw();

   //            }

   //         }

   //      }

   //   }

   //}


   void interaction::destruct()
   {

      // If this is a "top level" or "operating system" window,
      // the operating system may keep object to this object,
      // preventing it from being fully released.
      // If the window start_destroying_window member is called in interaction::~interaction destructor,
      // derived classes from interaction::~interaction may have deleted object resources
      // that could be used to correctly destroy window, as start_destroying_window generally require
      // that the object be a full valid object before being disposed.

      destroy_window();

      ::user::interaction_base::destruct();

   }


   //   void interaction::defer_notify_mouse_move()
   //   {
   //
   //      if (get_wnd() == nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      auto psession = get_session();
   //
   //      if (psession->get_capture() != nullptr)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      ::point_i32 pointCurrent;
   //
   //      psession->get_cursor_position(pointCurrent);
   //
   //#if !defined(LINUX)
   //
   //      get_wnd()->screen_to_client(pointCurrent);
   //
   //#endif
   //
   //      get_wnd()->send_message(e_message_mouse_move, 0, pointCurrent);
   //
   //   }




   void interaction::on_after_graphical_update()
   {

      ::user::interaction_base::on_after_graphical_update();

      if (::is_set(window()))
      {

         window()->on_after_graphical_update();

      }

   }


   void interaction::_001OnDeiconify(::e_display edisplayPrevious)
   {

      if (!windowing()->is_screen_visible(edisplayPrevious))
      {

         display(::e_display_normal);

      }
      else
      {

         display(edisplayPrevious);

      }

   }


   ::e_status interaction::is_edit_delete_enabled()
   {

      return ::success_none;

   }


   bool interaction::on_edit_delete(const ::action_context & actioncontext)
   {

      //return ::success_none;

      return true;

   }


   bool interaction::on_click_generation(::item * pitem)
   {

      auto pappearance = get_appearance();

      if (pappearance)
      {

         if (pappearance->call_click())
         {

            return true;

         }

      }

      if (m_callbackOnClick)
      {

         if (m_callbackOnClick(this, pitem))
         {

            return true;

         }

      }

      {

         auto pmessageOnClick = __create_new<::message::message>();

         pmessageOnClick->m_atom = "on_click";

         route_message(pmessageOnClick);

         if (pmessageOnClick->m_bRet)
         {

            return true;

         }

      }

      return on_click(pitem);

   }


   bool interaction::on_click(::item * pitem)
   {

      if (::is_set(pitem))
      {

         if (pitem->m_item.m_eelement == ::e_element_close_button
             || pitem->m_item.m_eelement == ::e_element_close_icon)
         {

            post_message(MESSAGE_CLOSE);

            return true;

         }
         else if (pitem->m_item.m_eelement == ::e_element_switch_button
                  || pitem->m_item.m_eelement == ::e_element_switch_icon)
         {

            post_message(e_message_switch);

            return true;

         }
         else if (pitem->m_item.m_eelement == ::e_element_maximize_button
                  || pitem->m_item.m_eelement == ::e_element_maximize_icon)
         {

            information() << "clicked maximize";

            if (is_display_like_maximized())
            {

               information() << "window is like maximized - going to display e_display_normal";

               auto rectangleWindowNormalStored = this->get_window_normal_stored_rectangle();

               place(rectangleWindowNormalStored);

               display(e_display_normal);

               //               information() << "window is like maximized - going to display_previous";

               //               display_previous();

            }
            else
            {

               information() << "window isn't like maximized - going to display e_display_zoomed";

               display(e_display_zoomed);

            }

            set_need_layout();

            set_need_redraw();

            post_redraw();

            return true;

         }
         else if (pitem->m_item.m_eelement == ::e_element_minimize_button
                  || pitem->m_item.m_eelement == ::e_element_minimize_icon)
         {

            display(e_display_iconic);

            return true;

         }

      }

      return false;

   }


   bool interaction::on_right_click_generation(::item * pitem)
   {

      return on_right_click(pitem);

   }


   bool interaction::on_right_click(::item * pitem)
   {

      return false;

   }


   ::size_f64 interaction::get_size(enum_layout elayout)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, elayout);

      return rectangleWindow.size();

   }


   ::size_f64 interaction::get_client_size(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      return rectangleX.size();

   }


   int interaction::width(enum_layout elayout)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, elayout);

      return rectangleWindow.width();

   }


   int interaction::height(enum_layout elayout)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, elayout);

      return rectangleWindow.height();

   }


   int interaction::client_width(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      return rectangleX.width();

   }


   int interaction::client_height(enum_layout elayout)
   {

      auto rectangleX = this->rectangle(elayout);

      return rectangleX.height();

   }


   //   void interaction::resize_to_fit(::draw2d::graphics_pointer & pgraphics)
   //   {
   //
   //      // this default implementation doesn't need to be called by derived
   //      // classes and it has the side effect of warning at debug output log
   //      // the default resize_to_fit implementation is being called.
   //
   //      informationf("default resize_to_fit doesn't do anything\n");
   //
   //
   //   }


   void interaction::wait_redraw()
   {

      while (has_pending_redraw_flags())
      {

         system()->do_tasks();

         sleep(5_ms);

      }


   }


   bool interaction::has_pending_redraw_flags()
   {

      if (window() == nullptr)
      {

         return false;

      }

      return window()->has_pending_redraw_flags();

   }


   bool interaction::is_window_resizing()
   {

      if (::is_set(m_pdragCurrent) && m_pdragCurrent->m_pitem->m_item.m_eelement == e_element_resize)
      {

         return true;

      }

      return false;

   }


   bool interaction::is_window_repositioning()
   {

      if (::is_set(m_pdragCurrent) && m_pdragCurrent->m_pitem->m_item.m_eelement == e_element_client)
      {

         return true;

      }

      return false;

   }


   bool interaction::is_window_docking()
   {

      return false;

   }


   void interaction::set_stock_icon(enum_stock_icon estockicon)
   {

      throw ::interface_only();

   }


   enum_stock_icon interaction::get_stock_icon()
   {

      return e_stock_icon_none;

   }


   void interaction::set_bitmap_source(const string & strBitmapSource)
   {

      if (!window())
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      //auto estatus =

      window()->set_bitmap_source(strBitmapSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void interaction::clear_bitmap_source()
   {

      if (!window())
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      //auto estatus =

      window()->clear_bitmap_source();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }

   //::item interaction::hit_test(::message::mouse* pmouse->
   //{

   //   auto point = pmouse->m_point;

   //   screen_to_client()(point);

   //   point += m_ptScroll;


   //}

   //::item interaction::on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
   //{

   //   auto rectangle = this->rectangle(::e_element_client);

   //   if (!rectangle.contains(point))
   //   {

   //      return ::e_element_none;

   //   }

   //   return ::e_element_client;

   //}


   bool interaction::scroll_bar_get_client_rect(::rectangle_i32 & rectangle)
   {

      rectangle = this->rectangle();

      rectangle.right() += get_final_scroll_bar_x_thickness();

      rectangle.bottom() += get_final_scroll_bar_y_thickness();

      return true;

   }


   //   void interaction::on_calc_size(calc_size * psize)
   //   {
   //
   //      ::rectangle_i32 rectangleWindow;
   //
   //      window_rectangle(rectangleWindow);
   //
   //      psize->m_size = rectangleWindow.size();
   //
   //   }


   enum_control_type interaction::get_control_type()
   {

      return m_econtroltype;

   }


   void interaction::show_software_keyboard(::user::element * pelement)
   {

      if (get_host_user_interaction() == this)
      {

         if (::is_null(window()))
         {

            throw ::exception(error_null_pointer);

         }

         return window()->show_software_keyboard(pelement);

      }
      else
      {

         auto pwindow = get_host_user_interaction();

         if (::is_null(pwindow))
         {

            throw ::exception(error_null_pointer);

         }

         return pwindow->show_software_keyboard(pelement);

      }

   }


   void interaction::hide_software_keyboard(::user::element * pelement)
   {

      if (get_host_user_interaction() == this)
      {

         if (::is_null(window()))
         {

            throw ::exception(error_null_pointer);

         }

         return window()->hide_software_keyboard(pelement);

      }
      else
      {

         auto pwindow = get_host_user_interaction();

         if (::is_null(pwindow))
         {

            throw ::exception(error_null_pointer);

         }

         return pwindow->hide_software_keyboard(pelement);

      }

   }


   void interaction::_post(const ::procedure & procedure)
   {

      if (::is_null(user_thread()))
      {

         ::user::interaction_base::_post(procedure);

         return;

      }

      user_thread()->_post(procedure);

   }


   //
   //#ifdef WINDOWS
   //
   //
   //   strsize interaction::_009GetWindowText(wchar_t * pwsz, int n)
   //   {
   //
   //      wstring wstr(m_strWindowText);
   //
   //      n = (int)minimum(wstr.length() + 1, n);
   //
   //      wcsncpy(pwsz, wstr.c_str(), n);
   //
   //      pwsz[n - 1] = '\0';
   //
   //      return n - 1;
   //
   //   }
   //
   //
   //   strsize interaction::_009GetWindowTextLength()
   //   {
   //      wstring wstr(m_strWindowText);
   //
   //      return wstr.length();
   //
   //   }
   //
   //
   //#else
   //
   //
   //   strsize interaction::_009GetWindowText(char * psz, int n)
   //   {
   //
   //      auto strWindowText = _get_window_text();
   //
   //      strncpy(psz, strWindowText, n);
   //
   //      psz[n - 1] = '\0';
   //
   //      return n - 1;
   //
   //   }
   //
   //
   //   strsize interaction::_009GetWindowTextLength()
   //   {
   //
   //      return m_strWindowText.length();
   //
   //   }
   //
   //
   //#endif


   //   void interaction::send_procedure(const ::procedure & procedure)
   //   {
   //
   //      ::thread * pthread = get_wnd() == nullptr ? (::thread *) nullptr : get_wnd()->user_thread().m_p;
   //
   //      ::task * ptaskCurrent = ::get_task();
   //
   //      if (pthread == nullptr || pthread == ptaskCurrent)
   //      {
   //
   //         return procedure();
   //
   //      }
   //
   //      pthread->send_procedure(procedure);
   //
   //   }


   //   ::pointer< ::mutex > g_pmutexChildren;
   //
   //
   //   CLASS_DECL_AURA::pointer< ::mutex > mutex_children()
   //   {
   //
   //      return g_pmutexChildren;
   //
   //   }


   //   void initialize_children_mutex()
   //   {
   //
   //      if (!g_pmutexChildren)
   //      {
   //
   //         __raw_construct(g_pmutexChildren);
   //
   //      }
   //
   //   }
   //
   //
   //   void finalize_children_mutex()
   //   {
   //
   //      ::release(g_pmutexChildren);
   //
   //   }


   //void interaction::get_layout_rect(::rectangle_i32 * prectangle)

   //{

   //   window_rectangle(prectangle);


   //}


   /*void interaction::set_placement(const ::rectangle_i32 & rectangle)

         {

            ::rectangle_i32 rectangleFinal(rectangle);


            rectangleFinal.deflate(m_rectanglePadding);

            SetPlacement(rectangleFinal);

         }*/


         //   void interaction::prodevian_redraw(bool bUpdateBuffer)
         //   {
         //
         //      auto type = ::type(this);
         //
         //      //      if (type.name().contains("list_box"))
         //      //      {
         //      //
         //      //         informationf("prodevian_redraw list_box");
         //      //
         //      //      }
         //
         //      if (::is_null(window()))
         //      {
         //
         //         return;
         //
         //      }
         //
         //      window()->prodevian_redraw(bUpdateBuffer);
         //
         //   }


         //   void interaction::prodevian_stop()
         //   {
         //
         //      if (!window())
         //      {
         //
         //         return;
         //
         //      }
         //
         //      window()->prodevian_stop();
         //
         //   }


         //   void interaction::install_click_default_mouse_handling(::channel* pchannel)
         //   {
         //
         //      m_bDefaultClickHandling = true;
         //
         //      // this is not needed, user::interaction hooks left_button_down by default.
         //      //MESSAGE_LINK(e_message_left_button_down, pchannel, this, &interaction::on_message_left_button_down);
         //
         //      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);
         //
         //
         //#if MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG
         //
         //      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &interaction::on_message_middle_button_down);
         //      MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &interaction::on_message_middle_button_up);
         //
         //#endif
         ////      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &interaction::on_message_mouse_move);
         ////      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &interaction::on_message_mouse_leave);
         //
         //   }
         //

         //   void interaction::install_hover_default_mouse_handling(::channel* pchannel)
         //   {
         //
         //      m_bDefaultMouseHoverHandling = true;
         //
         ////      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &interaction::on_message_left_button_down);
         ////      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);
         ////      MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &interaction::on_message_middle_button_down);
         ////      MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &interaction::on_message_middle_button_up);
         //      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &interaction::on_message_mouse_move);
         //      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &interaction::on_message_mouse_leave);
         //
         //   }


         //void interaction::install_update_data_message_routing(::channel * pchannel)
         //{

         //   MESSAGE_LINK(e_message_need_load_form_data, pchannel, this, &interaction::on_message_need_load_form_data);
         //   MESSAGE_LINK(e_message_need_save_form_data, pchannel, this, &interaction::on_message_need_save_form_data);

         //}



         //   bool interaction::simple_on_control_event(::message::message* pmessage, ::enum_topic etopic)
         //   {
         //
         //      if (eevent == e_event_mouse_leave)
         //      {
         //
         //         ::pointer<interaction>pinteraction = top_child();
         //
         //         while (pinteraction != nullptr)
         //         {
         //
         //            if (pinteraction->m_bCursorInside)
         //            {
         //
         //               pinteraction->m_bCursorInside = false;
         //
         //               pinteraction->message_handler(pmessage);
         //
         //            }
         //
         //            pinteraction = pinteraction->under_sibling();
         //
         //         }
         //
         //      }
         //
         //      ::topic topic;
         //
         //      topic.m_puserinteraction = this;
         //
         //      //topic.m_atom = m_atom;
         //
         //      topic.m_atom = eevent;
         //
         //      topic.m_pmessage = pmessage;
         //
         //      route(&topic);
         //
         //      if (::is_set(pmessage))
         //      {
         //
         //         pmessage->m_bRet = topic.m_bRet;
         //
         //         if (pmessage->m_bRet)
         //         {
         //
         //            if (pmessage != nullptr)
         //            {
         //
         //               pmessage->m_lresult = 1;
         //
         //            }
         //
         //         }
         //
         //      }
         //
         //      return topic.m_bRet;
         //
         //   }


   bool interaction::is_window_enabled()
   {

      auto pparent = get_parent();

      if (::is_set(pparent))
      {

         if (!pparent->is_window_enabled())
         {

            return false;

         }

      }

      return is_this_window_enabled();

   }


   void interaction::on_message_parent_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto strType = type(this).as_string();

      information() << "interaction::on_message_parent_left_button_down : " << strType;

      if (!is_window_enabled())
      {

         return;

      }

      if (strType.contains("simple_scroll_bar"))
      {

         information() << "interaction::on_message_parent_left_button_down simple_scroll_bar";

      }

      //auto psession = get_session();

      //try
      //{

      //   if (keyboard_focus_is_focusable())
      //   {

      //      set_keyboard_focus();

      //      {

      //         psession->user()->set_mouse_focus_LButtonDown(this);

      //         //set_need_redraw();

      //         //post_redraw();

      //      }

      //   }
      //   else
      //   {

      //      clear_keyboard_focus();

      //   }

      //}
      //catch (...)
      //{

      //}

      //if ((m_bEnableHorizontalBarDragScroll && _001HasHorizontalBarDragScrolling())
      //    || (m_bEnableVerticalBarDragScroll && _001HasVerticalBarDragScrolling()))
      //{

      //   m_pointBarDragScrollLeftButtonDown = pmouse->m_point;

      //   m_bBarDragScrollLeftButtonDown = true;

      //   m_pointBarDragScrollStart = m_pointBarDragScroll;

      //   set_mouse_capture();

      //}

      auto pitemLButtonDown = update_hover(pmouse, e_zorder_front);

      if (drag_on_button_down(pitemLButtonDown))
      {

         return;

      }

      if (pmouse->m_bRet)
      {

         return;

      }

      if (pitemLButtonDown && pitemLButtonDown->m_eitemflag & ::e_item_flag_drag)
      {

         auto pwindowHost = window();

         pwindowHost->m_puiLastLButtonDown = this;

         pwindowHost->m_pitemLButtonDown = pitemLButtonDown;

         auto ptopic = create_topic(::id_left_button_down);

         ptopic->m_puserelement = this;

         ptopic->m_actioncontext.m_pmessage = pmouse;

         ptopic->m_actioncontext.add(e_source_user);

         ptopic->m_pitem = pitemLButtonDown;

         route(ptopic);

         set_mouse_capture();

         track_mouse_leave();

         pmouse->m_bRet = true;

         return;

      }

      //if(m_pdragmove && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_item.m_eelement == e_element_client)
      //{

      //   get_wnd()->show_keyboard(false);

      //   m_pdragmove->m_bLButtonDown = true;

      //   m_pdragmove->m_bDrag = false;

      //   m_pdragmove->m_pointLButtonDown = pmouse->m_point;

      //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - layout().origin();

      //   set_mouse_capture();

      //   pmouse->m_bRet = true;

      //   return;

      //}
      //else if (m_pdragsize && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_item.m_eelement == e_element_drag_size)
      //{

      //   get_wnd()->show_keyboard(false);

      //   m_pdragsize->m_bLButtonDown = true;

      //   m_pdragsize->m_bDrag = false;

      //   m_pdragsize->m_pointLButtonDown = pmouse->m_point;

      //   m_pdragsize->m_sizeLButtonDownOffset = m_pdragsize->m_pointLButtonDown - layout().origin();

      //   set_mouse_capture();

      //   pmouse->m_bRet = true;

      //   return;

      //}

//      auto pwindowHost = window();
//
      if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
      {

         if (::is_item_set(pitemLButtonDown))
         {

            information() << "interaction::on_message_parent_left_button_down pitemLButtonDown set : " << strType;

            //auto psession = get_session();

            auto pwindowHost = window();

            pwindowHost->m_puiLastLButtonDown = this;

            pwindowHost->m_pitemLButtonDown = pitemLButtonDown;

            //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
            //{

            set_mouse_capture();

            //}

            track_mouse_leave();

            // For Windows: ... (please fill in...)
            // For Linux: ...
            // - control box button scenario:
            //   user presses down the button,
            //   m_itemLButtonDown turns e_element_client.
            //   m_itemLButtonDown isn't e_element_none
            //   but it is e_element_client,
            //   so it sets m_bRet to false
            //   further processing continues,
            //   main frame handling (move_manager)
            //   starts (and in this case, captures the mouse) (BAD)
            //   Later l_button_up in this case will route
            //   to main frame (that captured the mouse for
            //   move_manager)
//            pmouse->m_bRet = m_itemLButtonDown.m_eelement != e_element_none
            //             && m_itemLButtonDown.m_eelement != e_element_client;

            if (m_bDefaultClickHandling)
            {

               // For Windows: ... (please fill in...)
               // For Linux: ...
               // - control box button scenario:
               //   user presses down the button,
               //   m_itemLButtonDown turns e_element_client.
               //   m_itemLButtonDown isn't e_element_none,
               //   so it sets m_bRet to true
               //   further processing is quit,
               //   main frame handling (move_manager) is skipped. (OK)
               //   Later l_button_up can trigger button on click using
               //   interaction SimpleUIMouseHandling
               pmouse->m_bRet = true;

               return;

            }

         }

      }
      //
      //      {
      //
      //         auto pappearance = get_appearance();
      //
      //         if (::is_set(pappearance))
      //         {
      //
      //            pappearance->m_pointLastCursor = pmouse->m_point;
      //
      //            ::point_i32 pointClient;
      //
      //            pointClient = pmouse->m_point;
      //
      //            screen_to_client()(pointClient);
      //
      //            auto ekeyModifiers = psession->key_modifiers();
      //
      //            bool bDoubleClick = false;
      //
      //            if (pappearance->on_button_down(e_key_left_button, pointClient, ekeyModifiers, bDoubleClick))
      //            {
      //
      //               pmouse->m_bRet = true;
      //
      //               return;
      //
      //            }
      //
      //         }
      //
      //      }
      //
      //      //         else
      //      //         {
      //      //
      //      //            if (pmessage->previous())
      //      //            {
      //      //
      //      //               return;
      //      //
      //      //            }
      //      //
      //      //            auto psession = get_session();
      //      //
      //      //            psession->m_puiLastLButtonDown = this;
      //      //
      //      ////            simple_on_control_event(pmessage, ::id_button_down);
      //      ////
      //      ////            if (pmessage->m_bRet)
      //      ////            {
      //      ////
      //      ////               pmouse->m_bRet = true;
      //      ////
      //      ////               return;
      //      ////
      //      ////            }
      //      //
      //      //         }
      //      //
      //      //      }
      //
      //      puseritemLButtonDown = update_hover(pmouse, e_zorder_back);
      //
      //      if (drag_on_button_down(puseritemLButtonDown))
      //      {
      //
      //         return;
      //
      //      }
      //
      //      if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
      //      {
      //
      //         if (::is_item_set(puseritemLButtonDown))
      //         {
      //
      //            pwindowHost->m_puiLastLButtonDown = this;
      //
      //            pwindowHost->m_pitemLButtonDown = puseritemLButtonDown;
      //
      //            track_mouse_leave();
      //
      //            if (m_bDefaultClickHandling)
      //            {
      //
      //               pmouse->m_bRet = true;
      //
      //               return;
      //
      //            }
      //
      //         }
      //
      //      }

   }


   void interaction::on_message_parent_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::string strType = ::type(this).name();

      information() << "interaction::on_message_parent_left_button_up : " << strType;

      if (!is_window_enabled())
      {

         return;

      }

      //if (m_bEnableHorizontalBarDragScroll || m_bEnableVerticalBarDragScroll)
      //{

      //   //         m_pointDragScrollLeftButtonDown = pmouse->m_point;

      //   m_bBarDragScrollLeftButtonDown = false;

      //   release_mouse_capture();

      //}

      //if (m_bHorizontalDragScrollingActive)
      //{

      //   pmouse->m_bRet = true;

      //   pmouse->m_lresult = 1;

      //   m_bHorizontalDragScrollingActive = false;

      //   return;

      //}

      if (drag_on_button_up(pmouse))
      {

         pmouse->m_bRet = true;

         return;

      }

      //if (pmouse->previous())
      //{

      //   return;

      //}

      ////if (drag_on_button_up(pmouse))
      ////{

      ////   return;

      ////}

      ////if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
      ////{

      ////   m_pdragmove->m_bLButtonDown = false;

      ////   if (pmouse->previous())
      ////   {

      ////      return;

      ////   }

      ////   auto psession = get_session();

      ////   auto puser = psession->user();

      ////   auto pwindowing = puser->windowing();

      ////   pwindowing->release_mouse_capture();

      ////   m_pdragmove->m_bDrag = false;

      ////   pmessage->m_bRet = true;

      ////   return;

      ////}

      //if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
      //{

      //   //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
      //   //{

      //   if (has_mouse_capture())
      //   {

      //      auto pwindowing = windowing();

      //      pwindowing->release_mouse_capture();

      //   }

      //   //}

      //   auto pwindowimpl = window();

      //   if (m_bDefaultClickHandling && ::is_set(pwindowimpl->m_pitemLButtonDown))
      //   {

      //      auto puseritemLButtonDown = user_item(pwindowimpl->m_pitemLButtonDown);

      //      auto puseritemLeftButtonUp = hit_test(pmouse, puseritemLButtonDown->m_ezorder);

      //      bool bSameUserInteractionAsMouseDown = pwindowimpl->m_puiLastLButtonDown == this;

      //      bool bSameItemAsMouseDown = ::is_same_item(pwindowimpl->m_pitemLButtonDown, puseritemLeftButtonUp);

      //      //informationf("interaction::on_message_left_button_up item=" << (int)pitemLeftButtonUp->m_item.m_iItem<<", SameUserInteractionAsMsDwn="<< (int) bSameUserInteractionAsMouseDown<<", SameItemAsMsDwn=" << (int) bSameItemAsMouseDown);

      //      if (bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
      //      {

      //         pmessage->m_bRet = on_click_generation(pwindowimpl->m_pitemLButtonDown);

      //         information() << "interaction::on_message_left_button_up on_click_generation ret="
      //            << (int)pmessage->m_bRet;

      //         if (pmessage->m_bRet)
      //         {

      //            pmouse->m_lresult = 1;

      //         }
      //         else
      //         {

      //            ::atom atom;

      //            if (pwindowimpl->m_pitemLButtonDown->m_atom.is_empty())
      //            {

      //               atom = translate_property_id(m_atom);

      //            }
      //            else
      //            {

      //               atom = translate_property_id(pwindowimpl->m_pitemLButtonDown->m_atom);

      //            }

      //            if (has_handler())
      //            {

      //               auto ptopic = create_topic(id_click);

      //               ptopic->m_puserelement = this;

      //               ptopic->m_pitem = pwindowimpl->m_pitemLButtonDown;

      //               ptopic->m_actioncontext.m_pmessage = pmouse;

      //               ptopic->m_actioncontext.add(::e_source_user);

      //               route(ptopic);

      //               information() << "interaction::on_message_left_button_up route_btn_clked=" << (int)ptopic->m_bRet;

      //               pmessage->m_bRet = ptopic->m_bRet;

      //            }

      //            //if (!pmessage->m_bRet)
      //            //{

      //            //   auto estatus = command_handler(atom);

      //            //   pmessage->m_bRet = estatus.succeeded();

      //            //}

      //            if (!pmessage->m_bRet)
      //            {

      //               ::message::command command(atom);

      //               command.m_puiOther = this;

      //               //route_command_message(&command);

      //               route_command(&command);

      //               information() << "interaction::on_message_left_button_up route_cmd_msg=" << (int)command.m_bRet;

      //               pmessage->m_bRet = command.m_bRet;

      //            }

      //            if (pmessage->m_bRet)
      //            {

      //               pmouse->m_lresult = 1;

      //            }

      //            //               if(!pmessage->m_bRet)
      //            //               {
      //            //
      //            //                  auto linkedproperty = fetch_property(m_atom);
      //            //
      //            ////                  if(linkedproperty)
      //            ////                  {
      //            ////
      //            ////                     linkproperty
      //            ////
      //            ////                  }
      //            ////
      //            ////               }
      //         }

      //      }
      //      //            else
      //      //            {
      //      //
      //      //               if (pmessage->previous())
      //      //               {
      //      //
      //      //                  return;
      //      //
      //      //               }
      //      //
      //      //               simple_on_control_event(pmessage, ::id_button_down);
      //      //
      //      //            }

      //   }

      //   pwindowimpl->m_puiLastLButtonDown = nullptr;

      //   //set_need_redraw();

      //   //post_redraw();

      //}

      //auto pappearance = get_appearance();

      //if (::is_set(pappearance))
      //{

      //   pappearance->m_pointLastCursor = pmouse->m_point;

      //   ::point_i32 pointClient;

      //   pointClient = pmouse->m_point;

      //   screen_to_client()(pointClient);

      //   auto psession = this->get_session();

      //   auto ekeyModifiers = psession->key_modifiers();

      //   if (pappearance->on_button_up(e_key_left_button, pointClient, ekeyModifiers))
      //   {

      //      pmessage->m_bRet = true;

      //      return;

      //   }

      //}

   }


   void interaction::on_message_parent_mouse_move(::message::message * pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      auto pmouse = pmessage->m_union.m_pmouse;

      if (drag_on_mouse_move(pmouse))
      {

         pmessage->m_bRet = true;

         return;

      }

      ::string strType;

      strType = type(this).as_string();

      if (strType.contains("font_list"))
      {

         information() << "interaction::on_message_parent_mouse_move font_list";

      }
      else if (strType.contains("simple_scroll_bar"))
      {

         information() << "interaction::on_message_parent_mouse_move simple_scroll_bar";

      }
      else if (strType.contains("simple_application::main_frame"))
      {

         information() << "simple_application::main_frame on_message_parent_mouse_move";

      }

      //if (m_bBarDragScrollLeftButtonDown)
      //{

      //   if (m_bEnableHorizontalBarDragScroll)
      //   {

      //      m_bHorizontalBarDragScrollingActive = true;

      //      int iOffset = m_pointBarDragScrollLeftButtonDown.x() - pmouse->m_point.x();

      //      auto iHorizontalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.x() + iOffset, 0,
      //                                                      m_pointBarDragScrollMax.x());

      //      if (iHorizontalBarDragScroll != m_pointBarDragScroll.x())
      //      {

      //         m_pointBarDragScroll.x() = iHorizontalBarDragScroll;

      //         set_need_redraw();

      //         post_redraw();

      //      }

      //      pmouse->m_bRet = true;

      //      return;

      //   }

      //   if (m_bEnableVerticalBarDragScroll)
      //   {

      //      m_bVerticalBarDragScrollingActive = true;

      //      int iOffset = m_pointBarDragScrollLeftButtonDown.y() - pmouse->m_point.y();

      //      auto iVerticalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.y() + iOffset, 0,
      //                                                    m_pointBarDragScrollMax.y());

      //      if (iVerticalBarDragScroll != m_pointBarDragScroll.y())
      //      {

      //         m_pointBarDragScroll.y() = iVerticalBarDragScroll;

      //         set_need_redraw();

      //         post_redraw();

      //      }

      //   }

      //   pmouse->m_bRet = true;

      //   return;

      //}

      //{

      //   //_synchronous_lock synchronouslock(this->synchronization());

      //   pmouse->m_pcursor = get_mouse_cursor();

      //   if (drag_on_mouse_move(pmouse))
      //   {

      //      pmessage->m_bRet = true;

      //      return;

      //   }

      //   //if (m_pdragmove && m_pdragmove->m_bLButtonDown)
      //   //{

      //   //   auto psession = get_session();

      //   //   auto puser = psession->user();

      //   //   auto pwindowing = puser->windowing();

      //   //   auto pcursor = pwindowing->get_cursor(e_cursor_move);

      //   //   pmouse->m_pcursor = pcursor;

      //   //   if (!m_pdragmove->m_bDrag)
      //   //   {

      //   //      m_pdragmove->m_bDrag = true;

      //   //      auto point = pmouse->m_point - m_pdragmove->m_sizeLButtonDownOffset;

      //   //      move_to(point);

      //   //      set_reposition();

      //   //      set_need_redraw();

      //   //      post_redraw();

      //   //      m_pdragmove->m_bDrag = false;

      //   //   }

      //   //   pmessage->m_bRet = true;

      //   //   return;

      //   //}

      //}

      //if (m_bDefaultMouseHoverHandling)
      {
         auto type = ::type(this);

         if (type.name().contains("button"))
         {

            //informationf("button");

         }

         //bool bAvoidRedraw = !m_bDefaultMouseHoverHandling;


         if (m_atom == "frame::e_button_transparent_frame")
         {

            information() << "frame::e_button_transparent_frame on_message_parent_mouse_move";

         }
         else if (m_atom == "frame::e_button_dock")
         {

            information() << "frame::e_button_dock on_message_parent_mouse_move";

         }

         //::string strType = ::type(this).name();

         if (strType == "simple_scroll_bar")
         {

            information() << "simple_scroll_bar";

         }
         else if (strType == "font_list")
         {

            information() << "font_list";

         }

         auto pitemFront = update_hover(pmouse, e_zorder_front);

         if (pmouse->m_bRet)
         {

            return;

         }

         //decltype(pitemFront) pitemBack;

         //if (!pitemFront)
         //{

         //   pitemBack = update_hover(pmouse, e_zorder_back);

         //}

         //update_hover(pointCursorClient, false);

//         if (::is_item_set(m_pitemHover))
//         {
//
//            if (!m_bMouseHover)
//            {
//
//               m_bMouseHover = true;
//
//               track_mouse_leave();
//
//               //auto pappearance = get_appearance();
//
//               //if (::is_set(pappearance))
//               //{
//
//               //   ::point_i32 pointClient;
//
//               //   _screen_to_client(pointClient, pmouse->m_point);
//
//               //   auto psession = this->get_session();
//
//               //   auto ekeyModifiers = psession->key_modifiers();
//
//               //   pappearance->on_mouse_enter(pointClient, ekeyModifiers);
//
//               //}
//
//            }
//
//         }

      }

      //{

      //   auto pappearance = get_appearance();

      //   if (::is_set(pappearance))
      //   {

      //      pappearance->m_pointLastCursor = pmouse->m_point;

      //      ::point_i32 pointClient;

      //      pointClient = pmouse->m_point;

      //      screen_to_client()(pointClient);

      //      bool bRet;

      //      auto psession = this->get_session();

      //      auto ekeyModifiers = psession->key_modifiers();

      //      bool bDown = pmouse->m_ebuttonstate & e_button_state_left;
      //      /*{

      //         bRet = pappearance->on_mouse_drag(pointClient, ekeyModifiers);

      //      }
      //      else
      //      {*/

      //      bRet = pappearance->on_mouse_move(pointClient, bDown, ekeyModifiers);

      //      if (get_wnd()->windowing_window())
      //      {

      //         if (get_wnd()->windowing_window()->m_redrawitema.has_element())
      //         {

      //            post_redraw();

      //         }

      //      }
      //      //}

      //      pappearance->m_pointMouseLast = pointClient;

      //      if (bRet)
      //      {

      //         pmessage->m_bRet = true;

      //         return;

      //      }

      //   }

      //}

   }


   void interaction::on_message_left_button_down_handle_keyboard_focus(::message::message * pmessage)
   {

      try
      {

         if (keyboard_focus_is_focusable())
         {

            set_keyboard_focus();

            {

               auto psession = get_session();

               psession->user()->set_mouse_focus_LButtonDown(this);

               //set_need_redraw();

               //post_redraw();

            }

         }
         else
         {

            clear_keyboard_focus();

         }

      }
      catch (...)
      {

      }

   }


   void interaction::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::string strType = ::type(this).name();

      information() << "interaction::on_message_left_button_down : " << strType;

      if (!is_window_enabled())
      {

         return;

      }

      auto psession = get_session();

      on_message_left_button_down_handle_keyboard_focus(pmessage);

      if ((m_bEnableHorizontalBarDragScroll && _001HasBarXDragScrolling())
          || (m_bEnableVerticalBarDragScroll && _001HasBarYDragScrolling()))
      {

         m_pointBarDragScrollLeftButtonDown = pmouse->m_pointHost;

         m_bBarDragScrollLeftButtonDown = true;

         m_pointBarDragScrollStart = m_pointBarDragScroll;

         set_mouse_capture();

      }

      //auto puseritemLButtonDown = update_hover(pmouse, e_zorder_front);

      /*if (drag_on_button_down(puseritemLButtonDown))
      {

         return;

      }*/

      //if(m_pdragmove && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_item.m_eelement == e_element_client)
      //{

      //   get_wnd()->show_keyboard(false);

      //   m_pdragmove->m_bLButtonDown = true;

      //   m_pdragmove->m_bDrag = false;

      //   m_pdragmove->m_pointLButtonDown = pmouse->m_point;

      //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - layout().origin();

      //   set_mouse_capture();

      //   pmouse->m_bRet = true;

      //   return;

      //}
      //else if (m_pdragsize && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_item.m_eelement == e_element_drag_size)
      //{

      //   get_wnd()->show_keyboard(false);

      //   m_pdragsize->m_bLButtonDown = true;

      //   m_pdragsize->m_bDrag = false;

      //   m_pdragsize->m_pointLButtonDown = pmouse->m_point;

      //   m_pdragsize->m_sizeLButtonDownOffset = m_pdragsize->m_pointLButtonDown - layout().origin();

      //   set_mouse_capture();

      //   pmouse->m_bRet = true;

      //   return;

      //}

//      auto pwindowHost = window();
//
//      if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
//      {
//
//         if (::is_item_set(puseritemLButtonDown))
//         {
//
//            //auto psession = get_session();
//
//            pwindowHost->m_puiLastLButtonDown = this;
//
//            pwindowHost->m_pitemLButtonDown = puseritemLButtonDown;
//
//            //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
//            //{
//
//            //set_mouse_capture();
//
//            //}
//
//            track_mouse_leave();
//
//            // For Windows: ... (please fill in...)
//            // For Linux: ...
//            // - control box button scenario:
//            //   user presses down the button,
//            //   m_itemLButtonDown turns e_element_client.
//            //   m_itemLButtonDown isn't e_element_none
//            //   but it is e_element_client,
//            //   so it sets m_bRet to false
//            //   further processing continues,
//            //   main frame handling (move_manager)
//            //   starts (and in this case, captures the mouse) (BAD)
//            //   Later l_button_up in this case will route
//            //   to main frame (that captured the mouse for
//            //   move_manager)
////            pmouse->m_bRet = m_itemLButtonDown.m_eelement != e_element_none
//            //             && m_itemLButtonDown.m_eelement != e_element_client;
//
//            if (m_bDefaultClickHandling)
//            {
//
//               // For Windows: ... (please fill in...)
//               // For Linux: ...
//               // - control box button scenario:
//               //   user presses down the button,
//               //   m_itemLButtonDown turns e_element_client.
//               //   m_itemLButtonDown isn't e_element_none,
//               //   so it sets m_bRet to true
//               //   further processing is quit,
//               //   main frame handling (move_manager) is skipped. (OK)
//               //   Later l_button_up can trigger button on click using
//               //   interaction SimpleUIMouseHandling
//               pmouse->m_bRet = true;
//
//               return;
//
//            }
//
//         }
//
//      }

      {

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            pappearance->m_pointLastCursor = pmouse->m_pointHost;

            ::point_i32 pointClient;

            pointClient = pmouse->m_pointHost;

            host_to_client()(pointClient);

            auto ekeyModifiers = psession->key_modifiers();

            bool bDoubleClick = false;

            if (pappearance->on_button_down(e_key_left_button, pointClient, ekeyModifiers, bDoubleClick))
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      //         else
      //         {
      //
      //            if (pmessage->previous())
      //            {
      //
      //               return;
      //
      //            }
      //
      //            auto psession = get_session();
      //
      //            psession->m_puiLastLButtonDown = this;
      //
      ////            simple_on_control_event(pmessage, ::id_button_down);
      ////
      ////            if (pmessage->m_bRet)
      ////            {
      ////
      ////               pmouse->m_bRet = true;
      ////
      ////               return;
      ////
      ////            }
      //
      //         }
      //
      //      }

      auto pitemLButtonDown = update_hover(pmouse, e_zorder_back);

      if (drag_on_button_down(pitemLButtonDown))
      {

         return;

      }

      if (pmouse->m_bRet)
      {

         informationf("interaction::on_message_left_button_down m_bRet = true");
         //return;

      }

      if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
      {

         if (::is_item_set(pitemLButtonDown))
         {

            auto pwindowHost = window();

            pwindowHost->m_puiLastLButtonDown = this;

            pwindowHost->m_pitemLButtonDown = pitemLButtonDown;

            set_mouse_capture();

            track_mouse_leave();

            if (m_bDefaultClickHandling)
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

   }


   void interaction::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      ::string strType = ::type(this).name();

      information() << "interaction::on_message_left_button_up : " << strType;

      if (!is_window_enabled())
      {

         return;

      }

      if (m_bEnableHorizontalBarDragScroll || m_bEnableVerticalBarDragScroll)
      {

         //         m_pointDragScrollLeftButtonDown = pmouse->m_point;

         m_bBarDragScrollLeftButtonDown = false;

         defer_release_mouse_capture();

      }

      //if (m_bHorizontalDragScrollingActive)
      //{

      //   pmouse->m_bRet = true;

      //   pmouse->m_lresult = 1;

      //   m_bHorizontalDragScrollingActive = false;

      //   return;

      //}

      //if (drag_on_button_up(pmouse))
      //{

      //   return;

      //}

      if (pmouse->previous())
      {

         return;

      }

      //if (drag_on_button_up(pmouse))
      //{

      //   return;

      //}

      //if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
      //{

      //   m_pdragmove->m_bLButtonDown = false;

      //   if (pmouse->previous())
      //   {

      //      return;

      //   }

      //   auto psession = get_session();

      //   auto puser = psession->user();

      //   auto pwindowing = puser->windowing();

      //   pwindowing->release_mouse_capture();

      //   m_pdragmove->m_bDrag = false;

      //   pmessage->m_bRet = true;

      //   return;

      //}

      auto pwindowHost = window();

      if (pwindowHost->m_puiLastLButtonDown == this)
      {

         if (pwindowHost->m_pitemLButtonDown
                  && pwindowHost->m_pitemLButtonDown->m_eitemflag & ::e_item_flag_drag)
         {

            defer_release_mouse_capture();

            auto ptopic = create_topic(::id_left_button_up);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext.m_pmessage = pmouse;

            ptopic->m_actioncontext.add(e_source_user);

            ptopic->m_pitem = pwindowHost->m_pitemLButtonDown;

            route(ptopic);

            pmouse->m_bRet = true;

            pwindowHost->m_puiLastLButtonDown = nullptr;

            pwindowHost->m_pitemLButtonDown = nullptr;

            return;

         }

      }


      if (m_bDefaultClickHandling || m_bDefaultMouseHoverHandling)
      {

         //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
         //{

         //if (has_mouse_capture())
         //{

           // ::information() << "interaction::on_message_left_button_up had mouse capture, going to release : " << strType;

            //auto pwindowing = windowing();

            //pwindowing->release_mouse_capture();

         if (defer_release_mouse_capture())
         {

            information() << "interaction::on_message_left_button_up had mouse capture, released : " << strType;

         }
         else
         {

            information() << "interaction::on_message_left_button_up hadn't mouse capture, not releasing : " << strType;

         }





         //         }
         //         else
         //         {
         //
         //            ::information() << "interaction::on_message_left_button_up didn't have mouse capture : " << strType;
         //
         //         }

                  //}

         auto pwindowimpl = window();

         if (m_bDefaultClickHandling && ::is_set(pwindowimpl) && ::is_set(pwindowimpl->m_pitemLButtonDown))
         {

            auto puseritemLButtonDown = user_item(pwindowimpl->m_pitemLButtonDown);

            auto puseritemLeftButtonUp = hit_test(pmouse, puseritemLButtonDown->m_ezorder);

            bool bSameUserInteractionAsMouseDown = pwindowimpl->m_puiLastLButtonDown == this;

            bool bSameItemAsMouseDown = ::is_same_item(pwindowimpl->m_pitemLButtonDown, puseritemLeftButtonUp);

            //informationf("interaction::on_message_left_button_up item=" << (int)pitemLeftButtonUp->m_item.m_iItem<<", SameUserInteractionAsMsDwn="<< (int) bSameUserInteractionAsMouseDown<<", SameItemAsMsDwn=" << (int) bSameItemAsMouseDown);

            if (bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
            {

               pmessage->m_bRet = on_click_generation(pwindowimpl->m_pitemLButtonDown);

               information() << "interaction::on_message_left_button_up on_click_generation ret="
                  << (int)pmessage->m_bRet;

               if (pmessage->m_bRet)
               {

                  pmouse->m_lresult = 1;

               }
               else
               {

                  ::atom atom;

                  if (pwindowimpl->m_pitemLButtonDown->m_atom.is_empty())
                  {

                     //atom = translate_property_id(m_atom);
                     atom = m_atom;

                  }
                  else
                  {

                     //atom = translate_property_id(pwindowimpl->m_pitemLButtonDown->m_atom);
                     atom = pwindowimpl->m_pitemLButtonDown->m_atom;

                  }

                  if (has_handler())
                  {

                     auto ptopic = create_topic(id_click);

                     ptopic->m_puserelement = this;

                     ptopic->m_pitem = pwindowimpl->m_pitemLButtonDown;

                     ptopic->m_actioncontext.m_pmessage = pmouse;

                     ptopic->m_actioncontext.add(::e_source_user);

                     route(ptopic);

                     information() << "interaction::on_message_left_button_up route_btn_clked=" << (int)ptopic->m_bRet;

                     pmessage->m_bRet = ptopic->m_bRet;

                  }

                  //if (!pmessage->m_bRet)
                  //{

                  //   auto estatus = command_handler(atom);

                  //   pmessage->m_bRet = estatus.succeeded();

                  //}

                  if (!pmessage->m_bRet)
                  {

                     ::message::command command(atom);

                     command.m_puiOther = this;

                     //route_command_message(&command);

                     route_command(&command);

                     information() << "interaction::on_message_left_button_up route_cmd_msg=" << (int)command.m_bRet;

                     pmessage->m_bRet = command.m_bRet;

                  }

                  if (pmessage->m_bRet)
                  {

                     pmouse->m_lresult = 1;

                  }

                  //               if(!pmessage->m_bRet)
                  //               {
                  //
                  //                  auto linkedproperty = fetch_property(m_atom);
                  //
                  ////                  if(linkedproperty)
                  ////                  {
                  ////
                  ////                     linkproperty
                  ////
                  ////                  }
                  ////
                  ////               }
               }

            }
            //            else
            //            {
            //
            //               if (pmessage->previous())
            //               {
            //
            //                  return;
            //
            //               }
            //
            //               simple_on_control_event(pmessage, ::id_button_down);
            //
            //            }

         }

         pwindowimpl->m_puiLastLButtonDown = nullptr;

         information() << "interaction::on_message_left_button_up last_button_down set to null";
         information() << "m_pitemHover " << ::as_string((iptr)m_pitemHover.m_p);

         set_need_redraw();

         post_redraw();

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->m_pointLastCursor = pmouse->m_pointHost;

         ::point_i32 pointClient;

         pointClient = pmouse->m_pointHost;

         host_to_client()(pointClient);

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (pappearance->on_button_up(e_key_left_button, pointClient, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

   }


   void interaction::on_message_mouse_move(::message::message * pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      auto pwindowHost = window();

      if (pwindowHost->m_puiLastLButtonDown == this)
      {

         if (pwindowHost->m_pitemLButtonDown
                  && pwindowHost->m_pitemLButtonDown->m_eitemflag & ::e_item_flag_drag)
         {

            auto ptopic = create_topic(::id_left_button_drag);

            ptopic->m_puserelement = this;

            ptopic->m_actioncontext.m_pmessage = pmessage->m_union.m_pmouse;

            ptopic->m_actioncontext.add(e_source_user);

            ptopic->m_pitem = pwindowHost->m_pitemLButtonDown;

            route(ptopic);

            pmessage->m_bRet = true;

            return;

         }

      }


      ::string strType;

      strType = type(this).as_string();

      if (strType.contains("font_list"))
      {

         //information() << "interaction::on_message_mouse_move font_list";

      }
      else if (strType.contains("main_window"))
      {

         //information() << "interaction::on_message_mouse_move main_window";

      }

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_ekeyboardmode == ::user::e_keyboard_mode_reposition
   || m_ekeyboardmode == ::user::e_keyboard_mode_resize)
      {

         //information() << "interaction::on_message_mouse_move some keyboard mode on";

         auto pwindowing = windowing();

         auto pcursor = pwindowing->get_cursor(::e_cursor_move);

         user_mouse_set_cursor(pmouse, pcursor);

         pmouse->m_bRet = true;

         return;

      }


      if (m_bBarDragScrollLeftButtonDown)
      {

         information() << "interaction::on_message_mouse_move m_bBarDragScrollLeftButtonDown";

         if (m_bEnableHorizontalBarDragScroll)
         {

            information() << "interaction::on_message_mouse_move m_bEnableHorizontalBarDragScroll";

            m_bHorizontalBarDragScrollingActive = true;

            int iOffset = m_pointBarDragScrollLeftButtonDown.x() - pmouse->m_pointHost.x();

            auto iHorizontalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.x() + iOffset, 0,
                                                            m_pointBarDragScrollMax.x());

            if (iHorizontalBarDragScroll != m_pointBarDragScroll.x())
            {

               m_pointBarDragScroll.x() = iHorizontalBarDragScroll;

               set_need_redraw();

               post_redraw();

            }

            pmouse->m_bRet = true;

            return;

         }

         if (m_bEnableVerticalBarDragScroll)
         {

            information() << "interaction::on_message_mouse_move m_bEnableVerticalBarDragScroll";

            m_bVerticalBarDragScrollingActive = true;

            int iOffset = m_pointBarDragScrollLeftButtonDown.y() - pmouse->m_pointHost.y();

            auto iVerticalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.y() + iOffset, 0,
                                                          m_pointBarDragScrollMax.y());

            if (iVerticalBarDragScroll != m_pointBarDragScroll.y())
            {

               m_pointBarDragScroll.y() = iVerticalBarDragScroll;

               set_need_redraw();

               post_redraw();

            }

         }

         pmouse->m_bRet = true;

         return;

      }

      {

         //_synchronous_lock synchronouslock(this->synchronization());

         user_mouse_set_cursor(pmouse, get_mouse_cursor());

         if (user_mouse_get_cursor(pmouse))
         {

            // if (user_mouse_get_cursor(pmouse)->m_ecursor == e_cursor_size_bottom)
            // {

            //    information() << "e_cursor_size_bottom";

            // }
            // else
            // {

            //    information() << "(some cursor)";

            // }


         }
         else
         {

            //information() << "(no cursor)";

         }

         //if (m_pdragmove && m_pdragmove->m_bLButtonDown)
         //{

         //   auto psession = get_session();

         //   auto puser = psession->user();

         //   auto pwindowing = puser->windowing();

         //   auto pcursor = pwindowing->get_cursor(e_cursor_move);

         //   pmouse->m_pcursor = pcursor;

         //   if (!m_pdragmove->m_bDrag)
         //   {

         //      m_pdragmove->m_bDrag = true;

         //      auto point = pmouse->m_point - m_pdragmove->m_sizeLButtonDownOffset;

         //      move_to(point);

         //      set_reposition();

         //      set_need_redraw();

         //      post_redraw();

         //      m_pdragmove->m_bDrag = false;

         //   }

         //   pmessage->m_bRet = true;

         //   return;

         //}

      }

      //if (m_bDefaultMouseHoverHandling)
      {
         auto type = ::type(this);

         if (type.name().contains("button"))
         {

            //informationf("button");

         }

         //bool bAvoidRedraw = !m_bDefaultMouseHoverHandling;

         //auto pitemFront = update_hover(pmouse, e_zorder_front);

         //decltype(pitemFront) pitemBack;

         //if (!pitemFront)
         //{

         //information() << "update_hover pmouse e_zorder_back";

         auto pitemBack = update_hover(pmouse, e_zorder_back);

         //}

         //update_hover(pointCursorClient, false);

//         if (::is_item_set(m_pitemHover))
//         {
//
//            if (!m_bMouseHover)
//            {
//
//               m_bMouseHover = true;
//
//               track_mouse_leave();
//
//               //auto pappearance = get_appearance();
//
//               //if (::is_set(pappearance))
//               //{
//
//               //   ::point_i32 pointClient;
//
//               //   _screen_to_client(pointClient, pmouse->m_point);
//
//               //   auto psession = this->get_session();
//
//               //   auto ekeyModifiers = psession->key_modifiers();
//
//               //   pappearance->on_mouse_enter(pointClient, ekeyModifiers);
//
//               //}
//
//            }
//
//         }

      }

      {

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            pappearance->m_pointLastCursor = pmouse->m_pointHost;

            ::point_i32 pointClient;

            pointClient = pmouse->m_pointHost;

            host_to_client()(pointClient);

            bool bRet;

            auto psession = this->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            bool bDown = pmouse->m_ebuttonstate & e_button_state_left;
            /*{

               bRet = pappearance->on_mouse_drag(pointClient, ekeyModifiers);

            }
            else
            {*/

            pappearance->m_pmessage = pmessage;

            bRet = pappearance->on_mouse_move(pointClient, bDown, ekeyModifiers);

            if (get_wnd()->windowing_window())
            {

               if (get_wnd()->windowing_window()->m_redrawitema.has_element())
               {

                  post_redraw();

               }

            }
            //}

            pappearance->m_pointMouseLast = pointClient;

            if (bRet)
            {

               pmessage->m_bRet = true;

               return;

            }

         }

      }

   }



   void interaction::on_message_left_button_double_click(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();

      informationf("interaction::on_message_left_button_double_click" + ::string(pszType));

      if (!is_window_enabled())
      {

         return;

      }

      if (pmouse->previous())
      {

         return;

      }

      //      if (has_mouse_capture())
      //      {
      //
      //         auto pwindowing = windowing();

      defer_release_mouse_capture();

      //      }

      auto pwindowimpl = window();

      auto pitemLeftButtonDoubleClick = hit_test(pmouse, e_zorder_front);

      if (::is_item_set(pitemLeftButtonDoubleClick))
      {

         if (pitemLeftButtonDoubleClick->m_eitemflag & e_item_flag_double_click_as_second_click)
         {

            ::pointer<::message::mouse> pmouseUp1 = this->__create_new_clone(pmouse);

            pmouseUp1->m_atom = e_message_left_button_up;

            get_wnd()->post_message(pmouseUp1);

            ::pointer<::message::mouse> pmouseDown2 = this->__create_new_clone(pmouse);

            pmouseDown2->m_atom = e_message_left_button_down;

            get_wnd()->post_message(pmouseDown2);

            preempt(100_ms);

            ::pointer<::message::mouse> pmouseUp2 = this->__create_new_clone(pmouse);

            pmouseUp2->m_atom = e_message_left_button_up;

            get_wnd()->post_message(pmouseUp2);

            pmouse->m_bRet = true;

            return;

         }

         if (pitemLeftButtonDoubleClick->m_eitemflag & e_item_flag_eat_double_click)
         {

            pmouse->m_bRet = true;

            return;

         }

      }

      bool bSameUserInteractionAsMouseDown = pwindowimpl->m_puiLastLButtonDown == this;

      bool bSameItemAsMouseDown = ::is_same_item(pwindowimpl->m_pitemLButtonDown, pitemLeftButtonDoubleClick);

      if (::is_set(pwindowimpl->m_pitemLButtonDown) && bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
      {

         //psession->m_puiLastLButtonDown = nullptr;

         pmessage->m_bRet = on_click_generation(pwindowimpl->m_pitemLButtonDown);

         information() << "interaction::on_message_left_button_up on_click_generation ret=" << (int)pmessage->m_bRet;

         if (pmessage->m_bRet)
         {

            pmouse->m_lresult = 1;

         }
         else
         {

            ::atom atom;

            if (pwindowimpl->m_pitemLButtonDown->m_atom.is_empty())
            {

               //atom = translate_property_id(m_atom);

               atom = m_atom;

            }
            else
            {

               //atom = translate_property_id(pwindowimpl->m_pitemLButtonDown->m_atom);
               atom = pwindowimpl->m_pitemLButtonDown->m_atom;

            }

            if (has_handler())
            {

               auto ptopic = create_topic(id_left_button_double_click);

               ptopic->m_puserelement = this;

               ptopic->m_pitem = pwindowimpl->m_pitemLButtonDown;

               ptopic->m_actioncontext.m_pmessage = pmouse;

               ptopic->m_actioncontext.add(::e_source_user);

               route(ptopic);

               information() << "interaction::on_message_left_button_up route_btn_clked=" << (int)ptopic->m_bRet;

               pmessage->m_bRet = ptopic->m_bRet;

            }

            //if (!pmessage->m_bRet)
            //{

            //   auto estatus = command_handler(atom);

            //   pmessage->m_bRet = estatus.succeeded();

            //}

            if (!pmessage->m_bRet)
            {

               ::message::command command(atom);

               command.m_puiOther = this;

               //route_command_message(&command);

               route_command(&command);

               information() << "interaction::on_message_left_button_up route_cmd_msg=" << (int)command.m_bRet;

               pmessage->m_bRet = command.m_bRet;

            }

            if (pmessage->m_bRet)
            {

               pmouse->m_lresult = 1;

            }

            //               if(!pmessage->m_bRet)
            //               {
            //
            //                  auto linkedproperty = fetch_property(m_atom);
            //
            ////                  if(linkedproperty)
            ////                  {
            ////
            ////                     linkproperty
            ////
            ////                  }
            ////
            ////               }
         }

      }
      //            else
      //            {
      //
      //               if (pmessage->previous())
      //               {
      //
      //                  return;
      //
      //               }
      //
      //               simple_on_control_event(pmessage, ::id_button_down);
      //
      //            }

      pwindowimpl->m_puiLastLButtonDown = nullptr;

      set_need_redraw();

      post_redraw();

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->m_pointLastCursor = pmouse->m_pointHost;

         ::point_i32 pointClient;

         pointClient = pmouse->m_pointHost;

         host_to_client()(pointClient);

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         bool bDoubleClick = true;

         if (pappearance->on_button_down(e_key_left_button, pointClient, ekeyModifiers, bDoubleClick))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

   }


   void interaction::on_message_right_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_window_enabled())
      {

         return;

      }

      if (pmessage->previous())
      {

         return;

      }

      {

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            pappearance->m_pointLastCursor = pmouse->m_pointHost;

            ::point_i32 pointClient;

            pointClient = pmouse->m_pointHost;

            host_to_client()(pointClient);

            auto psession = this->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            bool bDoubleClick = false;

            if (pappearance->on_button_down(e_key_right_button, pointClient, ekeyModifiers, true))
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      auto pcontextmenu = __allocate::message::context_menu();

      pcontextmenu->m_oswindow = oswindow();
      pcontextmenu->m_pwindow = window();
      pcontextmenu->m_atom = e_message_context_menu;
      pcontextmenu->m_pointMessage = pmouse->m_pointHost;

      //;; pcontextmenu->m_wpar
      //pcontextmenu->set(oswindow(), window(), e_message_context_menu, (wparam)(iptr)oswindow(), pmouse->m_point.lparam());

      message_handler(pcontextmenu);

   }


   void interaction::on_message_right_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_window_enabled())
      {

         return;

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->m_pointLastCursor = pmouse->m_pointHost;

         ::point_i32 pointClient;

         pointClient = pmouse->m_pointHost;

         host_to_client()(pointClient);

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (pappearance->on_button_up(e_key_right_button, pointClient, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (m_einteraction & ::user::e_interaction_system_context_menu)
      {

         if (pmouse->m_pointHost.y() <= 48)
         {

            window()->defer_show_system_menu(pmouse);

         }

      }

   }


#ifdef MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG


   void interaction::on_message_middle_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->previous();

      //if (m_bDefaultClickHandling)
      //{

//         auto item = hit_test(pmouse);
//
//         if (item.is_set())
//         {
//
//            simple_on_control_event(pmessage, ::id_m_button_down);
//
//         }

      //}

   }


   void interaction::on_message_middle_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->previous();

      //if (m_bSimpleUIDefaultMouseHandling)
      //{

//         auto item = hit_test(pmouse);
//
//         if (item.is_set())
//         {
//
//            simple_on_control_event(pmessage, ::id_m_button_up);
//
//         }
//
//      }

   }

#endif // MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG



   void interaction::on_message_mouse_wheel(::message::message * pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      ::pointer<::message::mouse_wheel> pwheel = pmessage;

      double y = pwheel->m_Δ / 120.0;

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->m_pointLastCursor = pwheel->m_pointHost;

         ::point_i32 pointClient;

         pointClient = pwheel->m_pointHost;

         host_to_client()(pointClient);

         bool bRet;

         auto psession = this->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         bRet = pappearance->on_scroll_event(pointClient, 0., y);

         pappearance->m_pointMouseLast = pointClient;

         if (bRet)
         {

            pmessage->m_bRet = true;

            return;

         }

      }

   }


   ::item_pointer interaction::update_hover(::message::mouse * pmouse, e_zorder ezorder)
   {

      if (ezorder == e_zorder_any)
      {

         auto pitemHover = update_hover(pmouse, e_zorder_front);

         if (::is_item_set(pitemHover))
         {

            return pitemHover;

         }

         pitemHover = update_hover(pmouse, e_zorder_back);

         return pitemHover;

      }

      auto pitemHitTest = hit_test(pmouse, ezorder);

      bool bRet = false;

      if (::is_item_set(pitemHitTest))
      {

         bRet = drag_on_mouse_hover(pitemHitTest);

         if (!user_mouse_get_cursor(pmouse))
         {

            auto pwindowing = windowing();

            auto pcursor = pwindowing->get_cursor(e_cursor_arrow);

            user_mouse_set_cursor(pmouse, pcursor);

         }

         //bRet = true;

      }

      ///bool bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

      if (!::is_item_equivalent(pitemHitTest, m_pitemHover))
      {

         //informationf("user::interaction::update_hover !is_item_equivalent(pitemHitTest, m_pitemHover)");

         auto pitemOldHover = m_pitemHover;

         g_iMouseHoverCount++;

         m_pitemHover = pitemHitTest;

         on_update_hover(m_pitemHover);

         //m_pitemHOver->m_bAnyHoverChange = true;

         if (::is_item_set(m_pitemHover))
         {

            if (m_atom == "frame::e_button_transparent_frame")
            {

               information() << "frame::e_button_transparent_frame update_hover track_mouse_leave";

            }

            ::string strType = type(this).as_string();

            if (strType == "simple_scroll_bar")
            {

               information() << "simple_scroll_bar";

            }

            if (!pitemOldHover)
            {

               try
               {

                  track_mouse_leave();

               }
               catch (...)
               {

               }

            }

         }

         ::rectangle_i32_array rectanglea;

         if (::is_item_set(pitemOldHover))
         {

            //informationf("user::interaction::update_hover is_item_set(pitemOldHover)");

            if (should_redraw_on_hover(pitemOldHover))
            {

               //informationf("user::interaction::update_hover should_redraw_on_hover(pitemOldHover)");

               //auto puseritem = user_item(pitemOldHover);

               auto rectangleBounding = item_rectangle(pitemOldHover, e_layout_design);

               if (rectangleBounding.ok())
               {

                  rectangleBounding.inflate(1);

                  rectanglea.add(rectangleBounding);

               }

            }

         }

         if (::is_item_set(pitemHitTest))
         {

            //informationf("user::interaction::update_hover is_item_set(pitemHitTest)");

            if (should_redraw_on_hover(pitemHitTest))
            {

               //informationf("user::interaction::update_hover should_redraw_on_hover(pitemHitTest)");

               auto rectangleBounding = item_rectangle(pitemHitTest, e_layout_design);

               if (rectangleBounding.ok())
               {

                  //::rectangle_i32 rectangleBounding = ::bounding_box(user_item(pitemHitTest));

                  rectangleBounding.inflate(1);

                  rectanglea.add(rectangleBounding);

               }

            }

         }

         if (rectanglea.has_element())
         {

            //informationf("user::interaction::update_hover set_need_redraw (%d rectangle(s))", rectanglea.size());

            for (auto & rectangle : rectanglea)
            {

               information() << "user::interaction::update_hover set_need_redraw" << rectangle;

            }

            set_need_redraw(rectanglea);

            post_redraw();

         }

      }

      //if (!bAvoidRedraw)
      //{

      //   if (bAnyHoverChange || (!m_pitemHover || !m_pitemHover->is_drawn()))
      //   {

      //      set_need_redraw();

      //      post_redraw();

      //   }

      //}

      //if (::is_set(pmouse))
      //{

   //      auto pitemOldMouseHover = m_pitemHoverMouse;
   //
   //      if (!::is_item_equivalent(m_pitemHover, m_pitemHoverMouse))
   //      {
   //
   //         m_pitemHoverMouse = m_pitemHover;
   //
   //         bAnyHoverChange = true;
   //
   //         if (::is_set(m_pitemHoverMouse) && !::is_set(pitemOldMouseHover))
   //         {
   //
   //            track_mouse_hover();
   //
   //            //simple_on_control_event(pmouse, e_event_mouse_enter);
   //
   //         }
   //         else if (!::is_set(m_pitemHoverMouse) && ::is_set(pitemOldMouseHover))
   //         {
   //
   //            //simple_on_control_event(pmouse, e_event_mouse_leave);
   //
   //         }
   //
   //         //pmouse->m_bRet = true;
   //
   //      }

      //}

   //      if (bAnyHoverChange)
   //      {
   //
   //         //if (!bAvoidRedraw)
   //         //{
   //
   //         bool bAnyRedraw = false;
   //
   //         if(::is_item_set(pitemOldMouseHover) && pitemOldMouseHover->m_rectangle.is_set())
   //         {
   //
   //            set_need_redraw(pitemOldMouseHover->m_rectangle);
   //
   //            bAnyRedraw = true;
   //
   //         }
   //
   //         if(::is_item_set(m_pitemHoverMouse) && m_pitemHoverMouse->m_rectangle.is_set())
   //         {
   //
   //            set_need_redraw(m_pitemHoverMouse->m_rectangle);
   //
   //            bAnyRedraw = true;
   //
   //         }
   //
   //         if(bAnyRedraw)
   //         {
   //
   //            post_redraw();
   //
   //         }
   //
   //         //}
   //
   //      }

      if (bRet)
      {

         pmouse->m_bRet = true;

      }

      return pitemHitTest;

   }


   ::item_pointer interaction::update_hover_according_to_last_hover_update(e_zorder ezorder)
   {

      auto pmouse = __create_new < ::message::mouse >();

      pmouse->m_pointHost = host_mouse_cursor_position();

      pmouse->m_pointAbsolute = absolute_mouse_cursor_position();

      return update_hover(pmouse, ezorder);

   }


   void interaction::on_update_hover(::item * pitem)
   {


   }


   bool interaction::is_mouse_hover() const
   {

      bool bMouseHover = ::is_item_set(m_pitemHover);

      auto pwindowimpl = ((interaction *)this)->window();

      if (pwindowimpl->m_puiLastLButtonDown == this)
      {

         bMouseHover = true;

      }

      return bMouseHover;

   }


   void interaction::on_message_mouse_leave(::message::message * pmessage)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::string strType = ::type(this).name();

      information() << "interaction::on_message_mouse_leave type : " << strType;

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->on_mouse_leave();

      }

      auto pitemOldHover = m_pitemHover;

      m_pitemHover = nullptr;

      if (::is_item_set(pitemOldHover))
      {

         auto * puseritem = user_item(pitemOldHover);

         auto rectangle = user_item_rectangle(puseritem, ::user::e_layout_sketch);

         if (rectangle.is_set())
         {

            information() << "interaction::on_message_mouse_leave : " << rectangle;

            set_need_redraw({ rectangle });

            post_redraw();

         }
         else if (puseritem->m_ppath.is_set())
         {

            information() << "interaction::on_message_mouse_leave set_need_redraw()";

            set_need_redraw();

            post_redraw();

         }

      }

   }


   ::item_pointer interaction::hit_test(::user::mouse * pmouse, e_zorder ezorder)
   {

      ::point_i32 pointClient;

      pointClient = pmouse->m_pointHost;

      host_to_client()(pointClient);

      auto r = this->client2_rectangle();

      if (!r.contains(pointClient))
      {

         //information() << "hit_test !r.contains(pointClient)";

         auto pitemNone = stock_item(e_element_none);

         return pitemNone;

      }

      auto pitem = hit_test(pointClient, ezorder);

      if (!pitem)
      {

         return nullptr;

      }

      auto * puseritem = user_item(pitem);

      //puseritem->m_pointScreen = pmouse->m_point;

      puseritem->m_pointHost = pmouse->m_pointHost;

      puseritem->m_pmouse = pmouse;

      return pitem;

   }


   ::item_pointer interaction::hit_test(const ::point_i32 & pointClient, e_zorder ezorder)
   {

      ::rectangle_i32 rectangleXHitTest;

      if (get_element_rectangle(rectangleXHitTest, e_element_client_hit_test))
      {

         //information() << "hit_test got_element_rect client_hit_test";

         if (!rectangleXHitTest.contains(pointClient))
         {

            //information() << "hit_test got_element_rect !rectangleXHitTest";

            return nullptr;

         }

      }

      auto pitem = on_hit_test(pointClient, ezorder);

      auto * puseritem = user_item(pitem);

      puseritem->m_pointClient = pointClient;

      return pitem;

   }


   ::item_pointer interaction::parent_client_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      auto p = point;

      parent_to_client()(p);

      return hit_test(p, ezorder);

   }


   ::item_pointer interaction::parent_client_on_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      auto p = point;

      parent_to_client()(p);

      return hit_test(p, ezorder);

   }


   ::item_pointer interaction::on_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      {

         auto pitemHitTest = on_items_hit_test(point, ezorder);

         if (::is_set(pitemHitTest))
         {

            return pitemHitTest;

         }

      }

      //      {
      //
      //         auto pitemHitTest = on_default_bottom_right_resize_hit_test(point, ezorder);
      //
      //         if (::is_set(pitemHitTest))
      //         {
      //
      //            return pitemHitTest;
      //
      //         }
      //
      //      }
      //
      //
      //      {
      //
      //         auto pitemHitTest = on_client_area_hit_test(point, ezorder);
      //
      //         if (::is_set(pitemHitTest))
      //         {
      //
      //            return pitemHitTest;
      //
      //         }
      //
      //      }


      auto pitemNone = stock_item(e_element_none);

      return pitemNone;

   }


   bool interaction::item_contains(::item * pitem, const ::point_i32 & point)
   {

      // if(pitem->m_item.m_eelement == e_element_resize)
      // {

      //    information() << "item_contains e_element_resize pitem, iItem : " << (::iptr) pitem << ", " << pitem->m_item.m_iItem;

      // }

      auto * puseritem = user_item(pitem);

      if (puseritem->m_ppath)
      {

         auto ppath = puseritem->m_ppath;

         auto pgraphics = get_internal_draw2d_graphics();

         if (ppath->contains(pgraphics, point))
         {

            return true;

         }

      }
      else
      {

         auto rectangle = user_item_rectangle(puseritem, ::user::e_layout_sketch);

         // if(pitem->m_item.m_eelement == e_element_resize)
         // {

         //    information() << "user_item_rectangle e_element_resize r : " << rectangle;
         //    information() << "user_item_rectangle e_element_resize r2 : " << puseritem->m_rectangle2;

         // }

         if (rectangle.contains(point))
         {

            // if(pitem->m_item.m_eelement == e_element_resize)
            // {

            //    information() << "user_item_rectangle e_element_resize contains point : " << point;

            // }

            return true;

         }

      }

      return false;

   }


   ::item_pointer interaction::on_items_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      for (auto [iIndex, pitemcontainer] : m_itemcontainermap)
      {

         auto pitemHitTest = on_items_hit_test(point, ezorder, iIndex, pitemcontainer->m_pitema);

         if (pitemHitTest)
         {

            return pitemHitTest;

         }

      }

      return nullptr;

   }


   ::item_pointer interaction::on_items_hit_test(const ::point_i32 & point, e_zorder ezorder, ::collection::index iIdContainer, ::item_array * pitema)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //auto pointScroll = point + m_pointScroll + m_pointBarDragScroll;

      auto pointScroll = point - m_pointBarDragScroll;

      if (::is_null(pitema))
      {

         return nullptr;

      }

      for (auto & pitem : pitema->rear_payloads())
      {

         if (!pitem || pitem->is_hidden())
         {

            continue;

         }

         auto * puseritem = user_item(pitem);

         if (!(puseritem->m_ezorder & ezorder))
         {

            continue;

         }

         if (item_contains(pitem, pointScroll))
         {

            // if(pitem->m_item.m_eelement == e_element_resize)
            // {

            //    information() << "on_items_hit_test e_element_resize item_contains";

            // }

            return pitem;

         }

      }

      return nullptr;

   }


   void interaction::defer_setup_default_bottom_right_resize_user_item()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      //information() << "defer_setup_default_bottom_right_resize_user_item";

      auto pitemResize = tool().item(e_element_resize);

      if (pitemResize)
      {

         // if(pitemResize->m_item.m_eelement == e_element_resize)
         // {

         //    information() << "defer_setup_default_bottom_right_resize_user_item resize item OK pitemResize.m_p : " << (::iptr) pitemResize.m_p;

         // }
         // else
         // {

         //    information() << "defer_setup_default_bottom_right_resize_user_item resize item NOK pitemResize.m_p : " << (::iptr) pitemResize.m_p;

         // }

         // information() << "defer_setup_default_bottom_right_resize_user_item resize item iItem : " << pitemResize->m_item.m_iItem;

         auto pdragResize = drag(pitemResize);

         if (pdragResize)
         {

            //information() << "defer_setup_default_bottom_right_resize_user_item resize drag";

            //auto pointScroll = point + m_pointScroll + m_pointBarDragScroll;

            auto rectangleResize = this->rectangle(::e_element_resize);

            //if (rectangleResize.ok() && rectangleResize.contains(point))
            if (rectangleResize.ok())
            {

               auto puseritem = user_item(pitemResize);

               puseritem->m_rectangle2 = rectangleResize;

               //information() << "defer_setup_default_bottom_right_resize_user_item resize rectangle : " << rectangleResize;

               //return pitemHitTest;

            }

         }

      }

      //return nullptr;

   }


   //   ::item_pointer interaction::on_client_area_hit_test(const ::point_i32 &point, e_zorder ezorder)
   //   {
   //
   //      if (m_pitemClient)
   //      {
   //
   //         if (item_contains(m_pitemClient, point))
   //         {
   //
   //            return m_pitemClient;
   //
   //         }
   //
   //         return nullptr;
   //
   //      }
   //
   //      return on_default_full_client_area_hit_test(point, ezorder);
   //
   //   }


   void interaction::defer_setup_default_client_area_user_item()
   {

      //if (ezorder & e_zorder_back)
      //{

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitemClient = tool().item(e_element_client);

      if (pitemClient)
      {

         auto pdragClient = drag(pitemClient);

         if (pdragClient)
         {

            setup_default_client_area_user_item();

         }

      }

      //      }
      //
      //      return nullptr;

   }


   void interaction::setup_default_client_area_user_item()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pitemClient = tool().item(e_element_client);

      if (pitemClient)
      {

         auto rectangleX = this->rectangle(::e_element_client);

         if (rectangleX.ok())
         {

            auto puseritem = user_item(pitemClient);

            puseritem->m_rectangle2 = rectangleX;

         }

      }

   }

   //bool interaction::get_rect(::item * pitem)
   //{

   //   auto pitem = get_user_item(*pitem);

   //   if (pitem)
   //   {

   //      item.m_rectangle = pitem->m_rectangle;

   //      return true;

   //   }

   //   if (!item.is_set())
   //   {

   //      return false;

   //   }

   //   this->rectangle(item.m_rectangle);

   //   return true;

   //}


   bool interaction::on_action(const ::string & pszId)
   {

      auto pinteractionParent = get_parent();

      if (::is_set(pinteractionParent))
      {

         if (pinteractionParent->on_action(pszId))
         {

            return true;

         }

      }

      return false;

   }


   bool interaction::keyboard_focus_is_focusable()
   {

      if (m_ekeyboardmode != e_keyboard_mode_none)
      {

         return true;

      }

      return false;

   }


   void interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //   auto pparent = get_parent();

      //   if (::is_null(pparent))
      //   {

      //      //::rectangle_i32 rectangleWindow;

      //      //window_rectangle(rectangleWindow, e_layout_design);

      //      //::rectangle_i32 rectangle(rectangleWindow);

      //      auto rectangle = this->rectangle();

      //      //rectangle.offset(-rectangle.top_left());

      //      auto pstyle = get_style(pgraphics);

      //      if (pgraphics->m_pimage->is_ok())
      //      {

      //         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //         if (windowing_window()->is_composite())
      //         {

      //            auto & iNcDraw0FillCounter = payload("nc_draw_0_fill_counter").i32_reference();

      //            iNcDraw0FillCounter++;

      //            //information() << "interaction::_001OnNcDraw set_transparent";

      //            pgraphics->payload("set_transparent") = "set_transparent";

      //            auto prectangleitem = __create_new < ::geometry2d::rectangle_item >();

      //            pgraphics->get_clip_box(prectangleitem->m_item);

      //            pgraphics->payload("set_transparent_clip_box") = "set_transparent";

      //            pgraphics->fill_rectangle(rectangle, argb(0, 0, 0, 0));

      //            // pgraphics->fill_rectangle(rectangle, ::color::white);

      //            //information().set_precision(1);

      //            //information() << "_001OnNcDraw Fill0Rect " << rectangle;

      ////dr               information() << "set_transparent window_rectangle " << rectangle;

      ////               information() << "set_transparent clip_box " << prectangleitem->m_item;

      //         }
      //         else
      //         {

      //            pgraphics->fill_rectangle(rectangle, argb(255, 192, 192, 192));

      //         }

      //      }
      //      else
      //      {

      //         if (windowing_window()->is_composite())
      //         {

      //            pgraphics->fill_rectangle(rectangle, argb(0, 0, 0, 0));

      //         }
      //         else
      //         {

      //            if (pstyle && pstyle->is_dark_mode())
      //            {

      //               pgraphics->fill_rectangle(rectangle, argb(255, 25, 25, 25));

      //            }
      //            else
      //            {

      //               pgraphics->fill_rectangle(rectangle, argb(255, 255, 255, 255));

      //            }

      //         }

      //      }

      //   }

      if (m_flagNonClient.has(e_non_client_background) && !top_level()->frame_is_transparent())
      {

         draw_control_background(pgraphics);

      }

   }


   void interaction::_001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

      if (m_flagNonClient.has(e_non_client_focus_rect) && keyboard_focus_is_focusable())
      {

         simple_ui_draw_focus_rect(pgraphics);

      }
      //else
      //{

      //   simple_ui_draw_border(pgraphics);

      //}

   }


   void interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!pgraphics->m_bDraw)
      {

         information() << "interaction::_001OnDraw !m_bDraw";

         return;

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->_001OnDraw(pgraphics);

      }

      //::user::interaction::_001OnDraw(pgraphics);
      //if (m_pitema && m_pitema->has_element())
      //{

      _001DrawItems(pgraphics);

      //}

   }


   //::user::item * interaction::_add_user_item(::item * pitem)
   //{

   //   auto iIndex = m_pitema->add(pitem);

   //   //m_itemmap[*pitem] = iIndex;

   //   auto puseritem = user_item(pitem);

   //   return puseritem;

   //}


   //::user::item * interaction::add_user_item(::item * pitem)
   //{

   //   if (is_sandboxed())
   //   {

   //      if (pitem->m_atom == ::id_close_app)
   //      {

   //         return nullptr;

   //      }
   //      else if (pitem->m_atom == ::id_maximize)
   //      {

   //         return nullptr;

   //      }
   //      else if (pitem->m_atom == ::id_minimize)
   //      {

   //         return nullptr;

   //      }

   //   }

   //   return _add_user_item(pitem);

   //}


   void interaction::_001DrawItems(::draw2d::graphics_pointer & pgraphics)
   {

      //return;

      for (auto & [iIndex, pitemcontainer] : m_itemcontainermap)
      {

         _001DrawItems(pgraphics, iIndex, pitemcontainer->m_pitema);

      }

   }


   void interaction::_001DrawItems(::draw2d::graphics_pointer & pgraphics, ::collection::index iIdContainer, ::item_array * pitema)
   {

      if (::is_null(pitema))
      {

         return;

      }

      int iCount = 0;

      for (auto & pitem : *pitema)
      {

         auto puseritem = user_item(pitem);

         ::user::e_state estate = ::user::e_state_none;

         if (::is_same_item(pitem, m_pitemHover))
         {

            estate |= ::user::e_state_hover;

         }

         _001DrawItem(pgraphics, *puseritem, estate);

         iCount++;

         //         if(iCount > 1)
         //         {
         //
         //            informationf("drawing 2nd, 3rd, nth item");
         //
         //         }

      }

   }


   void interaction::_001DrawItem(::draw2d::graphics_pointer & pgraphics, ::user::item & useritem, const ::user::e_state & estate)
   {

      if (!::is_item_set(&useritem))
      {

         return;

      }

      auto pitem = useritem.m_pitem;

      if (pitem->m_item.m_eelement == ::e_element_close_icon)
      {

         ::user::draw_close_icon(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_switch_icon)
      {

         ::user::draw_switch_icon(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_maximize_icon)
      {

         ::user::draw_maximize_icon(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_minimize_icon)
      {

         ::user::draw_minimize_icon(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_maximize_button)
      {

         ::user::draw_maximize_button(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_minimize_button)
      {

         ::user::draw_minimize_button(pgraphics, this, useritem, estate);

      }
      else if (pitem->m_item.m_eelement == ::e_element_switch_button)
      {

         ::user::draw_switch_button(pgraphics, this, useritem, estate);

      }

   }


   //pointer< ::sequence < ::conversation > > interaction::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
   //{

   //   auto pmessagebox = __create < ::user::message_box >();

   //   auto psequence = pmessagebox->show(this, strMessage, strTitle, emessagebox);

   //   return psequence;

   //}


   bool interaction::has_text_input()
   {

      return false;

   }


   void interaction::edit_on_set_focus(::user::interaction * pinteraction)
   {

      if (::is_null(window()))
      {

         return;

      }

      window()->edit_on_set_focus(pinteraction);

   }


   void interaction::edit_on_kill_focus(::user::interaction * pinteraction)
   {

      if (::is_null(window()))
      {

         return;

      }

      window()->edit_on_kill_focus(pinteraction);

   }


   void interaction::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      if (pstyle)
      {

         pstyle->simple_ui_draw_focus_rect(this, pgraphics);

      }

   }


   void interaction::simple_ui_draw_border(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      if (pstyle)
      {

         pstyle->simple_ui_draw_border(this, pgraphics);

      }

   }


   void interaction::get_text_composition_area(::rectangle_i32 & rectangle)
   {


   }



   void interaction::edit_on_text(string str)
   {

      //set_text(str, ::e_source_user);

      m_textproperty.set_text(str, ::e_source_user);

   }


   void interaction::edit_on_sel(strsize iBeg, strsize iEnd)
   {

      set_text_selection(iBeg, iEnd, e_source_sync);

   }


   void interaction::on_text_composition(string str)
   {

      auto psz = str.c_str();

      while (*psz)
      {

         string strCharacter = get_utf8_char(psz);

         int iCharacter = unicode_index(strCharacter);

         if (m_pappearance)
         {

            m_pappearance->on_character(iCharacter);

         }

         psz += strCharacter.length();

         if (strCharacter.length() <= 0)
         {

            break;

         }


      }

   }


   void interaction::on_text_composition_done()
   {


   }


   bool interaction::edit_undo()
   {

      return false;

   }


   //void interaction::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   if (ptopic->m_atom == ID_REDRAW || ptopic->m_atom == m_atom)
   //   {

   //      set_need_redraw();

   //      post_redraw();

   //   }
   //   else if (ptopic->m_atom == id_os_dark_mode)
   //   {

   //      set_need_redraw();

   //      post_redraw();

   //   }

   //}


   double interaction::_001GetTopLeftWeightedOccludedOpaqueRate()
   {

      if (!window())
      {

         return ::user::interaction_base::_001GetTopLeftWeightedOccludedOpaqueRate();

      }

      return window()->_001GetTopLeftWeightedOccludedOpaqueRate();

   }


   point_i32 interaction::screen_origin(enum_layout elayout)
   {

      auto puserinteraction = this;

      ::point_i32 point;

      while (puserinteraction)
      {

         if (!::is_null(puserinteraction->get_parent())
         || (windowing() && windowing()->has_readily_gettable_absolute_coordinates()))
         {

            point += puserinteraction->const_layout().origin(elayout);

         }

         puserinteraction = puserinteraction->get_parent();

      }

      return point;

   }


   point_i32 interaction::host_origin(enum_layout elayout)
   {

      auto puserinteraction = this;

      ::point_i32 point;

      while (puserinteraction)
      {

         auto pparent = puserinteraction->get_parent();

         if (!pparent)
         {

            pparent = puserinteraction->get_host_user_interaction();

            if (!pparent || pparent == puserinteraction)
            {

               break;

            }

         }

         point += puserinteraction->const_layout().origin(elayout);

         puserinteraction = pparent;

      }

      return point;

   }


   //::item_pointer interaction::get_child_as_item(::collection::index iIndex)
   //{

   //   if (!m_puserinteractionpointeraChild)
   //   {

   //      return nullptr;

   //   }

   //   if (iIndex < 0)
   //   {

   //      return nullptr;

   //   }

   //   if (iIndex >= m_puserinteractionpointeraChild->interaction_count())
   //   {

   //      return nullptr;

   //   }

   //   return m_puserinteractionpointeraChild->interaction_at(iIndex);

   //}


   //::collection::count interaction::get_child_as_item_count()
   //{

   //   if (!m_puserinteractionpointeraChild)
   //   {

   //      return 0;

   //   }

   //   return m_puserinteractionpointeraChild->interaction_count();

   //}


   ::user::interaction * interaction::child_at(::collection::index iIndex)
   {

      _synchronous_lock synchronouslock(window()->m_pparticleChildrenSynchronization);

      if (::is_null(m_puserinteractionpointeraChild))
      {

         return nullptr;

      }

      return m_puserinteractionpointeraChild->interaction_at(iIndex);


   }


   void interaction::on_item_selected(::item * pitem)
   {

   }


   void interaction::on_item_hover(::item * pitem)
   {

      m_pitemHover = pitem;

   }


   ::item_pointer interaction::hover_item()
   {

      return m_pitemHover;

   }


   ::shift_i32 interaction::screen_to_client(enum_layout elayout)
   {

      return -client_to_screen(elayout);

   }


   ::shift_i32 interaction::client_to_screen(enum_layout elayout)
   {

      return (::shift_i32(screen_origin(elayout)) - ::shift_i32(get_accumulated_scroll(elayout)));

   }


   ::shift_i32 interaction::parent_to_client(enum_layout elayout)
   {

      return -client_to_parent(elayout);

   }


   ::shift_i32 interaction::client_to_parent(enum_layout elayout)
   {

      return ::shift_i32(m_layout.origin(elayout)) - ::shift_i32(get_scroll(elayout));

   }


   ::shift_i32 interaction::host_to_client(enum_layout elayout)
   {

      return -client_to_host(elayout);

   }


   ::shift_i32 interaction::client_to_host(enum_layout elayout)
   {

      return (::shift_i32(host_origin(elayout)) - ::shift_i32(get_accumulated_scroll(elayout)));

   }


   ::shift_i32 interaction::host_to_raw(enum_layout elayout)
   {

      return -raw_to_host(elayout);

   }


   ::shift_i32 interaction::raw_to_host(enum_layout elayout)
   {

      return ::shift_i32(host_origin(elayout));

   }


   // void interaction::initial_frame_placement()
   // {


   // }


   //bool interaction::_001FancyInitialFramePlacement(bool bForceRestore)
   //{

   //   return false;

   //}

   //    ::rectangle_i32 rectangleWindow;

   //    bool bSet = false;

   //    ::pointer<::aura::application>papp = get_app();

   //    if (m_bExtendOnParent ||
   //       (m_bExtendOnParentIfClientOnly && papp->m_bExperienceMainFrame))
   //    {

   //       auto puserinteractionParent = get_parent();

   //       if (puserinteractionParent)
   //       {

   //          puserinteractionParent->rectangle(rectangleWindow);

   //          bSet = true;

   //       }

   //    }

   //    if (!bSet)
   //    {

   //       if (!_001FancyInitialFramePlacement(rectangleWindow, { 0.05, 0.05, 0.4, 0.4 }))
   //       {

   //          return false;

   //       }

   //    }

   //    display(e_display_normal);

   //    place(rectangleWindow);

   //    set_need_layout();

   //    set_need_redraw();

   //    post_redraw();

   //    return true;

   // }


   // bool interaction::_001FancyInitialFramePlacement(::rectangle_i32 * lprect, const rectangle_f64 & rectangleOptionalRateOrSize)
   // {

   //    return calculate_window_rectangle_in_main_monitor(lprect, rectangleOptionalRateOrSize);

   // }


   //void interaction::destroy()
   //{

   //   start_destroying_window();

   //}


   // please refer to object::finish verses/documentation
   // ::user::interaction implements custom/dedicated finish protocol/feature/function
   // this is why default finish isn't/(and shouldn't be) called here
   // (like is done for a regular object instance of *object* class)
   // (look at ::object::delete_this implementation to confirm/study the default finish call)
   void interaction::delete_this()
   {

      object::delete_this();

   }


   void interaction::display_system_minimize()
   {

      display(e_display_iconic);

   }


   bool interaction::has_compulsory_window_manager_decorations()
   {

#ifdef UNIVERSAL_WINDOWS

      return true;

#else

      return false;

#endif


   }


   bool interaction::should_show_platform_control_box()
   {

      if (has_compulsory_window_manager_decorations())
      {

         return false;

      }

      return true;

   }


   bool interaction::should_inline_notify_context_menu()
   {

#ifdef UNIVERSAL_WINDOWS

      return true;

#else

      if (is_sandboxed())
      {

         return true;

      }

      return false;

#endif

   }


   // updown
   bool interaction::wfi_is_up()
   {

      return m_eupdown == e_updown_up;

   }


   bool interaction::wfi_is_down()
   {

      return m_eupdown == e_updown_down;

   }


   bool interaction::wfi_has_up_down()
   {

      return m_ewindowflag & e_window_flag_updown;

   }
   // updown end



   //index interaction::GetEditItem()
   //{

   //   return m_iEditItem;

   //}


   //index interaction::GetEditSubItem()
   //{

   //   return (::collection::index) m_iSubItem;

   //}


   //void interaction::SetEditItem(::collection::index iItem)
   //{

   //   m_iEditItem = iItem;

   //}


   //void interaction::SetEditSubItem(::collection::index iSubItem)
   //{

   //   m_iSubItem = iSubItem;

   //}


   bool interaction::get_data(::pointer<::user::interaction> puserinteraction, ::payload & payload)
   {

      string str;

      if (m_econtroltype == e_control_type_edit)
      {

         ::pointer<::user::text> pedit = puserinteraction.m_p;

         if (pedit == nullptr)
            return false;

         str = pedit->as_text();

      }
      else
      {

         ::pointer<::user::text> ptext = this;

         if (!ptext)
         {

            return false;

         }

         str = ptext->as_text();

      }

      switch (m_edatatype)
      {
      case e_control_data_type_string:
      {
         payload = str;
      }
      return true;
      case e_control_data_type_natural:
      {
         payload = atoi(str);
         return true;
      }
      break;
      default:
         return false;
      }

   }


   ::data::data * interaction::_get_data(const ::atom & atom)
   {

      return nullptr;

   }


   bool interaction::has_function(enum_control_function econtrolfunction)
   {

      //if (m_pdescriptor.is_null())
      //{

      //   return false;

      //}

      //return ::user::interaction_base::has_function(econtrolfunction);

      return false;

   }


   //bool interaction::create_interaction(::user::interaction * pinteractionParent, const ::atom & atom)
   //{

   //   try
   //   {

   //      if (!create_interaction(pinteractionParent))
   //      {

   //         return false;

   //      }

   //   }
   //   catch (...)
   //   {

   //      return false;

   //   }

   //   m_bCreated = true;

   //   //m_controlmap[m_iItem] = this;

   //   return true;

   //}


   ::user::enum_state interaction::get_state()
   {

      auto psession = get_session();

      auto puser = psession->user();

      if (m_pdrawcontext != nullptr)
      {

         ::user::e_state estate = e_state_none;

         if (!is_window_enabled())
         {

            estate |= e_state_disabled;

         }


         auto pprimitiveFocus = puser->get_keyboard_focus(user_thread());

         if (pprimitiveFocus == this)
         {

            estate |= e_state_focused;

         }

         if (m_pdrawcontext->is_control_hover())
         {

            estate |= e_state_hover;

         }

         if (m_pdrawcontext->is_control_selected())
         {

            estate |= e_state_selected;

         }

         return estate;

      }
      else
      {

         ::user::e_state estate = ::user::e_state_none;

         if (!is_window_enabled())
         {

            estate |= e_state_disabled;

         }

         if (is_mouse_hover())
         {

            if (m_atom == "frame::e_button_transparent_frame")
            {

               information() << "is_mouse_hover in transparent_button";
               information() << "m_pitemHover " << ::as_string((iptr)m_pitemHover.m_p);

            }
            estate |= e_state_hover;

         }

         auto puserinteractionHost = get_host_user_interaction();

         if (::is_set(puserinteractionHost) && puserinteractionHost->has_keyboard_focus())
         {

            auto pwindow = puserinteractionHost->windowing_window();

            if (::is_set(pwindow))
            {

               if (pwindow->m_puserinteractionKeyboardFocus == this)
               {

                  estate |= e_state_focused;

               }

            }

         }

         //         auto pprimitiveFocus = puser->get_keyboard_focus(user_thread());
         //
         //         if (pprimitiveFocus == this)
         //         {
         //
         //            estate |= e_state_focused;
         //
         //         }

         return estate;

      }

      return ::user::interaction::get_state();

   }


   bool interaction::IsControlCommandEnabled()
   {

      return m_bControlExCommandEnabled;

   }


   void interaction::EnableControlCommand(bool bEnable)
   {

      m_bControlExCommandEnabled = bEnable;

      set_need_redraw();

   }


   void control_cmd_ui::enable(bool bOn)
   {

      m_bEnableChanged = true;

      ::pointer<::user::interaction> puserinteraction = m_puiOther;

      ASSERT(puserinteraction != nullptr);

      //ASSERT_KINDOF(::user::interaction, puserinteraction);

      ::pointer<::user::interaction> pinteraction = puserinteraction->get_child_by_id(m_atomControl);

      //      //::pointer<control>pcontrolex = (pinteraction.m_p);
      //
      //      if (pinteraction)
      //      {
      //
      //         if (bOn)
      //         {
      //
      //            if (puserinteraction->is_window_enabled() && !pinteraction->IsControlCommandEnabled())
      //            {
      //
      //               pinteraction->EnableControlCommand(true);
      //
      //            }
      //
      //         }
      //         else
      //         {
      //
      //            if (pinteraction->IsControlCommandEnabled())
      //            {
      //
      //               pinteraction->EnableControlCommand(false);
      //
      //            }
      //
      //         }
      //
      //      }
      //      else
      {

         if (pinteraction != nullptr)
         {

            if (bOn)
            {

               if (!pinteraction->is_window_enabled())
               {

                  pinteraction->enable_window();

               }

            }
            else
            {

               if (pinteraction->is_window_enabled())
               {

                  pinteraction->enable_window(false);

               }

            }

         }

      }

   }


   void control_cmd_ui::SetCheck(i32 nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
      /*::pointer<::user::interaction>puserinteraction = (::pointer<::user::interaction>_pOther;
      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(simple_toolbar, pToolBar);
      ASSERT(m_nIndex < m_nIndexMax);

      ::u32 nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
          nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
          nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & e_tool_item_style_separator));
      pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);*/
   }

   void control_cmd_ui::SetText(const ::string &)
   {
      // ignore it
   }


   atom control_cmd_ui::GetControlCommand(atom atom)
   {
      ::atom idCommand;
      if (m_mapControlCommand.lookup(atom, idCommand))
      {
         return atom;
      }
      return atom;
   }


   control_cmd_ui::control_cmd_ui()
   {

   }


   bool interaction::is_ok()
   {

      return ::is_set(this);

   }


   string interaction::get_class_style(string strClass)
   {

      if (strClass.is_empty())
      {

         return "";

      }

      if (!strClass.contains(','))
      {

         strClass.trim();

         string strStyle;

         if (m_puserinteractionParent)
         {

            strStyle += m_puserinteractionParent->get_class_style(strClass);

         }

         //if (m_pdescriptor->m_playout != NULL && m_puserinteractionParent != m_pdescriptor->m_playout)
         //{

         //   strStyle += m_pdescriptor->m_playout->get_class_style(strClass);

         //}

         //if (m_pdescriptor.is_set())
         //{

         //   strStyle += m_pdescriptor->m_mapClassStyle[strClass];

         //}

         return strStyle;

      }

      string_array straClass;

      straClass.add_tokens(strClass, ",", false);

      string strStyle;

      for (auto & str : straClass)
      {

         strStyle += get_class_style(str);

         if (strStyle.has_char())
         {

            strStyle += ";";

         }

      }

      return strStyle;

   }


   void interaction::set_class_style(string strClass, string strStyle)
   {

      if (strClass.contains(","))
      {

         throw ::exception(error_bad_argument);

      }

      m_mapClassStyle[strClass] = strStyle;

      //return true;

   }


   string interaction::get_full_style()
   {

      string strStyle = get_class_style(m_strClass);

      if (strStyle.has_char())
      {

         strStyle += ";";


      }

      strStyle += m_strStyle;

      return strStyle;

   }


   void interaction::sync_style()
   {

      string strStyle = get_full_style();

      load_style(strStyle);

   }


   void interaction::load_style(string strStyle)
   {

      string_array stra;

      stra.explode(";", strStyle);

      for (auto & str : stra)
      {

         string_array straItem;

         straItem.explode(":", str);

         if (straItem.get_size() == 2)
         {

            string strKey = straItem[0];

            strKey.trim();

            strKey.make_lower();

            string strValue = straItem[1];

            strValue.trim();

            strValue.make_lower();

            m_setStyle[strKey] = strValue;

            if (strKey.case_insensitive_order("padding") == 0)
            {

               //m_rectanglePadding.left() = atoi(strValue);
               //m_rectanglePadding.top() = atoi(strValue);
               //m_rectanglePadding.right() = atoi(strValue);
               //m_rectanglePadding.bottom() = atoi(strValue);


            }
            else if (strKey.case_insensitive_order("cell-padding") == 0)
            {

               //m_iCellPadding = atoi(strValue);

            }


         }

      }

   }


   void interaction::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      if (pcommand->is_handled(this))
      {

         return;

      }

      pcommand->handle(this);

      ::user::interaction_base::route_command(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      ::pointer<::user::interaction> puserinteractionParent = get_parent();

      if (puserinteractionParent)
      {

         puserinteractionParent->route_command(pcommand, false);

      }
      else
      {

         ::pointer<::apex::context> pcontext = get_context();

         if (pcontext)
         {

            pcontext->route_command(pcommand);

         }

      }

   }


   void interaction::_001OnEnable(::message::message * pmessage)
   {

      ::pointer<::message::enable> penable(pmessage);

      if (m_puiLabel != nullptr)
      {

         m_puiLabel->enable_window(penable->get_enable());

      }

   }


   void interaction::_001OnUpdateEditDelete(::message::message * pmessage)
   {

      ::pointer<::message::command> pcommand(pmessage);

      auto estatus = is_edit_delete_enabled();

      pcommand->enable(estatus == ::success);

      pmessage->m_bRet = true;

   }


   void interaction::_001OnEditDelete(::message::message * pmessage)
   {

      bool bRet = on_edit_delete(pmessage ? pmessage->m_actioncontext : action_context(::e_source_user));

      if (::is_set(pmessage))
      {

         pmessage->m_bRet = bRet;

      }

   }


   bool interaction::get_element_rectangle(::rectangle_i32 & rectangle, enum_element eelement)
   {

      if (eelement == e_element_client)
      {

         if (!m_bEmptyAreaIsClientArea)
         {

            return false;

         }

         rectangle = this->rectangle();

         return true;

      }
      else if (eelement == e_element_resize)
      {

         auto pitemResize = tool().item(e_element_resize);

         if (!has_drag(pitemResize))
         {

            return false;

         }

         rectangle = this->rectangle();

         rectangle.left() = maximum(rectangle.left(), rectangle.right() - 25);
         rectangle.top() = maximum(rectangle.top(), rectangle.bottom() - 25);

         return true;

      }
      else if (eelement == e_element_drop_down)
      {

         auto pitemDropDown = tool().item(e_element_drop_down);

         //if (!has_drag(pitemDropDown))
         //{

         //   return false;

         //}

         auto rectangleX = this->rectangle();

         //i32 iMargin = rectangleX.height() / 8;
         i32 iMargin = 0;

         ::rectangle_i32 rectangleDropDown;

         rectangleDropDown = rectangleX;

         i32 iW = rectangleX.height() * 5 / 8;

         rectangleDropDown.right() -= iMargin;
         rectangleDropDown.bottom() -= iMargin;
         rectangleDropDown.top() += iMargin;
         rectangleDropDown.left() = rectangleDropDown.right() - iW;

         rectangle = rectangleDropDown;

         return true;

      }
      else if (eelement == e_element_combo_edit)
      {

         auto rectangleX = this->rectangle();

         ::rectangle_i32 rectangleDropDown;

         get_element_rectangle(rectangleDropDown, e_element_drop_down);

         ::rectangle_i32 rectangleEdit = rectangleX;

         rectangleEdit.right() = rectangleDropDown.left();

         //::rectangle_i32 rectanglePadding = _001GetRect(::user::rect_edit_padding);

         //rectangleEdit.deflate(rectanglePadding);

         rectangle = rectangleEdit;

         return true;

      }
      else if (eelement == e_element_close_button)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 32;

         rectangle.bottom() = rectangle.top() + 32;

         return true;

      }
      else if (eelement == e_element_maximize_button)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 64;

         rectangle.right() = rectangle.left() + 32;

         rectangle.bottom() = rectangle.top() + 32;

         return true;

      }
      else if (eelement == e_element_minimize_button)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 96;

         rectangle.right() = rectangle.left() + 32;

         rectangle.bottom() = rectangle.top() + 32;

         return true;

      }
      else if (eelement == e_element_close_icon)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 48;

         rectangle.bottom() = rectangle.top() + 48;

         return true;

      }
      else if (eelement == e_element_switch_button)
      {

         rectangle = this->rectangle();

         rectangle.right() = rectangle.right() - 48;

         rectangle.left() = rectangle.right() - 48;

         rectangle.top() = rectangle.bottom() - 48;

         return true;

      }
      else if (eelement == e_element_maximize_icon)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 96;

         rectangle.right() = rectangle.left() + 48;

         rectangle.bottom() = rectangle.top() + 48;

         return true;

      }
      else if (eelement == e_element_minimize_icon)
      {

         rectangle = this->rectangle();

         rectangle.left() = rectangle.right() - 144;

         rectangle.right() = rectangle.left() + 48;

         rectangle.bottom() = rectangle.top() + 48;

         return true;

      }

      return false;

   }


   ::rectangle_f64 interaction::user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout)
   {

      if (puseritem->m_euseritemflag & ::user::e_item_flag_rectangle_callback)
      {

         return _user_item_rectangle(puseritem, elayout);

      }

      return puseritem->m_rectangle2;

   }


   ::rectangle_f64 interaction::_user_item_rectangle(::user::item * puseritem, ::user::enum_layout elayout)
   {

      return puseritem->m_rectangle2;

   }


   status < rectangle_i32 > interaction::item_rectangle(::item * pitem, ::user::enum_layout elayout)
   {

      if (!::is_item_set(pitem))
      {

         return error_failed;

      }

      auto puseritem = user_item(pitem);

      auto rectangle = user_item_rectangle(puseritem, elayout);

      return ::rectangle_i32(rectangle);

   }


   ::draw2d::path_pointer interaction::item_graphics_path(::item * pitem)
   {

      if (!::is_item_set(pitem))
      {

         return nullptr;

      }

      auto puseritem = user_item(pitem);

      return puseritem->m_ppath;

   }


   void interaction::get_simple_drop_down_open_arrow_polygon(point_f64_array & pointa)
   {

      ::rectangle_i32 rectangleDropDown;

      get_element_rectangle(rectangleDropDown, e_element_drop_down);

      i32 cx = rectangleDropDown.width() / 3;

      i32 cy = cx * 2 / 3;

      ::point_i32 pointCenter = rectangleDropDown.center();

      pointa.add(pointCenter.x() - cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x() + cx / 2, pointCenter.y() - cy / 2);

      pointa.add(pointCenter.x(), pointCenter.y() + cy / 2);

   }



   //control_descriptor::control_descriptor()
   //{

   //   control_descriptor_common_construct();

   //}


   //control_descriptor::control_descriptor(arguments arguments)
   //{

   //   control_descriptor_common_construct();

   //   for (auto & argument : arguments)
   //   {

   //      auto etype = argument.get_type();

   //      switch (etype)
   //      {
   //      case type_type:
   //      {

   //         m_type.m_strName = argument.m_str;

   //         break;

   //      }
   //      case e_type_string:
   //      {

   //         string str = argument.get_string();

   //         if (str.case_insensitive_begins_eat("class="))
   //         {

   //            m_strClass = str;

   //         }
   //         else if (str.case_insensitive_begins_eat("style="))
   //         {

   //            m_strStyle = str;

   //         }
   //         else
   //         {

   //            m_atom = argument.get_id();

   //         }

   //         break;
   //      };
   //      case e_type_id:
   //      case e_type_i64:
   //      case e_type_i32:
   //      {

   //         m_atom = argument.get_id();

   //         break;

   //      }
   //      case e_type_element:
   //      {

   //         //auto pinteraction = argument.cast < interaction >();

   //         //if (pinteraction)
   //         //{

   //         //   if (::is_null(this))
   //         //   {

   //         //      set_object(pinteraction);

   //         //   }

   //         //   if (pinteraction->is_window())
   //         //   {

   //         //      m_puserinteractionParent = pinteraction;

   //         //      break;

   //         //   }
   //         //   else
   //         //   {

   //         //      m_pusercontrol = pinteraction;

   //         //      break;

   //         //   }

   //         //}

   //         //auto playout = argument.cast < layout >();

   //         //if (playout)
   //         //{

   //         //   if (::is_null(this))
   //         //   {

   //         //      set_object(playout);

   //         //   }

   //         //   m_playout = playout;

   //         //}

   //         //if (::is_null(this))
   //         //{

   //         //   set_object(argument.cast < ::object > ());

   //         //}

   //      }
   //      break;
   //      default:
   //         break;

   //      }

   //   }

   //}

   //control_descriptor::~control_descriptor()
   //{

   //   //if(m_pcontrol != nullptr)
   //   //{

   //   //   if(m_bCreated)
   //   //   {

   //   //      m_pcontrol->start_destroying_window();

   //   //   }
   //   //   else if(m_bSubclassed)
   //   //   {

   //   //      m_pcontrol->unsubclass_window();

   //   //   }

   //   //   m_pcontrol.release();

   //   //}

   //}


   /*void control_descriptor::control_descriptor_common_construct()
      {

         m_atom.is_empty();
         m_iItem = 0;
         m_econtroltype = e_control_type_none;
         m_bTransparent = false;
         m_bCreated = false;
         m_edatatype = e_control_data_type_string;
         m_flagsfunction.clear();
         m_controlmap.erase_all();
         m_bSubclassed = false;
         m_iSubItem = -1;
         m_iColumn = -1;

      }*/


      //void control_descriptor::clear()
      //{

      //   m_playout = nullptr;
      //   m_puserinteractionParent = nullptr;
      //   m_playout = nullptr;
      //   m_atom.is_empty();
      //   m_iItem = 0;
      //   m_econtroltype = e_control_type_none;
      //   m_bTransparent = false;
      //   m_bCreated = false;
      //   m_edatatype = e_control_data_type_string;
      //   m_flagsfunction.clear();
      //   m_controlmap.erase_all();
      //   m_bSubclassed = false;
      //   m_iSubItem = -1;
      //   m_iColumn = -1;

      //}




      //control_descriptor::control_descriptor(const class control_descriptor & control_descriptor)
      //{

      //   operator =(control_descriptor);

      //}


      //class control_descriptor & control_descriptor::operator = (const control_descriptor & control_descriptor)
      //{

      //   if (&control_descriptor == this)
      //      return *this;

      //   m_iItem = control_descriptor.m_iItem;
      //   m_atom = control_descriptor.m_atom;
      //   m_econtroltype = control_descriptor.m_econtroltype;
      //   m_strDataKey = control_descriptor.m_strDataKey;
      //   m_bTransparent = control_descriptor.m_bTransparent;
      //   m_flagsfunction = control_descriptor.m_flagsfunction;
      //   m_type = control_descriptor.m_type;
      //   m_bCreated = control_descriptor.m_bCreated;
      //   m_edatatype = control_descriptor.m_edatatype;
      //   m_atomPrivateDataSection = control_descriptor.m_atomPrivateDataSection;
      //   //m_pcontrol              = control_descriptor.m_pcontrol;
      //   m_controlmap.erase_all();
      //   m_eddx = control_descriptor.m_eddx;
      //   m_puserinteractionParent = control_descriptor.m_puserinteractionParent;
      //   m_iSubItem = control_descriptor.m_iSubItem;
      //   m_iColumn = control_descriptor.m_iColumn;
      //   m_setValue = control_descriptor.m_setValue;
      //   m_iSubItemDisableCheckBox = control_descriptor.m_iSubItemDisableCheckBox;
      //   m_iSubItemDuplicateCheckBox = control_descriptor.m_iSubItemDuplicateCheckBox;
      //   m_iaSubItemDuplicate = control_descriptor.m_iaSubItemDuplicate;
      //   m_iaSubItemDisable = control_descriptor.m_iaSubItemDisable;

      //   return *this;

      //}


      /*::database::client * control_descriptor::get_data_client()
         {
            if(m_puserinteraction == nullptr)
            {

               return nullptr;

            }

            return dynamic_cast < ::database::client * > (m_puserinteraction);

         }*/


         //  bool control_descriptor::operator == (const control_descriptor & descriptor) const
         //  {

         ///*     if (m_pusercontrol && ::is_set(descriptor.m_pusercontrol))
         //     {

         //        return m_pusercontrol == descriptor.m_pusercontrol;

         //     }*/

         //     return m_atom == descriptor.m_atom && m_puserinteractionParent->descriptor() == descriptor.m_puserinteractionParent->descriptor();

         //  }


   void interaction::add_function(enum_control_function enum_control_function)
   {

      m_flagsfunction.add(enum_control_function);

   }


   void interaction::erase_function(enum_control_function enum_control_function)
   {

      m_flagsfunction.erase(enum_control_function);

   }


   //   bool interaction::has_function(enum_control_function enum_control_function)
   //   {
   //
   //      return m_flagsfunction.has(enum_control_function);
   //
   //   }


   void interaction::set_data_type(enum_control_data_type edatatype)
   {

      m_edatatype = edatatype;

   }


   enum_control_data_type interaction::get_data_type()
   {

      return m_edatatype;

   }


   void interaction::set_ddx_dbflags(const ::scoped_string & scopestr, iptr value)
   {

      m_eddx = ::user::e_control_ddx_dbflags;

      //m_strDataKey = datakey;

      m_iDataValue = (int)value;

   }


   void interaction::set_control_type(enum_control_type econtroltype)
   {

      m_econtroltype = econtroltype;

      switch (m_econtroltype)
      {
      case e_control_type_edit:

         //         m_type = ::type < CSimpleFormListEdit >();

         break;

      case e_control_type_combo_box:
      {

         //throw ::exception(todo);

   //            m_data.m_pcombobox = __new Ex1FormInterfaceComboBox();

      }
      break;
      default:
         break;
      }

   }


   string interaction::get_class_name()
   {

      auto econtroltype = get_control_type();

      auto papp = get_app();

      string strClassName = papp->get_window_class_name(econtroltype);

      return strClassName;

   }


#ifdef WINDOWS_DESKTOP


   void interaction::_task_transparent_mouse_event()
   {

      if (!window())
      {

         return;

      }

      window()->_task_transparent_mouse_event();

   }


#endif


   //callback* interaction::get_user_callback()
   //{

   //   return nullptr;

   //}


   //oswindow interaction::get_oswindow() const
   //{

   //   auto puserinteraction = get_wnd();

   //   if (::is_null(puserinteraction))
   //   {

   //      return nullptr;

   //   }

   //   auto pwindow = puserinteraction->windowing_window();

   //   if (::is_null(pwindow))
   //   {

   //      return nullptr;

   //   }

   //   return pwindow->get_oswindow();

   //}


   ::aura::application * interaction::get_app()
   {

      return m_pcontext && m_pcontext->m_pacmeapplication->m_papexapplication
         ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;

   }


   ::aura::session * interaction::get_session()
   {

      return m_pcontext ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   //::aura::system * interactionacmesystem()
   //{

   //   return system() ? system()->m_paurasystem : nullptr;

   //}


   ::aura::context * interaction::context()
   {

      return m_pcontext ? m_pcontext->m_pauracontext : nullptr;

   }


   double interaction::screen_scaler()
   {

      return m_pinteractionScaler->screen_scaler();

   }


   double interaction::font_scaler()
   {

      return m_pinteractionScaler->font_scaler();

   }


   //   bool interaction::is_this_visible(enum_layout elayout)
   //   {
   //
   //      return m_layout.is_this_visible(elayout);
   //
   //   }


   bool interaction::is_this_screen_visible(enum_layout elayout)
   {

      return m_layout.is_this_screen_visible(elayout);

   }


   bool interaction::is_window_visible(enum_layout elayout)
   {

      if (m_puserinteractionParent
         && !m_puserinteractionParent->is_window_visible(elayout))
      {

         return false;

      }

      return is_this_visible(elayout);

   }


   bool interaction::is_window_screen_visible(enum_layout elayout)
   {

      return m_puserinteractionParent && !m_puserinteractionParent->is_window_screen_visible(elayout) ? false
         : is_screen_visible(
   m_layout.state(elayout).display());

   }


   //   bool interaction::has_fps_interest() const noexcept
   //   {
   //
   //      return windowing_window() ? windowing_window()->has_fps_interest() : false;
   //
   //   }


      //void interaction::pick_single_file(
      //   const ::array < ::pair < ::string, ::string > >& filetypes,
      //   const ::function < void(const ::file::path &) >& function,
      //   bool save)
      //{
      //
      //      node()->pick_single_file(oswindow(),
      //                                   filetypes,
      //                                   function,
      //                                   save);
      //
      //}
      //
      //
      //void interaction::pick_multiple_file(
      //   const ::array < ::pair < ::string, ::string > > & filetypes,
      //   const ::function < void(const ::file::path_array &) >& function)
      //{
      //
      //   node()->pick_multiple_file(oswindow(),
      //                                filetypes,
      //                                function);
      //
      //}
      //
      //
      //void interaction::pick_single_folder(
      //   //const ::array < ::pair < ::string, ::string > >& filetypes,
      //                        const ::function < void(const ::file::path &) >& function)
      //                        //,       bool save);
      //{
      //
      //   node()->pick_single_folder(oswindow(),
      //                                function);
      //
      //}


      //::user::interaction * message_user_interaction(::user::message * pusermessage)
      //{

      //   auto pimpl = message_interaction_impl(pusermessage);

      //   return pimpl ? pimpl->m_puserinteraction : nullptr;

      //}


   bool interaction::on_impact_update()
   {

      m_layout.m_statea[e_layout_sketch].m_bImpactUpdateGoingOn = true;

      return true;

   }


   void interaction::set_opacity(double dOpacity)
   {

      //if (::is_null(window()))
      //{

      //   return;

      //}

      //window()->set_opacity(dOpacity);

   }


} // namespace user


::point_i32 g_pointAuraTopRight;


CLASS_DECL_AURA::point_i32 __get_top_right()
{

   return g_pointAuraTopRight;

}


CLASS_DECL_AURA void __set_top_right(const ::point_i32 & pointTopRight)
{

   g_pointAuraTopRight = pointTopRight;

}


::point_i32 g_pointAuraBottomRight;


CLASS_DECL_AURA::point_i32 __get_bottom_right()
{

   return g_pointAuraBottomRight;

}


CLASS_DECL_AURA void __set_bottom_right(const ::point_i32 & pointBottomRight)
{

   g_pointAuraBottomRight = pointBottomRight;

}


