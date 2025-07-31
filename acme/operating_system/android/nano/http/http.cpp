//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"
#include "acme/_operating_system.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/url.h"


namespace android
{


   nano_http::nano_http()
   {
      
      
   }
        
                          
   nano_http::~nano_http()
   {
       
   }
      

   void nano_http::memory(const ::scoped_string & scopedstrUrl, ::nano::http_response & httpresponse, const class ::time & timeTimeout)
   {

      //using namespace std;

      //int main(void)
      //{
         //Variables 
         //DWORD dwSize = 0;
         //DWORD dwDownloaded = 0;
         //LPBYTE pszOutBuffer;

         //BOOL  bResults = FALSE;
         //HINTERNET  hSession = NULL, hConnect = NULL, hRequest = NULL;

         //http_session httpsession;

         //if (!httpsession.m_hinternet)
         //{

         //   throw ::exception(error_failed);

         //}

         //::string strServer = system()->url()->get_server(scopedstrUrl);

         //http_connect httpconnect(httpsession, strServer);

         //if (!httpconnect.m_hinternet)
         //{

         //   throw ::exception(error_failed);

         //}

         //::string strObject = system()->url()->get_object(scopedstrUrl);

         //http_get httpget(httpconnect, strObject);

         //if (!httpget.m_hinternet)
         //{

         //   throw ::exception(error_failed);

         //}

         //httpget.send_request();

         //httpget.get_response(httpresponse);

         // Use WinHttpOpen to obtain a session handle.
         // Specify an HTTP server.
         //if (hSession)
         //   hConnect = WinHttpConnect(hSession, L"192.168.20.69", INTERNET_DEFAULT_HTTP_PORT, 0);
         // Create an HTTP request handle.
         //if (hConnect)
         //   hRequest = WinHttpOpenRequest(hConnect, L"GET", L"/xyz/1.txt", NULL, WINHTTP_NO_REFERER, NULL, NULL);
         // Send a request.
         // Keep checking for data until there is nothing left.
         //HANDLE hFile = CreateFile("C:\\test1.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
         //if (bResults)
         //   do
         //   {
         //      // Check for available data.        
            //   dwSize = 0;
            //   if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
            //      printf("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
            //   // Allocate space for the buffer.        
            //   pszOutBuffer = ___new byte[dwSize + 1];
            //   if (!pszOutBuffer)
            //   {
            //      printf("Out of memory\n");
            //      dwSize = 0;
            //   }
            //   else
            //   {
            //      // Read the Data.            
            //      ZeroMemory(scopedstrOutBuffer, dwSize + 1);
            //      if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, dwSize, &dwDownloaded))
            //      {
            //         printf("Error %u in WinHttpReadData.\n", GetLastError());
            //      }
            //      else
            //      {
            //         //printf("%s", pszOutBuffer); 
            //         DWORD wmWritten;
            //         bool fr = WriteFile(hFile, pszOutBuffer, dwSize, &wmWritten, NULL);
            //         int n = GetLastError();
            //      }
            //      // Free the memory allocated to the buffer.            
            //      delete[] pszOutBuffer;
            //   }
            //} while (dwSize > 0);
            //CloseHandle(hFile);
            //// Report any errors.
            //if (!bResults)
            //   printf("Error %d has occurred.\n", GetLastError());
            //// Close any open handles.
            //if (hRequest) WinHttpCloseHandle(hRequest);
            //if (hConnect) WinHttpCloseHandle(hConnect);
            //if (hSession) WinHttpCloseHandle(hSession);
      //}
   }


} // namespace android



