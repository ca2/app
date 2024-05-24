//
// From http.cpp by camilo on 20/08/2023 02:08 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "request.h"
#include "connect.h"
#include "acid/nano/http/get.h"


namespace windows
{


   namespace nano
   {


      namespace http
      {


         request::request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject) :
            m_connect(connect)
         {

            wstring wstrOperation(scopedstrOperation);

            wstring wstrObject(scopedstrObject);

            m_hinternet = WinHttpOpenRequest(connect.m_hinternet, wstrOperation, wstrObject, NULL, WINHTTP_NO_REFERER, NULL, WINHTTP_FLAG_SECURE);
            DWORD dwOptionValue = WINHTTP_DISABLE_REDIRECTS;
            BOOL b = WinHttpSetOption(m_hinternet, WINHTTP_OPTION_DISABLE_FEATURE, &dwOptionValue, sizeof(dwOptionValue));

         }


         request::~request()
         {

         }


         bool request::send_request()
         {

            ::wstring wstrHost = m_connect.m_wstrHost;

            wstring wstrMoreHeaders;

            wstrMoreHeaders += L"Host: ";
            wstrMoreHeaders += wstrHost;
            wstrMoreHeaders += L"\r\n";
            wstrMoreHeaders += L"Accept: */*\r\n";

            auto bResults = WinHttpSendRequest(m_hinternet, wstrMoreHeaders, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
            // End the request.

            return bResults != FALSE;

         }


         bool request::get_response(::nano::http::get * pget)
         {

            auto    bResults = WinHttpReceiveResponse(m_hinternet, NULL);/**/

            if (!bResults)
            {

               DWORD dw = ::GetLastError();

               return false;

            }

            DWORD dwSize = 0;
            WinHttpQueryHeaders(m_hinternet,
               WINHTTP_QUERY_FLAG_REQUEST_HEADERS
               | WINHTTP_QUERY_RAW_HEADERS_CRLF,
               WINHTTP_HEADER_NAME_BY_INDEX, NULL,
               &dwSize, WINHTTP_NO_HEADER_INDEX);
            wstring wstrRequestHeaders;
            // Allocate memory for
            // 
            //  the buffer.
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               auto pwszHeaders = wstrRequestHeaders.get_buffer(dwSize / sizeof(WCHAR));

               // Now, use WinHttpQueryHeaders to retrieve the header.
               bResults = WinHttpQueryHeaders(m_hinternet,
                  WINHTTP_QUERY_FLAG_REQUEST_HEADERS
                  | WINHTTP_QUERY_RAW_HEADERS_CRLF,
                  WINHTTP_HEADER_NAME_BY_INDEX,
                  pwszHeaders, &dwSize,
                  WINHTTP_NO_HEADER_INDEX);
               wstrRequestHeaders.release_buffer();
            }
            ::string strRequestHeaders(wstrRequestHeaders);

            
            dwSize = 0;
            WinHttpQueryHeaders(m_hinternet, WINHTTP_QUERY_RAW_HEADERS_CRLF,
               WINHTTP_HEADER_NAME_BY_INDEX, NULL,
               &dwSize, WINHTTP_NO_HEADER_INDEX);
            wstring wstrHeaders;
            // Allocate memory for
            // 
            //  the buffer.
            if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
            {
               auto pwszHeaders = wstrHeaders.get_buffer(dwSize / sizeof(WCHAR));

               // Now, use WinHttpQueryHeaders to retrieve the header.
               bResults = WinHttpQueryHeaders(m_hinternet,
                  WINHTTP_QUERY_RAW_HEADERS_CRLF,
                  WINHTTP_HEADER_NAME_BY_INDEX,
                  pwszHeaders, &dwSize,
                  WINHTTP_NO_HEADER_INDEX);
               wstrHeaders.release_buffer();
            }

            ::string strHeaders(wstrHeaders);

            pget->m_setOut.parse_network_headers(strHeaders);

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

            bool bOnlyHeaders = pget->m_setIn["only_headers"].as_bool();

            if (bOnlyHeaders)
            {

               return true;

            }

            transfer_progress_function transferprogressfunction;

            transferprogressfunction = pget->m_setIn["transfer_progress_function"];

            dwSize = 0;
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



