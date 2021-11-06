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

      void OnHeader( i16 id, i16 len );
      void OnPacket( const char *buf, memsize sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

      void ReceiveBody( const char *buf, memsize sz );
      void ReceiveForwardRequest( const char *buf, memsize sz );
      void ReceiveShutdown( const char *buf, memsize sz );
      void ReceivePing( const char *buf, memsize sz );
      void ReceiveCPing( const char *buf, memsize sz );
      void Execute();

   };


} // namespace sockets

