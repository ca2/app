#include "framework.h"
//#include "acme/primitive/string/hex.h"
// #include "acme/primitive/string/string.h"


char* string_append_character(char* psz, ::ansi_character ch)
{

   *psz = ch;

   psz++;

   *psz = '\0';

   return psz;

}

bool is_url(const ::scoped_string & scopedstrCandidate,const char ** ppszRequest)
{

   const ::scoped_string & scopedstr = pszCandidate;
   while(*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
   {
      psz++;
   }
   if(psz == pszCandidate)
      return false;
   if(psz == pszCandidate + 1)
      return false;
   if(*psz != ':')
      return false;
   psz++;
   if(*psz != '/' && *psz != '\\')
      return false;
   psz++;
   if(*psz == '/' || *psz == '\\')
   {
      psz++;
   }
   /*if(*psz != '/' && *psz != '\\')
      return false;
   psz++;*/
   while(*psz != '\0' && (*psz == '.' || *psz == ':' || *psz == '@' || *psz == '_' || *psz == '-' || character_isalnum(*psz)))
   {
      psz++;
   }
   if(*psz != '\0' && *psz != '/' && *psz != '\\')
      return false;
   if(ppszRequest != nullptr)
   {
      *ppszRequest = psz;
   }
   return true;

}


CLASS_DECL_ACME bool is_like_url_protocol(const ::scoped_string & scopedstr)
{

   if (is_empty(psz))
   {

      return false;

   }

   if (character_isalpha(*psz))
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   while (character_isalnum(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   return false;

}




//#include "framework.h"
//#include "net.h"
//#include "as_string.h"
//#include "acme/exception/parsing.h"
//#include "acme/primitive/string/hex.h"
////#include "acme/operating_system.h"


//CLASS_DECL_ACME string ::url::decode(const & strParam)
//{
//
//   return ::url::decode(strParam, strParam.length());
//
//   /*string str(strParam);
//
//   string strDecode;
//
//   str.replace_with(" ", "+");
//
//   strsize iStart = 0;
//
//   while(true)
//   {
//
//      auto pFind = str.find("%",iStart);
//
//      if(iFind == -1)
//      {
//         strDecode += str.substr(iStart);
//         break;
//      }
//
//      strDecode += str.substr(iStart,iFind - iStart);
//
//      if(str[iFind + 1] == '%')
//      {
//
//         strDecode += "%";
//         iStart = iFind + 2;
//
//      }
//      else
//      {
//
//         char ch = (char)strtol(str.substr(iFind + 1,2),nullptr,16);
//
//         if(ch != 0)
//         {
//            strDecode += ch;
//         }
//
//         iStart = iFind + 3;
//
//      }
//
//
//   }
//
//   return strDecode;*/
//
//
//}
//


namespace url
{


   string decode(const ::block& block)
   {

      auto sizeLen = block.get_size();

      string strDecode;

      char* pszStart = strDecode.get_buffer(sizeLen * 4);

      auto pszDecode = pszStart;

      strsize i = 0;

      const ::scoped_string & scopedstrEncoded = (const char*)block.get_data();

      while (*pszEncoded != '\0' && i < sizeLen)
      {

         if (*pszEncoded == '+')
         {

            i++;

            *pszDecode = ' ';

            pszDecode++;

            pszEncoded++;

         }
         else if (*pszEncoded == '%')
         {

            sizeLen--;

            pszEncoded++;

            if (*pszEncoded == '%')
            {

               i++;

               *pszDecode = '%';

               pszDecode++;

               pszEncoded++;

            }
            else
            {

               i++;

               sizeLen--;

               auto nibble1 = hex::to_nibble(*pszEncoded++);

               if (nibble1 < 0)
               {

                  throw_parsing_exception("url decode: % first nibble non hex");

               }

               auto nibble2 = hex::to_nibble(*pszEncoded++);

               if (nibble2 < 0)
               {

                  throw_parsing_exception("url decode: % second nibble non hex");

               }

               *pszDecode = (char)(uchar)(((nibble1 << 4) & 0xf0) | (nibble2 & 0xf));

               pszDecode++;

            }

         }
         else
         {

            i++;

            *pszDecode = *pszEncoded;

            pszDecode++;

            pszEncoded++;

         }

      }

      strDecode.release_buffer(sizeLen);

      return ::transfer(strDecode);

   }



   CLASS_DECL_ACME bool query_get_param(string& strParam, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrUrl)
   {

      const ::scoped_string & scopedstrBeg;
      const ::ansi_character * pszEnd;

      {

         string strKey;

         strKey = "?";
         strKey += pszKey;
         strKey += "=";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            pszBeg += strKey.length();

            goto success;

         }

      }

      {

         string strKey;

         strKey = "&";
         strKey += pszKey;
         strKey += "=";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            pszBeg += strKey.length();

            goto success;

         }

      }

      {

         string strKey;

         strKey = "?";
         strKey += pszKey;
         strKey += "&";

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
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

         pszBeg = ansi_find_string(pszUrl, strKey);

         if (pszBeg != nullptr)
         {

            strParam = "";

            return true;

         }

      }

      return false;

   success:

      pszEnd = ansi_find_string(pszBeg, "&");

      if (pszEnd == nullptr)
      {
         strParam = pszBeg;
      }
      else
      {
         strParam = string(pszBeg, pszEnd - pszBeg);
      }

      return true;

   }


   string encode(const ::block& block)
   {

      string strEncoded;

      auto pszEncodedStart = strEncoded.get_buffer(block.get_size() * 5);

      auto pszEncoded = pszEncodedStart;

      auto pszInput = (const char*)block.get_data();

      memset(pszEncoded, 0, block.get_size() * 5);

      while (*pszInput != '\0')
      {

         char ch = *pszInput;

         if (ansi_char_isalnum(ch)
            || ch == '.'
            || ch == '-'
            || ch == '_')
         {

            pszEncoded = string_append_character(pszEncoded, ch);

         }
         else if (ch == ' ')
         {

            pszEncoded = string_append_character(pszEncoded, '+');

         }
         else
         {

            pszEncoded = string_append_character(pszEncoded, '%');

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_from((ch >> 4) & 0xf));

            pszEncoded = string_append_character(pszEncoded, ::hex::nibble_upper_from(ch & 0xf));

         }

         pszInput++;

      }

      strEncoded.release_buffer(pszEncoded - pszEncodedStart);

      return ::transfer(strEncoded);

   }


} // namespace urls



//string str;
//
//string strChar;
//
//while (*psz != '\0')
//{
//
//   if (ansi_char_isdigit(*psz)
//      || ansi_char_isalpha(*psz)
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
//      strChar.format("%02X", *psz);
//      str += "%" + strChar.right(2);
//   }
//
//   psz++;
//}
//
//return str;






















#if defined(MACOS)
#elif defined(APPLE_IOS)

void openURL(const string& url_str);

int ui_open_url(const ::scoped_string & scopedstr);

void openURL(const string& url_str)
{
   //   throw ::exception(todo);
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
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::scoped_string & scopedstrServerName, int bInteractive)
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
//   //strUsername = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\user.txt");
////
////   //strPassword = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\pass.txt");
////
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
//   auto pFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin(pFind + 1);
//
//      strDomain = user.m_strLogin(0, pFind);
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







//CLASS_DECL_ACME bool is_url(const ::scoped_string & scopedstrCandidate)
//{
//
//   string strCandidate(pszCandidate);
//
//   strsize iLen = strCandidate.length();
//
//   strsize i = 0;
//
//   char ch;
//
//   while (i < iLen)
//   {
//
//      ch = strCandidate[i];
//
//      if (isalpha((uchar)ch))
//         i++;
//      else if (ch == '.')
//         i++;
//      else if (ch == ':' && (((i + 1) == iLen) ||
//         (iLen > (i + 3)
//            && strCandidate[i + 1] == '/'
//            && strCandidate[i + 2] == '/')))
//         return true;
//      else
//         return false;
//
//   }
//
//   return false;
//
//}





//CLASS_DECL_ACME string ::url::decode(const ::scoped_string & scopedstr)
//{
//
//   string str(psz);
//
//   string strDecode;
//
//   str.replace_with(" ", "+");
//
//   strsize iStart = 0;
//
//   while (true)
//   {
//
//      auto pFind = str.find("%", iStart);
//
//      if (iFind == -1)
//      {
//         strDecode += str.substr(iStart);
//         break;
//      }
//
//      strDecode += str.substr(iStart, iFind - iStart);
//
//      if (str[iFind + 1] == '%')
//      {
//
//         strDecode += "%";
//         iStart = iFind + 2;
//
//      }
//      else
//      {
//
//         char ch = (char)strtol(str.substr(iFind + 1, 2), nullptr, 16);
//
//         if (ch != 0)
//         {
//            strDecode += ch;
//         }
//
//         iStart = iFind + 3;
//
//      }
//
//
//   }
//
//   return ::transfer(strDecode);
//
//
//}



//string ::url::decode(const ::scoped_string & scopedstrUrl, strsize iLen)
//
//{
//
//   string strDecode;
//
//   char* psz = strDecode.get_buffer(iLen * 4);
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
//   strDecode.release_buffer(iLen);
//
//   return strDecode;
//
//}
//
//




//CLASS_DECL_ACME bool url_query_get_param(string& strParam, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrUrl)
//{
//
//   const ::scoped_string & scopedstrBeg;
//   const ::ansi_character * pszEnd;
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
//         pszBeg += strKey.length();
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
//         pszBeg += strKey.length();
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








//CLASS_DECL_ACME string ::url::encode(const ::scoped_string & scopedstr)
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
//      if (ansi_char_isdigit(uch)
//         || ansi_char_isalpha(uch)
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
//   if (ansi_char_isdigit(*psz)
//      || ansi_char_isalpha(*psz)
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
//      strChar.format("%02X", *psz);
//      str += "%" + strChar.right(2);
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

int ui_open_url(const ::scoped_string & scopedstr);

//void openURL(const string& url_str)
//{
//   //   throw ::exception(todo);
//   //   CFURLRef url = CFURLCreateWithBytes(
//   //      nullptr,                        // allocator
//   //      (::u328*)url_str.c_str(),     // URLBytes
//   //      url_str.length(),            // length
//   //      kCFStringEncodingASCII,      // encoding
//   //      nullptr                         // baseURL
//   //      );
//   //       LSOpenCFURLRef(url,0);
//
//   ui_open_url(url_str);
//
//   //   CFRelease(url);
//}


#endif











//#ifdef WINDOWS
//#define strdup _strdup
//#endif
//
//CLASS_DECL_ACME int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::scoped_string & scopedstrServerName, int bInteractive)
//{
//
//   ::application * papp = (::apex::application *) instance;
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
//   //strUsername = acmefile()->as_string(         auto psystem = acmesystem();

   /*      auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->system() / "config\\user.txt")*/;
//
//   //strPassword = acmefile()->as_string(         auto psystem = acmesystem();
//
//         auto pacmedirectory = psystem->m_pacmedirectory;
//
//pacmedirectory->system() / "config\\pass.txt");
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
//   auto pFind = user.m_strLogin.find('/');
//
//   if(iFind > 0)
//   {
//
//      strUser = user.m_strLogin(pFind + 1);
//
//      strDomain = user.m_strLogin(0, pFind);
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











