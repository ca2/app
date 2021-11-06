#pragma once


namespace user
{


   class status_bar_control;   // forward object (see afxcmn.h for definition)


   struct __STATUSPANE :
      virtual public object
   {


      ::id              m_id;        // IDC of indicator: 0 => normal text area
      i32               cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      ::u32              nStyle;     // style flags (SBPS_*)
      ::u32              nFlags;     // state flags (SBPF_*)
      string            strText;    // text in the pane


      __STATUSPANE & operator = (const __STATUSPANE & pane);
      __STATUSPANE();
      __STATUSPANE(const __STATUSPANE & pane);


   };


   class CLASS_DECL_CORE status_bar :
      public ::user::control_bar
   {
   public:



      pointer_array < __STATUSPANE >     m_panecompositea;
      i32                                    m_nMinHeight;


      status_bar();
      virtual ~status_bar();

      //using ::user::control_bar::create_window;
      //using ::user::control_bar::create_window_ex;
      //virtual bool create_window(::user::interaction * puiParent,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,id nID = "status_bar");
      //virtual bool create_window_ex(::user::interaction * puiParent,u32 dwCtrlStyle = 0,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, id nID = "status_bar");
      //virtual bool create_child(::user)
      bool SetIndicators(string_array & stra);

      void SetBorders(const ::rectangle_i32 & rectangle);

      void SetBorders(i32 cxLeft = 0, i32 cyTop = 0, i32 cxRight = 0, i32 cyBottom = 0);

      // standard control bar things
      i32 CommandToIndex(id id);
      id GetItemId(i32 nIndex);
      void GetItemRect(i32 nIndex, RECTANGLE_I32 * prectangle);


      // specific to status_bar
      void GetPaneText(i32 nIndex, string & rString);
      string GetPaneText(i32 nIndex);
      bool SetPaneText(i32 nIndex, const ::string & pszNewText, bool bUpdate = true);

      void GetPaneInfo(i32 nIndex, id & id, ::u32& nStyle, i32& cxWidth);
      void SetPaneInfo(i32 nIndex, const ::id & id, ::u32 nStyle, i32 cxWidth);
      //void SetPaneInfo(i32 nIndex, i32 iId, ::u32 nStyle, i32 cxWidth);
      //void SetPaneInfo(i32 nIndex, const ::string & pszId, ::u32 nStyle, i32 cxWidth);
      ::u32 GetPaneStyle(i32 nIndex);
      void SetPaneStyle(i32 nIndex, ::u32 nStyle);

      // for direct access to the underlying common control
      status_bar_control& GetStatusBarCtrl();

//   // Overridables
//#ifdef WINDOWS_DESKTOP
//      virtual void DrawItem(LPDRAWITEMSTRUCT);
//#endif

      virtual ::size_i32 CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      bool pre_create_window(::user::system * pusersystem) override;
      //bool AllocElements(i32 nElements, i32 cbElement);
      void CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::rectangle_i32& rectangle, bool bHorz);
      virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;
      void EnableDocking(u32 dwDockStyle);


      virtual void on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler) override;


      __STATUSPANE * _GetPanePtr(index nIndex);
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


// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar
