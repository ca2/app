// Extracted part from acme/prototype/prototype/url to
// apex/networking/internet by
// camilo on 2024-08-27 19:11 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "internet.h"
#include "acme/platform/system.h"
#include "acme/nano/nano.h"
#include "acme/nano/idn/idn.h"


namespace internet
{


   internet::internet()
   {


   }


   internet::~internet()
   {


   }


   bool internet::locale_is_eu(const ::atom& idLocale)
   {

      if (
         idLocale == "eu"
         || idLocale == "se"
         || idLocale == "at"
         || idLocale == "dk"
         || idLocale == "en_uk"
         || idLocale == "uk"
         || idLocale == "fi"
         || idLocale == "gr"
         || idLocale == "de"
         || idLocale == "nl"
         || idLocale == "be"
         || idLocale == "fr"
         || idLocale == "it"
         || idLocale == "pt"
         || idLocale == "cz"
         || idLocale == "lu"
         || idLocale == "ie"
         || idLocale == "no"
         || idLocale == "cy"
         || idLocale == "su"
         || idLocale == "lv"
         || idLocale == "li"
         || idLocale == "hn"
         || idLocale == "es"
         || idLocale == "sk"
         || idLocale == "cz"
         || idLocale == "si"
         || idLocale == "ro"
         || idLocale == "kz"
         || idLocale == "ru"
         || idLocale == "pl"
         || idLocale == "tr"
         || idLocale == "ee")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_asia(const ::atom& idLocale)
   {

      if (idLocale == "asia"
         || idLocale == "cn"
         || idLocale == "tw"
         || idLocale == "vn"
         || idLocale == "in"
         || idLocale == "kg"
         || idLocale == "kz"
         || idLocale == "kr"
         || idLocale == "my"
         || idLocale == "ph"
         || idLocale == "sg"
         || idLocale == "su"
         || idLocale == "ru"
         || idLocale == "zh"
         || idLocale == "hk"
         || idLocale == "ja"
         || idLocale == "jp"
         || idLocale == "tr")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_middle_east(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "sy"
         || idLocale == "tr"
         || idLocale == "il"
         || idLocale == "ps")
      {
         return true;
      }

      return false;

   }



   bool internet::locale_is_south_america(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "ar"
         || idLocale == "bo"
         || idLocale == "br"
         || idLocale == "cl"
         || idLocale == "co"
         || idLocale == "ec"
         || idLocale == "gs"
         || idLocale == "pe"
         || idLocale == "py"
         || idLocale == "uy"
         || idLocale == "ve"
         || idLocale == "amdesur")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_oceania(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "au"
         || idLocale == "oceania"
         || idLocale == "nz"
         || idLocale == "tl")
      {
         return true;
      }

      return false;

   }


   bool internet::locale_is_africa(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "ug"
         || idLocale == "sc"
         || idLocale == "cm"
         || idLocale == "za"
         || idLocale == "africa")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_latin_america(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "mx")
      {
         return true;
      }

      return locale_is_caribe(idLocale) || locale_is_central_america(idLocale) || locale_is_south_america(idLocale);

   }

   bool internet::locale_is_north_america(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "mx"
         || idLocale == "us"
         || idLocale == "ca")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_caribe(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "caribe")
         return true;

      if (idLocale == "ht"
         || idLocale == "cu"
         || idLocale == "tc")
      {
         return true;
      }

      return false;

   }


   bool internet::locale_is_central_america(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (strLocale == "central_america")
         return true;

      if (idLocale == "centralam")
         return true;

      if (idLocale == "bz")
      {
         return true;
      }

      return false;

   }

   bool internet::locale_is_america(const ::atom& idLocale)
   {

      string strLocale(idLocale);

      if (idLocale == "america")
         return true;

      return
         locale_is_central_america(idLocale)
         || locale_is_caribe(idLocale)
         || locale_is_south_america(idLocale)
         || locale_is_north_america(idLocale);

   }


   bool internet::is_valid_public_domain(const ::scoped_string & scopedstrDomain)
   {

      critical_section_lock lock(&m_csPublicDomainExtension);

      if (m_straPublicDomainExtension.is_empty())
      {

         system()->get_public_internet_domain_extension_list(m_straPublicDomainExtension);

      }

      bool bPublicDomainExtensionListSuffixesDomain = m_straPublicDomainExtension.case_insensitive_suffix_find_first(strDomain) >= 0;

      return bPublicDomainExtensionListSuffixesDomain;

   }



   bool internet::case_insensitive_is_protocol(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstrProtocolCompare) const
   {

      ::url::url url(scopedstrUrl);

      auto strProtocol = url.connect().protocol();

      return strProtocol.case_insensitive_equals(scopedstrProtocolCompare);

   }


   bool internet::is_http(const ::scoped_string& strUrl) const
   {

      return case_insensitive_is_protocol(strUrl, "http");

   }


   bool internet::is_https(const ::scoped_string& scopedstrUrl) const
   {

      return case_insensitive_is_protocol(scopedstrUrl, "https");

   }


   bool internet::is_http_or_https(const ::scoped_string& scopedstrUrl) const
   {

      return is_http(scopedstrUrl) || is_https(scopedstrUrl);

   }


      bool internet::is_ftp(const ::scoped_string& scopedstrUrl) const
   {

      return case_insensitive_is_protocol(scopedstrUrl, "ftp");

   }


   bool internet::is_ftps(const ::scoped_string& scopedstrUrl) const
   {

      return case_insensitive_is_protocol(scopedstrUrl, "ftps");

   }


   bool internet::is_ftp_or_ftps(const ::scoped_string & scopedstrUrl) const
   {

      return is_ftp(scopedstrUrl) || is_ftps(scopedstrUrl);

   }



   bool internet::is_common_internet_protocol(const ::scoped_string& scopedstrUrl) const
   {

      return is_http_or_https(scopedstrUrl) || is_ftp_or_ftps(scopedstrUrl);

   }


   
   string internet::to_punycode(const ::scoped_string & scopedstr)
   {

      return nano()->idn()->idn_to_punycode(str);

   }


   string internet::from_punycode(const ::scoped_string & scopedstr)
   {

      return nano()->idn()->idn_from_punycode(str);

   }




} // namespace internet



