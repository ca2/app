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
      index                                  m_iIndex;
      i32                                    m_iState;
      bool                                   m_bInitialized;
      static const i32                       m_iMarging;
      i32                                    m_cxBorder;
      i32                                    m_cyBorder;
      //::rectangle_i32                        m_rectangleClient;
      
      ::count                                m_iPaneCount;


      split_layout();
      ~split_layout() override;


      void install_message_routing(::channel * pchannel) override;

      virtual i32 get_normal_dimension(enum_layout elayout = e_layout_design);
      virtual i32 get_ortogonal_dimension(enum_layout elayout = e_layout_design);

      //void RelayEventSplitBar(index iSplitBar, const ::atom & atom, WPARAM wParam, LPARAM lParam);
      enum_orientation GetSplitOrientation();
      i32 GetMaxPos(index iPane, enum_layout elayout = e_layout_design);
      i32 GetMinPos(index iPane, enum_layout elayout = e_layout_design);
      bool InsertPaneAt(index iIndex, ::user::interaction * puserinteraction, bool bFixedSize, atom idPane = atom());
      bool SetPane(index iIndex, ::user::interaction* puserinteraction, bool bFixedSize, atom idPane = atom());
      bool RemovePaneAt(index iIndex);
      void SetPaneFixedSize(index iIndex, const ::size_i32 & pSize);
      void CalcSplitBarRect(index iIndex, ::rectangle_i32 & rectangle, enum_layout elayout = e_layout_design);

      void CalcPaneRect(i32 nMinPos, i32 nMaxPos, ::rectangle_i32 & rectangle, enum_layout elayout = e_layout_design);

      void CalcPaneRect(index iIndex, ::rectangle_i32 & rectangle, enum_layout elayout = e_layout_design);


      virtual ::user::interaction * get_pane_window(index iPane);
      virtual ::user::place_holder * get_pane_holder(index iPane);
      virtual ::rectangle_i32 & get_pane_rect(index iPane);
      virtual atom get_pane_id(index iPane);
      virtual split_pane * get_pane_by_id(::atom atom);


      virtual ::count get_pane_count();
      virtual ::count get_visible_pane_count();
      virtual bool is_pane_visible(int iPane);

      ::count get_split_count();
      i32 get_position(index iIndex);
      void set_position(index iIndex, i32 nPos);
      void set_position_rate(index iIndex, double dRate, double dMinimumRate = 0.1, double dMaximumRate = 0.9);
      
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;


      i32 GetMaxPos(enum_layout elayout = e_layout_design);
      i32 GetMinPos(enum_layout elayout = e_layout_design);
      i32 GetPos(i32 xPos, i32 yPos);
      void RelayChildEvent(index iIndex, const MESSAGE *  pMsg);


      void SetSplitOrientation(enum_orientation eorientation);

      bool SetPaneCount(::count iPaneCount);

      virtual bool initialize_split_layout();

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      void draw_control_background(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics);


      //::rectangle_i32 hosting_rectangle(::user::enum_layout elayout = ::user::e_layout_design) override;


   };


} // namespace user



