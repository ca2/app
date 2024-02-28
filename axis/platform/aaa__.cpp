#include "framework.h"
//#include "aura/message.h"
#include <stdio.h>


//#ifdef WINDOWS_DESKTOP
//
//#pragma comment(lib, "Dxva2.lib")
//
//#endif
//
////extern string_map < ::pointer<::acme::library >> g_pmapLibrary;
//
////extern ::pointer< ::mutex > psystem->m_pmutexLibrary;
//
//
////extern "C"
//CLASS_DECL_AXIS int_bool defer_aura_init();

//extern "C"
CLASS_DECL_AXIS int_bool defer_aura_term();
//
//
//namespace axis
//{
//
//
//
//   bool extract_sub_string(string& rString, const ::string & strFullString, i32 iSubString, char chSep)
//   {
//
//      const ::scoped_string & scopedstrFullString = strFullString;
//
//      if (pszFullString == nullptr || *pszFullString == '\0')
//      {
//
//         return false;
//
//      }
//
//      while (iSubString--)
//      {
//         pszFullString = strchr(pszFullString, chSep);
//
//         if (pszFullString == nullptr)
//
//         {
//            rString.empty();        // return is_empty string as well
//            return false;
//         }
//         pszFullString++;       // point_i32 past the separator
//
//      }
//
//      const char* pchEnd = strchr(pszFullString, chSep);
//
//
//      strsize nLen = (pchEnd == nullptr) ? strlen(pszFullString) : (i32)(pchEnd - pszFullString);
//
//
//      ASSERT(nLen >= 0);
//
//      ::acme::memcpy_s(rString.get_buffer(nLen), nLen * sizeof(char), pszFullString, nLen * sizeof(char));
//
//      rString.release_buffer();   // Need to call ReleaseBuffer after calling get_buffer
//
//      return true;
//
//   }
//
//
//} // namespace axis
//
//
//
