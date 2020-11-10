#pragma once


namespace user
{


   class tool_tip_window;


   class tool_tip_tool :
      virtual public ::object
   {
   public:
      tool_tip_tool();
      virtual ~tool_tip_tool();

      // Attributes
      void BaseToolTipSetHandler(tool_tip_window * phandler);

      // Message handling
      void BaseToolTipRelayEvent(::message::message * pmessage);

      // Overridables
      virtual void BaseToolTipGetRect(RECT32 * prect);

      virtual bool BaseToolTipGetText(string & str);
      virtual i32 BaseToolTipGetIndex();
      virtual __pointer(::user::interaction) BaseToolTipGetWnd();

      tool_tip_window *  m_pbasetooltiphdl;      // Base tooltip handler
      ::u32              m_uiBaseToolTipText;    // Base tooltip text id

   };


} // namespace user



