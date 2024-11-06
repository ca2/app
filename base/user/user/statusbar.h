#pragma once


#include "base/user/user/control_bar.h"


// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar



namespace user
{


   class status_bar_control;   // forward object (see ::windows_definition::cmn.h for definition)


   struct __STATUSPANE :
      virtual public object
   {


      ::atom              m_atom;        // IDC of indicator: 0 => normal text area
      int               cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      ::u32              nStyle;     // style flags (SBPS_*)
      ::u32              nFlags;     // state flags (SBPF_*)
      string            strText;    // text in the pane


      __STATUSPANE & operator = (const __STATUSPANE & pane);
      __STATUSPANE();
      __STATUSPANE(const __STATUSPANE & pane);


   };


   class CLASS_DECL_BASE status_bar :
      public ::user::control_bar
   {
   public:



      pointer_array < __STATUSPANE >     m_panecompositea;
      int                                    m_nMinHeight;


      status_bar();
      ~status_bar() override;

      //using ::user::control_bar::create_window;
      //using ::user::control_bar::create_window_ex;
      //virtual bool create_window(::user::interaction * puiParent,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,atom nID = "status_bar");
      //virtual bool create_window_ex(::user::interaction * puiParent,u32 dwCtrlStyle = 0,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, atom nID = "status_bar");
      //virtual bool create_child(::user)
      bool SetIndicators(string_array & stra);

      void SetBorders(const ::rectangle_i32 & rectangle);

      void SetBorders(int cxLeft = 0, int cyTop = 0, int cxRight = 0, int cyBottom = 0);

      // standard control bar things
      int CommandToIndex(atom atom);
      atom GetItemId(int nIndex);
      void GetItemRect(int nIndex, ::rectangle_i32 * prectangle);


      // specific to status_bar
      void GetPaneText(int nIndex, string & rString);
      string GetPaneText(int nIndex);
      bool SetPaneText(int nIndex, const ::string & pszNewText, bool bUpdate = true);

      void GetPaneInfo(int nIndex, atom & atom, ::u32& nStyle, int& cxWidth);
      void SetPaneInfo(int nIndex, const ::atom & atom, ::u32 nStyle, int cxWidth);
      //void SetPaneInfo(int nIndex, int iId, ::u32 nStyle, int cxWidth);
      //void SetPaneInfo(int nIndex, const ::string & pszId, ::u32 nStyle, int cxWidth);
      ::u32 GetPaneStyle(int nIndex);
      void SetPaneStyle(int nIndex, ::u32 nStyle);

      // for direct access to the underlying common control
      status_bar_control& GetStatusBarCtrl();

//   // Overridables
//#ifdef WINDOWS_DESKTOP
//      virtual void DrawItem(LPDRAWITEMSTRUCT);
//#endif

      virtual ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      bool pre_create_window(::user::system * pusersystem) override;
      //bool AllocElements(int nElements, int cbElement);
      void CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::rectangle_i32& rectangle, bool bHorz);
      virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      void EnableDocking(u32 dwDockStyle);


      void on_command_probe(::user::interaction * puserinteraction, bool bDisableIfNoHndler) override;


      __STATUSPANE * _GetPanePtr(::collection::index nIndex);
      void UpdateAllPanes(bool bUpdateRects, bool bUpdateText);
      virtual bool OnChildNotify(::message::message * pmessage) override;

      DECLARE_MESSAGE_HANDLER(_001OnNcHitTest);
      DECLARE_MESSAGE_HANDLER(on_message_non_client_calculate_size);
      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(_001OnWindowPosChanging);
      DECLARE_MESSAGE_HANDLER(_001OnSetText);
      DECLARE_MESSAGE_HANDLER(_001OnGetText);
      DECLARE_MESSAGE_HANDLER(_001OnGetTextLength);
      DECLARE_MESSAGE_HANDLER(_001OnSetMinHeight);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void install_message_routing(::channel * pchannel) override;


   };


} // namespace user

