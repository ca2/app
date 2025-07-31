// Created by camilo on 2021-03-10 06:22 BRT ThomasBS_!!
#pragma once


#include "address.h"
////#include "acme/prototype/prototype/object.h"
#include "_constant.h"


namespace networking
{


   class CLASS_DECL_APEX networking :
      public object
   {
   public:

      void * m_p2;


      interlocked_int                              m_lHttpGetSerial;

      
      ::pointer<::sockets::sockets>    m_psockets;


      ::networking::enum_address_type       m_eaddresstypePreferred;


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
      //   class ::time m_timeLastChecked;
      //   bool              m_bOk;
      //   bool              m_bTimeout;


      //   dns_cache_item();
      //   dns_cache_item(const dns_cache_item& item);


      //   void write(::binary_stream & stream) const override;
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
      //   class ::time        m_timeLastChecked;
      //   bool              m_bOk;
      //   bool              m_bTimeout;
      //   bool              m_bProcessing;


      //   reverse_cache_item();
      //   reverse_cache_item(const reverse_cache_item& item);

      //   void write(::binary_stream & stream) const override;
      //   virtual ::stream& read(::stream& stream);

      //   reverse_cache_item& operator = (const reverse_cache_item& item);

      //};

      //::pointer < ::mutex >                                            m_pmutexCache;
      //::pointer < ::mutex >                                            m_pmutexReverseCache;
      //string_map < dns_cache_item >                      m_mapCache;
      //string_map < ::pointer<reverse_cache_item >>      m_mapReverseCache;
      //array < ::pointer<reverse_cache_item >>           m_reversecacheaRequest;
      //::task_pointer                                     m_pthreadReverse;

      networking();
      ~networking() override;


      virtual void initialize(::particle * pparticle) override;
      virtual void destroy() override;


      //virtual bool convert(string& str, const struct ::in_addr& inaddr);
      //virtual bool convert(string& str, const struct ::in6_addr& inaddr6);

      virtual ::string last_error_message(long long llError = 0x8000000000000000);
      virtual ::string _last_error_message(long long llError);
      virtual long long last_error();

      virtual bool has_ip4_internet();
      virtual bool has_ip6_internet();


      virtual ::sockets::sockets * sockets() { return m_psockets; }

      virtual void on_socket_thread_start();

      virtual bool gudo_set();

      ///virtual ::sockets::listen_socket * new_listen_socket(const ::type_atom & type);


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

      virtual bool is_ip4(const ::scoped_string & scopedstr);

      virtual bool is_ip6(const ::scoped_string & scopedstr);


      virtual address_pointer create_address(const ::scoped_string & scopedstrAddress, enum_address_type eaddresstypePreferred = e_address_type_none, port_t port = 0);
      virtual address_pointer create_ip4_address(int iIp, port_t port = 0);
      //virtual bool convert(struct ::in_addr& l, const ::scoped_string & scopedstr, int ai_flags = 0);
      //virtual bool convert(struct ::in6_addr& l, const ::scoped_string & scopedstr, int ai_flags = 0);
      //virtual bool convert(string& str, const struct ::in_addr& ip);
      //virtual bool convert(string& str, const struct ::in6_addr& ip, bool mixed = false);

      //virtual int in6_addr_compare(struct ::in6_addr a, struct ::in6_addr b);

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

      virtual bool u2service(const string& name, int& service, int ai_flags);

      virtual int service_port(const ::scoped_string & scopedstr, int flags = 0);

      virtual string  service_name(int iPort, int flags = 0);


      virtual string canonical_name(::networking::address * address);

      virtual string service_name(::networking::address * address);

      virtual string reverse_name(::networking::address * address);

      //virtual int _select(::sockets::socket_handler * psockethandler, const class time & timeWait);

      virtual ::pointer<::networking::address>create_ip4_address(const ::scoped_string & scopedstrIp4, ::networking::port_t port = 0);

      virtual ::pointer<::networking::address>create_ip6_address(const ::scoped_string & scopedstrIp6, ::networking::port_t port = 0);

      /// item: networking::address
      virtual ::pointer < ::item_array > list_computers();

      /// item: networking::address
      virtual ::pointer < ::item_array > list_network_interfaces();


   };

   //CLASS_DECL_APEX class address_department * address_department();


} // namespace networking



