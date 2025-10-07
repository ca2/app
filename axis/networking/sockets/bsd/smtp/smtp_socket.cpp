#include "framework.h"
#include "smtp_socket.h"
#include "apex/networking/networking.h"
#include "apex/networking/sockets/base/base_socket_handler.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/base64.h"
#include "acme/prototype/string/parse.h"
#include "acme/prototype/string/str.h"
#include "apex/networking/email.h"
//#include "axis/networking/_networking.h"


namespace sockets
{


	smtp_socket::smtp_socket()
	{

		m_bEnded = false;

	}


	void smtp_socket::initialize(::particle* pparticle)
	{

		tcp_socket::initialize(pparticle);

		SetLineProtocol();

	}

	void smtp_socket::OnException()
	{

		//tcp_socket::OnException();

		if (is_connecting())
		{

			m_strError += "smtp_socket::OnException while connecting\n";

			int iError = this->socket_handler()->m_iSelectErrno;

			if (iError == 0)
			{

				information() << "smtp_socket::OnException while connecting select error is 0, ignoring it from here\n";

				return;

			}

			if(iError == ETIMEDOUT)
			{

				m_strError += "timed out\n";

			}
			else
			{
				m_strError += "failed\n";

			}

			//int iGetConnectionRetry = GetMaximumConnectionRetryCount();

			//int iGetConnectionRetries = GetConnectionRetryCount();

			//if (Socks4())
			//{

			//   OnSocks4ConnectFailed();

			//}
			//else if(iGetConnectionRetry == -1 ||
			//        (iGetConnectionRetry &&
			//           iGetConnectionRetries < iGetConnectionRetry))
			//{

			//   const int nBufSize = 1024;

			//   char buf[nBufSize];

			//   socket_id iGetSocket = get_socket_id();

			//   int n = ::recv(iGetSocket, (char*)buf, (int)nBufSize, MSG_OOB);

			//   information() << "got " << n << " bytes of Out of Band Data";

			//   // even though the connection failed at once, only retry after
			//   // the connection timeout
			//   // should we even try to connect again, when CheckConnect returns
			//   // false it's because of a connection error - not a timeout...
			//}
			//else
			{
			   //set_connecting(false); // tnx snibbe
			   SetCloseAndDelete();
			   OnConnectFailed();
			}
			return;
		}
		//// %! exception doesn't always mean something bad happened, this code should be reworked
		//// errno valid here?
		int err = SoError();

		::string strBsdSocketError;
		
		strBsdSocketError << "exception on select " << err << 
			
			system()->networking()->so_error_description(err);


		m_strError += "smtp_socket::OnException\n";

		SetCloseAndDelete();

	}


	void smtp_socket::OnLine(const string& line)
	{

		SetNonblocking(false);
		::parse pa(line);
		string code = pa.getword();

		code.make_upper();
		if (m_estate == e_state_initial)
		{
			if (code == "220")
			{
				m_estate = state_hello;
				//print("HELO localhost\r\n");
				print("EHLO account.ca2.network\r\n");
				m_strError += "Got initial response\n";
			}
		}
		else if (m_estate == state_hello)
		{
			if (code == "250" || code.case_insensitive_order("250-Auth") == 0)
			{
				if (code.case_insensitive_order("250-Auth") == 0 || pa.getword().case_insensitive_order("auth") == 0)
				{
					string_array stra;
					stra.explode(" ", pa.getrest());
					stra.trim();
					if (stra.case_insensitive_contains("login"))
					{
						m_estate = state_auth_login;
						print("AUTH LOGIN\r\n");
					}
				}
				else
				{

					m_strError += "Sending login '" + m_pemail->m_addressSender.to_string() + "'\n";

					m_estate = state_sender;
					print("MAIL FROM: " + m_pemail->m_addressSender.to_string() + "\r\n");
				}
			}
		}
		else if (m_estate == state_auth_login)
		{
			if (code == "334")
			{

				string strWord = pa.getword();

				auto psystem = system();

				auto pbase64 = psystem->base64();

				string strRequest = pbase64->decode(strWord);
				string strResponse;
				if (::str::case_insensitive_find("username", strRequest) >= 0)
				{

					auto psystem = system();

					auto pbase64 = psystem->base64();

					::file::path pathDefaultSendMail;

					pathDefaultSendMail = directory_system()->sensitive() / "seed/default_sendmail_user.txt";

					strResponse = pbase64->encode(file()->as_string(pathDefaultSendMail));

					print(strResponse + "\r\n");

				}
				else if (::str::case_insensitive_find("password", strRequest) >= 0)
				{


					m_strError += "Sending password\n";
					auto psystem = system();

					auto pbase64 = psystem->base64();

					::file::path pathDefaultSendPass;

					pathDefaultSendPass = directory_system()->sensitive() / "seed/default_sendmail_pass.txt";

					strResponse = pbase64->encode(file()->as_string(pathDefaultSendPass));

					print(strResponse + "\r\n");

				}
			}
			else if (code == "235")
			{
				m_estate = state_sender;
				::string strSender = m_pemail->m_addressSender.to_string();
				print("MAIL FROM: <" + strSender + ">\r\n");
			}
			else if (code == "535")
			{

				string strWord = pa.getword();

				auto psystem = system();

				m_strError += "\nBad Credentials";

				m_bEnded = true;

			}

		}
		else if (m_estate == state_sender)
		{
			if (code == "250")
			{
				m_estate = state_recipient;
				print("RCPT TO: <" + m_pemail->m_addressRecipient.to_string() + ">\r\n");
			}
		}
		else if (m_estate == state_recipient)
		{
			if (code == "250")
			{
				m_estate = state_data;
				print("DATA\r\n");
			}
		}
		else if (m_estate == state_data)
		{
			if (code.substr(0, 1) == "3")
			{

				m_estate = state_body;

				auto psystem = system();

				auto pbase64 = psystem->base64();

				print("Subject:  =?utf-8?B?" + pbase64->encode(m_pemail->m_strSubject) + "?=\r\n");
				m_pemail->prepare_headers();
				print(m_pemail->m_strHeaders);
				print("Content-Type: text/plain; charset=\"utf-8\"\r\n");
				print("\r\n");
				string strBody = m_pemail->m_strBody;
				strBody.replace_with("\n", "\r\n");
				string_array stra;
				stra.add_tokens(strBody, "\n", true);
				for (int i = 0; i < stra.get_count(); i++)
				{
					if (stra[i].substr(0, 1) == ".")
					{
						print("." + stra[i] + "\r\n");
					}
					else
					{
						print(stra[i] + "\r\n");
					}
				}
				print(".\r\n");
			}
		}
		else if (m_estate == state_body)
		{
			if (code == "250")
			{
				m_estate = state_quit;
				print("QUIT\r\n");
			}
		}
		else if (m_estate == state_quit)
		{
			if (code == "221")
			{
				m_estate = state_end;
			}
		}
	}


} // namespace sockets

