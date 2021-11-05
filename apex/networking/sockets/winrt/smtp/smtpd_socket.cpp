#include "framework.h"


namespace sockets
{


   smtpd_socket::smtpd_socket() :
      ::object(h.get_application()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_hello(false),
      m_data(false),
      m_header(false)
   {
      SetLineProtocol();
   }


   void smtpd_socket::OnAccept()
   {
      write("220 ESMTP; \r\n");
   }


   void smtpd_socket::OnLine(const string & line)
   {
      if (m_data)
      {
         if (m_header)
         {
            if (!line.get_length())
            {
               if (m_header_line.get_length())
               {
                  ::str::parse pa(m_header_line, ":");
                  string key = pa.getword();
                  key.make_lower();
                  string value = pa.getrest();
                  string lowvalue = value;
                  lowvalue.make_lower();
                  OnHeader(key, value, lowvalue);
               }
               m_header = false;
               OnHeaderComplete();
            }
            else
               if (line[0] == ' ' || line[0] == '\t')
               {
                  m_header_line += line;
               }
               else
               {
                  if (m_header_line.get_length())
                  {
                     ::str::parse pa(m_header_line, ":");
                     string key = pa.getword();
                     key.make_lower();
                     string value = pa.getrest();
                     string lowvalue = value;
                     lowvalue.make_lower();
                     OnHeader(key, value, lowvalue);
                  }
                  m_header_line = line;
               }
         }
         else
            if (line == ".")
            {
               m_data = false;
               if (OnDataComplete())
                  write("250 OK\r\n");
               else
                  write("550 Failed\r\n");
            }
            else
               if (line.get_length() && line[0] == '.')
               {
                  OnData(line.Mid(1));
               }
               else
               {
                  OnData(line);
               }
               return;
      }
      ::str::parse pa(line);
      string cmd = pa.getword();
      cmd.make_upper();
      if (cmd == "EHLO")
      {
         if (!OnHello(pa.getrest()))
         {
            write("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            write("250 mail.alhem.net\r\n");
         }
      }
      else      if (cmd == "HELO")
      {
         if (!OnHello(pa.getrest()))
         {
            write("550 Failed\r\n");
         }
         else
         {
            m_hello = true;
            write("250 mail.alhem.net\r\n");
         }
      }
      else      if (!m_hello)
      {
         OnAbort(SMTP_NO_HELLO);
         SetCloseAndDelete();
      }
      else      if (cmd == "MAIL") // mail from:
      {
         ::str::parse pa(line, ":");
         pa.getword(); // 'mail'
         pa.getword(); // 'from'
         string email = pa.getrest();
         email.make_lower();
         ::net::email_address addr( email );
         if (addr.get_name().get_length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            write("500 Name too long.\r\n");
            return;
         }
         if (addr.get_domain().get_length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            write("500 Domain too long.\r\n");
            return;
         }

         if (!OnMailFrom( addr ))
         {
            write("550 Failed\r\n");
         }
         else
         {
            write("250 OK\r\n");
         }
      }
      else      if (cmd == "RCPT") // rcpt to:
      {
         ::str::parse pa(line, ":");
         pa.getword(); // 'rcpt'
         pa.getword(); // 'to'
         string email = pa.getrest();
         email.make_lower();
         // %! reject based on ::account::user / domain?
         ::net::email_address addr( email );

         if (addr.get_name().get_length() > 64)
         {
            OnAbort(SMTP_NAME_TOO_LONG);
            write("500 Name too long.\r\n");
            return;
         }
         if (addr.get_domain().get_length() > 64)
         {
            OnAbort(SMTP_DOMAIN_TOO_LONG);
            write("500 Domain too long.\r\n");
            return;
         }

         if (!OnRcptTo( addr ))
         {
            write("553 Failed\r\n");
         }
         else
         {
            write("250 OK\r\n");
         }
      }
      else      if (cmd == "DATA")
      {
         write("354 Enter mail, end with \".\" on a line by itself\r\n");
         m_data = true;
         m_header = true;
      }
      else      if (cmd == "RSET")
      {
         m_data = false;
         m_header = false;
         OnRset();
         write("250 OK\r\n"); // %! ???
      }
      else   if (cmd == "QUIT")
      {
         OnAbort(SMTP_QUIT);
         write("221 Bye Bye\r\n");
         SetCloseAndDelete();
      }
      else      if (cmd == "NOOP")
      {
         write("250 OK\r\n");
      }
      else
      {
         OnNotSupported(cmd, pa.getrest());
      }
   }

} // namespace sockets

