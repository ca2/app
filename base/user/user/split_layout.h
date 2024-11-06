#pragma once


#include "place_holder_container.h"


namespace user
{


   class split_bar;
   class split_pane;


   class CLASS_DECL_BASE split_layout :
      virtual public ::user::place_holder_container
   {
   public:


      enum
      {

         stateInitial = 1,
         stateDragging = 2

      };


      bool                                   m_bSplitBar;
      pointer_array < split_bar >            m_splitbara;
      ::pointer_array < split_pane >         m_panea;
      enum_orientation                       m_eorientationSplit;
      ::collection::index                                  m_iIndex;
      int                                    m_iState;
      bool                                   m_bInitialized;
      static const int                       m_iMarging;
      int                                    m_cxBorder;
      int                                    m_cyBorder;
      //::int_rectangle                        m_rectangleClient;
      
      ::collection::count                                m_iPaneCount;


      split_layout();
      ~split_layout() override;


      void install_message_routing(::channel * pchannel) override;

      virtual int get_normal_dimension(enum_layout elayout = e_layout_design);
      virtual int get_ortogonal_dimension(enum_layout elayout = e_layout_design);

      //void RelayEventSplitBar(::collection::index iSplitBar, const ::atom & atom, WPARAM wParam, LPARAM lParam);
      enum_orientation GetSplitOrientation();
      int GetMaxPos(::collection::index iPane, enum_layout elayout = e_layout_design);
      int GetMinPos(::collection::index iPane, enum_layout elayout = e_layout_design);
      bool InsertPaneAt(::collection::index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, atom idPane = atom());
      bool SetPane(::collection::index iIndex, ::user::interaction* puserinteraction, bool bFixedSize, atom idPane = atom());
      bool RemovePaneAt(::collection::index iIndex);
      void SetPaneFixedSize(::collection::index iIndex, const ::int_size & pSize);
      void CalcSplitBarRect(::collection::index iIndex, ::int_rectangle & rectangle, enum_layout elayout = e_layout_design);

      void CalcPaneRect(int nMinPos, int nMaxPos, ::int_rectangle & rectangle, enum_layout elayout = e_layout_design);

      void CalcPaneRect(::collection::index iIndex, ::int_rectangle & rectangle, enum_layout elayout = e_layout_design);


      virtual ::user::interaction * get_pane_window(::collection::index iPane);
      virtual ::user::place_holder * get_pane_holder(::collection::index iPane);
      virtual ::int_rectangle & get_pane_rect(::collection::index iPane);
      virtual atom get_pane_id(::collection::index iPane);
      virtual split_pane * get_pane_by_id(::atom atom);


      virtual ::collection::count get_pane_count();
      virtual ::collection::count get_visible_pane_count();
      virtual bool is_pane_visible(int iPane);

      ::collection::count get_split_count();
      int get_position(::collection::index iIndex);
      void set_position(::collection::index iIndex, int nPos);
      void set_position_rate(::collection::index iIndex, double dRate, double dMinimumRate = 0.1, double dMaximumRate = 0.9);
      
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


      int GetMaxPos(enum_layout elayout = e_layout_design);
      int GetMinPos(enum_layout elayout = e_layout_design);
      int GetPos(int xPos, int yPos);
      void RelayChildEvent(::collection::index iIndex, const MESSAGE *  pMsg);


      void SetSplitOrientation(enum_orientation eorientation);

      bool SetPaneCount(::collection::count iPaneCount);

      virtual bool initialize_split_layout();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics);


      //::int_rectangle hosting_rectangle(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace user



