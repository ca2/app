//
// From http.cpp by camilo on 20/08/2023 02:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "request.h"
#include "connect.h"
#include "acme/nano/http/get.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {


         request::request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject)
         {

            wstring wstrOperation(scopedstrOperation);

            wstring wstrObject(scopedstrObject);

            m_hinternet = WinHttpOpenRequest(connect.m_hinternet, wstrOperation, wstrObject, NULL, WINHTTP_NO_REFERER, NULL, NULL);

         }


         request::~request()
         {

         }


         bool request::send_request()
         {

            auto bResults = WinHttpSendRequest(m_hinternet, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
            // End the request.

            return bResults != FALSE;

         }


         bool request::get_response(::nano::http::get * pget)
         {

            auto    bResults = WinHttpReceiveResponse(m_hinternet, NULL);/**/

            if (!bResults)
            {

               return false;

            }
            ::u64 contentLength = 0;
            DWORD dwContentLengthBufferSize = sizeof(contentLength);

            auto bContentLength = WinHttpQueryHeaders(m_hinternet,
               WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER,
               WINHTTP_HEADER_NAME_BY_INDEX,
               &contentLength,
               &dwContentLengthBufferSize,
               WINHTTP_NO_HEADER_INDEX);

            if (!bContentLength)
            {

               contentLength = 0;

            }

            transfer_progress_function transferprogressfunction;

            transferprogressfunction = pget->m_setIn["transfer_progress_function"];

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

               if (dwDownloaded > 0)
               {

                  pget->m_memory.append(memory);

                  if (transferprogressfunction)
                  {

                     if (contentLength > 0)
                     {

                        transferprogressfunction((double)pget->m_memory.size() /
                           (double)contentLength, pget->m_memory.size(),
                           contentLength);
                     }
                     else
                     {

                        transferprogressfunction(0., pget->m_memory.size(),
                           0);

                     }


                  }

               }

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


      } // namespace http


   }// namespace nano


} // namespace windows



