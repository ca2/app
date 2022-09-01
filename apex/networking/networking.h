// Created by camilo on 2021-03-10 06:22 BRT ThomasBS_!!
#pragma once


#include "address.h"


namespace networking
{


   class CLASS_DECL_APEX networking :
      public object
   {
   public:

      interlocked_i32                              m_lHttpGetSerial;

      
      __pointer(::sockets::sockets)     m_psockets;


      //string         m_host; ///< local hostname
      //in_addr        m_ip; ///< local ip address
      //string         m_addr; ///< local ip address in string format
      //string         m_local_addr6; ///< local ip address in string format
      //in6_addr       m_local_ip6; ///< local ipv6 address
      //bool           m_local_resolved; ///< ResolveLocal has been called if true
      //bool           m_bInitialized;


      //class CLASS_DECL_APEX dns_cache_item :
      //   virtual public ::object
      //{
      //public:


      //   in_addr           m_ipaddr;
      //   ::duration m_durationLastChecked;
      //   bool              m_bOk;
      //   bool              m_bTimeout;


      //   dns_cache_item();
      //   dns_cache_item(const dns_cache_item& item);


      //   virtual ::stream& write(::stream& stream) const;
      //   virtual ::stream& read(::stream& stream);

      //   dns_cache_item& operator = (const dns_cache_item& item);

      //};

      //class CLASS_DECL_APEX reverse_cache_item :
      //   virtual public ::matter
      //{
      //public:

      //   
      //   ::networking::address    m_address;
      //   string            m_strReverse;
      //   ::duration        m_durationLastChecked;
      //   bool              m_bOk;
      //   bool              m_bTimeout;
      //   bool              m_bProcessing;


      //   reverse_cache_item();
      //   reverse_cache_item(const reverse_cache_item& item);

      //   virtual ::stream& write(::stream& stream) const;
      //   virtual ::stream& read(::stream& stream);

      //   reverse_cache_item& operator = (const reverse_cache_item& item);

      //};

      //::mutex                                            m_mutexCache;
      //::mutex                                            m_mutexReverseCache;
      //string_map < dns_cache_item >                      m_mapCache;
      //string_map < __pointer(reverse_cache_item) >       m_mapReverseCache;
      //array < __pointer(reverse_cache_item) >            m_reversecacheaRequest;
      //::task_pointer                                     m_pthreadReverse;

      networking();
      ~networking() override;


      virtual void initialize(::object * pobject) override;
      virtual void destroy() override;


      virtual ::sockets::sockets * sockets() { return m_psockets; }

      virtual bool gudo_set();


      /*
      * Encode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      virtual string rfc1738_encode(const string& src);

      /*
      * Decode string per RFC1738 URL encoding rules
      * tnx rstaveley
      */
      virtual string rfc1738_decode(const string& src);

      virtual bool isipv4(const string& str);

      virtual bool isipv6(const string& str);

      //virtual bool convert(struct ::in_addr& l, const string& str, i32 ai_flags = 0);
      //virtual bool convert(struct ::in6_addr& l, const string& str, i32 ai_flags = 0);
      //virtual bool convert(string& str, const struct ::in_addr& ip);
      //virtual bool convert(string& str, const struct ::in6_addr& ip, bool mixed = false);

      //virtual i32 in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

      //virtual void ResolveLocal();

      //virtual const string& GetLocalHostname();

      ////virtual in_addr GetLocalIP();

      //virtual const string& GetLocalAddress();

      //virtual const struct in6_addr& GetLocalIP6();

      //virtual const string& GetLocalAddress6();

      //virtual string Sa2String(sockaddr* psa);

      virtual bool reverse(string& hostname, ::networking::address * paddress);

      //virtual bool reverse_schedule(reverse_cache_item* pitem);

      //virtual bool reverse_sync(reverse_cache_item* pitem);

      virtual bool reverse(string& hostname, const string& number);
      
      virtual string ip_reverse(const string & number);

      virtual bool u2service(const string& name, i32& service, i32 ai_flags);

      virtual i32 service_port(const string& str, i32 flags = 0);

      virtual string  service_name(i32 iPort, i32 flags = 0);


      virtual string canonical_name(::networking::address * address);

      virtual string service_name(::networking::address * address);

      virtual string reverse_name(::networking::address * address);


   };

   //CLASS_DECL_APEX class address_department * address_department();


} // namespace networking



