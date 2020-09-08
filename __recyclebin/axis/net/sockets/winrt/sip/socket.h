#pragma once


namespace sockets
{


   class CLASS_DECL_AXIS sip_socket :
      public http_tunnel
   {
   public:
      enum e_state
      {
         state_free, // caller/receiver
         state_waiting_call_trying, // caller/server
         state_waiting_call_ringing, // caller/server
         state_waiting_call_ok, // caller/server
         state_ringing, // receiver/server/caller
         state_waiting_bye_ok,
      };

      enum e_error
      {
         error_none,
         error_wrong_state,
      };

      e_error m_eerrorLast;

      sip_socket(base_socket_handler& );
      void invite(const char * pszAddress);
      void OnHeaderComplete();


   };


} // namespace sockets


