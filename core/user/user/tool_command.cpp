#include "framework.h"
#include "tool_command.h"
#include "base/user/user/toolbar.h"


namespace user
{

   tool_command::tool_command()
   {
   }

   tool_command::~tool_command()
   {
   }



   void tool_command::enable(bool bOn)
   {

      m_bEnableChanged = true;


#ifdef WINDOWS_DESKTOP
      ::pointer<toolbar>pToolBar = m_puiOther;

      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);

      auto estyleNew = pToolBar->tool_item_style(m_iIndex) - e_tool_item_style_disabled;

      if (!bOn)
      {

         estyleNew |= e_tool_item_style_disabled;

         estyleNew -= e_tool_item_style_pressed;

      }

      pToolBar->set_tool_item_style(m_iIndex, estyleNew);

#else
      
      throw ::exception(todo);

#endif

   }

   void tool_command::SetCheck(int nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate

#ifdef WINDOWS_DESKTOP
      ::pointer<toolbar>pToolBar = m_puiOther;
      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);

      auto estyleNew = pToolBar->tool_item_style(m_iIndex) - (e_tool_item_style_checked | e_tool_item_style_indeterminate);

      if (nCheck == 1)
      {

         estyleNew |= e_tool_item_style_checked;

      }
      else if (nCheck == 2)
      {

         estyleNew |= e_tool_item_style_indeterminate;

      }

      pToolBar->set_tool_item_style(m_iIndex, estyleNew | e_tool_item_style_checkbox);

#else
      
      throw ::exception(todo);

#endif

   }

   void tool_command::SetText(const ::string &)
   {
      // ignore it
   }



} // namespace user

