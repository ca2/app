#pragma once


namespace sockets
{

   class Ajp13Socket : public AjpBaseSocket
   {
   public:
      Ajp13Socket();

      void OnHeader( short id, short len );
      void OnPacket( const char *buf, memsize sz );

      virtual void Respond();

      void OnTransferLimit();

      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

   private:
      void ReceiveBody( const char *buf, memsize sz );
      void ReceiveForwardRequest( const char *buf, memsize sz );
      void ReceiveShutdown( const char *buf, memsize sz );
      void ReceivePing( const char *buf, memsize sz );
      void ReceiveCPing( const char *buf, memsize sz );
      void Execute();

      memsize m_body_size_left;
      http::request m_request;
      http::response m_response;
   };


} // namespace sockets

