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
//   bool extract_sub_string(string& rString, const ::scoped_string & scopedstrFullString, ::i32 iSubString, ::i8 chSep)
//   {
//
//      const ::scoped_string & scopedstrFullString = strFullString;
//
//      if (scopedstrFullString == nullptr || *pszFullString == '\0')
//      {
//
//         return false;
//
//      }
//
//      while (iSubString--)
//      {
//         pszFullString = strchr(scopedstrFullString, chSep);
//
//         if (scopedstrFullString == nullptr)
//
//         {
//            rString.empty();        // return is_empty string as well
//            return false;
//         }
//         pszFullString++;       // i32_point past the separator
//
//      }
//
//      const_char_pointer pchEnd = strchr(scopedstrFullString, chSep);
//
//
//      character_count nLen = (pchEnd == nullptr) ? strlen(scopedstrFullString) : (::i32)(pchEnd - pszFullString);
//
//
//      ASSERT(nLen >= 0);
//
//      ::safe_memory_copy(rString.get_buffer(nLen), nLen * sizeof(::i8), pszFullString, nLen * sizeof(::i8));
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
