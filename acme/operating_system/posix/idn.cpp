// Created by camilo on 2022-11-01 23:04 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/exception/exception.h"
#include "acme/primitive/string/string.h"


#if defined(ANDROID)
#include "idn/idna.h"
#elif defined(__APPLE__)
#include "idn/idna.h"
#elif defined(LINUX)
// apt install libidn11-dev
// dnf install libidn-devel
#include <idna.h>
#elif defined(FREEBSD)
// apt install libidn11-dev
// dnf install libidn-devel
#include <idna.h>
#endif


string idn_to_punycode(const ::string & str)
{

   char * psz = nullptr;

   Idna_rc rc = (Idna_rc)idna_to_ascii_8z(str, &psz, IDNA_ALLOW_UNASSIGNED);

   if (rc != IDNA_SUCCESS)
   {

      throw ::exception(idna_strerror(rc));

   }

   string strReturn(psz);

   free(psz);

   return strReturn;

}


string idn_from_punycode(const ::string & str)
{
if (str.is_empty())
{

   return "";

}

string strTrimmed(str);

strTrimmed.trim();

if (strTrimmed.is_empty())
{

   return "";

}

char * psz = nullptr;

Idna_rc rc = (Idna_rc)idna_to_unicode_8z8z(strTrimmed, &psz, IDNA_ALLOW_UNASSIGNED);

if (rc != IDNA_SUCCESS)
{

   throw ::exception(idna_strerror(rc));

}

string strReturn(psz);

free(psz);

return strReturn;

}