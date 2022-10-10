#include "framework.h"
#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(FREEBSD)
#include <arpa/inet.h>
#endif

//#ifndef WINDOWS
//#include <arpa/inet.h>
//#endif

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
#include <netdb.h>
#endif

u32 c_inet_to_ui(const char * src)
{

   if(ansi_begins_ci(src, "0x"))
   {

      return (u32) ansi_to_i64(&src[2], nullptr, 16);

   }
   else if(ansi_begins(src, "0"))
   {

      return (u32) ansi_to_i64(&src[1], nullptr, 16);

   }
   else
   {

      return (u32) ansi_to_i64(src, nullptr, 10);

   }

}

#define XX 127
static const uchar index_hex[256] =
{
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   0, 1, 2, 3,  4, 5, 6, 7,  8, 9,XX,XX, XX,XX,XX,XX,
   XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,10,11,12, 13,14,15,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
   XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX, XX,XX,XX,XX,
};


#if defined(__APPLE__) || defined(FREEBSD)
#define pr_s6_addr16 __u6_addr.__u6_addr16
#define pr_s6_addr __u6_addr.__u6_addr8
#elif defined(LINUX)
#define pr_s6_addr16 __in6_u.__u6_addr16
#define pr_s6_addr __in6_u.__u6_addr8
#elif defined(ANDROID) || defined(SOLARIS)
#define pr_s6_addr16 s6_addr16
#define pr_s6_addr s6_addr
#else
#define pr_s6_addr16 u.Word
#define pr_s6_addr u.Byte
#endif

//
//namespace str
//{
//
///*
//* StringToV6Addr() returns 1 if the conversion succeeds,
//* or 0 if the input is not a valid IPv6 address string.
//* (Same as inet_pton(AF_INET6, string, addr).)
//*/
//CLASS_DECL_NETWORKING_BSD void from_string(in6_addr & addr, const ansichar * string)
//{
//   const uchar *s = (const uchar *)(const char *) string;
//   i32 department = 0;        /* index of the current department (a 16-bit
//                           * piece of the address */
//   i32 double_colon = -1;  /* index of the department after the first
//                           * 16-bit group of zeros represented by
//                           * the double colon */
//   u32 val = 0;
//   i32 len;
//
//   /* Handle initial (double) colon */
//   if (*s == ':')
//   {
//      if (s[1] != ':') throw parsing_exception("to in6_addr");
//      s += 2;
//      addr.pr_s6_addr16[0] = 0;
//      department = double_colon = 1;
//   }
//
//   while (*s)
//   {
//      if (department == 8) throw parsing_exception("to in6_addr (too long)"); /* too long */
//      if (*s == ':')
//      {
//         if (double_colon != -1) throw parsing_exception("to in6_addr (too double colons)"); /* two double colons */
//         addr.pr_s6_addr16[department++] = 0;
//         double_colon = department;
//         s++;
//         continue;
//      }
//      for (len = val = 0; len < 4 && index_hex[*s] != XX; len++)
//      {
//         val = (val << 4) + index_hex[*s++];
//      }
//      if (*s == '.')
//      {
//         if (len == 0) throw parsing_exception("to in6_addr (nothing between : and . )"); /* nothing between : and . */
//         break;
//      }
//      if (*s == ':')
//      {
//         s++;
//            
//         if (!*s) throw parsing_exception("to in6_addr (cannot end with single colon)"); /* cannot end with single colon */
//
//      }
//      else if (*s)
//      {
//            
//         throw parsing_exception("to in6_addr (bad character)"); /* bad character */
//
//      }
//      addr.pr_s6_addr16[department++] = htons((u16)val);
//   }
//
//   if (*s == '.')
//   {
//      /* Have a trailing v4 format address */
//      if (department > 6) throw parsing_exception("to in6_addr (not enough room)"); /* not enough room */
//
//      /*
//      * The number before the '.' is decimal, but we parsed it
//      * as hex.  That means it is in BCD.  Check it for validity
//      * and convert it to binary.
//      */
//      if (val > 0x0255 || (val & 0xf0) > 0x90 || (val & 0xf) > 9) throw parsing_exception("to in6_addr (I)");
//      val = (val >> 8) * 100 + ((val >> 4) & 0xf) * 10 + (val & 0xf);
//      addr.pr_s6_addr[2 * department] = val;
//
//      s++;
//      val = index_hex[*s++];
//      if (val > 9) throw parsing_exception("to in6_addr (val > 9 .1)");
//      while (*s >= '0' && *s <= '9')
//      {
//         val = val * 10 + *s++ - '0';
//         if (val > 255) throw parsing_exception("to in6_addr (val > 255 .1)");
//      }
//      if (*s != '.') throw parsing_exception("to in6_addr (must have exactly 4 decimal numbers (I))"); /* must have exactly 4 decimal numbers */
//      addr.pr_s6_addr[2 * department + 1] = val;
//      department++;
//
//      s++;
//      val = index_hex[*s++];
//      if (val > 9) throw parsing_exception("to in6_addr (val > 9 .2)");
//      while (*s >= '0' && *s <= '9')
//      {
//         val = val * 10 + *s++ - '0';
//         if (val > 255) throw parsing_exception("to in6_addr (val > 255 .2)");
//      }
//      if (*s != '.') parsing_exception("to in6_addr (must have exactly 4 decimal numbers (II)"); /* must have exactly 4 decimal numbers */
//      addr.pr_s6_addr[2 * department] = val;
//
//      s++;
//      val = index_hex[*s++];
//      if (val > 9) throw parsing_exception("to in6_addr (val > 9 .3)");
//      while (*s >= '0' && *s <= '9')
//      {
//         val = val * 10 + *s++ - '0';
//         if (val > 255) throw parsing_exception("to in6_addr (val > 255 .3)");
//      }
//      if (*s) throw parsing_exception("to in6_addr (must have exactly 4 decimal numbers (III))"); /* must have exactly 4 decimal numbers */
//      addr.pr_s6_addr[2 * department + 1] = val;
//      department++;
//   }
//
//   if (double_colon != -1)
//   {
//      /* Stretch the double colon */
//      i32 tosection;
//      i32 ncopy = department - double_colon;
//      for (tosection = 7; ncopy--; tosection--)
//      {
//         addr.pr_s6_addr16[tosection] =
//         addr.pr_s6_addr16[double_colon + ncopy];
//      }
//      while (tosection >= double_colon)
//      {
//         addr.pr_s6_addr16[tosection--] = 0;
//      }
//   }
//   else if (department != 8)
//   {
//      throw parsing_exception("to in6_addr (too i16)"); /* too i16 */
//   }
//}
//
//#undef XX
//
//static const char *basis_hex = "0123456789abcdef";



///*
//* V6AddrToString() returns a pointer to the buffer containing
//* the text string if the conversion succeeds, and nullptr otherwise.
//* (Same as inet_ntop(AF_INET6, addr, buf, size), except that errno
//* is not set on failure.)
//*/
//CLASS_DECL_NETWORKING_BSD ::string __string(const in6_addr  & addr)
//{
//
//   ::string str;
//
//#define STUFF(c) { str += ((char)(c)); }
//
//   i32 double_colon = -1;          /* index of the first 16-bit
//                                 * group of zeros represented
//                                 * by the double colon */
//   i32 double_colon_length = 1;    /* use double colon only if
//                                 * there are two or more 16-bit
//                                 * groups of zeros */
//   i32 zero_length;
//   i32 department;
//   u32 val;
//
//   /* Scan to find the placement of the double colon */
//   for (department = 0; department < 8; department++)
//   {
//      if (addr.pr_s6_addr16[department] == 0)
//      {
//         zero_length = 1;
//         department++;
//         while (department < 8 && addr.pr_s6_addr16[department] == 0)
//         {
//            zero_length++;
//            department++;
//         }
//         /* Select the longest sequence of zeros */
//         if (zero_length > double_colon_length)
//         {
//            double_colon = department - zero_length;
//            double_colon_length = zero_length;
//         }
//      }
//   }
//
//   /* Now start converting to a string */
//   department = 0;
//
//   if (double_colon == 0)
//   {
//      if (double_colon_length == 6 ||
//            (double_colon_length == 5 && addr.pr_s6_addr16[5] == 0xffff))
//      {
//         /* ipv4 format address */
//         STUFF(':');
//         STUFF(':');
//         if (double_colon_length == 5)
//         {
//            STUFF('f');
//            STUFF('f');
//            STUFF('f');
//            STUFF('f');
//            STUFF(':');
//         }
//         if (addr.pr_s6_addr[12] > 99) STUFF(addr.pr_s6_addr[12]/100 + '0');
//         if (addr.pr_s6_addr[12] > 9) STUFF((addr.pr_s6_addr[12]%100)/10 + '0');
//         STUFF(addr.pr_s6_addr[12]%10 + '0');
//         STUFF('.');
//         if (addr.pr_s6_addr[13] > 99) STUFF(addr.pr_s6_addr[13]/100 + '0');
//         if (addr.pr_s6_addr[13] > 9) STUFF((addr.pr_s6_addr[13]%100)/10 + '0');
//         STUFF(addr.pr_s6_addr[13]%10 + '0');
//         STUFF('.');
//         if (addr.pr_s6_addr[14] > 99) STUFF(addr.pr_s6_addr[14]/100 + '0');
//         if (addr.pr_s6_addr[14] > 9) STUFF((addr.pr_s6_addr[14]%100)/10 + '0');
//         STUFF(addr.pr_s6_addr[14]%10 + '0');
//         STUFF('.');
//         if (addr.pr_s6_addr[15] > 99) STUFF(addr.pr_s6_addr[15]/100 + '0');
//         if (addr.pr_s6_addr[15] > 9) STUFF((addr.pr_s6_addr[15]%100)/10 + '0');
//         STUFF(addr.pr_s6_addr[15]%10 + '0');
//         STUFF('\0');
////            return str;
//      }
//   }
//
//   while (department < 8)
//   {
//      if (department == double_colon)
//      {
//         STUFF(':');
//         STUFF(':');
//         department += double_colon_length;
//         continue;
//      }
//      val = ntohs(addr.pr_s6_addr16[department]);
//      if (val > 0xfff)
//      {
//         STUFF(basis_hex[val >> 12]);
//      }
//      if (val > 0xff)
//      {
//         STUFF(basis_hex[(val >> 8) & 0xf]);
//      }
//      if (val > 0xf)
//      {
//         STUFF(basis_hex[(val >> 4) & 0xf]);
//      }
//      STUFF(basis_hex[val & 0xf]);
//      department++;
//      if (department < 8 && department != double_colon) STUFF(':');
//   }
//   STUFF('\0');
////   return str;
//#undef STUFF
//}


//} // namespace str


struct c_in_addr
{
   union
   {
      struct
      {
         u8	s_b1;
         u8	s_b2;
         u8	s_b3;
         u8	s_b4;
      } S_un_b;

      u32 S_addr;
   } S_un;
};

//namespace str
//{

//CLASS_DECL_NETWORKING_BSD void from_string(in_addr & addrParam, const ansichar * string)
//{
//
//   c_in_addr & addr = (c_in_addr &) addrParam;
//
//
//   string_array stra;
//
//   stra.add_tokens(string, ".");
//
//   if(stra.get_count() != 4)
//      throw parsing_exception("to in_addr (stra.get_count() != 4)");
//
//   i32 i1 = ansi_to_i32(stra[0]);
//
//   if(i1 < 0 || i1 > 255)
//      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (I)");
//
//   i32 i2 = ansi_to_i32(stra[1]);
//
//   if(i2 < 0 || i2 > 255)
//      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (II)");
//
//   i32 i3 = ansi_to_i32(stra[2]);
//
//   if(i3 < 0 || i3 > 255)
//      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (III)");
//
//   i32 i4 = ansi_to_i32(stra[3]);
//
//   if(i4 < 0 || i4 > 255)
//      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (IV)");
//
//   addr.S_un.S_un_b.s_b1 = i1;
//
//   addr.S_un.S_un_b.s_b2 = i2;
//
//   addr.S_un.S_un_b.s_b3 = i3;
//
//   addr.S_un.S_un_b.s_b4 = i4;
//
//   //addr.S_un.S_addr = HTONL(addr.S_un.S_addr);
//
//   //return true;
//
//}

//} // namespace str

//inline string ip_to_string(byte b1, byte b2, byte b3, byte b4)
//{
//
//   string str;
//
//   char * psz = str.get_string_buffer(20);
//
//   ansi_concatenate_i64(psz, b1);
//
//   ansi_concatenate(psz, ".");
//
//   ansi_concatenate_i64(psz, b2);
//
//   ansi_concatenate(psz, ".");
//
//   ansi_concatenate_i64(psz, b3);
//
//   ansi_concatenate(psz, ".");
//
//   ansi_concatenate_i64(psz, b4);
//
//   str.release_string_buffer();
//
//   return str;
//
//}


CLASS_DECL_NETWORKING_BSD::string __string_inet_ntop(int iFamily, const void * paddr)
{

   char sz[INET6_ADDRSTRLEN * 2];

   if (!inet_ntop(iFamily, paddr, sz, sizeof(sz)))
   {

      int iErrNo = errno;

      auto estatus = errno_to_status(iErrNo);

      throw ::exception(estatus, "Failed to convert IP4 Address to text");

   }

   return sz;

}


CLASS_DECL_NETWORKING_BSD::string __string(const in_addr & addr)
{

   return __string_inet_ntop(AF_INET, &addr);

}


CLASS_DECL_NETWORKING_BSD::string __string(const in6_addr & addr)
{

   return __string_inet_ntop(AF_INET6, &addr);

}


CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in & addr)
{

   string strIp = __string(addr.sin_addr);

   if (addr.sin_port > 0)
   {

      string strAddress;

      strAddress = strIp + ":" + __string(addr.sin_port);

      return strAddress;

   }

   return strIp;


}


CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr_in6 &  addr)
{

   string strIp = __string(addr.sin6_addr);

   if (addr.sin6_port > 0)
   {

      string strAddress;

      strAddress.format("[%s]:%d", strIp.c_str(), addr.sin6_port);

      return strAddress;

   }

   return strIp;

}


CLASS_DECL_NETWORKING_BSD ::string __string(const sockaddr & addr)
{

   if(addr.sa_family == AF_INET)
   {

      return __string((sockaddr_in &)addr);

   }
   else if(addr.sa_family == AF_INET6)
   {

      return __string((sockaddr_in6 &)addr);

   }
   else
   {

      throw ::exception(error_bad_argument, "Unexpected IP Family " + __string(addr.sa_family));

   }

}


//CLASS_DECL_NETWORKING_BSD void from_string(const sockaddr & addr, string & str)
//{
//
//   if (addr.sa_family == AF_INET)
//   {
//
//      from_string(*(sockaddr_in *)addr.sa_data, str);
//
//   }
//   else if (addr.sa_family == AF_INET6)
//   {
//
//      from_string(*(sockaddr_in6 *)addr.sa_data, str);
//
//   }
//   else
//   {
//
//      throw ::exception(error_bad_argument, "unexpected address family");
//
//   }
//
//}

//
//} // namespace str


CLASS_DECL_NETWORKING_BSD i32 c_inet_pton(i32 af, const char *src, void *dst)
{

   if(af == AF_INET)
   {

      in_addr & addr = *(in_addr *) dst;

      ::from_string(addr, src);

      return 1;

   }
   else if(af == AF_INET6)
   {

      in6_addr & addr = *(in6_addr *) dst;

      ::from_string(addr, src);

      return 1;

   }
   else
   {

      return 0;

   }

}


//CLASS_DECL_NETWORKING_BSD string c_inet_ntop(i32 af, const void *src)
//{
//
//   string str;
//
//   if(af == AF_INET)
//   {
//
//      in_addr & addr = *(in_addr *)src;
//
//      ::to_string(str, addr);
//
//   }
//   else if(af == AF_INET6)
//   {
//
//      in6_addr & addr = *(in6_addr *)src;
//
//      ::to_string(str, addr);
//
//   }
//
//   return str;
//
//}
//

CLASS_DECL_NETWORKING_BSD void from_string(in_addr & addr, const char * src)
{

   int iRet = inet_pton(AF_INET, src, &addr);

   if (iRet == 0)
   {

      throw exception(error_parsing, "Unknown IP4 address format : " + ::string(src));

   }
   else if(iRet < 0)
   {

      throw exception(error_failed);

   }

}


CLASS_DECL_NETWORKING_BSD void from_string(in_addr6 & addr, const char * src)
{

   int iRet = inet_pton(AF_INET6, src, &addr);

   if (iRet == 0)
   {

      throw exception(error_parsing, "Unknown IP4 address format : " + ::string(src));

   }
   else if(iRet < 0)
   {

      throw exception(error_failed);

   }

}


CLASS_DECL_NETWORKING_BSD string c_gethostbyname(const char * hostname)
{

//#ifdef _UWP
//
//   return (ref memory_new ::winrt::Windows::Networking::HostName(string(hostname)))->DisplayName;
//
//#else

   struct hostent * pentry = gethostbyname(hostname);

   return __string_inet_ntop(pentry->h_addrtype, pentry->h_addr_list[0]);

//#endif

}






namespace net
{


   i32 family_len(i32 family)
   {

      if (family == AF_INET)
      {

         return sizeof(sockaddr_in);

      }
      else if (family == AF_INET6)
      {

         return sizeof(sockaddr_in6);

      }
      else if (family == AF_UNSPEC)
      {

         return 0;

      }
      else
      {
       
         throw ::not_implemented();

      }

   }


} // namespace net







// namespace str
// {


   CLASS_DECL_NETWORKING_BSD string to_string(const struct sockaddr & sockaddr)
   {

      string str;

      char sz[INET6_ADDRSTRLEN + INET_ADDRSTRLEN];

      switch (sockaddr.sa_family)
      {
      case AF_INET:
         inet_ntop(AF_INET, &(((struct sockaddr_in &)sockaddr).sin_addr), sz, sizeof(sz));
         break;

      case AF_INET6:
         inet_ntop(AF_INET6, &(((struct sockaddr_in6 &)sockaddr).sin6_addr), sz, sizeof(sz));
         break;

      default:
         strncpy(sz, "(Unknown Address Family)", sizeof(sz));
         break;
      };

      str = sz;

      return str;

   }


// } // namespace str




