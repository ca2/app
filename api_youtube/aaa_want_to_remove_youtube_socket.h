#pragma once


namespace youtube
{


   class CLASS_DECL_APP_CORE_YOUTUBE youtube_socket:
      public ::sockets::websocket_client
   {
   public:


      enum enum_state
      {

         state_disconnected,
         state_joining,
         state_cap_ls,
         state_cap_req_youtube_membership,
         state_cap_req_youtube_tags,
         state_cap_req_youtube_commands,
         state_cap_list,
         state_connected,
         state_finished,

      };

      bool m_bTags;
      bool m_bMembership;
      bool m_bCommands;

      comm *   m_pcomm;
      //bool m_bSsl;
      //bool m_bTls;
      string m_strKey;
      string m_strValue;

      enum_state  m_estate;


      youtube_socket(::sockets::socket_handler * handler, const string & url_in);
      virtual ~youtube_socket();
      bool retrieve();

      


      void OnLine(const string &);


      void SendPrompt();

      //virtual void msg(const string &str);
      virtual void on_bot(string strUser, string strText);
      virtual void on_pres(string strUser,string strType);

      virtual void process_line(string strLine);

      virtual void on_websocket_data(string str);

   };


} // namespace youtube



