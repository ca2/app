#include "framework.h"
#include "aura/operating_system.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/user/_user.h"
#endif
//#include "apex/platform/app_core.h"
#include "aura/message.h"
#include "aura/message/timer.h"
#include "acme/constant/timer.h"
#include "acme/id.h"
#include "acme/constant/simple_command.h"
#include "apex/message/simple_command.h"
#include "interaction_thread.h"
#include "acme/operating_system/_user.h"
//#include "interaction_draw2d.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/timer.h"
#include "acme/platform/timer_array.h"
#include "aura/graphics/draw2d/_draw2d.h"
#include "aura/graphics/graphics/_.h"
#include "aura/graphics/graphics/_graphics.h"
#include "acme/primitive/geometry2d/_shape.h"
#include "acme/primitive/geometry2d/_defer_shape.h"


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
#include "aura/operating_system/windows/windowing.h"
#define MESSAGE_WINDOW_PARENT HWND_MESSAGE
#elif defined(_UWP)

//#include "aura/os/universal_windows/_uwp.h"

#endif // _UWP

//#define new AURA_NEW


namespace user
{


   //#ifdef _UWP
   //
   //
   //   Agile<::winrt::Windows::UI::Core::CoreWindow>(*interaction::s_get_os_window)(interaction * pinteraction) = &interaction::get_os_window_default;
   //
   //
   //#endif


   interaction::interaction()
   {

#ifdef REPORT_OFFSETS

      if((offsetof(::user::interaction, m_oswindow) & 4) != 0)
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
      m_bMouseHover = false;
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

      m_durationMouseMoveIgnore = 20_ms;

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

      m_durationMouseMovePeriod = 5_ms;

      m_bOffScreenRender = false;

      m_uiUserInteractionFlags = 0;

      m_eupdown = ::user::interaction::updown_normal_frame;

      //m_playout = NULL;

      m_bWfiUpDownTarget = false;

      m_puserinteraction = this;

      m_dItemHeight = -1;

      m_flagNonClient.add(non_client_background);

      m_flagNonClient.add(non_client_focus_rect);

      m_bMouseHover = false;

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

      m_pointScroll.x = 0;
      m_pointScroll.y = 0;
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

      printf("interaction::common_construct - m_pwindow (0x%" PRI0xPTR ")\n", (uptr) m_pwindow);

      fflush(stdout);

   }


   interaction::~interaction()
   {

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

      display(e_display_restore);

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


   void interaction::set_position(const ::point_i32 & point, enum_layout elayout)
   {

      if (on_set_position(point, elayout))
      {

         m_layout.m_statea[elayout].m_point = point;

      }

   }


   void interaction::set_size(const ::size_i32 & size, enum_layout elayout)
   {

      if (on_set_size(size, elayout))
      {

         m_layout.m_statea[elayout].m_size = size;

      }

   }


   bool interaction::on_set_position(const ::point_i32 & point, enum_layout elayout)
   {

      return true;

   }


   bool interaction::on_set_size(const ::size_i32 & size, enum_layout elayout)
   {

      string strType = typeid(*this).name();

      if (strType.contains_ci("control_box"))
      {

         if (strType.contains_ci("button"))
         {

         }
         else
         {

            //output_debug_string("control_box::on_set_size(" + __string(size) + ")");

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


   //      m_pinteractiondraw2d = new interaction_draw2d();

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


   ::windowing::window * interaction::_window() const
   {
      
      auto puserinteractionTopLevel = ((interaction *)this)->_top_level();

      if (::is_null(puserinteractionTopLevel))
      {

         return nullptr;

      }

      auto pinteractionimpl = puserinteractionTopLevel->m_pinteractionimpl;

      if (::is_null(pinteractionimpl))
      {
         
         if(::is_set(puserinteractionTopLevel->m_puserinteractionParent))
         {
         
            pinteractionimpl = puserinteractionTopLevel->m_puserinteractionParent->m_pinteractionimpl;
            
         }
         
         if(::is_null(pinteractionimpl))
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


   //::windowing::windowing * interaction::windowing() const
   //{

   //   auto pwindow = window();

   //   if (::is_null(pwindow))
   //   {

   //      return nullptr;

   //   }

   //   auto pwindowing = pwindow->windowing();

   //   if (::is_null(pwindowing))
   //   {

   //      return nullptr;

   //   }

   //   return pwindowing;

   //}


   ::windowing::display * interaction::get_display() const
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


   ::user::interaction * interaction::get_host_window() const
   {

      auto psession = get_session();

      if (psession == nullptr)
      {

         return nullptr;

      }

      __pointer(::user::interaction) puserinteractionHost = psession->m_puserprimitiveHost;

      if (puserinteractionHost)
      {

         return puserinteractionHost;

      }
      else
      {

         return get_wnd();

      }

   }


   enum_element interaction::get_default_element() const
   {

      return e_element_none;

   }


   ::write_text::font_pointer
      interaction::get_font(style * pstyle, enum_element eelement, ::user::enum_state estate) const
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


   enum_translucency interaction::get_translucency(style * pstyle) const
   {

      if (pstyle)
      {

         return pstyle->m_etranslucency;

      }

      return e_translucency_undefined;

   }


   int interaction::get_int(style * pstyle, enum_int eint, ::user::enum_state estate, int iDefault) const
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


   double interaction::get_double(style * pstyle, enum_double edouble, ::user::enum_state estate, double dDefault) const
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


   status<::rectangle_f64>
      interaction::get_border(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      return nullptr;

   }


   status<::rectangle_f64>
      interaction::get_padding(style * pstyle, enum_element eelement, ::user::enum_state estate) const
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


   status<::rectangle_f64>
      interaction::get_margin(style * pstyle, enum_element eelement, ::user::enum_state estate) const
   {

      if (m_flagNonClient.has(non_client_focus_rect))
      {

         double dFocusHeightWidth = get_double(pstyle, ::user::e_double_focus_height_width, estate, 2.0);

         ::rectangle_f64 rectangleDefaultMargin(dFocusHeightWidth, dFocusHeightWidth, dFocusHeightWidth,
            dFocusHeightWidth);

         return rectangleDefaultMargin;

      }

      ::rectangle_f64 rectangleDefaultMargin(0.0, 0.0, 0.0, 0.0);

      return rectangleDefaultMargin;

   }


   status<::color::color> interaction::get_color(style * pstyle, enum_element eelement, ::user::enum_state estate) const
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


   eflag interaction::get_draw_flags(style * pstyle) const
   {

      return e_null;

   }


   style * interaction::get_style() const
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


   ::user::style * interaction::get_style(::draw2d::graphics_pointer & pgraphics) const
   {

      return pgraphics ? get_style(pgraphics->m_puserstyle) : get_style();

   }


   void interaction::on_tsf_activate(bool bActivate)
   {

      m_pinteractionimpl->on_tsf_activate(bActivate);

   }


   string interaction::default_id_prefix() const
   {

      return __type_name(this) + "_";

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

      //synchronous_lock slChildren(::user::mutex_children());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      for (index iIdSuffix = 1; iIdSuffix <= 1000; iIdSuffix++)
      {

         strCandidateId.format("%s_%d", strDefaultIdPrefix.c_str(), iIdSuffix);

         bDuplicate = false;

         for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
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

   //   __pointer(interaction) pinteraction = pdescriptor->alloc();

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


   interaction * interaction::get_tooltip()
   {

      return m_ptooltip;

   }


   void interaction::set_tool_window(bool bSet)
   {

      if (is_null(m_pprimitiveimpl))
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


   void interaction::set_need_redraw(bool bAscendants)
   {

      auto * pinteraction = get_wnd();

      if (::is_null(pinteraction))
      {

         pinteraction = this;

      }

      pinteraction->m_bNeedRedraw = true;

      auto edisplayRequest = pinteraction->layout().sketch().display();

      auto edisplayState = pinteraction->layout().window().display();

      if (pinteraction->m_pprimitiveimpl.is_set() &&
         (
            layout().sketch().is_screen_visible() || edisplayState != edisplayRequest
            ))
      {

         pinteraction->m_pprimitiveimpl->set_need_redraw();

      }

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
      
      auto * pinteraction = get_host_window();

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


   ::element * interaction::get_taskpool_container()
   {

      return parent_frame();

   }


   void interaction::set_place_child_title(const ::string & pszTitle)
   {

      payload("place_child_title") = pszTitle;

      //__pointer(::user::place_holder) pholder = get_parent();

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


   ::user::primitive * interaction::get_bind_ui()
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


   interaction * interaction::get_parent_window() const
   {

      return get_parent();

   }


   bool interaction::is_host_top_level() const
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
   //      __pointer(::user::interaction) puserinteractionHost = psession->m_puserprimitiveHost;
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


   ::user::element * interaction::get_parent_primitive() const
   {

      return get_parent();

   }


   interaction * interaction::get_parent() const
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


   oswindow interaction::GetParentHandle() const
   {

      interaction * puserinteractionParent = get_parent();

      if (puserinteractionParent == nullptr)
      {

         return nullptr;

      }

      return puserinteractionParent->get_safe_oswindow();

   }


   bool interaction::on_before_set_parent(::user::primitive * puserinteractionParent)
   {

      return true;

   }


   ::user::primitive * interaction::set_parent(::user::primitive * puserinteractionParent)
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

         if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
         {

            m_pthreadUserInteraction->m_puiptraThread->erase(this);

         }

         __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      }

      auto pprimitiveimplOld = m_pprimitiveimpl;

      __pointer(interaction) pparentOld = get_parent();

      if (puserinteractionParent == nullptr)
      {

         auto pprimitiveimplNew = __create<::user::interaction_impl>();

         auto strName = get_window_text();

         const char * pszClassName = nullptr;

         m_bEnableSaveWindowRect2 = true;

         on_set_parent(nullptr);

         if (m_ewindowflag & e_window_flag_load_window_rect_on_impl)
         {

            WindowDataLoadWindowRect();

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

         __pointer(::aura::application) papp = get_app();

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

         auto pparent = puserinteractionParent->cast<::user::interaction>();

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


   bool interaction::pre_message_handler(::message::key *& pkey, bool & bKeyMessage, ::message::message * pmessage)
   {

      ::u32 message = pmessage->m_atom.umessage();

      if (message == e_message_left_button_down)
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
      else if (message == e_message_left_button_up)
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
      else if (message == e_message_right_button_down)
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
      else if (message == e_message_right_button_up)
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
      else if (message == e_message_middle_button_down)
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
      else if (message == e_message_middle_button_up)
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

      bKeyMessage = message == e_message_key_down ||
         message == e_message_key_up ||
         message == e_message_char ||
         message == e_message_text_composition
#ifdef WINDOWS_DESKTOP
         || message == e_message_sys_key_down
         || message == e_message_sys_key_up
         || message == e_message_sys_char
         || message == e_message_ime_key_down
         || message == e_message_ime_key_up
         || message == e_message_ime_char
         || message == e_message_ime_select
         || message == e_message_ime_set_context
         || message == e_message_ime_start_composition
         || message == e_message_ime_composition
         || message == e_message_ime_composition_full
         || message == e_message_ime_notify
         || message == e_message_ime_end_composition
         || message == e_message_input_language
#endif
         ;

      if (bKeyMessage)
      {

         pkey = dynamic_cast <::message::key *> (pmessage);

         if (pkey)
         {

            windowing()->set(pkey, pkey->m_oswindow, pkey->m_pwindow, pkey->m_atom, pkey->m_wparam, pkey->m_lparam);

         }

         if (message == e_message_key_down || message == e_message_sys_key_down)
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
         else if (message == e_message_key_up || message == e_message_sys_key_up)
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
   //         __pointer(::aura::application) papp = get_app();
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

      auto puserinteractionKeyboardFocus = puser->get_keyboard_focus(m_pthreadUserInteraction);

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
      MESSAGE_LINK(e_message_text_composition, pchannel, this, &interaction::_001OnTextComposition);

      primitive::install_message_routing(pchannel);

      if (m_bMessageWindow)
      {

         //MESSAGE_LINK(e_message_destroy              , pchannel, this, &interaction::_001OnDestroyMessageWindow);

      }
      else
      {

         if (m_bEditDefaultHandling)
         {

            add_command_handler("edit_delete", this, &interaction::_001OnEditDelete);

         }

         MESSAGE_LINK(e_message_close, pchannel, this, &interaction::on_message_close);
         MESSAGE_LINK(e_message_size, pchannel, this, &interaction::on_message_size);
         MESSAGE_LINK(e_message_move, pchannel, this, &interaction::on_message_move);
         MESSAGE_LINK(e_message_non_client_calcsize, pchannel, this,
            &interaction::on_message_non_client_calculate_size);
         MESSAGE_LINK(e_message_show_window, pchannel, this, &interaction::on_message_show_window);
         MESSAGE_LINK(e_message_display_change, pchannel, this, &interaction::on_message_display_change);
         MESSAGE_LINK(e_message_subject, pchannel, this, &interaction::on_message_subject);
         MESSAGE_LINK(e_message_left_button_down, pchannel, this, &::user::interaction::on_message_left_button_down);
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


   void interaction::prio_install_message_routing(::channel * pchannel)
   {

      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &interaction::on_message_left_button_down);

   }


   void interaction::on_message_non_client_calculate_size(::message::message * pmessage)
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


   void interaction::set_layout_state(const layout_state & state, enum_layout elayout)
   {

      m_layout.m_statea[elayout] = state;

   }


   void interaction::set_activation(::e_activation eactivation, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eactivation = eactivation;

   }


   void interaction::display_restored()
   {

#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_restored");

#endif

#if DEBUG_LEVEL > 0

      if (m_pdescriptor.is_set() && m_puserinteractionParent == nullptr)
      {

         INFORMATION("Parent is Null. Display Request -> normal");

      }

#endif

      layout().sketch().display() = e_display_restored;

   }


   void interaction::display_iconic()
   {
      
#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_iconic");

#endif

      layout().sketch().display() = e_display_iconic;

   }


   void interaction::display_restore()
   {
      
#ifdef INFO_LAYOUT_DISPLAY

      INFORMATION("interaction_layout::display e_display_restore");

#endif
      
      auto edisplayDesign = const_layout().design().display();
      
      layout().sketch().display() = e_display_restore;

   }


   void interaction::display(::e_display edisplay, ::e_activation eactivation)
   {

      bool bToggle = false;

      if (edisplay == e_display_restored)
      {

         display_restored();

      }
      else if (edisplay == e_display_hide)
      {

#ifdef INFO_LAYOUT_DISPLAY

         INFORMATION("interaction_layout::display e_display_hide");

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

         output_debug_string("\ne_display_zoomed\n");

#ifdef INFO_LAYOUT_DISPLAY

         INFORMATION("interaction_layout::display e_display_zoomed");

#endif
         
         layout().sketch().display() = e_display_zoomed;

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
         
         layout().sketch().display() = e_display_full_screen;

      }
      else if (edisplay == e_display_restore)
      {

         display_restore();

      }
      else if (edisplay == e_display_default)
      {

   #ifdef INFO_LAYOUT_DISPLAY

            INFORMATION("interaction_layout::display e_display_default");

   #endif

         auto edisplayCurrent = layout().sketch().display();

         auto edisplayStored = window_stored_display();

         auto edisplayPrevious = window_previous_display();

         if (edisplayCurrent == e_display_undefined)
         {

            edisplay = e_display_restored;

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

            edisplay = ::e_display_restored;

         }

         layout().sketch().display() = edisplay;

      }
      else
      {

#ifdef INFO_LAYOUT_DISPLAY

         INFORMATION("interaction_layout::display (unknown)");

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


   void interaction::notify_on_destroy(::property_object * pobject)
   {

      ::user::primitive::notify_on_destroy(pobject);

   }


   void interaction::on_message_destroy(::message::message * pmessage)
   {

      m_ewindowflag += e_window_flag_destroying;

      try
      {

         if (m_pprimitiveimpl)
         {

            m_pprimitiveimpl->set_destroying();

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
   //         __pointer(::message::object) pobjectmessage(pmessage);
   //
   //         __pointer(::message::message) pmessage(pobjectmessage->m_pmatter);
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

      if (is_null(psession))
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

      clear_prodevian();

      try
      {

         if (!m_pprimitiveimpl->is_destroying())
         {

            //synchronous_lock slChildren(::user::mutex_children());

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

            call_message_handler(e_message_mouse_leave);

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
            || get_wnd()->m_pprimitiveimpl->is_destroying())
         {

            output_debug_string("destroying os window");

         }
         else
         {

            post_procedure([this]()
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

            synchronous_lock synchronouslock(psession->mutex());

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


   void interaction::_001GetSel(strsize & iBeg, strsize & iEnd) const
   {


   }


   void interaction::get_horizontal_scroll_info(scroll_info & info)
   {

      ::size_i32 sizeTotal = get_total_size();

      auto sizePage = get_page_size();

      auto pointOffset = get_viewport_offset();

      info.nMin = 0;
      info.nMax = (::i32)sizeTotal.cx;
      info.nPage = (::i32)sizePage.cx;
      info.nPos = pointOffset.x;
      info.nTrackPos = pointOffset.x;

   }


   void interaction::get_vertical_scroll_info(scroll_info & info)
   {

      auto sizeTotal = get_total_size();

      auto sizePage = get_page_size();

      auto pointOffset = get_viewport_offset();

      info.nMin = 0;
      info.nMax = (::i32)sizeTotal.cy;
      info.nPage = (::i32)sizePage.cy;
      info.nPos = pointOffset.y;
      info.nTrackPos = pointOffset.y;

   }


   void interaction::layout_scroll_bar(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void interaction::on_erase_child(::user::interaction * pinteraction)
   {

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

               synchronous_lock synchronouslock(pprimitiveimpl->mutex());

               pprimitiveimpl->m_userinteractionaMouseHover.erase(this);

            }

         }

      }

      {

         synchronous_lock synchronouslock(mutex());

         auto pthread = get_thread();

         if (pthread != nullptr)
         {

            if (pthread->get_active_user_primitive() == this)
            {

               pthread->set_active_user_primitive(nullptr);

            }

         }

      }

      ::user::interaction * puserinteractionParent = m_puserinteractionParent;

      if (puserinteractionParent != nullptr)
      {

         try
         {

            //synchronous_lock slChildren(::user::mutex_children());

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

               __pointer(::aura::application) papp = get_app();

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

                  __pointer(::aura::application) papp = get_app();

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


   void interaction::on_message_size(::message::message * pmessage)
   {

      __pointer(::message::size) psize(pmessage);

      pmessage->previous();

      if (psize->m_nType == SIZE_MINIMIZED)
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

         //synchronous_lock slChildren(::user::mutex_children());

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         if (puserinteractionpointeraChild)
         {

            for (auto & puserinteraction : puserinteractionpointeraChild->interactiona())
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

               for (auto & puserinteraction :
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


   void interaction::on_message_move(::message::message * pmessage)
   {

      pmessage->previous();

   }


   void interaction::defer_set_icon()
   {

#if defined(CUBE)

      return;

#endif

#ifdef WINDOWS_DESKTOP

      auto pwindowingicon = get_windowing_icon();

      if (get_parent() == nullptr && ::is_null(pwindowingicon))
      {

         ::file::path strMatter = get_window_default_matter();

         auto pwindowing = windowing();

         auto pcontext = m_pcontext->m_papexcontext;

         ::file::path pathIcon = "matter://main/icon.ico";

         auto picon = window()->load_icon(pathIcon);

         set_windowing_icon(picon);

      }

#endif

   }


   void interaction::set_windowing_icon(::windowing::icon * picon)
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


   void interaction::set_viewport_org(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->set_viewport_org(pgraphics);

   }


   ::point_i32 interaction::get_parent_accumulated_scroll(enum_layout elayout) const
   {

      ::point_i32 pointScroll;

      auto pChild = this;

      while (::is_set(pChild) && ::is_set(pChild->get_parent()))
      {

         if (pChild->m_bParentScrollX)
         {

            pointScroll.x += pChild->get_parent()->m_pointScroll.x;

         }

         if (pChild->m_bParentScrollY)
         {

            pointScroll.y += pChild->get_parent()->m_pointScroll.y;

         }

         pChild = pChild->get_parent();

      }

      return pointScroll;

   }


   void interaction::_001OnClip(::draw2d::graphics_pointer & pgraphics)
   {

      try
      {

         ::rectangle_i32 rectangleClip;

         ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain<::aura::draw_context>::get_last();

         ::rectangle_i32 rectangleClient;

         bool bFirst = true;

         auto type = __object_type(*this);

         if (type.name_contains("scroll_bar"))
         {

            output_debug_string("scroll_bar");

         }
         //         else if (strType.contains_ci("combo_box"))
         //         {
         //
         //            output_debug_string("combo box on clip");
         //
         //         }

#if defined(MACOS) || defined(LINUX) || defined(_UWP)

//         if (strType.contains_ci("pane"))
//         {
//
//            output_debug_string("a");
//
//         }

#endif

         if (pdrawcontext != nullptr)
         {

            get_client_rect(rectangleClient);

            rectangleClient.bottom++;
            rectangleClient.right++;

            rectangleClip = rectangleClient;

            bFirst = false;

         }

         ::user::interaction * pinteraction = this;

         //synchronous_lock synchronouslock(mutex());

         //auto pinteractiondraw2d = get_draw2d();

         //m_pshapeaClip.release();

         if (!m_bClipRectangle)
         {

            ::rectangle_i32 rectangleClient;

            ::index i = 0;

            while (pinteraction != nullptr)
            {

               pinteraction->get_client_rect(rectangleClient);

               pinteraction->client_to_host(rectangleClient);

               host_to_client(rectangleClient);

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

         pgraphics->reset_clip();

         pgraphics->m_pointAddShapeTranslate = m_pointScroll;

         pgraphics->intersect_clip(m_rectangleClip);

      }
      catch (...)
      {

         throw ::exception(error_exception, "no more a window");

      }

   }


   void interaction::_001DrawThis(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc k(pgraphics);

      ___scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      if (pgraphics == nullptr)
      {

         throw ::exception(error_bad_argument);

      }

      try
      {

         pgraphics->m_dFontFactor = 1.0;

         {

            //synchronous_lock synchronouslock(mutex());

            {

#ifdef __DEBUG

               auto tickStart = ::duration::now();

#endif //__DEBUG

               //auto pstyle = get_style(pgraphics);

               _001OnNcDraw(pgraphics);


#ifdef __DEBUG

               auto tickEnd = ::duration::now();

               ::duration durationElapsed = tickEnd - tickStart;

               if (durationElapsed > 100_ms)
               {

                  output_debug_string("\ndrawing took " + __string(durationElapsed.integral_millisecond()) + "!!");
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

            auto tickStart = ::duration::now();

#endif //__DEBUG

            try
            {

               _001CallOnDraw(pgraphics);

            }
            catch (...)
            {

            }

#ifdef __DEBUG

            auto durationElapsed = tickStart.elapsed();

            if (durationElapsed > 50_ms)
            {

               auto type = __object_type(*this);

               if (type.name_contains("font_list"))
               {

                  output_debug_string(type.m_strName + "\n");

               }

#ifdef VERBOSE_LOG               


               CATEGORY_INFORMATION(prodevian, type.m_strName << " drawing took more than 50ms to complete ("
                  << durationElapsed.integral_millisecond() << ")!!\n");

                  // let's trye to see what happened?
                  //_001CallOnDraw(pgraphics);

#endif

            }

#endif //__DEBUG

         }


      }
      catch (...)
      {

         INFORMATION("Exception: interaction::_001DrawThis %s" << __object_type(*this).m_strName);

      }

      if (m_puserinteractionParent != nullptr)
      {

         {

#ifdef __DEBUG

            auto tickStart = ::duration::now();

#endif //__DEBUG

            on_after_graphical_update();


#ifdef __DEBUG

            auto tickEnd = ::duration::now();

            auto durationElapsed = tickEnd - tickStart;

#ifdef VERBOSE_LOG               

            if (durationElapsed > 100_ms)
            {

               CATEGORY_INFORMATION(prodevian,
                  "\ndrawing took " + __string(durationElapsed.integral_millisecond()) + "!!");
               CATEGORY_INFORMATION(prodevian, "\ndrawing took more than 100ms more than 50ms to complete!!");

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

      ___scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      point_i32 pointScroll = m_pointScroll;

      if (!pointScroll.is_null())
      {

         pgraphics->OffsetViewportOrg(-pointScroll.x, -pointScroll.y);

      }

      //on_viewport_offset(pgraphics);

#ifdef __DEBUG

      auto tickStartWithLock = ::duration::now();

#endif

      //synchronous_lock synchronouslock(mutex());

      {

         {

#ifdef __DEBUG

            auto tickStart = ::duration::now();

#endif //__DEBUG

            _001OnClip(pgraphics);

            ::rectangle_i32 rectangleDraw;

            get_client_rect(rectangleDraw);

            __copy(pgraphics->m_rectangleDraw, rectangleDraw);

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

            auto tickEnd = ::duration::now();

            ::duration durationElapsed = tickEnd - tickStart;

#ifdef VERBOSE_LOG               

            if (durationElapsed > 100_ms)
            {

               CATEGORY_INFORMATION(prodevian, "\ndrawing at " << __type_name(this) << "!!");
               CATEGORY_INFORMATION(prodevian, "\ndrawing took " << durationElapsed.integral_millisecond() << +"!!");
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

      auto tickEndWithLock = ::duration::now();

      auto tickElapsedWithLock = tickEndWithLock - tickStartWithLock;

      if (tickElapsedWithLock > 3_ms)
      {

         //string strType = __type_name(this);

         //         output_debug_string("\n" + strType + "drawing took " + __string(tickElapsedWithLock.m_i) + "!!");
         //       output_debug_string("\ndrawing took more than 3ms to complete!!");
         //     output_debug_string("\n");

      }

#endif //__DEBUG

      pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);

   }


   void interaction::_008CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc k(pgraphics);

      try
      {

         set_viewport_org(pgraphics);

         synchronous_lock synchronouslock(mutex());

         _008OnDraw(pgraphics);

      }
      catch (...)
      {

      }

   }


   void interaction::on_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      ::point_i32 pointOffset;

      if (m_puserinteractionParent != nullptr)
      {

         pointOffset = layout().sketch().origin();

      }

      auto pointViewportOffset = get_viewport_offset();

      auto offset = pointOffset - pointViewportOffset;

      pgraphics->OffsetViewportOrg((::i32)offset.cx, (::i32)offset.cy);

   }


   synchronization_object * interaction::mutex_draw()
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

      return pgraphics->mutex();

   }


   void interaction::_001DrawChildren(::draw2d::graphics_pointer & pgraphics)
   {

      point_i32 pointScroll = m_pointScroll;

      bool bParentScrollX = false;

      bool bParentScrollY = false;

      try
      {

         //::draw2d::savedc k(pgraphics);

         //on_viewport_offset(pgraphics);
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

                  if (pinteraction->is_destroying() || !pinteraction->is_window())
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

                           pgraphics->OffsetViewportOrg(-pointScroll.x, 0);

                           bParentScrollX = true;

                        }
                        else if (bParentScrollX && !pinteraction->m_bParentScrollX)
                        {

                           pgraphics->OffsetViewportOrg(pointScroll.x, 0);

                           bParentScrollX = false;

                        }

                        if (!bParentScrollY && pinteraction->m_bParentScrollY)
                        {

                           pgraphics->OffsetViewportOrg(0, -pointScroll.y);

                           bParentScrollY = true;

                        }
                        else if (bParentScrollY && !pinteraction->m_bParentScrollY)
                        {

                           pgraphics->OffsetViewportOrg(0, pointScroll.y);

                           bParentScrollY = false;

                        }

                     }

                     pinteraction->_000CallOnDraw(pgraphics);

                     //{

                     //   //::duration t1 = ::duration::now();

                     //   pinteraction->_000OnDraw(pgraphics);

                     //   ///::duration d1 = t1.elapsed();

                     //   //if(d1.m_i > 50)
                     //   //{

                     //   //   string strType = __type_name(pinteraction);

                     //   //   if(strType.contains("hello_multiverse") && strType.contains("frame"))
                     //   //   {

                     //   //      output_debug_string(".");

                     //   //   }

                     //   //   CINFO(prodevian)("(more than 50ms)(D) "+strType+"::_000OnDraw took " + __string(d1.m_i) + "::duration.\n");

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

      //pgraphics->OffsetViewportOrg(pointScroll.x, pointScroll.y);

      if (bParentScrollX && pointScroll.x)
      {

         pgraphics->OffsetViewportOrg(pointScroll.x, 0);

      }

      if (bParentScrollY && pointScroll.y)
      {

         pgraphics->OffsetViewportOrg(0, pointScroll.y);

      }

   }


   void interaction::_001PrintBuffer(::draw2d::graphics_pointer & pgraphics)
   {

      windowing_output_debug_string("\n_001UpdateBuffer : before graphics lock");

      windowing_output_debug_string("\n_001UpdateBuffer : after graphics lock");

      windowing_output_debug_string("\n_001UpdateBuffer : after check1");

      ::draw2d::savedc savedc(pgraphics);

      windowing_output_debug_string("\n_001UpdateBuffer : after savedc");

      windowing_output_debug_string("\n_001UpdateBuffer : after check2");

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow, e_layout_design);

      ::rectangle_i32 rectangle(rectangleWindow);

      rectangle.offset(-rectangle.top_left());

      //#ifdef _UWP

      // pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

      //#else

      //pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);

      //#endif

      windowing_output_debug_string("\n_001UpdateBuffer : after set alphamode");

      auto pstyle = get_style(pgraphics);

      if (pgraphics->m_pimage->is_ok())
      {

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_set);
         
         if (m_pinteractionimpl->is_composite())
         {

            pgraphics->m_pimage->fill(0);

         }
         else
         {

            pgraphics->m_pimage->fill(255, 192, 192, 192);

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

      windowing_output_debug_string("\n_001UpdateBuffer : before Print");

      try
      {

         //synchronous_lock slChildren(::user::mutex_children());

         //if (0) // abcxxx
         {
            _001Print(pgraphics);

         }

      }
      catch (...)
      {


      }

#ifdef REDRAW_HINTING

      {

         auto rectangleClient = m_puserinteraction->get_client_rect();

         ::rectangle_i32 rectangleHint(rectangleClient);

         pgraphics->SelectClipRgn(nullptr);

         pgraphics->set_alpha_mode(::draw2d::e_alpha_mode_blend);

         pgraphics->fill_rectangle(rectangleHint, argb(128, __random(128, 255), __random(128, 255), __random(128, 255)));

      }

#endif
      //      pgraphics->fill_solid_rect_dim(10, 50, 200, 200, argb(128, __random(128, 255), __random(128, 255), __random(128, 255)));


      windowing_output_debug_string("\n_001UpdateBuffer : after Print");

#if HARD_DEBUG

      ::draw2d::graphics_pointer g(e_create);

      g->debug();

      m_size.cx = 0;

      m_size.cy = 0;

#endif

   }


   void interaction::_001Print(::draw2d::graphics_pointer & pgraphics)
   {

      windowing_output_debug_string("\n_001Print A");

      {

         ::draw2d::savedc k(pgraphics);

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

            ::draw2d::savedc k(pgraphics);

            try
            {

               auto pwindowing = windowing();

               auto pwindow = window();

               auto pointCursor = pwindow->get_cursor_position();

               screen_to_client(pointCursor, e_layout_design);

               auto * pcursor = pwindowing->get_cursor();

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


   void interaction::_000CallOnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         set_need_redraw();

         post_redraw();

         return;

      }

      ___scoped_restore(pgraphics->m_puserinteraction);

      pgraphics->m_puserinteraction = this;

      bool bUpdateBuffer = false;

      bool bUpdateWindow = false;

      auto type = __object_type(*this);

      if (type.name_contains("app_veriwell_keyboard") && type.name_contains("main_frame"))
      {

         // output_debug_string("app_veriwell_keyboard::main_frame");

      }
      else if (type.name_contains("plain_edit"))
      {

         //output_debug_string("plain_edit");

      }
      //      else if (strType.contains_ci("font_list"))
      //      {
      //
      //         output_debug_string("font_list");
      //
      //      }
      else if (type.name_contains("combo_box"))
      {

         //output_debug_string("combo_box");

      }
      else if (type.name_contains("list_box"))
      {

         output_debug_string("list_box");

      }

      //if (!is_sketch_to_design_locked())
      //{

         sketch_to_design(bUpdateBuffer, bUpdateWindow);

      //}

      if (m_bSketchToDesignLayout)
      {

         m_bSketchToDesignLayout = false;

         design_layout(pgraphics);



      }

      bool bZorder = check_child_zorder();

      if(bZorder)
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

      if (type.name_contains("list_box"))
      {

         output_debug_string("list_box");

      }

      //      if(m_strInteractionTag.begins_ci("button_"))
      //      {
      //
      //         output_debug_string("drawing: " + m_strInteractionTag + "\n");
      //
      //      }
      //      else if(m_strInteractionTag.begins_ci("control_box"))
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

         pgraphics->OffsetViewportOrg(pointOffset.x, pointOffset.y);

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

         pgraphics->OffsetViewportOrg(-pointOffset.x, -pointOffset.y);

      }

   }


   void interaction::process_graphics_call_queue(::draw2d::graphics_pointer & pgraphics)
   {

      //synchronous_lock synchronouslock(mutex());

      if (m_pgraphicscalla)
      {

         while (m_pgraphicscalla->has_element())
         {

            auto pcall = m_pgraphicscalla->pick_first();

            //synchronouslock.unlock();

            try
            {

               pcall->call(pgraphics);

            }
            catch (...)
            {

            }

            //synchronouslock.lock();

         }

      }

   }


   void interaction::_000OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::draw2d::savedc k(pgraphics);

      try
      {

         auto type = __object_type(*this);

         if (type.name_contains("waven::impact"))
         {

            output_debug_string("waven::impact");
         }
         //         else if(strType.contains_ci("menu_list_view"))
         //         {
         //
         //            output_debug_string("menu_list_view");
         //
         //         }
         //   if (!is_custom_draw() && pgraphics->m_pnext == nullptr)
         //   {

         //      set_viewport_org(pgraphics);

         //   }

         //}
         ////         ::point_i32 pointParentOffset = get_parent_viewport_offset();
         ////
         ////         pgraphics->OffsetViewportOrg(-pointParentOffset.x, -pointParentOffset.y);

         try
         {

            _001DrawThis(pgraphics);

         }
         catch (...)
         {

            TRACE("Exception: interaction::_000OnDraw _001DrawThis %s" << __object_type(*this).m_strName);

         }

      }
      catch (...)
      {

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

               TRACE("Exception: interaction::_000OnDraw _001DrawChildren %s" << __object_type(*this).m_strName);

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

               auto t1 = ::duration::now();

               _008CallOnDraw(pgraphics);

               auto d1 = t1.elapsed();

#ifdef VERBOSE_LOG

               if (d1 > 50_ms)
               {

                  auto type = __object_type(*this);

                  CATEGORY_INFORMATION(prodevian, "(more than 50ms)(E) " << type.m_strName << "::_008CallOnDraw took " <<
                     d1.integral_millisecond() << "::duration.\n");

               }

#endif

            }

         }

      }
      catch (...)
      {

      }

   }


   void interaction::_008OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

   }


   void interaction::draw_control_background(::draw2d::graphics_pointer & pgraphics)
   {

      ::aura::draw_context * pdrawcontext = pgraphics->::aura::simple_chain<::aura::draw_context>::get_last();

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

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


   void interaction::add_prodevian(::matter * pmatter)
   {

      auto phostwindow = get_host_window();

      if (phostwindow == nullptr)
      {

         throw ::exception(error_wrong_state);

      }

      auto pprimitiveimpl = phostwindow->m_pprimitiveimpl;

      return pprimitiveimpl->add_prodevian(pmatter);

   }


   void interaction::erase_prodevian(::matter * pmatter)
   {

      if (get_wnd() == nullptr || get_wnd()->m_pprimitiveimpl == nullptr)
      {

         return;

      }

      get_wnd()->m_pprimitiveimpl->erase_prodevian(pmatter);

   }


   bool interaction::is_prodevian(const ::matter * pmatter) const
   {

      if (get_wnd() == nullptr || get_wnd()->m_pprimitiveimpl == nullptr)
      {

         return false;

      }

      return get_wnd()->m_pprimitiveimpl->is_prodevian(pmatter);

   }


   __pointer(::message::message) interaction::get_message(const ::atom & atom, wparam wparam, lparam lparam)
   {

      __pointer(::message::message) pmessage;

      auto eprototype = ::message::get_message_prototype((enum_message)atom.i64(), 0);

      switch (eprototype)
      {
      case ::message::PrototypeNone:
      {

         pmessage = __new(::user::message);

      }
      break;
      case ::message::PrototypeCreate:
      {
         pmessage = __new(::message::create);
      }
      break;
      case ::message::PrototypeEnable:
      {
         pmessage = __new(::message::enable);
      }
      break;
      case ::message::PrototypeNcActivate:
      {
         pmessage = __new(::message::nc_activate);
      }
      break;
      case ::message::PrototypeKey:
      {
         pmessage = __new(::message::key);
      }
      break;
      case ::message::PrototypeTimer:
      {

         //throw ::exception(::exception("do not use e_message_timer or Windows SetTimer/KillTimer"));

         pmessage = __new(::message::timer);

      }
      break;
      case ::message::PrototypeShowWindow:
      {
         pmessage = __new(::message::show_window);
      }
      break;
      case ::message::PrototypeSetCursor:
      {
         pmessage = __new(::message::set_cursor);
      }
      break;
      case ::message::PrototypeNcHitTest:
      {
         pmessage = __new(::message::nc_hit_test);
      }
      break;
      case ::message::PrototypeMove:
      {
         pmessage = __new(::message::move);
      }
      break;
      case ::message::PrototypeEraseBkgnd:
      {
         pmessage = __new(::message::erase_bkgnd);
      }
      break;
      case ::message::PrototypeScroll:
      {
         pmessage = __new(::message::scroll);
      }
      break;
      case ::message::PrototypeSetFocus:
      {
         pmessage = __new(::message::set_keyboard_focus);
      }
      break;
      case ::message::PrototypeKillFocus:
      {
         pmessage = __new(::message::kill_keyboard_focus);
      }
      break;
#if !defined(_UWP) && !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID) && !defined(FREEBSD)
      case ::message::PrototypeWindowPos:
      {
         pmessage = __new(::message::window_pos);
      }
      break;
      case ::message::PrototypeNcCalcSize:
      {
         pmessage = __new(::message::nc_calc_size);
      }
      break;
#endif
      case ::message::PrototypeMouse:
      {
         pmessage = __new(::message::mouse);
      }
      break;
      case ::message::PrototypeMouseWheel:
      {
         pmessage = __new(::message::mouse_wheel);
      }
      break;
      case ::message::PrototypeSize:
      {
         pmessage = __new(::message::size);
      }
      break;
      case ::message::PrototypeActivate:
      {
         pmessage = __new(::message::activate);
      }
      break;
      case ::message::PrototypeMouseActivate:
      {
         pmessage = __new(::message::mouse_activate);
      }
      break;
      case ::message::PrototypeSimpleCommand:
      {
         pmessage = __new(::message::simple_command);
      }
      break;
      case ::message::PrototypeObject:
      {
         pmessage = __new(::message::object);
      }
      break;
      default:
      {
         pmessage = __new(::message::message);
      }
      break;
      }

      if (pmessage.is_null())
      {

         return nullptr;

      }

      //auto estatus =

      pmessage->initialize(this);

      //if (!estatus)
      //{

      //   return nullptr;

      //}

      pmessage->set(oswindow(), window(), atom, wparam, lparam);

      return pmessage;

   }


   void interaction::default_message_handler(::message::message * pmessage)
   {

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->default_message_handler(pmessage);

   }


   void interaction::_001OnTextComposition(::message::message * pmessage)
   {

      __pointer(::message::key) ptext = pmessage;

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

      return puser->get_keyboard_focus(m_pthreadUserInteraction);

   }


   void interaction::on_message_display_change(::message::message * pmessage)
   {

      //_001FancyInitialFramePlacement();

   }


   void interaction::on_message_subject(::message::message * pmessage)
   {

      __pointer(::topic) ptopic(pmessage->m_lparam);

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

      if (is_null(m_pthreadUserInteraction))
      {

         return false;

      }

      auto itaskCurrent = get_current_itask();

      auto itaskUserInteraction = m_pthreadUserInteraction->m_itask;

      return itaskCurrent == itaskUserInteraction;


   }


   ::item_pointer interaction::get_user_item(const ::item & item)
   {

      for (auto & pitem : m_useritema)
      {

         if (*pitem == (ITEM_BASE_ADDITIONS &)item)
         {

            return pitem;

         }

      }

      return nullptr;

   }


   void interaction::interaction_post(const ::procedure & procedure)
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


   bool interaction::is_user_thread() const
   {

      auto pthreadCurrent = ::get_task();

      auto pthreadUser = m_pthreadUserInteraction;

      auto bUserThread = pthreadCurrent && pthreadCurrent == pthreadUser;

      return bUserThread;

   }


   void interaction::interaction_send(const ::procedure & procedure)
   {

      __send_procedure(this, &interaction::interaction_post, procedure);

   }


   void interaction::on_message_create(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_bEnableDragClient)
      {

         enable_drag(e_element_client);

      }

      if (m_bEnableDragResize)
      {

         enable_drag(e_element_resize);

      }

      auto psystem = m_psystem->m_paurasystem;

      auto psignal = psystem->get_signal(id_user_style_change);

      psignal->add_handler(this);

      on_create_user_interaction();

      auto pcursor = get_mouse_cursor();

      if (::is_null(pcursor))
      {

         pcursor = windowing()->get_cursor(::e_cursor_arrow);

         set_mouse_cursor(pcursor);

      }

      run_property("on_create");

      call_routines_with_id(CREATE_ROUTINE);

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

         //synchronous_lock synchronouslock(mutex());

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

            __pointer(::aura::application) papp = get_app();

            papp->add_user_interaction(this);

         }

      }

      defer_create_mutex();

      //try
      //{
      //   if ((get_parent() != nullptr && get_parent() != psession->get_user_interaction_host())
      //         && !is_message_only_window()
      //         && psession->get_user_interaction_host() != this
      //      )
      //   {

      //      //__pointer(place_holder) pholder = get_parent();

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
      //            if (!_001IsPointInside(point_i32(pdrag->point.x, pdrag->point.y)))
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
      //      __pointer(::user::interaction) pinteraction = top_child();
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
      //               if (pinteraction->is_window_visible(e_layout_sketch) && (pdrag->m_atom == MESSAGE_OLE_DRAGLEAVE || pinteraction->_001IsPointInside(point_i32(pdrag->point.x, pdrag->point.y))))
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


   void interaction::_000OnMouseLeave(::message::message * pmessage)
   {

      if (!m_pprimitiveimpl)
      {

         return;

      }

      m_pprimitiveimpl->_000OnMouseLeave(pmessage);

   }


   //void interaction::_000OnMouse(::message::mouse * pmouse)
   //{

   //   // must lock ::user::mutex_children() at top stack chain
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

   //   // must lock ::user::mutex_children() at top stack chain
   //   // and only at top stack chain.

   //   // these try catchs are needed for multi threading : multi threaded windows: the hell
   //   // Now I understand why many OSes windows are single threaded.
   //   __pointer(::user::interaction) pinteraction;

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

      auto pwindow = window();

      auto pointCursor = pwindow->get_cursor_position();

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

      __pointer(interaction) pinteraction = top_child();

      while (pinteraction != nullptr)
      {

         __pointer(interaction) puie = pinteraction->_001FromPoint(point, true);

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

      if (m_pprimitiveimpl.is_null())
      {

         return false;

      }

      if (!is_window_screen_visible())
      {

         return false;

      }

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow, e_layout_sketch);

      return rectangleWindow.contains(point);

   }


   rectangle_i32 interaction::screen_rect()
   {

      ::rectangle_i32 rectangle;

      get_client_rect(rectangle);

      client_to_screen(rectangle);

      return rectangle;

   }



   bool interaction::_001IsPointInsideInline(const ::point_i32 & point)
   {

      return screen_rect().contains(point);

   }


   bool interaction::_001IsClientPointInsideInline(const ::point_i32 & point)
   {

      return layout().sketch().client_rect().contains(point);


   }


   bool interaction::_001IsParentClientPointInsideInline(const ::point_i32 & point)
   {

      return layout().sketch().parent_client_rect().contains(point);


   }


   void interaction::on_message_key_down(::message::message * pmessage)
   {

      if (get_parent() == nullptr)
      {

         if (pmessage->m_union.m_pkey->m_ekey == ::user::e_key_f4)
         {

            auto psession = m_puserinteraction->get_session();

            if (psession->is_key_pressed(::user::e_key_alt))
            {

               post_message(e_message_close);

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


   void interaction::on_message_key_up(::message::message * pmessage)
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


   ::point_i32 interaction::on_drag_start(::user::drag * pdrag)
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


   bool interaction::drag_shift(::user::drag * pdrag)
   {

      if (pdrag->m_eelement == e_element_client)
      {

         pdrag->m_ecursor = e_cursor_move;

         set_position(pdrag->point());

         set_reposition();

         set_need_redraw();

         post_redraw();

         return true;

      }
      else if (pdrag->m_eelement == e_element_resize)
      {

         pdrag->m_ecursor = e_cursor_size_bottom_right;

         auto size = pdrag->point() - layout().sketch().m_point;

         auto sizeMinimum = get_window_minimum_size();

         size = size.maximum(sizeMinimum);

         layout().sketch().m_size = size;

         set_need_layout();

         set_need_redraw();

         post_redraw();

         return true;

      }

      return false;

   }


   bool interaction::drag_hover(::user::drag * pdrag)
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


   void interaction::drag_set_cursor(::user::drag * pdrag)
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


   void interaction::on_message_character(::message::message * pmessage)
   {

      if (m_pappearance)
      {


         m_pappearance->on_character((int)pmessage->m_wparam.m_number);

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


   ::user::interaction * interaction::get_child_by_name(const ::string & strName, ::index iItem, i32 iLevel)
   {

      __pointer(interaction) pinteraction = top_child();

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

      __pointer(interaction) pchild;

      if (iLevel > 0 || iLevel == -1)
      {

         if (iLevel > 0)
         {

            iLevel--;

         }

         __pointer(interaction) pinteraction = top_child();

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


   ::user::interaction * interaction::get_child_by_id(const atom & atom, index iItem, i32 iLevel)
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

         ::user::interaction * puiChild = pinteraction->get_child_by_id(atom, iItem, iLevel);

         if (::is_set(puiChild))
         {

            return puiChild;

         }

      }

      return nullptr;

   }


   ::user::element * interaction::get_primitive_by_id(const atom & atom, ::index iItem, i32 iLevel)
   {

      auto pchild = get_child_by_id(atom, iItem, iLevel);

      if (::is_null(pchild))
      {

         return nullptr;

      }

      return pchild;

   }


   ::user::interaction * interaction::child_from_point(const ::point_i32 & point, const ::user::interaction_array & interactionaExclude)
   {

      auto pointClient = point;

      ::user::interaction * puserinteractionParent = nullptr;

      ::user::interaction * puserinteractionSearchChildren = this;

      do
      {

         if (!puserinteractionSearchChildren->is_this_visible())
         {

            break;

         }

         puserinteractionParent = puserinteractionSearchChildren;

         puserinteractionParent->parent_to_client(pointClient);

         auto puserinteractionpointeraChild = puserinteractionParent->m_puserinteractionpointeraChild;

         if (!puserinteractionpointeraChild)
         {

            break;

         }

         puserinteractionSearchChildren = nullptr;

         for (::index iChild = puserinteractionpointeraChild->interaction_last_index();
            iChild >= 0; iChild--)
         {

            auto & puserinteractionChild = puserinteractionpointeraChild->interaction_at(iChild);

            if (!interactionaExclude.contains_interaction(puserinteractionChild))
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

                     puserinteractionSearchChildren = puserinteractionChild;

                     break;

                  }

               }

            }

         }

      } while (puserinteractionSearchChildren != nullptr);

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


   lresult interaction::send(::message::message * pmessage)
   {

      message_handler(pmessage);

      return pmessage->m_lresult;

   }


   void interaction::post(::message::message * pmessage)
   {

      if (pmessage->m_atom == e_message_key_down)
      {

         output_debug_string("::user::interaction::post e_message_key_down");

      }

      ::lparam lparam(pmessage);

      post_message(e_message_post_user, 1, lparam);

   }


   lresult interaction::send_message(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->send_message(atom, wparam, lparam);

   }


   lresult interaction::message_call(const ::atom & atom, wparam wparam, lparam lparam, const ::point_i32 & point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->message_call(atom, wparam, lparam);

   }


   lresult interaction::message_call(::message::message * pmessage)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->message_call(pmessage);

   }


#ifdef LINUX


   lresult interaction::send_x11_event(void * pevent)
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


   void interaction::send_message_to_descendants(const ::atom & atom, wparam wparam, lparam lparam, bool bDeep,
      bool bOnlyPerm)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      //synchronous_lock synchronouslock(::user::mutex_children());

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         //synchronouslock.unlock();

         for (auto & puserinteraction : puserinteractionpointeraChild->interactiona())
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

         for (auto & puserinteraction : puserinteractionpointeraChild->interactiona())
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

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      {

         //synchronous_lock slChildren(::user::mutex_children());



      }

      for (auto & puiChild : puserinteractionpointeraChild->interactiona())
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

   //   //__pointer(::message::message) pmessage(pmessage);

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

   //   //         __pointer(::user::interaction) pinteraction = psession->get_keyboard_focus();

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
   //#if defined(_UWP)
   //
   //      __pointer(::user::interaction) puserinteraction;
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
   //      synchronous_lock synchronouslock(mutex());
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
   //      __pointer(primitive_impl) pprimitiveimplOld = m_pprimitiveimpl;
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

      auto pwindowing = puser->windowing1();

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

      __pointer(interaction_impl) pprimitiveimplNew;

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


   void interaction::create_child(::user::interaction * puserinteractionParent)
   {

      if (is_window())
      {

         start_destroying_window();

      }

      if (::is_null(m_psystem))
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

      //   //   pusersystem->m_createstruct.x = m_pprimitiveimpl->m_rectangle.left;
      //   //   pusersystem->m_createstruct.y = m_pprimitiveimpl->m_rectangle.top;
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

      //      puserinteractionParent->get_client_rect(rectangleFrame);

      //   }

      //}
      //else
      //{

      //   rectangleFrame = rectangle;

      //}

      //synchronous_lock synchronouslock(puserinteractionParent == nullptr ? nullptr : puserinteractionParent->mutex());

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

      if (is_null(this))
      {

         return false;

      }

      if (m_pprimitiveimpl.is_null())
      {

         return false;

      }

      if (get_parent() != nullptr)
      {

         if (!get_parent()->is_window())
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


   ::property_object * interaction::parent_property_set_holder() const
   {

      ::object * pobject = get_parent();

      if (::is_set(pobject))
      {

         return pobject;

      }

      pobject = get_owner();

      if (::is_set(pobject))
      {

         return pobject;

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


   void interaction::RedrawWindow(const ::rectangle_i32 & rectangleUpdate, ::draw2d::region * prgnUpdate, ::u32 flags)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->RedrawWindow(rectangleUpdate, prgnUpdate, flags);

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point_i32 & point)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->ChildWindowFromPoint(point);

   }


   ::user::interaction * interaction::ChildWindowFromPoint(const ::point_i32 & point, ::u32 nFlags)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->ChildWindowFromPoint(point, nFlags);

   }


   ::user::interaction * interaction::get_first_child_window() const
   {

      auto pchildren = m_puserinteractionpointeraChild;

      if (::is_null(pchildren) || pchildren->has_no_interaction())
      {

         return nullptr;

      }

      return pchildren->get_first_interaction();

   }


   ::user::interaction * interaction::get_next_sibling_window()
   {

      auto pparent = get_parent_window();

      if (pparent == nullptr)
      {

         return nullptr;

      }

      auto puserinteractionpointeraChild = pparent->m_puserinteractionpointeraChild;

      ::index iFind = puserinteractionpointeraChild->find_first_interaction(this);

      if (iFind + 1 >= puserinteractionpointeraChild->interaction_count())
      {

         return nullptr;

      }

      return puserinteractionpointeraChild->interaction_at(iFind + 1);

   }


   ::user::interaction *
      interaction::get_next_window(bool bIgnoreChildren, const ::user::interaction * puserinteractionStop) const
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

      if (iFind < 0)
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


   ::user::interaction * interaction::get_window(enum_next enext) const
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


   bool interaction::is_message_only_window() const
   {

      return m_bMessageWindow;

   }


   ::user::interaction * interaction::get_wnd(::u32 nCmd) const
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


   //bool interaction::SetFocus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->SetFocus();

   //}


   //::user::primitive * interaction::get_keyboard_focus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->get_keyboard_focus();

   //}


   //::user::interaction * interaction::SetActiveWindow()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   return m_pprimitiveimpl->SetActiveWindow();

   //}


   //bool interaction::SetForegroundWindow()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->SetForegroundWindow();

   //}


   ::user::interaction * interaction::GetLastActivePopup()
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


   void interaction::insert_text(string str, bool bForceNewStep, const ::action_context & context)
   {

      auto strText = get_window_text();

      strsize iBeg = strText.get_length();

      strsize iEnd = strText.get_length();

      _001GetSel(iBeg, iEnd);

      strText.translate_index(iBeg);

      strText.translate_index(iEnd);

      strText.replace(iBeg, iEnd, strText);

      if (m_pappearance)
      {

         auto psz = strText.c_str();

         while (*psz)
         {

            string strUtf8Character = ::str().get_utf8_char(psz);

            auto iCharacter = ::str::ch().uni_index(strUtf8Character);

            m_pappearance->on_character(iCharacter);

            psz += strUtf8Character.length();

         }

      }

   }


   void interaction::set_window_text(const ::string & pszString)
   {

      m_strWindowText = pszString;

      if (m_pprimitiveimpl != nullptr)
      {

         m_pprimitiveimpl->set_window_text(pszString);

      }

      set_need_layout();

      set_need_redraw();

   }


   strsize interaction::get_window_text(char * pszStringBuf, strsize nMaxCount)
   {

      strsize n = minimum(nMaxCount, m_strWindowText.get_length());

      ansi_count_copy(pszStringBuf, m_strWindowText, n);

      return n;

   }


   string interaction::get_window_text()
   {

      string str;

      get_window_text(str);

      return str;

   }


   void interaction::get_window_text(string & rectangleString)
   {

      synchronous_lock synchronouslock(mutex());

      rectangleString = m_strWindowText;

   }


   strsize interaction::get_window_text_length()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_pprimitiveimpl == nullptr)
      {

         return 0;

      }

      return m_pprimitiveimpl->get_window_text_length();

   }





   //::user::interaction * interaction::EnsureTopLevel()
   //{

   //   __pointer(interaction) pwindow = get_top_level();

   //   ENSURE_VALID(pwindow);

   //   return pwindow;

   //}


   ::user::frame * interaction::frame() const
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

            return pinteraction->cast<::user::frame>();

         }

         pinteraction = pinteraction->get_parent_window();

      } while (pinteraction != nullptr);

      return nullptr;

   }


   ::user::frame * interaction::_parent_frame() const
   {

      ::user::interaction * pinteraction = get_parent_window();

      if (pinteraction == nullptr)
      {

         return nullptr;

      }

      return pinteraction->frame();

   }


   ::user::interaction * interaction::_top_level() const
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


   ::user::frame * interaction::_top_level_frame() const
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


   void interaction::destroy_composites()
   {

      //auto estatus = 

      ::object::destroy_composites();

      //return estatus;

   }


   void interaction::start_destroying_window()
   {

      auto type = __object_type(*this);

      if (type.name_contains("main_frame"))
      {

         output_debug_string("main_frame start_destroying_window\n");

      }

      if (is_destroying())
      {

         return;

      }

      set_destroying();

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
      m_useritema.destroy_all();
      // tasks should not be destroyed in destroy
      //m_pform && m_pform != this && m_pform->destroy();
      if (m_palphasource) m_palphasource->destroy();
      if (m_pdrawableBackground) m_pdrawableBackground->destroy();
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
      m_playout.release();
      m_pgraphicscalla.release();
      m_puserinteractionCustomWindowProc.release();
      m_puiLabel.release();
      m_useritema.erase_all();
      m_pform.release();
      m_palphasource.release();
      m_pdrawableBackground.release();
      m_pprimitiveimpl.release();
      m_pinteractionimpl.release();
      m_puserinteractionpointeraOwned.release();
      m_puserinteractionpointeraChild.release();
      m_ptooltip.release();
      m_pmenuitem.release();
      m_menua.erase_all();


      // references
      __release(m_pitemComposing);
      __release(m_pthreadUserInteraction);
      m_puserinteractionParent.release();
      m_pupdowntarget.release();
      m_ptaskModal.release();
      m_puserinteractionOwner.release();

      //return ::success;

   }


   void interaction::post_non_client_destroy()
   {

      {

         synchronous_lock synchronouslock(mutex());

         try
         {

            erase_all_routes();

         }
         catch (...)
         {

         }

      }

      set(e_flag_task_ready);

      set(e_flag_task_terminated);

      if (::is_set(m_pobjectParentTask))
      {

         m_pobjectParentTask->erase_task(this);

      }

      if (::is_set(m_pthreadUserInteraction))
      {

         auto pthread = m_pthreadUserInteraction.cast<thread>();

         if (pthread->m_pimpl == m_pinteractionimpl)
         {

            pthread->set_finish();

            //pthread->m_pprimitiveimpl.release();

            //pthread->finish();

         }

         if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
         {

            m_pthreadUserInteraction->m_puiptraThread->erase(this);

         }

         __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

      }

      auto type = __object_type(*this);

      if (type.name_contains("main_frame"))
      {

         output_debug_string("main_frame post_non_client_destroy");

      }

      ///::channel::on_finish();

      ::user::primitive::post_non_client_destroy();

      m_pprimitiveimpl.release();

      m_pinteractionimpl.release();

   }


   bool interaction::is_ready_to_quit() const
   {

      bool bShouldContinue = task_get_run();

      return !bShouldContinue && has(e_flag_task_ready);

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


   //void interaction::CalcWindowRect(RECTANGLE_I32 * prectangle, ::u32 nAdjustType)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return;

   //   }

   //   return m_pprimitiveimpl->CalcWindowRect(prectangle, nAdjustType);

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
      RECTANGLE_I32 * prectParam, const ::rectangle_i32 & rectangleClient, bool bStretch)
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

      SIZEPARENTPARAMS sizeparentparams;

      __pointer(::user::interaction) puiLeft;

      sizeparentparams.bStretch = bStretch;

      sizeparentparams.sizeTotal.cx = sizeparentparams.sizeTotal.cy = 0;

      if (rectangleClient != nullptr)
      {

         sizeparentparams.rectangle = rectangleClient;

      }
      else
      {

         get_input_client_area(&sizeparentparams.rectangle);

      }

      if (::is_empty(sizeparentparams.rectangle))
      {

         return;

      }

      __pointer(::user::interaction) pinteraction;

      while (m_puserinteraction->get_child(pinteraction))
      {

         atom atom = pinteraction->GetDlgCtrlId();

         if (atom == idLeft)
         {

            puiLeft = pinteraction;

         }
         else
         {

            pinteraction->send_message(e_message_size_parent, 0, (lparam)&sizeparentparams);

         }

      }

      if ((nFlags & ~reposNoPosLeftOver) == reposQuery)
      {

         ASSERT(prectParam != nullptr);

         if (bStretch)
         {

            ::copy(prectParam, &sizeparentparams.rectangle);

         }
         else
         {

            prectParam->left = prectParam->top = 0;

            prectParam->right = sizeparentparams.sizeTotal.cx;

            prectParam->bottom = sizeparentparams.sizeTotal.cy;


         }

         return;

      }


      if (!idLeft.is_empty() && puiLeft != nullptr)
      {

         if ((nFlags & ~reposNoPosLeftOver) == reposExtra)
         {

            ASSERT(prectParam != nullptr);


            sizeparentparams.rectangle.left += prectParam->left;

            sizeparentparams.rectangle.top += prectParam->top;

            sizeparentparams.rectangle.right -= prectParam->right;

            sizeparentparams.rectangle.bottom -= prectParam->bottom;


         }

         if ((nFlags & reposNoPosLeftOver) != reposNoPosLeftOver)
         {

            //puiLeft->CalcWindowRect(&sizeparentparams.rectangle);

            puiLeft->place(sizeparentparams.rectangle);

            puiLeft->display();

            puiLeft->set_need_layout();

         }

      }

   }


   ::user::primitive * interaction::set_owner(::user::primitive * pprimitive)
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

      ::user::primitive * puiRet = m_pprimitiveimpl->set_owner(pprimitive);

      if (m_ewindowflag & e_window_flag_satellite_window)
      {

         __refer(m_pthreadUserInteraction, m_puserinteractionOwner->m_pthreadUserInteraction
            OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

      }

      on_set_owner(m_puserinteractionOwner);

      return puiRet;

   }


   void interaction::on_add_owned(::user::primitive * pprimitive)
   {

      __defer_construct_new(m_puserinteractionpointeraOwned);

      m_puserinteractionpointeraOwned->add_primitive(pprimitive);

   }


   ::user::interaction * interaction::get_owner() const
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


   ::user::frame * interaction::get_owner_frame() const
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


   ::user::interaction * interaction::get_parent_owner() const
   {

      __pointer(::user::interaction) puserinteractionParent = get_parent();

      if (puserinteractionParent.is_null())
      {

         return nullptr;

      }

      return puserinteractionParent->get_owner();

   }


   ::user::interaction * interaction::get_parent_or_owner() const
   {

      __pointer(::user::interaction) puserinteractionParent = get_parent();

      if (puserinteractionParent.is_set())
      {

         return puserinteractionParent;

      }

      return get_owner();

   }


   ::user::interaction * interaction::get_top_level_owner() const
   {

      __pointer(::user::interaction) puiOwner = get_owner();

      __pointer(::user::interaction) puiTopLevelOwner;

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


   void interaction::viewport_client_to_screen(POINT_I32 * ppt)
   {

      m_pprimitiveimpl->viewport_client_to_screen(ppt);

   }


   bool interaction::window_is_notify_icon_enabled()
   {

      return false;

   }


   void interaction::viewport_screen_to_client(POINT_I32 * ppt)
   {

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->viewport_screen_to_client(ppt);

   }


   void interaction::viewport_client_to_screen(RECTANGLE_I32 * prectangle)
   {

      viewport_client_to_screen((POINT_I32 *)&prectangle->left);

      viewport_client_to_screen((POINT_I32 *)&prectangle->right);

   }


   void interaction::viewport_screen_to_client(RECTANGLE_I32 * prectangle)
   {

      viewport_screen_to_client((POINT_I32 *)&prectangle->left);

      viewport_screen_to_client((POINT_I32 *)&prectangle->right);

   }


   //bool interaction::layout().is_zoomed()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return false;

   //   }

   //   return m_pprimitiveimpl->layout().is_zoomed();

   //}


   ::e_display interaction::window_stored_display() const
   {

      return e_display_none;

   }


   ::e_display interaction::window_previous_display() const
   {

      return e_display_none;

   }


   bool interaction::is_full_screen_enabled() const
   {

      return true;

   }


   bool interaction::_is_full_screen() const
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

      if(m_bPendingZorder)
      {

         return true;

      }

      if (m_puserinteractionpointeraChild)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild.get();

         for (auto & pchild : puserinteractionpointeraChild->interactiona())
         {

            if (pchild->layout().sketch().zorder().is_change_request())
            {

               m_bPendingZorder = true;

            }

         }

      }

      return m_bPendingZorder;

   }


   zorder interaction::zorder(enum_layout elayout) const
   {

      return const_layout().state(elayout).zorder();

   }


   void interaction::order(::zorder zorder)
   {

      layout().sketch() = zorder;

   }


   void interaction::_001OnAfterAppearance()
   {


   }


   bool interaction::should_save_window_rect()
   {

      return false;

   }


   void interaction::WindowDataSaveWindowRect()
   {

      //return false;

   }


   bool interaction::WindowDataLoadWindowRect()
   {

      return false;

   }


   bool interaction::FancyWindowDataLoadWindowRect(bool bForceRestore, bool bInitialFramePosition)
   {

      return false;

   }


   void interaction::on_defer_display()
   {

   }


   bool interaction::display_sketch_to_design()
   {

      auto type = __object_type(*this);

      if (type.name_contains("page_home"))
      {

         INFORMATION("page_home");

      }

      auto edisplayDesign = layout().design().display();

      auto edisplaySketch = layout().sketch().display();

      auto eactivationSketch = layout().sketch().activation();

      bool bDisplay =
         edisplaySketch != edisplayDesign
         || eactivationSketch & e_activation_under_mouse_cursor
         || eactivationSketch & e_activation_display_change;

      if (bDisplay)
      {

         design_display();

      }

      return bDisplay;

   }


   void interaction::design_restored()
   {

      design_window_restore(e_display_restored);

   }


   void interaction::design_iconic()
   {
      
      if (get_parent() != nullptr)
      {

         WARNING("iconify child window?");

         layout().sketch() = e_display_restored;

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

      auto edisplaySketch = layout().sketch().display();

      if (edisplaySketch == ::e_display_full_screen)
      {

         if (!is_top_level_window())
         {

            WARNING("full screen child window?");

            layout().sketch() = e_display_restored;

         }
         else
         {

            design_window_full_screen(layout().sketch().parent_client_rect());

         }

      }
      else if (edisplaySketch == ::e_display_iconic)
      {

         design_iconic();

      }
      else if (edisplaySketch == ::e_display_zoomed)
      {

         if (get_parent() != nullptr)
         {

            WARNING("zooming child window?");

            layout().sketch() = e_display_restored;

         }
         else
         {

            design_window_maximize();

         }

      }
      else if (edisplaySketch == ::e_display_restore)
      {
         
         if (get_parent() != nullptr)
         {

            WARNING("restoring child window?");

            layout().sketch() = e_display_restored;

         }
         else
         {

            design_window_restore(edisplaySketch);

         }
         
      }
      else if(edisplaySketch == ::e_display_restored)
      {
         
         INFORMATION("::user::interaction::design_display e_display_restored");
         
      }
      else if(edisplaySketch == ::e_display_compact
         || edisplaySketch == ::e_display_broad)
      {

         if (get_parent() != nullptr)
         {

            WARNING("restoring child window?");

            layout().sketch() = e_display_restored;

         }
         else
         {

            design_window_restore(edisplaySketch);

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

            layout().sketch() = e_display_restored;

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

            INFORMATION("hiding child window");

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


   CLASS_DECL_AURA void zorder_sort(::user::interaction_array & uia)
   {

      auto predZ = [](auto & pui1, auto & pui2)
      {

         if (!pui1 || !pui2)
         {

            return false;

         }

         return (bool) (pui1->const_layout().sketch().zorder() < pui2->const_layout().sketch().zorder());

      };

      uia.interactiona().predicate_sort(predZ);

   }


   void interaction::design_zorder()
   {

      //      ui_state().m_zorder = process_state().m_zorder;

      //    if (get_parent() != NULL)
      {

         //synchronous_lock slChildren(::user::mutex_children());

         //string strType = __type_name(this);

         auto puiptraChildNew = __new(::user::interaction_array(*m_puserinteractionpointeraChild));

         //auto & uiptra = m_uiptraChild;

         //zorder_pre_order(uiptra);

         zorder_sort(*puiptraChildNew);

         m_puserinteractionpointeraChild = puiptraChildNew;

         int iZOrder = 1024;

         bool bSetRequest = false;

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
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

         INFORMATION("tap prodevian_reposition (" << this->screen_origin().x << ", " << this->screen_origin().y << ")");
      }

      if (bRepositionThis)
      {

         auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

         if (puserinteractionpointeraChild)
         {

            for (auto & pinteraction : puserinteractionpointeraChild->interactiona())
            {

               pinteraction->set_reposition(true);

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


   void interaction::design_layout(::draw2d::graphics_pointer & pgraphics)
   {

      synchronous_lock synchronouslock(mutex());

      if (!m_pprimitiveimpl || !m_pprimitiveimpl->m_puserinteraction)
      {

         return;

      }

      //if(m_pinteractiondraw2d)
      {

         //m_pshapeaClip.release();

      }

      m_bClipRectangle = false;

      defer_graphics(pgraphics);

      m_pprimitiveimpl->on_layout(pgraphics);

      on_layout(pgraphics);

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->perform_layout(pgraphics);

      }

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (puserinteractionpointeraChild)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         auto children = puserinteractionpointeraChild->m_interactiona;

         for (auto & pinteraction : children)
         {

            try
            {

               __pointer(::aura::application) papp = get_app();

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


      //if (::is_set(m_playout))
      //{

      //   if (m_playout->m_bFillParent)
      //   {

      //      ::rectangle_i32 rectangleClient;

      //      get_client_rect(rectangleClient);

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


   void interaction::CenterWindow(::user::interaction * pAlternateOwner)
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


   void interaction::pre_translate_message(::message::message * pmessage)
   {

      if (pmessage->m_uiMessageFlags & 1)
      {

         // message already pre translated
         return;

      }

      //auto psession = get_session()->m_paurasession;

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

      primitive_impl * pprimitiveimpl = m_pprimitiveimpl;

      bool bDestroying = pprimitiveimpl->is_destroying();

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


   void interaction::update_dialog_controls(channel * pTarget)
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


   bool interaction::GetUpdateRect(RECTANGLE_I32 * prectangle, bool bErase)
   {

      //if (m_pprimitiveimpl == nullptr)
      //{

      //   return false;

      //}

      //return m_pprimitiveimpl->GetUpdateRect(prectangle, bErase);

      return false;

   }


   i32 interaction::GetUpdateRgn(::draw2d::region * pRgn, bool bErase)
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


   void interaction::InvalidateRect(const ::rectangle_i32 & rectangle, bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->InvalidateRect(rectangle, bErase);

   }


   void interaction::InvalidateRgn(::draw2d::region * pRgn, bool bErase)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->InvalidateRgn(pRgn, bErase);

   }


   void interaction::ValidateRect(const ::rectangle_i32 & rectangle)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->ValidateRect(rectangle);

   }


   void interaction::ValidateRgn(::draw2d::region * pRgn)
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


   void interaction::on_configuration_change(::user::primitive * pprimitiveSource)
   {

      if (m_pprimitiveimpl)
      {

         m_pprimitiveimpl->on_configuration_change(pprimitiveSource);

      }

   }


   ::size_f64 interaction::_001CalculateFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_font(this, ::e_element_none);

      ::write_text::text_metric metric;

      pgraphics->get_text_metrics(&metric);

      ::size_f64 setFittingFontHeight;

      string str;

      get_window_text(str);

      ::size_f64 size = pgraphics->get_text_extent(str);

      setFittingFontHeight.cx = size.cx;

      setFittingFontHeight.cy = metric.get_line_spacing();

      return setFittingFontHeight;

   }


   ::size_f64 interaction::_001CalculateAdjustedFittingSize(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      ::rectangle_f64 rectanglePadding = get_padding(pstyle);

      auto sizeFitting = _001CalculateFittingSize(pgraphics);

      ::size_f64 sizePaddedFitting;

      sizePaddedFitting.cx = rectanglePadding.left + sizeFitting.cx + rectanglePadding.right;

      sizePaddedFitting.cy = rectanglePadding.top + sizeFitting.cy + rectanglePadding.bottom;

      return sizePaddedFitting;

   }


   ::user::enum_state interaction::get_user_state() const
   {

      if (!is_window_enabled())
      {

         return ::user::e_state_disabled;

      }
      else
      {

         auto psession = get_session();

         if (has_hover() && (::is_set(m_pitemHover) || psession->m_puiLastLButtonDown == this))
         {

            return ::user::e_state_hover;

         }
         else
         {

            return ::user::e_state_none;

         }

      }

   }


   bool interaction::has_hover() const
   {

      return has_link();

   }


   bool interaction::has_link() const
   {

      return false;

   }


   void interaction::on_layout(::draw2d::graphics_pointer & pgraphics)
   {

      layout_tooltip();

      on_change_view_size(pgraphics);

      //if(m_pinteractiondraw2d)
      {

         m_pathFocusRect1.release();
         m_pathFocusRect2.release();
         m_pathFocusRect3.release();
         m_pathFocusRect4.release();

      }

      for (auto & puseritem : m_useritema)
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

      //         get_client_rect(pitem->m_rectangle);

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

      //         get_client_rect(pitem->m_rectangle);

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

      //         get_client_rect(pitem->m_rectangle);

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


   void interaction::on_visual_applied()
   {

      clear_visual_changed();

      if (m_pinteractionimpl)
      {

         m_pinteractionimpl->on_visual_applied();

      }


   }


   void interaction::on_reposition()
   {

      //if(m_pinteractiondraw2d)
      //{

      //   m_pshapeaClip.release();

      //}

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


   void interaction::window_show_change_visibility()
   {

      //::enum_display edisplayOutput = layout().output().display();
      ::enum_display edisplayOutput = layout().design().display();

      ::enum_display edisplayWindow = layout().window().display();

      if (is_equivalent(edisplayOutput, e_display_restored))
      {

         edisplayOutput = e_display_restored;

      }

      if (is_equivalent(edisplayWindow, e_display_restored))
      {

         edisplayWindow = e_display_restored;

      }

      ::enum_display edisplayOutputForOsShowWindow = edisplayOutput;

      ::enum_display edisplayWindowForOsShowWindow = edisplayWindow;

      if (::is_docking_appearance(edisplayOutputForOsShowWindow))
      {

         edisplayOutputForOsShowWindow = e_display_restored;

      }

      if (::is_docking_appearance(edisplayWindowForOsShowWindow))
      {

         edisplayWindowForOsShowWindow = e_display_restored;

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


   void * interaction::get_os_data() const
   {

      return window()->get_os_data();

   }


   //void interaction::clear_cache(bool bRecursive) const
   //{
   //
   //   __zero(m_cache);

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

      display(e_display_restored);

   }


   atom interaction::run_modal_loop(::user::interaction * pinteraction, u32 dwFlags)
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

      __keep(m_bModal);

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

      //psystem->post_to_all_threads(WM_KICKIDLE, 0, 0);

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

         m_atomResult = idResult;

         m_estatus = ::success;

      }

      post_message(e_message_close);

      if (::is_set(m_ptaskModal))
      {

         m_ptaskModal->kick_thread();

      }

      if (get_wnd() != nullptr && get_wnd()->m_pthreadUserInteraction.is_set())
      {

         get_wnd()->m_pthreadUserInteraction->kick_thread();

      }

   }


   //   void interaction::route_handling(control_event * pevent)
   //   {
   //
   //      handle(ptopic, pcontext);
   //
   //      if (ptopic->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //      on_notify_control_event(pevent);
   //
   //      if (ptopic->m_bRet)
   //      {
   //
   //         return;
   //
   //      }
   //
   //   }


   //   void interaction::on_notify_control_event(control_event* pevent)
   //   {
   //
   //      auto pusercallback = get_user_callback();
   //
   //      if (pusercallback)
   //      {
   //
   //         pusercallback->handle(ptopic, pcontext);
   //
   //         if (ptopic->m_bRet)
   //         {
   //
   //            return;
   //
   //         }
   //
   //      }
   //
   //      __pointer(::user::interaction) pinteractionBind = get_bind_ui();
   //
   //      if (pinteractionBind && pinteractionBind != pusercallback)
   //      {
   //
   //         pinteractionBind->handle(ptopic, pcontext);
   //
   //         if (ptopic->m_bRet)
   //         {
   //
   //            return;
   //
   //         }
   //
   //      }
   //
   //      auto puiOwner = get_owner();
   //
   //      if (puiOwner && puiOwner != pinteractionBind && puiOwner != pusercallback)
   //      {
   //
   //         puiOwner->route_handling(pevent);
   //
   //         return;
   //
   //      }
   //
   //      auto puserinteractionParent = get_parent();
   //
   //      if (puserinteractionParent && puserinteractionParent != puiOwner && puserinteractionParent != pinteractionBind && puserinteractionParent != pusercallback)
   //      {
   //
   //         puserinteractionParent->route_handling(pevent);
   //
   //         return;
   //
   //      }
   //
   //      auto papp = get_app();
   //
   //      if (papp && papp != pusercallback)
   //      {
   //
   //         papp->route_handling(pevent);
   //
   //         return;
   //
   //      }
   //
   //
   //   }




   void interaction::post_message(const ::atom & atom, wparam wparam, lparam lparam)
   {

      if (m_pprimitiveimpl.is_null())
      {

         //return false;

         return;

      }

      if (atom == e_message_key_down)
      {

         output_debug_string("::user::interaction::post_message e_message_key_down");

      }
      else if (atom == e_message_close)
      {

         output_debug_string("::user::interaction::post_message e_message_close");

      }

      auto type = __object_type(*this);

      if (type.name_contains("list_box"))
      {

         ::output_debug_string("list_box");

      }

      return m_pprimitiveimpl->post_message(atom, wparam, lparam);

   }


   void interaction::post_object(const ::atom & atom, wparam wparam, lparam lparam)
   {

      bool bIsWindow = m_pprimitiveimpl.is_set() && is_window();

      if (atom == e_message_quit || !bIsWindow)
      {

         {

            // discards object
            __pointer(::element) spo(lparam);


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



   void interaction::call_and_set_timer(uptr uEvent, const ::duration & durationElapse, PFN_TIMER pfnTimer)
   {

      if (has(e_flag_destroying))
      {

         return;

      }

      ::timer timer(uEvent);

      _001OnTimer(&timer);

      return SetTimer(uEvent, durationElapse, pfnTimer);

   }


   void interaction::set_timer(uptr uEvent, const ::duration & durationElapse, PFN_TIMER pfnTimer, bool bPeriodic,
      void * pdata)
   {

      if (is_destroying())
      {

         return;

      }

      return SetTimer(uEvent, durationElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::SetTimer(uptr uEvent, const ::duration & durationElapse, PFN_TIMER pfnTimer, bool bPeriodic,
      void * pdata)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      if (is_destroying())
      {

         return;

      }

      return m_pprimitiveimpl->SetTimer(uEvent, durationElapse, pfnTimer, bPeriodic, pdata);

   }


   void interaction::KillTimer(uptr uEvent)
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return;

      }

      m_pprimitiveimpl->KillTimer(uEvent);

   }


   bool interaction::has_keyboard_focus() const
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


   bool interaction::has_mouse_capture() const
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


   bool interaction::is_active_window() const
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

      //      synchronous_lock synchronouslock(mutex());

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


   void interaction::defer_restore(const ::rectangle_i32 & rectangleRequest)
   {

      ::rectangle_i32 rectangleWorkspace;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      index iBestWorkspace = pdisplay->get_best_monitor(rectangleWorkspace, rectangleRequest);

      bool bWindowCrossesWorkspaceBoundaries = !rectangleWorkspace.contains(rectangleRequest);

      bool bWindowLargerThanBroadRestore = rectangleRequest.width() > m_sizeRestoreBroad.cx
         || rectangleRequest.height() > m_sizeRestoreBroad.cy;

      if (bWindowCrossesWorkspaceBoundaries || bWindowLargerThanBroadRestore)
      {

         design_window_restore(e_display_restore);

      }
      else
      {

         //place(rectangle_i32_dimension(10, 10, 800, 300));

         ::rectangle_i32 rectanglePlace(rectangleRequest);

         if (rectanglePlace.size().any_lt(get_window_minimum_size()))
         {

            rectanglePlace.set_size(get_window_minimum_size());

         }

         place(rectanglePlace);

         display(e_display_restored);

      }

   }


   int interaction::get_derived_height(int iWidth)
   {

      return -1;

   }


   int interaction::get_derived_width(int iHeight)
   {

      return -1;

   }


   static i64 g_i_prodevian_update_visual = 0;


   void interaction::sketch_to_design(bool & bUpdateBuffer, bool & bUpdateWindow)
   {

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

      __keep(m_bUpdatingVisual);

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

         layout().m_durationLastSketchToDesign.Now();

      }

      bool bAppearance = layout().sketch().appearance() != layout().design().appearance();


      ::point_i32 pointSketch = layout().sketch().origin();

      ::point_i32 pointDesign = layout().design().origin();

      bool bPosition = pointSketch != pointDesign || m_bReposition;

      m_bReposition = false;

      ::size_i32 sizeSketch = layout().sketch().size();

      ::size_i32 sizeDesign = layout().design().size();

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

      }

      if (bDisplay)
      {

         _001OnExitAppearance();

         layout().design().copy_display(layout().sketch());

      }

      if (bDisplay)
      {

         layout().design().copy_display(layout().sketch());

      }

      if (is_top_level())
      {

         if (layout().sketch().zorder().is_change_request())
         {

            layout().design() = layout().sketch().zorder();

         }

      }

      layout().design() = layout().sketch().appearance();

      layout().sketch().clear_activation();

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

         if (m_ewindowflag & e_window_flag_loading_window_rect)
         {

            INFORMATION(
               "window visual changed: not setting pending save rectangle_i32 cause loading window rectangle_i32");

         }
         else
         {

            m_ewindowflag |= e_window_flag_pending_save_window_rect;

         }

      }

      bool bZorder = check_child_zorder();

      m_bUpdateVisual |= bDisplay || bZorder || bLayout;

      bUpdateBuffer = bLayout;

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

            //__pointer(::user::interaction_impl) pprimitiveimpl = m_pprimitiveimpl;

            //if (pprimitiveimpl)
            //{

            //   pprimitiveimpl->m_re;

            //}

            m_bSketchToDesignLayout = true;

            //design_layout(pgraphics);

         }

         if (bDisplay)
         {

            //output_debug_string(__string(++g_i_prodevian_update_visual) + "updvis dpy machine\n");

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

         _001OnAfterAppearance();

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


   void interaction::add_appearance(eappearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance += eappearance;

   }


   void interaction::erase_appearance(eappearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance -= eappearance;

   }


   void interaction::toggle_appearance(eappearance eappearance, enum_layout elayout)
   {

      m_layout.m_statea[elayout].m_eappearance.toggle(eappearance);

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


   void interaction::_001DeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_pprimitiveimpl != nullptr)
      {

         //         m_pprimitiveimpl->_001DeferPaintLayeredWindowBackground(pgraphics);

      }

   }


   void interaction::_001OnDeferPaintLayeredWindowBackground(::draw2d::graphics_pointer & pgraphics)
   {

      _001DeferPaintLayeredWindowBackground(pgraphics);

   }


   ::oswindow interaction::_oswindow() const
   {

      return oswindow();

   }


   void interaction::OnLinkClick(const ::string & psz, const ::string & pszTarget)
   {

      auto phyperlink = __create_new<::hyperlink>();

      phyperlink->m_strLink = psz;

      phyperlink->m_strTarget = pszTarget;

      phyperlink->run();

      //hyperlink.open_link(psz, "", pszTarget);

   }


   bool interaction::on_set_parent(::user::primitive * puserprimitiveParent)
   {

      auto puserinteractionParent = puserprimitiveParent->cast<::user::interaction>();

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

      __pointer(::user::interaction) puiThis = this;

      //synchronous_lock slChildren(::user::mutex_children());

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

            if (m_pthreadUserInteraction != puserinteractionParent->get_wnd()->m_pthreadUserInteraction)
            {

               if (m_pthreadUserInteraction)
               {

                  if (::is_set(m_pthreadUserInteraction->m_puiptraThread))
                  {

                     m_pthreadUserInteraction->m_puiptraThread->erase(this);

                  }

                  __release(m_pthreadUserInteraction OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS);

               }

               __refer(m_pthreadUserInteraction, puserinteractionParent->get_wnd()->m_pthreadUserInteraction
                  OBJECT_REFERENCE_COUNT_DEBUG_COMMA_THIS_FUNCTION_LINE);

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


   bool interaction::on_add_child(::user::interaction * puserinteractionChild)
   {

      INFORMATION("interaction::on_add_child start\n");

      puserinteractionChild->m_pinteractionScaler = m_pinteractionScaler;

      __pointer(::user::interaction_array) puserinteractionpointeraChildNew;

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

      m_pwindow = _window();
      
#ifdef REPORT_OFFSET

      printf("interaction::on_after_set_parent(2) m_pwindow (0x%x)\n", m_pwindow);

      fflush(stdout);
      
#endif

      m_oswindow = m_pwindow->oswindow();

   }


   bool interaction::on_set_owner(::user::primitive * pprimitive)
   {

      return true;

   }


   void interaction::create_message_queue(const ::string & lpszName)
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
         return;

      if (pmessage->m_bRet)
         return;

      ::user::interaction * puserinteractionParent = get_parent();

      if (puserinteractionParent != nullptr)
         return;

      if (puserinteractionParent == puiStop)
         return;

      try
      {

         puserinteractionParent->pre_translate_message(pmessage);

      }
      catch (...)
      {

      }


   }


   bool interaction::contains_user_interaction(::user::interaction * pinteraction, bool bRecursive) const
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


   double interaction::get_output_fps()
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

      return pinteractionimpl->get_output_fps();

   }


   ::windowing::cursor * interaction::get_mouse_cursor()
   {

      return m_pcursor;

   }


   ::draw2d::graphics_pointer interaction::create_memory_graphics()
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pdraw2d = psystem->draw2d();

      auto pgraphics = pdraw2d->create_memory_graphics(this);

      return pgraphics;

   }


   double interaction::_001GetDefaultFontHeight(::draw2d::graphics_pointer & pgraphics)
   {

      defer_graphics(pgraphics);

      pgraphics->set_font(this, ::e_element_none);

      ::size_f64 size;

      pgraphics->get_text_extent(size, unitext("Ág"));

      return size.cy;

   }


   void interaction::set_mouse_cursor(::windowing::cursor * pcursor)
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


   void interaction::on_message_mouse_enter(::message::message * pmessage)
   {

      pmessage->m_bRet = false;

   }


   //void interaction::on_message_set_cursor(::message::message* pmessage)
   //{

   //   //auto pcursor = get_mouse_cursor();

   //   //if (pcursor)
   //   //{

   //   //   __pointer(::message::set_cursor) psetcursor = pmessage;


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


   ::user::element * interaction::first_child_user_primitive()
   {

      return first_child();

   }


   ::user::element * interaction::top_user_primitive()
   {

      return primitive::top_user_primitive();

   }


   ::user::element * interaction::under_user_primitive()
   {

      return under_sibling();

   }


   ::user::element * interaction::above_user_primitive()
   {

      return above_sibling();

   }


   ::user::element * interaction::next_user_primitive()
   {

      return next_sibling();

   }


   ::user::element * interaction::previous_user_primitive()
   {

      return previous_sibling();

   }


   ::user::interaction * interaction::first_child()
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

   ::user::interaction * interaction::last_child()
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
      try
      {

         ::user::interaction * pinteraction = nullptr;
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

   ::user::interaction * interaction::next_sibling(::user::interaction * pinteraction)
   {
      synchronous_lock synchronouslock(mutex());
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

   ::user::interaction * interaction::previous_sibling()
   {

      try
      {

         ::user::interaction * pinteraction = nullptr;
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


   bool interaction::mouse_hover_erase(::user::interaction * pinterface)
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


   ::user::interaction * interaction::previous_sibling(::user::interaction * pinteraction)
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


   void interaction::get_child_rect(RECTANGLE_I32 * prectangle)
   {

      get_client_rect(prectangle);

   }


   //bool interaction::keyboard_focus_OnChildKillFocus()
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //      return true;


   //   return m_pprimitiveimpl->keyboard_focus_OnChildKillFocus();

   //}


   ::user::interaction * interaction::get_os_focus_uie()
   {

      return nullptr;

   }


   bool interaction::is_ascendant(const primitive * puiIsAscendant, bool bIncludeSelf) const
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return false;

      }

      return m_pprimitiveimpl->is_ascendant(puiIsAscendant, bIncludeSelf);

   }


   bool interaction::is_parent(const primitive * puiIsParent) const
   {

      return m_pprimitiveimpl->is_parent(puiIsParent);

   }


   bool interaction::is_child(const primitive * puiIsChild) const
   {

      return m_pprimitiveimpl->is_child(puiIsChild);

   }


   //bool interaction::is_descendant(const primitive * puiIsDescendant, bool bIncludeSelf) const
   //{

   //   return m_pprimitiveimpl->is_descendant(puiIsDescendant, bIncludeSelf);

   //}


   bool interaction::is_ascendant(const ::user::controller * pcontroller, bool bIncludeSelf) const
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


   bool interaction::contains(const primitive * puiIsChild) const
   {

      return is_child(puiIsChild);

   }


   bool interaction::recursively_contains(const primitive * puiIsChild, bool bIncludeSelf) const
   {

      return is_descendant(puiIsChild, bIncludeSelf);

   }


   ::user::interaction * interaction::get_wnd() const
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
   i32 interaction::get_descendant_level(const ::user::primitive * pinteraction) const
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


   bool interaction::is_descendant(const ::user::primitive * pinteraction, bool bIncludeSelf) const
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


   ::user::interaction * interaction::get_focusable_descendant() const
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


   void interaction::_001OnTriggerMouseInside()
   {

      if (m_pprimitiveimpl != nullptr)
      {

         m_pprimitiveimpl->_001OnTriggerMouseInside();

      }

   }


   void interaction::update_data(bool bSaveAndValidate)
   {

      //return true;

   }


   void interaction::on_message_close(::message::message * pmessage)
   {

      pmessage->m_bRet = true;

      for (auto & pitem : m_useritema)
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

   ::user::interaction::enum_type interaction::get_window_type()
   {
      return type_window;
   }


   //bool interaction::post_simple_command(e_simple_command ecommand,lparam lparam)

   //{

   //   post_message(e_message_simple_command,(wparam)ecommand,lparam);


   //   return true;

   //}

   //void interaction::_001OnCommand(::message::message * pmessage)
   //{

   //   __pointer(::message::message) pmessage(pmessage);

   //   lresult lresult = 0;

   //   pmessage->m_bRet = OnCommand(pmessage);

   //   pmessage->m_lresult = lresult;

   //}


   void interaction::on_message_simple_command(::message::message * pmessage)
   {

      SCAST_MSG(simple_command);

      on_simple_command(psimple_command);

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

      //if (m_pprimitiveimpl != nullptr)
      //{

      //   return m_pprimitiveimpl->OnCommand(pmessage);

      //}

      return false;

   }


   bool interaction::OnNotify(::message::message * pmessage)
   {

      //if (m_pprimitiveimpl != nullptr)
      //{

      //   return m_pprimitiveimpl->OnNotify(pmessage);

      //}

      return false;

   }


   bool interaction::OnChildNotify(::message::message * pmessage)
   {

      if (m_pprimitiveimpl != nullptr)
      {

         return m_pprimitiveimpl->OnChildNotify(pmessage);

      }

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

         __pointer(::user::interaction_impl) pprimitiveimpl = m_pprimitiveimpl;

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

            synchronous_lock synchronouslock(mutex());

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


   void interaction::on_command(::message::command * pcommand)
   {

      ::user::primitive::on_command(pcommand);

   }


   bool interaction::is_selected(::data::item * pitem)
   {

      __UNREFERENCED_PARAMETER(pitem);

      return false;

   }


   //// <3ThomasBorregaardSørensen__!!
   void interaction::handle_command(const ::atom & atom)
   {

      if (m_pmaterialCommandHandler)
      {

         return m_pmaterialCommandHandler->handle_command(atom);

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


   void interaction::_001OnExitIconic()
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

      m_pprimitiveimpl->_001OnExitIconic();

   }


   void interaction::_001OnExitNormal()
   {

      auto rect = layout().window().parent_client_rect();

      layout().normal() = layout().window();

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

   }


   void interaction::_001OnExitZoomed()
   {

      auto rect = layout().window().parent_client_rect();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

   }


   void interaction::_001OnExitFullScreen()
   {

      auto rect = layout().window().parent_client_rect();

      auto edisplay = layout().window().display();

      layout().normal().display() = edisplay;

      bool bProdevian = is_prodevian();

      layout().normal().m_bProdevian = bProdevian;

      if (m_pprimitiveimpl.is_null())
      {

         return;

      }

      m_pprimitiveimpl->_001OnExitFullScreen();

   }


   bool interaction::_001OnBeforeAppearance()
   {

      return true;

   }


   bool interaction::_001OnExitAppearance()
   {

      if (layout().sketch().display() != e_display_none && layout().sketch().display() != e_display_current)
      {

         auto edisplaySketch = layout().sketch().display();

         auto edisplayDesign = layout().design().display();

         if (edisplaySketch != e_display_iconic && edisplayDesign == e_display_iconic)
         {

            _001OnExitIconic();

         }
         else if (edisplaySketch != e_display_zoomed && edisplayDesign == e_display_zoomed)
         {

            _001OnExitZoomed();

         }
         else if (
            !(edisplaySketch == e_display_restore ||
               edisplaySketch == e_display_restored)
            &&
            (edisplayDesign == e_display_restore
               || edisplayDesign == e_display_restored))
         {

            _001OnExitNormal();

         }
         else if (layout().sketch().display() != e_display_full_screen && layout().design().display() == e_display_full_screen)
         {

            _001OnExitFullScreen();

         }

      }

      return true;

   }


   //void interaction::show_keyboard(bool bShow)
   //{

   //   if (m_pprimitiveimpl == nullptr)
   //   {

   //      return;

   //   }

   //   m_pprimitiveimpl->show_keyboard(bShow);

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


   void interaction::place(const ::rectangle_i32 & rectangle, enum_layout elayout)
   {

      bool bOnSetSize = on_set_size(rectangle.size(), elayout);

      bool bOnSetPosition = on_set_position(rectangle.origin(), elayout);

      if (bOnSetSize && bOnSetPosition)
      {

         layout().m_statea[elayout] = rectangle;

      }

   }


   //   void interaction::set_dim(i32 x, i32 y, i32 cx, i32 cy)
   //   {
   //
   //      place(rectangle_i32_dimension(x, y, cx, cy));
   //
   //   }


   interaction & interaction::operator =(const ::rectangle_i32 & rectangle)
   {

      place(rectangle);

      return *this;

   }


   void interaction::activation(::e_activation eactivation)
   {

      layout().sketch() = eactivation;

   }


   void interaction::display_child(const ::rectangle_i32 & rectangle)
   {

      place(rectangle);

      display(e_display_restored);

   }


   ::user::interaction * interaction::best_top_level_parent(RECTANGLE_I32 * prectangle)
   {

      auto ptoplevel = top_level();

      if (!ptoplevel || ptoplevel == this)
      {

         best_monitor(prectangle);

      }
      else
      {

         ptoplevel->get_window_rect(prectangle);

      }

      return ptoplevel;

   }


   ::rectangle_i32 interaction::get_window_rect(enum_layout elayout)
   {

      auto rectangle = get_client_rect();

      client_to_screen(rectangle);

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


   void interaction::design_window_full_screen(const ::rectangle_i32 & rectangleHint)
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


   void interaction::design_window_restore(edisplay edisplay)
   {
      
      auto activation = layout().sketch().activation();

      auto zorder = layout().sketch().zorder();

      auto rectangle = layout().normal().parent_client_rect();

      good_restore(nullptr, rectangle, true, layout().sketch().activation(), layout().sketch().zorder(), edisplay);

   }


   void interaction::design_window_dock(edisplay edisplay)
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

      display(e_display_restore);

   }


   ::user::notify_icon * interaction::notify_icon()
   {

      return nullptr;

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

         display(e_display_restore, e_activation_set_foreground);

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


   void interaction::get_input_client_area(RECTANGLE_I32* lprect)
   {
   
      get_client_rect(lprect);
      
   }

   void interaction::get_client_rect(RECTANGLE_I32 * lprect)
   {

      const_layout().state(e_layout_design).client_rect(lprect);

   }


   ::rectangle_i32 interaction::get_client_rect()
   {

      ::rectangle_i32 r;

      get_client_rect(&r);

      return r;

   }


   index interaction::best_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
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

         get_window_rect(rectangleSample);

      }

      ::rectangle_i32 rectangleNew;

      index iMatchingMonitor = -1;

      if (get_parent() != nullptr)
      {

         get_parent()->get_client_rect(rectangleNew);

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

            iMatchingMonitor = pdisplay->get_best_monitor(rectangleNew, rectangleSample);

         }

      }

      if (bSet && rectangleNew.is_set() && iMatchingMonitor >= 0)
      {

         INFORMATION("interaction::bestmonitor (" << rectangleNew.left << ", " << rectangleNew.top << ", " << rectangleNew.right << ", " << rectangleNew.bottom << ") activation " << (i32)eactivation);

         order(zorderParam);

         place(rectangleNew);

         display(e_display_full_screen, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   index interaction::best_workspace(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         get_window_rect(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_best_monitor(rectangleNew, rectangleWindow, eactivation, window());

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

         display(e_display_zoomed, eactivation | e_activation_display_change);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleWorkspace;


      }

      return iMatchingMonitor;

   }


   index interaction::get_zoneing(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleParam, edisplay edisplay)
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

         ::top_left(prectangle) = point;

         ::bottom_right(prectangle) = point;

      }

      auto sizeMinimum = get_window_minimum_size();

      if (edisplay & ::e_display_top)
      {

         prectangle->move_top_to(rectangleWorkspace.top);

         if (::height(prectangle) < sizeMinimum.cy)
         {

            prectangle->bottom = prectangle->top + sizeMinimum.cy;

         }

      }

      if (edisplay & ::e_display_bottom)
      {

         prectangle->move_bottom_to(rectangleWorkspace.bottom);

         if (::height(prectangle) < sizeMinimum.cy)
         {

            prectangle->top = prectangle->bottom - sizeMinimum.cy;

         }

      }

      if (edisplay & ::e_display_left)
      {

         prectangle->move_left_to(rectangleWorkspace.left);

         if (::width(prectangle) < sizeMinimum.cx)
         {

            prectangle->right = prectangle->left + sizeMinimum.cx;

         }

      }

      if (edisplay & ::e_display_right)
      {

         prectangle->move_right_to(rectangleWorkspace.right);

         if (::width(prectangle) < sizeMinimum.cx)
         {

            prectangle->left = prectangle->right + sizeMinimum.cx;

         }

      }

      return iWorkspace;

   }


   edisplay interaction::initial_restore_display()
   {

      return e_display_restore;

   }


   ::index interaction::get_preferred_restore(RECTANGLE_I32 * prectWorkspace)
   {

      return -1;

   }


   bool interaction::calculate_window_rectangle_in_main_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_f64 & rectangleOptionalRateOrSize)
   {

      ::rectangle_f64 rectangleRate(rectangleOptionalRateOrSize);

      ::rectangle_i32 rectangleMainMonitor;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing1();

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

         rectangleRate.set_dim(100, 100, 800, 400);

      }
      else if (fabs(rectangleRate.left) < 10.0
         && fabs(rectangleRate.right) < 10.0
         && fabs(rectangleRate.bottom) < 10.0
         && fabs(rectangleRate.top) < 10.0)
      {

         rectangleRate *= rectangle_f64(rectangleMainMonitor.width(), rectangleMainMonitor.height(), rectangleMainMonitor.width(), rectangleMainMonitor.height());

      }

      __copy(rectangleWindow, rectangleRate);

      rectangleWindow += rectangleMainMonitor.top_left();

#endif

      * prectangle = rectangleWindow;

      return true;

   }


   index interaction::calculate_broad_and_compact_restore(RECTANGLE_I32 * prectWorkspace, const ::size_i32 & sizeMinParam, const ::rectangle_i32 & rectangleHintParam)
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

      auto pwindowing = puser->windowing1();

      auto pdisplay = pwindowing->display();

      index iMatchingWorkspace = pdisplay->get_best_workspace(& rectangleWorkspace, rectangleHint);

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


   index interaction::make_zoneing(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, edisplay * pedisplay, ::e_activation eactivation, ::zorder zorderParam)
   {

      if (pedisplay == nullptr || !is_docking_appearance(*pedisplay))
      {

         return best_zoneing(prectangle, rectangle, bSet, pedisplay, eactivation, zorderParam);


      }

      ::rectangle_i32 rectangleWindow;

      if (is_empty(rectangle))
      {

         get_window_rect(rectangleWindow);

      }
      else
      {

         rectangleWindow = rectangle;

      }

      ::rectangle_i32 rectangleNew;

      index iMatchingMonitor = get_zoneing(&rectangleNew, rectangleWindow, *pedisplay);

      if (bSet && !is_empty(rectangleNew) && iMatchingMonitor >= 0)
      {

         synchronous_lock slUserMutex(mutex());

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


   index interaction::get_best_zoneing(edisplay & edisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
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


   index interaction::get_best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation)
   {

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      return pdisplay->get_best_workspace(prectangle, rectangle, eactivation, window());

   }


   index interaction::best_zoneing(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, edisplay * pedisplay, ::e_activation eactivation, ::zorder zorderParam)
   {

      edisplay edisplay;

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

         synchronous_lock slUserMutex(mutex());

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
   index interaction::good_restore(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam, edisplay edisplay)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         get_window_rect(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto psession = get_session();

      auto puser = psession->user();

      auto pwindowing = puser->windowing1();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_good_restore(rectangleNew, rectangleWindow, this, edisplay);

      if (bSet)
      {

         {

            //lock_sketch_to_design lockSketchToDesign(this);

            order(zorderParam);

            if (rectangleNew.is_set() && iMatchingMonitor >= 0)
            {

               place(rectangleNew);

            }
            else
            {

               place(rectangleWindow);

            }

            display(e_display_restored, eactivation);

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


   index interaction::good_iconify(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bSet, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         get_window_rect(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_good_iconify(&rectangleNew, rectangleWindow);

      if (bSet && (!::is_empty(rectangleNew) || iMatchingMonitor >= 0))
      {

         synchronous_lock slUserMutex(mutex());

         display(e_display_iconic, eactivation);

      }

      if (prectangle != nullptr)
      {

         *prectangle = rectangleNew;

      }

      return iMatchingMonitor;

   }


   index interaction::good_move(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation, ::zorder zorderParam)
   {

      ::rectangle_i32 rectangleWindow;

      if (!::is_empty(rectangle))
      {

         rectangleWindow = rectangle;

      }
      else
      {

         get_window_rect(rectangleWindow);

      }

      ::rectangle_i32 rectangleNew;

      auto pwindowing = windowing();

      auto pdisplay = pwindowing->display();

      index iMatchingMonitor = pdisplay->get_good_move(rectangleNew, rectangleWindow, this);

      if (!is_empty(rectangleNew) || iMatchingMonitor >= 0)
      {

         order(zorderParam);

         place(rectangleNew);

         display(e_display_restored, eactivation);

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


   atom interaction::SetDlgCtrlId(atom atom)
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


   void interaction::get_rect_normal(RECTANGLE_I32 * prectangle)
   {

      //return 

      m_pprimitiveimpl->get_rect_normal(prectangle);

   }


   scroll_bar * interaction::get_horizontal_scroll_bar()
   {

      return nullptr;

   }


   scroll_bar * interaction::get_vertical_scroll_bar()
   {

      return nullptr;

   }


   scroll_data * interaction::get_horizontal_scroll_data()
   {

      return nullptr;

   }


   scroll_data * interaction::get_vertical_scroll_data()
   {

      return nullptr;

   }


   void interaction::offset_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   {

      auto pointOffset = get_viewport_offset();

      set_viewport_offset(pgraphics, pointOffset.x + x, pointOffset.y + y);

   }


   void interaction::offset_viewport_offset_x(::draw2d::graphics_pointer & pgraphics, int x)
   {

      offset_viewport_offset(pgraphics, x, 0);

   }


   void interaction::offset_viewport_offset_y(::draw2d::graphics_pointer & pgraphics, int y)
   {

      offset_viewport_offset(pgraphics, 0, y);

   }


   void interaction::set_viewport_offset(::draw2d::graphics_pointer & pgraphics, int x, int y)
   {

      ::point_i32 pointOffset(x, y);

      if (pointOffset == m_pointScroll)
      {

         return;

      }

      if (!validate_viewport_offset(pointOffset))
      {

         return;

      }

      m_pointScroll = pointOffset;

      on_change_viewport_offset(pgraphics);

   }


   bool interaction::validate_viewport_offset(point_i32 & point)
   {

      if (point == m_pointScroll)
      {

         return false;

      }

      return true;

   }


   void interaction::set_viewport_offset_x(::draw2d::graphics_pointer & pgraphics, int x)
   {

      set_viewport_offset(pgraphics, x, (::i32)get_viewport_offset().y);

   }


   void interaction::set_viewport_offset_y(::draw2d::graphics_pointer & pgraphics, int y)
   {

      set_viewport_offset(pgraphics, (::i32)get_viewport_offset().x, y);

   }


   void interaction::on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics)
   {

      //set_need_redraw();

      set_reposition();

   }


   point_i32 interaction::get_viewport_offset()
   {

      ::point_i32 point = m_pointScroll;

      return point;

   }


   size_f64 interaction::get_total_size()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.size();

   }

   void interaction::set_total_size(const ::size_f64 & size)
   {

      throw ::interface_only();

   }


   void interaction::set_page_size(const ::size_f64 & size)
   {

      throw ::interface_only();

   }


   void interaction::on_change_view_size(::draw2d::graphics_pointer & pgraphics)
   {

   }


   size_f64 interaction::get_page_size()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.size();

   }


   point_i32 interaction::get_ascendant_viewport_offset() const
   {

      __pointer(::user::interaction) puser = get_parent();

      point_i32 point;

      while (puser.is_set())
      {

         point += puser->get_viewport_offset();

         puser = puser->get_parent();

      }

      return point;

   }


   void interaction::get_margin_rect(RECTANGLE_I32 * prectMargin)
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


   point_i32 interaction::get_parent_viewport_offset() const
   {

      ::user::interaction * puser = get_parent();

      if (puser == nullptr)
      {

         return ::point_i32();

      }

      ::point_i32 pointParentAccumulated;

      if (puser != NULL)
      {

         pointParentAccumulated = puser->get_viewport_offset();

         pointParentAccumulated += puser->get_parent_viewport_offset();

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

      __pointer(::message::show_window) pshowwindow(pmessage);

      if (!layout().design().is_screen_visible()
         || layout().design().m_edisplay == e_display_iconic)
      {

         for (auto & pmenu : m_menua)
         {

            pmenu->hide();

            pmenu->set_need_redraw();

            pmenu->post_redraw();

         }

      }
      else
      {

         for (auto & pmenu : m_menua)
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




   ::graphics::graphics * interaction::get_window_graphics()
   {

      if (m_pprimitiveimpl == nullptr)
      {

         return nullptr;

      }

      return m_pprimitiveimpl->get_window_graphics();

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

   // up down target

   //UpDownTarget::UpDownTarget()
   //{
   //   m_eupdowntargettype = type_normal_frame;
   //}

   void interaction::UpDownTargetAttach(::user::interaction * pupdown)
   {

      bool bAttached = false;

      pupdown->m_eupdown = updown_down;

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

         pupdown->m_eupdown = updown_none;

      }

   }


   void interaction::UpDownTargetDetach(::user::interaction * pupdown)
   {

      bool bDetached = false;

      pupdown->m_eupdown = updown_up;

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

         pupdown->m_eupdown = updown_none;

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



   bool interaction::get_child(__pointer(::user::interaction) & pinteraction)
   {

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->get_child(pinteraction);

   }


   bool interaction::rget_child(__pointer(::user::interaction) & pinteraction)
   {

      //synchronous_lock synchronouslock(mutex());

      auto puserinteractionpointeraChild = m_puserinteractionpointeraChild;

      if (!puserinteractionpointeraChild)
      {

         return false;

      }

      return puserinteractionpointeraChild->rget_child(pinteraction);

   }


   enum_input_type interaction::preferred_input_type() const
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


   void interaction::clear_keyboard_focus(::user::element * pelementGainingFocusIfAny)
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


   bool interaction::is_ascendant_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const
   {

      if (::is_null(puiDescendantCandidate))
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const
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


   bool interaction::is_ascendant_or_owner_of(const ::user::primitive * puiDescendantCandidate, bool bIncludeSelf) const
   {

      if (puiDescendantCandidate == nullptr)
      {

         return false;

      }

      return puiDescendantCandidate->is_descendant_of_or_owned_by(this, bIncludeSelf);

   }


   bool interaction::is_descendant_of_or_owned_by(const ::user::primitive * puiAscendantCandidate, bool bIncludeSelf) const
   {

      const ::user::interaction * pinteraction = bIncludeSelf ? this : get_parent_or_owner();

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


   bool interaction::is_left_button_pressed() const
   {

      auto psession = get_session();

      return psession->m_puiLastLButtonDown == this;

   }


   void interaction::set_current_item(::item * pitem, const ::action_context & context)
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


   void interaction::show_tooltip(const ::string & str, bool bError)
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


   void interaction::handle(::topic * ptopic, ::context * pcontext)
   {

      //auto pevent = pmessage->m_lparam.cast < ::user::control_event >();

      //handle(ptopic, pcontext);

      if (ptopic->m_atom == REDRAW_ID || ptopic->m_atom == m_atom)
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

      //get_window_rect(rectangleThisWindow);

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
      //m_ptooltip->display(e_display_restored, e_activation_no_activate);
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


   bool interaction::has_translucency() const
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
      //         synchronous_lock synchronouslock(mutex());
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

      ::user::interaction * puiTop = get_wnd();

      if (puiTop == nullptr)
      {

         throw ::exception(error_null_pointer);

      }

      synchronous_lock synchronouslock(puiTop->mutex());

      __pointer(::user::interaction_impl) pprimitiveimpl = puiTop->m_pprimitiveimpl;

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


   void interaction::redraw_add(::object * p)
   {

      get_wnd()->m_pprimitiveimpl->redraw_add(p);

   }


   void interaction::redraw_erase(::object * p)
   {

      get_wnd()->m_pprimitiveimpl->redraw_erase(p);

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


   double alpha_source::get_alpha(::user::interaction * puiTarget)
   {

      return 1.0;

   }


   void alpha_source::on_alpha_target_initial_frame_position()
   {


   }


   void interaction::on_after_graphical_update()
   {

      ::user::primitive::on_after_graphical_update();

      if (m_pprimitiveimpl.is_set())
      {

         m_pprimitiveimpl->on_after_graphical_update();

      }

   }


   void interaction::_001OnDeiconify(edisplay edisplay)
   {

      display(e_display_restored);

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


   bool interaction::on_click(::item * pitem)
   {

      auto pappearance = get_appearance();

      if (pappearance)
      {

         if (pappearance->call_click())
         {

            return true;

         }

      }

      if (::is_set(pitem))
      {

         if (pitem->m_eelement == ::e_element_close_button
            || pitem->m_eelement == ::e_element_close_icon)
         {

            post_message(e_message_close);

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

               display(e_display_restored);

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


   bool interaction::on_right_click(::item * pitem)
   {

      return false;

   }


   ::size_f64 interaction::get_size()
   {

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow);

      return rectangleWindow.size();

   }


   ::size_f64 interaction::get_client_size()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.size();

   }


   int interaction::width()
   {

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow);

      return rectangleWindow.width();

   }


   int interaction::height()
   {

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow);

      return rectangleWindow.height();

   }


   int interaction::client_width()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.width();

   }


   int interaction::client_height()
   {

      ::rectangle_i32 rectangleClient;

      get_client_rect(rectangleClient);

      return rectangleClient.height();

   }


   void interaction::resize_to_fit(::draw2d::graphics_pointer & pgraphics)
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

         get_system()->do_events();

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


   void interaction::set_bitmap_source(const string & strBitmapSource)
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

   //   screen_to_client(point);

   //   point += m_ptScroll;


   //}

   //::item interaction::on_hit_test(const ::point_i32& point)
   //{

   //   auto rectangle = this->rectangle(::e_element_client);

   //   if (!rectangle.contains(point))
   //   {

   //      return ::e_element_none;

   //   }

   //   return ::e_element_client;

   //}


   bool interaction::scroll_bar_get_client_rect(RECTANGLE_I32 * prectangle)
   {

      get_client_rect(prectangle);

      prectangle->right += get_final_y_scroll_bar_width();

      prectangle->bottom += get_final_x_scroll_bar_width();

      return true;

   }


   void interaction::on_calc_size(calc_size * psize)
   {

      ::rectangle_i32 rectangleWindow;

      get_window_rect(rectangleWindow);

      psize->m_size = rectangleWindow.size();

   }


   enum_control_type interaction::get_control_type() const
   {

      return m_econtroltype;

   }


   void interaction::show_software_keyboard(::user::element * pelement)
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


   void interaction::hide_software_keyboard(::user::element * pelement)
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


   void interaction::post_procedure(const ::procedure & procedure)
   {

      if (!::is_set(m_pthreadUserInteraction))
      {

         throw ::exception(error_null_pointer);

      }

      m_pthreadUserInteraction->post_procedure(procedure);

   }


#ifdef WINDOWS


   strsize interaction::_009GetWindowText(wchar_t * pwsz, int n)
   {

      wstring wstr(m_strWindowText);

      n = (int)minimum(wstr.get_length() + 1, n);

      wcsncpy(pwsz, wstr.c_str(), n);

      pwsz[n - 1] = '\0';

      return n - 1;

   }


   strsize interaction::_009GetWindowTextLength()
   {
      wstring wstr(m_strWindowText);

      return wstr.get_length();

   }


#else


   strsize interaction::_009GetWindowText(char * psz, int n)
   {

      strncpy(psz, m_strWindowText.c_str(), n);

      psz[n - 1] = '\0';

      return n - 1;

   }


   strsize interaction::_009GetWindowTextLength()
   {

      return m_strWindowText.get_length();

   }


#endif


   void interaction::send_procedure(const ::procedure & procedure)
   {

      ::thread * pthread = get_wnd() == nullptr ? (::thread *) nullptr : get_wnd()->m_pthreadUserInteraction;

      ::task * ptaskCurrent = ::get_task();

      if (pthread == nullptr || pthread == ptaskCurrent)
      {

         return procedure();

      }

      pthread->send_procedure(procedure);

   }


   ::mutex * g_pmutexChildren;


   CLASS_DECL_AURA::mutex * mutex_children()
   {

      return g_pmutexChildren;

   }


   void initialize_children_mutex()
   {

      if (!g_pmutexChildren)
      {

         g_pmutexChildren = new mutex();

      }

   }


   void finalize_children_mutex()
   {

      ::acme::del(g_pmutexChildren);

   }


   //void interaction::get_layout_rect(RECTANGLE_I32 * prectangle)

//{

//   get_window_rect(prectangle);


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

      if (type.name_contains("list_box"))
      {

         output_debug_string("prodevian_redraw list_box");

      }

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
   //         __pointer(interaction) pinteraction = top_child();
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


   bool interaction::is_window_enabled() const
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


   void interaction::on_message_left_button_down(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();
      
      ::output_debug_string("interaction::on_message_left_button_down " + __string(pszType));

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

               set_need_redraw();

               post_redraw();

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

      {

         auto pappearance = get_appearance();

         if (::is_set(pappearance))
         {

            ::point_i32 pointClient;

            _screen_to_client(pointClient, pmouse->m_point);

            auto psession = m_puserinteraction->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            if (pappearance->on_button_down(e_key_left_button, pointClient, ekeyModifiers))
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      m_pitemLButtonDown = update_hover(pmouse);

      if (drag_on_button_down(m_pitemLButtonDown))
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

      if (m_bClickDefaultMouseHandling || m_bHoverDefaultMouseHandling)
      {

         if (::is_set(m_pitemLButtonDown))
         {

            auto psession = get_session();

            psession->m_puiLastLButtonDown = this;

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

   }


   void interaction::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pszType = typeid(*this).name();
      
      ::output_debug_string("interaction::on_message_left_button_up " + __string(pszType));
      
      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         _screen_to_client(pointClient, pmouse->m_point);

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         if (pappearance->on_button_up(e_key_left_button, pointClient, ekeyModifiers))
         {

            pmessage->m_bRet = true;

            return;

         }

      }

      if (!is_window_enabled())
      {

         return;

      }

      if (drag_on_button_up(pmouse))
      {

         return;

      }

      if (pmouse->previous())
      {

         return;

      }

      if (drag_on_button_up(pmouse))
      {

         return;

      }

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

         auto psession = get_session();

         if (m_bClickDefaultMouseHandling)
         {

            auto pitemLeftButtonUp = hit_test(pmouse);

            bool bSameUserInteractionAsMouseDown = psession->m_puiLastLButtonDown == this;

            bool bSameItemAsMouseDown = ::is_same_item(m_pitemLButtonDown, pitemLeftButtonUp);

            //TRACE("interaction::on_message_left_button_up item=" << (int)pitemLeftButtonUp->m_iItem<<", SameUserInteractionAsMsDwn="<< (int) bSameUserInteractionAsMouseDown<<", SameItemAsMsDwn=" << (int) bSameItemAsMouseDown);

            if (::is_set(m_pitemLButtonDown) && bSameUserInteractionAsMouseDown && bSameItemAsMouseDown)
            {

               psession->m_puiLastLButtonDown = nullptr;

               pmessage->m_bRet = on_click(m_pitemLButtonDown);

               INFORMATION("interaction::on_message_left_button_up on_click_ret=" << (int)pmessage->m_bRet);

               if (pmessage->m_bRet)
               {

                  pmouse->m_lresult = 1;

               }
               else
               {

                  ::atom atom;

                  if (m_pitemLButtonDown->m_atom.is_empty())
                  {

                     atom = translate_property_id(m_atom);

                  }
                  else
                  {

                     atom = translate_property_id(m_pitemLButtonDown->m_atom);

                  }

                  if (has_handler())
                  {

                     auto ptopic = create_topic(id_click);

                     ptopic->m_puserelement = this;

                     ptopic->m_pitem = m_pitemLButtonDown;

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

         psession->m_puiLastLButtonDown = nullptr;

         set_need_redraw();

         post_redraw();

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

            ::point_i32 pointClient;

            _screen_to_client(pointClient, pmouse->m_point);

            auto psession = m_puserinteraction->get_session();

            auto ekeyModifiers = psession->key_modifiers();

            if (pappearance->on_button_down(e_key_right_button, pointClient, ekeyModifiers))
            {

               pmouse->m_bRet = true;

               return;

            }

         }

      }

      auto pcontextmenu = __new(::message::context_menu);

      pcontextmenu->set(oswindow(), window(), e_message_context_menu, (wparam)(iptr)oswindow(), pmouse->m_point.lparam());

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

         ::point_i32 pointClient;

         _screen_to_client(pointClient, pmouse->m_point);

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


   void interaction::on_message_middle_button_down(::message::message * pmessage)
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


   void interaction::on_message_mouse_move(::message::message * pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      auto pmouse = pmessage->m_union.m_pmouse;

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         _screen_to_client(pointClient, pmouse->m_point);

         bool bRet;

         //if (pmouse->m_nFlags & MK_LBUTTON)
         //{

         //   bRet = pappearance->on_mouse_drag(pointClient);

         //}
         //else
         //{

         auto psession = m_puserinteraction->get_session();

         auto ekeyModifiers = psession->key_modifiers();

         bRet = pappearance->on_mouse_move(pointClient, ekeyModifiers);

         //         }

         pappearance->m_pointMouseLast = pointClient;

         if (bRet)
         {

            pmessage->m_bRet = true;

            return;

         }

      }


      {

         //synchronous_lock synchronouslock(mutex());

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

         bool bAvoidRedraw = !m_bHoverDefaultMouseHandling;

            update_hover(pmouse, bAvoidRedraw);

            //update_hover(pointCursorClient, false);

            if (::is_set(m_pitemHover))
            {

               if (!m_bMouseHover)
               {

                  m_bMouseHover = true;

                  track_mouse_leave();

                  //auto pappearance = get_appearance();

                  //if (::is_set(pappearance))
                  //{

                  //   ::point_i32 pointClient;

                  //   _screen_to_client(pointClient, pmouse->m_point);

                  //   auto psession = m_puserinteraction->get_session();

                  //   auto ekeyModifiers = psession->key_modifiers();

                  //   pappearance->on_mouse_enter(pointClient, ekeyModifiers);

                  //}

               }

            }

      }

   }


   void interaction::on_message_mouse_wheel(::message::message * pmessage)
   {

      if (!is_window_enabled())
      {

         return;

      }

      __pointer(::message::mouse_wheel) pwheel = pmessage;

      double y = pwheel->GetDelta() / 120.0;

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         ::point_i32 pointClient;

         _screen_to_client(pointClient, pwheel->m_point);

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


   ::item_pointer interaction::update_hover(::user::mouse * pmouse, bool bAvoidRedraw)
   {

      //synchronous_lock synchronouslock(mutex());

      auto pitemHitTest = hit_test(pmouse);

      drag_on_mouse_hover(pitemHitTest);

      bool & bAnyHoverChange = pitemHitTest->m_bAnyHoverChange;

      if (!::is_same_item(pitemHitTest, m_pitemHover))
      {

         g_iMouseHoverCount++;

         m_pitemHover = pitemHitTest;

         bAnyHoverChange = true;

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

      if (m_pitemHover != m_pitemHoverMouse)
      {

         auto pitemOldMouseHover = m_pitemHoverMouse;

         m_pitemHoverMouse = m_pitemHover;

         bAnyHoverChange = true;

         if (::is_set(m_pitemHoverMouse) && !::is_set(pitemOldMouseHover))
         {

            track_mouse_hover();

            //simple_on_control_event(pmouse, e_event_mouse_enter);

         }
         else if (!::is_set(m_pitemHoverMouse) && ::is_set(pitemOldMouseHover))
         {

            //simple_on_control_event(pmouse, e_event_mouse_leave);

         }

         //pmouse->m_bRet = true;

      }

      //}

      if (bAnyHoverChange || (!::is_set(m_pitemHover) || !m_pitemHover->is_drawn()))
      {

         if (!bAvoidRedraw)
         {

            set_need_redraw();

            post_redraw();

         }

      }
      
      
      
      return pitemHitTest;

   }


   void interaction::on_message_mouse_leave(::message::message * pmessage)
   {

      synchronous_lock synchronouslock(mutex());

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->on_mouse_leave();

      }

      auto pitemOldHover = m_pitemHover;

      auto pitemOldHoverMouse = m_pitemHoverMouse;

      m_pitemHover = nullptr;

      m_pitemHoverMouse = nullptr;

      if (pitemOldHover.is_set() || pitemOldHoverMouse.is_set())
      {

         set_need_redraw();

         //simple_on_control_event(pmessage, e_event_mouse_leave);

         post_redraw();

      }

   }


   ::item_pointer interaction::hit_test(::user::mouse * pmouse)
   {

      ::point_i32 pointClient;

      _screen_to_client(pointClient, pmouse->m_point);

      auto pitem = hit_test(pointClient);

      pitem->m_pointScreen = pmouse->m_point;

      pitem->m_pmouse = pmouse;

      return pitem;

   }


   ::item_pointer interaction::hit_test(const ::point_i32 & pointClient)
   {

      auto pitem = on_hit_test(pointClient);

      pitem->m_pointClient = pointClient;

      return pitem;

   }


   ::item_pointer interaction::on_hit_test(const ::point_i32 & point)
   {

      synchronous_lock synchronouslock(mutex());

      auto pointScroll = point + m_pointScroll;

      for (auto & pitem : m_useritema)
      {

         if (pitem->m_ppath)
         {

            auto ppath = pitem->m_ppath;

            auto & pgraphics = pitem->m_pgraphics;

            defer_graphics(pgraphics);

            if (ppath->contains(pgraphics, pointScroll))
            {

               return pitem;

            }

         }
         else
         {

            if (pitem->m_rectangle.contains(pointScroll))
            {

               return pitem;

            }

         }

      }

      auto rectangleResize = this->rectangle(::e_element_resize);

      if (rectangleResize.contains(point))
      {

         auto pitemClient = __new(::item(e_element_resize));

         pitemClient->m_rectangle = rectangleResize;

         return pitemClient;

      }

      auto rectangle = this->rectangle(::e_element_client);

      if (rectangle.contains(point))
      {

         auto pitemClient = __new(::item(e_element_client));

         pitemClient->m_rectangle = rectangle;

         return pitemClient;

      }

      auto pitemNone = __new(::item(e_element_none));

      return pitemNone;

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

   //   get_client_rect(item.m_rectangle);

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


   bool interaction::keyboard_focus_is_focusable() const
   {

      return false;

   }


   void interaction::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      if (m_flagNonClient.has(non_client_background)
         && !(top_level()->frame_is_transparent()))
      {

         draw_control_background(pgraphics);

      }

      if (m_flagNonClient.has(non_client_focus_rect) && keyboard_focus_is_focusable())
      {

         simple_ui_draw_focus_rect(pgraphics);

      }

   }


   void interaction::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      auto pappearance = get_appearance();

      if (::is_set(pappearance))
      {

         pappearance->_001OnDraw(pgraphics);

      }

      //::user::interaction::_001OnDraw(pgraphics);
      if (m_useritema.has_element())
      {

         _001DrawItems(pgraphics);

      }


   }


   void interaction::add_user_item(item * pitem)
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

      m_useritema.add(pitem);

   }


   void interaction::_001DrawItems(::draw2d::graphics_pointer & pgraphics)
   {

      int iCount = 0;

      for (auto & pitem : m_useritema)
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


   void interaction::_001DrawItem(::draw2d::graphics_pointer & pgraphics, ::item * pitem, const ::user::e_state & estate)
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


   //__pointer(::sequence < ::conversation >) interaction::message_box(const ::string& strMessage, const ::string& strTitle, const ::e_message_box& emessagebox)
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

      if (::is_null(m_pprimitiveimpl))
      {

         return;

      }

      m_pprimitiveimpl->edit_on_set_focus(pinteraction);

   }


   void interaction::edit_on_kill_focus(::user::interaction * pinteraction)
   {

      if (::is_null(m_pprimitiveimpl))
      {

         return;

      }

      m_pprimitiveimpl->edit_on_kill_focus(pinteraction);

   }


   void interaction::simple_ui_draw_focus_rect(::draw2d::graphics_pointer & pgraphics)
   {

      auto pstyle = get_style(pgraphics);

      if (pstyle)
      {

         pstyle->simple_ui_draw_focus_rect(this, pgraphics);

      }

   }


   void interaction::get_text_composition_area(::rectangle_i32 & rectangle)
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

         string strCharacter = ::str().get_utf8_char(psz);

         int iCharacter = ::str::ch().uni_index(strCharacter);

         if (m_pappearance)
         {

            m_pappearance->on_character(iCharacter);

         }

         psz += strCharacter.get_length();

         if (strCharacter.get_length() <= 0)
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

   //   if (ptopic->m_atom == REDRAW_ID || ptopic->m_atom == m_atom)
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


   point_i32 interaction::screen_origin(enum_layout elayout) const
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


   point_i32 interaction::host_origin(enum_layout elayout) const
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


   // void interaction::initial_frame_placement()
   // {


   // }


   //bool interaction::_001FancyInitialFramePlacement(bool bForceRestore)
   //{

   //   return false;

   //}

   //    ::rectangle_i32 rectangleWindow;

   //    bool bSet = false;

   //    __pointer(::aura::application) papp = get_app();

   //    if (m_bExtendOnParent ||
   //       (m_bExtendOnParentIfClientOnly && papp->m_bExperienceMainFrame))
   //    {

   //       auto puserinteractionParent = get_parent();

   //       if (puserinteractionParent)
   //       {

   //          puserinteractionParent->get_client_rect(rectangleWindow);

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

   //    display(e_display_restored);

   //    place(rectangleWindow);

   //    set_need_layout();

   //    set_need_redraw();

   //    post_redraw();

   //    return true;

   // }


   // bool interaction::_001FancyInitialFramePlacement(RECTANGLE_I32 * lprect, const rectangle_f64 & rectangleOptionalRateOrSize)
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

      return m_eupdown == updown_up;

   }


   bool interaction::wfi_is_down()
   {

      return m_eupdown == updown_down;

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


   bool interaction::get_data(__pointer(::user::interaction)puserinteraction, ::payload & payload)
   {

      string str;

      if (m_econtroltype == e_control_type_edit)
      {

         __pointer(::user::text) pedit = puserinteraction.m_p;

         if (pedit == nullptr)
            return false;

         pedit->_001GetText(str);

      }
      else
      {

         __pointer(::user::text) ptext = this;

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




   bool interaction::has_function(enum_control_function econtrolfunction) const
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


   ::user::enum_state interaction::get_state() const
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

      __pointer(::user::interaction) puserinteraction = m_puiOther;

      ASSERT(puserinteraction != nullptr);

      ASSERT_KINDOF(::user::interaction, puserinteraction);

      __pointer(::user::interaction) pinteraction = puserinteraction->get_child_by_id(m_atomControl);

      //      //__pointer(control) pcontrolex = (pinteraction.m_p);
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
      /*__pointer(::user::interaction) puserinteraction = (__pointer(::user::interaction))m_pOther;
      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(simple_toolbar, pToolBar);
      ASSERT(m_nIndex < m_nIndexMax);

      ::u32 nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
                  ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
          nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
          nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & e_toolbar_item_style_separator));
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


   string interaction::get_class_style(string strClass)
   {

      if (strClass.is_empty())
      {

         return "";

      }

      if (strClass.find(',') < 0)
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

      if (strClass.find(",") >= 0)
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

            if (strKey.compare_ci("padding") == 0)
            {

               //m_rectanglePadding.left = atoi(strValue);
               //m_rectanglePadding.top = atoi(strValue);
               //m_rectanglePadding.right = atoi(strValue);
               //m_rectanglePadding.bottom = atoi(strValue);


            }
            else if (strKey.compare_ci("cell-padding") == 0)
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

      ::user::primitive::route_command(pcommand);

      if (pcommand->m_bRet)
      {

         return;

      }

      __pointer(::user::interaction) puserinteractionParent = get_parent();

      if (puserinteractionParent)
      {

         puserinteractionParent->route_command(pcommand, false);

      }
      else
      {

         __pointer(::apex::context) pcontext = get_context();

         if (pcontext)
         {

            pcontext->route_command(pcommand);

         }

      }

   }


   void interaction::_001OnEnable(::message::message * pmessage)
   {

      __pointer(::message::enable) penable(pmessage);

      if (m_puiLabel != nullptr)
      {

         m_puiLabel->enable_window(penable->get_enable());

      }

   }


   void interaction::_001OnUpdateEditDelete(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

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


   bool interaction::get_element_rect(RECTANGLE_I32 * prectangle, enum_element eelement)
   {

      if (eelement == e_element_client)
      {

         get_client_rect(prectangle);

         return true;

      }
      else if (eelement == e_element_resize)
      {

         get_client_rect(prectangle);

         prectangle->left = maximum(prectangle->left, prectangle->right - 25);
         prectangle->top = maximum(prectangle->top, prectangle->bottom - 25);

         return true;

      }
      else if (eelement == e_element_drop_down)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         //i32 iMargin = rectangleClient.height() / 8;
         i32 iMargin = 0;

         ::rectangle_i32 rectangleDropDown;

         rectangleDropDown = rectangleClient;

         i32 iW = rectangleClient.height() * 5 / 8;

         rectangleDropDown.right -= iMargin;
         rectangleDropDown.bottom -= iMargin;
         rectangleDropDown.top += iMargin;
         rectangleDropDown.left = rectangleDropDown.right - iW;

         *prectangle = rectangleDropDown;


         return true;

      }
      else if (eelement == e_element_combo_edit)
      {

         ::rectangle_i32 rectangleClient;

         get_client_rect(rectangleClient);

         ::rectangle_i32 rectangleDropDown;

         get_element_rect(rectangleDropDown, e_element_drop_down);

         ::rectangle_i32 rectangleEdit = rectangleClient;

         rectangleEdit.right = rectangleDropDown.left;

         //::rectangle_i32 rectanglePadding = _001GetRect(::user::rect_edit_padding);

         //rectangleEdit.deflate(rectanglePadding);

         *prectangle = rectangleEdit;


         return true;

      }
      else if (eelement == e_element_close_button)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 32;

         prectangle->bottom = prectangle->top + 32;

         return true;

      }
      else if (eelement == e_element_maximize_button)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 64;

         prectangle->right = prectangle->left + 32;

         prectangle->bottom = prectangle->top + 32;

         return true;

      }
      else if (eelement == e_element_minimize_button)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 96;

         prectangle->right = prectangle->left + 32;

         prectangle->bottom = prectangle->top + 32;

         return true;

      }
      else if (eelement == e_element_close_icon)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 48;

         prectangle->bottom = prectangle->top + 48;

         return true;

      }
      else if (eelement == e_element_switch_button)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 48;

         prectangle->top = prectangle->bottom - 48;

         return true;

      }
      else if (eelement == e_element_maximize_icon)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 96;

         prectangle->right = prectangle->left + 48;

         prectangle->bottom = prectangle->top + 48;

         return true;

      }
      else if (eelement == e_element_minimize_icon)
      {

         get_client_rect(prectangle);

         prectangle->left = prectangle->right - 144;

         prectangle->right = prectangle->left + 48;

         prectangle->bottom = prectangle->top + 48;

         return true;

      }


      return false;

   }


   void interaction::get_simple_drop_down_open_arrow_polygon(point_f64_array & pointa)
   {

      ::rectangle_i32 rectangleDropDown;

      get_element_rect(rectangleDropDown, e_element_drop_down);

      i32 cx = rectangleDropDown.width() / 3;

      i32 cy = cx * 2 / 3;

      ::point_i32 pointCenter = rectangleDropDown.center();

      pointa.add(pointCenter.x - cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x + cx / 2, pointCenter.y - cy / 2);

      pointa.add(pointCenter.x, pointCenter.y + cy / 2);

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

   //         if (::str().begins_eat_ci(str, "class="))
   //         {

   //            m_strClass = str;

   //         }
   //         else if (::str().begins_eat_ci(str, "style="))
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
   //   m_datakey = control_descriptor.m_datakey;
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


   bool interaction::has_function(enum_control_function enum_control_function)
   {

      return m_flagsfunction.has(enum_control_function);

   }


   void interaction::set_data_type(enum_control_data_type edatatype)
   {

      m_edatatype = edatatype;

   }


   enum_control_data_type interaction::get_data_type()
   {

      return m_edatatype;

   }


   void interaction::set_ddx_dbflags(::database::key datakey, iptr value)
   {

      m_eddx = ::user::e_control_ddx_dbflags;

      m_datakey = datakey;

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

//            m_data.m_pcombobox = new Ex1FormInterfaceComboBox;

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



} // namespace user



