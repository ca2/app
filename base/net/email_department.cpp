#include "framework.h"
#include "aura/net/sockets/_.h"
#include "email_department.h"


namespace net
{


   email_department::email_department()
   {

   }


   bool email_department::utf8_mail(class ::net::email * pemail)
   {

      ::sockets::socket_handler handler(get_context_object());

      ::sockets::smtp_socket socket(handler);

      if(!socket.open((const string &) Context.file().as_string("C:\\sensitive\\sensitive\\seed\\default_sendmail_host.txt"), (port_t) 25))
         return false;

      socket.m_estate = ::sockets::smtp_socket::state_initial;

      socket.m_pemail = pemail;

      auto tickStart = ::tick::now();

      handler.add(&socket);

      while (true)
      {

         handler.select(8,0);

         if(tickStart.elapsed() > 15_s)
            break;

         if(socket.m_estate == ::sockets::smtp_socket::state_end)
            break;

      }

      return socket.m_estate == ::sockets::smtp_socket::state_sent || socket.m_estate == ::sockets::smtp_socket::state_quit || socket.m_estate == ::sockets::smtp_socket::state_end;
   }


   bool email_department::syntax_is_valid(const string & strEmailAddress)
   {

      auto iAt = strEmailAddress.find('@');

      if (iAt < 0)
      {

         return false;

      }

      if (iAt >= strEmailAddress.length() - 1)
      {

         return false;

      }

      string strDomain = strEmailAddress.Mid(iAt + 1);

      if (strDomain.is_empty())
      {

         return false;

      }

      //auto iLastDot = strDomain.reverse_find('.');

      //if (iLastDot <= 0)
      //{

      //   return false;

      //}

      return true;

   }


   bool email_department::is_valid_public_address(const string& strEmailAddress)
   {

      auto iAt = strEmailAddress.find('@');

      if (iAt < 0)
      {

         return false;

      }

      if (iAt >= strEmailAddress.length() - 1)
      {

         return false;

      }

      string strDomain = strEmailAddress.Mid(iAt + 1);

      if (strDomain.is_empty())
      {

         return false;

      }

      auto iLastDot = strDomain.reverse_find('.');

      if (iLastDot <= 0)
      {

         return false;

      }

      if (!System.url().is_valid_public_domain(strDomain))
      {

         return false;

      }

      return true;

   }



} // namespace base




