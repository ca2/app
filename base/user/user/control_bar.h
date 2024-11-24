#pragma once


#include "aura/user/user/interaction.h"
#include "acme/prototype/geometry2d/point.h"
#include "acme/prototype/geometry2d/size.h"
#include "acme/prototype/geometry2d/rectangle.h"


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
   
   BaseControlBarInfo();

   
   unsigned int m_nBarID;      // ID of this bar
   bool m_bVisible;    // visibility of this bar
   bool m_bFloating;   // whether floating or not
   bool m_bHorz;       // orientation of floating dockbar
   bool m_bDockBar;    // true if a dockbar
   int_point m_pointPos;  // topleft int_point of interaction_impl

   unsigned int m_nMRUWidth;   // MRUWidth for Dynamic Toolbars
   bool m_bDocking;    // true if this bar has a DockContext
   unsigned int m_uMRUDockID;  // most recent docked dockbar
   ::int_rectangle m_rectangleMRUDockPos; // most recent docked position
   unsigned int m_dwMRUFloatStyle; // most recent floating orientation
   int_point m_pointMRUFloatPos; // most recent floating position

   void_ptra m_arrBarID;   // bar IDs for bars contained within this one
   ::user::control_bar * m_pBar;    // bar which this refers to (transient)

   //   void Serialize(CArchive& ar, BaseDockState* pDockState);
   bool LoadState(const ::string & pszProfileName, int nIndex, BaseDockState* pDockState);

   bool SaveState(const ::string & pszProfileName, int nIndex);

};


namespace user
{


   class CLASS_DECL_BASE control_bar :
      virtual public ::user::interaction
   {
   public:


      // info about bar (for status bar and toolbar)
//      int m_rectangleBorder.left(), m_rectangleBorder.right();
  //    int m_rectangleBorder.top(), m_rectangleBorder.bottom();
      ::int_rectangle                           m_rectangleBorder;
      int                                       m_cxDefaultGap;         // default gap value
      unsigned int                                     m_nMRUWidth;   // For dynamic resizing.
      bool                                      m_bDockTrack;
      bool                                      m_bFullScreenBar;

      unsigned int                                     m_nStateFlags;

      unsigned int                                       m_dwStyle;
      unsigned int                                       m_dwDockStyle;
      ::pointer<::user::frame_window>    m_pframewindowDockSite;
      BaseDockBar*                              m_pDockBar;
      BaseDockContext *                         m_pDockContext; // used during dragging
      unsigned int                                       m_dwCtrlStyle;



      control_bar();
      virtual ~control_bar();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      // for styles specific to ::user::control_bar
      unsigned int GetBarStyle();
      void SetBarStyle(unsigned int dwStyle);

      bool m_bAutoDelete;

      // getting and setting border space
      void SetBorders(const ::int_rectangle & rectangle);
      void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);
      ::int_rectangle GetBorders();

      ::pointer<::user::frame_window>GetDockingFrame();
      bool IsFloating();
      virtual ::int_size CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz);
      virtual ::int_size CalcDynamicLayout(::draw2d::graphics_pointer& pgraphics, int nLength, unsigned int nMode);

      
      void EnableDocking(unsigned int dwDockStyle);

      // Overridables
      virtual void on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler) = 0;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      virtual void message_handler(::message::message * pmessage) override;


      //virtual void DelayShow(bool bShow);
      virtual bool IsVisible();
      virtual unsigned int RecalcDelayShow(void * pLayoutSIZEPARENTPARAMS);


      virtual bool IsDockBar();
      void destroy_window() override;
      virtual void OnBarStyleChange(unsigned int dwOldStyle, unsigned int dwNewStyle);


      void pre_translate_message(::message::message * pmessage) override;
      bool pre_create_window(::user::system * pusersystem) override;
      void destroy() override;

      virtual void DoPaint(::draw2d::graphics_pointer & pgraphics);
      void DrawBorders(::draw2d::graphics_pointer & pgraphics, ::int_rectangle& rectangle);
      void DrawGripper(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle& rectangle);

      // implementation helpers
      void CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::int_rectangle& rectangle, bool bHorz) const; // adjusts borders etc
      //bool AllocElements(int nElements, int cbElement);
      virtual bool SetStatusText(int nHit);
      void ResetTimer(unsigned int nEvent, const class time & time);
      void EraseNonClient();
      void EraseNonClient(::draw2d::graphics_pointer & pgraphics);

      void GetBarInfo(BaseControlBarInfo* pInfo);
      void SetBarInfo(BaseControlBarInfo* pInfo, ::pointer<::user::frame_window>pFrameWnd);

      void on_timer(::timer * ptimer) override;
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







