#pragma once


namespace sockets
{


   class CLASS_DECL_AURA sip_socket :
      public http_tunnel
   {
   public:
      enum enum_state
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

      sip_socket();
      void invite(const ::string & pszAddress);
      void OnHeaderComplete();


   };


} // namespace sockets


