// Created by camilo on 2022-11-01 23:04 <3ThomasBorregaardSorensen!!
// Merged acme/nano/idn and acme/operating_system/windows_common/idn.cpp by
// camilo on 2024-06-02 21:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "idn.h"
#include "acme/_operating_system.h"
#pragma comment(lib, "Normaliz.lib")


namespace windows_common
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


         ::string idn::idn_to_punycode(const ::scoped_string & scopedstr)
         {

            wstring wstr(scopedstr);

            int iSize = IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int)wstr.length(), nullptr, 0);

            wstring wstrTarget;

            WCHAR* pwszTarget = wstrTarget.get_buffer(iSize);

            IdnToAscii(IDN_RAW_PUNYCODE, wstr, (int)wstr.length(), pwszTarget, iSize);

            wstrTarget.release_buffer();

            string strTarget = wstrTarget;

            return ::transfer(strTarget);

         }


         ::string idn::idn_from_punycode(const ::scoped_string & scopedstr)
         {

            wstring wstrSource(scopedstr);

            int iSize = IdnToUnicode(IDN_RAW_PUNYCODE, wstrSource, (int)wstrSource.length(), nullptr, 0);

            wstring wstrTarget;

            auto pwszTarget = wstrTarget.get_buffer(iSize);

            IdnToUnicode(IDN_RAW_PUNYCODE, wstrSource, (int)wstrSource.length(), pwszTarget, iSize);

            wstrTarget.release_buffer(iSize);

            string strTarget = wstrTarget;

            return ::transfer(strTarget);

         }


      } // namespace idn


   } // namespace nano


} // namespace windows_common



