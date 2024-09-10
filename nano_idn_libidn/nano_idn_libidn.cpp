// Created by camilo on 2022-11-01 23:04 <3ThomasBorregaardSorensen!!
// From nano_archive_libarchive by camilo on 2024-06-02 17:28 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "nano_idn_libidn.h"


#if defined(ANDROID)
#include "idn/idna.h"
#elif defined(__APPLE__)
#include "idn/idna.h"
#elif defined(LINUX)
// apt install libidn11-dev
// dnf install libidn-devel
#include <idna.h>
#elif defined(__BSD__)
// apt install libidn11-dev
// dnf install libidn-devel
#include <idna.h>
#endif


namespace libidn
{


   namespace nano
   {


      namespace idn
      {


         idn::idn()
         {
         }


         idn::~idn()
         {

         }


         string idn::idn_to_punycode(const ::string &str)
         {

            char *psz = nullptr;

            Idna_rc rc = (Idna_rc) idna_to_ascii_8z(str, &psz, IDNA_ALLOW_UNASSIGNED);

            if (rc != IDNA_SUCCESS)
            {

               throw ::exception(::error_failed, idna_strerror(rc));

            }

            string strReturn(psz);

            free(psz);

            return strReturn;

         }


         string idn::idn_from_punycode(const ::string &str)
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

            char *psz = nullptr;

            Idna_rc rc = (Idna_rc) idna_to_unicode_8z8z(strTrimmed, &psz, IDNA_ALLOW_UNASSIGNED);

            if (rc != IDNA_SUCCESS)
            {

               throw ::exception(::error_failed, idna_strerror(rc));

            }

            string strReturn(psz);

            free(psz);

            return strReturn;

         }


      } // namespace idn


   } // namespace nano


} // namespace libidn



