#pragma once


namespace user
{


   class split_bar;


   class CLASS_DECL_BASE split_layout :
      virtual public ::user::place_holder_container
   {
   public:


      enum
      {

         stateInitial = 1,
         stateDragging = 2

      };


      class CLASS_DECL_BASE Pane :
         virtual public object
      {
      public:


         id                                  m_id;
         ::rect                              m_rect;
         ::rect                              m_rectClient;
         ::size                              m_sizeFixed;
         bool                                m_bFixedSize;
         __pointer(::user::place_holder)     m_pplaceholder;
         __pointer(::user::impact_data)      m_pimpactdata;


         Pane();


      };


      bool                                   m_bSplitBar;
      __pointer_array(split_bar)             m_splitbara;
      __pointer_array(Pane)                  m_panea;
      e_orientation                          m_eorientationSplit;
      index                                  m_iIndex;
      i32                                    m_iState;
      bool                                   m_bInitialized;
      static const i32                       m_iMarging;
      i32                                    m_cxBorder;
      i32                                    m_cyBorder;

      
      ::count                                m_iPaneCount;


      split_layout();
      virtual ~split_layout();


      virtual void install_message_routing(::channel * pchannel) override;

      virtual i32 get_normal_dimension();
      virtual i32 get_ortogonal_dimension();

      void RelayEventSplitBar(index iSplitBar, UINT message, WPARAM wParam, LPARAM lParam);
      e_orientation GetSplitOrientation();
      i32 GetMaxPos(index iPane);
      i32 GetMinPos(index iPane);
      bool InsertPaneAt(index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, id idPane = id());
      bool SetPane(index iIndex, ::user::interaction* puserinteraction, bool bFixedSize, id idPane = id());
      bool RemovePaneAt(index iIndex);
      void SetPaneFixedSize(index iIndex, SIZE * pSize);
      void CalcSplitBarRect(index iIndex, RECT * prect);

      void CalcPaneRect(i32 nMinPos, i32 nMaxPos, RECT * prect);

      void CalcPaneRect(index iIndex, RECT * prect);


      virtual __pointer(::user::interaction) get_pane_window(index iPane);
      virtual __pointer(::user::place_holder) get_pane_holder(index iPane);
      virtual ::rect & get_pane_rect(index iPane);
      virtual id get_pane_id(index iPane);
      virtual Pane * get_pane_by_id(::id id);


      virtual ::count get_pane_count();
      virtual ::count get_visible_pane_count();
      virtual bool is_pane_visible(int iPane);

      ::count get_split_count();
      i32 get_position(index iIndex);
      void set_position(index iIndex, i32 nPos);
      void set_position_rate(index iIndex, double dRate, double dMinimumRate = 0.1, double dMaximumRate = 0.9);
      
      void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      i32 GetMaxPos();
      i32 GetMinPos();
      i32 GetPos(i32 xPos, i32 yPos);
      void RelayChildEvent(index iIndex, const MESSAGE *  pMsg);


      void SetSplitOrientation(e_orientation eorientation);

      bool SetPaneCount(::count iPaneCount);

      virtual bool initialize_split_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      virtual void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics);


   };


} // namespace user



