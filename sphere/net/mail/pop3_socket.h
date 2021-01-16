#pragma once


#include "aura/net/net_sockets.h"


namespace mail
{


   class pop3;


   class CLASS_DECL_SPHERE pop3_socket :
      public ::sockets::tcp_socket
   {
   public:


      enum enum_state
      {

         state_disconnected,
         state_auth_1,
         state_auth_2,
         state_transaction,
         state_listmessages_start,
         state_listmessages,
         state_receive_message,
         state_receive_headers,
         state_receive_body,
         state_finished,
         state_stat_start,
         state_top_start,
         state_receive_top_headers,
         state_receive_top_body,
         state_receive_specific_list,
         state_receive_list,
         state_retr_only_headers_start,
         state_retr_only_headers,
         state_retr_start,
         state_retr_headers,
         state_retr_body,
         state_quit,
         state_rset

      };

      pop3 *   m_ppop3;
      bool m_bSsl;
      bool m_bTls;
      string m_strKey;
      string m_strValue;

      enum_state  m_estate;


      pop3_socket(::sockets::socket_handler & handler);
      virtual ~pop3_socket();
      bool retrieve();

      void InitSSLClient();


      void OnLine(const string & );


      void SendPrompt();


   };


} // namespace mail



