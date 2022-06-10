#include "framework.h"
#include "acme/primitive/string/base64.h"


namespace sockets
{


   smtp_socket::smtp_socket() :
      ::object(h.get_app()),
      base_socket(h),
      socket(h),
      stream_socket(h),
      tcp_socket(h),
      m_email(h.get_app())
   {
      SetLineProtocol();

   }


   void smtp_socket::OnLine(const string & line)
   {
      SetNonblocking(false);
      ::str().parse pa(line);
      string code = pa.getword();

      code.make_upper();
      if(m_estate == e_state_initial)
      {
         if(code == "220")
         {
            m_estate = state_hello;
            //write("HELO localhost\r\n");
            write("EHLO account.ca2.software\r\n");
         }
      }
      else if(m_estate == state_hello)
      {
         if(code == "250")
         {
            if(pa.getword().compare_ci("auth") == 0)
            {
               string_array stra;
               stra.explode(" ", pa.getrest());
               stra.trim();
               if(stra.contains_ci("login"))
               {
                  m_estate = state_auth_login;
                  write("AUTH LOGIN\r\n");
               }
            }
            else
            {
               m_estate = state_sender;
               write("MAIL FROM: " + m_email.m_addressSender.to_string() + "\r\n");
            }
         }
      }
      else if(m_estate == state_auth_login)
      {
         if(code == "334")
         {
            string strWord = pa.getword();
            string strRequest = ::apex::get_system()->base64().decode(strWord);
            string strResponse;
            if(::str().find_ci("username", strRequest) >= 0)
            {
               strResponse = ::apex::get_system()->base64().encode(m_psystem->m_pacmefile->as_string("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\sendmail_user.txt"));
               write(strResponse + "\r\n");
            }
            else if(::str().find_ci("password", strRequest) >= 0)
            {
               strResponse = ::apex::get_system()->base64().encode(m_psystem->m_pacmefile->as_string("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\sendmail_pass.txt"));
               write(strResponse + "\r\n");
            }
         }
         else if(code == "235")
         {
            m_estate = state_sender;
            write("MAIL FROM: " + m_email.m_addressSender.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_sender)
      {
         if(code == "250")
         {
            m_estate = state_recipient;
            write("RCPT TO: " + m_email.m_addressRecipient.to_string() + "\r\n");
         }
      }
      else if(m_estate == state_recipient)
      {
         if(code == "250")
         {
            m_estate = state_data;
            write("DATA\r\n");
         }
      }
      else if(m_estate == state_data)
      {
         if(code.Mid(0, 1) == "3")
         {
            m_estate = state_body;
            write("Subject:  =?utf-8?B?" + ::apex::get_system()->base64().encode(m_email.m_strSubject) + "?=\r\n");
            m_email.prepare_headers();
            write(m_email.m_strHeaders);
            write("Content-Type: text/plain; charset=\"utf-8\"\r\n");
            write("\r\n");
            string strBody = m_email.m_strBody;
            strBody.replace("\r\n", "\n");
            string_array stra;
            stra.add_tokens(strBody, "\n", true);
            for(int i = 0; i < stra.get_count(); i++)
            {
               if(stra[i].Mid(0, 1) == ".")
               {
                  write("." + stra[i] + "\r\n");
               }
               else
               {
                  write(stra[i] + "\r\n");
               }
            }
            write(".\r\n");
         }
      }
      else if(m_estate == state_body)
      {
         if(code == "250")
         {
            m_estate = state_quit;
            write("QUIT\r\n");
         }
      }
      else if(m_estate == state_quit)
      {
         if(code == "221")
         {
            m_estate = state_end;
         }
      }
   }


} // namespace sockets

