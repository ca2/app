//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "session.h"
#include "connect.h"
#include "get.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"


namespace windows
{



   namespace nano
   {


      namespace http
      {

         http::http()
         {


         }


         http::~http()
         {

         }


         //void http::s_http_response(long http_status, const void * data, long size, void * userdata)
         //{
         //   
         //   ::pointer < ::nano::asynchronous_http_response > passynchronoushttpdata(e_pointer_transfer, (::particle *) userdata);
         //   
         //   passynchronoushttpdata->m_response.m_memory.assign(data, size);
         //   
         //   passynchronoushttpdata->m_response.m_set["http_status_code"] = http_status;
         //   
         //   passynchronoushttpdata->m_event.SetEvent();
         //   
         //   //passynchronoushttpdata->m_function(passynchronoushttpdata);
         //   
         //}


      //   void http::asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
      //   {
      //      
      ////      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
      ////      {                                s_http_response(pasynchronoushttpresponse);
      ////      };
      //      
      //      nano_asynchronous_http_memory(scopedstrUrl.c_str(), s_http_response, pasynchronoushttpresponse.detach_particle());
      //     
      //   }


         void http::sync(::nano::http::get * pget)
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

            ::windows::nano::http::session session;

            if (!session.m_hinternet)
            {

               throw ::exception(error_failed);

            }

            ::string strServer = system()->url()->get_server(pget->m_strUrl);

            ::windows::nano::http::connect connect(session, strServer);

            if (!connect.m_hinternet)
            {

               throw ::exception(error_failed);

            }

            ::string strObject = system()->url()->get_object(pget->m_strUrl);

            ::windows::nano::http::get get(connect, strObject);

            if (!get.m_hinternet)
            {

               throw ::exception(error_failed);

            }

            get.send_request();

            get.get_response(pget);

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
               //   pszOutBuffer = new byte[dwSize + 1];
               //   if (!pszOutBuffer)
               //   {
               //      printf("Out of memory\n");
               //      dwSize = 0;
               //   }
               //   else
               //   {
               //      // Read the Data.            
               //      ZeroMemory(pszOutBuffer, dwSize + 1);
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


      } // namespace http


   }// namespace nano


} // namespace windows



