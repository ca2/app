#pragma once


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

      enum e_position
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
         public map < i32, i32, tool_tip_tool *, tool_tip_tool * >
      {
      public:
          void AddTool(tool_tip_tool * ptool);
      };


      CEnumAlign                 m_ealign;         // current alignment of the tool tip
      CEnumAlign                 m_ealignDefault;  // default alignment of the tool tip
      __pointer(::user::interaction)    m_puserinteraction;           // window associate with this tool tip wnd
      string                     m_strTip;         // tip string
      i32                        m_iEventTool;     // item selected
      i32                        m_iTool;          // item where the tip will be showed
      ::draw2d::font_pointer          m_font;           // tip string font
      point                      m_pointOffset;       // tip point offset
      ::size                     m_sizeArrow;      // arrow size
      bool                       m_bTipEnable;     // set if the tip is enabled

      point                      m_point;             // coordinates fo the cursor position used to track changes in cursor position
      CToolMap                   m_toolmap;        // map of tool index to tool pointers

      tool_tip_window();
      virtual ~tool_tip_window();


      void RemoveAllTools();
      tool_tip_tool * GetTool(i32 iTool);
      bool GetToolText(i32 iTool, string & str);
      void AddTool(tool_tip_tool * ptool);
      bool GetToolRect(i32 iTool, RECT * prect);

      void update_drawing_objects();
      bool ShowTip();
      bool IsTipEnabled();
      void EnableTip(bool bEnable = true);
      bool HideTip();
      virtual bool create(::user::interaction * puserinteraction, const id & id);
      bool CalcRect(::draw2d::graphics_pointer & pgraphics, RECT * prect, const ::rect & lprectToolScreen, const char * pcsz);

      void ShowTip(i32 iTool, bool bForce = false);
      void SetPositionHint(::user::interaction * puserinteraction, e_position eposition);
      void relay_event(tool_tip_tool * pwnd, ::message::message * pmessage);

      void OnPaint();
      void OnTimer(UINT nIDEvent);
      void OnSize(UINT nType, i32 cx, i32 cy);
      void OnDestroy();


   };


} // namespace user



