#include "framework.h"
#include "apex/networking/sockets/_sockets.h"


namespace sockets
{

   #define TMPSIZE 10000




   httpd_socket::httpd_socket() :
      ::object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      http_base_socket(h),
      http_socket(h),
      m_received(0)
   {

      m_http_date = datetime2httpdate(GetDate());

   }



   httpd_socket::~httpd_socket()
   {
   }







   void httpd_socket::Send64(const ::string & str64, const string & type)
   {
   //   Base64 bb;

   /*   if (request().headers()["if-modified-since"].get_string().compare_ci(m_start) == 0)
      {
         m_response.attr("http_status_code") = 304;
         m_response.attr("http_status") = "Not Modified";
         SendResponse();
      }
      else*/
      {
         memory mem;
         ::apex::get_system()->base64().decode(mem, str64);
         m_response.attr("http_status_code") = 200;
         m_response.attr("http_status") = "OK";

         m_response.header("Content-length") = (i64) mem.get_size();
         m_response.header("Content-type") = type;
   //      m_response.header("Last-modified") = m_start;
         SendResponse();

         write((char *)mem.get_data(), mem.get_size());
      }
   }


   string httpd_socket::datetime2httpdate(const string & dt)
   {
      struct tm tp;
      time_t t;
      const char *days[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
      const char *months[] = { "Jan","Feb","Mar","Apr","May","Jun",
                         "Jul","Aug","Sep","Oct","Nov","Dec" };
      int i;
      char s[40];

   /* 1997-12-16 09:50:40 */

      if (dt.get_length() == 19)
      {
         tp.tm_year = atoi(dt.Mid(0,4)) - 1900;
         i = atoi(dt.Mid(5,2)) - 1;
         tp.tm_mon = i >= 0 ? i : 0;
         tp.tm_mday = atoi(dt.Mid(8,2));
         tp.tm_hour = atoi(dt.Mid(11,2));
         tp.tm_min = atoi(dt.Mid(14,2));
         tp.tm_sec = atoi(dt.Mid(17,2));
         tp.tm_wday = 0;
         tp.tm_yday = 0;
         tp.tm_isdst = 0;
         t = mktime(&tp);
         if (t == -1)
         {
            
            //log("datetime2httpdate", 0, "mktime() failed");

         }

         sprintf(s,"%s, %02d %s %d %02d:%02d:%02d GMT",
          days[tp.tm_wday],
          tp.tm_mday,
          months[tp.tm_mon],
          tp.tm_year + 1900,
          tp.tm_hour,tp.tm_min,tp.tm_sec);
      }
      else
      {
         *s = 0;
      }
      return s;
   }


   string httpd_socket::GetDate()
   {
      time_t t = time(nullptr);
      struct tm tp;
   #ifdef _WIN32
      ::memcpy_dup(&tp, localtime(&t), sizeof(tp));
   #else
      localtime_r(&t, &tp);
   #endif
      char slask[40]; // yyyy-mm-dd hh:mm:ss
      sprintf(slask,"%d-%02d-%02d %02d:%02d:%02d",
         tp.tm_year + 1900,
         tp.tm_mon + 1,
         tp.tm_mday,
         tp.tm_hour,tp.tm_min,tp.tm_sec);
      return slask;
   }


   void httpd_socket::Reset()
   {
      http_socket::Reset();
      m_received = 0;
   }



   void httpd_socket::InitSSLServer()
   {
/*      
      // here's the server.pem file we just created above
      // %! remember to change the password to the one you used for your server key
      InitializeContext(m_strCat, m_strCat, "", SSLv23_server_method());
      */
   }



} // namespace sockets


