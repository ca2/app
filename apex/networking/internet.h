// Extracted part from acme/prototype/prototype/url to
// apex/networking/internet by
// camilo on 2024-08-27 19:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/department.h"


namespace internet
{


   class CLASS_DECL_APEX internet :
      virtual public ::acme::department
   {
   public:


      string_array_base                     m_straPublicDomainExtension;
      ::critical_section               m_csPublicDomainExtension;

      internet();

      ~internet() override;


      bool case_insensitive_is_protocol(const ::scoped_string& scopedstrUrl, const ::scoped_string& strProtocolCompare) const;


      bool is_http(const ::scoped_string& scopedstrUrl) const;
      bool is_https(const ::scoped_string& scopedstrUrll) const;
      bool is_http_or_https(const ::scoped_string& scopedstrUrl) const;
      bool is_ftp(const ::scoped_string& scopedstrUrl) const;
      bool is_ftps(const ::scoped_string& scopedstrUrl) const;
      bool is_ftp_or_ftps(const ::scoped_string& scopedstrUrl) const;
      bool is_common_internet_protocol(const ::scoped_string& scopedstrUrl) const;

      virtual bool locale_is_eu(const ::atom& pszLocale);
      virtual bool locale_is_asia(const ::atom& pszLocale);
      virtual bool locale_is_africa(const ::atom& pszLocale);
      virtual bool locale_is_america(const ::atom& pszLocale);
      virtual bool locale_is_caribe(const ::atom& pszLocale);
      virtual bool locale_is_middle_east(const ::atom& pszLocale);
      virtual bool locale_is_south_america(const ::atom& pszLocale);
      virtual bool locale_is_latin_america(const ::atom& pszLocale);
      virtual bool locale_is_north_america(const ::atom& pszLocale);
      virtual bool locale_is_central_america(const ::atom& pszLocale);
      virtual bool locale_is_oceania(const ::atom& pszLocale);

      virtual bool is_valid_public_domain(const ::scoped_string & scopedstrDomain);

      virtual string to_punycode(const ::scoped_string & scopedstr);
      virtual string from_punycode(const ::scoped_string & scopedstr);


   };

} // namespace internet
