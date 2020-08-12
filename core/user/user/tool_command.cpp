#include "framework.h"
#include "tool_command.h"


namespace user
{

   tool_command::tool_command()
   {
   }

   tool_command::~tool_command()
   {
   }



   void tool_command::Enable(bool bOn)
   {

      m_bEnableChanged = TRUE;


#ifdef WINDOWS_DESKTOP
      __pointer(toolbar) pToolBar = m_puiOther;

      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);
      UINT nNewStyle = pToolBar->GetButtonStyle((i32) m_iIndex) & ~TBBS_DISABLED;
      if (!bOn)
      {
         nNewStyle |= TBBS_DISABLED;
         // WINBUG: If a button is currently pressed and then is disabled
         // COMCTL32.DLL does not unpress the button, even after the mouse
         // button goes up!  We work around this bug by forcing TBBS_PRESSED
         // off when a button is disabled.
         nNewStyle &= ~TBBS_PRESSED;
      }
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle((i32) m_iIndex, nNewStyle);
#else
      __throw(todo());
#endif
   }

   void tool_command::SetCheck(i32 nCheck)
   {
      ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate

#ifdef WINDOWS_DESKTOP
      __pointer(toolbar) pToolBar = m_puiOther;
      ASSERT(pToolBar != nullptr);
      ASSERT_KINDOF(toolbar, pToolBar);
      ASSERT(m_iIndex < m_iCount);
      UINT nNewStyle = pToolBar->GetButtonStyle((i32) m_iIndex) & ~(TBBS_CHECKED | TBBS_INDETERMINATE);
      if (nCheck == 1)
         nNewStyle |= TBBS_CHECKED;
      else if (nCheck == 2)
         nNewStyle |= TBBS_INDETERMINATE;
      ASSERT(!(nNewStyle & TBBS_SEPARATOR));
      pToolBar->SetButtonStyle((i32) m_iIndex, nNewStyle | TBBS_CHECKBOX);
#else
      __throw(todo());
#endif
   }

   void tool_command::SetText(const char *)
   {
      // ignore it
   }



} // namespace user

