#include "framework.h"
#include "acme/primitive/string/string.h"


namespace url
{

   bool is_url(const char * pszCandidate,const char ** ppszRequest)
   {
      const char * psz = pszCandidate;
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



} // namespace url


CLASS_DECL_ACME bool is_like_url_protocol(const char * psz)
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



