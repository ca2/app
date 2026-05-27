#pragma once


namespace sockets
{

   class Ajp13Socket : public AjpBaseSocket
   {
   public:


      memsize     m_body_size_left;
      http::request     m_request;
      http::response    m_response;


      Ajp13Socket();

      void OnHeader( ::i16 atom, ::i16 len );
      void OnPacket( const_char_pointer pszBuffer, memsize sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

      void ReceiveBody( const_char_pointer pszBuffer, memsize sz );
      void ReceiveForwardRequest( const_char_pointer pszBuffer, memsize sz );
      void ReceiveShutdown( const_char_pointer pszBuffer, memsize sz );
      void ReceivePing( const_char_pointer pszBuffer, memsize sz );
      void ReceiveCPing( const_char_pointer pszBuffer, memsize sz );
      void Execute();

   };


} // namespace sockets

