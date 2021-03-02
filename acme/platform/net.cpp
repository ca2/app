#include "framework.h"


CLASS_DECL_ACME string url_decode(const string & strParam)
{

   string str(strParam);

   string strDecode;

   str.replace("+"," ");

   strsize iStart = 0;

   while(true)
   {

      strsize iFind = str.find("%",iStart);

      if(iFind == -1)
      {
         strDecode += str.Mid(iStart);
         break;
      }

      strDecode += str.Mid(iStart,iFind - iStart);

      if(str[iFind + 1] == '%')
      {

         strDecode += "%";
         iStart = iFind + 2;

      }
      else
      {

         char ch = (char)strtol(str.Mid(iFind + 1,2),nullptr,16);

         if(ch != 0)
         {
            strDecode += ch;
         }

         iStart = iFind + 3;

      }


   }

   return strDecode;


}



string url_decode(const char * pszUrl,strsize iLen)

{

   string strDecode;

   char * psz = strDecode.get_string_buffer(iLen * 4);

   strsize i = 0;

   while(*pszUrl != '\0' && i < iLen)

   {
      if(*pszUrl == '+')

      {
         i++;
         *psz = ' ';
         psz++;
         pszUrl++;

      }
      else if(*pszUrl == '%')

      {
         iLen--;
         pszUrl++;

         if(*pszUrl == '%')

         {
            i++;
            *psz = '%';
            psz++;
            pszUrl++;

         }
         else
         {
            i++;
            iLen--;
            *psz = (char)(uchar)(hex::to(*pszUrl) * 16 + hex::to(*(pszUrl + 1)));

            psz++;
            pszUrl += 2;

         }
      }
      else
      {
         i++;
         *psz = *pszUrl;

         psz++;
         pszUrl++;

      }
   }

   strDecode.release_string_buffer(iLen);

   return strDecode;

}






CLASS_DECL_ACME bool url_query_get_param(string & strParam,const char * pszKey,const char * pszUrl)
{

   const char * pszBeg;
   const char * pszEnd;

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = ansi_find_string(pszUrl,strKey);

      if(pszBeg != nullptr)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "=";

      pszBeg = ansi_find_string(pszUrl,strKey);

      if(pszBeg != nullptr)
      {

         pszBeg += strKey.get_length();

         goto success;

      }

   }

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "&";

      pszBeg = ansi_find_string(pszUrl,strKey);

      if(pszBeg != nullptr)
      {

         strParam = "";

         return true;

      }

   }

   {

      string strKey;

      strKey = "&";
      strKey += pszKey;
      strKey += "&";

      pszBeg = ansi_find_string(pszUrl,strKey);

      if(pszBeg != nullptr)
      {

         strParam = "";

         return true;

      }

   }

   return false;

success:

   pszEnd = ansi_find_string(pszBeg,"&");

   if(pszEnd == nullptr)
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = string(pszBeg,pszEnd - pszBeg);
   }

   return true;

}








string url_encode(const char * psz)
{

   string str;

   char sz[256];

   while(*psz != '\0')
   {

      char uch = *psz;

      if(ansi_char_is_digit(uch)
            || ansi_char_is_alphabetic(uch)
            || uch == '.'
            || uch == '-'
            || uch == '_')
      {

         str += uch;

      }
      else if(uch == ' ')
      {

         str += "+";

      }
      else
      {

         ansi_from_i64(sz,uch,16);

         ansi_upper(sz);

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


//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (ansi_char_is_digit(*psz)
//      || ansi_char_is_alphabetic(*psz)
//      || *psz == '.'
//      || *psz == '-'
//      || *psz == '_')
//   {
//      str += *psz;
//   }
//   else if (*psz == ' ')
//   {
//      str += "+";
//   }
//   else
//   {
//      strChar.Format("%02X", *psz);
//      str += "%" + strChar.Right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)

void openURL(const string &url_str);


void openURL(const string &url_str)
{
   CFURLRef url = CFURLCreateWithBytes(
                  nullptr,                        // allocator
                  (::u328*)url_str.c_str(),     // URLBytes
                  url_str.length(),            // length
                  kCFStringEncodingASCII,      // encoding
                  nullptr                         // baseURL
                  );
   LSOpenCFURLRef(url,0);
   CFRelease(url);
}

#elif defined(APPLE_IOS)

void openURL(const string &url_str);

int ui_open_url(const char * psz);

void openURL(const string &url_str)
{
//   __throw(todo);
//   CFURLRef url = CFURLCreateWithBytes(
//      nullptr,                        // allocator
//      (::u328*)url_str.c_str(),     // URLBytes
//      url_str.length(),            // length
//      kCFStringEncodingASCII,      // encoding
//      nullptr                         // baseURL
//      );
//       LSOpenCFURLRef(url,0);

   ui_open_url(url_str);

//   CFRelease(url);
}


#endif











//#ifdef WINDOWS
//#define strdup _strdup
//#endif
//
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive)
//{
//
//   ::acme::application * papp = (::acme::application *) instance;
//
//   ::account::user user;
//
//   user.initialize(papp);
//
//   ::account::credentials credentials;
//
//   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
//
//   //string strUsername;
//
//   //string strUser;
//
//   //string strDomain;
//
//   //string strPassword;
//
//   //string strToken;
//
//   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
//
//   //string strTitle;
//
//   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
//
//   credentials.m_bInteractive = bInteractive;
//
//   //strUsername = file_as_string(::dir::system() / "config\\user.txt");
//
//   //strPassword = file_as_string(::dir::system() / "config\\pass.txt");
//
//   //if(strUsername.has_char() && strPassword.has_char())
//   //{
//
//   //}
//   //else
//   //{
//
//   if(credentials.get_credentials() != ::success_credentials)
//   {
//
//      return false;
//
//   }
//
//   string strUser;
//
//   string strPassword(credentials.m_strPassword);
//
//   string strDomain;
//
//   index iFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin.Mid(iFind + 1);
//
//      strDomain = user.m_strLogin.Left(iFind);
//
//   }
//   else
//   {
//
//      strUser = user.m_strLogin;
//
//   }
//
//   if(username != nullptr)
//   {
//
//      *username = strdup(strUser);
//
//   }
//
//   if(domain != nullptr && strDomain.has_char())
//   {
//
//      *domain = strdup(strDomain);
//
//   }
//
//   if(password != nullptr)
//   {
//
//      *password = strdup(strPassword);
//
//   }
//
//   return true;
//
//}







CLASS_DECL_ACME bool is_url(const char* pszCandidate)
{

   string strCandidate(pszCandidate);

   strsize iLen = strCandidate.get_length();

   strsize i = 0;

   char ch;

   while (i < iLen)
   {

      ch = strCandidate[i];

      if (isalpha((uchar)ch))
         i++;
      else if (ch == '.')
         i++;
      else if (ch == ':' && (((i + 1) == iLen) ||
         (iLen > (i + 3)
            && strCandidate[i + 1] == '/'
            && strCandidate[i + 2] == '/')))
         return true;
      else
         return false;

   }

   return false;

}





CLASS_DECL_ACME string url_decode(const char* psz)
{

   string str(psz);

   string strDecode;

   str.replace("+", " ");

   strsize iStart = 0;

   while (true)
   {

      strsize iFind = str.find("%", iStart);

      if (iFind == -1)
      {
         strDecode += str.Mid(iStart);
         break;
      }

      strDecode += str.Mid(iStart, iFind - iStart);

      if (str[iFind + 1] == '%')
      {

         strDecode += "%";
         iStart = iFind + 2;

      }
      else
      {

         char ch = (char)strtol(str.Mid(iFind + 1, 2), nullptr, 16);

         if (ch != 0)
         {
            strDecode += ch;
         }

         iStart = iFind + 3;

      }


   }

   return strDecode;


}



//string url_decode(const char* pszUrl, strsize iLen)
//
//{
//
//   string strDecode;
//
//   char* psz = strDecode.get_string_buffer(iLen * 4);
//
//   strsize i = 0;
//
//   while (*pszUrl != '\0' && i < iLen)
//
//   {
//      if (*pszUrl == '+')
//
//      {
//         i++;
//         *psz = ' ';
//         psz++;
//         pszUrl++;
//
//      }
//      else if (*pszUrl == '%')
//
//      {
//         iLen--;
//         pszUrl++;
//
//         if (*pszUrl == '%')
//
//         {
//            i++;
//            *psz = '%';
//            psz++;
//            pszUrl++;
//
//         }
//         else
//         {
//            i++;
//            iLen--;
//            *psz = (char)(uchar)(hex::to(*pszUrl) * 16 + hex::to(*(pszUrl + 1)));
//
//            psz++;
//            pszUrl += 2;
//
//         }
//      }
//      else
//      {
//         i++;
//         *psz = *pszUrl;
//
//         psz++;
//         pszUrl++;
//
//      }
//   }
//
//   strDecode.release_string_buffer(iLen);
//
//   return strDecode;
//
//}
//
//




//CLASS_DECL_ACME bool url_query_get_param(string& strParam, const char* pszKey, const char* pszUrl)
//{
//
//   const char* pszBeg;
//   const char* pszEnd;
//
//   {
//
//      string strKey;
//
//      strKey = "?";
//      strKey += pszKey;
//      strKey += "=";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         pszBeg += strKey.get_length();
//
//         goto success;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "&";
//      strKey += pszKey;
//      strKey += "=";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         pszBeg += strKey.get_length();
//
//         goto success;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "?";
//      strKey += pszKey;
//      strKey += "&";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         strParam = "";
//
//         return true;
//
//      }
//
//   }
//
//   {
//
//      string strKey;
//
//      strKey = "&";
//      strKey += pszKey;
//      strKey += "&";
//
//      pszBeg = ansi_find_string(pszUrl, strKey);
//
//      if (pszBeg != nullptr)
//      {
//
//         strParam = "";
//
//         return true;
//
//      }
//
//   }
//
//   return false;
//
//success:
//
//   pszEnd = ansi_find_string(pszBeg, "&");
//
//   if (pszEnd == nullptr)
//   {
//      strParam = pszBeg;
//   }
//   else
//   {
//      strParam = string(pszBeg, pszEnd - pszBeg);
//   }
//
//   return true;
//
//}








//CLASS_DECL_ACME string url_encode(const char* psz)
//{
//
//   string str;
//
//   char sz[256];
//
//   while (*psz != '\0')
//   {
//
//      char uch = *psz;
//
//      if (ansi_char_is_digit(uch)
//         || ansi_char_is_alphabetic(uch)
//         || uch == '.'
//         || uch == '-'
//         || uch == '_')
//      {
//
//         str += uch;
//
//      }
//      else if (uch == ' ')
//      {
//
//         str += "+";
//
//      }
//      else
//      {
//
//         ansi_from_i64(sz, uch, 16);
//
//         ansi_upper(sz);
//
//         if (ansi_length(sz) == 0)
//         {
//
//            str += "%00";
//
//         }
//         else if (ansi_length(sz) == 1)
//         {
//
//            str += "%0";
//
//            str += sz;
//
//         }
//         else if (ansi_length(sz) == 2)
//         {
//
//            str += "%";
//
//            str += sz;
//
//         }
//
//      }
//
//      psz++;
//
//   }
//
//   return str;
//
//}


//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (ansi_char_is_digit(*psz)
//      || ansi_char_is_alphabetic(*psz)
//      || *psz == '.'
//      || *psz == '-'
//      || *psz == '_')
//   {
//      str += *psz;
//   }
//   else if (*psz == ' ')
//   {
//      str += "+";
//   }
//   else
//   {
//      strChar.Format("%02X", *psz);
//      str += "%" + strChar.Right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)

//void openURL(const string& url_str);
//
//
//void openURL(const string& url_str)
//{
//   CFURLRef url = CFURLCreateWithBytes(
//      nullptr,                        // allocator
//      (::u328*)url_str.c_str(),     // URLBytes
//      url_str.length(),            // length
//      kCFStringEncodingASCII,      // encoding
//      nullptr                         // baseURL
//   );
//   LSOpenCFURLRef(url, 0);
//   CFRelease(url);
//}

#elif defined(APPLE_IOS)

void openURL(const string& url_str);

int ui_open_url(const char* psz);

void openURL(const string& url_str)
{
   //   __throw(todo);
   //   CFURLRef url = CFURLCreateWithBytes(
   //      nullptr,                        // allocator
   //      (::u328*)url_str.c_str(),     // URLBytes
   //      url_str.length(),            // length
   //      kCFStringEncodingASCII,      // encoding
   //      nullptr                         // baseURL
   //      );
   //       LSOpenCFURLRef(url,0);

   ui_open_url(url_str);

   //   CFRelease(url);
}


#endif











//#ifdef WINDOWS
//#define strdup _strdup
//#endif
//
//CLASS_DECL_APEX int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const char * pszServerName, int bInteractive)
//{
//
//   ::apex::application * papp = (::apex::application *) instance;
//
//   ::account::user user;
//
//   user.initialize(papp);
//
//   ::account::credentials credentials;
//
//   credentials.initialize_account_credentials(&user, Sess(papp).account()->storage());
//
//   //string strUsername;
//
//   //string strUser;
//
//   //string strDomain;
//
//   //string strPassword;
//
//   //string strToken;
//
//   credentials.m_strToken = Sys(papp).crypto_md5_text(pszServerName);
//
//   //string strTitle;
//
//   credentials.m_strTitle = "Enter Credentials for : " + string(pszServerName);
//
//   credentials.m_bInteractive = bInteractive;
//
//   //strUsername = file_as_string(::dir::system() / "config\\user.txt");
//
//   //strPassword = file_as_string(::dir::system() / "config\\pass.txt");
//
//   //if(strUsername.has_char() && strPassword.has_char())
//   //{
//
//   //}
//   //else
//   //{
//
//   if(credentials.get_credentials() != ::success_credentials)
//   {
//
//      return false;
//
//   }
//
//   string strUser;
//
//   string strPassword(credentials.m_strPassword);
//
//   string strDomain;
//
//   index iFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin.Mid(iFind + 1);
//
//      strDomain = user.m_strLogin.Left(iFind);
//
//   }
//   else
//   {
//
//      strUser = user.m_strLogin;
//
//   }
//
//   if(username != nullptr)
//   {
//
//      *username = strdup(strUser);
//
//   }
//
//   if(domain != nullptr && strDomain.has_char())
//   {
//
//      *domain = strdup(strDomain);
//
//   }
//
//   if(password != nullptr)
//   {
//
//      *password = strdup(strPassword);
//
//   }
//
//   return true;
//
//}









