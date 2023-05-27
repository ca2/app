#include "framework.h"
#include "interaction_child.h"
#include "scroll_info.h"
#include "alpha_source.h"
#include "interaction.h"
#include "interaction_impl.h"
#include "interaction_scaler.h"
#include "interaction_thread.h"
#include "style.h"
#include "user.h"
#include "frame.h"
#include "form.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/constant/message_prototype.h"
#include "acme/constant/simple_command.h"
#include "acme/handler/item.h"
#include "acme/platform/keep.h"
#include "acme/user/user/drag.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/node.h"
#include "acme/platform/timer.h"
#include "acme/platform/timer_array.h"
#include "acme/platform/scoped_restore.h"
#include "acme/primitive/geometry2d/_enhanced.h"
#include "acme/primitive/geometry2d/_collection_enhanced.h"
#include "acme/primitive/geometry2d/_defer_shape.h"
#include "acme/primitive/geometry2d/_text_stream.h"
#include "acme/primitive/string/international.h"
#include "acme/primitive/time/_string.h"
#include "apex/message/simple_command.h"
#include "apex/user/message.h"
#include "aqua/user/controller.h"
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
#ifdef WINDOWS_DESKTOP
//#include "acme/_operating_system.h"
#endif


#define INFO_LAYOUT_DISPLAY




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
#define TEST_PRINT_BUFFER

#ifdef WINDOWS_DESKTOP
//#include "aura/operating_system/windows/windowing.h"
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#elif defined(UNIVERSAL_WINDOWS)

//#include "aura/os/universal_windows/_uwp.h"

#endif // UNIVERSAL_WINDOWS

//#define memory_new AURA_NEW


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


      m_bVisualChanged = false;


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

      m_bExtendOnParent = false;
      m_bExtendOnParentIfClientOnly = false;

      m_bToolWindow = false;
      m_bMessageWindow = false;
      m_bCompositedFrameWindow = false;

      m_bEdgeGestureDisableTouchWhenFullscreen = false;
      m_bVisible = false;

      m_bPendingZorder = false;

      m_bMouseHoverOnCapture = false;
      //m_bMouseHover = false;
      m_bClickDefaultMouseHandling = false;
      m_bHoverDefaultMouseHandling = false;
      m_bEditDefaultHandling = false;
      m_bKeyboardMultipleSelectionDefaultHandling = false;
      m_bDataUpdateDefaultHandling = false;
      //m_bLockSketchToDesign = false;
      m_bParentScrollX = false;
      m_bParentScrollY = false;
      m_bUserInteractionHost = false;
      m_bEnableDragClient = false;
      m_bEnableDragResize = false;

      //m_pinteractiondraw2d = nullptr;

      m_bSketchToDesignLayout = false;

      //m_uUserInteractionFlags = 0;

      m_bEnableDragClient = false;

      m_bEnableDragResize = false;

      //m_bTaskPending = true;

      //m_pprimitiveimplBase = nullptr;

      m_bEdgeGestureDisableTouchWhenFullscreen = true;

      //m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown = false;

      m_bUserInteractionHost = false;

      m_bMouseHoverOnCapture = false;

      m_bCompositedFrameWindow = true;

      m_oswindow = nullptr;

      //m_playout = nullptr;

      //m_puserinteractionParent = nullptr;

      m_bExtendOnParentIfClientOnly = false;

      m_bExtendOnParent = false;

      m_bDerivedHeight = false;

      m_bLayoutModified = false;

      m_ewindowflag += e_window_flag_enable | e_window_flag_graphical;

      //#ifdef __APPLE__

      //m_puserinteraction->m_ewindowflag |= e_window_flag_postpone_visual_update;

      //#endif

      //m_bFocus = false;

      m_bParentScrollX = true;
      m_bParentScrollY = true;

      m_bUserInteractionSetFinish = false;

      m_timeMouseMoveIgnore = 20_ms;

      m_bOverdraw = false;

      m_bEditDefaultHandling = false;

      m_bClickDefaultMouseHandling = false;

      m_bHoverDefaultMouseHandling = false;

      m_bKeyboardMultipleSelectionDefaultHandling = false;

      m_iIndex = -1;

      m_ewindowflag |= e_window_flag_enable;

      m_iMouseMoveSkipCount = 0;

      int iMouseMoveTriggerDistance = 10;

      m_iMouseMoveSkipSquareDistance = iMouseMoveTriggerDistance * iMouseMoveTriggerDistance;

      m_timeMouseMovePeriod = 5_ms;

      m_bOffScreenRender = false;

      m_uiUserInteractionFlags = 0;

      m_eupdown = ::user::interaction::e_updown_normal_frame;

      //m_playout = NULL;

      m_bWfiUpDownTarget = false;

      m_puserinteraction = this;

      m_dItemHeight = -1;

      m_flagNonClient.add(e_non_client_background);

      m_flagNonClient.add(e_non_client_focus_rect);

      //m_bMouseHover = false;

      m_bNeedRedraw = false;

      m_bRedrawOnVisible = false;

      m_bUpdateVisual = false;

      m_bNeedLayout = false;

      //m_bLockSketchToDesign = false;

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

      m_bDefaultWalkPreTranslateParentTree = false;

      m_bMoveWindow = false;

      m_bSizeMove = false;

      //m_bEatsDoubleClick = true;

      m_pointScroll.x() = 0;
      m_pointScroll.y() = 0;
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

      m_puserinteractionTopLevel = nullptr;
      m_puserframeTopLevel = nullptr;
      m_puserframeParent = nullptr;
      m_pwindow = nullptr;
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

      ::user::primitive::on_initialize_particle();

      if (m_bEnableDragClient)
      {

         m_bHoverDefaultMouseHandling = true;

         m_bClickDefaultMouseHandling = true;

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


   void interaction::set_restored_rectangle(const ::rectangle_i32& rectangleRestored)
   {

   }


   void interaction::set_position(const ::point_i32& point, enum_layout elayout)
   {

      if (on_set_position(point, elayout))
      {

         m_layout.m_statea[elayout].m_point = point;

      }

   }


   void interaction::set_size(const ::size_i32& size, enum_layout elayout)
   {

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

      }

   }


   void interaction::set_width(::i32 width, enum_layout elayout)
   {

      auto size = this->size(elayout);

      size.cx = width;

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

      }

   }


   void interaction::set_height(::i32 height, enum_layout elayout)
   {

      auto size = this->size(elayout);

      size.cy = height;

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

      }

   }


   void interaction::shift_left(::i32 left, enum_layout elayout)
   {

      auto point = this->position(elayout);

      auto size = this->size(elayout);

      size.cx += point.x() - left;

      point.x() = left;

      bool bOnSetSize = on_set_size(size, elayout);

      bool bOnSetPosition = on_set_position(point, elayout);

      if (bOnSetSize && bOnSetPosition)
      {

         m_layout.m_statea[elayout].m_point = point;

         m_layout.m_statea[elayout].m_size = size;

      }

   }


   void interaction::set_right(::i32 right, enum_layout elayout)
   {

      auto point = this->position(elayout);

      auto size = this->size(elayout);

      point.x() = right - size.cx;

      if (on_set_position(point, elayout))
      {

         m_layout.m_statea[elayout].m_point = point;

      }

   }


   void interaction::set_top(const ::i32 top, enum_layout elayout)
   {

      auto point = position(elayout);

      point.y() = top;

      if (on_set_position(point, elayout))
      {

         m_layout.m_statea[elayout].m_point = point;

      }

   }


   bool interaction::on_set_position(const ::point_i32& point, enum_layout elayout)
   {

      return true;

   }


   bool interaction::on_set_size(const ::size_i32& size, enum_layout elayout)
   {

      string strType = typeid(*this).name();

      if (strType.case_insensitive_contains("control_box"))
      {

         if (strType.case_insensitive_contains("button"))
         {

         }
         else
         {

            //output_debug_string("control_box::on_set_size(" + as_string(size) + ")");

            //if (size.cx > 500)
            //{

            //   output_debug_string("size.cx > 500");

            //}

         }

      }

      return true;

   }


   //interaction_draw2d * interaction::get_draw2d()
   //{

   //   if(::is_null(m_pinteractiondraw2d))
   //   {


   //      m_pinteractiondraw2d = memory_new interaction_draw2d();

   //   }

   //   return m_pinteractiondraw2d;

   //}


   double interaction::point_dpi(double d)
   {

      auto pwindow = window();

      double dTransformed = pwindow->point_dpi((float)d);

      return dTransformed;

   }


   double interaction::dpiy(double d)
   {

      auto pwindow = window();

      double dTransformed = pwindow->dpiy((float)d);

      return dTransformed;

   }


   float interaction::get_dpi_for_window()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return 96.0f;

      }

      return pwindow->get_dpi_for_window();

   }


   float interaction::get_density_for_window()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return 1.0f;

      }

      return pwindow->get_density_for_window();

   }


   ::string interaction::calculate_data_key()
   {

      return m_atom;

   }


   ::string interaction::get_data_key(const ::scoped_string& scopedstrAppend)
   {

      if (m_strDataKey20.is_empty())
      {

         m_strDataKey20 = calculate_data_key();

      }

      return m_strDataKey20 + "." + scopedstrAppend;

   }



   ::windowing::window* interaction::window()
   {

      auto puserinteractionTopLevel = ((interaction*)this)->_top_level();

      if (::is_null(puserinteractionTopLevel))
      {

         return nullptr;

      }

      auto pinteractionimpl = puserinteractionTopLevel->m_pinteractionimpl;

      if (::is_null(pinteractionimpl))
      {

         if (::is_set(puserinteractionTopLevel->m_puserinteractionParent))
         {

            pinteractionimpl = puserinteractionTopLevel->m_puserinteractionParent->m_pinteractionimpl;

         }

         if (::is_null(pinteractionimpl))
         {

            return nullptr;

         }

      }

      auto pwindow = pinteractionimpl->m_pwindow;

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      return pwindow;

   }


   ::user::copydesk* interaction::copydesk()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      auto pcopydesk = pwindow->copydesk();

      if (::is_null(pcopydesk))
      {

         return nullptr;

      }

      return pcopydesk;

   }


   ::windowing::windowing* interaction::windowing()
   {

      auto pwindow = m_pwindow;

      if (::is_null(pwindow))
      {

         auto psession = get_session();

         auto puser = psession->user();

         auto pwindowing = puser->windowing();

         return pwindowing;

      }

      auto pwindowing = pwindow->m_pwindowing;

      if (::is_null(pwindowing))
      {

         return nullptr;

      }

      return pwindowing;

   }


   ::windowing::display* interaction::get_display()
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


   ::user::interaction* interaction::get_host_window()
   {

      auto psession = get_session();

      if (psession == nullptr)
      {

         return nullptr;

      }

      ::pointer<::user::interaction>puserinteractionHost = psession->m_puserprimitiveHost;

      if (puserinteractionHost)
      {

         return puserinteractionHost;

      }

      return get_wnd();

   }


   ::user::interaction_impl* interaction::get_window_impl()
   {

      auto puserinteraction = get_host_window();

      if (::is_null(puserinteraction))
      {

         return nullptr;

      }

      auto puserinteractionimpl = puserinteraction->m_pinteractionimpl;

      if (::is_null(puserinteractionimpl))
      {

         return nullptr;

      }

      return puserinteractionimpl;

   }


   enum_element interaction::get_default_element()
   {

      return e_element_none;

   }


   ::write_text::font_pointer interaction::get_font(style* pstyle, enum_element eelement, ::user::enum_state estate)
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


   enum_translucency interaction::get_translucency(style* pstyle)
   {

      if (pstyle)
      {

         return pstyle->m_etranslucency;

      }

      return e_translucency_undefined;

   }


   int interaction::get_int(style* pstyle, enum_int eint, ::user::enum_state estate, int iDefault)
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


   double interaction::get_double(style* pstyle, enum_double edouble, ::user::enum_state estate, double dDefault)
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


   status<::rectangle_f64> interaction::get_border(style* pstyle, enum_element eelement, ::user::enum_state estate)
   {

      return nullptr;

   }


   status<::rectangle_f64> interaction::get_padding(style* pstyle, enum_element eelement, ::user::enum_state estate)
   {

      if (get_control_type() == ::user::e_control_type_button)
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


   status<::rectangle_f64> interaction::get_margin(style* pstyle, enum_element eelement, ::user::enum_state estate)
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


   status<::color::color> interaction::get_color(style* pstyle, enum_element eelement, ::user::enum_state estate)
   {

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


   ::user::e_flag interaction::get_draw_flags(::user::style* pstyle)
   {

      return e_null;

   }


   style* interaction::get_style()
   {

      auto pframe = top_level_frame();

      if (pframe && pframe->m_puserstyle)
      {

         return pframe->m_puserstyle;

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pstyleSession = puser->user_style();

      return pstyleSession;

   }


   ::user::style* interaction::get_style(::draw2d::graphics_pointer& pgraphics)
   {

      return pgraphics ? get_style(pgraphics->m_puserstyle) : get_style();

   }


   void interaction::on_tsf_activate(bool bActivate)
   {

      m_pinteractionimpl->on_tsf_activate(bActivate);

   }


   string interaction::default_id_prefix()
   {

      return __type_name(this) + "_";

   }


   void interaction::child_set_unique_id(::user::interaction* pinteraction)
   {

      if (pinteraction->m_atom.has_char())
      {

         return;

      }

      string strDefaultIdPrefix;

      string strCandidateId;

      bool bDuplicate = true;

      //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      for (index iIdSuffix = 1; iIdSuffix <= 1000; iIdSuffix++)
      {

         strCandidateId.format("%s_%d", strDefaultIdPrefix.c_str(), iIdSuffix);

         bDuplicate = false;

         for (auto& pinteraction : puserinteractionpointeraChild->interactiona())
         {

            if (pinteraction->m_atom == strCandidateId)
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

   //   auto pdescriptor = __new(control_descriptor(arguments));

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

   //   //auto pdescriptor = __new(control_descriptor());


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


   interaction* interaction::get_tooltip()
   {

      return m_ptooltip;

   }


   void interaction::set_tool_window(bool bSet)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         m_bToolWindow = true;

         //return ::error_failed;

         return;

      }

      //auto estatus = 

      m_pprimitiveimpl->set_tool_window(bSet);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_bToolWindow = bSet;

      //return ::success;

   }


   void interaction::set_reposition(bool bSetThis)
   {

      //synchronous_lock synchronouslock(mutex_children());

      _set_reposition(bSetThis);

   }


   void interaction::_set_reposition(bool bSetThis)
   {

      if (bSetThis)
      {

         m_bReposition = true;

      }

   }


   void interaction::set_need_layout(bool bAscendants)
   {

      m_bNeedLayout = true;

   }


   void interaction::set_need_redraw(const ::rectangle_i32& rectangleNeedRedraw, bool bAscendants)
   {

      auto* pinteraction = get_wnd();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto rectangle = rectangleNeedRedraw;

      if (rectangle.is_empty())
      {

         rectangle = client_rectangle();

      }

      pinteraction->m_bNeedRedraw = true;

      auto edisplayRequest = pinteraction->layout().sketch().display();

      auto edisplayState = pinteraction->layout().window().display();

      if (pinteraction->m_pprimitiveimpl.is_set() &&
         (
            layout().sketch().is_screen_visible() || edisplayState != edisplayRequest
            ))
      {

         auto rectangleHost = rectangle;

         client_to_host()(rectangleHost);

         pinteraction->m_pprimitiveimpl->set_need_redraw(rectangleHost);

      }

   }


   bool interaction::needs_to_draw(::draw2d::graphics* pgraphics, const ::rectangle_i32& rectangleNeedsToDraw)
   {

      if(get_host_window()->has_prodevian())
      {

         return true;

      }

      auto* pinteraction = get_wnd();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto rectangle = rectangleNeedsToDraw;

      if (rectangle.is_empty())
      {

         rectangle = client_rectangle();

      }

      client_to_host()(rectangle);

      bool bNeedsToDraw = false;

      if (pgraphics->m_rectangleaNeedRedraw.is_empty())
      {

         return true;

      }

      for (auto& r : pgraphics->m_rectangleaNeedRedraw)
      {

         if (r.intersects(rectangle))
         {

            bNeedsToDraw = true;

            break;

         }

      }

      if (!bNeedsToDraw)
      {

         //INFORMATION("Opting out from draw!! " << typeid(*this).name() << " " << m_atom.as_string());

      }

      return bNeedsToDraw;

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

      auto* pinteraction = get_host_window();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      auto edisplaySketch = pinteraction->layout().sketch().display();

      auto edisplayWindow = pinteraction->layout().window().display();

      auto psession = get_session();

      if (pinteraction->m_pprimitiveimpl.is_set() &&
         (layout().sketch().is_screen_visible()
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

         pinteraction->m_pprimitiveimpl->post_redraw();

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

   
   bool interaction::should_redraw_on_hover(::item* pitem)
   {

      if (!::is_item_set(pitem))
      {

         return false;

      }

      if (pitem->m_eelement == e_element_client)
      {

         bool bShouldRedrawOnMouseHover = should_redraw_on_mouse_hover();

         if (!bShouldRedrawOnMouseHover)
         {

            return false;

         }

      }

      if (pitem->m_rectangle.is_empty() && pitem->m_ppath.is_null())
      {

         return false;

      }

      return true;

   }


   ::user::form* interaction::get_form()
   {

      return m_pform;

   }


   ::user::form* interaction::get_parent_form()
   {

      auto pform = get_form();

      if (::is_null(pform))
      {

         return nullptr;

      }

      return pform;

   }


   ::user::element* interaction::get_form_user_element()
   {

      return get_form();

   }


   ::user::element* interaction::get_parent_form_user_element()
   {

      return get_parent_form();

   }


   ::particle* interaction::get_taskpool_container()
   {

      return parent_frame();

   }


   void interaction::set_place_child_title(const ::string& pszTitle)
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


   ::user::interaction* interaction::get_user_interaction()
   {

      return this;

   }


   ::user::primitive* interaction::get_bind_ui()
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


   interaction* interaction::get_parent_window()
   {

      return get_parent();

   }


   bool interaction::is_host_top_level()
   {

      return ::is_set(m_puserinteractionParent) && is_top_level();

   }


   //   bool interaction::is_host_window() const
   //   {
   //
   //      auto pprimitiveimpl = m_pprimitiveimpl;
   //
   //      if (!pprimitiveimpl)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      auto pinteractionimpl = pprimitiveimpl.cast<::user::interaction_impl>();
   //
   //      if (!pinteractionimpl)
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


   ::user::element* interaction::get_parent_primitive()
   {

      return get_parent();

   }


   interaction* interaction::get_parent()
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

      interaction* puserinteractionParent = get_parent();

      if (puserinteractionParent == nullptr)
      {

         return nullptr;

      }

      return puserinteractionParent->get_safe_oswindow();

   }


   bool interaction::on_before_set_parent(::user::primitive* puserinteractionParent)
   {

      return true;

   }


   ::user::primitive* interaction::set_parent(::user::primitive* puserinteractionParent)
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

      if (m_pthreadUserInteraction)
      {

         if (::is_set(m_pthreadUserInteraction->m_puserprimitiveaThread))
         {

            m_pthreadUserInteraction->m_puserprimitiveaThread->erase(this);

         }

         m_pthreadUserInteraction.release();

      }

      auto pprimitiveimplOld = m_pprimitiveimpl;

      ::pointer<interaction>pparentOld = get_parent();

      if (puserinteractionParent == nullptr)
      {

         auto pprimitiveimplNew = __create<::user::interaction_impl>();

         auto strName = get_window_text();

         const ::scoped_string& scopedstrClassName = nullptr;

         m_bEnableSaveWindowRect2 = true;

         on_set_parent(nullptr);

         if (m_ewindowflag & e_window_flag_load_window_rect_on_impl)
         {

            WindowDataLoadWindowRectangle();

         }

         auto rectangleRequest = this->screen_rect();

         //auto pusersystem = __new(::user::system);

         //pusersystem->add_visible(is_visible(layout().sketch().display()));

         if (pprimitiveimplOld.is_set())
         {

            pprimitiveimplOld->destroy_impl_only();

         }

         pprimitiveimplNew->create_host(this);

         on_after_set_parent();

      }
      else // puserinteractionParent != nullptr
      {

         on_set_parent(puserinteractionParent);

         auto pprimitiveimplNew = __create_new<::user::interaction_child>();

         pprimitiveimplNew->m_puserinteraction = this;

         ::pointer<::aura::application>papp = get_app();

         //psession->erase_frame(this); // no more a top level frame if it were one
         papp->erase_user_interaction(this); // no more a top level frame if it were one

         m_pprimitiveimpl = pprimitiveimplNew;

         string strName;

         //i32 iStyle = get_window_long(GWL_STYLE);

         //iStyle |= WS_CHILD;

         //if (is_visible(layout().sketch().display()))
         //{

         //   iStyle |= WS_VISIBLE;

         //}

         ::rectangle_i32 rectangleWindow;

         ::pointer < ::user::interaction > pparent = puserinteractionParent;

         if (pparent)
         {

            pparent->get_child_rect(rectangleWindow);

         }

         if (pprimitiveimplOld.is_set())
         {

            pprimitiveimplOld->destroy_impl_only();

         }

         pprimitiveimplNew->create_child(this, pparent);

         //if (!pprimitiveimplNew->create_child(this, pparent))
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


   bool interaction::pre_message_handler(::message::key*& pkey, bool& bKeyMessage, ::message::message* pmessage)
   {

      auto emessage = pmessage->m_atom.as_emessage();

      if (emessage == e_message_left_button_down)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_left_button, true);

         }
         catch (...)
         {

         }

      }
      else if (emessage == e_message_left_button_up)
      {

         auto psession = get_session();

         try
         {

            psession->set_key_pressed(::user::e_key_left_button, false);

         }
         catch (...)
         {

         }

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

            ::output_debug_string("e_message_key_down");

         }

         pkey = dynamic_cast <::message::key*> (pmessage);

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

      if (::is_set(m_puserinteraction))
      {

         m_puserinteraction->pre_translate_message(pmessage);

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
   //         auto pinteractionHost = get_host_window();
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


   ::user::element* interaction::get_keyboard_focus()
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

      auto puserinteractionKeyboardFocus = puser->get_keyboard_focus(m_pthreadUserInteraction);

      if (::is_null(puserinteractionKeyboardFocus))
      {

         return nullptr;

      }

      return puserinteractionKeyboardFocus;

   }


   void interaction::install_message_routing(::channel* pchannel)
   {

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &interaction::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &interaction::on_message_destroy);
      MESSAGE_LINK(e_message_text_composition, pchannel, this, &interaction::_001OnTextComposition);

      primitive::install_message_routing(pchannel);

      if (m_bMessageWindow)
      {

         //MESSAGE_LINK(MESSAGE_DESTROY              , pchannel, this, &interaction::_001OnDestroyMessageWindow);

      }
      else
      {

         if (m_bEditDefaultHandling)
         {

            add_command_handler("edit_delete", { this,  &interaction::_001OnEditDelete });

         }

         MESSAGE_LINK(MESSAGE_CLOSE, pchannel, this, &interaction::on_message_close);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction::on_message_size);
         MESSAGE_LINK(e_message_reposition, pchannel, this, &interaction::on_message_move);
         MESSAGE_LINK(e_message_non_client_calc_size, pchannel, this,
            &interaction::on_message_non_client_calculate_size);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction::on_message_show_window);
         MESSAGE_LINK(e_message_display_change, pchannel, this, &interaction::on_message_display_change);
         MESSAGE_LINK(e_message_subject, pchannel, this, &interaction::on_message_subject);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
         MESSAGE_LINK(e_message_left_button_double_click, pchannel, this, &::user::interaction::on_message_left_button_double_click);
         //MESSAGE_LINK(e_message_set_focus, pchannel, this, &::user::interaction::on_message_set_focus);

         if (m_bDataUpdateDefaultHandling)
         {

            MESSAGE_LINK(e_message_need_load_form_data, pchannel, this, &interaction::on_message_need_load_form_data);
            MESSAGE_LINK(e_message_need_save_form_data, pchannel, this, &interaction::on_message_need_save_form_data);

         }

         //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

         //MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

         if (m_bClickDefaultMouseHandling)
         {

            MESSAGE_LINK(e_message_left_button_up, pchannel, this, &interaction::on_message_left_button_up);

            m_bHoverDefaultMouseHandling = true;

#if MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG

            MESSAGE_LINK(e_message_middle_button_down, pchannel, this, &interaction::on_message_middle_button_down);
            MESSAGE_LINK(e_message_middle_button_up, pchannel, this, &interaction::on_message_middle_button_up);

#endif

         }

         MESSAGE_LINK(e_message_mouse_wheel, pchannel, this, &interaction::on_message_mouse_wheel);

         if (m_bHoverDefaultMouseHandling)
         {

            MESSAGE_LINK(e_message_mouse_move, pchannel, this, &interaction::on_message_mouse_move);
            MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &interaction::on_message_mouse_leave);

         }

         //MESSAGE_LINK(e_message_set_cursor, pchannel, this, &::user::interaction::on_message_set_cursor);

         if (m_bEditDefaultHandling || m_bKeyboardMultipleSelectionDefaultHandling)
         {

            MESSAGE_LINK(e_message_key_down, pchannel, this, &::user::interaction::on_message_key_down);
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


      //if (m_bClickDefaultMouseHandling)
      //{

      //   install_click_default_mouse_handling(pchannel);
      //   
      //}

      //if (m_bHoverDefaultMouseHandling)
      //{

      //   install_hover_default_mouse_handling(pchannel);

      //}

   }


   void interaction::prio_install_message_routing(::channel* pchannel)
   {

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &interaction::on_message_left_button_down);

   }


   void interaction::on_message_non_client_calculate_size(::message::message* pmessage)
   {

      pmessage->m_bRet = true; // avoid any Microsoft-Window-concept-of-non-client-area

   }


   //bool interaction::is_sketch_to_design_locked() const
   //{

   //   if (m_bLockSketchToDesign)
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


   void interaction::clear_activation(enum_layout elayout)
   {

      m_layout.m_statea[elayout].clear_activation();

   }


   void interaction::set_display(::e_display edisplay, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_edisplay = edisplay;

   }


   void interaction::set_layout_state(const layout_state& state, enum_layout elayout)
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

      //INFORMATION("interaction_layout::display e_display_normal");

#endif

#if DEBUG_LEVEL > 0

      if (m_pdescriptor.is_set() && m_puserinteractionParent == nullptr)
      {

         INFORMATION("Parent is Null. Display Request -> normal");

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

      output_debug_string("\ne_display_zoomed\n");

#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_zoomed");

#endif

      layout().sketch().display() = e_display_zoomed;

      ::rectangle_i32 rectangleRequest = this->screen_rect();

      best_workspace(nullptr, rectangleRequest, true, layout().sketch().activation(), layout().sketch().zorder());

   }


   void interaction::display_iconic()
   {

#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_iconic");

#endif

      layout().sketch().display() = e_display_iconic;

   }


   void interaction::display_full_screen(::index iMonitor, ::e_activation eactivation)
   {

      best_monitor(nullptr, nullptr, true, e_activation_default, e_zorder_top);

   }


   void interaction::display_previous()
   {

      auto edisplayPrevious = window_previous_display();

      if (!::is_screen_visible(edisplayPrevious))
      {

         edisplayPrevious = e_display_normal;

      }

      display(edisplayPrevious);

   }


   void interaction::display_normal(::e_display edisplay, ::e_activation eactivation)
   {

#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_restore");

#endif

      if (equivalence_sink(edisplay) == e_display_normal)
      {

         layout().sketch().display() = edisplay;

      }
      else
      {

         layout().sketch().display() = e_display_normal;

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

      output_debug_string("\ne_display_notify_icon\n");

#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_notify_icon");

#endif

      layout().sketch().display() = e_display_notify_icon;

   }


   void interaction::display(::e_display edisplay, ::e_activation eactivation)
   {

      bool bToggle = false;

      if (equivalence_sink(edisplay) == e_display_normal)
      {

         display_normal(edisplay, eactivation);

      }
      else if (edisplay == e_display_hide || edisplay == e_display_none)
      {

#ifdef INFO_LAYOUT_DISPLAY

         //INFORMATION("interaction_layout::display e_display_hide");

#endif

#if DEBUG_LEVEL > 0
         if (m_pdescriptor.is_set() && m_puserinteractionParent == nullptr)
         {

            INFORMATION("Parent is Null. Display Request -> hide");

         }

#endif

         layout().sketch().display() = e_display_hide;

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

         output_debug_string("e_display_full_screen");

#ifdef INFO_LAYOUT_DISPLAY

         INFORMATION("interaction_layout::display e_display_full_screen");

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

         //INFORMATION("interaction_layout::display e_display_default");

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

         layout().sketch().display() = edisplay;

      }
      else
      {

#ifdef INFO_LAYOUT_DISPLAY

         //INFORMATION("interaction_layout::display (unknown)");

#endif

      }

      layout().sketch() = eactivation;

      if (!sketch_on_display())
      {

         return;

      }

   }


   void interaction::on_set_finish()
   {

      if (!m_bUserInteractionSetFinish)
      {

         m_bUserInteractionSetFinish = true;

         start_destroying_window();

         return;

         //return error_pending;

      }

      //::user::primitive::on_set_finish();

   }


   void interaction::notify_on_destroy(::property_object* pparticle)
   {

      ::user::primitive::notify_on_destroy(pparticle);

   }


   void interaction::on_message_destroy(::message::message* pmessage)
   {

      m_ewindowflag += e_window_flag_destroying;

      try
      {

         if (m_pprimitiveimpl)
         {

            m_pprimitiveimpl->set_destroying_flag();

         }

      }
      catch (...)
      {

      }

      auto type = __object_type(*this);

      if (type.name_contains("main_frame"))
      {

         output_debug_string("main_frame on_message_destroy");

      }

      __UNREFERENCED_PARAMETER(pmessage);

      user_interaction_on_destroy();

      pmessage->previous();

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

      if (::is_null(m_pprimitiveimpl))
      {

         return;

      }

      m_pprimitiveimpl->user_interaction_on_hide();

      // Remark, Kill focus should have been called if this window
      // had focus and is being hidden. At kill focus, the host
      // window m_puserinteractionFocus member should haven cleared
      // in this case.
      //::user::interaction * pinteraction = get_wnd();

      //if(::is_set(pinteraction) && pinteraction != this && pinteraction->get_keyboard_focus()== this)
      //{

      //   if (pinteraction->get_wnd()->m_pinteractionimpl->m_puserinteractionFocus == this)
      //   {


      //   }

      //}

      //clear_prodevian();

      try
      {

         if (!m_pprimitiveimpl->has_destroying_flag())
         {

            //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

            auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

            if (puserinteractionpointeraChild)
            {

               for (index i = 0; i < puserinteractionpointeraChild->interaction_count(); i++)
               {

                  try
                  {

                     if (puserinteractionpointeraChild->interaction_at(i).is_set())
                     {

                        puserinteractionpointeraChild->interaction_at(i)->send_message(e_message_show_window, 0, 1);

                     }

                  }
                  catch (...)
                  {

                  }

               }

            }

         }

      }
      catch (...)
      {

      }

      if (m_puserinteractionpointeraOwned)
      {

         try
         {

            for (index i = 0; i < m_puserinteractionpointeraOwned->primitive_count(); i++)
            {

               try
               {

                  if (::is_set(m_puserinteractionpointeraOwned->primitive_at(i)))
                  {

                     m_puserinteractionpointeraOwned->primitive_at(i)->display(e_display_none);

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

            if (has_mouse_capture())
            {

               auto pwindowing = windowing();

               pwindowing->release_mouse_capture();

            }

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
            pmessage->m_pwindow = window();
            pmessage->m_oswindow = window()->oswindow();
            pmessage->m_wparam = 0;
            pmessage->m_lparam = 0;
            //          pmessage->m_time = pevent->time;

            post(pmessage);

         }

      }
      catch (...)
      {

      }

      try
      {

         auto pinteraction = get_wnd();

         if (::is_null(pinteraction)
            || ::is_null(get_wnd()->m_pprimitiveimpl)
            || get_wnd()->m_pprimitiveimpl->has_destroying_flag())
         {

            output_debug_string("destroying os window");

         }
         else
         {

            interaction_post([this]()
               {

                  if (get_app() != nullptr && get_app()->get_session() != nullptr &&
                     has_keyboard_focus())
                  {

                     if (get_parent() != nullptr && is_window_visible(e_layout_sketch))
                     {

                        keyboard_set_focus_next();

                     }

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

            pwindowing->clear_active_window(m_pthreadUserInteraction, window());

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

      ::user::interaction* puserinteractionParent = get_parent();

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

            synchronous_lock synchronouslock(psession->synchronization());

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


   void interaction::_001GetSel(strsize& iBeg, strsize& iEnd)
   {


   }


   bool interaction::set_sel_by_name(const ::string& strName)
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


   void interaction::set_sel_color(const ::color::hls& hls)
   {


   }


   ::color::hls interaction::get_sel_color()
   {

      return {};

   }


   void interaction::get_horizontal_scroll_info(scroll_info& info)
   {

      ::size_i32 sizeTotal = get_total_size();

      auto sizePage = get_page_size();

      auto pointOffset = get_context_offset();

      info.nMin = 0;
      info.nMax = (::i32)sizeTotal.cx;
      info.nPage = (::i32)sizePage.cx;
      info.nPos = pointOffset.x();
      info.nTrackPos = pointOffset.x();

   }


   void interaction::get_vertical_scroll_info(scroll_info& info)
   {

      auto sizeTotal = get_total_size();

      auto sizePage = get_page_size();

      auto pointOffset = get_context_offset();

      info.nMin = 0;
      info.nMax = (::i32)sizeTotal.cy;
      info.nPage = (::i32)sizePage.cy;
      info.nPos = pointOffset.y();
      info.nTrackPos = pointOffset.y();

   }


   void interaction::layout_scroll_bar(::draw2d::graphics_pointer& pgraphics)
   {

   }


   void interaction::on_erase_child(::user::interaction* pinteraction)
   {

   }


   void interaction::on_erase_place_holder_child(::user::interaction* pinteraction)
   {

   }


   void interaction::on_hide_child(::user::interaction* pinteraction)
   {

   }


   void interaction::on_hide_place_holder_child(::user::interaction* pinteraction)
   {

   }


   void interaction::user_interaction_on_destroy()
   {

      {

         single_lock slDraw(get_wnd() == nullptr || get_wnd()->m_pprimitiveimpl.is_null()
            || get_wnd()->m_pprimitiveimpl.cast<::user::interaction_impl>() == nullptr ? nullptr
            : get_wnd()->m_pprimitiveimpl.cast<::user::interaction_impl>()->draw_mutex(),
            true);


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

         auto pprimitiveimpl = m_pprimitiveimpl;

         if (pprimitiveimpl)
         {

            auto ptimerarray = pprimitiveimpl->m_ptimerarray;

            if (ptimerarray)
            {

               ptimerarray->delete_all_timers();

            }

         }

      }

      prodevian_stop();

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

            auto pprimitiveimpl = puserinteractionTopLevelHost->m_pinteractionimpl;

            if (pprimitiveimpl)
            {

               synchronous_lock synchronouslock(pprimitiveimpl->synchronization());

               pprimitiveimpl->m_userinteractionaMouseHover.erase(this);

            }

         }

      }

      {

         synchronous_lock synchronouslock(this->synchronization());

         auto pthread = get_thread();

         if (pthread != nullptr)
         {

            if (pthread->get_active_user_primitive() == this)
            {

               pthread->set_active_user_primitive(nullptr);

            }

         }

      }

      ::user::interaction* puserinteractionParent = m_puserinteractionParent;

      if (puserinteractionParent != nullptr)
      {

         try
         {

            //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

            auto puserinteractionpointeraChild = __new(
               ::user::interaction_array(*puserinteractionParent->m_puserinteractionpointeraChild));

            if (puserinteractionParent->m_bUserElementOk)
            {

               puserinteractionParent->on_erase_child(this);

               puserinteractionpointeraChild->erase_interaction(this);

               puserinteractionParent->m_puserinteractionpointeraChild = puserinteractionpointeraChild;

            }
            else
            {

               output_debug_string("Parent being destroyed");

            }

         }
         catch (...)
         {

         }

         //m_puserinteractionParent = nullptr;

      }

      if (!is_message_only_window())
      {

         if (get_app() != nullptr)
         {

            try
            {

               ::pointer<::aura::application>papp = get_app();

               papp->erase_user_interaction(
                  this); // guess this may be a frame, it doesn't hurt to erase if this is not there

            }
            catch (...)
            {

            }

            if (get_app()->get_session() != nullptr)
            {

               try
               {

                  ::pointer<::aura::application>papp = get_app();

                  papp->erase_user_interaction(
                     this); // guess this may be a frame, it doesn't hurt to erase if this is not there

               }
               catch (...)
               {

               }

            }

         }

      }

      m_bUserElementOk = false;

      m_ewindowflag -= e_window_flag_is_window;

      auto type = __object_type(*this);

      if (type.name_contains("simple_scroll_bar"))
      {

         output_debug_string("simple_scroll_bar::user_interaction_on_destroy");

      }


      //task_erase_all();


      //synchronous_lock synchronouslock(mutex_children());

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         for (i32 i = 0; i < puserinteractionpointeraChild->interaction_count(); i++)
         {

            auto pinteraction = puserinteractionpointeraChild->interaction_at(i);

            auto type = __object_type(*this);

            if (type.name_contains("auraclick::impact"))
            {

               output_debug_string("auraclick::impact");

            }

            try
            {

               pinteraction->destroy_window();

            }
            catch (...)
            {

            }

            //try
            //{

            //   pinteraction->destroy();

            //}
            //catch (...)
            //{

            //}

         }

      }

      //m_pdescriptor.release();

   }


   void interaction::on_message_size(::message::message* pmessage)
   {

      ::pointer<::message::size>psize(pmessage);

      pmessage->previous();

      if (psize->m_nType == ::user::e_size_minimized)
      {

         TRACE("::user::interaction::on_message_size SIZE_MINIMIZED - ignoring event");

      }
      else if (m_pprimitiveimpl->m_bIgnoreSizeEvent)
      {

         TRACE("::user::interaction::on_message_size instructed to m_bIgnoreSizeEvent");

      }

      auto psession = get_session();

      if (this == psession->get_user_interaction_host())
      {

         //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         if (puserinteractionpointeraChild)
         {

            for (auto& puserinteraction : puserinteractionpointeraChild->interactiona())
            {

               puserinteraction->post_message((enum_message)e_message_display_change);

            }

         }

      }

      if (is_root())
      {

         if (m_puserinteractionpointeraChild)
         {

            if (m_puserinteractionpointeraChild->has_interaction())
            {

               for (auto& puserinteraction :
                  m_puserinteractionpointeraChild->interactiona())
               {

                  puserinteraction->set_size(psize->m_size);

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


   void interaction::show_window()
   {

      window_show_change_visibility();

   }


   void interaction::on_message_move(::message::message* pmessage)
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

         if (acmeapplication()->m_bImaging)
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


   void interaction::set_windowing_icon(::windowing::icon* picon)
   {

      if (::is_null(m_pinteractionimpl))
      {

         return;

      }

      //auto estatus = 

      m_pinteractionimpl->set_icon(picon);

      //if(!estatus)
      //{

//   return estatus;

//}

//return estatus;

   }


   ::windowing::icon * interaction::get_windowing_icon()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return nullptr;

      }

      auto picon = pwindow->get_icon();

      if (::is_null(picon))
      {

         return nullptr;

      }

      return picon;

   }


   ::draw2d::icon * interaction::get_draw_icon()
   {

      throw ::interface_only();

      return nullptr;

   }


   void interaction::set_context_org(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->set_origin(pgraphics);

   }


   ::point_i32 interaction::get_parent_accumulated_scroll(enum_layout elayout)
   {

      ::point_i32 pointScroll;

      auto pChild = this;

      while (::is_set(pChild) && ::is_set(pChild->get_parent()))
      {

         if (pChild->m_bParentScrollX)
         {

            pointScroll.x() += pChild->get_parent()->m_pointScroll.x();
            //pointScroll.x() += pChild->get_parent()->m_pointDragScroll.x();

         }

         if (pChild->m_bParentScrollY)
         {

            pointScroll.y() += pChild->get_parent()->m_pointScroll.y();
            //pointScroll.y() += pChild->get_parent()->m_pointDragScroll.y();

         }

         pChild = pChild->get_parent();

      }

      return pointScroll;

   }


   void interaction::_001OnNcClip(::draw2d::graphics_pointer & pgraphics)
   {

      if (!get_host_window()->m_pinteractionimpl->m_pgraphics->is_single_buffer_mode())
      {

         return;

      }

      try
      {

         pgraphics->reset_clip();

         if(!get_host_window()->has_prodevian())
         {

            pgraphics->m_pointAddShapeTranslate = m_pointScroll;

            if (pgraphics->m_rectangleaNeedRedraw.has_element())
            {

               if (pgraphics->m_rectangleaNeedRedraw.size() == 1)
               {

                  auto rectangleNeedRedraw = pgraphics->m_rectangleaNeedRedraw.first();

                  auto hostToClient = host_to_client();

                  hostToClient(rectangleNeedRedraw);

                  pgraphics->intersect_clip(rectangleNeedRedraw);

                  INFORMATION("Single rectangle need redraw " << rectangleNeedRedraw);

               }
               else
               {

                  ::pointer<::draw2d::region> pregion;

                  bool bFirst = true;

                  //::rectangle_i32 rUnion;

                  for (auto rectangleHostNeedRedraw: pgraphics->m_rectangleaNeedRedraw)
                  {

                     auto rectangleNeedRedraw = rectangleHostNeedRedraw;

                     auto hostToClient = host_to_client();

                     hostToClient(rectangleNeedRedraw);

                     ::pointer<::draw2d::region> pregionItem = __create<::draw2d::region>();

                     pregionItem->create_rectangle(rectangleNeedRedraw);

                     INFORMATION("Multiple rectangle need redraw " << rectangleNeedRedraw);

                     if (bFirst)
                     {

                        pregion = pregionItem;

                        bFirst = false;

                        //rUnion = rectangleNeedRedraw;

                     }
                     else
                     {

                        ::pointer<::draw2d::region> pregionCombine = __create<::draw2d::region>();

                        pregionCombine->combine(pregion, pregionItem, ::draw2d::e_combine_add);

                        pregion = pregionCombine;

                        //rUnion.unite(rUnion, rectangleNeedRedraw);

                     }

                  }

                  pgraphics->set_clipping(pregion);

                  //pgraphics->intersect_clip(rUnion);

               }

            }

         }

      }
      catch (...)
      {

         throw ::exception(error_exception, "no more a window");

      }

   }


   void interaction::_001OnClip(::draw2d::graphics_pointer& pgraphics)
   {

      try
      {

         ::user::interaction* pinteraction = this;

         if (!m_bClipRectangle)
         {

            ::rectangle_i32 rectangleClient;

            ::index i = 0;

            while (pinteraction != nullptr)
            {

               pinteraction->client_rectangle(rectangleClient);

               pinteraction->client_to_host()(rectangleClient);

               host_to_client()(rectangleClient);

               if (i == 0)
               {

                  m_rectangleClip = rectangleClient;

               }
               else
               {

                  m_rectangleClip.intersect(m_rectangleClip, rectangleClient);

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


   void interaction::_001DrawThis(::draw2d::graphics_pointer& pgraphics)
   {

      ::draw2d::save_context savecontext(pgraphics);

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      if (pgraphics == nullptr)
      {

         throw ::exception(error_bad_argument);

      }

      try
      {

         pgraphics->m_dFontFactor = 1.0;

         {

            //synchronous_lock synchronouslock(this->synchronization());

            if(pgraphics->m_bDraw)
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

               _001OnNcClip(pgraphics);

               //auto pstyle = get_style(pgraphics);

               _001OnNcDraw(pgraphics);


#ifdef __DEBUG

               auto timeEnd = ::time::now();

               auto timeElapsed = timeEnd - timeStart;

               if (timeElapsed > 100_ms)
               {

                  output_debug_string("\ndrawing took " + ::as_string(timeElapsed.integral_millisecond()) + "!!");
                  output_debug_string("\ndrawing took more than 100ms to complete!!");
                  output_debug_string("\n");

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

            try
            {

               _001CallOnDraw(pgraphics);

            }
            catch (...)
            {

            }

#ifdef __DEBUG

            auto timeElapsed = timeStart.elapsed();

            if (timeElapsed > 50_ms)
            {

               auto type = __object_type(*this);

               if (type.name_contains("font_list"))
               {

                  output_debug_string(type + "\n");

               }

#ifdef VERBOSE_LOG               


               CATEGORY_INFORMATION(prodevian, type.m_strName << " drawing took more than 50ms to complete ("
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

         INFORMATION("Exception: interaction::_001DrawThis %s" << __object_type(*this).as_string());

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

               CATEGORY_INFORMATION(prodevian,
                  "\ndrawing took " + as_string(timeElapsed.integral_millisecond()) + "!!");
               CATEGORY_INFORMATION(prodevian, "\ndrawing took more than 100ms more than 50ms to complete!!");

               // let's trye to see what happened?
               //on_after_graphical_update();


            }

#endif

#endif //__DEBUG

         }

      }

   }


   void interaction::_001CallOnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      point_i32 pointScroll = m_pointScroll;

      if (!pointScroll.is_null())
      {

         pgraphics->offset_origin(-pointScroll.x(), -pointScroll.y());

      }

      //point_i32 pointDragScroll = m_pointDragScroll;

      //if (!pointDragScroll.is_null())
      //{

      //   pgraphics->offset_origin(-pointDragScroll.x(), -pointDragScroll.y());

      //}

      //on_context_offset(pgraphics);

#ifdef __DEBUG

      auto timeStartWithLock = ::time::now();

#endif

      //synchronous_lock synchronouslock(this->synchronization());

      {

         if(pgraphics->m_bDraw)
         {

#ifdef __DEBUG

            auto timeStart = ::time::now();

#endif //__DEBUG

            _001OnClip(pgraphics);

            ::rectangle_i32 rectangleDraw;

            client_rectangle(rectangleDraw);

            copy(pgraphics->m_rectangleDraw, rectangleDraw);

            _001OnDraw(pgraphics);

#ifdef __DEBUG

            if (m_pitemHover)
            {

               m_pitemHover->set_drawn();

            }

            if (m_pitemCurrent)
            {

               m_pitemCurrent->set_drawn();

            }

            auto timeEnd = ::time::now();

            auto timeElapsed = timeEnd - timeStart;

#ifdef VERBOSE_LOG               

            if (timeElapsed > 100_ms)
            {

               CATEGORY_INFORMATION(prodevian, "\ndrawing at " << __type_name(this) << "!!");
               CATEGORY_INFORMATION(prodevian, "\ndrawing took " << timeElapsed.integral_millisecond() << +"!!");
               CATEGORY_INFORMATION(prodevian, "\ndrawing took more more than 100ms more than 50ms to complete!!");
               CATEGORY_INFORMATION(prodevian, "\n");

               // let's trye to see what happened?
               //_001OnDraw(pgraphics);

            }

#endif

#endif //__DEBUG

         }

      }

#ifdef __DEBUG

      auto timeEndWithLock = ::time::now();

      auto tickElapsedWithLock = timeEndWithLock - timeStartWithLock;

      if (tickElapsedWithLock > 3_ms)
      {

         //string strType = __type_name(this);

         //         output_debug_string("\n" + strType + "drawing took " + as_string(tickElapsedWithLock.m_i) + "!!");
         //       output_debug_string("\ndrawing took more than 3ms to complete!!");
         //     output_debug_string("\n");

      }

#endif //__DEBUG

      pgraphics->offset_origin(pointScroll.x(), pointScroll.y());

   }


   void interaction::_008CallOnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      ::draw2d::save_context savecontext(pgraphics);

      try
      {

         set_context_org(pgraphics);

         synchronous_lock synchronouslock(this->synchronization());

         _008OnDraw(pgraphics);

      }
      catch (...)
      {

      }

   }


   void interaction::on_context_offset(::draw2d::graphics_pointer& pgraphics)
   {

      ::point_i32 pointOffset;

      if (m_puserinteractionParent != nullptr)
      {

         pointOffset = layout().sketch().origin();

      }

      auto pointContextOffset = get_context_offset();

      auto offset = pointOffset - pointContextOffset;

      pgraphics->offset_origin((::i32)offset.cx, (::i32)offset.cy);

   }


   ::particle* interaction::mutex_draw()
   {

      auto puserinteraction = get_wnd();

      if (::is_null(puserinteraction))
      {

         return nullptr;

      }

      auto pprimitiveimpl = puserinteraction->m_pprimitiveimpl;

      if (::is_null(pprimitiveimpl))
      {

         return nullptr;

      }

      auto pinteractionimpl = pprimitiveimpl->m_pinteractionimpl;

      if (::is_null(pinteractionimpl))
      {

         return nullptr;

      }

      auto pgraphics = pinteractionimpl->m_pgraphics;

      if (::is_null(pgraphics))
      {

         return nullptr;

      }

      return pgraphics->synchronization();

   }


   void interaction::_001DrawChildren(::draw2d::graphics_pointer& pgraphics)
   {

      point_i32 pointScroll = m_pointScroll;

      //point_i32 pointDragScroll = m_pointDragScroll;

      bool bParentScrollX = false;

      bool bParentScrollY = false;

      try
      {

         //::draw2d::save_context savecontext(pgraphics);

         //on_context_offset(pgraphics);
         //// while drawing layout can occur and machine z-order.
         //// keep this past z-order
         //interaction_pointer_array uia;

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (puserinteractionpointeraChild)
         {

            for (auto pinteraction : puserinteractionpointeraChild->interactiona())
            {


               try
               {

                  if (!pinteraction)
                  {

                     continue;

                  }

                  if (pinteraction->has_destroying_flag() || !pinteraction->is_window())
                  {

                     ::output_debug_string("trying to draw window being destroyed");

                     continue;

                  }

                  if (::is_set(pinteraction) && !pinteraction->is_custom_draw())
                  {

                     if (!pointScroll.is_null())
                     {

                        if (!bParentScrollX && pinteraction->m_bParentScrollX)
                        {

                           pgraphics->offset_origin(-pointScroll.x(), 0);
                           //pgraphics->offset_origin(-pointDragScroll.x(), 0);

                           bParentScrollX = true;

                        }
                        else if (bParentScrollX && !pinteraction->m_bParentScrollX)
                        {

                           pgraphics->offset_origin(pointScroll.x(), 0);
                           //pgraphics->offset_origin(pointDragScroll.x(), 0);


                           bParentScrollX = false;

                        }

                        if (!bParentScrollY && pinteraction->m_bParentScrollY)
                        {

                           pgraphics->offset_origin(0, -pointScroll.y());
                           //pgraphics->offset_origin(0, -pointDragScroll.y());

                           bParentScrollY = true;

                        }
                        else if (bParentScrollY && !pinteraction->m_bParentScrollY)
                        {

                           pgraphics->offset_origin(0, pointScroll.y());
                           //pgraphics->offset_origin(0, pointDragScroll.y());

                           bParentScrollY = false;

                        }

                     }

                     pinteraction->_000CallOnDraw(pgraphics);

                     //{

                     //   //::time t1 = ::time::now();

                     //   pinteraction->_000OnDraw(pgraphics);

                     //   ///::time d1 = t1.elapsed();

                     //   //if(d1.m_i > 50)
                     //   //{

                     //   //   string strType = __type_name(pinteraction);

                     //   //   if(strType.contains("hello_multiverse") && strType.contains("frame"))
                     //   //   {

                     //   //      output_debug_string(".");

                     //   //   }

                     //   //   CINFO(prodevian)("(more than 50ms)(D) "+strType+"::_000OnDraw took " + as_string(d1.m_i) + "::time.\n");

                     //   //   //pinteraction->_000OnDraw(pgraphics);

                     //   //}

                     //}


                  }

               }
               catch (...)
               {

                  TRACE("\n\nException thrown while drawing user::interaction\n\n");

               }

            }

         }

      }
      catch (...)
      {


      }

      //pgraphics->offset_origin(pointScroll.x(), pointScroll.y());

      if (bParentScrollX && pointScroll.x())
      {

         pgraphics->offset_origin(pointScroll.x(), 0);

      }

      if (bParentScrollY && pointScroll.y())
      {

         pgraphics->offset_origin(0, pointScroll.y());

      }

   }


   void interaction::do_graphics(::draw2d::graphics_pointer& pgraphics)
   {

      windowing_output_debug_string("\ndo_graphics : before graphics lock");

      windowing_output_debug_string("\ndo_graphics : after graphics lock");

      windowing_output_debug_string("\ndo_graphics : after check1");

      ::draw2d::save_context savecontext(pgraphics);

      windowing_output_debug_string("\ndo_graphics : after savedc");

      windowing_output_debug_string("\ndo_graphics : after check2");

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, e_layout_design);

      ::rectangle_i32 rectangle(rectangleWindow);

      rectangle.offset(-rectangle.top_left());

      //#ifdef UNIVERSAL_WINDOWS

      // pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //#else

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //#endif

      windowing_output_debug_string("\ndo_graphics : after set alphamode");

      //auto pstyle = get_style(pgraphics);

      //if (pgraphics->m_pimage->is_ok())
      //{

      //   pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //   if (m_pinteractionimpl->is_composite())
      //   {

      //      pgraphics->m_pimage->fill(0);

      //   }
      //   else
      //   {

      //      pgraphics->m_pimage->fill(255, 192, 192, 192);

      //   }

      //}
      //else
      //{

      //   if (m_pinteractionimpl->is_composite())
      //   {

      //      pgraphics->fill_rectangle(rectangle, argb(0, 0, 0, 0));

      //   }
      //   else
      //   {

      //      if (pstyle && pstyle->is_dark_mode())
      //      {

      //         pgraphics->fill_rectangle(rectangle, argb(255, 25, 25, 25));

      //      }
      //      else
      //      {

      //         pgraphics->fill_rectangle(rectangle, argb(255, 255, 255, 255));

      //      }

      //   }

      //}

      windowing_output_debug_string("\ndo_graphics : before Print");

      try
      {

         //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

         //if (0) // abcxxx
         {

            on_graphics(pgraphics);

         }

      }
      catch (...)
      {


      }

#ifdef REDRAW_HINTING

      {

         auto rectangleClient = m_puserinteraction->client_rectangle();

         ::rectangle_i32 rectangleHint(rectangleClient);

         pgraphics->SelectClipRgn(nullptr);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleHint, argb(128, random(128, 255), random(128, 255), random(128, 255)));

      }

#endif
      //      pgraphics->fill_solid_rect_dim(10, 50, 200, 200, argb(128, random(128, 255), random(128, 255), random(128, 255)));


      windowing_output_debug_string("\ndo_graphics : after Print");

#if HARD_DEBUG

      ::draw2d::graphics_pointer g(e_create);

      g->debug();

      m_size.cx = 0;

      m_size.cy = 0;

#endif

   }


   void interaction::on_graphics(::draw2d::graphics_pointer& pgraphics)
   {

      windowing_output_debug_string("\n_001Print A");

      {

         ::draw2d::save_context savecontext(pgraphics);

         try
         {

            _000CallOnDraw(pgraphics);

         }
         catch (...)
         {

         }

      }

      windowing_output_debug_string("\n_001Print B");

      auto pwindowing = windowing();

      if (::is_set(pwindowing) && pwindowing->m_bDrawCursor)
      {

         {

            ::draw2d::save_context savecontext(pgraphics);

            try
            {

               auto pwindowing = windowing();

               auto pwindow = window();

               auto pointCursor = pwindow->get_cursor_position();

               screen_to_client(e_layout_design)(pointCursor);

               auto* pcursor = pwindowing->get_cursor();

               if (pcursor != nullptr && pgraphics != nullptr)
               {

                  pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

                  //pgraphics->draw(pointCursor, pcursor);

               }

            }
            catch (...)
            {

            }

         }

      }

   }


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


   void interaction::_000CallOnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         set_need_redraw();

         post_redraw();

         return;

      }

      auto type = __object_type(*this);

      if (type.name_contains("app_veriwell_keyboard") && type.name_contains("main_frame"))
      {

         // output_debug_string("app_veriwell_keyboard::main_frame");

      }
      else if (type.name_contains("plain_edit"))
      {

         //output_debug_string("plain_edit");

      }
      //      else if (strType.case_insensitive_contains("font_list"))
      //      {
      //
      //         output_debug_string("font_list");
      //
      //      }
      else if (type.name_contains("combo_box"))
      {

         //output_debug_string("combo_box");

      }

      scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      auto phostwindow = this->get_host_window();

      if (phostwindow != this)
      {

         bool bUpdateBuffer = false;

         bool bUpdateWindow = false;

    
         //      else if (type.name_contains("list_box"))
         //      {
         //
         //         output_debug_string("list_box");
         //
         //      }

               //if (!is_sketch_to_design_locked())
               //{

         sketch_to_design(bUpdateBuffer, bUpdateWindow);

      }

      //}

      if (m_bSketchToDesignLayout)
      {

         m_bSketchToDesignLayout = false;

         design_layout(pgraphics);

      }

      bool bZorder = check_child_zorder();

      if (bZorder)
      {

         design_zorder();

      }

      process_graphics_call_queue(pgraphics);

      if (!is_this_visible(e_layout_design))
      {

         if (type.name_contains("experience"))
         {

            if (type.name_contains("button"))
            {

               string strTag = m_strInteractionTag;

               strTag = "";

               if (strTag == "button_close")
               {

                  output_debug_string("button_close not visible\n");

               }
               else if (strTag == "button_maximize")
               {

                  output_debug_string("button_maximize not visible\n");

               }
               else if (strTag == "button_minimize")
               {

                  output_debug_string("button_minimize not visible\n");

               }
               else if (strTag == "button_restore")
               {

                  output_debug_string("button_restore not visible\n");

               }
               else if (strTag == "button_dock")
               {

                  output_debug_string("button_dock not visible\n");

               }
               else if (strTag == "button_transparent_frame")
               {

                  output_debug_string("button_transparent_frame not visible\n");

               }

            }

         }

         return;

      }

      if (layout().is_iconic())
      {

         return;

      }

         //      if (type.name_contains("list_box"))
      //      {
      //
      //         output_debug_string("list_box");
      //
      //      }

            //      if(m_strInteractionTag.case_insensitive_begins("button_"))
            //      {
            //
            //         output_debug_string("drawing: " + m_strInteractionTag + "\n");
            //
            //      }
            //      else if(m_strInteractionTag.case_insensitive_begins("control_box"))
            //      {
            //
            //         output_debug_string("-------- drawing: " + m_strInteractionTag + "\n");
            //
            //      }

      ::point_i32 pointOffset;

      if (m_puserinteractionParent != nullptr)
      {

         pointOffset = layout().design().origin();

      }

      if (!pointOffset.is_null())
      {

         pgraphics->offset_origin(pointOffset.x(), pointOffset.y());

      }

      try
      {

         _000OnDraw(pgraphics);

      }
      catch (...)
      {

      }

      if (!pointOffset.is_null())
      {

         pgraphics->offset_origin(-pointOffset.x(), -pointOffset.y());

      }

   }


   void interaction::queue_graphics_call(const ::function<void(::draw2d::graphics_pointer&) >& function)
   {

      synchronous_lock synchronouslock(this->synchronization());

      __defer_construct_new(m_pgraphicscalla);

      m_pgraphicscalla->add(__new(::draw2d::graphics_call(function)));

   }


   void interaction::process_graphics_call_queue(::draw2d::graphics_pointer& pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_pgraphicscalla)
      {

         while (m_pgraphicscalla->has_element())
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

            synchronouslock.lock();

         }

      }

   }


   void interaction::_000OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      ::draw2d::save_context savecontext(pgraphics);

      if (pgraphics->m_bDraw && needs_to_draw(pgraphics))
      {

         try
         {

            auto type = __object_type(*this);

            //         if (type.name_contains("waven::impact"))
            //         {
            //
            //            output_debug_string("waven::impact");
            //         }
                     //         else if(strType.case_insensitive_contains("menu_list_impact"))
                     //         {
                     //
                     //            output_debug_string("menu_list_impact");
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

            try
            {

               _001DrawThis(pgraphics);

            }
            catch (...)
            {

               TRACE("Exception: interaction::_000OnDraw _001DrawThis %s" << __object_type(*this).as_string());

            }

         }
         catch (...)
         {

         }

      }

      try
      {

         if (m_puserinteractionpointeraChild && m_puserinteractionpointeraChild->has_interaction())
         {

            try
            {

               _001DrawChildren(pgraphics);

            }
            catch (...)
            {

               TRACE("Exception: interaction::_000OnDraw _001DrawChildren %s" << __object_type(*this).as_string());

            }

         }

      }
      catch (...)
      {

      }

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

                  auto type = __object_type(*this);

                  CATEGORY_INFORMATION(prodevian, "(more than 50ms)(E) " << type.m_strName << "::_008CallOnDraw took " <<
                     d1.integral_millisecond() << "::time.\n");

               }

#endif

            }

         }

      }
      catch (...)
      {

      }

   }


   void interaction::_008OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

   }


   void interaction::draw_control_background(::draw2d::graphics_pointer& pgraphics)
   {

      ::aura::draw_context* pdrawcontext = pgraphics->::aura::simple_chain<::aura::draw_context>::get_last();

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      auto pstyle = get_style(pgraphics);

      if (get_draw_flags(pstyle) & e_flag_background_bypass)
      {

      }
      else if (get_translucency(pstyle) >= e_translucency_total)
      {

      }
      else if (get_translucency(pstyle) >= e_translucency_present)
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto colorBackground = get_color(pstyle, e_element_background);

         //if (colorref_get_r_value(crBackground) != 255)
         //{

         //   output_debug_string("no full red");

         //}

         if (colorBackground.is_ok())
         {

            auto esmoothmode = pgraphics->get_smooth_mode();

            pgraphics->set_smooth_mode(::draw2d::e_smooth_mode_none);

            pgraphics->fill_rectangle(rectangleClient, colorBackground);

            pgraphics->set_smooth_mode(esmoothmode);

         }

      }
      else
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         auto colorBackground = get_color(pstyle, e_element_background);

         //if (colorref_get_r_value(crBackground) != 255)
         //{

         //   output_debug_string("no full red");

         //}

         pgraphics->fill_rectangle(rectangleClient, colorBackground);

      }

   }


   bool interaction::is_custom_draw()
   {

      return false;

   }


   void interaction::add_prodevian(::matter* pmatter)
   {

      auto phostwindow = get_host_window();

      if (phostwindow == nullptr)
      {

         throw ::exception(error_wrong_state);

      }

      auto pprimitiveimpl = phostwindow->m_pprimitiveimpl;

      return pprimitiveimpl->add_prodevian(pmatter);

   }


   void interaction::erase_prodevian(::matter* pmatter)
   {

      if (get_wnd() == nullptr || get_wnd()->m_pprimitiveimpl == nullptr)
      {

         return;

      }

      get_wnd()->m_pprimitiveimpl->erase_prodevian(pmatter);

   }


   bool interaction::is_prodevian(const ::matter* pmatter) const
   {

      auto pwnd = ((interaction*)this)->get_wnd();

      if (pwnd == nullptr || pwnd->m_pprimitiveimpl == nullptr)
      {

         return false;

      }

      return pwnd->m_pprimitiveimpl->is_prodevian(pmatter);

   }




   void interaction::default_message_handler(::message::message* pmessage)
   {

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->default_message_handler(pmessage);

   }


   void interaction::_001OnTextComposition(::message::message* pmessage)
   {

      ::pointer<::message::key>ptext = pmessage;

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


   element* interaction::keyboard_set_focus_next(bool bSkipChild, bool bSkipSiblings, bool bSkipParent)
   {

      element* pelement = keyboard_get_next_focusable(nullptr, bSkipChild, bSkipSiblings, bSkipParent);

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

      return puser->get_keyboard_focus(m_pthreadUserInteraction);

   }


   void interaction::on_message_display_change(::message::message* pmessage)
   {

      //_001FancyInitialFramePlacement();

   }


   void interaction::on_message_subject(::message::message* pmessage)
   {

      ::pointer<::topic>ptopic(pmessage->m_lparam);

      if (!ptopic)
      {

         return;

      }

      if (pmessage->m_wparam == 0)
      {

         route(ptopic);

      }

   }


   void interaction::on_create_user_interaction()
   {


   }


   bool interaction::is_branch_current() const
   {

      if (::is_null(m_pthreadUserInteraction))
      {

         return false;

      }

      auto itaskCurrent = get_current_itask();

      auto itaskUserInteraction = m_pthreadUserInteraction->m_itask;

      return itaskCurrent == itaskUserInteraction;


   }


   ::item_pointer interaction::get_user_item(const ::item& item)
   {

      for (auto& pitem : *m_pitema)
      {

         if (*pitem == (ITEM_BASE_ADDITIONS&)item)
         {

            return pitem;

         }

      }

      return nullptr;

   }


   void interaction::interaction_post(const ::procedure& procedure)
   {

      auto puserinteractionHost = get_host_window();

      if (!puserinteractionHost || puserinteractionHost == this)
      {

         return m_pprimitiveimpl->interaction_post(procedure);

      }

      return puserinteractionHost->interaction_post(procedure);

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


   bool interaction::is_user_thread()
   {

      auto pthreadCurrent = ::get_task();

      auto pthreadUser = m_pthreadUserInteraction;

      auto bUserThread = pthreadCurrent && pthreadCurrent == pthreadUser;

      return bUserThread;

   }


   void interaction::interaction_send(const ::procedure& procedure)
   {

      __matter_send_procedure(this, this, &interaction::interaction_post, procedure);

   }


   void interaction::on_message_create(::message::message* pmessage)
   {

      __defer_construct_new(m_pitema);

      if (pmessage->previous())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_bEnableDragClient)
      {

         enable_drag(e_element_client);

      }

      if (m_bEnableDragResize)
      {

         enable_drag(e_element_resize);

      }

      //if (m_bEnableHorizontalBarDragScroll)
      //{

      //   enable_drag(e_element_bar_drag_scroll_horizontal);

      //}


      //if (m_bEnableVerticalBarDragScroll)
      //{

      //   enable_drag(e_element_bar_drag_scroll_vertical);

      //}

      auto psystem = acmesystem()->m_paurasystem;

      auto psignal = psystem->get_signal(id_user_style_change);

      psignal->add_handler(this);

      on_create_user_interaction();

      auto pcursor = get_mouse_cursor();

      if (::is_null(pcursor))
      {

         pcursor = windowing()->get_cursor(::e_cursor_arrow);

         set_mouse_cursor(pcursor);

      }

      run_property(ID_CREATE);

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

         //synchronous_lock synchronouslock(this->synchronization());

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

            ::pointer<::aura::application>papp = get_app();

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

      send_message(e_message_change_experience);

   }


   void interaction::windowing_send(const ::procedure& procedure)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         throw ::exception(error_wrong_state);

      }

      pwindowing->windowing_send(procedure);

   }


   void interaction::windowing_post(const ::procedure& procedure)
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         throw ::exception(error_wrong_state);

      }

      pwindowing->windowing_post(procedure);

   }


   void interaction::_000OnDrag(::message::drag_and_drop* pdrag)
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
      //         if (m_pprimitiveimpl == nullptr)
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


   void interaction::_000OnMouseLeave(::message::message* pmessage)
   {

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->_000OnMouseLeave(pmessage);

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

   //      if (m_pprimitiveimpl == nullptr)
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


   void interaction::_000OnKey(::message::key* pkey)
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

      auto pwindow = window();

      auto pointCursor = pwindow->get_cursor_position();

      if (!pkey->m_bRet)
      {

         // these try catchs are needed for multi threading : multi threaded windows: the hell
         // Now I understand why Microsoft (TM) Windows (R) windows are single threaded.

         ::user::interaction* pinteraction = top_child();

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

         //   m_pprimitiveimpl->route_message(pkey);

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


   ::user::interaction* interaction::_001FromPoint(::point_i32 point, bool bTestedIfParentVisible)
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

      ::pointer<interaction>pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         ::pointer<interaction>puie = pinteraction->_001FromPoint(point, true);

         if (puie != nullptr)
         {

            return puie;

         }

         pinteraction = pinteraction->under_sibling();

      }

      return this;

   }


   bool interaction::_001IsPointInside(const ::point_i32& point)
   {

      if (m_pprimitiveimpl.is_null())
      {

         return false;

      }

      if (!is_window_screen_visible())
      {

         return false;

      }

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow, e_layout_sketch);

      return rectangleWindow.contains(point);

   }


   rectangle_i32 interaction::screen_rect()
   {

      ::rectangle_i32 rectangle;

      client_rectangle(rectangle);

      client_to_screen()(rectangle);

      return rectangle;

   }


   bool interaction::_001IsPointInsideInline(const ::point_i32& point)
   {

      return screen_rect().contains(point);

   }


   bool interaction::_001IsClientPointInsideInline(const ::point_i32& point)
   {

      return layout().sketch().client_rect().contains(point);


   }


   bool interaction::_001IsParentClientPointInsideInline(const ::point_i32& point)
   {

      return layout().sketch().parent_client_rectangle().contains(point);

   }


   void interaction::on_message_key_down(::message::message* pmessage)
   {

      if (get_parent() == nullptr)
      {

         if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_f4)
         {

            auto psession = m_puserinteraction->get_session();

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

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (m_pappearance->on_key_down(pmessage->m_union.m_pkey->m_ekey, pmessage->m_wparam, ekeyModifiers,
            pmessage->m_union.m_pkey->m_strText))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (m_bEditDefaultHandling || m_bKeyboardMultipleSelectionDefaultHandling)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey)
         {

            if (m_bEditDefaultHandling && pkey->m_ekey == ::user::e_key_delete)
            {

               auto pcommand = __new(::message::command("edit_delete"));

               pcommand->initialize(this);

               route_command(pcommand);

               pkey->m_bRet = pcommand->m_bRet;

            }
            else if (m_bKeyboardMultipleSelectionDefaultHandling &&
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


   void interaction::on_message_key_up(::message::message* pmessage)
   {

      if (m_pappearance)
      {

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (m_pappearance->on_key_up(pmessage->m_union.m_pkey->m_ekey, pmessage->m_wparam, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (m_bEditDefaultHandling || m_bKeyboardMultipleSelectionDefaultHandling)
      {

         auto pkey = pmessage->m_union.m_pkey;

         if (pkey)
         {

            if (m_bEditDefaultHandling && pkey->m_ekey == ::user::e_key_delete)
            {

               pkey->m_bRet = true;

            }
            else if (m_bKeyboardMultipleSelectionDefaultHandling &&
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


   ::point_i32 interaction::on_drag_start(::user::drag* pdrag)
   {

      get_wnd()->hide_software_keyboard(this);

      if (pdrag->m_eelement == e_element_client)
      {

         return layout().window().origin();

      }
      else if (pdrag->m_eelement == e_element_resize)
      {

         return layout().window().origin() + layout().window().size();

      }

      throw exception(::error_unexpected);

   }


   bool interaction::drag_shift(::user::drag* pdrag)
   {

      if (pdrag->m_eelement == e_element_client)
      {

         pdrag->m_ecursor = e_cursor_move;

         set_position(pdrag->point());

         set_reposition();

         //set_need_redraw();

         post_redraw();

         return true;

      }
      else if (pdrag->m_eelement == e_element_resize)
      {

         pdrag->m_ecursor = e_cursor_size_bottom_right;

         auto size = pdrag->point() - layout().sketch().m_point;

         auto sizeMinimum = get_window_minimum_size();

         size = size.maximum(sizeMinimum);

         auto rectanglePrevious = layout().window().client_rect();

         layout().sketch().m_size = size;

         auto rectangle = layout().sketch().client_rect();

         set_need_layout();

         if (rectangle.right > rectanglePrevious.right)
         {

            ::rectangle_i32 r;

            r.left = rectanglePrevious.right;
            r.right = rectangle.right;
            r.top = rectangle.top;
            r.bottom = rectangle.bottom;

            set_need_redraw(r);

         }

         if (rectangle.bottom > rectanglePrevious.bottom)
         {

            ::rectangle_i32 r;

            r.left = rectangle.left;
            r.right = rectangle.right;
            r.top = rectanglePrevious.bottom;
            r.bottom = rectangle.bottom;

            set_need_redraw(r);

         }

         post_redraw();

         return true;

      }

      return false;

   }


   bool interaction::drag_hover(::user::drag* pdrag)
   {

      if (pdrag->m_eelement == e_element_client)
      {

         pdrag->m_ecursor = e_cursor_hand;

      }
      else if (pdrag->m_eelement == e_element_resize)
      {

         pdrag->m_ecursor = e_cursor_size_bottom_right;

      }

      return false;

   }


   void interaction::drag_release_capture()
   {

      auto pwindowing = windowing();

      pwindowing->release_mouse_capture();

   }


   void interaction::drag_set_cursor(::user::drag* pdrag)
   {

      auto pwindowing = windowing();

      auto pcursor = pwindowing->get_cursor(pdrag->m_ecursor);

      pdrag->m_pmouse->m_pcursor = pcursor;

   }


   //void interaction::on_message_ime_char(::message::message * pmessage)
   //{

   //   

   //   //if (m_bEditDefaultHandling || m_bKeyboardMultipleSelectionDefaultHandling)
   //   //{

   //   //   auto pkey = pmessage->m_union.m_pkey;

   //   //   if (pkey)
   //   //   {

   //   //      if (m_bEditDefaultHandling && pkey->m_ekey == ::user::e_key_delete)
   //   //      {

   //   //         pkey->m_bRet = true;

   //   //      }
   //   //      else if (m_bKeyboardMultipleSelectionDefaultHandling &&
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


   void interaction::on_message_character(::message::message* pmessage)
   {

      if (m_pappearance)
      {

         if (pmessage->m_wparam.m_number != 0)
         {

            m_pappearance->on_character((int)pmessage->m_wparam.m_number);

         }

         for (auto psz = pmessage->m_union.m_pkey->m_strText.c_str(); psz < pmessage->m_union.m_pkey->m_strText.end(); psz = ::unicode_next(psz))
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


   void interaction::_001OnTimer(::timer* ptimer)
   {

   }


   void interaction::on_timer(::timer* ptimer)
   {

      _001OnTimer(ptimer);

      //return true;

   }


   ::user::interaction* interaction::get_child_by_name(const ::string& strName, ::index iItem, i32 iLevel)
   {

      ::pointer<interaction>pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         if (pinteraction->m_strName == strName)
         {

            if (iItem < 0 || iItem == pinteraction->m_iItem)
            {

               return pinteraction;

            }

         }

         pinteraction = pinteraction->under_sibling();

      }

      ::pointer<interaction>pchild;

      if (iLevel > 0 || iLevel == -1)
      {

         if (iLevel > 0)
         {

            iLevel--;

         }

         ::pointer<interaction>pinteraction = top_child();

         while (pinteraction != nullptr)
         {

            pchild = pinteraction->get_child_by_name(strName, iItem, iLevel);

            if (pchild != nullptr)
            {

               return pchild;

            }

            pinteraction = pinteraction->under_sibling();

         }

      }

      return nullptr;

   }


   ::user::interaction* interaction::get_child_by_id(const atom& atom, index iItem, i32 iLevel)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return nullptr;

      }

      for (index i = puserinteractionpointeraChild->interaction_last_index(); i >= 0; i--)
      {

         auto pinteraction = puserinteractionpointeraChild->get_interaction(i);

         if (pinteraction->GetDlgCtrlId() == atom)
         {

            if (iItem < 0 || iItem == pinteraction->m_iItem)
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

      for (index i = puserinteractionpointeraChild->interaction_last_index(); i >= 0; i--)
      {

         auto pinteraction = puserinteractionpointeraChild->get_interaction(i);

         ::user::interaction* puiChild = pinteraction->get_child_by_id(atom, -1, iLevel);

         if (::is_set(puiChild))
         {

            return puiChild;

         }

      }

      return nullptr;

   }


   ::user::element* interaction::get_primitive_by_id(const atom& atom, ::index iItem, i32 iLevel)
   {

      auto pchild = get_child_by_id(atom, iItem, iLevel);

      if (::is_null(pchild))
      {

         return nullptr;

      }

      return pchild;

   }


   ::user::interaction* interaction::child_from_point(const ::point_i32& point, ::i32 iLevel, const ::user::interaction_array* pinteractionaExclude)
   {

      auto pointClient = point;

      ::user::interaction* puserinteractionParent = nullptr;

      ::user::interaction* puserinteractionSearchChildren = this;

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

         auto puserinteractionpointeraChild = puserinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            break;

         }

         puserinteractionSearchChildren = nullptr;

         for (::index iChild = puserinteractionpointeraChild->interaction_last_index();
            iChild >= 0; iChild--)
         {

            auto& puserinteractionChild = puserinteractionpointeraChild->interaction_at(iChild);

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


   lresult interaction::send(::message::message* pmessage)
   {

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void interaction::post(::message::message* pmessage)
   {

      if (pmessage->m_atom == e_message_key_down)
      {

         output_debug_string("::user::interaction::post e_message_key_down");

      }

      ::pointer < ::user::message > pusermessage = pmessage;

      if (pusermessage)
      {

         pusermessage->m_pchannel = this;

      }

      m_pthreadUserInteraction->post(pmessage);

   }


   lresult interaction::send_message(const ::atom& atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->send_message(atom, wparam, lparam);

   }


   lresult interaction::message_call(const ::atom& atom, wparam wparam, lparam lparam, const ::point_i32& point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->message_call(atom, wparam, lparam);

   }


   lresult interaction::message_call(::message::message* pmessage)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->message_call(pmessage);

   }


#ifdef LINUX


   lresult interaction::send_x11_event(void* pevent)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return false;

      }
      else
      {

         return m_pprimitiveimpl->send_x11_event(pevent);

      }

   }


#endif


   void interaction::enable_window(bool bEnable)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->enable_window(bEnable);

   }


   // void interaction::SetWindowDisplayChanged()
   // {

   //    if (m_pprimitiveimpl.is_null())
   //    {

   //       return;

   //    }

   //    m_pprimitiveimpl->SetWindowDisplayChanged();

   // }


   //bool interaction::is_this_enabled() const
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->is_this_enabled();

   //}


   void interaction::send_message_to_descendants(const ::atom& atom, wparam wparam, lparam lparam, bool bDeep,
      bool bOnlyPerm)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      //synchronous_lock synchronouslock(::user::pointer < ::mutex >_children());

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         //synchronouslock.unlock();

         for (auto& puserinteraction : puserinteractionpointeraChild->interactiona())
         {

            try
            {

               puserinteraction->send_message(atom, wparam, lparam);

            }
            catch (...)
            {

            }

         }

         if (!bDeep)
         {

            return;

         }

         for (auto& puserinteraction : puserinteractionpointeraChild->interactiona())
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


   void interaction::route_message_to_descendants(::message::message* pmessage)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      {

         //synchronous_lock slChildren(::user::pointer < ::mutex >_children());



      }

      for (auto& puiChild : puserinteractionpointeraChild->interactiona())
      {

         try
         {

            puiChild->route_message_to_descendants(pmessage);

         }
         catch (...)
         {

         }

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
   //         if (!puserinteraction->m_pprimitiveimpl)
   //         {
   //
   //            return nullptr;
   //
   //         }
   //
   //         return oswindow_get(puserinteraction->m_pprimitiveimpl->m_pinteractionimpl);
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
   //      ::user::interaction_impl * puserinteraction;
   //
   //      try
   //      {
   //
   //         pinteraction = get_wnd();
   //
   //         if (pinteraction == nullptr)
   //            return nullptr;
   //
   //         if (pinteraction->m_pprimitiveimpl == nullptr)
   //            return nullptr;
   //
   //         puserinteraction = pinteraction->m_pprimitiveimpl->get_user_interaction_impl();
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
   //      synchronous_lock synchronouslock(this->synchronization());
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
   //      ::pointer<primitive_impl>pprimitiveimplOld = m_pprimitiveimpl;
   //
   //      auto pprimitiveimplNew = __create < interaction_impl >();
   //
   //      pprimitiveimplNew->m_puserinteraction = this;
   //
   //      if (!pprimitiveimplNew->subclass_window(posdata))
   //      {
   //
   //         pprimitiveimplNew.release();
   //
   //      }
   //
   //      if (pprimitiveimplNew != nullptr)
   //      {
   //
   //         if (pprimitiveimplOld != nullptr)
   //         {
   //
   //            pprimitiveimplOld->m_puserinteraction = nullptr;
   //
   //            pprimitiveimplOld->erase_all_routes();
   //
   //            auto pwindowOld = pprimitiveimplOld;
   //
   //            if (pwindowOld != nullptr)
   //            {
   //
   //               pwindowOld->install_message_routing(this);
   //
   //            }
   //
   //            pprimitiveimplOld.release();
   //
   //         }
   //
   //         m_pprimitiveimpl = pprimitiveimplNew;
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
   //      auto pwindow = m_pprimitiveimpl;
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

   //      TRACE("Failed to create control");

   //      return false;

   //   }

   //   return true;

   //}


   void interaction::create_host()
   {

      if (is_window())
      {

         start_destroying_window();

      }

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pwindowHost = pwindowing->get_application_host_window();

      m_ewindowflag += e_window_flag_top_level;

      if (::is_set(pwindowHost))
      {

         create_child(pwindowHost->m_puserinteractionimpl->m_puserinteraction);

         //         pwindowHost->m_puserinteractionimpl->m_puserinteraction->set_need_layout();
         //
         //         pwindowHost->m_puserinteractionimpl->m_puserinteraction->set_need_redraw();
         //
         //         pwindowHost->m_puserinteractionimpl->m_puserinteraction->post_redraw();

         return;

      }

      //__refer(m_pthreadUserInteraction, ::get_task() OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      //if (m_pthreadUserInteraction)
      //{

      //   m_pthreadUserInteraction->uiptra().add(this);

      //}

      //try
      //{

      m_bUserElementOk = true;

      ::pointer<interaction_impl>pprimitiveimplNew;

      auto rectangle(this->screen_rect());

      /* auto psession = get_session();

       if (puserinteractionParent == nullptr && psession->get_user_interaction_host().is_set() && psession->get_user_interaction_host() != this)
       {

          puserinteractionParent = __user_interaction(psession->get_user_interaction_host());

       }

       if (puserinteractionParent == nullptr || puserinteractionParent->get_safe_handle() == (oswindow)MESSAGE_WINDOW_PARENT)
       {*/

       //auto estatus =

      __construct(pprimitiveimplNew);

      /*        if (!estatus)
              {

                 return estatus;

              }*/

              //#ifdef WINDOWS_DESKTOP
              //
              //            wstring wstrClassName(pszClassName);
              //
              //            wstring wstrWindowName(pszWindowName);
              //
              //            ::user::system pusersystem(0, wstrClassName, wstrWindowName, uStyle, rectangle, pcreate);
              //
              //#else

              //auto pusersystem = __new(::user::system(uExStyle, uStyle, rectangle, pcreate));

              //#endif

              //pusersystem->m_createstruct.hwndParent = ::is_set(puserinteractionParent) ? puserinteractionParent->get_safe_handle() : nullptr;


      pprimitiveimplNew->create_host(this);
      //if (!pprimitiveimplNew->create_host(this))
      //{

      //   m_pprimitiveimpl.release();

      //   pprimitiveimplNew.release();

      //}

      //}
      //else
      //{

      //   pprimitiveimplNew = __create_new < ::user::interaction_child >();

      //   //m_pdescriptor.defer_create(this);

      //   if (!pprimitiveimplNew->create_interaction(this, uStyle, rectangle, puserinteractionParent, pcreate))
      //   {

      //      pprimitiveimplNew.release();

      //      m_bUserElementOk = false;

      //      if (m_pthreadUserInteraction)
      //      {

      //         if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
      //         {

      //            m_pthreadUserInteraction->m_puiptraThread->erase(this);

      //         }

      //         __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      //      }

      //      return false;

      //   }

      //        }

      //}
      //catch (...)
      //{

      //   m_bUserElementOk = false;

      //   if (m_pthreadUserInteraction)
      //   {

      //      if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
      //      {

      //         m_pthreadUserInteraction->m_puiptraThread->erase(this);

      //      }

      //      __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      //   }

      //   //return false;

      //}

      //return true;

   }


   void interaction::create_child(::user::interaction* puserinteractionParent)
   {

      if (is_window())
      {

         start_destroying_window();

      }

      if (::is_null(m_pcontext))
      {

         initialize(puserinteractionParent);

      }

      if (::is_null(acmesystem()))
      {

         initialize(puserinteractionParent);

      }

      ::e_status estatus = error_exception;

      //try
      //{

      m_bUserElementOk = true;

      //auto psession = get_session();

      //auto puserinteractionHost = psession->get_user_interaction_host();

      //if (puserinteractionParent == nullptr && this != puserinteractionHost && ::is_set(puserinteractionHost))
      //{

      //   puserinteractionParent = __user_interaction(psession->get_user_interaction_host());

      //}

      //if ((WS_CHILD & pusersystem->m_createstruct.style) == 0 && (!puserinteractionParent || puserinteractionParent != psession->get_user_interaction_host()))
      //{

      //   //if (psession->m_pprimitiveimplLastSeed || pusersystem->m_pprimitiveimpl)
      //   //{

      //   //   if (pusersystem->m_pprimitiveimpl)
      //   //   {

      //   //      m_pprimitiveimpl = pusersystem->m_pprimitiveimpl;

      //   //      pusersystem->m_pprimitiveimpl.release();

      //   //   }
      //   //   else
      //   //   {

      //   //      m_pprimitiveimpl = psession->m_pprimitiveimplLastSeed;

      //   //      psession->m_pprimitiveimplLastSeed.release();

      //   //   }

      //   //   if (!m_pprimitiveimpl)
      //   //   {

      //   //      auto estatus = m_pprimitiveimpl->initialize(this);

      //   //      if (!estatus)
      //   //      {

      //   //         return false;

      //   //      }

      //   //   }

      //   //   pusersystem->m_createstruct.x() = m_pprimitiveimpl->m_rectangle.left;
      //   //   pusersystem->m_createstruct.y() = m_pprimitiveimpl->m_rectangle.top;
      //   //   pusersystem->m_createstruct.cx = m_pprimitiveimpl->m_rectangle.width();
      //   //   pusersystem->m_createstruct.cy = m_pprimitiveimpl->m_rectangle.height();

      //   //}
      //   //else
      //   //{

      //   //   m_pprimitiveimpl = __create < interaction_impl >();

      //   //}

      //   //uStyle &= ~WS_CHILD;

      //   //m_pdescriptor.defer_create(this);

      //   if (!m_pprimitiveimpl->create_window_ex(this, pusersystem, puserinteractionParent, atom))
      //   {

      //      m_bUserElementOk = false;

      //      m_pprimitiveimpl.release();

      //      if (m_pthreadUserInteraction)
      //      {

      //         if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
      //         {

      //            m_pthreadUserInteraction->m_puiptraThread->erase(this);

      //         }

      //         __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

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

      //      puserinteractionParent->client_rectangle(rectangleFrame);

      //   }

      //}
      //else
      //{

      //   rectangleFrame = rectangle;

      //}

      //synchronous_lock synchronouslock(puserinteractionParent == nullptr ? nullptr : puserinteractionParent->synchronization());

      m_pprimitiveimpl = __create_new<::user::interaction_child>();

      //m_pprimitiveimpl->m_puserinteraction = this;

      //m_pdescriptor.defer_create(this);

      //estatus = 

      m_pprimitiveimpl->create_child(this, puserinteractionParent);

      //if (!estatus)
      //{

      //   m_bUserElementOk = false;

      //   m_pprimitiveimpl.release();

      //   if (m_pthreadUserInteraction)
      //   {

      //      if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
      //      {

      //         m_pthreadUserInteraction->m_puiptraThread->erase(this);

      //      }

      //      __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      //   }

      //   return estatus;

      //}

      //}

      //}
      //catch (...)
      //{

      //   m_bUserElementOk = false;

      //   if (m_pthreadUserInteraction)
      //   {

      //      if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
      //      {

      //         m_pthreadUserInteraction->m_puiptraThread->erase(this);

      //      }

      //      __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      //   }

      //}

      //return estatus;

   }


   bool interaction::_is_window() const
   {

      if (::is_null(this))
      {

         return false;

      }

      if (m_pprimitiveimpl.is_null())
      {

         return false;

      }

      if (((interaction*)this)->get_parent() != nullptr)
      {

         if (!((interaction*)this)->get_parent()->is_window())
         {

            return false;

         }

      }

      return is_window();

   }


   //::i32 interaction::get_window_long(i32 nIndex) const
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return 0;

   //   }

   //   return m_pprimitiveimpl->get_window_long(nIndex);

   //}


   //::i32 interaction::set_window_long(i32 nIndex, ::i32 lValue)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return 0;

   //   }

   //   return m_pprimitiveimpl->set_window_long(nIndex, lValue);

   //}


   ::property_object* interaction::parent_property_set_holder() const
   {

      ::user::element* pelement = ((interaction*)this)->get_parent();

      if (::is_set(pelement))
      {

         return pelement;

      }

      pelement = ((interaction*)this)->get_owner();

      if (::is_set(pelement))
      {

         return pelement;

      }

      return ::user::primitive::parent_property_set_holder();

   }


   //iptr interaction::get_window_long_ptr(i32 nIndex) const
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return 0;

   //   }

   //   return m_pprimitiveimpl->get_window_long_ptr(nIndex);

   //}


   //void interaction::set_window_long_ptr(i32 nIndex, iptr lValue)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return 0;

   //   }

   //   return m_pprimitiveimpl->set_window_long_ptr(nIndex, lValue);

   //}


   void interaction::RedrawWindow(const ::rectangle_i32& rectangleUpdate, ::draw2d::region* prgnUpdate, ::u32 flags)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   ::user::interaction* interaction::ChildWindowFromPoint(const ::point_i32& point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->ChildWindowFromPoint(point);

   }


   ::user::interaction* interaction::ChildWindowFromPoint(const ::point_i32& point, ::u32 nFlags)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->ChildWindowFromPoint(point, nFlags);

   }


   ::user::interaction* interaction::get_first_child_window()
   {

      auto pchildren = m_puserinteractionpointeraChild;

      if (::is_null(pchildren) || pchildren->has_no_interaction())
      {

         return nullptr;

      }

      return pchildren->get_first_interaction();

   }


   ::user::interaction* interaction::get_next_sibling_window()
   {

      auto pparent = get_parent_window();

      if (pparent == nullptr)
      {

         return nullptr;

      }

      auto puserinteractionpointeraChild = pparent->m_puserinteractionpointeraChild;

      auto iFind = puserinteractionpointeraChild->find_first_interaction(this);

      if (iFind + 1 >= puserinteractionpointeraChild->interaction_count())
      {

         return nullptr;

      }

      return puserinteractionpointeraChild->interaction_at(iFind + 1);

   }


   ::user::interaction* interaction::get_next_window(bool bIgnoreChildren, ::user::interaction* puserinteractionStop)
   {

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

      auto puserinteractionParent = get_parent();

      if (!puserinteractionParent)
      {

         return nullptr;

      }

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


   ::user::interaction* interaction::get_window(enum_next enext)
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


   ::user::interaction* interaction::get_wnd(::u32 nCmd)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->get_wnd(nCmd);

   }


   //::user::interaction * interaction::GetActiveWindow()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->GetActiveWindow();

   //}


   //bool interaction::set_keyboard_focus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->set_keyboard_focus();

   //}


   //::user::primitive * interaction::get_keyboard_focus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->get_keyboard_focus();

   //}


   //::user::interaction * interaction::set_active_window()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->set_active_window();

   //}


   //bool interaction::set_foreground_window()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->set_foreground_window();

   //}


   ::user::interaction* interaction::GetLastActivePopup()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->GetLastActivePopup();

   }


   /*bool interaction::is_text_composition_active()
   {

      auto pprimitiveimpl = m_pprimitiveimpl;

      if (::is_null(pprimitiveimpl))
      {

         return false;

      }

      return pprimitiveimpl->is_text_composition_active();

   }*/


   //::form_property_set * interaction::get_form_property_set()
   //{

   //   if (m_pformpropertyset)
   //   {

   //      return m_pformpropertyset;

   //   }

   //   return ::user::primitive::get_form_property_set();

   //}


   int interaction::on_text_composition_message(int iMessage)
   {

      return -1;

   }


   void interaction::insert_text(string str, bool bForceNewStep, const ::action_context& context)
   {

      auto strText = get_window_text();

      strsize iBeg = strText.length();

      strsize iEnd = strText.length();

      _001GetSel(iBeg, iEnd);

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


   void interaction::set_window_text(const ::string& pszString)
   {

      m_strWindowText2 = pszString;

      on_set_window_text();

   }


   void interaction::set_window_text_source(const ::a_string_function& astringfunction)
   {

      m_astringfunctionWindowText = astringfunction;

   }


   void interaction::clear_window_text_source()
   {

      m_astringfunctionWindowText = nullptr;

   }


   void interaction::on_set_window_text()
   {

      if (m_pprimitiveimpl != nullptr)
      {

         m_pprimitiveimpl->on_set_window_text();

      }

   }


   ::string interaction::get_window_text()
   {

      if (m_astringfunctionWindowText)
      {

         return m_astringfunctionWindowText();

      }
      else
      {

         synchronous_lock synchronouslock(this->synchronization());

         return m_strWindowText2;

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
//      synchronous_lock synchronouslock(this->synchronization());
//
//      if (m_pprimitiveimpl == nullptr)
//      {
//
//         return 0;
//
//      }
//
//      return m_pprimitiveimpl->get_window_text_length();
//
//   }


   //::user::interaction * interaction::EnsureTopLevel()
   //{

   //   ::pointer<interaction>pwindow = get_top_level();

   //   ENSURE_VALID(pwindow);

   //   return pwindow;

   //}


   ::user::frame* interaction::frame()
   {

      ::user::interaction* pinteraction = (::user::interaction*)this;

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      do
      {

         if (pinteraction->is_frame_window())
         {

            return dynamic_cast <::user::frame*>(pinteraction);

         }

         pinteraction = pinteraction->get_parent_window();

      } while (pinteraction != nullptr);

      return nullptr;

   }


   ::user::frame* interaction::_parent_frame()
   {

      ::user::interaction* pinteraction = get_parent_window();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      return pinteraction->frame();

   }


   ::user::interaction* interaction::_top_level()
   {

      ::user::interaction* puserinteractionParent = (::user::interaction*)this;

      ::user::interaction* puiTopLevelParent;

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


   ::user::frame* interaction::_top_level_frame()
   {

      auto pframe = frame();

      if (!pframe)
      {

         return nullptr;

      }

      ::user::frame* pframeTopLevel;

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


   void interaction::start_destroying_window()
   {

      auto type = __object_type(*this);

      if (type.name_contains("main_frame"))
      {

         output_debug_string("main_frame start_destroying_window\n");

      }

      if (has_destroying_flag())
      {

         return;

      }

      set_destroying_flag();

      // set_destroying() m_bUserElementOk = false;

      // set_destroying() m_ewindowflag -= e_window_flag_is_window;

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      //::user::primitive::on_finish();

      m_pprimitiveimpl->start_destroying_window();

   }


   void interaction::destroy_window()
   {

      //   m_bUserElementOk = false;
      //
      //   m_ewindowflag -= e_window_flag_is_window;
      //
      //   if (!m_pprimitiveimpl)
      //   {
      //
      //      throw ::exception(error_wrong_state);
      //
      //   }

      m_pprimitiveimpl->destroy_window();
      //
      //   }

   }


   void interaction::destroy()
   {

      ::user::primitive::destroy();

      ::user::drag_client::destroy();

      if (m_pprimitiveimpl.is_set())
      {

         m_pprimitiveimpl->destroy();

      }

      // ownership

      //if(m_pinteractiondraw2d)
      //{
      //if (m_pshapeaClip) m_pshapeaClip->destroy();
      if (m_pdrawcontext) m_pdrawcontext->destroy();

      //}
      if (m_pusersystem) m_pusersystem->destroy();
      //      if (m_playout) m_playout->destroy();
      if (m_pgraphicscalla) m_pgraphicscalla->destroy();
      if (m_puserinteractionCustomWindowProc) m_puserinteractionCustomWindowProc->destroy();
      if (m_puiLabel) m_puiLabel->destroy();
      if (m_pitema) m_pitema->destroy_all();
      // tasks should not be destroyed in destroy
      //m_pform && m_pform != this && m_pform->destroy();
      if (m_palphasource) m_palphasource->destroy();
      //if (m_pdrawableBackground) m_pdrawableBackground->destroy();
      if (m_pprimitiveimpl) m_pprimitiveimpl->destroy();
      if (m_pinteractionimpl) m_pinteractionimpl->destroy();
      if (m_puserinteractionpointeraOwned) m_puserinteractionpointeraOwned->destroy();
      if (m_puserinteractionpointeraChild) m_puserinteractionpointeraChild->destroy();
      //m_pthreadUserInteraction && m_pthreadUserInteraction->destroy();
      // tasks should not be destroyed in destroy
      //m_pthreadUserInteraction && m_pthreadUserInteraction->destroy();
      if (m_ptooltip) m_ptooltip->destroy();
      if (m_pmenuitem) m_pmenuitem->destroy();
      m_menua.destroy_all();

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
      if (m_pitema) m_pitema->erase_all();
      m_pform.release();
      m_palphasource.release();
      //m_pdrawableBackground.release();
      m_pprimitiveimpl.release();
      m_pinteractionimpl.release();
      m_puserinteractionpointeraOwned.release();
      m_puserinteractionpointeraChild.release();
      m_ptooltip.release();
      m_pmenuitem.release();
      m_menua.erase_all();


      // references
      m_pitemComposing.release();
      m_pthreadUserInteraction.release();
      m_puserinteractionParent.release();
      m_pupdowntarget.release();
      m_ptaskModal.release();
      m_puserinteractionOwner.release();

      //return ::success;

   }


   void interaction::post_non_client_destroy()
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

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

      if (::is_set(m_pobjectParentTask))
      {

         m_pobjectParentTask->erase_task_and_set_task_new_parent(this, nullptr);

      }

      if (::is_set(m_pthreadUserInteraction))
      {

         auto pthread = m_pthreadUserInteraction.cast<thread>();

         if (pthread->m_pimpl == m_pinteractionimpl)
         {

            pthread->set_finish();

         }

         if (::is_set(m_pthreadUserInteraction->m_puserprimitiveaThread))
         {

            m_pthreadUserInteraction->m_puserprimitiveaThread->erase(this);

         }

         m_pthreadUserInteraction.release();

      }

      auto type = __object_type(*this);

      if (type.name_contains("main_frame"))
      {

         output_debug_string("main_frame post_non_client_destroy");

      }

      ::user::primitive::post_non_client_destroy();

      m_pprimitiveimpl.release();

      m_pinteractionimpl.release();

   }


   bool interaction::is_ready_to_quit() const
   {

      bool bShouldContinue = task_get_run();

      return !bShouldContinue && has_flag(e_flag_task_ready);

   }


   void interaction::set_appearance(::appearance::appearance* pappearance)
   {

      m_pappearance = pappearance;

      pappearance->set_user_interaction(this);

   }


   ::appearance::appearance* interaction::get_appearance()
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


   //void interaction::CalcWindowRect(::rectangle_i32 * prectangle, ::u32 nAdjustType)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return;

   //   }

   //   return m_pprimitiveimpl->CalcWindowRect(prectangle, nAdjustType);

   //}


   void interaction::show_control_bar(::user::control_bar* pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void interaction::hide_control_bar(::user::control_bar* pcontrolbar)
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   void interaction::RepositionBars(::u32 nIDFirst, ::u32 nIDLast, ::atom idLeft, ::u32 nFlags,
      ::rectangle_i32* prectParam, const ::rectangle_i32& rectangleClient, bool bStretch)
   {

      //if (m_pprimitiveimpl == nullptr)
      //{

      //   return;

      //}

      //return m_pprimitiveimpl->RepositionBars(nIDFirst, nIDLast, idLeftOver, nFlag, prectParam, rectangleClient,
//                                              bStretch);


      if (!_is_window())
      {

         return;

      }

      __UNREFERENCED_PARAMETER(nIDFirst);

      __UNREFERENCED_PARAMETER(nIDLast);

      ASSERT(nFlags == 0 || (nFlags & ~reposNoPosLeftOver) == reposQuery || (nFlags & ~reposNoPosLeftOver) == reposExtra);

      size_parent_layout sizeparentlayout;

      ::pointer<::user::interaction>puiLeft;

      sizeparentlayout.m_bStretch = bStretch;

      sizeparentlayout.m_sizeTotal.cx = sizeparentlayout.m_sizeTotal.cy = 0;

      if (rectangleClient.is_set())
      {

         sizeparentlayout.m_rectangle = rectangleClient;

      }
      else
      {

         input_client_rectangle(sizeparentlayout.m_rectangle);

      }

      if (::is_empty(sizeparentlayout.m_rectangle))
      {

         return;

      }

      ::pointer<::user::interaction>pinteraction;

      while (m_puserinteraction->get_child(pinteraction))
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

            ::copy(*prectParam, sizeparentlayout.m_rectangle);

         }
         else
         {

            prectParam->left = prectParam->top = 0;

            prectParam->right = sizeparentlayout.m_sizeTotal.cx;

            prectParam->bottom = sizeparentlayout.m_sizeTotal.cy;

         }

         return;

      }

      if (!idLeft.is_empty() && puiLeft != nullptr)
      {

         if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {

            ASSERT(prectParam != nullptr);


            sizeparentlayout.m_rectangle.left += prectParam->left;

            sizeparentlayout.m_rectangle.top += prectParam->top;

            sizeparentlayout.m_rectangle.right -= prectParam->right;

            sizeparentlayout.m_rectangle.bottom -= prectParam->bottom;

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


   ::user::primitive* interaction::set_owner(::user::primitive* pprimitive)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      auto puserinteractionOwner = m_puserinteractionOwner;

      if (::is_set(puserinteractionOwner))
      {

         auto puserinteractionpointeraOwned = puserinteractionOwner->m_puserinteractionpointeraOwned;

         if (::is_set(puserinteractionpointeraOwned))
         {

            try
            {

               puserinteractionpointeraOwned->erase_primitive(this);

            }
            catch (...)
            {

            }

         }

      }

      m_puserinteractionOwner = pprimitive;

      m_puserinteractionOwner->on_add_owned(this);

      ::user::primitive* puiRet = m_pprimitiveimpl->set_owner(pprimitive);

      if (m_ewindowflag & e_window_flag_satellite_window)
      {

         m_pthreadUserInteraction = m_puserinteractionOwner->m_pthreadUserInteraction;

      }

      on_set_owner(m_puserinteractionOwner);

      return puiRet;

   }


   void interaction::on_add_owned(::user::primitive* pprimitive)
   {

      __defer_construct_new(m_puserinteractionpointeraOwned);

      m_puserinteractionpointeraOwned->add_primitive(pprimitive);

   }


   ::user::interaction* interaction::get_owner()
   {

      if (m_puserinteractionOwner != nullptr)
      {

         return m_puserinteractionOwner;

      }

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->get_owner();

   }


   ::user::frame* interaction::get_owner_frame()
   {

      ::user::interaction* pinteraction = get_owner();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      ::user::frame* pframe = dynamic_cast <::user::frame*> (pinteraction);

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

         pframe = dynamic_cast <::user::frame*> (pinteraction);

      }

      return nullptr;

   }


   ::user::interaction* interaction::get_parent_owner()
   {

      ::pointer<::user::interaction>puserinteractionParent = get_parent();

      if (puserinteractionParent.is_null())
      {

         return nullptr;

      }

      return puserinteractionParent->get_owner();

   }


   ::user::interaction* interaction::get_parent_or_owner()
   {

      ::pointer<::user::interaction>puserinteractionParent = get_parent();

      if (puserinteractionParent.is_set())
      {

         return puserinteractionParent;

      }

      return get_owner();

   }


   ::user::interaction* interaction::get_top_level_owner()
   {

      ::pointer<::user::interaction>puiOwner = get_owner();

      ::pointer<::user::interaction>puiTopLevelOwner;

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


   void interaction::viewport_client_to_screen(::point_i32& point)
   {

      m_pprimitiveimpl->viewport_client_to_screen(point);

   }


   bool interaction::window_is_notify_icon_enabled()
   {

      return false;

   }


   void interaction::viewport_screen_to_client(::point_i32& point)
   {

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->viewport_screen_to_client(point);

   }


   void interaction::viewport_client_to_screen(::rectangle_i32& rectangle)
   {

      viewport_client_to_screen((::point_i32&)rectangle.left);

      viewport_client_to_screen((::point_i32&)rectangle.right);

   }


   void interaction::viewport_screen_to_client(::rectangle_i32& rectangle)
   {

      viewport_screen_to_client((::point_i32&)rectangle.left);

      viewport_screen_to_client((::point_i32&)rectangle.right);

   }


   //bool interaction::layout().is_zoomed()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->layout().is_zoomed();

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

      auto pwindow = window();

      if (!pwindow->is_full_screen())
      {

         return false;

      }

      bool bDisplayIsFullScreen = top_level_frame()->layout().is_full_screen();

      return bDisplayIsFullScreen;

   }


   float interaction::preferred_dpi_x()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return ::user::primitive::preferred_dpi_x();

      }

      return pwindow->get_dpi_for_window();

   }


   float interaction::preferred_dpi_y()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return ::user::primitive::preferred_dpi_y();

      }

      return pwindow->get_dpi_for_window();

   }


   float interaction::preferred_density()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return ::user::primitive::preferred_density();

      }

      return pwindow->get_density_for_window();

   }

   //void interaction::set_need_redraw()
   //{

   //   set_need_redraw();

   //}


   bool interaction::check_child_zorder()
   {

      if (m_bPendingZorder)
      {

         return true;

      }

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         for (auto& pchild : puserinteractionpointeraChild->interactiona())
         {

            if (pchild->layout().sketch().zorder().is_change_request())
            {

               m_bPendingZorder = true;

            }

         }

      }

      return m_bPendingZorder;

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


   bool interaction::display_sketch_to_design()
   {

      auto type = __object_type(*this);

      auto edisplayDesign = layout().design().display();

      auto edisplaySketch = layout().sketch().display();

      auto eactivationSketch = layout().sketch().activation();

      bool bDisplay =
         edisplaySketch != edisplayDesign
         || eactivationSketch & e_activation_under_mouse_cursor
         || eactivationSketch & e_activation_display_change;

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

         design_display();

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

         WARNING("iconify child window?");

         layout().sketch() = e_display_normal;

      }
      else
      {

         design_window_minimize(layout().sketch().activation());

      }

   }


   void interaction::design_display()
   {

      auto type = __object_type(*this);

      if (type.name_contains("page_home"))
      {

         INFORMATION("page_home");

      }

      auto edisplayPrevious = layout().design().display();

      auto edisplaySketch = layout().sketch().display();

      // This check prevents saving a previous state that is the same as
      // the current one or that is equivalent (through the equivalence_sink function)
      // to the current e_display (Currently this means that e_display_broad,
      // e_display_compact and e_display_normal are considered the same
      // and not saved as previous state of such equivalent e_displays)
      if (!::is_same_in_equivalence_sink(edisplayPrevious, edisplaySketch))
      {

         set_window_previous_display(edisplayPrevious);

      }

      if (edisplaySketch == ::e_display_full_screen)
      {

         if (!is_top_level_window())
         {

            WARNING("full screen child window?");

            layout().sketch() = e_display_normal;

         }
         else
         {

            design_window_full_screen(layout().sketch().parent_client_rectangle());

         }

      }
      else if (edisplaySketch == ::e_display_iconic)
      {

         design_window_iconic();

      }
      else if (edisplaySketch == ::e_display_zoomed)
      {

         if (get_parent() != nullptr)
         {

            WARNING("zooming child window?");

            layout().sketch() = e_display_normal;

         }
         else
         {

            design_window_maximize();

         }

      }
      else if (edisplaySketch == ::e_display_normal)
      {

         //bool bIsUniversalWindows = is_universal_windows();

         //bool bIsSandboxed = is_sandboxed();

         //if (get_parent() != nullptr || bIsSandboxed || bIsUniversalWindows)
         //{

         //   WARNING("restoring child window?");

         //   layout().sketch() = e_display_normal;

         //}
         //else
         //{

            //design_window_restore(edisplaySketch);

      //   }


         layout().sketch() = e_display_normal;

      }
      else if (edisplaySketch == ::e_display_normal)
      {

         //INFORMATION("::user::interaction::design_display e_display_normal");

         layout().sketch() = e_display_normal;

      }
      else if (edisplaySketch == ::e_display_compact
         || edisplaySketch == ::e_display_broad)
      {

         if (get_parent() != nullptr)
         {

            WARNING("restoring child window?");

            layout().sketch() = e_display_normal;

         }
         else
         {

            design_window_normal(edisplaySketch);

         }

      }
      else if (edisplaySketch == ::e_display_up)
      {

         design_up();

      }
      else if (edisplaySketch == ::e_display_down)
      {

         design_down();

      }
      else if (::is_docking_appearance(edisplaySketch))
      {

         if (get_parent() != nullptr)
         {

            WARNING("snapping child window?");

            layout().sketch() = e_display_normal;

         }
         else
         {

            design_window_dock(edisplaySketch);

         }

      }
      else if (is_screen_visible(edisplaySketch))
      {

         if (get_parent() != nullptr)
         {

            INFORMATION("showing child window");

         }
         else
         {

            INFORMATION("simply showing top level window");

         }

         //display();

      }
      else
      {

         auto type = __object_type(*this);

         if (type.name_contains("page_home"))
         {

            INFORMATION("page_home");

         }

         if (get_parent() != nullptr)
         {

            //INFORMATION("hiding child window");

            layout().sketch() = e_display_none;

         }
         else
         {

            INFORMATION("hiding top level window");

         }

         //hide();

      }

      //return true;

   }


   void interaction::design_appearance()
   {

      //      ui_state().m_eappearance = process_state().m_eappearance;

      //return true;

   }


#undef false


   CLASS_DECL_AURA void zorder_sort(::user::interaction_array& uia)
   {

      auto predZ = [](auto& pui1, auto& pui2)
      {

         if (!pui1 || !pui2)
         {

            return false;

         }

         return (bool)(pui1->const_layout().sketch().zorder() < pui2->const_layout().sketch().zorder());

      };

      uia.interactiona().predicate_sort(predZ);

   }


   void interaction::design_zorder()
   {

      //      ui_state().m_zorder = process_state().m_zorder;

      //    if (get_parent() != NULL)
      {

         //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

         //string strType = __type_name(this);

         auto puiptraChildNew = __new(::user::interaction_array(*m_puserinteractionpointeraChild));

         //auto & uiptra = m_uiptraChild;

         //zorder_pre_order(uiptra);

         zorder_sort(*puiptraChildNew);

         m_puserinteractionpointeraChild = puiptraChildNew;

         int iZOrder = 1024;

         bool bSetRequest = false;

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         for (auto& pinteraction : puserinteractionpointeraChild->interactiona())
         {

            pinteraction->layout().sketch()._patch_order(iZOrder);

            pinteraction->layout().sketch().zorder().clear_request();

            iZOrder += 1024;

         }

      }

      //return true;

      m_bPendingZorder = false;

   }


#undef EXTRA_DESIGN_REPOSITION_LOG


   void interaction::design_reposition()
   {

      if (!m_bUserElementOk)
      {

         return;

      }

#ifdef EXTRA_DESIGN_REPOSITION_LOG
      auto type = __object_type(*this);

      if (type.name_contains("control_box"))
      {

         output_debug_string("control_box design_reposition");

      }

#endif

      ::point_i32 point = layout().sketch().origin();

      ::point_i32 pointScreen;

      ::point_i32 pointHost;

      auto type = __object_type(*this);

      if (type.name_contains("list_box"))
      {

         output_debug_string("list_box reposition");

      }
      else if (type.name_contains("_001"))
      {

         output_debug_string("_001 reposition");

      }


      ::point_i32 screenOriginSketchBefore = layout().sketch().origin();

      ::point_i32 screenOriginDesignBefore = layout().design().origin();

      bool bRepositionThis = true;
      //         layout().sketch().origin() != point ||
      //         layout().design().origin() != pointScreen;
      //
      //      if(bRepositionThis)
      //      {
      //
      //         screen_origin() = pointScreen;
      //
      //         layout().design().screen_origin() = pointScreen;
      //
      //         layout().sketch().host_origin() = pointHost;
      //
      //         layout().design().host_origin() = pointHost;
      //
      //      }

//      auto type = __object_type(*this);

      if (type.name_contains("tap"))
      {

         INFORMATION("tap prodevian_reposition (" << this->screen_origin().x() << ", " << this->screen_origin().y() << ")");
      }

      if (bRepositionThis)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (puserinteractionpointeraChild)
         {

            for (auto& pinteraction : puserinteractionpointeraChild->interactiona())
            {

               pinteraction->set_reposition(true);

            }

         }

      }

      on_reposition();

      set_reposition(false);

      //return true;

   }


   ::size_i32 interaction::preferred_size(::draw2d::graphics_pointer& pgraphics)
   {

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         return pappearance->preferred_size(pgraphics);

      }

      return {};

   }


   void interaction::design_layout(::draw2d::graphics_pointer& pgraphics)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (!m_pprimitiveimpl || !m_pprimitiveimpl->m_puserinteraction)
      {

         return;

      }

      //if(m_pinteractiondraw2d)
      {

         //m_pshapeaClip.release();

      }

      m_bClipRectangle = false;

      if (pgraphics)
      {

         //defer_graphics(pgraphics);

         m_pprimitiveimpl->on_layout(pgraphics);

         on_layout(pgraphics);

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            pappearance->perform_layout(pgraphics);

         }

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (puserinteractionpointeraChild)
      {

         ::rectangle_i32 rectangleClient;

         client_rectangle(rectangleClient);

         auto children = puserinteractionpointeraChild->m_interactiona;

         for (auto& pinteraction : children)
         {

            try
            {

               ::pointer<::aura::application>papp = get_app();

               if (pinteraction->m_bExtendOnParent ||
                  (pinteraction->m_bExtendOnParentIfClientOnly
                     && papp && papp->m_bExperienceMainFrame))
               {

                  bool bThisVisible = pinteraction->is_this_visible();

                  pinteraction->place(rectangleClient);

                  pinteraction->set_need_layout();

               }

            }
            catch (...)
            {

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

      //      ::rectangle_i32 rectangleClient;

      //      client_rectangle(rectangleClient);

      //      m_playout->place(rectangleClient);

      //   }

      //   m_playout->on_layout(pgraphics);

      //}

      m_bNeedLayout = false;

      //return true;

   }


   //bool interaction::CheckAutoCenter()
   //{
   //
   //   if (m_pprimitiveimpl == nullptr)
   //   {
   //
   //      return true;
   //
   //   }
   //
   //   return m_pprimitiveimpl->CheckAutoCenter();
   //
   //}


   void interaction::CenterWindow(::user::interaction* pAlternateOwner)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->CenterWindow(pAlternateOwner);

   }


   //void interaction::default_window_procedure(::message::message * pmessage)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return;

   //   }

   //   return m_pprimitiveimpl->default_window_procedure(pmessage);

   //}


   void interaction::pre_translate_message(::message::message* pmessage)
   {

      if (pmessage->m_uiMessageFlags & 1)
      {

         // message already pre translated
         return;

      }

      //auto psession = acmesession()->m_paurasession;

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


   void interaction::message_handler(::message::message* pmessage)
   {

      auto type = __object_type(*this);

      if (type.name_contains("list_box"))
      {

         ::output_debug_string("list_box");

      }

      //      pre_translate_message(pmessage);

      //      if (pmessage->m_bRet)
      //      {

      //         return;

      //      }

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      primitive_impl* pprimitiveimpl = m_pprimitiveimpl;

      bool bDestroying = pprimitiveimpl->has_destroying_flag();

      pprimitiveimpl->message_handler(pmessage);

      if (!bDestroying && m_ewindowflag & e_window_flag_window_created)
      {

         if (m_bNeedRedraw || m_bReposition)
         {

            bool bUpdateBuffer = m_bNeedRedraw;

            m_bNeedRedraw = false;

            prodevian_redraw(bUpdateBuffer);

         }

      }

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
   //      if (m_pprimitiveimpl == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return m_pprimitiveimpl->GetWindowPlacement(puserinteractionpl);
   //
   //   }
   //
   //
   //   bool interaction::SetWindowPlacement(const WINDOWPLACEMENT* puserinteractionpl)
   //   {
   //
   //      if (m_pprimitiveimpl == nullptr)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return m_pprimitiveimpl->SetWindowPlacement(puserinteractionpl);
   //
   //   }
   //
   //
   //#endif


   bool interaction::pre_create_window(::user::system* pusersystem)
   {
      //
      //#ifdef WINDOWS_DESKTOP
      //

      //#endif

      return true;

   }


   bool interaction::IsTopParentActive()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return false;

      }

      return m_pprimitiveimpl->IsTopParentActive();

   }


   void interaction::ActivateTopParent()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->ActivateTopParent();

   }


   void interaction::update_dialog_controls(channel* pTarget)
   {

      //if (m_pprimitiveimpl.is_null())
      //{

      //   return;

      //}

      //m_pprimitiveimpl->update_dialog_controls(pTarget);

   }


   void interaction::UpdateWindow()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->UpdateWindow();

   }


   void interaction::register_drop_target()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->register_drop_target();

   }


   void interaction::SetRedraw(bool bRedraw)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->SetRedraw(bRedraw);

   }


   bool interaction::GetUpdateRect(::rectangle_i32* prectangle, bool bErase)
   {

      //if (m_pprimitiveimpl == nullptr)
      //{

      //   return false;

      //}

      //return m_pprimitiveimpl->GetUpdateRect(prectangle, bErase);

      return false;

   }


   i32 interaction::GetUpdateRgn(::draw2d::region* pRgn, bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->GetUpdateRgn(pRgn, bErase);

   }


   void interaction::Invalidate(bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->Invalidate(bErase);

   }


   void interaction::InvalidateRect(const ::rectangle_i32& rectangle, bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->InvalidateRect(rectangle, bErase);

   }


   void interaction::InvalidateRgn(::draw2d::region* pRgn, bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->InvalidateRgn(pRgn, bErase);

   }


   void interaction::ValidateRect(const ::rectangle_i32& rectangle)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->ValidateRect(rectangle);

   }


   void interaction::ValidateRgn(::draw2d::region* pRgn)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->ValidateRgn(pRgn);

   }


   void interaction::on_start_layout_experience(enum_layout_experience elayoutexperience)
   {

      layout().m_elayoutexperience = elayoutexperience;

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->on_start_layout_experience(elayoutexperience);

   }


   void interaction::on_end_layout_experience(enum_layout_experience elayoutexperience)
   {

      ASSERT(layout().m_elayoutexperience == elayoutexperience);

      layout().m_elayoutexperience = e_layout_experience_none;

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      //m_pprimitiveimpl->on_end_layout_experience(elayoutexperience);

   }


   void interaction::on_configuration_change(::user::primitive* pprimitiveSource)
   {

      if (m_pprimitiveimpl)
      {

         m_pprimitiveimpl->on_configuration_change(pprimitiveSource);

      }

   }


   ::size_f64 interaction::_001CalculateFittingSize(::draw2d::graphics_pointer& pgraphics)
   {

      pgraphics->set_font(this, ::e_element_none);

      ::write_text::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      ::size_f64 setFittingFontHeight;

      string strWindowText = get_window_text();

      ::size_f64 size = pgraphics->get_text_extent(strWindowText);

      setFittingFontHeight.cx = size.cx;

      setFittingFontHeight.cy = metric.get_line_spacing();

      return setFittingFontHeight;

   }


   ::size_f64 interaction::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer& pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      ::rectangle_f64 rectanglePadding = get_padding(pstyle);

      auto sizeFitting = _001CalculateFittingSize(pgraphics);

      ::size_f64 sizePaddedFitting;

      sizePaddedFitting.cx = rectanglePadding.left + sizeFitting.cx + rectanglePadding.right;

      sizePaddedFitting.cy = rectanglePadding.top + sizeFitting.cy + rectanglePadding.bottom;

      return sizePaddedFitting;

   }


   ::user::enum_state interaction::get_user_state()
   {

      if (!is_window_enabled())
      {

         return ::user::e_state_disabled;

      }
      else
      {

         auto pwindowimpl = get_window_impl();

         if (has_hover() && (::is_set(m_pitemHover) || pwindowimpl->m_puiLastLButtonDown == this))
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


   pointer_array < interaction >* interaction::children()
   {

      if (::is_null(m_puserinteractionpointeraChild))
      {

         return nullptr;

      }

      return &m_puserinteractionpointeraChild->interactiona();

   }


   void interaction::on_layout(::draw2d::graphics_pointer& pgraphics)
   {

      layout_tooltip();

      on_change_impact_size(pgraphics);

      //if(m_pinteractiondraw2d)
      {

         m_pathFocusRect1.release();
         m_pathFocusRect2.release();
         m_pathFocusRect3.release();
         m_pathFocusRect4.release();

      }

      for (auto& puseritem : *m_pitema)
      {

         if (puseritem && puseritem->m_eelement != ::e_element_item)
         {

            puseritem->m_ppath.release();

            if (puseritem->m_eelement != e_element_item)
            {

               auto rectangle = this->rectangle(puseritem->m_eelement);

               puseritem->m_rectangle = rectangle;

            }

         }

      }

      //{

      //   auto pitem = get_user_item(::e_element_close_button);

      //   if (pitem)
      //   {

      //      //if (pitem->m_rectangle.is_null())
      //      {

      //         client_rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left = pitem->m_rectangle.right - 32;

      //         pitem->m_rectangle.bottom = pitem->m_rectangle.top + 32;

      //      }

      //   }

      //}

      //{

      //   auto pitem = get_user_item(::e_element_close_icon);

      //   if (pitem)
      //   {

      //      if (pitem->m_rectangle.is_null())
      //      {

      //         client_rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left = pitem->m_rectangle.right - 48;

      //         pitem->m_rectangle.bottom = pitem->m_rectangle.top + 48;

      //      }

      //   }

      //}

      //{

      //   auto pitem = get_user_item(::e_element_switch_button);

      //   if (pitem)
      //   {

      //      if (pitem->m_rectangle.is_null())
      //      {

      //         client_rectangle(pitem->m_rectangle);

      //         pitem->m_rectangle.left = pitem->m_rectangle.right - 48;

      //         pitem->m_rectangle.top = pitem->m_rectangle.bottom - 48;

      //      }

      //   }

      //}

      if (is_root())
      {

         m_puserinteraction->set_size(get_size());

      }

   }


   void interaction::window_show()
   {

      m_pinteractionimpl->window_show();

      if (m_bVisualChanged)
      {

         on_visual_applied();

         m_bVisualChanged = false;

      }

   }


   void interaction::on_visual_applied()
   {

      if (m_pinteractionimpl)
      {

         m_pinteractionimpl->on_visual_applied();

      }

   }


   void interaction::on_reposition()
   {

      m_bClipRectangle = false;

      layout_tooltip();

   }


   void interaction::on_show_window()
   {

      layout_tooltip();

      //      user_interaction_update_visibility_cache(_is_window_visible());

   }


   bool interaction::is_this_visible(enum_layout elayout)
   {

      if (!m_pprimitiveimpl)
      {

         return false;

      }

      return m_pprimitiveimpl->is_this_visible(elayout);

   }


#undef INFO_LAYOUT_DISPLAY


   bool interaction::sketch_on_display()
   {

      return true;

   }


   void interaction::_on_show_window()
   {

      if (is_auto_prodevian_on_show())
      {

         if (is_this_visible())
         {

            set_prodevian();

         }
         else
         {

            clear_prodevian();

         }

      }

      if (is_window_screen_visible())
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

      if (get_parent() == nullptr || is_top_level())
      {

         window_show_change_visibility();

      }

   }


   void interaction::on_drag_scroll_layout(::draw2d::graphics_pointer& pgraphics)
   {

      //if(m_bVerticalDragScroll)
      //{
      auto rectangleClient = client_rectangle();
      m_pointBarDragScrollMax = m_sizeBarDragScroll - rectangleClient.size();
      //}
      //if(m_bHorizontalDragScroll)
   //   {
   //      //auto rectangleClient = client_rectangle();
   //      //m_iHorizontalDragScrollMax = m_iHorizontalDragSize - rectangleClient.width();
   //
   //   }


   }


   void interaction::window_show_change_visibility()
   {

      //::enum_display edisplayOutput = layout().output().display();
      ::enum_display edisplayOutput = layout().design().display();

      ::enum_display edisplayWindow = layout().window().display();

      if (equivalence_sink(edisplayOutput) == e_display_normal)
      {

         edisplayOutput = e_display_normal;

      }

      if (equivalence_sink(edisplayWindow) == e_display_normal)
      {

         edisplayWindow = e_display_normal;

      }

      ::enum_display edisplayOutputForOsShowWindow = edisplayOutput;

      ::enum_display edisplayWindowForOsShowWindow = edisplayWindow;

      if (::is_docking_appearance(edisplayOutputForOsShowWindow))
      {

         edisplayOutputForOsShowWindow = e_display_normal;

      }

      if (::is_docking_appearance(edisplayWindowForOsShowWindow))
      {

         edisplayWindowForOsShowWindow = e_display_normal;

      }

#ifdef WINDOWS_DESKTOP
      if (
         //((GetExStyle() & WS_EX_LAYERED) &&
         //(::is_different(
         // ::is_screen_visible(edisplayOutputForOsShowWindow),
         // ::is_screen_visible(edisplayWindowForOsShowWindow))))
         //||
         //(!(GetExStyle() & WS_EX_LAYERED) &&
         (edisplayOutputForOsShowWindow != edisplayWindowForOsShowWindow)
         //)
         )
#else
      if (edisplayOutputForOsShowWindow != edisplayWindowForOsShowWindow)
#endif
      {

         if (m_pprimitiveimpl.is_set())
         {

            //auto eactivation = layout().output().activation();

            auto eactivation = layout().design().activation();

            m_pprimitiveimpl->window_show_change_visibility(edisplayOutputForOsShowWindow, eactivation);

         }

      }

      //      if (edisplayOutput == e_display_iconic)
      //      {
      //
      //         //#ifdef WINDOWS_DESKTOP
      //         //
      //         //         if (GetExStyle() & WS_EX_LAYERED)
      //         //         {
      //         //
      //         //            layout().window() = edisplayOutput;
      //         //
      //         //         }
      //         //
      //         //#endif
      //         //
      //         output_debug_string("blocking setting window state to iconic (1)");
      //
      //      }
      //      else
      //      {

      layout().window() = edisplayOutput;

      //      }
      //
   }


   void interaction::defer_save_window_placement()
   {


   }


   void interaction::ShowOwnedPopups(bool bShow)
   {
      if (m_pprimitiveimpl == nullptr)
         return;
      else
      {
         m_pprimitiveimpl->ShowOwnedPopups(bShow);

      }
   }


   void* interaction::get_os_data()
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
   //   if (m_pprimitiveimpl == nullptr)
   //      return false;
   //   else
   //      return m_pprimitiveimpl->attach(oswindow_New);

   //}


   oswindow interaction::detach_window()
   {

      auto pprimitiveimpl = m_pprimitiveimpl;

      if (!pprimitiveimpl)
      {

         return nullptr;

      }

      auto oswindow = pprimitiveimpl->detach_window();

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

       auto pinteractionimpl = puserinteraction->m_pinteractionimpl;

       if (!pinteractionimpl)
       {

          return nullptr;

       }

       return pinteractionimpl->get_window();

    }*/


   void interaction::pre_subclass_window()
   {
      if (m_pprimitiveimpl == nullptr)
         return;
      else
         m_pprimitiveimpl->pre_subclass_window();
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

      layout().sketch() = rectangle_i32_dimension(x, y, cx, cy);

      display(e_display_normal);

   }


   atom interaction::run_modal_loop(::user::interaction* pinteraction, u32 dwFlags)
   {

      return pinteraction->_001RunModalLoop(dwFlags);

   }


   atom interaction::RunModalLoop(u32 dwFlags)
   {

      set_need_redraw();

      post_redraw();

      return _001RunModalLoop(dwFlags);

   }


   atom interaction::_001RunModalLoop(u32 dwFlags)
   {

      ASSERT(!m_bModal);

      if (m_bModal)
      {

         return ::atom();

      }

      KEEP(m_bModal);

      __keep_current_thread(m_ptaskModal);

      while (true)
      {

         if (!ContinueModal())
         {

            break;

         }


         if (::is_null(get_task()))
         {

            break;

         }

         if (!get_thread()->pump_message())
         {

            break;

         }

      }

      //psystem->post_to_all_threads(e_message_kick_idle, 0, 0);

      return m_atomModalResult;

   }


   bool interaction::ContinueModal()
   {

      bool bRun = ::task_get_run();

      return m_bModal && bRun;

   }


   void interaction::EndModalLoop(atom idResult)
   {

      TRACE("EndModalLoop");

      ASSERT(is_window());

      // this result will be returned from interaction_impl::RunModalLoop
      m_atomModalResult = idResult;

      // make sure a message goes through to exit the modal loop
      m_bModal = false;

      //if (::sequence<::conversation>::m_p)
      {

         m_payloadResult = idResult;

         m_estatus = ::success;

      }

      post_message(MESSAGE_CLOSE);

      if (::is_set(m_ptaskModal))
      {

         m_ptaskModal->kick_thread();

      }

      if (get_wnd() != nullptr && get_wnd()->m_pthreadUserInteraction.is_set())
      {

         get_wnd()->m_pthreadUserInteraction->kick_thread();

      }

   }


   void interaction::post_message(const ::atom& atom, wparam wparam, lparam lparam)
   {

      return m_pprimitiveimpl->post_message(atom, wparam, lparam);

   }


   void interaction::post_object(const ::atom& atom, wparam wparam, lparam lparam)
   {

      bool bIsWindow = m_pprimitiveimpl.is_set() && is_window();

      if (atom == e_message_quit || !bIsWindow)
      {

         {

            // discards object
            ::pointer <::particle > pparticle(lparam);


         }

         if (!bIsWindow)
         {

            return;

         }

         return m_pprimitiveimpl->post_message(atom);

      }

      return m_pprimitiveimpl->post_message(atom, wparam, lparam);


   }


   //bool interaction::user_post(const ::atom& atom, wparam wparam, lparam lparam)
   //{
   //
   //   return m_pthreadUserInteraction->post_message(atom, wparam, lparam);
   //
   //}



   void interaction::call_and_set_timer(uptr uEvent, const class time& timeElapse, PFN_TIMER pfnTimer)
   {

      if (has_flag(e_flag_destroying))
      {

         return;

      }

      ::timer timer(uEvent);

      _001OnTimer(&timer);

      return SetTimer(uEvent, timeElapse, pfnTimer);

   }


   void interaction::set_timer(uptr uEvent, const class time& timeElapse, PFN_TIMER pfnTimer, bool bPeriodic,
      void* pdata)
   {

      if (has_destroying_flag())
      {

         return;

      }

      return SetTimer(uEvent, timeElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::SetTimer(uptr uEvent, const class time& timeElapse, PFN_TIMER pfnTimer, bool bPeriodic,
      void* pdata)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      if (has_destroying_flag())
      {

         return;

      }

      return m_pprimitiveimpl->SetTimer(uEvent, timeElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::KillTimer(uptr uEvent)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->KillTimer(uEvent);

   }


   bool interaction::has_keyboard_focus()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return false;

      }

      if (!pwindowThis->has_keyboard_focus())
      {

         return false;

      }

      auto pprimitiveimplFocus = pwindowThis->m_puserinteractionimpl;

      if (::is_null(pprimitiveimplFocus))
      {

         return false;

      }

      if (pprimitiveimplFocus->m_puserinteractionKeyboardFocus != this)
      {

         return false;

      }

      return true;

   }


   void interaction::set_keyboard_focus()
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return;

      }

      auto pprimitiveimpl = pwindowThis->m_puserinteractionimpl;

      if (::is_null(pprimitiveimpl))
      {

         return;

      }

      pprimitiveimpl->m_puserinteractionKeyboardFocusRequest = this;

      if (pwindowThis->has_keyboard_focus())
      {

         pprimitiveimpl->on_final_set_keyboard_focus();

      }
      else
      {

         pwindowThis->set_keyboard_focus();

      }

   }


   bool interaction::has_mouse_capture()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return false;

      }

      auto pwindow = pwindowing->get_mouse_capture(m_pthreadUserInteraction);

      if (::is_null(pwindow))
      {

         return false;

      }

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return false;

      }

      if (*pwindow != *pwindowThis)
      {

         return false;

      }

      auto pprimitiveimpl = pwindowThis->m_puserinteractionimpl;

      if (::is_null(pprimitiveimpl))
      {

         return false;

      }

      if (pprimitiveimpl->m_puserinteractionMouseCapture != this)
      {

         return false;

      }

      return true;

   }


   void interaction::set_foreground_window()
   {

      auto phost = get_host_window();

      if (!phost)
      {

         //return error_failed;

         return;

      }

      auto pprimitiveimpl = phost->m_pinteractionimpl;

      if (!pprimitiveimpl)
      {

         //return error_failed;

         return;

      }

      auto pwindow = pprimitiveimpl->m_pwindow;

      if (!pprimitiveimpl)
      {

         //return error_failed;

         return;

      }

      return pwindow->set_foreground_window();

   }


   void interaction::set_active_window()
   {

      auto phost = get_host_window();

      if (!phost)
      {

         //return error_failed;

         return;

      }

      auto pprimitiveimpl = phost->m_pinteractionimpl;

      if (!pprimitiveimpl)
      {

         //return error_failed;

         return;

      }

      auto pwindow = pprimitiveimpl->m_pwindow;

      if (!pprimitiveimpl)
      {

         //return error_failed;

         return;

      }

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
      //      auto pwindow = pwindowing->get_active_window(m_pthreadUserInteraction);
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

      //      if (*pwindow != *pwindowThis)
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


   void interaction::set_mouse_capture()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         return;

      }

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         throw ::exception(error_wrong_state);

      }

      auto pprimitiveimpl = pwindowThis->m_puserinteractionimpl;

      if (::is_null(pprimitiveimpl))
      {

         throw ::exception(error_wrong_state);

      }

      //auto estatus = 

      pwindowThis->set_mouse_capture();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      pprimitiveimpl->m_puserinteractionMouseCapture = this;

      g_i134++;

      //return true;

   }


   //::user::interaction * interaction::get_capture()
   //{

   //   if (m_pprimitiveimpl != nullptr)
   //   {

   //      return m_pprimitiveimpl->get_capture();

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

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->ReleaseCapture();

   //}


   void interaction::track_mouse_leave()
   {

      track_mouse_hover();

   }


   void interaction::track_mouse_hover()
   {

      //      synchronous_lock synchronouslock(this->synchronization());

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

   //   bool bWindowLargerThanBroadRestore = rectangleRequest.width() > m_sizeRestoreBroad.cx
   //      || rectangleRequest.height() > m_sizeRestoreBroad.cy;

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


   static i64 g_i_prodevian_update_visual = 0;


   void interaction::sketch_to_design(bool& bUpdateBuffer, bool& bUpdateWindow)
   {
      
      _synchronous_lock synchronouslock(this->synchronization());

      bUpdateBuffer = false;

      bUpdateWindow = false;

      //string strType = __type_name(this);

      //if (strType.contains("app_veriwell_keyboard") && strType.contains("main_frame"))
      //{

      //   //output_debug_string("app_veriwell_keyboard::main_frame");

      //}
      ////      else if (strType.contains("main_frame"))
      ////      {
      ////
      ////         output_debug_string("main_frame");
      ////
      ////      }
      ////      else if (strType.contains("place_holder"))
      ////      {
      ////
      ////         output_debug_string("place_holder");
      ////
      ////      }
      ////   else if (strType.contains("combo_box"))
      ////   {
      ////
      ////      output_debug_string("combo_box");
      ////
      ////   }
      ////   else if (strType.contains("list_box"))
      ////   {
      ////
      ////      output_debug_string("list_box");
      ////
      ////   }

      KEEP(m_bUpdatingVisual);

      bool bDisplay = display_sketch_to_design();

      if (m_pinteractionimpl && m_pinteractionimpl->m_bOfflineRender)
      {

         if (layout().sketch().display() != e_display_hide)
         {

            hide();

         }

      }

      if (!is_equivalent(layout().sketch().display(), layout().design().display()))
      {

         layout().m_timeLastSketchToDesign.Now();

      }

      bool bAppearance = layout().sketch().appearance() != layout().design().appearance();

      ::point_i32 pointSketch = layout().sketch().origin();

      ::point_i32 pointDesign = layout().design().origin();

      bool bPosition = pointSketch != pointDesign || m_bReposition;

      m_bReposition = false;

      ::size_i32 & sizeSketch = layout().sketch().size();

      ::size_i32 & sizeDesign = layout().design().size();

      if (m_bDerivedHeight)
      {

         int iDerivedWidth = sizeSketch.cx;

         int iDerivedHeight = get_derived_height(iDerivedWidth);

         ::size_i32 sizeMinimum = get_window_minimum_size();

         if (iDerivedHeight > 0)
         {

            if (iDerivedHeight < sizeMinimum.cy)
            {

               iDerivedHeight = sizeMinimum.cy;

               iDerivedWidth = get_derived_width(iDerivedHeight);

            }

         }

         if (iDerivedWidth >= sizeMinimum.cx && iDerivedHeight >= sizeMinimum.cy)
         {

            sizeSketch.cx = iDerivedWidth;

            sizeSketch.cy = iDerivedHeight;

            layout().sketch().size() = sizeSketch;

         }

      }

      bool bLayout = sizeSketch != sizeDesign || m_bNeedLayout;

      m_bNeedLayout = false;

      if (bLayout)
      {

         layout().design().copy_size(layout().sketch());

      }

      if (bPosition)
      {

         layout().design().copy_position(layout().sketch());

         if (::is_set(get_parent()))
         {

            set_need_redraw(layout().design().client_rect());

         }

      }

      if (bDisplay)
      {

         layout().design().copy_display(layout().sketch());

      }

      if (bDisplay)
      {

         layout().design().copy_display(layout().sketch());

      }

      bool bZorder = false;

      if (is_top_level())
      {

         if (layout().sketch().zorder().is_change_request())
         {

            layout().design() = layout().sketch().zorder();

            bZorder = true;

         }

      }

      bool bActivation = layout().sketch().m_eactivation != ::e_activation_default;

      layout().design() = layout().sketch().appearance();

      if (bActivation)
      {

         layout().design().m_eactivation = layout().sketch().m_eactivation;

      }

      layout().sketch().clear_activation();

      if (m_bAutomaticallyStoreWindowRectangle)
      {

         if (bDisplay || bAppearance)
         {

            // bPosition and bLayout wouldn't set this flag,
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

               INFORMATION(
                  "window visual changed: not setting pending save rectangle_i32 cause loading window rectangle_i32");

            }
            else
            {

               m_bPendingSaveWindowRectangle = true;

            }

         }

      }

      if (check_child_zorder())
      {

         bZorder = true;

      }

      m_bUpdateVisual |= bDisplay || bZorder || bLayout || bActivation;

      if (!bUpdateBuffer && ::is_set(get_parent()))
      {

         bUpdateBuffer = bPosition;

      }

      if (!bUpdateBuffer && m_pinteractionimpl)
      {

         bUpdateBuffer = m_pinteractionimpl->m_rectangleaNeedRedraw.has_element();

      }

      //INFORMATION("bLayout=" << (bLayout?"true":"false"));

      bUpdateWindow = bDisplay || bZorder || bPosition;

      bool bDeferDisplay =
         m_bUpdateVisual
         || bPosition
         || !is_equivalent(layout().sketch().display(), layout().design().display());

      if (bDeferDisplay)
      {

         on_defer_display();

      }

      if (m_bUpdateVisual)
      {

         if (bAppearance)
         {

            design_appearance();

         }

         //         if (bZorder)
         //         {
         //
         //            //design_zorder();
         //            m_bPendingZorder = true;
         //
         //         }
         //
         if (bLayout)
         {

            //::pointer<::user::interaction_impl>pprimitiveimpl = m_pprimitiveimpl;

            //if (pprimitiveimpl)
            //{

            //   pprimitiveimpl->m_re;

            //}

            m_bSketchToDesignLayout = true;

            //design_layout(pgraphics);

         }

         if (bDisplay)
         {

            //output_debug_string(as_string(++g_i_prodevian_update_visual) + "updvis dpy machine\n");

         }

      }

      if (bDeferDisplay || bPosition)
      {

         if (!(m_ewindowflag & e_window_flag_embedded_prodevian))
         {

            if (!(m_ewindowflag & e_window_flag_postpone_visual_update))
            {

               if (m_pprimitiveimpl)
               {

                  m_pprimitiveimpl->start_window_visual();

               }

            }

         }

      }

      if (bPosition)
      {

         design_reposition();

      }

      if (bDisplay)
      {

         _001OnAfterExitAppearance();

         _001OnAfterEnterAppearance();

      }

      if (!layout().design().is_screen_visible())
      {

         if (m_ewindowflag & e_window_flag_on_show_window_visible
            || m_ewindowflag & e_window_flag_on_show_window_screen_visible)
         {

            m_ewindowflag -= e_window_flag_on_show_window_visible;

            m_ewindowflag -= e_window_flag_on_show_window_screen_visible;

            _on_show_window();

         }

      }
      else if (get_parent() != nullptr)
      {

         m_ewindowflag += e_window_flag_on_show_window_visible;

         m_ewindowflag += e_window_flag_on_show_window_screen_visible;

         _on_show_window();

      }

      if (m_bUpdateVisual || m_bReposition)
      {

         if (!(m_ewindowflag & e_window_flag_postpone_visual_update))
         {

            if (m_ewindowflag & e_window_flag_embedded_prodevian)
            {

               auto psession = get_session();

               if (get_parent() == nullptr || get_parent() == psession->get_user_interaction_host())
               {

                  if (m_pinteractionimpl)
                  {

                     m_pinteractionimpl->window_show();

                  }

               }
               else
               {

                  if (m_pprimitiveimpl)
                  {

                     m_pprimitiveimpl->start_window_visual();

                  }

               }

            }

         }

      }

   }


   void interaction::_001UpdateWindow()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->_001UpdateWindow();

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

   //    m_pprimitiveimpl->window_apply_visual(windowstate);

   // }


   //void interaction::GuieProc(::message::message * pmessage)
   //{
   //
   //   __UNREFERENCED_PARAMETER(pmessage);
   //
   //}


   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics)
   {

      if (m_pprimitiveimpl != nullptr)
      {

         //         m_pprimitiveimpl->_001DeferPaintLayeredWindowBackground(pgraphics);

      }

   }


   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer& pgraphics)
   {

      _001DeferPaintLayeredWindowBackground(pgraphics);

   }


   //::oswindow interaction::_oswindow() const
   //{

   //   return oswindow();

   //}


   void interaction::OnLinkClick(const ::string& psz, const ::string& pszTarget)
   {

      auto phyperlink = __create_new<::hyperlink>();

      phyperlink->m_strLink = psz;

      phyperlink->m_strTarget = pszTarget;

      phyperlink->run();

      //hyperlink.open_link(psz, "", pszTarget);

   }


   bool interaction::on_set_parent(::user::primitive* puserprimitiveParent)
   {

      ::pointer < ::user::interaction > puserinteractionParent = puserprimitiveParent;

      if (m_puserinteractionParent == puserinteractionParent)
      {

         INFORMATION("-------------------------------------------------------------------");
         INFORMATION("");
         INFORMATION("");
         INFORMATION("interaction::on_set_parent (xxxx1)");
         INFORMATION("");
         INFORMATION("");
         return false;

      }

      if (::is_set(puserinteractionParent) && puserinteractionParent->is_descendant_of(this, true))
      {

         INFORMATION("-------------------------------------------------------------------");
         INFORMATION("");
         INFORMATION("");
         INFORMATION("interaction::on_set_parent (xxxx2)");
         INFORMATION("");
         INFORMATION("");

         return false;

      }

      ::pointer<::user::interaction>puiThis = this;

      //synchronous_lock slChildren(::user::pointer < ::mutex >_children());

      try
      {

         if (m_puserinteractionParent != nullptr
            && m_puserinteractionParent != puserinteractionParent)
         {

            INFORMATION("-------------------------------------------------------------------");
            INFORMATION("");
            INFORMATION("");
            INFORMATION("interaction::on_set_parent (erase)");
            INFORMATION("");
            INFORMATION("");

            auto puiptraChildNew = __new(
               ::user::interaction_array(*m_puserinteractionParent->m_puserinteractionpointeraChild));
            puiptraChildNew->erase_interaction(this);
            m_puserinteractionParent->m_puserinteractionpointeraChild = puiptraChildNew;

         }

      }
      catch (...)
      {
      }

      m_puserinteractionParent = puserinteractionParent;

      try
      {

         if (::is_set(puserinteractionParent))
         {

            auto pthreadParentUserInteraction = puserinteractionParent->get_wnd()->m_pthreadUserInteraction;

            if (m_pthreadUserInteraction != pthreadParentUserInteraction)
            {

               if (m_pthreadUserInteraction)
               {

                  if (::is_set(m_pthreadUserInteraction->m_puserprimitiveaThread))
                  {

                     m_pthreadUserInteraction->m_puserprimitiveaThread->erase(this);

                  }

                  m_pthreadUserInteraction.release();

               }

               m_pthreadUserInteraction = puserinteractionParent->get_wnd()->m_pthreadUserInteraction;

            }

            puserinteractionParent->on_add_child(this);

         }

      }
      catch (...)
      {

         INFORMATION("-------------------------------------------------------------------");
         INFORMATION("");
         INFORMATION("");
         INFORMATION("interaction::on_set_parent (xxxxxx3)");
         INFORMATION("");
         INFORMATION("");

      }

      return true;

   }


   bool interaction::on_add_child(::user::interaction* puserinteractionChild)
   {

      //INFORMATION("interaction::on_add_child start\n");

      puserinteractionChild->m_pinteractionScaler = m_pinteractionScaler;

      ::pointer<::user::interaction_array>puserinteractionpointeraChildNew;

      if (::is_set(m_puserinteractionpointeraChild))
      {

         puserinteractionpointeraChildNew = __new(::user::interaction_array(*m_puserinteractionpointeraChild));

      }
      else
      {

         __construct_new(puserinteractionpointeraChildNew);

      }

      puserinteractionpointeraChildNew->add_unique_interaction(puserinteractionChild);

      m_puserinteractionpointeraChild = puserinteractionpointeraChildNew;

      return true;

   }


   void interaction::on_after_set_parent()
   {

#ifdef REPORT_OFFSET

      printf("interaction::on_after_set_parent(1) m_pwindow (0x%x)\n", m_pwindow);

      fflush(stdout);

#endif

      m_puserinteractionTopLevel = _top_level();

      m_puserframeParent = _parent_frame();

      m_puserframeTopLevel = _top_level_frame();

      m_pwindow = window();

#ifdef REPORT_OFFSET

      printf("interaction::on_after_set_parent(2) m_pwindow (0x%x)\n", m_pwindow);

      fflush(stdout);

#endif

      m_oswindow = m_pwindow->oswindow();

   }


   bool interaction::on_set_owner(::user::primitive* pprimitive)
   {

      return true;

   }


   void interaction::create_message_queue(const ::string& lpszName)
   {

      if (is_window())
      {

         start_destroying_window();

      }

      //try
      //{

      m_bUserElementOk = true;

      m_pprimitiveimpl = __create<interaction_impl>();

      if (m_pprimitiveimpl == nullptr)
      {

         m_bUserElementOk = false;

         return;

      }

      m_bMessageWindow = true;

      m_pprimitiveimpl->m_puserinteraction = this;

      //m_pdescriptor.defer_create(this);

      m_pprimitiveimpl->create_message_queue(this, lpszName);

      //if (!m_pprimitiveimpl->create_message_queue(this, lpszName))
      //{

      //   //m_threadptra.erase_all();

      //   m_bUserElementOk = false;

      //   m_pprimitiveimpl.release();

      //   return false;

      //}

      //}
      //catch (...)
      //{

      //   m_bUserElementOk = false;

      //   return false;

      //}

      //return true;

   }


   ::pointer<::message::message> interaction::get_message(const ::atom& atom, wparam wparam, lparam lparam, ::message::enum_prototype eprototype)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return ::user::primitive::get_message(atom, wparam, lparam, eprototype);

      }

      return m_pprimitiveimpl->get_message(atom, wparam, lparam, eprototype);

   }


   void interaction::walk_pre_translate_tree(::message::message* pmessage, ::user::interaction* puiStop)
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

      ::user::interaction* puserinteractionParent = get_parent();

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


   bool interaction::contains_user_interaction(::user::interaction* pinteraction, bool bRecursive)
   {

      if (this == pinteraction)
      {

         return true;

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (puserinteractionpointeraChild->contains_interaction(pinteraction))
      {

         return true;

      }

      if (!bRecursive)
      {

         return false;

      }

      for (auto& puiChild : puserinteractionpointeraChild->interactiona())
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

      auto pinteraction = get_host_window();

      if (::is_null(pinteraction))
      {

         return 0.0;

      }

      auto pinteractionimpl = pinteraction->m_pinteractionimpl;

      if (!pinteractionimpl)
      {

         return 0.0;

      }

      return pinteractionimpl->get_output_per_second();

   }


   ::pointer<::windowing::cursor>interaction::get_mouse_cursor(enum_cursor ecursor)
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


   ::windowing::cursor* interaction::get_mouse_cursor()
   {

      return m_pcursor;

   }


   ::point_i32 interaction::get_cursor_position()
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         return {};

      }

      auto pointCursor = pwindow->get_cursor_position();

      return pointCursor;

   }


   void interaction::set_cursor_position(const ::point_i32& pointCursor)
   {

      auto pwindow = window();

      if (::is_null(pwindow))
      {

         throw ::exception(::error_wrong_state);

      }

      pwindow->set_cursor_position(pointCursor);

   }


   void interaction::release_mouse_capture()
   {

      auto pwindowing = windowing();

      if (::is_null(pwindowing))
      {

         throw ::exception(::error_wrong_state);

      }


      pwindowing->release_mouse_capture();

   }


   ::draw2d::graphics_pointer interaction::create_memory_graphics()
   {

      auto psystem = acmesystem()->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      return pgraphics;

   }


   double interaction::_001GetDefaultFontHeight(::draw2d::graphics_pointer& pgraphics)
   {

      defer_graphics(pgraphics);

      pgraphics->set_font(this, ::e_element_none);

      ::size_f64 size;

      size = pgraphics->get_text_extent(unitext("Ág"));

      return size.cy;

   }


   void interaction::set_mouse_cursor(::windowing::cursor* pcursor)
   {

      //      if (!m_pprimitiveimpl)
      //      {
      //
      //         return false;
      //
      //      }
      //
      //      auto estatus = m_pprimitiveimpl->set_mouse_cursor(pcursor);
      //
      //      if(!estatus)
      //      {
      //
      //         return estatus;
      //
      //      }

      m_pcursor = pcursor;

   }


   //void interaction::set_mouse_cursor(::windowing::cursor * pcursor)
   //{

   //   if (!m_pinteractionimpl)
   //   {

   //      return false;

   //   }

   //   if (!m_pinteractionimpl->set_mouse_cursor(pcursor))
   //   {

   //      return false;

   //   }

   //   return true;

   //}


   //::point_i32 interaction::get_cursor_position() const
   //{

   //   auto puserinteraction = get_host_window();

   //   if (puserinteraction == this)
   //   {

   //      return m_pprimitiveimpl->get_cursor_position();

   //   }

   //   if (!puserinteraction)
   //   {

   //      return ::point_i32();

   //   }

   //   return puserinteraction->get_cursor_position();

   //}


   void interaction::on_message_mouse_enter(::message::message* pmessage)
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



   bool interaction::can_merge(::user::interaction* pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   bool interaction::merge(::user::interaction* pinteraction)
   {

      __UNREFERENCED_PARAMETER(pinteraction);

      return false;

   }


   ::user::element* interaction::first_child_user_primitive()
   {

      return first_child();

   }


   ::user::element* interaction::top_user_primitive()
   {

      return primitive::top_user_primitive();

   }


   ::user::element* interaction::under_user_primitive()
   {

      return under_sibling();

   }


   ::user::element* interaction::above_user_primitive()
   {

      return above_sibling();

   }


   ::user::element* interaction::next_user_primitive()
   {

      return next_sibling();

   }


   ::user::element* interaction::previous_user_primitive()
   {

      return previous_sibling();

   }


   ::user::interaction* interaction::first_child()
   {

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

   ::user::interaction* interaction::last_child()
   {
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


   ::user::interaction* interaction::first_sibling()
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


   ::user::interaction* interaction::next_sibling()
   {
      try
      {

         ::user::interaction* pinteraction = nullptr;
         try
         {
            pinteraction = get_parent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteraction == nullptr)
            return nullptr;
         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         index i = puserinteractionpointeraChild->interactiona().find_first(this);
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

   ::user::interaction* interaction::next_sibling(::user::interaction* pinteraction)
   {
      synchronous_lock synchronouslock(this->synchronization());
      try
      {
         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;
         index i = puserinteractionpointeraChild->find_first_interaction(pinteraction);
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

   ::user::interaction* interaction::previous_sibling()
   {

      try
      {

         ::user::interaction* pinteraction = nullptr;
         try
         {
            pinteraction = get_parent();
         }
         catch (...)
         {
            return nullptr;
         }
         if (pinteraction == nullptr)
            return nullptr;

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            return nullptr;

         }

         index i = puserinteractionpointeraChild->find_first_interaction(this);
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

   ::user::interaction* interaction::last_sibling()
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


   void interaction::mouse_hover_add(::user::interaction* pinterface)
   {

      auto puserinteraction = get_wnd();

      if (!puserinteraction)
      {

         //return false;

         throw ::exception(error_wrong_state);

      }

      auto pprimitiveimpl = puserinteraction->m_pprimitiveimpl;

      if (!pprimitiveimpl)
      {

         throw ::exception(error_null_pointer);

      }

      //auto bOk = 

      pprimitiveimpl->mouse_hover_add(pinterface);

      //if (!bOk)
      //{

      //   return bOk;

      //}

      //return bOk;

   }


   bool interaction::mouse_hover_erase(::user::interaction* pinterface)
   {

      auto puserinteraction = get_wnd();

      if (!puserinteraction || puserinteraction == this)
      {

         return false;

      }

      auto pprimitiveimpl = puserinteraction->m_pprimitiveimpl;

      if (!pprimitiveimpl)
      {

         return false;

      }

      auto bOk = pprimitiveimpl->mouse_hover_erase(pinterface);

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


   ::user::interaction* interaction::previous_sibling(::user::interaction* pinteraction)
   {
      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      index i = puserinteractionpointeraChild->find_first_interaction(pinteraction);
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


   void interaction::get_child_rect(::rectangle_i32& rectangle)
   {

      client_rectangle(rectangle);

   }


   //bool interaction::keyboard_focus_OnChildKillFocus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //      return true;


   //   return m_pprimitiveimpl->keyboard_focus_OnChildKillFocus();

   //}


   ::user::interaction* interaction::get_os_focus_uie()
   {

      return nullptr;

   }


   bool interaction::is_ascendant(element* puiIsAscendant, bool bIncludeSelf)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return false;

      }

      return m_pprimitiveimpl->is_ascendant(puiIsAscendant, bIncludeSelf);

   }


   bool interaction::is_parent(element* puiIsParent)
   {

      return m_pprimitiveimpl->is_parent(puiIsParent);

   }


   bool interaction::is_child(element* puiIsChild)
   {

      return m_pprimitiveimpl->is_child(puiIsChild);

   }


   //bool interaction::is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const
   //{

   //   return m_pprimitiveimpl->is_descendant(puiIsDescendant, bIncludeSelf);

   //}


   bool interaction::is_ascendant(::user::controller* pcontroller, bool bIncludeSelf)
   {

      if (::is_null(pcontroller))
      {

         return false;

      }

      for (::index iImpact = 0; iImpact < pcontroller->impact_count(); iImpact++)
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


   bool interaction::contains(element* puiIsChild)
   {

      return is_child(puiIsChild);

   }


   bool interaction::recursively_contains(element* puiIsChild, bool bIncludeSelf)
   {

      return is_descendant(puiIsChild, bIncludeSelf);

   }


   ::user::interaction* interaction::get_wnd()
   {

      if (m_puserinteractionParent == this)
      {

         ((::user::interaction*)this)->m_puserinteractionParent.release();

         return nullptr;

      }

      if (m_puserinteractionParent == nullptr)
      {

         return (::user::interaction*)this;

      }

      //auto psession = get_session();

      //if(::is_set(psession) && m_puserinteractionParent == psession->get_user_interaction_host())
      if (m_bUserInteractionHost)
      {

         return (::user::interaction*)this;

      }

      return m_puserinteractionParent->get_wnd();

   }


   // returns -1 if not descendant
   i32 interaction::get_descendant_level(::user::element* pinteraction)
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


   bool interaction::is_descendant(::user::element* pinteraction, bool bIncludeSelf)
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


   ::user::interaction* interaction::get_focusable_descendant()
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

            return (::user::interaction*)pinteraction;

         }

      }

   }


//   void interaction::_001OnTriggerMouseInside()
//   {
//
//      if (m_pprimitiveimpl != nullptr)
//      {
//
//         m_pprimitiveimpl->_001OnTriggerMouseInside();
//
//      }
//
//   }


   void interaction::update_data(bool bSaveAndValidate)
   {

      //return true;

   }


   void interaction::on_message_close(::message::message* pmessage)
   {

      pmessage->m_bRet = true;

      for (auto& pitem : *m_pitema)
      {

         if (pitem->m_eelement == ::e_element_close_button || pitem->m_eelement == ::e_element_close_icon)
         {

            if (pitem->m_atom == ::id_close_app)
            {

               display(e_display_hide);

               set_need_layout();

               set_need_redraw();

               post_redraw();

               auto papp = get_app();

               papp->_001TryCloseApplication();

               return;

            }

         }

      }

      display(e_display_none);

      start_destroying_window();

   }


   string interaction::get_window_default_matter()
   {

      return "";

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


   void interaction::on_message_simple_command(::message::message* pmessage)
   {

      ::pointer < ::message::simple_command > psimplecommand = pmessage;

      on_simple_command(psimplecommand);

   }


   void interaction::on_message_need_load_form_data(::message::message* pmessage)
   {

      m_bNeedLoadFormData = false;

      update_data(false);

      set_need_redraw();

      post_redraw();

   }


   void interaction::on_message_need_save_form_data(::message::message* pmessage)
   {

      m_bNeedSaveFormData = false;

      update_data(true);

   }


   bool interaction::OnCommand(::message::message* pmessage)
   {

      //if (m_pprimitiveimpl != nullptr)
      //{

      //   return m_pprimitiveimpl->OnCommand(pmessage);

      //}

      return false;

   }


   bool interaction::OnNotify(::message::message* pmessage)
   {

      //if (m_pprimitiveimpl != nullptr)
      //{

      //   return m_pprimitiveimpl->OnNotify(pmessage);

      //}

      return false;

   }


   bool interaction::OnChildNotify(::message::message* pmessage)
   {

      if (m_pprimitiveimpl != nullptr)
      {

         return m_pprimitiveimpl->OnChildNotify(pmessage);

      }

      return false;

   }


   void interaction::on_simple_command(::message::simple_command* psimplecommand)
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

         ::user::interaction* puiTop = get_wnd();

         if (puiTop != this)
         {

            ASSERT(false);

            return;

         }

         ::pointer<::user::interaction_impl>pprimitiveimpl = m_pprimitiveimpl;

         bool bStart = pprimitiveimpl->m_bTransparentMouseEvents
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

            synchronous_lock synchronouslock(this->synchronization());

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
      //case e_simple_command_defer_start_prodevian:
      //{

      //   m_pprimitiveimpl->_defer_start_prodevian();


      //}
      break;
      default:

         break;

      }

      if (psimplecommand->m_bRet)
      {

         return;

      }

      ::user::primitive::on_simple_command(psimplecommand);

   }


   void interaction::on_command(::message::command* pcommand)
   {

      ::user::primitive::on_command(pcommand);

   }


   bool interaction::is_selected(::data::item* pitem)
   {

      __UNREFERENCED_PARAMETER(pitem);

      return false;

   }


   //// <3ThomasBorregaardSørensen__!!
   void interaction::handle_command(const ::atom& atom)
   {

      if (m_pmatterCommandHandler)
      {

         return m_pmatterCommandHandler->handle_command(atom);

      }

      //return ::error_failed;

   }


   bool interaction::has_command_handler(::message::command* pcommand)
   {

      if (channel::has_command_handler(pcommand))
      {

         return true;

      }

      return false;

   }


   bool interaction::_001OnBeforeEnterIconic()
   {

      return ::user::primitive::_001OnBeforeEnterIconic();

   }


   bool interaction::_001OnBeforeEnterNormal()
   {

      return ::user::primitive::_001OnBeforeEnterNormal();

   }


   bool interaction::_001OnBeforeEnterZoomed()
   {

      return ::user::primitive::_001OnBeforeEnterZoomed();

   }


   bool interaction::_001OnBeforeEnterFullScreen()
   {

      return ::user::primitive::_001OnBeforeEnterFullScreen();

   }


   bool interaction::_001OnBeforeEnterAppearance()
   {

      if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
      {

         auto edisplaySketch = layout().sketch().display();

         auto edisplayDesign = layout().design().display();

         if (edisplaySketch == e_display_iconic && edisplayDesign != e_display_iconic)
         {

            return _001OnBeforeEnterIconic();

         }
         else if (edisplaySketch == e_display_zoomed && edisplayDesign != e_display_zoomed)
         {

            return _001OnBeforeEnterZoomed();

         }
         else if (equivalence_sink(edisplaySketch) == e_display_normal && equivalence_sink(edisplayDesign) != e_display_normal)
         {

            return _001OnBeforeEnterNormal();

         }
         else if (edisplaySketch == e_display_full_screen && edisplayDesign != e_display_full_screen)
         {

            return _001OnBeforeEnterFullScreen();

         }

      }

      return true;

   }


   void interaction::_001OnAfterEnterIconic()
   {

      ::user::primitive::_001OnAfterEnterIconic();

   }


   void interaction::_001OnAfterEnterNormal()
   {

      ::user::primitive::_001OnAfterEnterNormal();

   }


   void interaction::_001OnAfterEnterZoomed()
   {

      ::user::primitive::_001OnAfterEnterZoomed();

   }


   void interaction::_001OnAfterEnterFullScreen()
   {

      ::user::primitive::_001OnAfterEnterFullScreen();

   }


   void interaction::_001OnAfterEnterAppearance()
   {

      if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
      {

         auto edisplayDesign = layout().design().display();

         if (edisplayDesign == e_display_iconic)
         {

            _001OnAfterEnterIconic();

            auto ptopic = create_topic(id_on_after_enter_iconic);

            route(ptopic);

         }
         else if (equivalence_sink(edisplayDesign) == e_display_normal)
         {

            _001OnAfterEnterNormal();

            auto ptopic = create_topic(id_on_after_enter_normal);

            route(ptopic);

         }
         else if (edisplayDesign == e_display_zoomed)
         {

            _001OnAfterEnterZoomed();

            auto ptopic = create_topic(id_on_after_enter_zoomed);

            route(ptopic);

         }
         else if (layout().design().display() == e_display_full_screen)
         {

            _001OnAfterEnterFullScreen();

            auto ptopic = create_topic(id_on_after_enter_full_screen);

            route(ptopic);

         }

      }

   }


   bool interaction::_001OnBeforeExitIconic()
   {

      return ::user::primitive::_001OnBeforeExitIconic();

   }


   bool interaction::_001OnBeforeExitNormal()
   {

      return ::user::primitive::_001OnBeforeExitNormal();

   }


   bool interaction::_001OnBeforeExitZoomed()
   {

      return ::user::primitive::_001OnBeforeExitZoomed();

   }


   bool interaction::_001OnBeforeExitFullScreen()
   {

      return ::user::primitive::_001OnBeforeExitFullScreen();

   }


   bool interaction::_001OnBeforeExitAppearance()
   {

      if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
      {

         auto edisplayCurrent = layout().design().display();

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

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      if (layout().normal().m_bProdevian)
      {

         if (!is_prodevian())
         {

            set_prodevian();

         }

      }

      m_pprimitiveimpl->_001OnAfterExitIconic();

   }


   void interaction::_001OnAfterExitNormal()
   {

      auto rectangle = layout().window().parent_client_rectangle();

      layout().normal() = layout().window();

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

      m_pprimitiveimpl->_001OnAfterExitNormal();

   }


   void interaction::_001OnAfterExitZoomed()
   {

      auto rectangle = layout().window().parent_client_rectangle();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

      m_pprimitiveimpl->_001OnAfterExitZoomed();

   }


   void interaction::_001OnAfterExitFullScreen()
   {

      auto rectangle = layout().window().parent_client_rectangle();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->_001OnAfterExitFullScreen();

   }


   void interaction::_001OnAfterExitAppearance()
   {

      if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
      {

         auto edisplay = layout().sketch().display();

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

   //   if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
   //   {

   //      auto edisplaySketch = layout().sketch().display();

   //      auto edisplayDesign = layout().design().display();

   //      if (edisplaySketch != e_display_iconic && edisplayDesign == e_display_iconic)
   //      {

   //         _001OnExitIconic();

   //      }
   //      else if (edisplaySketch != e_display_zoomed && edisplayDesign == e_display_zoomed)
   //      {

   //         _001OnExitZoomed();

   //      }
   //      else if (
   //         !(edisplaySketch == e_display_restore ||
   //            edisplaySketch == e_display_normal)
   //         &&
   //         (edisplayDesign == e_display_restore
   //            || edisplayDesign == e_display_normal))
   //      {

   //         _001OnExitNormal();

   //      }
   //      else if (layout().sketch().display() != e_display_full_screen && layout().design().display() == e_display_full_screen)
   //      {

   //         _001OnExitFullScreen();

   //      }

   //   }

   //   return true;

   //}


   void interaction::keep_alive(::object* pliveobject)
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
   //      layout().sketch().origin() = point;
   //
   //   }


   //   void interaction::set_size(const ::size_i32 & size)
   //   {
   //
   //      layout().sketch().size() = size;
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


   void interaction::place(const ::rectangle_i32& rectangle, enum_layout elayout)
   {

      bool bOnSetSize = on_set_size(rectangle.size(), elayout);

      bool bOnSetPosition = on_set_position(rectangle.origin(), elayout);

      if (bOnSetSize && bOnSetPosition)
      {

         _synchronous_lock synchronouslock(this->synchronization());

         layout().m_statea[elayout] = rectangle;

      }

   }


   //   void interaction::set_dim(i32 x, i32 y, i32 cx, i32 cy)
   //   {
   //
   //      place(rectangle_i32_dimension(x, y, cx, cy));
   //
   //   }


   interaction& interaction::operator =(const ::rectangle_i32& rectangle)
   {

      place(rectangle);

      return *this;

   }


   void interaction::place_rate_or_size(const ::rectangle_f64& rectangleRateOrSize)
   {

      ::rectangle_i32 rectangle;

      calculate_window_rectangle_in_main_monitor(rectangle, rectangleRateOrSize);

      place(rectangle);

   }


   void interaction::activation(::e_activation eactivation)
   {

      layout().sketch() = eactivation;

   }


   void interaction::display_child(const ::rectangle_i32& rectangle)
   {

      place(rectangle);

      display(e_display_normal);

   }


   ::user::interaction* interaction::best_top_level_parent(::rectangle_i32& rectangle)
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

      auto rectangle = this->client_rectangle(elayout);

      this->client_to_parent(elayout)(rectangle);

      return rectangle;

   }


   ::point_i32    interaction::position(enum_layout elayout) { return parent_client_rectangle(elayout).top_left(); }
   ::size_i32     interaction::size(enum_layout elayout) { return parent_client_rectangle(elayout).size(); }
   ::i32          interaction::top(enum_layout elayout) { return parent_client_rectangle(elayout).top; }
   ::i32          interaction::left(enum_layout elayout) { return parent_client_rectangle(elayout).left; }
   ::i32          interaction::right(enum_layout elayout) { return parent_client_rectangle(elayout).right; }
   ::i32          interaction::bottom(enum_layout elayout) { return parent_client_rectangle(elayout).bottom; }


   void interaction::window_rectangle(::rectangle_i32& rect, enum_layout elayout)
   {

      rect = this->window_rectangle(elayout);

   }


   ::rectangle_i32 interaction::window_rectangle(enum_layout elayout)
   {

      auto rectangle = this->client_rectangle(elayout);

      this->client_to_screen(elayout)(rectangle);

      return rectangle;

   }


   void interaction::design_window_minimize(::e_activation eactivation)
   {

      auto rectangleRequest = this->screen_rect();

      good_iconify(nullptr, rectangleRequest, true, eactivation, layout().sketch().zorder());

   }


   void interaction::design_window_maximize()
   {

      ::rectangle_i32 rectangleRequest = this->screen_rect();

      best_workspace(nullptr, rectangleRequest, true, layout().sketch().activation(), layout().sketch().zorder());

   }


   void interaction::design_window_full_screen(const ::rectangle_i32& rectangleHint)
   {

      ::rectangle_i32 rectangleRequest;

      if (!rectangleHint.is_empty())
      {

         rectangleRequest = rectangleHint;

      }
      else
      {

         rectangleRequest = this->screen_rect();

      }

      best_monitor(nullptr, rectangleRequest, true, layout().sketch().activation(), layout().sketch().zorder());

   }


   void interaction::design_window_normal(::e_display edisplay)
   {

      auto activation = layout().sketch().activation();

      auto zorder = layout().sketch().zorder();

      auto rectangle = layout().sketch().parent_client_rectangle();

      good_restore(nullptr, rectangle, true, layout().sketch().activation(), layout().sketch().zorder(), edisplay);

   }


   void interaction::design_window_dock(::e_display edisplay)
   {

      ASSERT(is_docking_appearance(edisplay));

      if (is_docking_appearance(edisplay))
      {

         auto rectangleRequest = this->screen_rect();

         make_zoneing(nullptr, rectangleRequest, true, &edisplay, layout().sketch().activation(), layout().sketch().zorder());

      }

   }


   void interaction::frame_experience_restore()
   {

      //throw ::interface_only();

      display(e_display_normal);

   }


   ::user::notify_icon* interaction::notify_icon()
   {

      return nullptr;

   }


   void interaction::on_update_notify_icon_menu(::index& iNotifyIconIndex)
   {

   }


   void interaction::on_app_activated()
   {

      //auto estatus = 

      frame_toggle_restore();

      //if(!estatus)
      //{
      //   
      //   return estatus;
      //   
      //}
      //
      //return estatus;

   }


   void interaction::frame_restore()
   {

      if (notify_icon())
      {

         set_tool_window(false);

      }

      if (!is_window_screen_visible())
      {

         frame_experience_restore();

      }
      else
      {

         order_top();

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


   void interaction::frame_toggle_restore()
   {

      bool bWindowVisible = is_window_visible();

      double dOccludedOpaqueRate = _001GetTopLeftWeightedOccludedOpaqueRate();

      bool bIconic = layout().is_iconic();

      if (!bWindowVisible || dOccludedOpaqueRate > 0.025 || bIconic)
      {

         frame_restore();

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


   void interaction::input_client_rectangle(::rectangle_i32& rectangle, enum_layout elayout)
   {

      client_rectangle(rectangle, elayout);

   }


   void interaction::client_rectangle(::rectangle_i32& rectangle, enum_layout elayout)
   {

      const_layout().state(elayout).client_rect(rectangle);

   }


   ::rectangle_i32 interaction::client_rectangle(enum_layout elayout)
   {

      ::rectangle_i32 r;

      client_rectangle(r, elayout);

      return r;

   }


   index interaction::best_monitor(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleSample;

      //auto pwindowing = windowing();

      //auto pdisplay = pwindowing->display();

      if (window() && (eactivation & e_activation_under_mouse_cursor || rectangle.is_null()))
      {

         ::point_i32 pointCursor = window()->get_mouse_cursor_position();

         rectangleSample.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

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

      index iMatchingMonitor = -1;

      if (get_parent() != nullptr)
      {

         get_parent()->client_rectangle(rectangleNew);

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

         INFORMATION("interaction::bestmonitor (" << rectangleNew.left << ", " << rectangleNew.top << ", " << rectangleNew.right << ", " << rectangleNew.bottom << ") activation " << (i32)eactivation);

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


   index interaction::best_workspace(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
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

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_best_monitor(&rectangleNew, rectangleWindow, eactivation, window());

      ::rectangle_i32 rectangleWorkspace;

      pdisplay->get_workspace_rectangle(iMatchingMonitor, rectangleWorkspace);

      if (bSet && (!::is_empty(rectangle) || iMatchingMonitor >= 0))
      {

#if !MOBILE_PLATFORM

         if (iMatchingMonitor >= 0 && rectangleNew.bottom > 0)
         {

            if (rectangleWorkspace.bottom > rectangleNew.bottom - 2)
            {

               rectangleWorkspace.bottom = rectangleNew.bottom - 2;

            }

         }

#endif

         order(zorderParam);

         place(rectangleWorkspace);

         //display(e_display_zoomed, eactivation | e_activation_display_change);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleWorkspace;


      }

      return iMatchingMonitor;

   }


   index interaction::get_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangleParam, ::e_display edisplay)
   {

      if (!is_docking_appearance(edisplay))
      {

         return -1;

      }

      ::rectangle_i32 rectangleWorkspace;

      index iWorkspace = get_best_workspace(&rectangleWorkspace, rectangleParam);

      if (iWorkspace < 0 || rectangleWorkspace.is_empty())
      {

         return -1;

      }

      if (rectangleParam)
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

         prectangle->move_top_to(rectangleWorkspace.top);

         if (::height(*prectangle) < sizeMinimum.cy)
         {

            prectangle->bottom = prectangle->top + sizeMinimum.cy;

         }

      }

      if (edisplay & ::e_display_bottom)
      {

         prectangle->move_bottom_to(rectangleWorkspace.bottom);

         if (::height(*prectangle) < sizeMinimum.cy)
         {

            prectangle->top = prectangle->bottom - sizeMinimum.cy;

         }

      }

      if (edisplay & ::e_display_left)
      {

         prectangle->move_left_to(rectangleWorkspace.left);

         if (::width(*prectangle) < sizeMinimum.cx)
         {

            prectangle->right = prectangle->left + sizeMinimum.cx;

         }

      }

      if (edisplay & ::e_display_right)
      {

         prectangle->move_right_to(rectangleWorkspace.right);

         if (::width(*prectangle) < sizeMinimum.cx)
         {

            prectangle->left = prectangle->right + sizeMinimum.cx;

         }

      }

      return iWorkspace;

   }


   ::e_display interaction::initial_restore_display()
   {

      return e_display_normal;

   }


   ::index interaction::get_preferred_restore(::rectangle_i32& rectWorkspace)
   {

      return -1;

   }


   bool interaction::calculate_window_rectangle_in_main_monitor(::rectangle_i32& rectangle, const ::rectangle_f64& rectangleOptionalRateOrSize)
   {

      ::rectangle_f64 rectangleRate(rectangleOptionalRateOrSize);

      ::rectangle_i32 rectangleMainMonitor;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      ::index iMainMonitor = pdisplay->get_main_monitor(rectangleMainMonitor);

      if (iMainMonitor < 0)
      {

         return false;

      }

      ::rectangle_i32 rectangleWindow;

#if MOBILE_PLATFORM

      // rectangleOptionalRateOrSize is disregarded on mobile platform

      rectangleWindow = rectangleMainMonitor;

#else

      if (rectangleRate.is_empty())
      {

         rectangleRate.set_dimension(100, 100, 800, 400);

      }
      else if (fabs(rectangleRate.left) < 10.0
         && fabs(rectangleRate.right) < 10.0
         && fabs(rectangleRate.bottom) < 10.0
         && fabs(rectangleRate.top) < 10.0)
      {

         rectangleRate *= rectangle_f64(rectangleMainMonitor.width(), rectangleMainMonitor.height(), rectangleMainMonitor.width(), rectangleMainMonitor.height());

      }

      copy(rectangleWindow, rectangleRate);

      rectangleWindow += rectangleMainMonitor.top_left();

#endif

      rectangle = rectangleWindow;

      return true;

   }


   index interaction::calculate_broad_and_compact_restore(::rectangle_i32* prectWorkspace, const ::size_i32& sizeMinParam, const ::rectangle_i32& rectangleHintParam)
   {

      ::rectangle_i32 rectangleHint(rectangleHintParam);

      if (rectangleHint.is_empty())
      {

         rectangleHint = this->screen_rect();

      }

      ::size_i32 sizeMin(sizeMinParam);

      if (sizeMin.is_empty())
      {

         sizeMin = this->get_window_minimum_size();

      }

      ::rectangle_i32 rectangleWorkspace;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingWorkspace = pdisplay->get_best_workspace(&rectangleWorkspace, rectangleHint);

      if (iMatchingWorkspace >= 0)
      {

         m_sizeRestoreBroad = sizeMin.maximum(rectangleWorkspace.size() * 4 / 5);

         m_sizeRestoreCompact = sizeMin.maximum(rectangleWorkspace.size() * 2 / 5);

         if (::is_set(prectWorkspace))
         {

            *prectWorkspace = rectangleWorkspace;

         }

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
   //   m_windowrectangle.reset();
   //   m_windowrectangleStore.reset();

   //}


   index interaction::make_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_display* pedisplay, ::e_activation eactivation, ::zorder zorderParam)
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

      index iMatchingMonitor = get_zoneing(&rectangleNew, rectangleWindow, *pedisplay);

      if (bSet && !is_empty(rectangleNew) && iMatchingMonitor >= 0)
      {

         synchronous_lock slUserMutex(synchronization());

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


   index interaction::get_best_zoneing(::e_display& edisplay, ::rectangle_i32* prectangle, const ::rectangle_i32& rectangleRequest, bool bPreserveSize)
   {

      edisplay = layout().design().display();

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      if (rectangleRequest.is_empty())
      {

         return pdisplay->_get_best_zoneing(&edisplay, prectangle, this->screen_rect(), bPreserveSize);

      }
      else
      {

         return pdisplay->_get_best_zoneing(&edisplay, prectangle, rectangleRequest, bPreserveSize);

      }

   }


   index interaction::get_best_workspace(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation)
   {

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      return pdisplay->get_best_workspace(prectangle, rectangle, eactivation, window());

   }


   index interaction::get_best_monitor(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation)
   {

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      return pdisplay->get_best_monitor(prectangle, rectangle, eactivation, window());

   }


   index interaction::best_zoneing(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_display* pedisplay, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::e_display edisplay;

      if (pedisplay == nullptr)
      {

         pedisplay = &edisplay;

      }

      *pedisplay = layout().design().display();

      ::rectangle_i32 rectangleNew;

      index iMatchingMonitor;

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

         synchronous_lock slUserMutex(synchronization());

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
   index interaction::good_restore(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam, ::e_display edisplay)
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

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_good_restore(&rectangleNew, rectangleWindow, this, edisplay);

      if (bSet)
      {

         {

            //lock_sketch_to_design lockSketchToDesign(this);

            order(zorderParam);

            if (rectangleNew.is_set() && iMatchingMonitor >= 0)
            {

               place(rectangleNew);

               ///set_restored_rectangle(rectangleNew);

               //display(edisplay, eactivation);

               set_display(edisplay);

               set_activation(eactivation);

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

      return iMatchingMonitor;

   }


   index interaction::good_iconify(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
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

      index iMatchingMonitor = pdisplay->get_good_iconify(&rectangleNew, rectangleWindow);

      if (bSet && (!::is_empty(rectangleNew) || iMatchingMonitor >= 0))
      {

         synchronous_lock slUserMutex(synchronization());

         display(e_display_iconic, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   index interaction::good_move(::rectangle_i32* prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation, ::zorder zorderParam)
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

      index iMatchingMonitor = pdisplay->get_good_move(&rectangleNew, rectangleWindow, this);

      if (!is_empty(rectangleNew) || iMatchingMonitor >= 0)
      {

         order(zorderParam);

         place(rectangleNew);

         if (equivalence_sink(layout().sketch().display()) != e_display_normal
            || equivalence_sink(layout().design().display()) != e_display_normal)
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


   atom interaction::SetDlgCtrlId(const atom& atom)
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
   //      if (!m_pprimitiveimpl)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return m_pprimitiveimpl->open_clipboard();
   //
   //   }
   //   
   //   
   //   bool interaction::close_clipboard()
   //   {
   //
   //      if (!m_pprimitiveimpl)
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      return m_pprimitiveimpl->close_clipboard();
   //
   //   }
   //
   //
   //#endif


   void interaction::get_rect_normal(::rectangle_i32* prectangle)
   {

      //return 

      m_pprimitiveimpl->get_rect_normal(prectangle);

   }


   scroll_bar* interaction::get_horizontal_scroll_bar()
   {

      return nullptr;

   }


   scroll_bar* interaction::get_vertical_scroll_bar()
   {

      return nullptr;

   }


   scroll_data* interaction::get_horizontal_scroll_data()
   {

      return nullptr;

   }


   scroll_data* interaction::get_vertical_scroll_data()
   {

      return nullptr;

   }


   void interaction::offset_context_offset(::draw2d::graphics_pointer& pgraphics, int x, int y)
   {

      auto pointOffset = get_context_offset();

      set_context_offset(pgraphics, pointOffset.x() + x, pointOffset.y() + y);

   }


   void interaction::offset_context_offset_x(::draw2d::graphics_pointer& pgraphics, int x)
   {

      offset_context_offset(pgraphics, x, 0);

   }


   void interaction::offset_context_offset_y(::draw2d::graphics_pointer& pgraphics, int y)
   {

      offset_context_offset(pgraphics, 0, y);

   }


   void interaction::set_context_offset(::draw2d::graphics_pointer& pgraphics, int x, int y)
   {

      ::point_i32 pointOffset(x, y);

      //if (pointOffset == (m_pointScroll + m_pointDragScroll))
      if (pointOffset == m_pointScroll)
      {

         return;

      }

      if (!validate_context_offset(pointOffset))
      {

         return;

      }

      m_pointScroll = pointOffset;

      on_change_context_offset(pgraphics);

   }


   bool interaction::validate_context_offset(point_i32& point)
   {

      if (point == m_pointScroll)
      {

         return false;

      }

      return true;

   }


   void interaction::set_context_offset_x(::draw2d::graphics_pointer& pgraphics, int x)
   {

      set_context_offset(pgraphics, x, (::i32)get_context_offset().y());

   }


   void interaction::set_context_offset_y(::draw2d::graphics_pointer& pgraphics, int y)
   {

      set_context_offset(pgraphics, (::i32)get_context_offset().x(), y);

   }


   void interaction::on_change_context_offset(::draw2d::graphics_pointer& pgraphics)
   {

      //set_need_redraw();

      set_reposition();

   }


   point_i32 interaction::get_context_offset()
   {

      //::point_i32 point = m_pointScroll + m_pointDragScroll;
      ::point_i32 point = m_pointScroll;

      return point;

   }


   size_f64 interaction::get_total_size()
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      return rectangleClient.size();

   }

   void interaction::set_total_size(const ::size_f64& size)
   {

      throw ::interface_only();

   }


   void interaction::set_page_size(const ::size_f64& size)
   {

      throw ::interface_only();

   }


   void interaction::on_change_impact_size(::draw2d::graphics_pointer& pgraphics)
   {

   }


   size_f64 interaction::get_page_size()
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      return rectangleClient.size();

   }


   point_i32 interaction::get_ascendant_context_offset()
   {

      ::pointer<::user::interaction>puser = get_parent();

      point_i32 point;

      while (puser.is_set())
      {

         point += puser->get_context_offset();

         puser = puser->get_parent();

      }

      return point;

   }


   void interaction::get_margin_rect(::rectangle_i32* prectMargin)
   {

      prectMargin->left = 0;

      prectMargin->top = 0;

      prectMargin->right = 0;

      prectMargin->bottom = 0;


   }

   int interaction::get_final_x_scroll_bar_width()
   {

      return 0;

   }

   int interaction::get_final_y_scroll_bar_width()
   {

      return 0;

   }


   bool interaction::is_system_message_window()
   {

      return false;

   }


   point_i32 interaction::get_parent_context_offset()
   {

      ::user::interaction* puser = get_parent();

      if (puser == nullptr)
      {

         return ::point_i32();

      }

      ::point_i32 pointParentAccumulated;

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

   void interaction::on_message_show_window(::message::message* pmessage)
   {

      ::pointer<::message::show_window>pshowwindow(pmessage);

      bool bShowWindow = pshowwindow->m_bShow;

      if (!layout().design().is_screen_visible()
         || layout().design().m_edisplay == e_display_iconic)
      {

         for (auto& pmenu : m_menua)
         {

            pmenu->hide();

            pmenu->set_need_redraw();

            pmenu->post_redraw();

         }

      }
      else
      {

         for (auto& pmenu : m_menua)
         {

            pmenu->display();

            pmenu->set_need_redraw();

            pmenu->post_redraw();

         }

      }

      //      string strType = __type_name(this);
      //      
      //      if(strType.contains("main_frame"))
      //      {
      //      
      //         output_debug_string("main_frame interaction::on_message_show_window\n");
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

            //synchronous_lock synchronouslock(mutex_children());

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

            //      for (index i = 0; i < uiptra.get_size(); i++)
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




   ::graphics::graphics* interaction::get_window_graphics()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->get_window_graphics();

   }

   
   ::draw2d::graphics_pointer interaction::get_internal_draw2d_graphics()
   {

      if (::is_null(m_pinteractionimpl))
      {

         return nullptr;

      }
    
      auto & pdraw2dgraphics = m_pinteractionimpl->m_pdraw2dgraphics;

      defer_graphics(pdraw2dgraphics);

      return pdraw2dgraphics;

   }


   bool interaction::is_composite()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return true; // optimistic response, assume always true alpha blendable

      }

      return m_pprimitiveimpl->is_composite();

   }


   size_i32 interaction::get_window_minimum_size()
   {

      return nullptr;

   }


   ::size_i32 interaction::get_window_normal_stored_size()
   {

      return this->size();

   }


   // up down target

   //UpDownTarget::UpDownTarget()
   //{
   //   m_eupdowntargettype = type_normal_frame;
   //}

   void interaction::UpDownTargetAttach(::user::interaction* pupdown)
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


   void interaction::UpDownTargetDetach(::user::interaction* pupdown)
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


   bool interaction::OnUpDownTargetAttach(::user::interaction* pupdown)
   {

      return false;

   }


   bool interaction::OnUpDownTargetDetach(::user::interaction* pupdown)
   {

      return false;

   }


   void interaction::keyboard_focus_OnKeyDown(::message::message* pmessage)
   {

      auto pkey = pmessage->m_union.m_pkey;

      if (pkey->m_ekey == ::user::e_key_tab)
      {

         auto ptopic = create_topic(::id_tab_key);

         ptopic->m_puserelement = dynamic_cast <::user::interaction*> (this);
         ptopic->m_actioncontext = ::e_source_user;

         route(ptopic);

      }

   }



   bool interaction::get_child(::pointer<::user::interaction>& pinteraction)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->get_child(pinteraction);

   }


   bool interaction::rget_child(::pointer<::user::interaction>& pinteraction)
   {

      //synchronous_lock synchronouslock(this->synchronization());

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


   //::user::primitive * interaction::get_keyboard_focus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->get_keyboard_focus();

   //}


   //void interaction::set_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   auto puserinteractionHost = get_host_window();

   //   if (this == puserinteractionHost)
   //   {

   //      return pprimitive->set_keyboard_focus();

   //   }
   //   else
   //   {

   //      return puserinteractionHost->set_keyboard_focus(pprimitive);

   //   }

   //}


   //void interaction::erase_keyboard_focus(::user::primitive * pprimitive)
   //{

   //   auto puserinteractionHost = get_host_window();

   //   if (this == puserinteractionHost)
   //   {

   //      return m_pprimitiveimpl->erase_keyboard_focus(pprimitive);

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


   void interaction::clear_keyboard_focus(::user::element* pelementGainingFocusIfAny)
   {

      auto pwindowThis = window();

      if (::is_null(pwindowThis))
      {

         return;

      }

      auto pprimitiveimpl = pwindowThis->m_puserinteractionimpl;

      if (::is_null(pprimitiveimpl))
      {

         return;

      }

      pprimitiveimpl->m_puserinteractionToKillKeyboardFocus = pprimitiveimpl->m_puserinteractionKeyboardFocus;


      //      if (pwindowThis->has_keyboard_focus())
      //      {
      //
      //         pprimitiveimpl->m_puserinteractionToKillKeyboardFocus->clear_keyboard_focus(pelementGainingFocusIfAny);
      //
      //      }
      //      else
      //      {

      pprimitiveimpl->on_final_kill_keyboard_focus();

      //}

//      auto puserinteractionHost = get_host_window();
//
//      if (this == puserinteractionHost)
//      {
//
//         ::user::primitive_impl* pprimitiveimplGainingFocusIfAny = nullptr;
//
//         if (pelementGainingFocusIfAny)
//         {
//
//            pprimitiveimplGainingFocusIfAny = pelementGainingFocusIfAny->get_primitive_impl();
//
//         }
//
//         return m_pprimitiveimpl->clear_keyboard_focus(pprimitiveimplGainingFocusIfAny);
//
//      }
//      else
//      {
//
//         return puserinteractionHost->clear_keyboard_focus(pelementGainingFocusIfAny);
//
//      }

   }


   bool interaction::is_ascendant_of(::user::element* puiDescendantCandidate, bool bIncludeSelf)
   {

      if (::is_null(puiDescendantCandidate))
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of(::user::element* puiAscendantCandidate, bool bIncludeSelf)
   {

      const ::user::interaction* pinteraction = bIncludeSelf ? this : get_parent();

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


   bool interaction::is_ascendant_or_owner_of(::user::element* puiDescendantCandidate, bool bIncludeSelf)
   {

      if (puiDescendantCandidate == nullptr)
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of_or_owned_by(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of_or_owned_by(::user::element* puiAscendantCandidate, bool bIncludeSelf)
   {

      ::user::interaction* pinteraction = bIncludeSelf ? this : get_parent_or_owner();

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

      auto pwindowimpl = get_window_impl();

      return pwindowimpl->m_puiLastLButtonDown == this;

   }


   void interaction::set_current_item(::item* pitem, const ::action_context& context)
   {

      if (::is_same_item(m_pitemCurrent, pitem))
      {

         return;

      }

      m_pitemCurrent = pitem;

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


   item_pointer interaction::current_item()
   {

      return m_pitemCurrent;

   }


   item_pointer interaction::hover_item()
   {

      return m_pitemHover;

   }


   void interaction::show_tooltip(const ::string& str, bool bError)
   {

      //
      //
      //      if (m_ptooltip.is_null())
      //      {
      //
      //         m_ptooltip = __new(tooltip(this));
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


   void interaction::handle(::topic* ptopic, ::context* pcontext)
   {

      //auto pevent = pmessage->m_lparam.cast < ::user::control_event >();

      //handle(ptopic, pcontext);

      if (ptopic)
      {

         if (ptopic->m_atom == ID_REDRAW || ptopic->m_atom == m_atom)
         {

            if (m_puserinteraction->m_ewindowflag & ::e_window_flag_window_created)
            {

               set_need_redraw();

               post_redraw();

            }

         }
         else if (ptopic->m_atom == id_user_style_change)
         {

            if (m_puserinteraction->m_ewindowflag & ::e_window_flag_window_created)
            {

               set_need_redraw();

               post_redraw();

            }

         }

      }

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

      //rectangleWindow.offset(0, -sizeTooltip.cy);

      //if (rectangleWindow.top < rectangleMonitor.top)
      //{

      //   rectangleWindow.move_top_to(rectangleThisWindow.bottom);

      //}

      //if (rectangleWindow.right > rectangleMonitor.right)
      //{

      //   rectangleWindow.move_left_to(rectangleMonitor.right - sizeTooltip.cx - rectangleThisWindow.height());

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


   bool interaction::has_pending_graphical_update()
   {

      if (has_prodevian())
      {

         return true;

      }

      //#ifdef APPLE_IOS
      //
      //      {
      //
      //         synchronous_lock synchronouslock(this->synchronization());
      //
      //         for (index i = 0; i < m_uiptraChild.get_size(); i++)
      //         {
      //
      //            ::user::interaction * pinteraction = m_uiptraChild[i];
      //
      //            if (pinteraction)
      //            {
      //               synchronouslock.unlock();
      //
      //
      //               if (pinteraction->has_pending_graphical_update())
      //               {
      //
      //                  return true;
      //
      //               }
      //
      //               synchronouslock.lock();
      //
      //            }
      //
      //
      //         }
      //
      //      }
      //
      //#endif

      if (is_window_visible())
      {

         if (m_bRedrawOnVisible)
         {

            return true;

         }

      }

      if (!m_pprimitiveimpl)
      {

         return false;

      }

      if (m_pprimitiveimpl->has_pending_graphical_update())
      {

         return true;

      }

      return false;

   }


   void interaction::enable_transparent_mouse_events(bool bEnable)
   {

      //#ifdef WINDOWS

      ::user::interaction* puiTop = get_wnd();

      if (puiTop == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(puiTop->synchronization());

      ::pointer<::user::interaction_impl>pprimitiveimpl = puiTop->m_pprimitiveimpl;

      if (pprimitiveimpl.is_null())
      {

         //return false;

         throw ::exception(error_null_pointer);

      }

      if (is_different(pprimitiveimpl->m_bTransparentMouseEvents, bEnable))
      {

         pprimitiveimpl->m_bTransparentMouseEvents = bEnable;

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


   void interaction::redraw_add(::particle* pparticle)
   {

      get_wnd()->m_pprimitiveimpl->redraw_add(pparticle);

   }


   void interaction::redraw_erase(::particle* pparticle)
   {

      get_wnd()->m_pprimitiveimpl->redraw_erase(pparticle);

   }


   bool interaction::has_redraw()
   {

      return get_wnd()->m_pprimitiveimpl->has_redraw();

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

   //         //   output_debug_string("void sending :: defer_notify_mouse_move");

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

   //               auto pmouse = __new(message::mouse);

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

      start_destroying_window();

      ::user::primitive::destruct();

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

      ::user::primitive::on_after_graphical_update();

      if (m_pprimitiveimpl.is_set())
      {

         m_pprimitiveimpl->on_after_graphical_update();

      }

   }


   void interaction::_001OnDeiconify(::e_display edisplayPrevious)
   {

      if (edisplayPrevious == ::e_display_iconic)
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


   bool interaction::on_edit_delete(const ::action_context& actioncontext)
   {

      //return ::success_none;

      return true;

   }


   bool interaction::on_click_generation(::item* pitem)
   {

      auto pappearance = get_appearance();

      if (pappearance)
      {

         if (pappearance->call_click())
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


   bool interaction::on_click(::item* pitem)
   {

      if (::is_set(pitem))
      {

         if (pitem->m_eelement == ::e_element_close_button
            || pitem->m_eelement == ::e_element_close_icon)
         {

            post_message(MESSAGE_CLOSE);

            return true;

         }
         else if (pitem->m_eelement == ::e_element_switch_button
            || pitem->m_eelement == ::e_element_switch_icon)
         {

            post_message(e_message_switch);

            return true;

         }
         else if (pitem->m_eelement == ::e_element_maximize_button
            || pitem->m_eelement == ::e_element_maximize_icon)
         {

            auto edisplay = layout().sketch().display();

            if (edisplay == e_display_zoomed)
            {

               display(e_display_normal);

            }
            else
            {

               display(e_display_zoomed);

            }

            return true;

         }
         else if (pitem->m_eelement == ::e_element_minimize_button
            || pitem->m_eelement == ::e_element_minimize_icon)
         {

            display(e_display_iconic);

            return true;

         }

      }

      return false;

   }


   bool interaction::on_right_click_generation(::item* pitem)
   {

      return on_right_click(pitem);

   }


   bool interaction::on_right_click(::item* pitem)
   {

      return false;

   }


   ::size_f64 interaction::get_size()
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      return rectangleWindow.size();

   }


   ::size_f64 interaction::get_client_size()
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      return rectangleClient.size();

   }


   int interaction::width()
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      return rectangleWindow.width();

   }


   int interaction::height()
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      return rectangleWindow.height();

   }


   int interaction::client_width()
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      return rectangleClient.width();

   }


   int interaction::client_height()
   {

      ::rectangle_i32 rectangleClient;

      client_rectangle(rectangleClient);

      return rectangleClient.height();

   }


   void interaction::resize_to_fit(::draw2d::graphics_pointer& pgraphics)
   {

      // this default implementation doesn't need to be called by derived
      // classes and it has the side effect of warning at debug output log
      // the default resize_to_fit implementation is being called.

      ::output_debug_string("default resize_to_fit doesn't do anything\n");


   }


   void interaction::wait_redraw()
   {

      while (has_pending_redraw_flags())
      {

         acmesystem()->do_events();

         sleep(5_ms);

      }


   }


   bool interaction::has_pending_redraw_flags()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return false;

      }

      return m_pprimitiveimpl->has_pending_redraw_flags();

   }



   void interaction::set_stock_icon(enum_stock_icon estockicon)
   {

      throw ::interface_only();

   }


   enum_stock_icon interaction::get_stock_icon()
   {

      return e_stock_icon_none;

   }


   void interaction::set_bitmap_source(const string& strBitmapSource)
   {

      if (!m_pprimitiveimpl)
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      //auto estatus = 

      m_pprimitiveimpl->set_bitmap_source(strBitmapSource);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void interaction::clear_bitmap_source()
   {

      if (!m_pprimitiveimpl)
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      //auto estatus = 

      m_pprimitiveimpl->clear_bitmap_source();

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


   bool interaction::scroll_bar_get_client_rect(::rectangle_i32& rectangle)
   {

      client_rectangle(rectangle);

      rectangle.right += get_final_y_scroll_bar_width();

      rectangle.bottom += get_final_x_scroll_bar_width();

      return true;

   }


   void interaction::on_calc_size(calc_size* psize)
   {

      ::rectangle_i32 rectangleWindow;

      window_rectangle(rectangleWindow);

      psize->m_size = rectangleWindow.size();

   }


   enum_control_type interaction::get_control_type() const
   {

      return m_econtroltype;

   }


   void interaction::show_software_keyboard(::user::element* pelement)
   {

      if (get_host_window() == this)
      {

         if (m_pprimitiveimpl.is_null())
         {

            throw ::exception(error_null_pointer);

         }

         return m_pprimitiveimpl->show_software_keyboard(pelement);

      }
      else
      {

         auto pwindow = get_host_window();

         if (::is_null(pwindow))
         {

            throw ::exception(error_null_pointer);

         }

         return pwindow->show_software_keyboard(pelement);

      }

   }


   void interaction::hide_software_keyboard(::user::element* pelement)
   {

      if (get_host_window() == this)
      {

         if (m_pprimitiveimpl.is_null())
         {

            throw ::exception(error_null_pointer);

         }

         return m_pprimitiveimpl->hide_software_keyboard(pelement);

      }
      else
      {

         auto pwindow = get_host_window();

         if (::is_null(pwindow))
         {

            throw ::exception(error_null_pointer);

         }

         return pwindow->hide_software_keyboard(pelement);

      }

   }


   //   void interaction::post_procedure(const ::procedure & procedure)
   //   {
   //
   //      if (!::is_set(m_pthreadUserInteraction))
   //      {
   //
   //         throw ::exception(error_null_pointer);
   //
   //      }
   //
   //      m_pthreadUserInteraction->post_procedure(procedure);
   //
   //   }

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
   //      ::thread * pthread = get_wnd() == nullptr ? (::thread *) nullptr : get_wnd()->m_pthreadUserInteraction.m_p;
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


   void interaction::prodevian_redraw(bool bUpdateBuffer)
   {

      auto type = __object_type(*this);

      //      if (type.name_contains("list_box"))
      //      {
      //
      //         output_debug_string("prodevian_redraw list_box");
      //
      //      }

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->prodevian_redraw(bUpdateBuffer);

   }



   void interaction::prodevian_stop()
   {

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->prodevian_stop();

   }


   //   void interaction::install_click_default_mouse_handling(::channel* pchannel)
   //   {
   //
   //      m_bClickDefaultMouseHandling = true;
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
   //      m_bHoverDefaultMouseHandling = true;
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


   void interaction::on_message_left_button_down(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();

      ::output_debug_string("interaction::on_message_left_button_down " + ::string(pszType));

      if (!is_window_enabled())
      {

         return;

      }

      auto psession = get_session();

      try
      {

         if (keyboard_focus_is_focusable())
         {

            set_keyboard_focus();

            {

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

      if ((m_bEnableHorizontalBarDragScroll && _001HasHorizontalBarDragScrolling())
         || (m_bEnableVerticalBarDragScroll && _001HasVerticalBarDragScrolling()))
      {

         m_pointBarDragScrollLeftButtonDown = pmouse->m_point;

         m_bBarDragScrollLeftButtonDown = true;

         m_pointBarDragScrollStart = m_pointBarDragScroll;

         set_mouse_capture();

      }

      auto pitemLButtonDown = update_hover(pmouse, e_zorder_front);

      if (drag_on_button_down(pitemLButtonDown))
      {

         return;

      }

      //if(m_pdragmove && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_eelement == e_element_client)
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
      //else if (m_pdragsize && ::is_set(m_pitemLButtonDown) && m_pitemLButtonDown->m_eelement == e_element_drag_size)
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

      auto puserinteractionimplHost = get_window_impl();

      if (m_bClickDefaultMouseHandling || m_bHoverDefaultMouseHandling)
      {

         if (::is_item_set(pitemLButtonDown))
         {

            //auto psession = get_session();

            puserinteractionimplHost->m_puiLastLButtonDown = this;

            puserinteractionimplHost->m_pitemLButtonDown = pitemLButtonDown;

            //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
            //{

               //set_mouse_capture();

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

            if (m_bClickDefaultMouseHandling)
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

      {

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            ::point_i32 pointClient;

            pointClient = pmouse->m_point;

            screen_to_client()(pointClient);

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

      pitemLButtonDown = update_hover(pmouse, e_zorder_back);

      if (drag_on_button_down(pitemLButtonDown))
      {

         return;

      }

      if (m_bClickDefaultMouseHandling || m_bHoverDefaultMouseHandling)
      {

         if (::is_item_set(pitemLButtonDown))
         {

            puserinteractionimplHost->m_puiLastLButtonDown = this;

            puserinteractionimplHost->m_pitemLButtonDown = pitemLButtonDown;

            track_mouse_leave();

            if (m_bClickDefaultMouseHandling)
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

   }


   void interaction::on_message_left_button_up(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();

      ::output_debug_string("interaction::on_message_left_button_up " + ::string(pszType));

      if (!is_window_enabled())
      {

         return;

      }

      if (m_bEnableHorizontalBarDragScroll || m_bEnableVerticalBarDragScroll)
      {

         //         m_pointDragScrollLeftButtonDown = pmouse->m_point;

         m_bBarDragScrollLeftButtonDown = false;

         release_mouse_capture();

      }

      //if (m_bHorizontalDragScrollingActive)
      //{

      //   pmouse->m_bRet = true;

      //   pmouse->m_lresult = 1;

      //   m_bHorizontalDragScrollingActive = false;

      //   return;

      //}

      if (drag_on_button_up(pmouse))
      {

         return;

      }

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

      if (m_bClickDefaultMouseHandling || m_bHoverDefaultMouseHandling)
      {

         //if(m_bSimpleUIDefaultMouseHandlingMouseCaptureOnLeftButtonDown)
         //{

         if (has_mouse_capture())
         {

            auto pwindowing = windowing();

            pwindowing->release_mouse_capture();

         }

         //}

         auto pwindowimpl = get_window_impl();

         if (m_bClickDefaultMouseHandling)
         {

            auto pitemLeftButtonUp = hit_test(pmouse, e_zorder_any);

            bool bSameUserInteractionAsMouseDown = pwindowimpl->m_puiLastLButtonDown == this;

            bool bSameItemAsMouseDown = ::is_same_item(pwindowimpl->m_pitemLButtonDown, pitemLeftButtonUp);

            //TRACE("interaction::on_message_left_button_up item=" << (int)pitemLeftButtonUp->m_iItem<<", SameUserInteractionAsMsDwn="<< (int) bSameUserInteractionAsMouseDown<<", SameItemAsMsDwn=" << (int) bSameItemAsMouseDown);

            if (::is_set(pwindowimpl->m_pitemLButtonDown) && bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
            {

               pmessage->m_bRet = on_click_generation(pwindowimpl->m_pitemLButtonDown);

               INFORMATION("interaction::on_message_left_button_up on_click_generation ret=" << (int)pmessage->m_bRet);

               if (pmessage->m_bRet)
               {

                  pmouse->m_lresult = 1;

               }
               else
               {

                  ::atom atom;

                  if (pwindowimpl->m_pitemLButtonDown->m_atom.is_empty())
                  {

                     atom = translate_property_id(m_atom);

                  }
                  else
                  {

                     atom = translate_property_id(pwindowimpl->m_pitemLButtonDown->m_atom);

                  }

                  if (has_handler())
                  {

                     auto ptopic = create_topic(id_click);

                     ptopic->m_puserelement = this;

                     ptopic->m_pitem = pwindowimpl->m_pitemLButtonDown;

                     ptopic->m_actioncontext.m_pmessage = pmouse;

                     ptopic->m_actioncontext.add(::e_source_user);

                     route(ptopic);

                     INFORMATION("interaction::on_message_left_button_up route_btn_clked=" << (int)ptopic->m_bRet);

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

                     TRACE("interaction::on_message_left_button_up route_cmd_msg=" << (int)command.m_bRet);

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

         set_need_redraw();

         post_redraw();

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         pointClient = pmouse->m_point;
         
         screen_to_client()(pointClient);

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (pappearance->on_button_up(e_key_left_button, pointClient, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

   }


   void interaction::on_message_left_button_double_click(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();

      ::output_debug_string("interaction::on_message_left_button_double_click" + ::string(pszType));

      if (!is_window_enabled())
      {

         return;

      }

      if (pmouse->previous())
      {

         return;

      }


      if (has_mouse_capture())
      {

         auto pwindowing = windowing();

         pwindowing->release_mouse_capture();

      }

      auto pwindowimpl = get_window_impl();

      auto pitemLeftButtonDoubleClick = hit_test(pmouse, e_zorder_front);

      bool bSameUserInteractionAsMouseDown = pwindowimpl->m_puiLastLButtonDown == this;

      bool bSameItemAsMouseDown = ::is_same_item(pwindowimpl->m_pitemLButtonDown, pitemLeftButtonDoubleClick);

      if (::is_set(pwindowimpl->m_pitemLButtonDown) && bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
      {

         //psession->m_puiLastLButtonDown = nullptr;

         pmessage->m_bRet = on_click_generation(pwindowimpl->m_pitemLButtonDown);

         INFORMATION("interaction::on_message_left_button_up on_click_generation ret=" << (int)pmessage->m_bRet);

         if (pmessage->m_bRet)
         {

            pmouse->m_lresult = 1;

         }
         else
         {

            ::atom atom;

            if (pwindowimpl->m_pitemLButtonDown->m_atom.is_empty())
            {

               atom = translate_property_id(m_atom);

            }
            else
            {

               atom = translate_property_id(pwindowimpl->m_pitemLButtonDown->m_atom);

            }

            if (has_handler())
            {

               auto ptopic = create_topic(id_left_button_double_click);

               ptopic->m_puserelement = this;

               ptopic->m_pitem = pwindowimpl->m_pitemLButtonDown;

               ptopic->m_actioncontext.m_pmessage = pmouse;

               ptopic->m_actioncontext.add(::e_source_user);

               route(ptopic);

               INFORMATION("interaction::on_message_left_button_up route_btn_clked=" << (int)ptopic->m_bRet);

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

               TRACE("interaction::on_message_left_button_up route_cmd_msg=" << (int)command.m_bRet);

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

         ::point_i32 pointClient;

         pointClient = pmouse->m_point;
         
         screen_to_client()(pointClient);

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         bool bDoubleClick = true;

         if (pappearance->on_button_down(e_key_left_button, pointClient, ekeyModifiers, bDoubleClick))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

   }


   void interaction::on_message_right_button_down(::message::message* pmessage)
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

            ::point_i32 pointClient;

            pointClient = pmouse->m_point;
            
            screen_to_client()(pointClient);

            auto psession = m_puserinteraction->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            bool bDoubleClick = false;

            if (pappearance->on_button_down(e_key_right_button, pointClient, ekeyModifiers, true))
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      auto pcontextmenu = __new(::message::context_menu);

      pcontextmenu->m_oswindow = oswindow();
      pcontextmenu->m_pwindow = window();
      pcontextmenu->m_atom = e_message_context_menu;
      pcontextmenu->m_pointMessage = pmouse->m_point;

      //;; pcontextmenu->m_wpar
      //pcontextmenu->set(oswindow(), window(), e_message_context_menu, (wparam)(iptr)oswindow(), pmouse->m_point.lparam());

      message_handler(pcontextmenu);

   }


   void interaction::on_message_right_button_up(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      if (!is_window_enabled())
      {

         return;

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         pointClient = pmouse->m_point;
         
         screen_to_client()(pointClient);

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (pappearance->on_button_up(e_key_right_button, pointClient, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }



   }


#ifdef MOUSE_MIDDLE_BUTTON_MESSAGE_HANDLING_DEBUG


   void interaction::on_message_middle_button_down(::message::message* pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      pmessage->previous();

      //if (m_bClickDefaultMouseHandling)
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


   void interaction::on_message_middle_button_up(::message::message* pmessage)
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


   void interaction::on_message_mouse_move(::message::message* pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      auto pmouse = pmessage->m_union.m_pmouse;

      if (m_bBarDragScrollLeftButtonDown)
      {

         if (m_bEnableHorizontalBarDragScroll)
         {

            m_bHorizontalBarDragScrollingActive = true;

            int iOffset = m_pointBarDragScrollLeftButtonDown.x() - pmouse->m_point.x();

            auto iHorizontalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.x() + iOffset, 0, m_pointBarDragScrollMax.x());

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

            m_bVerticalBarDragScrollingActive = true;

            int iOffset = m_pointBarDragScrollLeftButtonDown.y() - pmouse->m_point.y();

            auto iVerticalBarDragScroll = minimum_maximum(m_pointBarDragScrollStart.y() + iOffset, 0, m_pointBarDragScrollMax.y());

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

         //synchronous_lock synchronouslock(this->synchronization());

         pmouse->m_pcursor = get_mouse_cursor();

         if (drag_on_mouse_move(pmouse))
         {

            pmessage->m_bRet = true;

            return;

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

      //if (m_bHoverDefaultMouseHandling)
      {
         auto type = __object_type(*this);

         if (type.name_contains("button"))
         {

            //output_debug_string("button");

         }

         //bool bAvoidRedraw = !m_bHoverDefaultMouseHandling;

         update_hover(pmouse, e_zorder_any);

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
//               //   auto psession = m_puserinteraction->get_session();
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

            ::point_i32 pointClient;

            pointClient = pmouse->m_point;
            
            screen_to_client()(pointClient);

            bool bRet;

            auto psession = m_puserinteraction->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            bool bDown = pmouse->m_ebuttonstate & e_button_state_left;
            /*{

               bRet = pappearance->on_mouse_drag(pointClient, ekeyModifiers);

            }
            else
            {*/

            bRet = pappearance->on_mouse_move(pointClient, bDown, ekeyModifiers);

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


   void interaction::on_message_mouse_wheel(::message::message* pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      ::pointer<::message::mouse_wheel>pwheel = pmessage;

      double y = pwheel->m_Δ / 120.0;

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         pointClient = pwheel->m_point;
         
         screen_to_client()(pointClient);

         bool bRet;

         auto psession = m_puserinteraction->get_session();

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


   ::item_pointer interaction::update_hover(::user::mouse* pmouse, e_zorder ezorder)
   {

      auto pitemHitTest = hit_test(pmouse, ezorder);

      drag_on_mouse_hover(pitemHitTest);

      ///bool bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

      if (!::is_item_equivalent(pitemHitTest, m_pitemHover))
      {

         auto pitemOldHover = m_pitemHover;

         g_iMouseHoverCount++;

         m_pitemHover = pitemHitTest;

         //m_pitemHOver->m_bAnyHoverChange = true;

         if(::is_item_set(m_pitemHover))
         {

            track_mouse_leave();

         }

         bool bAnyRedraw = false;

         if(::is_item_set(pitemOldHover) && should_redraw_on_hover(pitemOldHover))
         {

            set_need_redraw(pitemOldHover->m_rectangle);

            bAnyRedraw = true;

         }

         if(::is_item_set(pitemHitTest) && should_redraw_on_hover(pitemHitTest))
         {

            set_need_redraw(pitemHitTest->m_rectangle);

            bAnyRedraw = true;

         }

         if(bAnyRedraw)
         {

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

      return pitemHitTest;

   }


   bool interaction::is_mouse_hover() const
   {

      bool bMouseHover = ::is_item_set(m_pitemHover);

      return bMouseHover;

   }


   void interaction::on_message_mouse_leave(::message::message* pmessage)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->on_mouse_leave();

      }

      auto pitemOldHover = m_pitemHover;

      m_pitemHover = nullptr;

      if (::is_item_set(pitemOldHover))
      {

         if(pitemOldHover->m_rectangle.is_set())
         {

            set_need_redraw(pitemOldHover->m_rectangle);

            post_redraw();

         }
         else if (pitemOldHover->m_ppath.is_set())
         {

            set_need_redraw();

            post_redraw();

         }

      }

   }


   ::item_pointer interaction::hit_test(::user::mouse* pmouse, e_zorder ezorder)
   {

      ::point_i32 pointClient;

      pointClient = pmouse->m_point;
      
      screen_to_client()(pointClient);

      auto pitem = hit_test(pointClient, ezorder);

      pitem->m_pointScreen = pmouse->m_point;

      pitem->m_pmouse = pmouse;

      return pitem;

   }


   ::item_pointer interaction::hit_test(const ::point_i32& pointClient, e_zorder ezorder)
   {

      auto pitem = on_hit_test(pointClient, ezorder);

      pitem->m_pointClient = pointClient;

      return pitem;

   }


   ::item_pointer interaction::on_hit_test(const ::point_i32& point, e_zorder ezorder)
   {

      {

         auto pitemHitTest = on_items_hit_test(point, ezorder);

         if (::is_set(pitemHitTest))
         {

            return pitemHitTest;

         }

      }

      {

         auto pitemHitTest = on_default_bottom_right_resize_hit_test(point, ezorder);

         if (::is_set(pitemHitTest))
         {

            return pitemHitTest;

         }

      }


      {

         auto pitemHitTest = on_client_area_hit_test(point, ezorder);

         if (::is_set(pitemHitTest))
         {

            return pitemHitTest;

         }

      }

      auto pitemNone = __new(::item(e_element_none));

      return pitemNone;

   }


   bool interaction::item_contains(::item * pitem, const ::point_i32 & point)
   {

      if (pitem->m_ppath)
      {

         auto ppath = pitem->m_ppath;

         auto pgraphics = get_internal_draw2d_graphics();

         if (ppath->contains(pgraphics, point))
         {

            return true;

         }

      }
      else
      {

         if (pitem->m_rectangle.contains(point))
         {

            return true;

         }

      }

      return false;

   }


   ::item_pointer interaction::on_items_hit_test(const ::point_i32& point, e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pointScroll = point + m_pointScroll + m_pointBarDragScroll;

      for (auto& pitem : *m_pitema)
      {

         if (pitem->is_hidden())
         {

            continue;

         }

         if (!(pitem->m_ezorder & ezorder))
         {

            continue;

         }

         if (item_contains(pitem, pointScroll))
         {

            return pitem;

         }

      }

      return nullptr;

   }


   ::item_pointer interaction::on_default_bottom_right_resize_hit_test(const ::point_i32& point, e_zorder ezorder)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto pointScroll = point + m_pointScroll + m_pointBarDragScroll;

      auto rectangleResize = this->rectangle(::e_element_resize);

      if (rectangleResize.ok() && rectangleResize.contains(point))
      {

         auto pitemHitTest = __new(::item(e_element_resize));

         pitemHitTest->m_rectangle = rectangleResize;

         return pitemHitTest;

      }

      return nullptr;


   }


   ::item_pointer interaction::on_client_area_hit_test(const ::point_i32 & point, e_zorder ezorder)
   {

      if (m_pitemClient)
      {

         if (item_contains(m_pitemClient, point))
         {

            return m_pitemClient;

         }

         return nullptr;

      }

      return on_default_full_client_area_hit_test(point, ezorder);

   }


   ::item_pointer interaction::on_default_full_client_area_hit_test(const ::point_i32& point, e_zorder ezorder)
   {

      if (ezorder & e_zorder_back)
      {

         auto rectangleClient = this->rectangle(::e_element_client);

         if (rectangleClient.ok() && rectangleClient.contains(point))
         {

            auto pitemHitTest = __new(::item(e_element_client));

            pitemHitTest->m_rectangle = rectangleClient;

            return pitemHitTest;

         }

      }

      return nullptr;

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

   //   client_rectangle(item.m_rectangle);

   //   return true;

   //}


   bool interaction::on_action(const ::string& pszId)
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

      return false;

   }


   void interaction::_001OnNcDraw(::draw2d::graphics_pointer& pgraphics)
   {

      auto pparent = get_parent();

      if (::is_null(pparent))
      {

         ::rectangle_i32 rectangleWindow;

         window_rectangle(rectangleWindow, e_layout_design);

         ::rectangle_i32 rectangle(rectangleWindow);

         rectangle.offset(-rectangle.top_left());

         auto pstyle = get_style(pgraphics);

         if (pgraphics->m_pimage->is_ok())
         {

            pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

            if (m_pinteractionimpl->is_composite())
            {

               pgraphics->fill_rectangle(rectangle, argb(0, 0, 0, 0));

            }
            else
            {

               pgraphics->fill_rectangle(rectangle, argb(255, 192, 192, 192));

            }

         }
         else
         {

            if (m_pinteractionimpl->is_composite())
            {

               pgraphics->fill_rectangle(rectangle, argb(0, 0, 0, 0));

            }
            else
            {

               if (pstyle && pstyle->is_dark_mode())
               {

                  pgraphics->fill_rectangle(rectangle, argb(255, 25, 25, 25));

               }
               else
               {

                  pgraphics->fill_rectangle(rectangle, argb(255, 255, 255, 255));

               }

            }

         }

      }

      if (m_flagNonClient.has(e_non_client_background) && !top_level()->frame_is_transparent())
      {

         draw_control_background(pgraphics);

      }

      if (m_flagNonClient.has(e_non_client_focus_rect) && keyboard_focus_is_focusable())
      {

         simple_ui_draw_focus_rect(pgraphics);

      }

   }


   void interaction::_001OnDraw(::draw2d::graphics_pointer& pgraphics)
   {

      if (!pgraphics->m_bDraw)
      {

         return;

      }

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->_001OnDraw(pgraphics);

      }

      //::user::interaction::_001OnDraw(pgraphics);
      if (m_pitema->has_element())
      {

         _001DrawItems(pgraphics);

      }

   }


   void interaction::add_user_item(item* pitem)
   {

      if (is_sandboxed())
      {

         if (pitem->m_atom == ::id_close_app)
         {

            return;

         }
         else if (pitem->m_atom == ::id_maximize)
         {

            return;

         }
         else if (pitem->m_atom == ::id_minimize)
         {

            return;

         }

      }

      m_pitema->add(pitem);

   }


   void interaction::_001DrawItems(::draw2d::graphics_pointer& pgraphics)
   {

      int iCount = 0;

      for (auto& pitem : *m_pitema)
      {

         ::user::e_state estate = ::user::e_state_none;

         if (::is_same_item(pitem, m_pitemHover))
         {

            estate |= ::user::e_state_hover;

         }

         _001DrawItem(pgraphics, pitem, estate);


         iCount++;

         //         if(iCount > 1)
         //         {
         //
         //            output_debug_string("drawing 2nd, 3rd, nth item");
         //
         //         }

      }

   }


   void interaction::_001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item* pitem, const ::user::e_state& estate)
   {

      if (::is_null(pitem))
      {

         return;

      }

      if (pitem->m_eelement == ::e_element_close_icon)
      {

         ::user::draw_close_icon(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_switch_icon)
      {

         ::user::draw_switch_icon(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_maximize_icon)
      {

         ::user::draw_maximize_icon(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_minimize_icon)
      {

         ::user::draw_minimize_icon(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_close_button)
      {

         ::user::draw_close_button(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_maximize_button)
      {

         ::user::draw_maximize_button(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_minimize_button)
      {

         ::user::draw_minimize_button(pgraphics, this, pitem, estate);

      }
      else if (pitem->m_eelement == ::e_element_switch_button)
      {

         ::user::draw_switch_button(pgraphics, this, pitem, estate);

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


   void interaction::edit_on_set_focus(::user::interaction* pinteraction)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return;

      }

      m_pprimitiveimpl->edit_on_set_focus(pinteraction);

   }


   void interaction::edit_on_kill_focus(::user::interaction* pinteraction)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return;

      }

      m_pprimitiveimpl->edit_on_kill_focus(pinteraction);

   }


   void interaction::simple_ui_draw_focus_rect(::draw2d::graphics_pointer& pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      if (pstyle)
      {

         pstyle->simple_ui_draw_focus_rect(this, pgraphics);

      }

   }


   void interaction::get_text_composition_area(::rectangle_i32& rectangle)
   {


   }


   void interaction::edit_on_text(string str)
   {

      _001SetText(str, ::e_source_user);

   }


   void interaction::edit_on_sel(strsize iBeg, strsize iEnd)
   {

      _001SetSel(iBeg, iEnd);

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

      if (!m_pprimitiveimpl)
      {

         return ::user::primitive::_001GetTopLeftWeightedOccludedOpaqueRate();

      }

      return m_pprimitiveimpl->_001GetTopLeftWeightedOccludedOpaqueRate();

   }


   point_i32 interaction::screen_origin(enum_layout elayout)
   {

      auto puserinteraction = this;

      ::point_i32 point;

      while (puserinteraction)
      {

         point += puserinteraction->const_layout().origin(elayout);

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

            break;

         }

         point += puserinteraction->const_layout().origin(elayout);

         puserinteraction = pparent;

      }

      return point;

   }


   ::shift_i32 interaction::screen_to_client(enum_layout elayout)
   {

      return -client_to_screen(elayout);

   }


   ::shift_i32 interaction::client_to_screen(enum_layout elayout)
   {

      return (::shift_i32(screen_origin(elayout)) - ::shift_i32(get_parent_accumulated_scroll(elayout)));

   }


   ::shift_i32 interaction::parent_to_client(enum_layout elayout)
   {

      return -client_to_parent(elayout);

   }


   ::shift_i32 interaction::client_to_parent(enum_layout elayout)
   {

      return ::shift_i32(m_layout.origin(elayout));

   }


   ::shift_i32 interaction::host_to_client(enum_layout elayout)
   {

      return -client_to_host(elayout);

   }


   ::shift_i32 interaction::client_to_host(enum_layout elayout)
   {

      return (::shift_i32(host_origin(elayout)) - ::shift_i32(get_parent_accumulated_scroll(elayout)));

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

   //          puserinteractionParent->client_rectangle(rectangleWindow);

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

   //   return (::index) m_iSubItem;

   //}


   //void interaction::SetEditItem(index iItem)
   //{

   //   m_iEditItem = iItem;

   //}


   //void interaction::SetEditSubItem(index iSubItem)
   //{

   //   m_iSubItem = iSubItem;

   //}


   bool interaction::get_data(::pointer<::user::interaction>puserinteraction, ::payload& payload)
   {

      string str;

      if (m_econtroltype == e_control_type_edit)
      {

         ::pointer<::user::text>pedit = puserinteraction.m_p;

         if (pedit == nullptr)
            return false;

         pedit->_001GetText(str);

      }
      else
      {

         ::pointer<::user::text>ptext = this;

         if (!ptext)
         {

            return false;

         }

         ptext->_001GetText(str);

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


   bool interaction::has_function(enum_control_function econtrolfunction)
   {

      //if (m_pdescriptor.is_null())
      //{

      //   return false;

      //}

      //return ::user::primitive::has_function(econtrolfunction);

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


         auto pprimitiveFocus = puser->get_keyboard_focus(m_pthreadUserInteraction);

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

         if (::is_set(m_pitemHover))
         {

            estate |= e_state_hover;

         }

         auto pprimitiveFocus = puser->get_keyboard_focus(m_pthreadUserInteraction);

         if (pprimitiveFocus == this)
         {

            estate |= e_state_focused;

         }

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

      ::pointer<::user::interaction>puserinteraction = m_puiOther;

      ASSERT(puserinteraction != nullptr);

      //ASSERT_KINDOF(::user::interaction, puserinteraction);

      ::pointer<::user::interaction>pinteraction = puserinteraction->get_child_by_id(m_atomControl);

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

   void control_cmd_ui::SetText(const ::string&)
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

      for (auto& str : straClass)
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

      for (auto& str : stra)
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

               //m_rectanglePadding.left = atoi(strValue);
               //m_rectanglePadding.top = atoi(strValue);
               //m_rectanglePadding.right = atoi(strValue);
               //m_rectanglePadding.bottom = atoi(strValue);


            }
            else if (strKey.case_insensitive_order("cell-padding") == 0)
            {

               //m_iCellPadding = atoi(strValue);

            }


         }

      }

   }


   void interaction::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      if (pcommand->is_handled(this))
      {

         return;

      }

      pcommand->handle(this);

      ::user::primitive::route_command(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      ::pointer<::user::interaction>puserinteractionParent = get_parent();

      if (puserinteractionParent)
      {

         puserinteractionParent->route_command(pcommand, false);

      }
      else
      {

         ::pointer<::apex::context>pcontext = get_context();

         if (pcontext)
         {

            pcontext->route_command(pcommand);

         }

      }

   }


   void interaction::_001OnEnable(::message::message* pmessage)
   {

      ::pointer<::message::enable>penable(pmessage);

      if (m_puiLabel != nullptr)
      {

         m_puiLabel->enable_window(penable->get_enable());

      }

   }


   void interaction::_001OnUpdateEditDelete(::message::message* pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      auto estatus = is_edit_delete_enabled();

      pcommand->enable(estatus == ::success);

      pmessage->m_bRet = true;

   }


   void interaction::_001OnEditDelete(::message::message* pmessage)
   {

      bool bRet = on_edit_delete(pmessage ? pmessage->m_actioncontext : action_context(::e_source_user));

      if (::is_set(pmessage))
      {

         pmessage->m_bRet = bRet;

      }

   }


   bool interaction::get_element_rect(::rectangle_i32& rectangle, enum_element eelement)
   {

      if (eelement == e_element_client)
      {

         if (!m_bEmptyAreaIsClientArea)
         {

            return false;

         }

         client_rectangle(rectangle);

         return true;

      }
      else if (eelement == e_element_resize)
      {

         if (!has_drag(eelement))
         {

            return false;

         }

         client_rectangle(rectangle);

         rectangle.left = maximum(rectangle.left, rectangle.right - 25);
         rectangle.top = maximum(rectangle.top, rectangle.bottom - 25);

         return true;

      }
      else if (eelement == e_element_drop_down)
      {

         if (!has_drag(eelement))
         {

            return false;

         }

         ::rectangle_i32 rectangleClient;

         client_rectangle(rectangleClient);

         //i32 iMargin = rectangleClient.height() / 8;
         i32 iMargin = 0;

         ::rectangle_i32 rectangleDropDown;

         rectangleDropDown = rectangleClient;

         i32 iW = rectangleClient.height() * 5 / 8;

         rectangleDropDown.right -= iMargin;
         rectangleDropDown.bottom -= iMargin;
         rectangleDropDown.top += iMargin;
         rectangleDropDown.left = rectangleDropDown.right - iW;

         rectangle = rectangleDropDown;

         return true;

      }
      else if (eelement == e_element_combo_edit)
      {

         ::rectangle_i32 rectangleClient;

         client_rectangle(rectangleClient);

         ::rectangle_i32 rectangleDropDown;

         get_element_rect(rectangleDropDown, e_element_drop_down);

         ::rectangle_i32 rectangleEdit = rectangleClient;

         rectangleEdit.right = rectangleDropDown.left;

         //::rectangle_i32 rectanglePadding = _001GetRect(::user::rect_edit_padding);

         //rectangleEdit.deflate(rectanglePadding);

         rectangle = rectangleEdit;

         return true;

      }
      else if (eelement == e_element_close_button)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 32;

         rectangle.bottom = rectangle.top + 32;

         return true;

      }
      else if (eelement == e_element_maximize_button)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 64;

         rectangle.right = rectangle.left + 32;

         rectangle.bottom = rectangle.top + 32;

         return true;

      }
      else if (eelement == e_element_minimize_button)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 96;

         rectangle.right = rectangle.left + 32;

         rectangle.bottom = rectangle.top + 32;

         return true;

      }
      else if (eelement == e_element_close_icon)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 48;

         rectangle.bottom = rectangle.top + 48;

         return true;

      }
      else if (eelement == e_element_switch_button)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 48;

         rectangle.top = rectangle.bottom - 48;

         return true;

      }
      else if (eelement == e_element_maximize_icon)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 96;

         rectangle.right = rectangle.left + 48;

         rectangle.bottom = rectangle.top + 48;

         return true;

      }
      else if (eelement == e_element_minimize_icon)
      {

         client_rectangle(rectangle);

         rectangle.left = rectangle.right - 144;

         rectangle.right = rectangle.left + 48;

         rectangle.bottom = rectangle.top + 48;

         return true;

      }

      return false;

   }


   void interaction::get_simple_drop_down_open_arrow_polygon(point_f64_array& pointa)
   {

      ::rectangle_i32 rectangleDropDown;

      get_element_rect(rectangleDropDown, e_element_drop_down);

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


   void interaction::set_ddx_dbflags(const ::scoped_string& scopestr, iptr value)
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

         //         m_type = __type(CSimpleFormListEdit);

         break;

      case e_control_type_combo_box:
      {

         //throw ::exception(todo);

//            m_data.m_pcombobox = memory_new Ex1FormInterfaceComboBox;

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

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->_task_transparent_mouse_event();

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

   //   auto pinteractionimpl = puserinteraction->m_pinteractionimpl;

   //   if (::is_null(pinteractionimpl))
   //   {

   //      return nullptr;

   //   }

   //   return pinteractionimpl->get_oswindow();

   //}


   ::aura::application* interaction::get_app()
   {

      return m_pcontext && m_pcontext->m_pacmeapplication->m_papexapplication ? m_pcontext->m_pacmeapplication->m_pauraapplication : nullptr;

   }


   ::aura::session* interaction::get_session()
   {

      return m_pcontext ? m_pcontext->m_pacmesession->m_paurasession : nullptr;

   }


   //::aura::system * interactionacmesystem()
   //{

   //   return acmesystem() ? acmesystem()->m_paurasystem : nullptr;

   //}


   ::aura::context* interaction::context()
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

      return m_puserinteractionParent && !m_puserinteractionParent->is_window_visible(elayout) ? false : m_layout.state(elayout).is_visible();

   }


   bool interaction::is_window_screen_visible(enum_layout elayout)
   {

      return m_puserinteractionParent && !m_puserinteractionParent->is_window_screen_visible(elayout) ? false : is_screen_visible(m_layout.state(elayout).display());

   }


   bool interaction::has_prodevian() const noexcept
   {

      return m_pinteractionimpl ? m_pinteractionimpl->has_prodevian() : false;

   }


   //void interaction::pick_single_file(
   //   const ::array < ::pair < ::string, ::string > >& filetypes,
   //   const ::function < void(const ::file::path &) >& function,
   //   bool save)
   //{
   //   
   //      acmenode()->pick_single_file(oswindow(),
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
   //   acmenode()->pick_multiple_file(oswindow(),
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
   //   acmenode()->pick_single_folder(oswindow(),
   //                                function);
   //
   //}


   ::user::interaction* message_user_interaction(::user::message* pusermessage)
   {

      auto pimpl = message_interaction_impl(pusermessage);

      return pimpl ? pimpl->m_puserinteraction : nullptr;

   }


} // namespace user



