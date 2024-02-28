//
// From http.cpp by camilo on 20/08/2023 02:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http_request.h"
#include "http_connect.h"
#include "acme/platform/nano_http_response.h"


namespace windows
{


   http_request::http_request(http_connect & connect, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrObject)
   {

      wstring wstrOperation(scopedstrOperation);

      wstring wstrObject(scopedstrObject);

      m_hinternet = WinHttpOpenRequest(connect.m_hinternet, wstrOperation, wstrObject, NULL, WINHTTP_NO_REFERER, NULL, NULL);

   }


   http_request::~http_request()
   {

   }

   
   bool http_request::send_request()
   {

      auto bResults = WinHttpSendRequest(m_hinternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
      // End the request.

      return bResults != FALSE;

   }


   bool http_request::get_response(::nano::http_response & httpresponse)
   {

      auto    bResults = WinHttpReceiveResponse(m_hinternet, NULL);/**/

      if (!bResults)
      {

         return false;

      }

      DWORD dwSize = 0;
      do
      {

         if (!WinHttpQueryDataAvailable(m_hinternet, &dwSize))
         {
            //            printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());

            return false;

         }
         ::memory memory;

         memory.set_size(dwSize);
         // Allocate space for the buffer.        
         //pszOutBuffer = new byte[dwSize + 1];
         //if (!pszOutBuffer)
         //{
           // printf("Out of memory\n");
            //dwSize = 0;
         //}
         //else
         //{
         // 
         memory.zero();
         // Read the Data.            
         //ZeroMemory(pszOutBuffer, dwSize + 1);
         DWORD dwDownloaded = 0;
         if (!WinHttpReadData(m_hinternet, (LPVOID)memory.data(), dwSize, &dwDownloaded))
         {
            //printf("Error %u in WinHttpReadData.\n", GetLastError());
            return false;
         }

         memory.set_size(dwDownloaded);

         httpresponse.m_memory.append(memory);

         //dwSize -= dwDownloaded;
         //else
         //
         //{
         //   //printf("%s", pszOutBuffer); 
         //   DWORD wmWritten;
         //   bool fr = WriteFile(hFile, pszOutBuffer, dwSize, &wmWritten, NULL);
         //   int n = GetLastError();
         ////}
         // Free the memory allocated to the buffer.            
         //delete[] pszOutBuffer;
      //}
      } while (dwSize > 0);

      return true;

   }


} // namespace windows



