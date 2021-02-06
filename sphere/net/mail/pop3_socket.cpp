#include "StdAfx.h"

namespace mail
{

   pop3_socket::pop3_socket(ISocketHandler& h) :
      ::ca::ca(h.get_context_application()),
      TcpSocket(h),
      m_estate(state_disconnected)
   {
      m_bSsl = false;
      m_bTls = false;
	   SetLineProtocol();
   }


   pop3_socket::~pop3_socket()
   {
   }




   void pop3_socket::OnLine(const string& line)
   {
      string strLine(line);
      AStrArray stra;
	   switch (m_estate)
	   {
	   case state_disconnected:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
            if(m_bTls)
            {
               m_estate = state_auth_1;
               Send("STLS\r\n");
            }
            else
            {
               m_estate = state_auth_2;
               string str = "USER " + m_ppop3->m_paccount->m_strLogin + "\r\n";
               Send((const char *) str);
            }
         }
		   break;
	   case state_auth_1:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
            m_bTls = true;
            m_estate = state_auth_2;
            EnableSSL();
            OnSSLConnect();
            //Handler().Select(1, 0);
   /*         if(GetOutputLength())
               OnWrite();
		      if(IsReconnect())
				   OnReconnect();
			   else
               OnConnect();
            Handler().AddList(GetSocket(), LIST_CALLONCONNECT, false);*/
            string str = "USER " + m_ppop3->m_paccount->m_strLogin + "\r\n";
            Send((const char *) str);
         }
		   break;
	   case state_auth_2:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
            m_estate = state_transaction;
            string strPass;
            Application.crypt().file_get(
               Context.dir().default_userappdata(m_ppop3->m_paccount->m_strEmail, "license_auth/00003"),
               strPass);
            Send("PASS " + strPass + "\r\n");
         }
		   break;
	   case state_transaction:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
            m_estate = state_listmessages_start;
            Send("UIDL\r\n");
         }
		   break;
	   case state_listmessages_start:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
            m_estate = state_listmessages;
         }
		   break;
	   case state_listmessages:
         if(strLine == ".")
         {

            m_ppop3->filter_id();
            if(retrieve())
               m_estate = state_receive_message;
            else
               m_estate = state_transaction;
         }
         else
         {
            stra.add_tokens(strLine, " ", true);
            m_ppop3->m_straIndex.add(stra[0]);
            m_ppop3->m_straId.add(stra[1]);
         }
		   break;
	   case state_receive_message:
         stra.add_tokens(strLine, " ", true);
         if(stra.get_size() > 0 && stra[0] == "+OK")
         {
               m_estate = state_receive_headers;
               m_ppop3->m_iHeaderLine = 0;
         }
         else
         {
            if(retrieve())
               m_estate = state_receive_message;
            else
               m_estate = state_finished;
         }
		   break;
	   case state_receive_headers:
         if(strLine == ".")
         {
            m_ppop3->store();
            if(retrieve())
               m_estate = state_receive_message;
            else
               m_estate = state_finished;
         }
         else if(strLine == "")
         {
            m_estate = state_receive_body;
         }
         else
         {
            if(m_ppop3->m_iHeaderLine > 0
               && (strLine[0] == '\t' || strLine[0] == ' '))
            {
               m_ppop3->m_strHeaders += strLine;
            }
            else
            {
               if(m_ppop3->m_iHeaderLine > 0)
               {
                  m_ppop3->m_strHeaders += "\r\n";
               }
               m_ppop3->m_strHeaders += strLine;
               m_ppop3->m_iHeaderLine++;
            }
         }
		   break;
	   case state_receive_body:
         if(strLine == ".")
         {
            m_ppop3->store();
            if(retrieve())
               m_estate = state_receive_message;
            else
               m_estate = state_transaction;
         }
         else
         {
            m_ppop3->m_strBody += strLine + "\r\n";
         }
		   break;
	   }
   }

   bool pop3_socket::retrieve()
   {
      if(m_ppop3->m_straId.get_size() == 0)
         return false;
      m_ppop3->m_id = m_ppop3->m_straId[0];
      string strSend;
      strSend.Format("RETR %s\r\n", m_ppop3->m_straIndex[0]);
      Send((const char *) strSend);
      m_ppop3->m_strHeaders.Empty();
      m_ppop3->m_strBody.Empty();
      m_ppop3->m_straId.remove_at(0);
      m_ppop3->m_straIndex.remove_at(0);
      return true;
   }


   void pop3_socket::SendPrompt()
   {
   }




   void pop3_socket::InitSSLClient()
   {
      if(m_bTls)
      {
	      InitializeContext("", TLSv1_method());
      }
      else
      {
         InitializeContext("", SSLv3_method());
      }
   }

} // namespace mail
