#include "framework.h"
#include "apex/networking/sockets/_sockets.h"
#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
#include <arpa/inet.h>
#endif

//#ifndef WINDOWS
//#include <arpa/inet.h>
//#endif

#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
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


#if defined(__APPLE__)
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


namespace str
{

   /*
   * StringToV6Addr() returns 1 if the conversion succeeds,
   * or 0 if the input is not a valid IPv6 address string.
   * (Same as inet_pton(AF_INET6, string, addr).)
   */
   CLASS_DECL_APEX void to(in6_addr & addr, const ansichar * string)
   {
      const uchar *s = (const uchar *)(const char *) string;
      i32 department = 0;        /* index of the current department (a 16-bit
                              * piece of the address */
      i32 double_colon = -1;  /* index of the department after the first
                              * 16-bit group of zeros represented by
                              * the double colon */
      u32 val = 0;
      i32 len;

      /* Handle initial (double) colon */
      if (*s == ':')
      {
         if (s[1] != ':') throw parsing_exception("to in6_addr");
         s += 2;
         addr.pr_s6_addr16[0] = 0;
         department = double_colon = 1;
      }

      while (*s)
      {
         if (department == 8) throw parsing_exception("to in6_addr (too long)"); /* too long */
         if (*s == ':')
         {
            if (double_colon != -1) throw parsing_exception("to in6_addr (too double colons)"); /* two double colons */
            addr.pr_s6_addr16[department++] = 0;
            double_colon = department;
            s++;
            continue;
         }
         for (len = val = 0; len < 4 && index_hex[*s] != XX; len++)
         {
            val = (val << 4) + index_hex[*s++];
         }
         if (*s == '.')
         {
            if (len == 0) throw parsing_exception("to in6_addr (nothing between : and . )"); /* nothing between : and . */
            break;
         }
         if (*s == ':')
         {
            s++;
            
            if (!*s) throw parsing_exception("to in6_addr (cannot end with single colon)"); /* cannot end with single colon */

         }
         else if (*s)
         {
            
            throw parsing_exception("to in6_addr (bad character)"); /* bad character */

         }
         addr.pr_s6_addr16[department++] = htons((u16)val);
      }

      if (*s == '.')
      {
         /* Have a trailing v4 format address */
         if (department > 6) throw parsing_exception("to in6_addr (not enough room)"); /* not enough room */

         /*
         * The number before the '.' is decimal, but we parsed it
         * as hex.  That means it is in BCD.  Check it for validity
         * and convert it to binary.
         */
         if (val > 0x0255 || (val & 0xf0) > 0x90 || (val & 0xf) > 9) throw parsing_exception("to in6_addr (I)");
         val = (val >> 8) * 100 + ((val >> 4) & 0xf) * 10 + (val & 0xf);
         addr.pr_s6_addr[2 * department] = val;

         s++;
         val = index_hex[*s++];
         if (val > 9) throw parsing_exception("to in6_addr (val > 9 .1)");
         while (*s >= '0' && *s <= '9')
         {
            val = val * 10 + *s++ - '0';
            if (val > 255) throw parsing_exception("to in6_addr (val > 255 .1)");
         }
         if (*s != '.') throw parsing_exception("to in6_addr (must have exactly 4 decimal numbers (I))"); /* must have exactly 4 decimal numbers */
         addr.pr_s6_addr[2 * department + 1] = val;
         department++;

         s++;
         val = index_hex[*s++];
         if (val > 9) throw parsing_exception("to in6_addr (val > 9 .2)");
         while (*s >= '0' && *s <= '9')
         {
            val = val * 10 + *s++ - '0';
            if (val > 255) throw parsing_exception("to in6_addr (val > 255 .2)");
         }
         if (*s != '.') parsing_exception("to in6_addr (must have exactly 4 decimal numbers (II)"); /* must have exactly 4 decimal numbers */
         addr.pr_s6_addr[2 * department] = val;

         s++;
         val = index_hex[*s++];
         if (val > 9) throw parsing_exception("to in6_addr (val > 9 .3)");
         while (*s >= '0' && *s <= '9')
         {
            val = val * 10 + *s++ - '0';
            if (val > 255) throw parsing_exception("to in6_addr (val > 255 .3)");
         }
         if (*s) throw parsing_exception("to in6_addr (must have exactly 4 decimal numbers (III))"); /* must have exactly 4 decimal numbers */
         addr.pr_s6_addr[2 * department + 1] = val;
         department++;
      }

      if (double_colon != -1)
      {
         /* Stretch the double colon */
         i32 tosection;
         i32 ncopy = department - double_colon;
         for (tosection = 7; ncopy--; tosection--)
         {
            addr.pr_s6_addr16[tosection] =
            addr.pr_s6_addr16[double_colon + ncopy];
         }
         while (tosection >= double_colon)
         {
            addr.pr_s6_addr16[tosection--] = 0;
         }
      }
      else if (department != 8)
      {
         throw parsing_exception("to in6_addr (too i16)"); /* too i16 */
      }
   }

   #undef XX

   static const char *basis_hex = "0123456789abcdef";



   /*
   * V6AddrToString() returns a pointer to the buffer containing
   * the text string if the conversion succeeds, and nullptr otherwise.
   * (Same as inet_ntop(AF_INET6, addr, buf, size), except that errno
   * is not set on failure.)
   */
   CLASS_DECL_APEX void from(string & str, const in6_addr  & addr)
   {

      str.Empty();

   #define STUFF(c) { str += ((char)(c)); }

      i32 double_colon = -1;          /* index of the first 16-bit
                                    * group of zeros represented
                                    * by the double colon */
      i32 double_colon_length = 1;    /* use double colon only if
                                    * there are two or more 16-bit
                                    * groups of zeros */
      i32 zero_length;
      i32 department;
      u32 val;

      /* Scan to find the placement of the double colon */
      for (department = 0; department < 8; department++)
      {
         if (addr.pr_s6_addr16[department] == 0)
         {
            zero_length = 1;
            department++;
            while (department < 8 && addr.pr_s6_addr16[department] == 0)
            {
               zero_length++;
               department++;
            }
            /* Select the longest sequence of zeros */
            if (zero_length > double_colon_length)
            {
               double_colon = department - zero_length;
               double_colon_length = zero_length;
            }
         }
      }

      /* Now start converting to a string */
      department = 0;

      if (double_colon == 0)
      {
         if (double_colon_length == 6 ||
               (double_colon_length == 5 && addr.pr_s6_addr16[5] == 0xffff))
         {
            /* ipv4 format address */
            STUFF(':');
            STUFF(':');
            if (double_colon_length == 5)
            {
               STUFF('f');
               STUFF('f');
               STUFF('f');
               STUFF('f');
               STUFF(':');
            }
            if (addr.pr_s6_addr[12] > 99) STUFF(addr.pr_s6_addr[12]/100 + '0');
            if (addr.pr_s6_addr[12] > 9) STUFF((addr.pr_s6_addr[12]%100)/10 + '0');
            STUFF(addr.pr_s6_addr[12]%10 + '0');
            STUFF('.');
            if (addr.pr_s6_addr[13] > 99) STUFF(addr.pr_s6_addr[13]/100 + '0');
            if (addr.pr_s6_addr[13] > 9) STUFF((addr.pr_s6_addr[13]%100)/10 + '0');
            STUFF(addr.pr_s6_addr[13]%10 + '0');
            STUFF('.');
            if (addr.pr_s6_addr[14] > 99) STUFF(addr.pr_s6_addr[14]/100 + '0');
            if (addr.pr_s6_addr[14] > 9) STUFF((addr.pr_s6_addr[14]%100)/10 + '0');
            STUFF(addr.pr_s6_addr[14]%10 + '0');
            STUFF('.');
            if (addr.pr_s6_addr[15] > 99) STUFF(addr.pr_s6_addr[15]/100 + '0');
            if (addr.pr_s6_addr[15] > 9) STUFF((addr.pr_s6_addr[15]%100)/10 + '0');
            STUFF(addr.pr_s6_addr[15]%10 + '0');
            STUFF('\0');
   //            return str;
         }
      }

      while (department < 8)
      {
         if (department == double_colon)
         {
            STUFF(':');
            STUFF(':');
            department += double_colon_length;
            continue;
         }
         val = ntohs(addr.pr_s6_addr16[department]);
         if (val > 0xfff)
         {
            STUFF(basis_hex[val >> 12]);
         }
         if (val > 0xff)
         {
            STUFF(basis_hex[(val >> 8) & 0xf]);
         }
         if (val > 0xf)
         {
            STUFF(basis_hex[(val >> 4) & 0xf]);
         }
         STUFF(basis_hex[val & 0xf]);
         department++;
         if (department < 8 && department != double_colon) STUFF(':');
      }
      STUFF('\0');
   //   return str;
   #undef STUFF
   }


} // namespace str


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

namespace str
{

CLASS_DECL_APEX void to(in_addr & addrParam, const ansichar * string)
{

   c_in_addr & addr = (c_in_addr &) addrParam;


   string_array stra;

   stra.add_tokens(string, ".");

   if(stra.get_count() != 4)
      throw parsing_exception("to in_addr (stra.get_count() != 4)");

   i32 i1 = ansi_to_i32(stra[0]);

   if(i1 < 0 || i1 > 255)
      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (I)");

   i32 i2 = ansi_to_i32(stra[1]);

   if(i2 < 0 || i2 > 255)
      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (II)");

   i32 i3 = ansi_to_i32(stra[2]);

   if(i3 < 0 || i3 > 255)
      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (III)");

   i32 i4 = ansi_to_i32(stra[3]);

   if(i4 < 0 || i4 > 255)
      throw parsing_exception("to in_addr (i1 < 0 || i1 > 255) (IV)");

   addr.S_un.S_un_b.s_b1 = i1;

   addr.S_un.S_un_b.s_b2 = i2;

   addr.S_un.S_un_b.s_b3 = i3;

   addr.S_un.S_un_b.s_b4 = i4;

   //addr.S_un.S_addr = HTONL(addr.S_un.S_addr);

   //return true;

}

} // namespace str

inline string ip_to_string(byte b1, byte b2, byte b3, byte b4)
{

   string str;

   char * psz = str.get_string_buffer(20);

   ansi_concatenate_i64(psz, b1);

   ansi_concatenate(psz, ".");

   ansi_concatenate_i64(psz, b2);

   ansi_concatenate(psz, ".");

   ansi_concatenate_i64(psz, b3);

   ansi_concatenate(psz, ".");

   ansi_concatenate_i64(psz, b4);

   str.release_string_buffer();

   return str;

}


namespace str
{


   CLASS_DECL_APEX void from(string & str, const in_addr &  addr)
   {
   #if defined(WINDOWS)
      str = ip_to_string(
            addr.S_un.S_un_b.s_b1,
            addr.S_un.S_un_b.s_b2,
            addr.S_un.S_un_b.s_b3,
            addr.S_un.S_un_b.s_b4);
   #else
      char sz[32];
      str = inet_ntop(AF_INET, &addr, sz, sizeof(sz));
   #endif
   }


   CLASS_DECL_APEX void from(string & str, const sockaddr_in &  addr)
   {

      return from(str, addr.sin_addr);

   }


   CLASS_DECL_APEX void from(string & str, const sockaddr_in6 &  addr)
   {

      return from(str, addr.sin6_addr);

   }


   CLASS_DECL_APEX void to(sockaddr_in & addr, const ::string & str)
   {

      return to(addr.sin_addr, str);

   }


   CLASS_DECL_APEX void to(sockaddr_in6 & addr, const ::string & str)
   {

      return to(addr.sin6_addr, str);

   }


   CLASS_DECL_APEX void from(string & str, const sockaddr & addr)
   {

      if(addr.sa_family == AF_INET)
      {

         from(str, *(sockaddr_in *)addr.sa_data);

      }
      else if(addr.sa_family == AF_INET6)
      {

         from(str, *(sockaddr_in6 *)addr.sa_data);

      }
      else
      {

         throw ::exception::exception(error_invalid_argument, "unexpected address family");

      }

   }


   CLASS_DECL_APEX void to(const sockaddr & addr, string & str)
   {

      if (addr.sa_family == AF_INET)
      {

         to(*(sockaddr_in *)addr.sa_data, str);

      }
      else if (addr.sa_family == AF_INET6)
      {

         to(*(sockaddr_in6 *)addr.sa_data, str);

      }
      else
      {

         throw ::exception::exception(error_invalid_argument, "unexpected address family");

      }

   }


} // namespace str


CLASS_DECL_APEX i32 c_inet_pton(i32 af, const char *src, void *dst)
{

   if(af == AF_INET)
   {

      in_addr & addr = *(in_addr *) dst;

      ::str::to(addr, src);

      return 1;

   }
   else if(af == AF_INET6)
   {

      in6_addr & addr = *(in6_addr *) dst;

      ::str::to(addr, src);

      return 1;

   }
   else
   {

      return 0;

   }

}


CLASS_DECL_APEX string c_inet_ntop(i32 af, const void *src)
{

   string str;

   if(af == AF_INET)
   {

      in_addr & addr = *(in_addr *)src;

      ::str::from(str, addr);

   }
   else if(af == AF_INET6)
   {

      in6_addr & addr = *(in6_addr *)src;

      ::str::from(str, addr);

   }

   return str;

}

CLASS_DECL_APEX const char * c_inet_ntop(i32 af, const void *src, char *dst, i32 cnt)
{

   if(dst == nullptr)
      return nullptr;

   string str = c_inet_ntop(af, src);

   if(str.is_empty())
      return nullptr;

   if(str.get_length() > cnt)
      return nullptr;

   strcpy(dst, str);

   return dst;

}

#define C_INADDR_NONE ((u32) -1)

CLASS_DECL_APEX u32 c_inet_addr(const char * src)
{

   try
   {


   string_array stra;

   stra.add_tokens(src, ".");

   if(stra.get_count() > 4)
      return C_INADDR_NONE;

   if(stra.get_count() == 1)
   {

      return htonl(c_inet_to_ui(src));

   }
   else
   {

      c_in_addr addr;

      u32 ul;

      if(stra.get_count() == 2)
      {

         ul = c_inet_to_ui(stra[0]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b1 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if((ul & 0xff000000u) != 0)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = ul & 0xFF;

         addr.S_un.S_un_b.s_b3 = (ul >> 8) & 0xFF;

         addr.S_un.S_un_b.s_b4 = (ul >> 16) & 0xFF;

      }
      else if(stra.get_count() == 3)
      {

         ul = c_inet_to_ui(stra[0]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b1 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if(ul > 255)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = (byte) ul;

         ul = c_inet_to_ui(stra[1]);

         if((ul & 0xffff0000u) != 0)
            return C_INADDR_NONE;

         addr.S_un.S_un_b.s_b2 = ul & 0xFF;

         addr.S_un.S_un_b.s_b4 = (ul >> 8) & 0xFF;

      }
      else if(stra.get_count() == 4)
      {

         ::str::to((in_addr &)addr, src);
            return C_INADDR_NONE;

         return addr.S_un.S_addr;

      }
      else
      {

         throw ::exception::exception(error_invalid_argument, "not expected");

      }

      return HTONL(addr.S_un.S_addr);

   }

   }
   catch(...)
   {

   }

   return C_INADDR_NONE;


}


CLASS_DECL_APEX string c_gethostbyname(const char * hostname)
{

//#ifdef _UWP
//
//   return (ref new ::winrt::Windows::Networking::HostName(string(hostname)))->DisplayName;
//
//#else

   struct hostent * pentry = gethostbyname(hostname);

   return c_inet_ntop(pentry->h_addrtype, pentry->h_addr_list[0]);

//#endif

}





string get_file_extension_mime_type(const ::string & strExtension)
{

   if(strExtension == "iso")
   {
      return "application/octetstream";
   }
   else if(strExtension == "mp3")
   {
      return "audio/mpeg";
   }
   else if(strExtension == "exe")
   {
      return "application/x-msdownload";
   }
   else if(strExtension == "spa")
   {
      return "application/x-spa";
   }
   else if(strExtension == "mid")
   {
      return "audio/midi";
   }
   else if(strExtension == "js")
   {
      return "text/javascript";
   }
   else if(strExtension == "css")
   {
      return "text/css";
   }
   else if(strExtension == "xpi")
   {
      return "application/x-xpinstall";
   }
   else if(strExtension == "ttf")
   {
      return "font/ttf";
   }
   else if(strExtension == "ogv")
   {
      return "video/ogg";
   }
   else if(strExtension == "mp4")
   {
      return "video/mp4";
   }
   else if(strExtension == "webm")
   {
      return "video/webm";
   }
   else if(strExtension == "zip")
   {
      return "application/x-zip-compressed";
   }
   else if(strExtension == "crx")
   {
      return "application/x-chrome-extension";
   }
   else if(strExtension == "swf")
   {
      return "application/x-shockwave-flash";
   }
   else if(strExtension == "cab")
   {
      return "application/vnd.ms-cab-compressed";
   }
   else if(strExtension == "jar")
   {
      return "application/x-jar";
   }
   else if(strExtension == "jpg")
   {
      return "image/jpeg";
   }
   else if(strExtension == "png")
   {
      return "image/png";
   }
   else if(strExtension == "gif")
   {
      return "image/gif";
   }
   else if(strExtension == "svg")
   {
      return "image/svg+xml";
   }
   else if(strExtension == "ttf")
   {
      return "application/x-font-ttf";
   }
   else if(strExtension == "otf")
   {
      return "application/x-font-opentype";
   }
   else if(strExtension == "woff")
   {
      return "application/x-font-woff";
   }
   else if(strExtension == "eot")
   {
      return "application/vnd.ms-fontobject";
   }
   else if(strExtension == "md5")
   {
      return "text/plain";
   }
   else if(strExtension == "html")
   {
      return "text/html";
   }
   else if(strExtension == "htm")
   {
      return "text/html";
   }
   else if(strExtension == "rdf")
   {
      return "application/rdf+xml";
   }
   else
   {
      return "";
   }

}


namespace net
{


   i32 family_len(i32 family)
   {

      if(family == AF_INET)
         return sizeof(sockaddr_in);
      else if (family == AF_INET6)
         return sizeof(sockaddr_in6);
      else
         return 0;

   }


} // namespace net







namespace str
{


   CLASS_DECL_APEX string from(const struct sockaddr & sockaddr)
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


} // namespace str




