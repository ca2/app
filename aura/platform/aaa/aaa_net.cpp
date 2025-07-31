#include "framework.h"


CLASS_DECL_AURA string url_decode(const ::scoped_string & scopedstr)
{
   string str(scopedstr);

   string strDecode;

   str.replace("+"," ");

   character_count iStart = 0;

   while(true)
   {

      auto pFind = str.find("%",iStart);

      if(iFind == -1)
      {
         strDecode += str.substr(iStart);
         break;
      }

      strDecode += str.substr(iStart,iFind - iStart);

      if(str[iFind + 1] == '%')
      {

         strDecode += "%";
         iStart = iFind + 2;

      }
      else
      {

         char ch = (char)strtol(str.substr(iFind + 1,2),nullptr,16);

         if(ch != 0)
         {
            strDecode += ch;
         }

         iStart = iFind + 3;

      }


   }

   return strDecode;


}



string url_decode(const ::scoped_string & scopedstrUrl,character_count iLen)

{

   string strDecode;

   char * psz = strDecode.get_buffer(iLen * 4);

   character_count i = 0;

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
            *psz = (char)(uchar)(hex::to(*pszUrl) * 16 + hex::to(*(scopedstrUrl + 1)));

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

   strDecode.release_buffer(iLen);

   return strDecode;

}






CLASS_DECL_AURA bool url_query_get_param(string & strParam, const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrUrl)
{

   const ::scoped_string & scopedstrBeg;
   const ::ansi_character * pszEnd;

   {

      string strKey;

      strKey = "?";
      strKey += pszKey;
      strKey += "=";

      pszBeg = ansi_find_string(scopedstrUrl,strKey);

      if(scopedstrBeg != nullptr)
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

      pszBeg = ansi_find_string(scopedstrUrl,strKey);

      if(scopedstrBeg != nullptr)
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

      pszBeg = ansi_find_string(scopedstrUrl,strKey);

      if(scopedstrBeg != nullptr)
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

      pszBeg = ansi_find_string(scopedstrUrl,strKey);

      if(scopedstrBeg != nullptr)
      {

         strParam = "";

         return true;

      }

   }

   return false;

success:

   pszEnd = ansi_find_string(scopedstrBeg,"&");

   if(scopedstrEnd == nullptr)
   {
      strParam = pszBeg;
   }
   else
   {
      strParam = string(scopedstrBeg,pszEnd - pszBeg);
   }

   return true;

}








string url_encode(const ::scoped_string & scopedstr)
{

   string str;

   char sz[256];

   while(*psz != '\0')
   {

      char uch = *psz;

      if(ansi_char_isdigit(uch)
            || ansi_char_isalpha(uch)
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

         ansi_from_long_long(sz,uch,16);

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
//      strChar.formatf("%02X", *psz);
//      str += "%" + strChar.right(2);
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

int ui_open_url(const ::scoped_string & scopedstr);

void openURL(const string &url_str)
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
//CLASS_DECL_AURA int_bool freerdp_get_credentials(void * instance, char** username,char** password,char** domain, const ::scoped_string & scopedstrServerName, int bInteractive)
//{
//
//   ::aura::application * papp = (::aura::application *) instance;
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
//   credentials.m_strToken = Sys(papp).crypto_md5_text(scopedstrServerName);
//
//   //string strTitle;
//
//   credentials.m_strTitle = "Enter Credentials for : " + string(scopedstrServerName);
//
//   credentials.m_bInteractive = bInteractive;
//
//   //strUsername = file_system()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\user.txt");
//
//   //strPassword = file_system()->as_string(         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->system() / "config\\pass.txt");
//
//   //if(strUsername.has_character() && strPassword.has_character())
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
//   if(domain != nullptr && strDomain.has_character())
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








