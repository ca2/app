#include "framework.h"


namespace url
{

   bool is_url(const char * pszCandidate,const char ** ppszRequest)
   {
      const char * psz = pszCandidate;
      while(*psz != '\0' && (*psz == '.' || *psz == '_' || *psz == '-' || ansi_char_is_alphanumeric(*psz)))
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
      while(*psz != '\0' && (*psz == '.' || *psz == ':' || *psz == '@' || *psz == '_' || *psz == '-' || ansi_char_is_alphanumeric(*psz)))
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



} // namespace url


CLASS_DECL_ACME bool is_like_url_protocol(const char * psz)
{

   if (is_empty(psz))
   {

      return false;

   }

   if (::str::ch().is_letter(*psz))
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   while (::str::ch().is_letter_or_digit(*psz) || *psz == '-' || *psz == '_' || *psz == '.')
   {

      psz++;

   }

   if (*psz == ':' && (psz[1] == '\0' || (psz[1] == '/' && psz[2] == '/' && psz[3] == '\0')))
   {

      return true;

   }

   return false;

}



