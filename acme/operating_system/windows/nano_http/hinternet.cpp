//
// From http.cpp by camilo on 20/08/2023 02:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_.h"
#include "hinternet.h"
#pragma comment(lib, "Winhttp.lib")


namespace windows
{


   hinternet::hinternet(HINTERNET hinternet) :
      m_hinternet(hinternet)
   {
   
   }


   hinternet::~hinternet()
   {

      if (m_hinternet)
      {

         ::WinHttpCloseHandle(m_hinternet);

      }

   }


} // namespace windows



