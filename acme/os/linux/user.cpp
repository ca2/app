#include "framework.h"


namespace user
{


//   CLASS_DECL_ACME bool is_app_dark_mode()
//   {
//
//      return false;
//
//   }



} // namespace user


string _os_message_box(const char* pszMessage, const char* pszTitle, ::emessagebox emessagebox)
{


#ifdef WINDOWS_DESKTOP

   wstring wstrText(m_strText);

   wstring wstrTitle(m_strTitle);

   iResult = ::MessageBox(nullptr, wstrText, wstrTitle, iMessageBox);


#elif defined(LINUX)

   iResult = x11_message_box(m_strText, m_strTitle, m_emessagebox);

#elif defined(_UWP) || defined(__APPLE__)

   _os_message_box(m_strText, m_strTitle, m_emessagebox, m_future);

   //   string strResult = message_box_result_to_string(iResult);

   //   m_future.send(strResult);

   //});

#else

   iResult = _os_message_box(m_strText, m_strTitle, m_emessagebox);
   string strResult = message_box_result_to_string(iResult);

   m_future.send(strResult);


#endif

   return strResult;


   return ::success;

}



