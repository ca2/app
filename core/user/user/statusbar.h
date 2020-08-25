#pragma once


namespace user
{


   class status_bar_control;   // forward context_object (see afxcmn.h for definition)


   struct __STATUSPANE :
      virtual public object
   {


      ::id              m_id;        // IDC of indicator: 0 => normal text area
      i32               cxText;     // width of string area in pixels
                     //   on both sides there is a 3 pixel gap and
                     //   a one pixel border, making a pane 6 pixels wider
      UINT              nStyle;     // style flags (SBPS_*)
      UINT              nFlags;     // state flags (SBPF_*)
      string            strText;    // text in the pane


      __STATUSPANE & operator = (const __STATUSPANE & pane);
      __STATUSPANE();
      __STATUSPANE(const __STATUSPANE & pane);


   };


   class CLASS_DECL_CORE status_bar :
      public ::user::control_bar
   {
   public:



      pointer_array < __STATUSPANE >     m_panea;
      i32                                    m_nMinHeight;


      status_bar();
      virtual ~status_bar();

      using ::user::control_bar::create_window;
      using ::user::control_bar::create_window_ex;
      virtual bool create_window(::user::interaction * puiParent,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM,id nID = "status_bar");
      virtual bool create_window_ex(::user::interaction * puiParent,u32 dwCtrlStyle = 0,u32 uStyle = WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, id nID = "status_bar");
      bool SetIndicators(string_array & stra);

      void SetBorders(const ::rect & rect);

      void SetBorders(i32 cxLeft = 0, i32 cyTop = 0, i32 cxRight = 0, i32 cyBottom = 0);

      // standard control bar things
      i32 CommandToIndex(id id);
      id GetItemId(i32 nIndex);
      void GetItemRect(i32 nIndex, RECT * prect);


      // specific to status_bar
      void GetPaneText(i32 nIndex, string & rString);
      string GetPaneText(i32 nIndex);
      bool SetPaneText(i32 nIndex, const char * pszNewText, bool bUpdate = TRUE);

      void GetPaneInfo(i32 nIndex, id & id, UINT& nStyle, i32& cxWidth);
      void SetPaneInfo(i32 nIndex, id id, UINT nStyle, i32 cxWidth);
      void SetPaneInfo(i32 nIndex, i32 iId, UINT nStyle, i32 cxWidth);
      void SetPaneInfo(i32 nIndex, const char * pszId, UINT nStyle, i32 cxWidth);
      UINT GetPaneStyle(i32 nIndex);
      void SetPaneStyle(i32 nIndex, UINT nStyle);

      // for direct access to the underlying common control
      status_bar_control& GetStatusBarCtrl();

   // Overridables
#ifdef WINDOWS_DESKTOP
      virtual void DrawItem(LPDRAWITEMSTRUCT);
#endif

      virtual ::size CalcFixedLayout(::draw2d::graphics_pointer& pgraphics, bool bStretch, bool bHorz) override;
      bool pre_create_window(::user::create_struct& cs) override;
      //bool AllocElements(i32 nElements, i32 cbElement);
      void CalcInsideRect(::draw2d::graphics_pointer& pgraphics, ::rect& rect, bool bHorz);
      virtual void OnBarStyleChange(u32 dwOldStyle, u32 dwNewStyle) override;

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      void EnableDocking(u32 dwDockStyle);


      virtual void on_command_probe(::user::frame_window * ptarget, bool bDisableIfNoHndler) override;


      __STATUSPANE * _GetPanePtr(index nIndex);
      void UpdateAllPanes(bool bUpdateRects, bool bUpdateText);
      virtual bool OnChildNotify(::message::base * pbase) override;

      DECL_GEN_SIGNAL(_001OnNcHitTest);
      DECL_GEN_SIGNAL(_001OnNcCalcSize);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnWindowPosChanging);
      DECL_GEN_SIGNAL(_001OnSetText);
      DECL_GEN_SIGNAL(_001OnGetText);
      DECL_GEN_SIGNAL(_001OnGetTextLength);
      DECL_GEN_SIGNAL(_001OnSetMinHeight);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void install_message_routing(::channel * pchannel) override;


   };


} // namespace user


// Styles for status bar panes
#define SBPS_NORMAL     0x0000
#define SBPS_NOBORDERS  SBT_NOBORDERS
#define SBPS_POPOUT     SBT_POPOUT
#define SBPS_OWNERDRAW  SBT_OWNERDRAW
#define SBPS_DISABLED   0x04000000
#define SBPS_STRETCH    0x08000000  // stretch to fill status bar
