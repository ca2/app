#include "framework.h"

//// Global helper functions
// CLASS_DECL_BASE __pointer(::aura::application) __get_app()
//{ return afxCurrentWinApp; }
//
// CLASS_DECL_BASE HINSTANCE __get_instance_handle()
//   { ASSERT(afxCurrentInstanceHandle != nullptr);
//      return afxCurrentInstanceHandle; }
// CLASS_DECL_BASE HINSTANCE __get_resource_handle()
//   { ASSERT(afxCurrentResourceHandle != nullptr);
//      return afxCurrentResourceHandle; }
// CLASS_DECL_BASE void __set_resource_handle(HINSTANCE hInstResource)
//   { ASSERT(hInstResource != nullptr); afxCurrentResourceHandle = hInstResource; }
// CLASS_DECL_BASE const char * __get_app_name()
//   { ASSERT(afxCurrentAppName != nullptr); return afxCurrentAppName; }
// CLASS_DECL_BASE __pointer(::user::interaction) __get_main_window()
//{
//      ::thread* pThread = dynamic_cast < ::thread * > (::android::get_thread());
//      return pThread != nullptr ? pThread->GetMainWnd().m_p : nullptr;
// }
//
// CLASS_DECL_BASE bool __gen_get_ambient_act_ctx()
//   {    return afxAmbientActCtx; }
// CLASS_DECL_BASE void __set_ambient_act_ctx(bool bSet)
//   {  afxAmbientActCtx = bSet; }



//// __MAINTAIN_STATE functions
// __MAINTAIN_STATE::__MAINTAIN_STATE(__MODULE_STATE* pNewState) NOTHROW
//   {  m_pPrevModuleState = __set_module_state(pNewState); }
//
//// __MAINTAIN_STATE2 functions
// __MAINTAIN_STATE2::~__MAINTAIN_STATE2()
//{
//   // Not a good place to report errors here, so just be safe
//   if(m_pThreadState)
//   {
//      m_pThreadState->m_pModuleState = m_pPrevModuleState;
//   }
//
///*   if (m_bValidActCtxCookie)
//   {
//      bool bRet;
//      bRet = __deactivate_act_ctx(0, m_ulActCtxCookie);
//      ASSERT(bRet == TRUE);
//   }*/
//}
//
//



 // __is_valid_atom() returns TRUE if the passed parameter is
// a valid local or global atom.

/*bool __is_valid_atom(ATOM nAtom)
{
   return true;

   char sBuffer[256];
   if (GetAtomName(nAtom, sBuffer, _countof(sBuffer)))
   {
      return TRUE;
   }
   DWORD dwError = get_last_error();
   if (dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {
      return TRUE;
   }
   if (GlobalGetAtomName(nAtom, sBuffer, _countof(sBuffer)))
   {
      return TRUE;
   }
   dwError = get_last_error();
   if (dwError == ERROR_INSUFFICIENT_BUFFER || dwError == ERROR_MORE_DATA)
   {
      return TRUE;
   }
   return FALSE;
}

// __is_valid_address() returns TRUE if the passed parameter is
// a valid representation of a local or a global atom within a const char *.

bool __is_valid_atom(const char * psz)
{
   return HIWORD(psz) == 0L && __is_valid_atom(ATOM(LOWORD(psz)));
}
*/
