// Created by camilo on 2021-03-10 06:22 BRT ThomasBS_!!
#pragma once


namespace net
{


   class CLASS_DECL_APEX address_department :
      public object
   {
   public:


      string         m_host; ///< local hostname
      in_addr        m_ip; ///< local ip address
      string         m_addr; ///< local ip address in string format
      string         m_local_addr6; ///< local ip address in string format
      in6_addr       m_local_ip6; ///< local ipv6 address
      bool           m_local_resolved; ///< ResolveLocal has been called if true
      bool           m_bInitialized;


      class CLASS_DECL_APEX dns_cache_item :
         virtual public ::object
      {
      public:


         in_addr           m_ipaddr;
         ::duration m_durationLastChecked;
         bool              m_bOk;
         bool              m_bTimeout;


         dns_cache_item();
         dns_cache_item(const dns_cache_item& item);


         virtual ::stream& write(::stream& stream) const;
         virtual ::stream& read(::stream& stream);

         dns_cache_item& operator = (const dns_cache_item& item);

      };

      class CLASS_DECL_APEX reverse_cache_item :
         virtual public ::matter
      {
      public:

         ::net::address    m_address;
         string            m_strReverse;
         ::duration              m_durationLastChecked;
         bool              m_bOk;
         bool              m_bTimeout;
         bool              m_bProcessing;


         reverse_cache_item();
         reverse_cache_item(const reverse_cache_item& item);

         virtual ::stream& write(::stream& stream) const;
         virtual ::stream& read(::stream& stream);

         reverse_cache_item& operator = (const reverse_cache_item& item);

      };

      ::mutex                                            m_mutexCache;
      ::mutex                                            m_mutexReverseCache;
      string_map < dns_cache_item >                      m_mapCache;
      string_map < __pointer(reverse_cache_item) >       m_mapReverseCache;
      array < __pointer(reverse_cache_item) >            m_reversecacheaRequest;
      ::task_pointer                                     m_pthreadReverse;

      address_department();
      ~address_department() override;


      virtual ::e_status initialize(::object * pobject) override;
      virtual ::e_status destroy() override;

      virtual bool gudo_set();


      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_encode(const string& src);

      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      string rfc1738_decode(const string& src);

      bool isipv4(const string& str);

      bool isipv6(const string& str);

      bool convert(struct ::in_addr& l, const string& str, i32 ai_flags = 0);
      bool convert(struct ::in6_addr& l, const string& str, i32 ai_flags = 0);
      bool convert(string& str, const struct ::in_addr& ip);
      bool convert(string& str, const struct ::in6_addr& ip, bool mixed = false);

      i32 in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

      void ResolveLocal();

      const string& GetLocalHostname();

      in_addr GetLocalIP();

      const string& GetLocalAddress();

      const struct in6_addr& GetLocalIP6();

      const string& GetLocalAddress6();

      string Sa2String(sockaddr* psa);

      bool reverse(string& hostname, const ::net::address& address);

      bool reverse_schedule(reverse_cache_item* pitem);

      bool reverse_sync(reverse_cache_item* pitem);

      bool reverse(string& hostname, const string& number);


      bool u2service(const string& name, i32& service, i32 ai_flags);

      i32 service_port(const string& str, i32 flags = 0);

      string  service_name(i32 iPort, i32 flags = 0);


      string canonical_name(const ::net::address& address);

      string service_name(const ::net::address& address);

      string reverse_name(const ::net::address& address);


   };

   CLASS_DECL_APEX class address_department * address_department();

} // namespace net


