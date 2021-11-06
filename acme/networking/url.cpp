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




































