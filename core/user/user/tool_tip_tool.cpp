#include "framework.h"
#include "core/user/user/_user.h"
#include "tool_tip_window.h"
#include "tool_tip_tool.h"


namespace user
{


   tool_tip_tool::tool_tip_tool()
   {

      m_uiBaseToolTipText  = 0xffffffff;
      m_pbasetooltiphdl    = nullptr;

   }


   tool_tip_tool::~tool_tip_tool()
   {
      m_pbasetooltiphdl    = nullptr;
   }


   void tool_tip_tool::BaseToolTipRelayEvent(::message::message * pmessage)
   {

      if (m_pbasetooltiphdl != nullptr)
      {
         
         m_pbasetooltiphdl->relay_event(this, pmessage);

      }

   }


   void tool_tip_tool::BaseToolTipSetHandler(tool_tip_window *phandler)
   {
      m_pbasetooltiphdl = phandler;
   }

   __pointer(::user::interaction) tool_tip_tool::BaseToolTipGetWnd()
   {
      return (this);
   }

   void tool_tip_tool::BaseToolTipGetRect(RECTANGLE_I32 * prectangle)

   {
      __UNREFERENCED_PARAMETER(prectangle);

   }

   i32 tool_tip_tool::BaseToolTipGetIndex()
   {
      return -1;
   }

   bool tool_tip_tool::BaseToolTipGetText(string & str)
   {
      __UNREFERENCED_PARAMETER(str);
      return false;
   }

} // namespace user
