#include "framework.h"
#include "smtpd_socket.h"
#include "acme/prototype/string/parse.h"
#include "apex/networking/email_address.h"
//#include "axis/networking/_networking.h"


namespace sockets
{


   smtpd_socket::smtpd_socket() :
      m_hello(false),
      m_data(false),
      m_header(false)
   {

      SetLineProtocol();

   }


   void smtpd_socket::OnAccept()
   {

      print("220 ESMTP; \r\n");

   }


   void smtpd_socket::OnLine(const ::scoped_string & scopedstrLine)
   {

      if (m_data)
      {

         if (m_header)
         {

            if (!scopedstrLine.length())
            {
               if (m_header_line.length())
               {
                  ::parse pa(m_header_line, ":"_ansi);
                  string key = pa.getword();
                  key.make_lower();
                  string value = pa.getrest();
                  OnHeader(key, value);
               }
               m_header = false;
               OnHeaderComplete();
            }
            else
            if (scopedstrLine[0] == ' ' || scopedstrLine[0] == '\t')
            {
               m_header_line += scopedstrLine;
            }
            else
            {
               if (m_header_line.length())
               {
                  ::parse pa(m_header_line, ":"_ansi);
                  string key = pa.getword();
                  key.make_lower();
                  string value = pa.getrest();
                  OnHeader(key, value);
               }
               m_header_line = scopedstrLine;
            }
         }
         else
         if (scopedstrLine == ".")
         {
            m_data = false;
            if (OnDataComplete())
               print("250 OK\r\n");
            else
               print("550 Failed\r\n");
         }
         else
         if (scopedstrLine.length() && scopedstrLine[0] == '.')
         {
            OnData(scopedstrLine.substr(1));
         }
         else
         {
            OnData(scopedstrLine);
         }
         return;
      }
      ::parse pa(scopedstrLine);
      string cmd = pa.getword();
      cmd.make_upper();
      if (cmd == "EHLO")
      {
         if (!OnHello(pa.getrest()))
         {
            print("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            print("250 mail.alhem.net\r\n");
         }
      }
      else
      if (cmd == "HELO")
      {
         if (!OnHello(pa.getrest()))
         {
            print("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            print("250 mail.alhem.net\r\n");
         }
      }
      else
      if (!m_hello)
      {
         OnAbort(SMTP_NO_HELLO);
         SetCloseAndDelete();
      }
      else
      if (cmd == "MAIL") // mail from:
      {
         ::parse pa(scopedstrLine, ":"_ansi);
         pa.getword(); // 'mail'
         pa.getword(); // 'from'

         string strEmailAddress = pa.getrest();

         strEmailAddress.make_lower();

         ::networking::email_address addr( strEmailAddress );

         if (addr.get_name().length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            print("500 Name too long.\r\n");
            return;
         }

         if (addr.get_domain().length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            print("500 Domain too long.\r\n");
            return;
         }

         if (!OnMailFrom( addr ))
         {
            print("550 Failed\r\n");
         }
         else
         {
            print("250 OK\r\n");
         }
      }
      else if (cmd == "RCPT") // rcpt to:
      {
         ::parse pa(scopedstrLine, ":"_ansi);
         pa.getword(); // 'rcpt'
         pa.getword(); // 'to'

         string strEmailAddress = pa.getrest();

         strEmailAddress.make_lower();

         // %! reject axisd on ::account::user / domain?

         ::networking::email_address addr(strEmailAddress);

         if(addr.get_name().length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            print("500 Name too long.\r\n");
            return;
         }

         if (addr.get_domain().length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            print("500 Domain too long.\r\n");
            return;
         }

         if (!OnRcptTo( addr ))
         {
            print("553 Failed\r\n");
         }
         else
         {
            print("250 OK\r\n");
         }
      }
      else
      if (cmd == "DATA")
      {
         print("354 Enter mail, end with \".\" on a line by itself\r\n");
         m_data = true;
         m_header = true;
      }
      else
      if (cmd == "RSET")
      {
         m_data = false;
         m_header = false;
         OnRset();
         print("250 OK\r\n"); // %! ???
      }
      else
      if (cmd == "QUIT")
      {
         OnAbort(SMTP_QUIT);
         print("221 Bye Bye\r\n");
         SetCloseAndDelete();
      }
      else
      if (cmd == "NOOP")
      {
         print("250 OK\r\n");
      }
      else
      {
         OnNotSupported(cmd, pa.getrest());
      }
   }

} // namespace sockets

