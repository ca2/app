#pragma once


namespace user
{


   class frame_window;
   class control_bar;


} // namespace user


class BaseDockBar;
class BaseDockContext;
class BaseDockState;

#define CBRS_DRAGMOVE            0x01000000L
/*#undef CBRS_ALL
#define CBRS_ALL            0x0140ffffL*/





// Standard control bars (IDW = interaction_impl ID)
#define __IDW_CONTROLBAR_FIRST        0xE800
#define __IDW_CONTROLBAR_LAST         0xE8FF

#define __IDW_TOOLBAR                 0xE800  // main Toolbar for interaction_impl
//#define "status_bar"              0xE801  // Status bar interaction_impl
#define __IDW_PREVIEW_BAR             0xE802  // PrintPreview Dialog Bar
#define __IDW_RESIZE_BAR              0xE803  // OLE in-place resize bar
#define __IDW_REBAR                   0xE804  // COMCTL32 "rebar" Bar
#define __IDW_DIALOGBAR               0xE805  // dialogBar

// Note: If your application supports docking toolbars, you should
//  not use the following IDs for your own toolbars.  The IDs chosen
//  are at the top of the first 32 such that the bars will be hidden
//  while in print preview mode, and are not likely to conflict with
//  IDs your application may have used succesfully in the past.

#define __IDW_DOCKBAR_TOP             0xE81B
#define __IDW_DOCKBAR_LEFT            0xE81C
#define __IDW_DOCKBAR_RIGHT           0xE81D
#define __IDW_DOCKBAR_BOTTOM          0xE81E
#define __IDW_DOCKBAR_FLOAT           0xE81F

// Macro for mapping standard control bars to bitmask (limit of 32)
#define __CONTROLBAR_MASK(nIDC)   (1L << (nIDC - __IDW_CONTROLBAR_FIRST))



// on_layout Modes for CalcDynamicLayout
#define LM_STRETCH  0x01    // same meaning as bStretch in CalcFixedLayout.  If set, ignores nLength
// and returns dimensions based on LM_HORZ state, otherwise LM_HORZ is used
// to determine if nLength is the desired horizontal or vertical length
// and dimensions are returned based on nLength
#define LM_HORZ     0x02    // same as bHorz in CalcFixedLayout
#define LM_MRUWIDTH 0x04    // Most Recently Used Dynamic width
#define LM_HORZDOCK 0x08    // Horizontal Docked Dimensions
#define LM_VERTDOCK 0x10    // Vertical Docked Dimensions
#define LM_LENGTHY  0x20    // set if nLength is a height instead of a width
#define LM_COMMIT   0x40    // Remember MRUWidth


#ifndef CCS_TOP

// begin_r_commctrl

//====== COMMON CONTROL STYLES ================================================

#define CCS_TOP                 0x00000001L
#define CCS_NOMOVEY             0x00000002L
#define CCS_BOTTOM              0x00000003L
#define CCS_NORESIZE            0x00000004L
#define CCS_NOPARENTALIGN       0x00000008L
#define CCS_ADJUSTABLE          0x00000020L
#define CCS_NODIVIDER           0x00000040L
#define CCS_VERT                0x00000080L
#define CCS_LEFT                (CCS_VERT | CCS_TOP)
#define CCS_RIGHT               (CCS_VERT | CCS_BOTTOM)
#define CCS_NOMOVEX             (CCS_VERT | CCS_NOMOVEY)

// end_r_commctrl

//====== SysLink control =========================================

#ifdef _WIN32
#if (NTDDI_VERSION >= NTDDI_WINXP)

#define INVALID_LINK_INDEX  (-1)
#define MAX_LINKID_TEXT     48
#define L_MAX_URL_LENGTH    (2048 + 32 + sizeof("://"))

#define WC_LINK         L"SysLink"

// begin_r_commctrl

#define LWS_TRANSPARENT     0x0001
#define LWS_IGNORERETURN    0x0002
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LWS_NOPREFIX        0x0004
#define LWS_USEVISUALSTYLE  0x0008
#define LWS_USECUSTOMTEXT   0x0010
#define LWS_RIGHT           0x0020
#endif // (NTDDI_VERSION >= NTDDI_VISTA)

// end_r_commctrl

#define LIF_ITEMINDEX    0x00000001
#define LIF_STATE        0x00000002
#define LIF_ITEMID       0x00000004
#define LIF_URL          0x00000008

#define LIS_FOCUSED         0x00000001
#define LIS_ENABLED         0x00000002
#define LIS_VISITED         0x00000004
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define LIS_HOTTRACK        0x00000008
#define LIS_DEFAULTCOLORS   0x00000010 // Don't use any custom text colors
#endif

#endif

#endif

#endif


/////////////////////////////////////////////////////////////////////////////
// BaseControlBarInfo - used for docking serialization

class BaseControlBarInfo
{
public:
   // Implementation
   BaseControlBarInfo();

   // Attributes
   ::u32 m_nBarID;      // ID of this bar
   bool m_bVisible;    // visibility of this bar
   bool m_bFloating;   // whether floating or not
   bool m_bHorz;       // orientation of floating dockbar
   bool m_bDockBar;    // true if a dockbar
   point_i32 m_pointPos;  // topleft point_i32 of interaction_impl

   ::u32 m_nMRUWidth;   // MRUWidth for Dynamic Toolbars
   bool m_bDocking;    // true if this bar has a DockContext
   ::u32 m_uMRUDockID;  // most recent docked dockbar
   ::rectangle_i32 m_rectangleMRUDockPos; // most recent docked position
   u32 m_dwMRUFloatStyle; // most recent floating orientation
   point_i32 m_pointMRUFloatPos; // most recent floating position

   void_ptra m_arrBarID;   // bar IDs for bars contained within this one
   ::user::control_bar * m_pBar;    // bar which this refers to (transient)

   //   void Serialize(CArchive& ar, BaseDockState* pDockState);
   bool LoadState(const ::string & pszProfileName, i32 nIndex, BaseDockState* pDockState);

   bool SaveState(const ::string & pszProfileName, i32 nIndex);

};


namespace user
{


   class CLASS_DECL_BASE control_bar :
      virtual public ::user::interaction
   {
   public:


      // info about bar (for status bar and toolbar)
//      i32 m_rectangleBorder.left, m_rectangleBorder.right;
  //    i32 m_rectangleBorder.top, m_rectangleBorder.bottom;
      ::rectangle_i32                           m_rectangleBorder;
      i32                                       m_cxDefaultGap;         // default gap value
      ::u32                                     m_nMRUWidth;   // For dynamic resizing.
      bool                                      m_bDockTrack;
      bool                                      m_bFullScreenBar;

      ::u32                                     m_nStateFlags;

      u32                                       m_dwStyle;
      u32                                       m_dwDockStyle;
      __pointer(::user::frame_window)     m_pframewindowDockSite;
      BaseDockBar*                              m_pDockBar;
      BaseDockContext *                         m_pDockContext; // used during dragging
      u32                                       m_dwCtrlStyle;



      control_bar();
      virtual ~control_bar();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      // for styles specific to ::user::control_bar
      u32 GetBarStyle();
      void SetBarStyle(u32 dwStyle);

      bool m_bAutoDelete;

      // getting and setting border space
      void SetBorders(const ::rectangle_i32 & rectangle);
      void SetBorders(i32 cxLeft = 0, i32 cyTop = 0, i32 cxRight = 0, i32 cyBottom = 0);
      ::rectangle_i32 GetBorders();

      __pointer(::user::frame_window) GetDockingFrame();
      bool IsFloating();
      virtual ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz);
      virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, i32 nLength, u32 nMode);

      // Operations
      void EnableDocking(u32 dwDockStyle);

      // Overridables
      virtual void on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler) = 0;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void message_handler(::message::message * pmessage) override;


      //virtual void DelayShow(bool bShow);
      virtual bool IsVisible();
      virtual u32 RecalcDelayShow(void * pLayoutSIZEPARENTPARAMS);


      virtual bool IsDockBar();
      virtual bool start_destroying_window() override;
      virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle);


      virtual void pre_translate_message(::message::message * pmessage) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;
      virtual void post_non_client_destroy() override;

      virtual void DoPaint(::draw2d::graphics_pointer & pgraphics);
      void DrawBorders(::draw2d::graphics_pointer & pgraphics, ::rectangle_i32& rectangle);
      void DrawGripper(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32& rectangle);

      // implementation helpers
      void CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::rectangle_i32& rectangle, bool bHorz) const; // adjusts borders etc
      //bool AllocElements(i32 nElements, i32 cbElement);
      virtual bool SetStatusText(i32 nHit);
      void ResetTimer(::u32 nEvent, ::u32 nTime);
      void EraseNonClient();
      void EraseNonClient(::draw2d::graphics_pointer & pgraphics);

      void GetBarInfo(BaseControlBarInfo* pInfo);
      void SetBarInfo(BaseControlBarInfo* pInfo, __pointer(::user::frame_window) pFrameWnd);

      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnCtlColor);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      DECLARE_MESSAGE_HANDLER(_001OnSizeParent);
      DECLARE_MESSAGE_HANDLER(_001OnHelpHitTest);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(_001OnCancelMode);

      //   DECLARE_MESSAGE_HANDLER(_001OnPaint);
      //   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void install_message_routing(::channel * pchannel) override;

      friend class ::user::frame_window;
      friend class BaseDockBar;


      virtual void handle(::subject * psubject, ::context * pcontext) override;



   };


} // namespace user







