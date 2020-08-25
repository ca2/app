#pragma once


namespace sockets
{

   class response;

   class CLASS_DECL_BASE http_base_socket : public http_socket
   {
   public:


      http_base_socket(base_socket_handler& h);
      ~http_base_socket();


      void OnFirst();
      void OnHeader(id key, const string & value);
      void OnHeaderComplete();
      void OnData(const char *,memsize);

      void Respond();

      void OnWriteComplete();


      virtual void OnExecute() = 0;
      virtual void OnResponseComplete();

      string set_cookie(
         const char * name,
         var var,
         int iExpire,
         const char * path,
         const char * domain,
         bool bSecure);

      virtual void on_compress();



      void Reset();

      void Execute();
      int m_iContentLength;
   };




} // namespace sockets


