//
// Created by camilo on 26/07/2023 23:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "http.h"
#include "_nano_http.h"
#include "acme/_operating_system.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
//#include <winsock2.h>
#include <Winhttp.h>
//      //#include <urlmon.h>
//#include <windows.h>
//#include <iostream>
//#include <fstream>
#pragma comment(lib, "Winhttp.lib")

namespace windows
{

   class hinternet
   {
   public:


      HINTERNET  m_hinternet;

      hinternet(HINTERNET hinternet = nullptr):m_hinternet(hinternet)
      {}

      virtual ~hinternet()
      {
         if (m_hinternet)
         {

            ::WinHttpCloseHandle(m_hinternet);
         }
      }

   };

   class http_session :
      public hinternet
   {
   public:
      http_session(const ::scoped_string & scopedstrAgent = "nano_http")
      {

         wstring wstrAgent(scopedstrAgent);

         m_hinternet = ::WinHttpOpen(wstrAgent, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

      }
      ~http_session() override
      {

      }


   };

   class http_connect :
      public hinternet
   {
   public:


      http_connect(http_session & session, const ::scoped_string & scopedstrHost)
      {

         wstring wstrHost(scopedstrHost);

         m_hinternet = WinHttpConnect(session.m_hinternet, wstrHost, INTERNET_DEFAULT_HTTP_PORT, 0);

      }
      ~http_connect() override
      {

      }

   };

   class http_request :
      public hinternet
   {
   public:


      http_request(http_connect & connect, const ::scoped_string & scopedstrOperation, const ::scoped_string & scopedstrObject)
      {

         wstring wstrOperation(scopedstrOperation);

         wstring wstrObject(scopedstrObject);

         m_hinternet = WinHttpOpenRequest(connect.m_hinternet, wstrOperation, wstrObject, NULL, WINHTTP_NO_REFERER, NULL, NULL);

      }

      ~http_request() override
      {

      }

      bool send_request()
      {

         auto bResults = WinHttpSendRequest(m_hinternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
         // End the request.

         return bResults != FALSE;

      }

      bool get_response(::nano::http_response & httpresponse)
      {
         auto    bResults = WinHttpReceiveResponse(m_hinternet, NULL);/**/

         if (bResults)
         {

            return false;

         }

         DWORD dwSize = 0;
         while (true)
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

   }


   };

   class http_get :
      public http_request
   {
   public:


      http_get(http_connect & connect, const ::scoped_string & scopedstrObject) :
         http_request(connect, "GET", scopedstrObject)
      {

      }

      ~http_get() override
      {


      }

   };


      
   nano_http::nano_http()
   {
      
      
   }
        
                          
   nano_http::~nano_http()
   {
       
   }
      

   //void nano_http::s_http_response(long http_status, const void * data, long size, void * userdata)
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

      
//   void nano_http::asynchronous_memory(const ::scoped_string & scopedstrUrl, ::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
//   {
//      
////      pasynchronoushttpresponse->m_function = [](::pointer < ::nano::asynchronous_http_response > pasynchronoushttpresponse)
////      {                                s_http_response(pasynchronoushttpresponse);
////      };
//      
//      nano_asynchronous_http_memory(scopedstrUrl.c_str(), s_http_response, pasynchronoushttpresponse.detach_particle());
//     
//   }


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

         http_session httpsession;

         if (!httpsession.m_hinternet)
         {

            throw ::exception(error_failed);

         }

         ::string strServer = acmesystem()->url()->get_server(scopedstrUrl);

         http_connect httpconnect(httpsession, strServer);

         if (!httpconnect.m_hinternet)
         {

            throw ::exception(error_failed);

         }

         ::string strObject = acmesystem()->url()->get_object(scopedstrUrl);

         http_get httpget(httpconnect, strObject);

         if (!httpget.m_hinternet)
         {

            throw ::exception(error_failed);

         }

         httpget.send_request();

         httpget.get_response(httpresponse);

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


} // namespace windows





