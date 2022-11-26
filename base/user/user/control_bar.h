#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class frame_window;
   class control_bar;


} // namespace user


class BaseDockBar;
class BaseDockContext;
class BaseDockState;

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
      ::pointer<::user::frame_window>    m_pframewindowDockSite;
      BaseDockBar*                              m_pDockBar;
      BaseDockContext *                         m_pDockContext; // used during dragging
      u32                                       m_dwCtrlStyle;



      control_bar();
      virtual ~control_bar();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      // for styles specific to ::user::control_bar
      u32 GetBarStyle();
      void SetBarStyle(u32 dwStyle);

      bool m_bAutoDelete;

      // getting and setting border space
      void SetBorders(const ::rectangle_i32 & rectangle);
      void SetBorders(i32 cxLeft = 0, i32 cyTop = 0, i32 cxRight = 0, i32 cyBottom = 0);
      ::rectangle_i32 GetBorders();

      ::pointer<::user::frame_window>GetDockingFrame();
      bool IsFloating();
      virtual ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz);
      virtual ::size_i32 CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, ::i32 nLength, u32 nMode);

      // Operations
      void EnableDocking(u32 dwDockStyle);

      // Overridables
      virtual void on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler) = 0;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void message_handler(::message::message * pmessage) override;


      //virtual void DelayShow(bool bShow);
      virtual bool IsVisible();
      virtual u32 RecalcDelayShow(void * pLayoutSIZEPARENTPARAMS);


      virtual bool IsDockBar();
      virtual void start_destroying_window() override;
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
      void ResetTimer(::u32 nEvent, const class time & time);
      void EraseNonClient();
      void EraseNonClient(::draw2d::graphics_pointer & pgraphics);

      void GetBarInfo(BaseControlBarInfo* pInfo);
      void SetBarInfo(BaseControlBarInfo* pInfo, ::pointer<::user::frame_window>pFrameWnd);

      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(_001OnCtlColor);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      DECLARE_MESSAGE_HANDLER(_001OnSizeParent);
      DECLARE_MESSAGE_HANDLER(_001OnHelpHitTest);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(_001OnMouseActivate);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      //DECLARE_MESSAGE_HANDLER(on_message_show_window);
      //DECLARE_MESSAGE_HANDLER(_001OnCancelMode);

      //   DECLARE_MESSAGE_HANDLER(_001OnPaint);
      //   virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      void install_message_routing(::channel * pchannel) override;

      friend class ::user::frame_window;
      friend class BaseDockBar;


      void handle(::topic * ptopic, ::context * pcontext) override;



   };


} // namespace user







