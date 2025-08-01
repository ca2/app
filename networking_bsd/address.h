#pragma once


#include "apex/networking/address.h"


namespace networking_bsd
{


   class CLASS_DECL_NETWORKING_BSD address :
      virtual public ::networking::address
   {
   public:


#ifdef BSD_STYLE_SOCKETS

      union address_union
      {


         struct address_struct
         {


#if defined(FREEBSD) || defined(__APPLE__) || defined(OPENBSD)

            unsigned char m_len;
            unsigned char m_uchFamily;


#else // !FREEBSD

            unsigned short m_ushFamily;

#endif // !FREEBSD

            unsigned short m_port;

#if defined(FREEBSD) || defined(__APPLE__) || defined(OPENBSD)


            void set_family(int family, int len)
            {

               m_len = len;

               m_uchFamily = family;

            }


            void set_family(int family)
            {

               set_family(family, family_len(family));

            }

            unsigned char get_family() const
            {

               return m_uchFamily;

            }

            int get_family_len() const
            {

               return m_len;

            }


#else // !FREEBSD

      void set_family(int family)
      {

         m_ushFamily = family;

      }

      unsigned short get_family() const
      {

         return m_ushFamily;

      }


      int get_family_len() const
      {

         return family_len(m_ushFamily);

      }

#endif // !FREEBSD

         } s;


         struct sockaddr_in      m_addr;
         struct sockaddr_in6     m_addr6;
         struct sockaddr         m_sa;


      } u;

      int   m_iLen;


#elif defined(WINRT_SOCKETS)

      //::winrt::Windows::Networking::HostName^ m_hostname;
      //::networking::port_t      m_port;


#else

#error "what sockets?"


#endif


      address();
      ~address();


      //address & operator = (const address & address);
      //bool operator == (const address & address) const;

      void set_address(::networking::address * paddress);
      void set_family(int family, ::networking::port_t port = 0);
      //void set_address(const ::scoped_string & scopedstrAddress, ::networking::port_t port = 0);
      //void set_address(::particle * pparticle, const ::scoped_string & scopedstrAddress, const ::scoped_string & scopedstrServiceName);
#if defined(BSD_STYLE_SOCKETS)
      void set_address(const in_addr & a, ::networking::port_t port = 0);
      void set_address(const in6_addr & a, ::networking::port_t port = 0);
      void set_address(const sockaddr_in & a);
      void set_address(const sockaddr_in6 & a, int iLen = -1);
      void set_address(const sockaddr & sa, int iLen = -1);
#endif

      ::networking_bsd::address & operator=(const ::networking_bsd::address & address);

      string get_display_number() const override;

      ::networking::port_t get_service_number() const override;
      ::networking::port_t use_address_service_number_as_offset_for_base_port(::networking::port_t portBase) const override;
      void set_service_number(::networking::port_t port) override;


      bool is_in_same_net(::networking::address * paddress, ::networking::address * paddressMask) const override;
      bool is_equal(::networking::address * paddress) const override;


      bool is_ip4() const override;
      bool is_ip6() const override;


      inline bool _is_ip4() const { return u.m_sa.sa_family == AF_INET; }
      inline bool _is_ip6() const { return u.m_sa.sa_family == AF_INET6; }


      bool is_valid() const override;


      inline int get_family() const;


#if defined(BSD_STYLE_SOCKETS)

      inline sockaddr * sa();
      inline const sockaddr * sa() const;
      int sa_len() const;

      void * addr_data();

#endif

      //void parse_string(const ::scoped_string & scopedstrAddress);
      //string get_string() const;

#ifdef BSD_STYLE_SOCKETS
      inline void SetFlowinfo(unsigned int x);
      inline unsigned int GetFlowinfo();
#endif

#ifndef WINDOWS
      inline void SetScopeId(unsigned int x);
      inline unsigned int GetScopeId();
#endif

      void sync_os_address() override;
      void sync_os_service() override;

      //void write(::binary_stream & stream) const override;
      //void read(::binary_stream & stream) override;


   };


   inline int address::get_family() const
   {

#if defined(BSD_STYLE_SOCKETS)

      return u.s.get_family();

#elif defined(WINRT_SOCKETS)

      if (is_ipv4())
      {

         return AF_INET;

      }
      else if (_is_ip6())
      {

         return AF_INET6;

      }
      else
      {

         return -1;

      }

#else

#error "what socket?"

#endif


   }




#ifdef BSD_STYLE_SOCKETS


   inline sockaddr * address::sa()
   {

      return &u.m_sa;

   }


   inline const sockaddr * address::sa() const
   {

      return &u.m_sa;

   }


#endif


#ifdef BSD_STYLE_SOCKETS


   inline void address::SetFlowinfo(unsigned int x)
   {
      ASSERT(_is_ip6());
      u.m_addr6.sin6_flowinfo = x;
   }


   inline unsigned int address::GetFlowinfo()
   {
      ASSERT(_is_ip6());
      return u.m_addr6.sin6_flowinfo;
   }


#endif


#ifndef WINDOWS

   inline void address::SetScopeId(unsigned int x)
   {
      ASSERT(_is_ip6());
      u.m_addr6.sin6_scope_id = x;
   }


   inline unsigned int address::GetScopeId()
   {
      ASSERT(_is_ip6());
      return u.m_addr6.sin6_scope_id;
   }

#endif



} // namespace sockets_bsd





//inline void __exchange(::stream& s, ::networking::address& address);



