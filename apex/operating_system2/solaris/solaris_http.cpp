#include "framework.h"

#ifdef LINUX
#undef USE_MISC

#endif

tiny_http g_tinyhttp;
::u32 g_MsDownloadSize = 1024 * 128;
char * g_MsDownloadBuffer = nullptr;

void prepare_http()
{
   if(g_MsDownloadBuffer == nullptr)
   {
      g_MsDownloadBuffer = memory_new char[g_MsDownloadSize];
   }

}


bool ms_download_dup(const char * pszUrl, const char * pszFile, bool bProgress, bool bUrlEncode, i32 * piStatus, void (*callback)(void *, i32, dword_ptr), void * callback_param )
{

   if(piStatus != nullptr)
      *piStatus = 0;

   vsstring strUrl;

   char * szBuf = (char *) ca2_alloc(4096);

   prepare_http();

   if(acmefile()->exists(pszFile) && !::unlink(pszFile))
   {
      //trace("download failed: could not delete file prior to download.");
      vsstring str;
      str = "ms_download_dup: error url=\"";
      str += pszUrl;
      str += "\"";
      str = "file path=\"";
      str += pszFile;
      str += "\"";
      trace(str);
      return false;
   }

   if(callback != nullptr)
   {
      callback(callback_param, -1, 0);
   }

   i32 iCol = 3;


   strUrl = pszUrl;
   if(bUrlEncode)
   {
      strUrl = ::url::encode(strUrl);
      strUrl.replace_ci("%5C", "\\");
      strUrl.replace_ci("\\", "/");
      strUrl.replace_ci("%3A", ":");
      strUrl.replace_ci("%2F", "/");
   }
   vsstring strHost;
   vsstring strReq;
   if(strUrl.substr(0, 7) == "http://")
   {
      size_t iPos = strUrl.find("/", 8);
      strHost = strUrl.substr(7, iPos - 7);
      strReq = strUrl.substr(iPos);
   }
   ::u32 dwSize = 0;
   char * pszOutBuffer;
   int_bool  bResults = false;

   WCHAR * pwzHost = utf8_to_16(strHost);

   g_tinyhttp.m_strUserAgent = "ccwarehouse_ca2_account/linux";

   g_tinyhttp.t_parse_url(strUrl);

   char * buffer;
   i32 len;

   tiny_http::http_retcode ret = g_tinyhttp.t_get(&buffer, &len, callback, callback_param);

   acmefile()->put_contents(pszFile, buffer, len);

   ca2_free(buffer);

   return ret == tiny_http::OK200;
}



vsstring ms_get_dup(const char * pszUrl, bool bCache, void (*callback)(void *, i32, dword_ptr), void * callback_param, bool bProgress)
{

   prepare_http();
   vsstring strUrl(pszUrl);
   vsstring strHost;
   vsstring strReq;
   if(strUrl.substr(0, 7) == "http://")
   {
      size_t iPos = strUrl.find("/", 8);
      strHost = strUrl.substr(7, iPos - 7);
      strReq = strUrl.substr(iPos);
   }
   ::u32 dwSize = 0;
   ::u32 dwDownloaded = 0;
   char * pszOutBuffer;
   int_bool  bResults = false;

   g_tinyhttp.m_strUserAgent = "ccwarehouse_ca2_account/linux";

   g_tinyhttp.t_parse_url(strUrl);

   char * buffer;
   i32 len;

   tiny_http::http_retcode ret = g_tinyhttp.t_get(&buffer, &len, callback, callback_param);

   vsstring strRet(buffer, len);

   ca2_free(buffer);

   return strRet;
}


vsstring ::url::encode(const char * psz)
{
   vsstring str;
   char sz[256];
   while(*psz != '\0')
   {
      unsigned char uch = *psz;
      if(ansi_char_isdigit(uch)
            || ansi_char_isalpha(uch)
            || uch == '.'
            || uch == '-'
            || uch== '_')
      {
         str += uch;
      }
      else if(uch == ' ')
      {
         str += "+";
      }
      else
      {
         ansi_from_i64(sz, uch, 16);
         if(ansi_length(sz) == 0)
         {
            str += "%00";
         }
         else if(ansi_length(sz) == 1)
         {
            str += "%0";
            str += sz;
         }
         else if(ansi_length(sz) == 2)
         {
            str += "%";
            str += sz;
         }
      }
      psz++;
   }
   return str;
}





/*
vsstring ms_post(const char * pszUrl, const char * pszPost)
{
vsstring strUrl(pszUrl);
vsstring strHost;
vsstring strReq;
i32 iPort;
if(strUrl.substr(0, 7) == "http://")
{
i32 iPos = strUrl.find("/", 8);
strHost = strUrl.substr(7, iPos - 7);
strReq = strUrl.substr(iPos);
iPort = 80;
}
else if(strUrl.substr(0, 8) == "https://")
{
i32 iPos = strUrl.find("/", 9);
strHost = strUrl.substr(8, iPos - 8);
strReq = strUrl.substr(iPos);
iPort = 443;
}
::u32 dwSize = 0;
::u32 dwDownloaded = 0;
char * pszOutBuffer;
int_bool  bResults = false;
HINTERNET  hSession = nullptr,
hConnect = nullptr,
hRequest = nullptr;

WCHAR * pwzHost = utf8_to_16(strHost);

/*WCHAR * pwzAutoUrl = nullptr;
if(WinHttpDetectAutoProxyConfigUrl(
WINHTTP_AUTO_DETECT_TYPE_DHCP|
WINHTTP_AUTO_DETECT_TYPE_DNS_A, pwzAutoUrl))
{
WinHttpGetProxyForUrl
GlobalFree((HGLOBAL) pwzAutoUrl);
}*/



// Use WinHttpOpen to obtain a session handle.
/*  hSession = WinHttpOpen( L"ccwarehouse_ca2_account",
WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
WINHTTP_NO_PROXY_NAME,
WINHTTP_NO_PROXY_BYPASS, 0);

WCHAR * pwzReq = utf8_to_16(strReq);
WCHAR * pwzUrl = utf8_to_16(strUrl);
config_session_proxy(hSession, pwzUrl);





// Specify an HTTP server.
if (hSession)
hConnect = WinHttpConnect( hSession, pwzHost,
iPort, 0);


// Create an HTTP request handle.
if (hConnect)
hRequest = WinHttpOpenRequest( hConnect, L"POST",
pwzReq,
nullptr, WINHTTP_NO_REFERER,
WINHTTP_DEFAULT_ACCEPT_TYPES,
iPort == 443 ? WINHTTP_FLAG_SECURE : 0);
//                                       WINHTTP_FLAG_SECURE);

// Add a request header.
WCHAR * hd1 = utf8_to_16(("Host: " + strHost));
if( hRequest )
bResults = WinHttpAddRequestHeaders( hRequest,
hd1,
-1,
WINHTTP_ADDREQ_FLAG_ADD );
if( hRequest )
bResults = WinHttpAddRequestHeaders( hRequest,
L"Content-Type: application/x-www-form-urlencoded",
-1,
WINHTTP_ADDREQ_FLAG_ADD );

// Send a request.
if (hRequest)
bResults = WinHttpSendRequest( hRequest,
WINHTTP_NO_ADDITIONAL_HEADERS,
0, WINHTTP_NO_REQUEST_DATA, 0,
strlen(pszPost), 0);

::u32 dwUploaded;
if (bResults)
if (! (bResults = WinHttpWriteData( hRequest, (LPVOID)pszPost,
strlen(pszPost), &dwUploaded)))
printf( "Error %u in WinHttpReadData.\n",
get_last_error());

// End the request.
if (bResults)
bResults = WinHttpReceiveResponse( hRequest, nullptr);

vsstring strResult;

// Keep checking for data until there is nothing left.
if (bResults)
{
do
{

// Check for available data.
dwSize = 0;
if (!WinHttpQueryDataAvailable( hRequest, &dwSize))
printf( "Error %u in WinHttpQueryDataAvailable.\n",
get_last_error());

// Allocate space for the buffer.
pszOutBuffer = memory_new char[dwSize+1];
if (!pszOutBuffer)
{
printf("Out of memory\n");
dwSize=0;
}
else
{
// Read the Data.
ZeroMemory(pszOutBuffer, dwSize+1);

if (!WinHttpReadData( hRequest, (LPVOID)pszOutBuffer,
dwSize, &dwDownloaded))
printf( "Error %u in WinHttpReadData.\n",
get_last_error());
else
{
g_dwDownloadLen += dwSize;
strResult += pszOutBuffer;
}

// Free the memory allocated to the buffer.
delete [] pszOutBuffer;
}

} while (dwSize>0);
}

::u32 dw = get_last_error();
// Report any errors.
if (!bResults)
printf("Error %d has occurred.\n",dw);

delete [] hd1;
delete [] pwzUrl;
delete [] pwzReq;
delete [] pwzHost;

// Close any open handles.
if (hRequest) WinHttpCloseHandle(hRequest);
if (hConnect) WinHttpCloseHandle(hConnect);
if (hSession) WinHttpCloseHandle(hSession);
return strResult;
}
*/
/*
void config_session_proxy(HINTERNET hSession, WCHAR * pwzUrl)
{
WINHTTP_AUTOPROXY_OPTIONS apop;

char szPac[4096];
memory_set(szPac, 0, sizeof(szPac));
::u32 lcbPac;
HKEY hkey;
memory_set(&apop, 0, sizeof(apop));
bool bGot = false;
lcbPac = sizeof(szPac);
if(RegOpenKey(HKEY_CURRENT_USER,
"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\\Connections",
&hkey) == ERROR_SUCCESS)
{
::i32 l;
::u32 dw;
if((l = RegQueryValueEx(hkey, "DefaultConnectionSettings", nullptr, nullptr, (byte *) &szPac, &lcbPac)) == ERROR_SUCCESS
&& (szPac[8] & 8))
{
apop.dwAutoDetectFlags = WINHTTP_AUTO_DETECT_TYPE_DHCP | WINHTTP_AUTO_DETECT_TYPE_DNS_A;
apop.dwFlags = WINHTTP_AUTOPROXY_AUTO_DETECT;
apop.fAutoLogonIfChallenged = true;
apop.lpszAutoConfigUrl = nullptr;
bGot = true;
}
else
{
FormatMessage(0, 0, l, 0, szPac, sizeof(szPac), nullptr);
}
}
lcbPac = sizeof(szPac);
if(!bGot)
{
if(RegOpenKey(HKEY_CURRENT_USER,
"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
&hkey) == ERROR_SUCCESS)
{
::i32 l;
if((l = RegQueryValueEx(hkey, "AutoConfigURL", nullptr, nullptr, (byte *) szPac, &lcbPac)) == ERROR_SUCCESS)
{

apop.dwAutoDetectFlags = 0;
apop.dwFlags = WINHTTP_AUTOPROXY_CONFIG_URL;
apop.lpszAutoConfigUrl = utf8_to_16(szPac);
apop.fAutoLogonIfChallenged = true;
bGot = true;
}
else
{
FormatMessage(0, 0, l, 0, szPac, sizeof(szPac), nullptr);
}
}
}
if(!bGot)
{
return;
}

WINHTTP_PROXY_INFO pinfo;


if(WinHttpGetProxyForUrl(
hSession,
pwzUrl,
&apop,
&pinfo))
{
WinHttpSetOption(
hSession,
WINHTTP_OPTION_PROXY,
&pinfo,
sizeof(pinfo));

}


}
*/

