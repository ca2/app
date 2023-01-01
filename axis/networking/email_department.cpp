#include "framework.h"
#include "email_department.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/url.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/email.h"
#include "apex/networking/sockets/basic/socket_handler.h"
#include "axis/networking/sockets/bsd/smtp/smtp_socket.h"


namespace networking
{


   email_department::email_department()
   {

   }


   bool email_department::utf8_mail(class ::networking::email * pemail)
   {

      auto phandler = __create < ::sockets::socket_handler >();

      auto psocket = __create_new < ::sockets::smtp_socket >();

      string strHost = file()->as_string("/sensitive/sensitive/seed/default_sendmail_host.txt");

      if (!psocket->open(strHost, (port_t)25))
      {

         return false;

      }

      psocket->m_estate = ::sockets::smtp_socket::e_state_initial;

      psocket->m_pemail = pemail;

      auto tickStart = ::time::now();

      phandler->add(psocket);

      while (true)
      {

         phandler->select(8,0);

         if (tickStart.elapsed() > 15_s)
         {

            break;

         }

         if (psocket->m_estate == ::sockets::smtp_socket::state_end)
         {

            break;

         }

      }

      return psocket->m_estate == ::sockets::smtp_socket::state_sent || psocket->m_estate == ::sockets::smtp_socket::state_quit || psocket->m_estate == ::sockets::smtp_socket::state_end;

   }


   bool email_department::syntax_is_valid(const ::string & strEmailAddress)
   {

      auto iAt = strEmailAddress.find_index('@');

      if (iAt < 0)
      {

         return false;

      }

      if (iAt >= strEmailAddress.length() - 1)
      {

         return false;

      }

      string strDomain = strEmailAddress.substr(iAt + 1);

      if (strDomain.is_empty())
      {

         return false;

      }

      //auto iLastDot = strDomain.rear_find('.');

      //if (iLastDot <= 0)
      //{

      //   return false;

      //}

      return true;

   }


   bool email_department::is_valid_public_address(const string& strEmailAddress)
   {

      auto iAt = strEmailAddress.find_index('@');

      if (iAt < 0)
      {

         return false;

      }

      if (iAt >= strEmailAddress.length() - 1)
      {

         return false;

      }

      string strDomain = strEmailAddress.substr(iAt + 1);

      if (strDomain.is_empty())
      {

         return false;

      }

      auto iLastDot = strDomain.rear_find_index('.');

      if (iLastDot <= 0)
      {

         return false;

      }

      auto psystem = acmesystem();

      auto purl = psystem->url();

      if (!purl->is_valid_public_domain(strDomain))
      {

         return false;

      }

      return true;

   }



} // namespace axis




