#pragma once


#include "acme/platform/enum.h"
#include "acme/primitive/collection/int_map.h"
#include "aura/user/user/interaction.h"


namespace user
{


   class tool_tip_tool;


   class tool_tip_window :
      virtual public ::user::interaction
   {
   public:


      enum e_message
      {
         MessageBaseToolTipText = WM_USER + 110
      };

      enum enum_position
      {
         PositionCenter,
         PositionRandomTopRight
      };




      enum EAlign
      {
         AlignNone = 0,
         AlignLeft = 1,
         AlignRight = 2,
         AlignTop = 4,
         AlignBottom = 8
      };

      typedef base_enum < EAlign, AlignNone > CEnumAlign;

      class CText
      {
      public:
         string m_str;
      };

      class CToolMap :
         public i32_map < ::pointer < tool_tip_tool > >
      {
      public:
          void AddTool(tool_tip_tool * ptool);
      };


      CEnumAlign                 m_ealign;         // current alignment of the tool tip
      CEnumAlign                 m_ealignDefault;  // default alignment of the tool tip
      ::pointer<::user::interaction>   m_puserinteraction;           // window associate with this tool tip wnd
      string                     m_strTip;         // tip string
      i32                        m_iEventTool;     // item selected
      i32                        m_iTool;          // item where the tip will be showed
      ::write_text::font_pointer          m_pfont;           // tip string font
      point_i32                      m_pointOffset;       // tip point_i32 offset
      ::size_i32                     m_sizeArrow;      // arrow size_i32
      bool                       m_bTipEnable;     // set if the tip is enabled

      point_i32                      m_point;             // coordinates fo the cursor position used to track changes in cursor position
      CToolMap                   m_toolmap;        // map of tool index to tool pointers

      tool_tip_window();
      virtual ~tool_tip_window();


      //virtual bool pre_create_window(::user::system * pusersystem) override;


      void RemoveAllTools();
      tool_tip_tool * GetTool(i32 iTool);
      bool GetToolText(i32 iTool, string & str);
      void AddTool(tool_tip_tool * ptool);
      bool GetToolRect(i32 iTool, ::rectangle_i32 * prectangle);

      void update_drawing_objects();
      bool ShowTip();
      bool IsTipEnabled();
      void EnableTip(bool bEnable = true);
      bool HideTip();
      //virtual bool create(::user::interaction * puserinteraction, const atom & atom);
      bool CalcRect(::draw2d::graphics_pointer & pgraphics, ::rectangle_i32 * prectangle, const ::rectangle_i32 & lprectToolScreen, const ::string & pcsz);

      void ShowTip(i32 iTool, bool bForce = false);
      void SetPositionHint(::user::interaction * puserinteraction, enum_position eposition);
      void relay_event(tool_tip_tool * puserinteraction, ::message::message * pmessage);

      void OnPaint();
      void OnTimer(::u32 uEvent);
      void OnSize(::u32 nType, i32 cx, i32 cy);
      void on_destroy() override;


   };


} // namespace user



